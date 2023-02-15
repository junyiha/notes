#include <rtdk.h>
#include <sys/mman.h>

#include <atomic>
#include <chrono>
#include <cstring>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <thread>

#include <alchemy/task.h>
#include <alchemy/timer.h>
/*****************************/

/******** ethercat ***********/
#include "ecat/ecat_master.h"
#include "ecat/ecat_taike.h"
/*****************************/

#include "glog/logging.h"

#include "control/control.h"
#include "driver/driver.h"
/************* webserver *************/
// #include "webserver/server.h"
#include "getopt.h"
#include <syslog.h>
#include "webserver/webserver.h"

/************************************/

#include "dynamics/solver/fk_solver_pos_kdl.h"
#include "dynamics/solver/fk_solver_pos_recursive.h"
#include "dynamics/solver/ik_solver_pos_lma.h"
#include "gflags/gflags.h"
#include "planning/planning.h"
#include "protocol/configuration/manipulator.h"

using namespace arwen;
using namespace arwen::planning;
using namespace arwen::driver;
using namespace arwen::control;
using namespace arwen::dynamics::common;
using namespace arwen::dynamics::chain;
using namespace arwen::protocol::configuration;
using namespace arwen::dynamics::solver;

/***********************/
#define TAIKE_TOTAL 6
#define ARM_DOF 6
#define CYCLE_NS 1000e3  // 1 ms
#define CYCLE_NS_WS 300000e3  // 300 ms
#define JOINTS_PULSE (131072.0 / 2.0 / M_PI)

Master ecatmaster;
EcatTaike ecat_taike[ARM_DOF];

std::atomic_bool system_ready = false;
std::atomic_bool break_flag = false;

// Xenomai RT tasks
RT_TASK driver_task;
RT_TASK control_task;
RT_TASK planning_task;
RT_TASK ws_auto_send_task;
std::atomic_bool AutoSendTask_ = false;  //  标志定时发送信息的线程是否创建： true, 已创建； false， 未创建

Planning planner;
FkSolverPosKdl fk_solver_kdl;
IkSolverPosLma ik_solver_pos_lma;
FkSolverPosRecursive fk_solver_pos;
bool running = false;
bool flag_movel = false;
bool flag_speedj = false;
bool flag_speedl = false;
// parameters of joint space and cartesian space:
double cart_max_vel = 0.01;
double cart_max_acc = 0.01;
double cart_max_jerk = 0.01;
double rot_max_vel = 0.01;
double rot_max_acc = 0.01;
double rot_max_jerk = 0.01;
JointVector max_vel(6);
JointVector max_acc(6);
JointVector max_jerk(6);

/***********************/
std::shared_ptr<arwen::dynamics::chain::Chain> chain = std::make_shared<arwen::dynamics::chain::Chain>(Manipulator());

std::shared_ptr<std::atomic<uint64_t>> timestamp = std::make_shared<std::atomic<uint64_t>>();

std::shared_ptr<std::atomic<protocol::message::DriverStatusMessage>> 
    driver_status_message = std::make_shared<std::atomic<protocol::message::DriverStatusMessage>>();

std::shared_ptr<std::atomic<protocol::message::DriverCommandMessage>>
    driver_command_message = std::make_shared<std::atomic<protocol::message::DriverCommandMessage>>();

std::shared_ptr<std::atomic<protocol::message::JointStatusMessage>>
    joint_status_message = std::make_shared<std::atomic<arwen::protocol::message::JointStatusMessage>>();

std::shared_ptr<std::atomic<protocol::message::JointCommandMessage>>
    joint_command_message = std::make_shared<std::atomic<protocol::message::JointCommandMessage>>();
/*******************/

int isSlaveInit() 
{
  int taike_count = 0;
  int slave_count = 0;

  for (int i = 0; i < TAIKE_TOTAL; ++i) 
  {
    if (ecat_taike[i].initialized()) { taike_count++; }
  }

  for (int j = 0; j < TAIKE_TOTAL; j++) 
  {
    if (ecatmaster.GetSlaveState(j) == 0x08) { slave_count++; }
  }

  if ((taike_count == TAIKE_TOTAL) && (slave_count == TAIKE_TOTAL))
    return 1;
  else
    return 0;
}

void signal_handler(int signum) 
{
  printf("\nSignal Interrupt: %d", signum);
  break_flag = true;
}

// ethercat update task
void DriverThread(void* arg) 
{
  RTIME now_ns;
  uint64_t tid = 0;
  unsigned long long count = 0;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS);

  protocol::message::DriverStatusMessage driver_status_buffer;
  protocol::message::DriverCommandMessage driver_command_buffer;
  while (true) 
  {
    rt_task_wait_period(nullptr);  // wait for next cycle
    if (break_flag) break;
    now_ns = rt_timer_read();
    timestamp->store(now_ns);
    // Recv pdo
    ecatmaster.RxUpdate();
    // driver status data
    driver_status_buffer.header.timestamp_ns = now_ns;
    driver_status_buffer.header.publish_timestamp_ns = now_ns;
    driver_status_buffer.header.process_sequence_number = tid;
    for (int k = 0; k < ARM_DOF; k++) 
    {
      driver_status_buffer.data[k].joint_position = ecat_taike[k].actual_position_ / JOINTS_PULSE;
      driver_status_buffer.data[k].joint_velocity = ecat_taike[k].actual_velocity_;
      driver_status_buffer.data[k].joint_torque   = ecat_taike[k].actual_torque_;
      ecat_taike[k].target_position_ = ecat_taike[k].actual_position_;
    }
    driver_status_message->store(driver_status_buffer);
    
    if (!system_ready) 
    {
      driver_command_buffer.header = driver_status_buffer.header;
      memcpy(&driver_command_buffer, &driver_status_buffer, sizeof(protocol::message::DriverMessage));
      driver_command_message->store(driver_command_buffer);
    } 
    else 
    {
      driver_command_buffer = driver_command_message->load();
      ecat_taike[0].target_position_ = std::round(driver_command_buffer.data[0].joint_position * JOINTS_PULSE);
      ecat_taike[1].target_position_ = std::round(driver_command_buffer.data[1].joint_position * JOINTS_PULSE);
      ecat_taike[2].target_position_ = std::round(driver_command_buffer.data[2].joint_position * JOINTS_PULSE);
      ecat_taike[3].target_position_ = std::round(driver_command_buffer.data[3].joint_position * JOINTS_PULSE);
      ecat_taike[4].target_position_ = std::round(driver_command_buffer.data[4].joint_position * JOINTS_PULSE);
      ecat_taike[5].target_position_ = std::round(driver_command_buffer.data[5].joint_position * JOINTS_PULSE);
    }

    // Send pdo
    ecatmaster.TxUpdate(0, rt_timer_read());
    if (isSlaveInit()) 
    {
      // printf("----system_ready==1---\n");
      ++count;
      system_ready = (count > 1000);
    } 
    else 
    {
      count = 0;
      system_ready = false;
    }

    ++tid;
  }
}

void ControlThread(void* arg) 
{
  RTIME now_ns;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS);

  Control control;
  control.Init(chain, timestamp, joint_command_message, joint_status_message, driver_command_message, driver_status_message);

  while (true) 
  {
    rt_task_wait_period(nullptr);  // wait for next cycle

    if (break_flag) break;
    if (!system_ready) 
    {
      arwen::protocol::message::JointStatusMessage joint_status_buffer = 
          control.ConvertDriverStatusToJointStatus(driver_status_message->load());

      arwen::protocol::message::JointCommandMessage joint_command_buffer;
      memcpy(&joint_command_buffer, &joint_status_buffer, sizeof(protocol::message::JointMessage));

      joint_status_message->store(joint_status_buffer);
      joint_command_message->store(joint_command_buffer);
      continue;
    }
    control.ProcessFrame();
  }
}

void PlanningThread(void* arg) 
{
  RTIME now_ns;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS);
  protocol::message::JointStatusMessage joint_status_buffer;

  planner.Init(0.001, chain, timestamp, joint_command_message, joint_status_message);

  max_vel.data  << 5.0, 5.0, 5.0, 5.0, 5.0, 5.0;
  max_acc.data  << 2.0, 2.0, 2.0, 3.0, 3.0, 3.0;
  max_jerk.data << 2.0, 2.0, 2.0, 2.0, 2.0, 2.0;
  max_vel.data  = max_vel.data  / 180 * M_PI;
  max_acc.data  = max_acc.data  / 180 * M_PI;
  max_jerk.data = max_jerk.data / 180 * M_PI;

  /*********************MOVEJ joint points*********************/ 
  JointVector joint_init(6);
  JointVector joint_point1(6);
  joint_init.data   << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  joint_point1.data << 0.0, 10.0, 0.0, 15.0, -45.0, 20.0;
  joint_init.data   = joint_init.data / 180 * M_PI;
  joint_point1.data = joint_point1.data / 180 * M_PI;
  /***********************************************************/ 

  /*********************MOVEL cart points*********************/ 
  Frame cart_point01;
  Frame cart_point02;
  // FkSolverPosKdl fk_solver_kdl;
  fk_solver_kdl.Init(chain);
  fk_solver_pos.Init(chain);
  ik_solver_pos_lma.Init(chain);

  JointVector input_joint_point02(6);
  input_joint_point02.data << -40.0, 10.0, -40.0, 40.0, -70.0, -40.0;
  input_joint_point02.data = input_joint_point02.data / 180 * M_PI;
  fk_solver_kdl.JntToCart(input_joint_point02, cart_point01);
  cart_point02 = cart_point01;

  cart_point02.p(2) = cart_point02.p(2) - 0.05;  //  move 5cm in -z
  cart_point02.p(1) = cart_point02.p(1) - 0.05;  //  move 5cm in -y
  cart_point02.p(0) = cart_point02.p(0) - 0.05;  //  move 5cm in -x

  Rotation rot_x = Rotation::RotX(0.2);  // rotate 0.2 rad around x axis
  cart_point02.rot.data = rot_x.data * cart_point02.rot.data;

  Rotation rot_y = Rotation::RotY(0.2);  // rotate 0.2 rad around y axis
  cart_point02.rot.data = rot_y.data * cart_point02.rot.data;

  Rotation rot_z = Rotation::RotZ(0.2);  // rotate 0.2 rad around y axis
  cart_point02.rot.data = rot_z.data * cart_point02.rot.data;
  /***********************************************************/ 
  // planning Init
  while (true) 
  {
    rt_task_wait_period(nullptr);  // wait for next cycle

    if (break_flag) { break; }

    if (!system_ready) { continue; }

    joint_status_buffer = joint_status_message->load();
    planner.ProcessFrame(); // 每一帧都
  }
}

void GetResponseHeader(std::string &response_header)
{
  response_header =  "Content-Type: application/json\r\n";
  response_header += "Connection: keep-alive\r\n";
  response_header += "Server: armcontrol\r\n";
  response_header += "Cache-control: no-cache, max-age=0, must-revalidate\r\n";
  response_header += "Access-Control-Allow-Origin: *\r\n";
  response_header += "Access-Control-Allow-Methods: *\r\n";
}

Eigen::Matrix<double, 6, 1> Pose2Vec(
    const arwen::dynamics::common::Pose& pose) {
  Eigen::Matrix<double, 6, 1> vec;
  vec.segment(0, 3) = pose.p.data;
  vec.segment(3, 3) = pose.rot.data;
  return vec;
};

void PrintPoseInfo(arwen::dynamics::common::Pose &pose)
{
  std::cout << '\n';
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.p.data.x: " << pose.p.X() << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.p.data.y: " << pose.p.Y() << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.p.data.z: " << pose.p.Z() << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.rot.data.x: " << pose.rot.X() * 180 / M_PI << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.rot.data.y: " << pose.rot.Y() * 180 / M_PI << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.rot.data.z: " << pose.rot.Z() * 180 / M_PI << std::endl;
  std::cout << '\n';
}

void PrintCartInfo(arwen::dynamics::common::JointVector &q_in)
{
  Pose pose_init;
  Frame frame_init;
  fk_solver_pos.JntToCart(q_in, frame_init);
  pose_init = frame_init.ToPose();
  std::cout <<  __FILE__ << __LINE__ << " : " << "q: " << q_in.data.transpose() << std::endl;
  PrintPoseInfo(pose_init);
}

// webserver auto send status info task
void WSAutoSendThread(void* arg) 
{
  std::string Info_str;
  std::string RunningFlag;
  std::string CartInfo_str;
  std::string JointInfo_str;
  JointVector joint_vector(6);
  Frame frame_init;
  Pose pose_init;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS_WS);
  struct mg_connection *connect = (struct mg_connection *)arg;
  protocol::message::DriverStatusMessage driver_status_buffer;

  while (true) 
  {
    rt_task_wait_period(nullptr);  // wait for next cycle
    if (break_flag) { break; }

    //read data
    driver_status_buffer = driver_status_message->load();

    joint_vector.data << std::round(driver_status_buffer.data[0].joint_position), 
                         std::round(driver_status_buffer.data[1].joint_position), 
                         std::round(driver_status_buffer.data[2].joint_position), 
                         std::round(driver_status_buffer.data[3].joint_position), 
                         std::round(driver_status_buffer.data[4].joint_position), 
                         std::round(driver_status_buffer.data[5].joint_position);

    fk_solver_pos.JntToCart(joint_vector, frame_init);
    pose_init = frame_init.ToPose();

    JointInfo_str = mg_mprintf("%Q:[%f,%f,%f,%f,%f,%f]", "JointInfo",
                                driver_status_buffer.data[0].joint_position * 180 / M_PI,
                                driver_status_buffer.data[1].joint_position * 180 / M_PI,
                                driver_status_buffer.data[2].joint_position * 180 / M_PI,
                                driver_status_buffer.data[3].joint_position * 180 / M_PI,
                                driver_status_buffer.data[4].joint_position * 180 / M_PI,
                                driver_status_buffer.data[5].joint_position * 180 / M_PI);

    CartInfo_str = mg_mprintf("%Q:[%f,%f,%f,%f,%f,%f]", "CartInfo",
                               pose_init.p.X(),
                               pose_init.p.Y(),
                               pose_init.p.Z(),
                               pose_init.rot.X() * 180 / M_PI,
                               pose_init.rot.Y() * 180 / M_PI,
                               pose_init.rot.Z() * 180 / M_PI);
    
    if (planner.IsRunning() && !planner.getStopFlag())
      RunningFlag = mg_mprintf("%Q:%Q", "RunningFlag", "True");
    else
      RunningFlag = mg_mprintf("%Q:%Q", "RunningFlag", "False");

    Info_str = mg_mprintf("{%Q:{%s, %s, %s}}", "Info", RunningFlag.c_str(), JointInfo_str.c_str(), CartInfo_str.c_str());

    mg_ws_send(connect, Info_str.c_str(), Info_str.size(), WEBSOCKET_OP_TEXT);
  }
}

int http_api_reply(struct mg_connection *connect, int status, const char *reply_key, const char *reply_value)
{
  std::string response_header;
  GetResponseHeader(response_header);

  mg_http_reply(connect, status, response_header.c_str(), "{%Q:%Q}\n", reply_key, reply_value);

  return 0;
}

// 登录功能，默认密码为 123456
int api_login(struct mg_http_message *http_msg, struct mg_connection *connect)
{
  std::string response_header;
  GetResponseHeader(response_header);

  double passwd = 0.0;
  if (mg_json_get_num(http_msg->body, "$.passwd", &passwd))
  {
    std::cout << __FILE__ << __LINE__ << " : " <<  passwd << std::endl;
    if (passwd == 123456)
        http_api_reply(connect, 200, "login", "success");
    else
        http_api_reply(connect, 404, "login", "failed");
  }
  else
        http_api_reply(connect, 404, "login", "Unknown key");

  return 0;
}

// 手动控制界面的关节空间位置控制
int api_manual_jointPosition_movJ(struct mg_http_message *http_msg, struct mg_connection *connect)
{
  std::string response_header;
  GetResponseHeader(response_header);

  bool result = false;
  int offset, length;
  std::string tmp_str;
  std::string key_json_;
  std::string string_http_msg_;
  std::vector<double> joint_position_;

  string_http_msg_ = http_msg->body.ptr;
  offset = mg_json_get(http_msg->body, "$", &length);
  key_json_ = string_http_msg_.substr(offset + 2, strlen("movj"));
  std::cout << __FILE__ << __LINE__ << " : " <<  "the key value of api_manual_jointPosition_movJ is : " << key_json_ << '\n';
  if (strncasecmp(key_json_.c_str(), "movj", strlen("movj")) == 0)
  {
    for (int i = 0; i < 6; i++)
    {
      tmp_str =  "$.movj[" + std::to_string(i) +"]";
      offset = mg_json_get(http_msg->body, tmp_str.c_str(), &length);
      joint_position_.push_back(std::atof((string_http_msg_.substr(offset, length)).c_str()));
      std::cout << __FILE__ << __LINE__ << "] : " << "jointPositon[" << i << "] : " << joint_position_[i] << '\n';
    }

    JointVector joint_point01(6);
    joint_point01.data << joint_position_[0], joint_position_[1], joint_position_[2], joint_position_[3], joint_position_[4], joint_position_[5];
    joint_point01.data << joint_point01.data / 180 * M_PI;

    if (!planner.IsRunning() && !planner.getStopFlag())
    {
      result = planner.MoveJ(joint_point01, max_vel, max_acc, max_jerk);
      if (result)
      {
        while(true)
        {
          if (break_flag)
            break;
          
          if (!planner.IsRunning() && !planner.getStopFlag())
          {
            http_api_reply(connect, 200, "movJ", "Success");
            break;
          }
        }
      }
      else
        http_api_reply(connect, 404, "movJ", "Failed to call moveJ");
    }
    else
        http_api_reply(connect, 404, "movJ", "Failed, not ready");
  }
  else
        http_api_reply(connect, 404, "Status", "Unknown key");

  return 0;
}

// 手动控制界面下的笛卡尔空间位姿控制
int api_manual_tcpPosition_movJ(struct mg_http_message *http_msg, struct mg_connection *connect)
{
  std::string response_header;
  GetResponseHeader(response_header);

  bool result = false;
  int offset, length;
  std::vector<double> tcpSpace_point_;
  std::string tmp_str;
  std::string key_json_;
  std::string tmp_point_str;
  std::string string_http_msg_ = http_msg->body.ptr;

  offset = mg_json_get(http_msg->body, "$", &length);
  key_json_ = string_http_msg_.substr(offset + 2, strlen("movj"));
  std::cout << __FILE__ << __LINE__ << " : " <<  "the key value of api_manual_tcpPosition_movJ is : " << key_json_ << '\n';
  if (strncasecmp(key_json_.c_str(), "movj", strlen("movj")) == 0)
  {
    for (int i = 0; i < 6; i++)
    {
      tmp_str = "$.movj[" + std::to_string(i) + "]";
      offset = mg_json_get(http_msg->body, tmp_str.c_str(), &length);
      tmp_point_str = http_msg->body.ptr[offset];
      tcpSpace_point_.push_back(std::atof((string_http_msg_.substr(offset, length)).c_str()));
      std::cout << __FILE__ << __LINE__ << "] : " << "tcpPosition[" << i << "] : " << tcpSpace_point_[i] << '\n';
    }

    Frame cart_point;
    JointVector joint_point_init(6);
    JointVector joint_point_out(6);
    joint_point_init.data << 0, 0, 0, 0, 0, 0;
    joint_point_init.data = joint_point_init.data / 180 * M_PI;

    cart_point.p(0) = tcpSpace_point_[0];  // x
    cart_point.p(1) = tcpSpace_point_[1];  // y
    cart_point.p(2) = tcpSpace_point_[2];  // z
    Rotation rot_x = Rotation::RotX(tcpSpace_point_[3] * M_PI / 180);
    cart_point.rot.data = rot_x.data * cart_point.rot.data;
    Rotation rot_y = Rotation::RotY(tcpSpace_point_[4] * M_PI / 180);
    cart_point.rot.data = rot_y.data * cart_point.rot.data;
    Rotation rot_z = Rotation::RotZ(tcpSpace_point_[5] * M_PI / 180);
    cart_point.rot.data = rot_z.data * cart_point.rot.data;

    result = ik_solver_pos_lma.CartToJnt(joint_point_init, cart_point, joint_point_out);
    if (result)
    {
      if (!planner.IsRunning() && !planner.getStopFlag())
      {
        result = planner.MoveJ(joint_point_out, max_vel, max_acc, max_jerk);
        if (result)
        {
          while (true)
          {
            if (break_flag)
              break;
            
            if (!planner.IsRunning() && !planner.getStopFlag())
            {
              http_api_reply(connect, 200, "tcpSpace_movJ", "Success");
              break;
            }
          }
        }
        else
          http_api_reply(connect, 404, "tcpSpace_movJ", "Failed to call moveJ");
      }
      else
        http_api_reply(connect, 404, "tcpSpace_movJ", "Failed! System not ready");
    }
  }
  else
    http_api_reply(connect, 404, "Status", "Unknown key");

  return 0;
}

// 精确控制处理：接收目标点信息，调用movej
int WSJointSpace(struct mg_connection *connect, struct mg_ws_message *ws_msg)
{
  int offset, length;
  std::string tmp_str;
  std::string key_json_;
  std::string tmp_position_str;
  std::string string_ws_msg = ws_msg->data.ptr;
  std::vector<double> joint_space_position_;

  offset = mg_json_get(ws_msg->data, "$", &length);
  key_json_ = string_ws_msg.substr(offset + 2, strlen("jointSpace"));
  std::cout << __FILE__ << __LINE__ << " : " <<  "the key value of WSJointSpace is : " << key_json_ << '\n';
  if (strncasecmp(key_json_.c_str(), "jointSpace", strlen("jointSpace")) == 0)
  {
    for (int i = 0; i < 6; i++)
    {
      tmp_str = "$.jointSpace[" + std::to_string(i) + "]";
      offset = mg_json_get(ws_msg->data, tmp_str.c_str(), &length);
      tmp_position_str = ws_msg->data.ptr[offset];
      joint_space_position_.push_back(std::atoi((string_ws_msg.substr(offset, length)).c_str()));
    }

    JointVector joint_point02(6);
    joint_point02.data << joint_space_position_[0], 
                          joint_space_position_[1], 
                          joint_space_position_[2], 
                          joint_space_position_[3], 
                          joint_space_position_[4], 
                          joint_space_position_[5];
    joint_point02.data << joint_point02.data / 180 * M_PI;

    if (!planner.IsRunning() && !planner.getStopFlag())
    {
      planner.MoveJ(joint_point02, max_vel, max_acc, max_jerk);
    }
    
    std::string flag_str = mg_mprintf("{%Q:%Q}", "Status", "Success to call movej");
    mg_ws_send(connect, flag_str.c_str(), flag_str.size(), WEBSOCKET_OP_TEXT);
  }
  else
  {
    std::string flag_str = mg_mprintf("{%Q:%Q}", "Status", "Error key");
    mg_ws_send(connect, flag_str.c_str(), flag_str.size(), WEBSOCKET_OP_TEXT);
  }

  return 0;
}

int WSMoveL(struct mg_connection *connect, struct mg_ws_message *ws_msg)
{
  int offset, length;
  std::vector<double> moveL_point_;
  std::string tmp_str;
  std::string tmp_point_str;
  std::string string_ws_msg = ws_msg->data.ptr;
  for (int i = 0; i < 6; i++)
  {
    tmp_str = "$.moveL[" + std::to_string(i) + "]";
    offset = mg_json_get(ws_msg->data, tmp_str.c_str(), &length);
    tmp_point_str = ws_msg->data.ptr[offset];
    moveL_point_.push_back(std::atof((string_ws_msg.substr(offset, length)).c_str()));
  }

  Frame cart_point_start;
  Frame cart_point_end;
  JointVector joint_vector_cur(6);
  JointVector joint_point_start(6);
  protocol::message::DriverStatusMessage driver_status_buffer;

  driver_status_buffer = driver_status_message->load();
  joint_vector_cur.data << std::round(driver_status_buffer.data[0].joint_position), 
                           std::round(driver_status_buffer.data[1].joint_position), 
                           std::round(driver_status_buffer.data[2].joint_position), 
                           std::round(driver_status_buffer.data[3].joint_position), 
                           std::round(driver_status_buffer.data[4].joint_position), 
                           std::round(driver_status_buffer.data[5].joint_position);
  // fk_solver_kdl.JntToCart(joint_vector_cur, cart_point_start);

  // joint_point_start.data << -40.0, 10.0, -40.0, 40.0, -70.0, -40.0;
  joint_point_start.data << 0.0, 0.0, 85.0, 90.0, 0.0, 0.0;
  joint_point_start.data = joint_point_start.data / 180 * M_PI;
  fk_solver_kdl.JntToCart(joint_point_start, cart_point_start);
  cart_point_end = cart_point_start;
  Pose pose_point_start = cart_point_start.ToPose();
  PrintPoseInfo(pose_point_start);
  
  cart_point_end.p(0) = cart_point_end.p(0) - 0.05;  // set x
  // cart_point_end.p(1) = cart_point_end.p(1) - 0.05;  // set x
  // cart_point_end.p(2) = cart_point_end.p(2) - 0.05;  // set x
  // cart_point_end.p(0) = cart_point_end.p(0) + moveL_point_[0];  // set x
  // cart_point_end.p(1) = cart_point_end.p(1) + moveL_point_[1];  // set y
  // cart_point_end.p(2) = cart_point_end.p(2) + moveL_point_[2];  // set z
  // Rotation rot_x = Rotation::RotX(moveL_point_[3] * M_PI / 180);
  // cart_point_end.rot.data = rot_x.data * cart_point_end.rot.data;

  // Rotation rot_y = Rotation::RotX(moveL_point_[4] * M_PI / 180);
  // cart_point_end.rot.data = rot_y.data * cart_point_end.rot.data;
  
  // Rotation rot_z = Rotation::RotX(moveL_point_[5] * M_PI / 180);
  // cart_point_end.rot.data = rot_z.data * cart_point_end.rot.data;

  Pose pose_point_end = cart_point_end.ToPose();
  PrintPoseInfo(pose_point_end);

  // MOVEL cartesian points
  JointVector joint_init(6);
  JointVector joint_point00(6);
  JointVector joint_point1(6);
  JointVector joint_point2(6);
  JointVector joint_point3(6);
  JointVector joint_point4(6);
  JointVector joint_point5(6);
  JointVector joint_point6(6);

  joint_init.data << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  joint_point00.data << 30.0, 10.0, -40.0, 30.0, -90.0, 30.0;
  joint_point1.data << 0.0, 10.0, 0.0, 15.0, -45.0, 20.0;  // start point:success
  joint_point2.data << 30.0, 10.0, -20.0, 45.0, -90.0, 30.0;
  joint_point3.data << 5.0, -30.0, -30.0, 30.0, -30.0, 10.0;
  joint_point4.data << -30.0, -20.0, -15.0, 15.0, 0.0, 45.0;
  joint_point5.data << 40.0, 15.0, -30.0, 35.0, -45.0, 60.0;
  joint_point6.data << -40.0, 10.0, 1.0, 15.0, -45.0, 20.0;  // start point: joint_point2, end point: joint_point6

  joint_init.data = joint_init.data / 180 * M_PI;
  joint_point00.data = joint_point00.data / 180 * M_PI;
  joint_point1.data = joint_point1.data / 180 * M_PI;
  joint_point2.data = joint_point2.data / 180 * M_PI;
  joint_point3.data = joint_point3.data / 180 * M_PI;
  joint_point4.data = joint_point4.data / 180 * M_PI;
  joint_point5.data = joint_point5.data / 180 * M_PI;
  joint_point6.data = joint_point6.data / 180 * M_PI;

  Frame cart_point1;
  Frame cart_point2;
  Frame cart_point3;
  Frame cart_point4;
  Frame cart_point5;
  Frame cart_point6;
  fk_solver_kdl.JntToCart(joint_point1, cart_point1);
  fk_solver_kdl.JntToCart(joint_point2, cart_point2);
  fk_solver_kdl.JntToCart(joint_point3, cart_point3);
  fk_solver_kdl.JntToCart(joint_point4, cart_point4);
  fk_solver_kdl.JntToCart(joint_point5, cart_point5);
  fk_solver_kdl.JntToCart(joint_point6, cart_point6);
  Frame cart_point00;
  fk_solver_kdl.JntToCart(joint_point00, cart_point00);

  if (!planner.IsRunning() && !planner.getStopFlag())
  {
    /*********************MOVEL cart points*********************/ 
    bool result = false;
   std::cout <<  __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "Execute planner.MoveJ()" << std::endl;
    // planner.MoveJ(joint_point_start, max_vel, max_acc, max_jerk);
    // planner.MoveJ(joint_vector_cur, max_vel, max_acc, max_jerk);
    planner.MoveJ(joint_point1, max_vel, max_acc, max_jerk);
    // planner.MoveJ(joint_point2, max_vel, max_acc, max_jerk);

    std::cout <<  __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "Execute planner.MoveL()" << std::endl;
    // result = planner.MoveL(cart_point_start, cart_max_vel, cart_max_acc, cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    // result = planner.MoveL(cart_point_end, cart_max_vel, cart_max_acc, cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    // result = planner.MoveL(cart_point2, cart_max_vel, cart_max_acc, cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    // result = planner.MoveL(cart_point3, cart_max_vel, cart_max_acc, cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    // result = planner.MoveL(cart_point4, cart_max_vel, cart_max_acc, cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    // result = planner.MoveL(cart_point5, cart_max_vel, cart_max_acc, cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    result = planner.MoveL(cart_point6, cart_max_vel, cart_max_acc, cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    if (result)
    {
      std::string reply_str = mg_mprintf("{%Q:%Q}", "movel", "Success");
      mg_ws_send(connect, reply_str.c_str(), reply_str.size(), WEBSOCKET_OP_TEXT);
    }
    else
    {
      std::string reply_str = mg_mprintf("{%Q:%Q}", "movel", "Failed");
      mg_ws_send(connect, reply_str.c_str(), reply_str.size(), WEBSOCKET_OP_TEXT);
    }
    /***********************************************************/ 
  }
  return 0;
}

int WSTcpSpace(struct mg_connection *connect, struct mg_ws_message *ws_msg)
{
  bool result = false;
  int offset, length;
  std::vector<double> tcpSpace_point_;
  std::string tmp_str;
  std::string key_json_;
  std::string tmp_point_str;
  std::string string_ws_msg = ws_msg->data.ptr;

  offset = mg_json_get(ws_msg->data, "$", &length);
  key_json_ = string_ws_msg.substr(offset + 2, strlen("tcpSpace"));
  std::cout << __FILE__ << __LINE__ << " : " <<  "the key value of WSTcpSpace is : " << key_json_ << '\n';
  if (strncasecmp(key_json_.c_str(), "tcpSpace", strlen("tcpSpace")) == 0)
  {
    for (int i = 0; i < 6; i++)
    {
      tmp_str = "$.tcpSpace[" + std::to_string(i) + "]";
      offset = mg_json_get(ws_msg->data, tmp_str.c_str(), &length);
      tmp_point_str = ws_msg->data.ptr[offset];
      tcpSpace_point_.push_back(std::atof((string_ws_msg.substr(offset, length)).c_str()));
    }

    JointVector joint_point_init(6);
    JointVector joint_point_out(6);
    joint_point_init.data << 0, 0, 0, 0, 0, 0;
    joint_point_init.data = joint_point_init.data / 180 * M_PI;

    Frame cart_point;
    cart_point.p(0) = tcpSpace_point_[0];  // x
    cart_point.p(1) = tcpSpace_point_[1];  // y
    cart_point.p(2) = tcpSpace_point_[2];  // z
    Rotation rot_x = Rotation::RotX(tcpSpace_point_[3] * M_PI / 180);
    cart_point.rot.data = rot_x.data * cart_point.rot.data;

    Rotation rot_y = Rotation::RotY(tcpSpace_point_[4] * M_PI / 180);
    cart_point.rot.data = rot_y.data * cart_point.rot.data;

    Rotation rot_z = Rotation::RotZ(tcpSpace_point_[5] * M_PI / 180);
    cart_point.rot.data = rot_z.data * cart_point.rot.data;

    result = ik_solver_pos_lma.CartToJnt(joint_point_init, cart_point, joint_point_out);
    if (result)
    {
      if (!planner.IsRunning() && !planner.getStopFlag())
      {
        result = planner.MoveJ(joint_point_out, max_vel, max_acc, max_jerk);
        if (result)
        {
          std::string reply_str = mg_mprintf("{%Q:%Q}", "tcpSpace", "Success");
          mg_ws_send(connect, reply_str.c_str(), reply_str.size(), WEBSOCKET_OP_TEXT);
        }
        else  
        {
          std::string reply_str = mg_mprintf("{%Q:%Q}", "tcpSpace", "Failed");
          mg_ws_send(connect, reply_str.c_str(), reply_str.size(), WEBSOCKET_OP_TEXT);  
        }
      }
      else
      {
          std::string reply_str = mg_mprintf("{%Q:%Q}", "tcpSpace", "failed, not ready");
          mg_ws_send(connect, reply_str.c_str(), reply_str.size(), WEBSOCKET_OP_TEXT);
      }
    }
    else  
    {
        std::string reply_str = mg_mprintf("{%Q:%Q}", "tcpSpace", "Error Point");
        mg_ws_send(connect, reply_str.c_str(), reply_str.size(), WEBSOCKET_OP_TEXT); 
    }
  }
  else
  {
    std::string reply_str = mg_mprintf("{%Q:%Q}", "Status", "Error key");
    mg_ws_send(connect, reply_str.c_str(), reply_str.size(), WEBSOCKET_OP_TEXT); 
  }

  return 0;
}

void WSMSGProcess(struct mg_connection *connect, struct mg_ws_message *ws_msg)
{
  std::cout <<  __FILE__ << __LINE__ << " : " << "websocket message is :[" << ws_msg->data.ptr << "]" << std::endl;

  int offset, length;
  std::string json_key;
  std::string tmp_str_msg = ws_msg->data.ptr;

  // moveL 指令
  offset = mg_json_get(ws_msg->data, "$", &length);
  json_key = tmp_str_msg.substr(offset + 2, strlen("moveL"));
  if (mg_ncasecmp(json_key.c_str(), "moveL", strlen("moveL")) == 0)
  {
    WSMoveL(connect, ws_msg);
    return;
  }
  else
  {
    std::string flag_str = mg_mprintf("{%Q:%Q}", "Status", "Failed to call moveL");
    mg_ws_send(connect, flag_str.c_str(), flag_str.size(), WEBSOCKET_OP_TEXT);
  }

  // 关节空间
  json_key = tmp_str_msg.substr(offset + 2, strlen("jointSpace"));
  if (mg_ncasecmp(json_key.c_str(), "jointSpace", strlen("jointSpace")) == 0)
  {
    WSJointSpace(connect, ws_msg);
  }
  else
  {
    std::string flag_str = mg_mprintf("{%Q:%Q}", "Status", "Failed in joint space");
    mg_ws_send(connect, flag_str.c_str(), flag_str.size(), WEBSOCKET_OP_TEXT);
  }

  // TCP空间
  json_key = tmp_str_msg.substr(offset + 2, strlen("tcpSpace"));
  if (mg_ncasecmp(json_key.c_str(), "tcpSpace", strlen("tcpSpace")) == 0)
  {
    WSTcpSpace(connect, ws_msg);
  }
  else
  {
    std::string flag_str = mg_mprintf("{%Q:%Q}", "Status", "Failed in tcp space");
    mg_ws_send(connect, flag_str.c_str(), flag_str.size(), WEBSOCKET_OP_TEXT);
  }

  return;
}

// // 关节位置， planning  都要加规划  长按 调用speed J，检测到
void EventHandlerFunc(struct mg_connection *connect, int event, void *event_data, void *func_data)
{
  if (event == MG_EV_HTTP_MSG)
  {
    struct mg_http_message *http_msg = (struct mg_http_message *)event_data;
    if (mg_http_match_uri(http_msg, "/websocket"))
    {
      std::string response_header;
      GetResponseHeader(response_header);
      mg_ws_upgrade(connect, http_msg, response_header.c_str());
    }
    else if (mg_http_match_uri(http_msg, "/api/control/manual/jointPosition/movj"))
    {
      api_manual_jointPosition_movJ(http_msg, connect);
    }
    else if (mg_http_match_uri(http_msg, "/api/control/manual/tcpPosition/movj"))
    {
      api_manual_tcpPosition_movJ(http_msg, connect);
    }
    else if (mg_vcmp(&(http_msg->uri), "/api/login") == 0)
    {
      api_login(http_msg, connect);
    }
    else
    {
      http_api_reply(connect, 404, "status","Error Command");
    }
  }
  else if (event == MG_EV_WS_OPEN)
  {
    std::cout << __FILE__ << " " << __LINE__ <<" There is a event : MG_EV_WS_OPEN" << std::endl;
    // Create auto send info RT task
    if (!AutoSendTask_)
    {
      std::cout << __FILE__ << " " << __LINE__ << " Create Real Time Task" << '\n';
      rt_task_create(&ws_auto_send_task, "ws_auto_send_task", 1024 * 1024 * 4, 50, 0);
      rt_task_start(&ws_auto_send_task, &WSAutoSendThread, connect);
      AutoSendTask_ = true;
    }
    std::string flag_str = mg_mprintf("{%Q:%d}", "flag", 1);
    mg_ws_send(connect, flag_str.c_str(), flag_str.size(), WEBSOCKET_OP_TEXT);
  }
  else if (event == MG_EV_CLOSE)
  {
    std::cout << __FILE__ << " " << __LINE__ << " There is a event : MG_EV_CLOSE" << '\n';
    if (AutoSendTask_)
    {
      std::cout << __FILE__ << " " <<  __LINE__ << " Delete Real Time Task" << '\n';
      rt_task_delete(&ws_auto_send_task);
      AutoSendTask_ = false;
    }
  }
  else if (event == MG_EV_WS_MSG)
  {
    struct mg_ws_message *ws_msg = (struct mg_ws_message *) event_data;
    WSMSGProcess(connect, ws_msg);
  }
  else
  {
    return;
  }
}

void StartMGServer(std::string listen_addr, struct mg_mgr *manager, struct mg_connection *connect)
{
  connect = mg_http_listen(manager, listen_addr.c_str(), EventHandlerFunc, NULL);

  for (;;)
  {
    if (break_flag)
      break;

    mg_mgr_poll(manager, 1000);
  }

	return ;
}

int main(int argc, char* argv[]) 
{
  // signal mask
  signal(SIGHUP,  signal_handler);
  signal(SIGINT,  signal_handler);
  signal(SIGQUIT, signal_handler);
  signal(SIGIOT,  signal_handler);
  signal(SIGFPE,  signal_handler);
  signal(SIGKILL, signal_handler);
  signal(SIGSEGV, signal_handler);
  signal(SIGTERM, signal_handler);

  // Avoids memory swapping for this program
  mlockall(MCL_CURRENT | MCL_FUTURE);

  // add salves
  for (int SlaveNum = 0; SlaveNum < TAIKE_TOTAL; SlaveNum++) 
  {
    // printf("---add %d slave---\n", SlaveNum);
    ecatmaster.addSlave(0, SlaveNum, &ecat_taike[SlaveNum]);
  }

  // master active
  ecatmaster.activateWithDC(0, CYCLE_NS);

  rt_task_create(&driver_task, "cyclic_task", 1024 * 1024 * 4, 90, 0);
  rt_task_start(&driver_task, &DriverThread, nullptr);

  rt_task_create(&control_task, "control_task", 1024 * 1024 * 4, 60, 0);
  rt_task_start(&control_task, &ControlThread, nullptr);

  rt_task_create(&planning_task, "planning_task", 1024 * 1024 * 4, 50, 0);
  rt_task_start(&planning_task, &PlanningThread, nullptr);

  /************************** Webserver **************************/
  struct mg_mgr manager;
  struct mg_connection *connect;

  std::string listen_addr = getarg("0.0.0.0:9999", "--listen-address");
  mg_mgr_init(&manager);
  StartMGServer(listen_addr, &manager, connect);
  mg_mgr_free(&manager);
  /**************************************************************/

  // pause
  while (break_flag == false) 
  	sched_yield();

  // cleanup
  printf("\n Deleting RT task ....");
  rt_task_delete(&driver_task);
  rt_task_delete(&control_task);
  rt_task_delete(&planning_task);

  if (AutoSendTask_)
  {
    rt_task_delete(&ws_auto_send_task);
  }

  printf("\n\n\t !! Controller Stopped!! \n");
  ecatmaster.deactivate();

  return 0;
}