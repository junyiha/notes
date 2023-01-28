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
#define CYCLE_NS_WS 3000000e3  // 300 ms
#define JOINTS_PULSE (131072.0 / 2.0 / M_PI)

Master ecatmaster;
EcatTaike ecat_taike[ARM_DOF];

std::atomic_bool system_ready = false;
std::atomic_bool break_flag = false;

// Xenomai RT tasks
RT_TASK driver_task;
RT_TASK control_task;
RT_TASK planning_task;

RT_TASK webserver_task;
RT_TASK print_JointInfo;
Planning planner;
bool running = false;
bool flag_movel = false;
bool flag_speedj = false;
bool flag_speedl = false;
JointVector max_vel(6);
JointVector max_acc(6);
JointVector max_jerk(6);
/***********************/
std::shared_ptr<arwen::dynamics::chain::Chain> chain =
    std::make_shared<arwen::dynamics::chain::Chain>(Manipulator());

std::shared_ptr<std::atomic<uint64_t>> timestamp =
    std::make_shared<std::atomic<uint64_t>>();

std::shared_ptr<std::atomic<protocol::message::DriverStatusMessage>>
    driver_status_message =
        std::make_shared<std::atomic<protocol::message::DriverStatusMessage>>();
std::shared_ptr<std::atomic<protocol::message::DriverCommandMessage>>
    driver_command_message = std::make_shared<
        std::atomic<protocol::message::DriverCommandMessage>>();

std::shared_ptr<std::atomic<protocol::message::JointStatusMessage>>
    joint_status_message = std::make_shared<
        std::atomic<arwen::protocol::message::JointStatusMessage>>();
std::shared_ptr<std::atomic<protocol::message::JointCommandMessage>>
    joint_command_message =
        std::make_shared<std::atomic<protocol::message::JointCommandMessage>>();

/**************/
int isSlaveInit() {
  int taike_count = 0;
  int slave_count = 0;

  for (int i = 0; i < TAIKE_TOTAL; ++i) {
    if (ecat_taike[i].initialized()) {
      taike_count++;
    }
  }

  for (int j = 0; j < TAIKE_TOTAL; j++) {
    if (ecatmaster.GetSlaveState(j) == 0x08) {
      slave_count++;
    }
  }

  if ((taike_count == TAIKE_TOTAL) && (slave_count == TAIKE_TOTAL))
    return 1;
  else
    return 0;
}
void signal_handler(int signum) {
  printf("\nSignal Interrupt: %d", signum);
  break_flag = true;
}

// ethercat update task
void DriverThread(void* arg) {
  RTIME now_ns;
  uint64_t tid = 0;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS);

  protocol::message::DriverStatusMessage driver_status_buffer;
  protocol::message::DriverCommandMessage driver_command_buffer;

  unsigned long long count = 0;

  while (true) {
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

    for (int k = 0; k < ARM_DOF; k++) {
      driver_status_buffer.data[k].joint_position =
          ecat_taike[k].actual_position_ / JOINTS_PULSE;
      driver_status_buffer.data[k].joint_velocity =
          ecat_taike[k].actual_velocity_;
      driver_status_buffer.data[k].joint_torque = ecat_taike[k].actual_torque_;

      ecat_taike[k].target_position_ = ecat_taike[k].actual_position_;
    }
    driver_status_message->store(driver_status_buffer);

    if (!system_ready) {
      driver_command_buffer.header = driver_status_buffer.header;
      memcpy(&driver_command_buffer, &driver_status_buffer,
             sizeof(protocol::message::DriverMessage));
      driver_command_message->store(driver_command_buffer);
    } else {
      driver_command_buffer = driver_command_message->load();

      ecat_taike[0].target_position_ = std::round(
          driver_command_buffer.data[0].joint_position * JOINTS_PULSE);
      ecat_taike[1].target_position_ = std::round(
          driver_command_buffer.data[1].joint_position * JOINTS_PULSE);
      ecat_taike[2].target_position_ = std::round(
          driver_command_buffer.data[2].joint_position * JOINTS_PULSE);
      ecat_taike[3].target_position_ = std::round(
          driver_command_buffer.data[3].joint_position * JOINTS_PULSE);
      ecat_taike[4].target_position_ = std::round(
          driver_command_buffer.data[4].joint_position * JOINTS_PULSE);
      ecat_taike[5].target_position_ = std::round(
          driver_command_buffer.data[5].joint_position * JOINTS_PULSE);
    }

    // Send pdo
    ecatmaster.TxUpdate(0, rt_timer_read());

    if (isSlaveInit()) {
      // printf("----system_ready==1---\n");
      ++count;
      system_ready = (count > 1000);
    } else {
      count = 0;
      system_ready = false;
    }

    ++tid;
  }
}

void ControlThread(void* arg) {
  RTIME now_ns;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS);

  Control control;
  control.Init(chain, timestamp, joint_command_message, joint_status_message,
               driver_command_message, driver_status_message);

  while (true) {
    rt_task_wait_period(nullptr);  // wait for next cycle

    if (break_flag) break;
    if (!system_ready) {
      arwen::protocol::message::JointStatusMessage joint_status_buffer =
          control.ConvertDriverStatusToJointStatus(
              driver_status_message->load());

      arwen::protocol::message::JointCommandMessage joint_command_buffer;
      memcpy(&joint_command_buffer, &joint_status_buffer,
             sizeof(protocol::message::JointMessage));

      joint_status_message->store(joint_status_buffer);
      joint_command_message->store(joint_command_buffer);
      continue;
    }

    control.ProcessFrame();
  }
}

void PlanningThread(void* arg) {
  RTIME now_ns;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS);
  unsigned long long count = 0;

  // Planning planner;

  protocol::message::JointStatusMessage joint_status_buffer;

  // bool running = false;
  // bool flag_movel = false;
  // bool flag_speedj = false;
  // bool flag_speedl = false;

  // joint space constraint condition
  // JointVector max_vel(6);
  // JointVector max_acc(6);
  // JointVector max_jerk(6);
  max_vel.data << 5.0, 5.0, 5.0, 5.0, 5.0, 5.0;
  max_acc.data << 2.0, 2.0, 2.0, 3.0, 3.0, 3.0;
  max_jerk.data << 2.0, 2.0, 2.0, 2.0, 2.0, 2.0;
  max_vel.data = max_vel.data / 180 * M_PI;
  max_acc.data = max_acc.data / 180 * M_PI;
  max_jerk.data = max_jerk.data / 180 * M_PI;
  // cartesian space constraint condition
  double cart_max_vel = 0.01;
  double cart_max_acc = 0.01;
  double cart_max_jerk = 0.01;
  double rot_max_vel = 0.01;
  double rot_max_acc = 0.01;
  double rot_max_jerk = 0.01;
  // MOVEJ joint points
  JointVector joint_init(6);
  JointVector joint_point1(6);
  JointVector joint_point2(6);
  JointVector joint_point3(6);
  JointVector joint_point4(6);
  JointVector joint_point5(6);

  joint_init.data << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  joint_point1.data << 0.0, 10.0, 0.0, 15.0, -45.0, 20.0;
  joint_point2.data << 30.0, 10.0, -20.0, 45.0, -90.0, 30.0;
  joint_point3.data << 5.0, -30.0, -30.0, 30.0, -30.0, 10.0;
  joint_point4.data << -30.0, -20.0, -15.0, 15.0, 0.0, 45.0;
  joint_point5.data << 40.0, 15.0, -30.0, 35.0, -45.0, 60.0;

  joint_init.data = joint_init.data / 180 * M_PI;
  joint_point1.data = joint_point1.data / 180 * M_PI;
  joint_point2.data = joint_point2.data / 180 * M_PI;
  joint_point3.data = joint_point3.data / 180 * M_PI;
  joint_point4.data = joint_point4.data / 180 * M_PI;
  joint_point5.data = joint_point5.data / 180 * M_PI;

  JointVector joint_point00(6);
  joint_point00.data << 30.0, 10.0, -40.0, 30.0, -90.0, 30.0;
  joint_point00.data = joint_point00.data / 180 * M_PI;
  // MOVEL cartesian points
  FkSolverPosKdl fk_solver_kdl;
  fk_solver_kdl.Init(chain);
  Frame cart_point1;
  Frame cart_point2;
  Frame cart_point3;
  Frame cart_point4;
  Frame cart_point5;

  fk_solver_kdl.JntToCart(joint_point1, cart_point1);
  fk_solver_kdl.JntToCart(joint_point2, cart_point2);
  fk_solver_kdl.JntToCart(joint_point3, cart_point3);
  fk_solver_kdl.JntToCart(joint_point4, cart_point4);
  fk_solver_kdl.JntToCart(joint_point5, cart_point5);
  Frame cart_point00;
  fk_solver_kdl.JntToCart(joint_point00, cart_point00);
  // SPEEDL joint velocity
  JointVector joint_vel(6);
  joint_vel.data << 2.0, 2.0, 2.0, 2.0, 2.0, 2.0;
  joint_vel.data = joint_vel.data / 180 * M_PI;
  // SEPPDL cartesian velocity(joint_point2, max_vel, max_acc, max_jerk);
      // planner.MoveJ(joint_point3, max_vel, max_acc, max_jerk);
      // planner.MoveJ(joint_point4, max_vel, max_acc, max_jerk);
      // planner.Mov
  dynamics::common::Velocity cart_vel_1;
  cart_vel_1.p =
      dynamics::common::Vector(-0.00024261, -0.00148931, -0.00284365);
  cart_vel_1.rot = dynamics::common::Vector(0.0138894, -0.0139764, -0.00342715);
  dynamics::common::Velocity cart_vel_2;
  cart_vel_2.p =
      dynamics::common::Vector(-0.00600435, -0.00346661, -0.00720628);
  cart_vel_2.rot =
      dynamics::common::Vector(0.00443943, -0.00768932, -2.71051e-19);

  // planning Init
  planner.Init(0.001, chain, timestamp, joint_command_message,
               joint_status_message);

  std::ofstream outfile;
  outfile.open("./log/movel_11.csv");
  outfile << "t"
          << ","
          << "pos_x"
          << ","
          << "pos_y"
          << ","
          << "pos_z"
          << ","
          << "vel_x"
          << ","
          << "vel_y"
          << ","
          << "vel_z"
          << "\n";
  outfile.close();
  // cyclic run
  while (true) {
    rt_task_wait_period(nullptr);  // wait for next cycle

    if (break_flag) break;
    if (!system_ready) {
      count = 0;
      continue;
    }
    joint_status_buffer = joint_status_message->load();
    planner.ProcessFrame(); // 每一帧都

    /***********MOVEJ***********/
    if (count > 45000 && !planner.getStopFlag()) {
      planner.Stop(max_vel, max_acc, max_jerk);
      count = 0;
      running = false;
    }
    if (count > 2000 && planner.getStopFlag()) {
      planner.StopRelease();
    }
    if (count > 6000 && !running && !planner.IsRunning() &&
        !planner.getStopFlag()) {
      planner.MoveJ(joint_init, max_vel, max_acc, max_jerk);  // init
      running = true;
    }
    if (running && !planner.IsRunning() && !planner.getStopFlag()) {
      // planner.MoveJ(joint_point1, max_vel, max_acc, max_jerk);
      // planner.MoveJ(joint_point2, max_vel, max_acc, max_jerk);
      // planner.MoveJ(joint_point3, max_vel, max_acc, max_jerk);
      // planner.MoveJ(joint_point4, max_vel, max_acc, max_jerk);
      // planner.MoveJ(joint_point5, max_vel, max_acc, max_jerk);
      running = false;
    }
    /***********MOVEJ***********/
    /***********MOVEL***********/
    // if (count > 1000 && !running && !planner.IsRunning() &&
    //   !planner.getStopFlag()) {
    //   planner.MoveJ(joint_point1, max_vel, max_acc, max_jerk);  //init
    //   running = true;
    // }
    // if (running && !planner.IsRunning() &&
    //   !planner.getStopFlag()) {
    //   planner.MoveL(cart_point2, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   planner.MoveL(cart_point3, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   // planner.MoveL(cart_point4, cart_max_vel, cart_max_acc,
    //   cart_max_jerk,
    //   //               rot_max_vel, rot_max_acc, rot_max_jerk);
    //   // planner.MoveL(cart_point5, cart_max_vel, cart_max_acc,
    //   cart_max_jerk,
    //   //               rot_max_vel, rot_max_acc, rot_max_jerk);
    //   running = false;
    // }
    /***********MOVEL***********/
    /***********SPEEDJ***********/
    // if (count > 30000 && !planner.getStopFlag()) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    // }
    // if (count > 1000 && !running && !planner.IsRunning() &&
    //         !planner.getStopFlag()) {
    //       planner.MoveJ(joint_point1, max_vel, max_acc, max_jerk);
    //       running = true;
    //     }
    // if (running && !planner.IsRunning() && !planner.getStopFlag()) {
    //   planner.SpeedJ(joint_vel, max_vel, max_acc, max_jerk);
    // }
    /***********SPEEDJ***********/
    /***********SPEEDL***********/
    // if (count > 40000 && !planner.getStopFlag()) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    // }
    // if (count > 1000 && !running && !planner.IsRunning() &&
    //         !planner.getStopFlag()) {
    //       planner.MoveJ(joint_point2, max_vel, max_acc, max_jerk);
    //       running = true;
    //     }
    // // if (running && !planner.IsRunning() && !planner.getStopFlag()) {
    // //   planner.SpeedL(cart_vel_1, cart_max_vel, cart_max_acc,
    // cart_max_jerk,
    // //                  rot_max_vel, rot_max_acc, rot_max_jerk);
    // // }
    // if (running && !planner.IsRunning() && !planner.getStopFlag()) {
    //   planner.SpeedL(cart_vel_2, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                  rot_max_vel, rot_max_acc, rot_max_jerk);
    // }
    /***********SPEEDL***********/

    //***********test speedl***********
    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !getStopFlag()) {
    //   planner.MoveJ(user_input_point1, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedl &&
    //     !getStopFlag()) {
    //   planner.SpeedL(tar_vel, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                  rot_max_vel, rot_max_acc, rot_max_jerk);
    //   flag_speedl = true;
    // }
    //***********test speedj***********
    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !getStopFlag()) {
    //   planner.MoveJ(user_input_point1, max_vel, max_acc, max_jerk);

    //   running = true;
    //   //  flag_movel = false;
    // }

    // if (running && !planner.IsRunning() && !flag_speedj &&
    //     !getStopFlag()) {
    //   planner.SpeedJ(input_target_vel, max_vel, max_acc, max_jerk);
    //   flag_speedj = true;
    // }
    //***********test movej and movel***********
    // LOG(INFO)<<"BOOL RUNNING:"<<running;
    //  if (count > 1000 && !running && !planner.IsRunning() &&
    //  !getStopFlag()) {
    //    planner.MoveJ(user_input_point1, max_vel, max_acc, max_jerk);
    //   // planner.MoveJ(user_input_point2, max_vel, max_acc, max_jerk);

    //   running = true;
    //   flag_movel = false;
    // }
    // if (running && !planner.IsRunning() && !flag_movel &&
    // !getStopFlag()) {
    //   planner.MoveL(cart_point2, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   flag_movel = true;
    //   running = false;
    // }

    ++count;
  }
}

bool auto_send_exit_flag = false;  /*true : exit auto send thread; false : not*/
struct JointData_t
{
  double position_value;
};

void movejCMD()
{
  // Planning planner;

  // planner.MoveJ();
  JointVector joint_point01(6);  // 一个目标点，保存六个关节转动的目标角度
  joint_point01.data << 10.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  joint_point01.data << joint_point01.data / 180 * M_PI ;

  while(true)
  {
    if (running && !planner.IsRunning() && !planner.getStopFlag())
    {
      std::cout << "Start running moveJ command" << std::endl;
      planner.MoveJ(joint_point01, max_vel, max_acc, max_jerk);
      running = false;
      break;
    }
    else
    {
      std::cout << "Not read to running movej" << std::endl;
    }
  }
}

void WSMSGProcess(struct mg_ws_message *ws_msg)
{
  std::cout << "websocket message is :[" << ws_msg->data.ptr << "]" << std::endl;
  if (mg_vcmp(&(ws_msg->data), "movej") == 0)
  {
    movejCMD();
  }
}

// webserver task
void WebserverThread(void* arg) {
  RTIME now_ns;
  uint64_t tid = 0;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS_WS);

  unsigned long long count = 0;
  struct mg_connection *connect = (struct mg_connection *)arg;
  std::string JointInfo_str;
  struct JointData_t joint_data_array[ARM_DOF];

  std::ofstream data_file;
  data_file.open("/tmp/log/data.txt");

  while (true) {
    rt_task_wait_period(nullptr);  // wait for next cycle

    if (break_flag) break;

    //read data
    for (int k = 0; k < ARM_DOF; k++) 
    {
      joint_data_array[k].position_value = ecat_taike[k].actual_position_ / JOINTS_PULSE;
      data_file << joint_data_array[k].position_value;
      // data_file << ecat_taike[k].actual_position_ / JOINTS_PULSE;
      data_file << "\n";
      // data[k].joint_position =  ecat_taike[k].actual_position_ / JOINTS_PULSE;
      // data[k].joint_velocity = ecat_taike[k].actual_velocity_;
      // data[k].joint_torque = ecat_taike[k].actual_torque_;
    }

    JointInfo_str = mg_mprintf("{%Q:[%f,%f,%f,%f,%f,%f]}", "JointInfo",
                                joint_data_array[0].position_value,
                                joint_data_array[1].position_value,
                                joint_data_array[2].position_value,
                                joint_data_array[3].position_value,
                                joint_data_array[4].position_value,
                                joint_data_array[5].position_value);

    mg_ws_send(connect, JointInfo_str.c_str(), JointInfo_str.size(), WEBSOCKET_OP_TEXT);
    data_file << "next status info \n";
    //send data
    // if (system_ready && ws_connected) {

    // }

    // ++tid;
  }
  data_file << "End";
  data_file.close();
}

// 关节位置， planning  都要加规划  长按 调用speed J，检测到
void PrintJointInfoThread(void *arg)
{
  RTIME now_ns;
  uint64_t tid = 0;
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS_WS);

  std::vector<std::string> tmp(6);

  std::string ident = "JointInfo";
  std::vector<const char *> joint01;
  std::vector<const char *> joint02;
  std::vector<const char *> joint03;
  std::vector<const char *> joint04;
  std::vector<const char *> joint05;
  std::vector<const char *> joint06;

  // driver_status_message

  struct timespec rqtp;
  struct timespec tmtp;
  rqtp.tv_nsec = 0;  /* 1 秒*/
  rqtp.tv_sec = 1;

  openlog(ident.c_str(), LOG_NOWAIT, LOG_INFO);
  std::ofstream outfile;
  outfile.open("/tmp/log/webserver.txt");
  for (int i = 0;; i++)
  {
    // rt_task_wait_period(nullptr);  // wait for next cycle
      if (break_flag)
        break;
      
      joint01.push_back(std::to_string(ecat_taike[1].status_word_).c_str());
      joint02.push_back(std::to_string(ecat_taike[2].status_word_).c_str());
      joint03.push_back(std::to_string(ecat_taike[3].status_word_).c_str());
      joint04.push_back(std::to_string(ecat_taike[4].status_word_).c_str());
      joint05.push_back(std::to_string(ecat_taike[5].status_word_).c_str());
      joint06.push_back(std::to_string(ecat_taike[6].status_word_).c_str());

      outfile << *(joint01.data());
      outfile << *(joint02.data());
      outfile << *(joint03.data());
      outfile << *(joint04.data());
      outfile << *(joint05.data());
      outfile << *(joint06.data());
      outfile << "\n";

      syslog(LOG_INFO, *(joint01.data()));
      syslog(LOG_INFO, *(joint02.data()));
      syslog(LOG_INFO, *(joint03.data()));
      syslog(LOG_INFO, *(joint04.data()));
      syslog(LOG_INFO, *(joint05.data()));
      syslog(LOG_INFO, *(joint06.data()));

      // sleep(1);
    // nanosleep(&rqtp, &tmtp);  
  }

  outfile << "Done";
  closelog();
  outfile.close();
  
  return ;
}

int GetResponseHeader(std::string &response_header)
{
  response_header =  "Content-Type: application/json\r\n";
  response_header += "Connection: keep-alive\r\n";
  response_header += "Server: armcontrol\r\n";
  response_header += "Cache-control: no-cache, max-age=0, must-revalidate\r\n";
  response_header += "Access-Control-Allow-Origin: *\r\n";
  response_header += "Access-Control-Allow-Methods: *\r\n";

  return 0;
}

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
  }
  else if (event == MG_EV_WS_OPEN)
  {
    auto_send_exit_flag = false;
    // std::thread tmp{WebserverThread, connect};
    // tmp.detach();
    rt_task_create(&webserver_task, "webserver_task", 1024 * 1024 * 4, 50, 0);
    rt_task_start(&webserver_task, &WebserverThread, connect);
  }
  else if (event == MG_EV_CLOSE)
  {
    auto_send_exit_flag = true;
  }
  else if (event == MG_EV_WS_MSG)
  {
    struct mg_ws_message *ws_msg = (struct mg_ws_message *) event_data;
    WSMSGProcess(ws_msg);
  }
  else
  {
    return;
  }
}

void StartMGServer(std::string listen_addr, struct mg_mgr *manager, struct mg_connection *connect)
{
  mg_mgr_init(manager);

  connect = mg_http_listen(manager, listen_addr.c_str(), EventHandlerFunc, NULL);

  for (;;)
  {
    mg_mgr_poll(manager, 1000);
  }

	return ;
}


int main(int argc, char* argv[]) {
  // signal mask
  signal(SIGHUP, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGQUIT, signal_handler);
  signal(SIGIOT, signal_handler);
  signal(SIGFPE, signal_handler);
  signal(SIGKILL, signal_handler);
  signal(SIGSEGV, signal_handler);
  signal(SIGTERM, signal_handler);

  // planner

  // Avoids memory swapping for this program
  mlockall(MCL_CURRENT | MCL_FUTURE);

  // Perform auto-init of rt_print buffers if the task doesn't do so
  // rt_print_auto_init(1);

  // add salves
  for (int SlaveNum = 0; SlaveNum < TAIKE_TOTAL; SlaveNum++) {
    // printf("---add %d slave---\n", SlaveNum);
    ecatmaster.addSlave(0, SlaveNum, &ecat_taike[SlaveNum]);
  }

  // master active
  // printf("---activate---\n");
  ecatmaster.activateWithDC(0, CYCLE_NS);


  //  printf("\n--create cyclic(ethercat) task ...\n");
  rt_task_create(&driver_task, "cyclic_task", 1024 * 1024 * 4, 90, 0);
  rt_task_start(&driver_task, &DriverThread, nullptr);

  printf("\n-- running control(robot) task ...\n");
  rt_task_create(&control_task, "control_task", 1024 * 1024 * 4, 60, 0);
  rt_task_start(&control_task, &ControlThread, nullptr);

  rt_task_create(&planning_task, "planning_task", 1024 * 1024 * 4, 50, 0);
  rt_task_start(&planning_task, &PlanningThread, nullptr);

  /************************** Webserver **************************/
  struct mg_mgr manager;
  struct mg_connection *connect;

  std::string listen_addr = getarg("0.0.0.0:9999", "--listen-address");
  StartMGServer(listen_addr, &manager, connect);

  // rt_task_create(&webserver_task, "webserver_task", 1024 * 1024 * 4, 50, 0);
  // rt_task_start(&webserver_task, &WebserverThread, nullptr);

  // rt_task_create(&print_JointInfo, "print_JointInfo", 1024 * 1024 * 4, 50, 0);
  // rt_task_start(&print_JointInfo, &PrintJointInfoThread, nullptr);

  // std::thread print_thread{print_JointInfo};
  // print_thread.detach();
  // print_JointInfo();
  // start_webserver();
  // arwen::WebServer::Help();
  // std::thread test{test_file};
  // test.detach();
  /**************************************************************/

  // pause
  while (break_flag == false) 
  	sched_yield();

  // cleanup
  printf("\n Deleting RT task ....");
  rt_task_delete(&driver_task);
  rt_task_delete(&control_task);
  rt_task_delete(&planning_task);

  rt_task_delete(&print_JointInfo);
  rt_task_delete(&webserver_task);

  printf("\n\n\t !! Controller Stopped!! \n");
  ecatmaster.deactivate();

  return 0;
}
