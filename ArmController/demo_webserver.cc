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
RT_TASK ws_auto_send_task;

Planning planner;
bool running = false;
bool flag_movel = false;
bool flag_speedj = false;
bool flag_speedl = false;
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

  max_vel.data  << 5.0, 5.0, 5.0, 5.0, 5.0, 5.0;
  max_acc.data  << 2.0, 2.0, 2.0, 3.0, 3.0, 3.0;
  max_jerk.data << 2.0, 2.0, 2.0, 2.0, 2.0, 2.0;
  max_vel.data  = max_vel.data / 180 * M_PI;
  max_acc.data  = max_acc.data / 180 * M_PI;
  max_jerk.data = max_jerk.data / 180 * M_PI;

  /*********************MOVEJ joint points*********************/ 
  JointVector joint_init(6);
  JointVector joint_point1(6);
  joint_init.data   << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  joint_point1.data << 0.0, 10.0, 0.0, 15.0, -45.0, 20.0;
  joint_init.data   = joint_init.data / 180 * M_PI;
  joint_point1.data = joint_point1.data / 180 * M_PI;
  /***********************************************************/ 
  // planning Init
  planner.Init(0.001, chain, timestamp, joint_command_message, joint_status_message);
  while (true) 
  {
    rt_task_wait_period(nullptr);  // wait for next cycle

    if (break_flag) { break; }

    if (!system_ready) { continue; }

    joint_status_buffer = joint_status_message->load();
    planner.ProcessFrame(); // 每一帧都
  }
}

struct JointData_t
{
  double position_value;
};

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

int api_manual_movJ(struct mg_http_message *http_msg, struct mg_connection *connect)
{
  std::string response_header;
  GetResponseHeader(response_header);

  std::string tmp_str;
  double jointPosition[6];
  for (int i = 0; i < 6; i++)
  {
    tmp_str =  "$["+ std::to_string(i) +"]";
    mg_json_get_num(http_msg->body, tmp_str.c_str(), &jointPosition[i]);
    std::cout << "jointPositon[" << i << "] : " << jointPosition[i] << '\n';
  }

  JointVector joint_point01(6);
  joint_point01.data << jointPosition[0], jointPosition[1], jointPosition[2], jointPosition[3], jointPosition[4], jointPosition[5];
  joint_point01.data << joint_point01.data / 180 * M_PI;

  if (!planner.IsRunning() && !planner.getStopFlag())
  {
    planner.MoveJ(joint_point01, max_vel, max_acc, max_jerk);
    mg_http_reply(connect, 200, response_header.c_str(), "{%Q:%Q}\n", "movJ", "success");
  }
  else
  {
    std::string tmp_reply = "failed, the data :";
    for (int i = 0; i < 6; i++)
    {
      tmp_reply += std::to_string(jointPosition[i]);
      tmp_reply += ", ";
    }
    mg_http_reply(connect, 404, response_header.c_str(), "{%Q:%Q}\n", "movJ", "failed, not ready");
    // mg_http_reply(connect, 404, response_header.c_str(), "{%Q:%Q}\n", "movJ", tmp_reply.c_str());
  }

  return 0;
}

void WSMSGProcess(struct mg_ws_message *ws_msg)
{
  std::cout << "websocket message is :[" << ws_msg->data.ptr << "]" << std::endl;
}

// webserver auto send status info task
void WSAutoSendThread(void* arg) {
  RTIME now_ns;
  uint64_t tid = 0;
  std::string JointInfo_str;
  unsigned long long count = 0;
  struct JointData_t joint_data_array[ARM_DOF];
  rt_task_set_periodic(nullptr, TM_NOW, CYCLE_NS_WS);
  struct mg_connection *connect = (struct mg_connection *)arg;

  while (true) 
  {
    rt_task_wait_period(nullptr);  // wait for next cycle
    if (break_flag) { break; }
    //read data
    for (int k = 0; k < ARM_DOF; k++) 
    {
      joint_data_array[k].position_value = (ecat_taike[k].actual_position_ / JOINTS_PULSE) * 100;
    }

    JointInfo_str = mg_mprintf("{%Q:[%f,%f,%f,%f,%f,%f]}", "JointInfo",
                                joint_data_array[0].position_value,
                                joint_data_array[1].position_value,
                                joint_data_array[2].position_value,
                                joint_data_array[3].position_value,
                                joint_data_array[4].position_value,
                                joint_data_array[5].position_value);

    mg_ws_send(connect, JointInfo_str.c_str(), JointInfo_str.size(), WEBSOCKET_OP_TEXT);
  }
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
      api_manual_movJ(http_msg, connect);
    }
  }
  else if (event == MG_EV_WS_OPEN)
  {
    rt_task_create(&ws_auto_send_task, "ws_auto_send_task", 1024 * 1024 * 4, 50, 0);
    rt_task_start(&ws_auto_send_task, &WSAutoSendThread, connect);
  }
  else if (event == MG_EV_CLOSE)
  {
    rt_task_delete(&ws_auto_send_task);
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
  StartMGServer(listen_addr, &manager, connect);
  /**************************************************************/

  // pause
  while (break_flag == false) 
  	sched_yield();

  // cleanup
  printf("\n Deleting RT task ....");
  rt_task_delete(&driver_task);
  rt_task_delete(&control_task);
  rt_task_delete(&planning_task);
  rt_task_delete(&ws_auto_send_task);

  printf("\n\n\t !! Controller Stopped!! \n");
  ecatmaster.deactivate();

  return 0;
}