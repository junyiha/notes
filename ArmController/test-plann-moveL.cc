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
#define JOINTS_PULSE (131072.0 / 2.0 / M_PI)

Master ecatmaster;
EcatTaike ecat_taike[ARM_DOF];

std::atomic_bool system_ready = false;
std::atomic_bool break_flag = false;

// Xenomai RT tasks
RT_TASK driver_task;
RT_TASK control_task;
RT_TASK planning_task;

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

  Planning planner;
  planner.Init(0.001, chain, timestamp, joint_command_message,
               joint_status_message);

  protocol::message::JointStatusMessage joint_status_buffer;

  bool running = false;
  bool flag_movel = false;
  bool flag_stop_onlyonce = false;
  bool flag_release_once = false;
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
  max_vel.data << 5.0, 5.0, 5.0, 5.0, 5.0, 5.0;
  max_acc.data << 2.0, 2.0, 2.0, 3.0, 3.0, 3.0;
  max_jerk.data << 2.0, 2.0, 2.0, 2.0, 2.0, 2.0;
  max_vel.data = max_vel.data / 180 * M_PI;
  max_acc.data = max_acc.data / 180 * M_PI;
  max_jerk.data = max_jerk.data / 180 * M_PI;

  // zero point:
  JointVector zero_point(6);
  zero_point.data << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  // user input joint point:
  JointVector input_joint_point1(6);
  input_joint_point1.data << 30.0, 30.0, 30.0, 30.0, 30.0, 30.0;
  // input_joint_point1.data<<-30.0,-30.0,-30.0,-30.0,-30.0,-30.0;
  // input_joint_point1.data<<-40.0,-40.0,-40.0,-40.0,-40.0,-40.0;
  input_joint_point1.data = input_joint_point1.data / 180 * M_PI;
  JointVector input_joint_point2(6);
  input_joint_point2.data << -40.0, 10.0, -40.0, 40.0, -70.0, -40.0;
  input_joint_point2.data = input_joint_point2.data / 180 * M_PI;
  // user input single moveL point:
  Frame cart_point1;
  FkSolverPosKdl fk_solver_kdl;
  fk_solver_kdl.Init(chain);
  fk_solver_kdl.JntToCart(input_joint_point2, cart_point1);
  Frame cart_point2;
  cart_point2 = cart_point1;

  // cart_point2.p(2) = cart_point2.p(2) - 0.05;// move 5cm in -z
  // cart_point2.p(1) = cart_point2.p(1) - 0.05;//move 5cm in -y
  // cart_point2.p(0) = cart_point2.p(0) - 0.05;//move 5cm in -x

  //  Rotation rot_x=Rotation::RotX(0.2);//rotate 0.2 rad around x axis
  //  cart_point2.rot.data=rot_x.data*cart_point2.rot.data;

  //  Rotation rot_y=Rotation::RotY(0.2);//rotate 0.2 rad around y axis
  //  cart_point2.rot.data=rot_y.data*cart_point2.rot.data;

  //  Rotation rot_z=Rotation::RotZ(0.2);//rotate 0.2 rad around y axis
  //  cart_point2.rot.data=rot_z.data*cart_point2.rot.data;

  // user input multiple MoveL Point:
  cart_point2.p(2) = cart_point2.p(2) - 0.05;  // move 5cm in -z
  Frame cart_point3 = cart_point2;
  Rotation rot_x = Rotation::RotX(0.2);  // rotate 0.2 rad around x axis
  cart_point3.rot.data = rot_x.data * cart_point3.rot.data;
  Frame cart_point4 = cart_point3;
  cart_point4.p(0) = cart_point4.p(0) + 0.05;  // move 5cm in +x

  // user input speedJ velocity:
  JointVector input_joint_vel(6);
  input_joint_vel.data << 2.0, 2.0, 2.0, 2.0, 2.0, 2.0;
  input_joint_vel.data = input_joint_vel.data / 180 * M_PI;

  // user input speedL velocity:
  dynamics::common::Velocity input_cart_vel;
  input_cart_vel.p = dynamics::common::Vector(
      0.0, 0.0, -0.005);  // move in -z axis with speed of 0.005m/s
  input_cart_vel.rot = dynamics::common::Vector(0.0, 0.0, 0.0);

  dynamics::common::Velocity input_cart_vel2;
  input_cart_vel2.p = dynamics::common::Vector(0.0, 0.0, 0.0);
  input_cart_vel2.rot = dynamics::common::Vector(
      0.0, 0.0, 0.01);  // rotate around z-axis with speed of 0.01 rad/s

  // singular point
  JointVector joint_point_start(6);
  joint_point_start.data << 0.0, 0.0, 85.0, 90.0, 0.0, 0.0;
  joint_point_start.data = joint_point_start.data / 180 * M_PI;
  Frame cart_point_start;
  fk_solver_kdl.JntToCart(joint_point_start, cart_point_start);
  Frame cart_pointend;
  cart_pointend = cart_point_start;
  cart_pointend.p(2) = cart_pointend.p(2) + 0.5;

  // test virtuallwall
  JointVector virtual_wall_start(6);
  virtual_wall_start.data << 7.0, 40.0, -40.0, 60.0, 20.0, 0.0;
  virtual_wall_start.data = virtual_wall_start.data / 180.0 * M_PI;
  dynamics::common::Velocity input_cart_vel_vw;
  input_cart_vel_vw.p = dynamics::common::Vector(0.005, 0.0, 0.0);
  input_cart_vel_vw.rot = dynamics::common::Vector(0.0, 0.0, 0.0);

  CartesianConstraint cart_constrain;
  cart_constrain.vel_p = 0.05;
  cart_constrain.vel_rot = 0.05;
  cart_constrain.acc_p = 0.05;
  cart_constrain.vel_p = 0.05;

  Plane plane1;
  Plane plane2;
  plane1.normal_vec << -1.0, 0.0, 0.0;
  plane1.point << -0.4, 0.0, 0.0;  // about -0.58 singular point
  plane2.normal_vec << 0.0, 0.0, 1.0;
  plane2.point << 0.0, 0.0, 0.0;

  cart_constrain.planes.emplace_back(plane1);
  cart_constrain.planes.emplace_back(plane2);
  chain->SetUserCartesianConstraint(cart_constrain);

  planner.SetVirtualWall(false);

  // test joint position constraint
  JointVector input_joint_vel_constrain(6);
  input_joint_vel_constrain.data << 0.0, 0.0, 5.0, 0.0, 0.0, 0.0;
  input_joint_vel_constrain.data = input_joint_vel_constrain.data / 180 * M_PI;

  // test joint velocity constraint
  JointVector joint_velc_start(6);
  joint_velc_start.data << 0.0, 0.0, -80.0, 0.0, 0.0, 0.0;
  joint_velc_start.data = joint_velc_start.data / 180 * M_PI;
  JointVector max_vel_c(6);
  JointVector max_acc_c(6);
  JointVector max_jerk_c(6);
  max_vel_c.data << 1.0, 1.0, 2.0, 1.0, 1.0, 1.0;
  max_acc_c.data << 1.0, 1.0, 1.0, 1.0, 1.0, 1.0;
  max_jerk_c.data << 1.0, 1.0, 1.0, 1.0, 1.0, 1.0;

  JointVector target_vel_c(6);
  target_vel_c.data << 0.0, 0.0, 1.1, 0.0, 0.0, 0.0;

  while (true) {
    rt_task_wait_period(nullptr);  // wait for next cycle

    if (break_flag) break;
    if (!system_ready) {
      count = 0;
      continue;
    }
    joint_status_buffer = joint_status_message->load();

    planner.ProcessFrame();

    // test joint velocity constraint

    // if (count > 1000 && !running && !planner.IsRunning()) {
    //   planner.MoveJ(joint_velc_start, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedj) {
    //   // planner.SpeedJ(target_vel_c, max_vel_c, max_acc_c, max_jerk_c);
    //   // flag_speedj = true;
    // }

    // test joint position constraint

    // if (count > 1000 && !running && !planner.IsRunning()) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedj) {

    //   planner.SpeedJ(input_joint_vel_constrain, max_vel, max_acc, max_jerk);
    //   flag_speedj = true;
    // }

    // test virtual wall

    // if (count > 1000 && !running && !planner.IsRunning()) {
    //   planner.MoveJ(virtual_wall_start, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedl) {
    //   planner.SetVirtualWall(true);
    //   planner.SpeedL(input_cart_vel_vw, cart_max_vel, cart_max_acc,
    //                  cart_max_jerk, rot_max_vel, rot_max_acc, rot_max_jerk);
    //   flag_speedl = true;
    // }

    // test singular point

    // if (count > 3000 && !running && !planner.IsRunning()) {
    //   planner.MoveJ(joint_point_start, max_vel, max_acc, max_jerk);
    //   planner.MoveL(cart_pointend, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   running = true;
    // }

    // test single MoveJ

    // if (count > 1000 && !running && !planner.IsRunning()) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);
    //   planner.MoveJ(input_joint_point1, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // test multiple MoveJ

    // if (count > 1000 && !running && !planner.IsRunning()) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);
    //   planner.MoveJ(input_joint_point1, max_vel, max_acc, max_jerk);
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // test single MoveL

    // if (!running && !planner.IsRunning()) {
    // // if (count > 1000 && !running && !planner.IsRunning()) {
    //   std::cout << "Starting to execute moveL" << std::endl;
    // // if (!running && !planner.IsRunning()) {
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   planner.MoveL(cart_point2, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   running = true;
    // }

    // //test multiple MoveL:

    if (count > 1000 && !running && !planner.IsRunning()) {
      printf("Start moveL command >>> \n");
      //planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
      planner.MoveL(cart_point2, cart_max_vel, cart_max_acc, cart_max_jerk,
                    rot_max_vel, rot_max_acc, rot_max_jerk);
      planner.MoveL(cart_point3, cart_max_vel, cart_max_acc, cart_max_jerk,
                    rot_max_vel, rot_max_acc, rot_max_jerk);
      planner.MoveL(cart_point4, cart_max_vel, cart_max_acc, cart_max_jerk,
                    rot_max_vel, rot_max_acc, rot_max_jerk);
      running = true;
    }

    // cross MoveJ and MoveL

    // if (count > 1000 && !running && !planner.IsRunning()) {
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   planner.MoveL(cart_point2, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   planner.MoveL(cart_point3, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   running = true;
    // }

    // stop at MoveJ

    // if (count > 5000 && !planner.getStopFlag()) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    // }
    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !planner.getStopFlag()) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);
    //   planner.MoveJ(input_joint_point1, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // stop at MoveL

    // if (count > 20000 && !planner.getStopFlag()) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    // }

    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !planner.getStopFlag()) {
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   planner.MoveL(cart_point2, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);
    //   running = true;
    // }

    // stop at speedJ
    // if (count > 45000 && !planner.getStopFlag()) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    // }

    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !planner.getStopFlag()) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);

    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedj &&
    //     !planner.getStopFlag()) {
    //   planner.SpeedJ(input_joint_vel, max_vel, max_acc, max_jerk);
    //   flag_speedj = true;
    // }

    // //stop at speedL:

    // if (count > 12000 && !planner.getStopFlag()) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    // }
    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !planner.getStopFlag()) {
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedl &&
    //     !planner.getStopFlag()) {
    //   planner.SpeedL(input_cart_vel, cart_max_vel, cart_max_acc,
    //   cart_max_jerk,
    //                  rot_max_vel, rot_max_acc, rot_max_jerk);
    //   flag_speedl = true;
    // }

    // test MoveJ after Stoprelease

    // if (count > 12000 && !planner.getStopFlag() && !flag_stop_onlyonce) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    //   flag_stop_onlyonce = true;
    // }

    // if (count > 2000 && !running && !planner.IsRunning() &&
    //     !flag_stop_onlyonce && !flag_stop_onlyonce) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);

    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedj &&
    //     !flag_stop_onlyonce) {
    //   planner.SpeedJ(input_joint_vel, max_vel, max_acc, max_jerk);
    //   flag_speedj = true;
    // }

    // if (count > 13000 && planner.getStopFlag() && !flag_release_once) {
    //   planner.StopRelease();
    //   flag_release_once = true;
    // }

    // if (count > 13500 && running && !planner.IsRunning() &&
    //     flag_stop_onlyonce) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);

    //   running = false;
    // }

    // test moveL after stoprelease:

    // if (count > 10000 && !planner.getStopFlag() && !flag_stop_onlyonce) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    //   flag_stop_onlyonce = true;
    // }

    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !planner.getStopFlag() && !flag_stop_onlyonce) {
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedl &&
    //     !planner.getStopFlag()) {
    //   planner.SpeedL(input_cart_vel, cart_max_vel, cart_max_acc,
    //   cart_max_jerk,
    //                  rot_max_vel, rot_max_acc, rot_max_jerk);
    //   flag_speedl = true;
    // }

    // if (count > 11000 && planner.getStopFlag() && !flag_release_once) {
    //   planner.StopRelease();
    //   flag_release_once = true;
    // }

    // if (count > 11500 && running && !planner.IsRunning() &&
    // flag_release_once) {
    //   planner.MoveL(cart_point1, cart_max_vel, cart_max_acc, cart_max_jerk,
    //                 rot_max_vel, rot_max_acc, rot_max_jerk);

    //   running = false;
    // }

    // test speedJ after stoprelease:

    // if (count > 13000 && !planner.getStopFlag() && !flag_stop_onlyonce &&
    //     !flag_release_once) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    //   flag_stop_onlyonce = true;
    // }

    // if (count > 2000 && !running && !planner.IsRunning() &&
    //     !flag_stop_onlyonce && !flag_release_once) {
    //   planner.MoveJ(zero_point, max_vel, max_acc, max_jerk);

    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedj &&
    //     !flag_stop_onlyonce) {
    //   planner.SpeedJ(input_joint_vel, max_vel, max_acc, max_jerk);
    //   flag_speedj = true;
    // }

    // if (count > 16000 && planner.getStopFlag() && !flag_release_once) {
    //   planner.StopRelease();
    //   flag_release_once = true;
    // }

    // if (count > 17000 && running && !planner.IsRunning() &&
    // flag_release_once) {
    //   planner.SpeedJ(input_joint_vel, max_vel, max_acc, max_jerk);

    //   running = false;
    // }

    // if (count > 22000 && !planner.getStopFlag() && flag_stop_onlyonce &&
    //     flag_release_once) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    //   flag_stop_onlyonce = false;
    // }

    // test speedL after stoprelease

    // if (count > 12000 && !planner.getStopFlag() && !flag_stop_onlyonce &&
    //     !flag_release_once) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    //   flag_stop_onlyonce = true;
    // }

    // if (count > 1000 && !running && !planner.IsRunning() &&
    //     !flag_stop_onlyonce && !flag_release_once) {
    //   planner.MoveJ(input_joint_point2, max_vel, max_acc, max_jerk);
    //   running = true;
    // }

    // if (running && !planner.IsRunning() && !flag_speedl &&
    //     !flag_stop_onlyonce) {
    //   planner.SpeedL(input_cart_vel, cart_max_vel, cart_max_acc,
    //   cart_max_jerk,
    //                  rot_max_vel, rot_max_acc, rot_max_jerk);
    //   flag_speedl = true;
    // }
    // if (count > 15000 && planner.getStopFlag() && !flag_release_once) {
    //   planner.StopRelease();
    //   flag_release_once = true;
    // }
    // if (count > 16000 && running && !planner.IsRunning() &&
    // flag_release_once) {
    //   planner.SpeedL(input_cart_vel2, cart_max_vel, cart_max_acc,
    //   cart_max_jerk,
    //                  rot_max_vel, rot_max_acc, rot_max_jerk);
    //   running = false;
    // }
    // if (count > 22000 && !planner.getStopFlag() && flag_stop_onlyonce &&
    //     flag_release_once) {
    //   planner.Stop(max_vel, max_acc, max_jerk);
    //   flag_stop_onlyonce = false;
    // }

    ++count;
  }
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
  // printf("\n-- running cyclic(ethercat) task ...\n");
  rt_task_start(&driver_task, &DriverThread, nullptr);

  // printf("\n-- running control(robot) task ...\n");
  rt_task_create(&control_task, "control_task", 1024 * 1024 * 4, 60, 0);
  rt_task_start(&control_task, &ControlThread, nullptr);

  rt_task_create(&planning_task, "planning_tast", 1024 * 1024 * 4, 50, 0);
  rt_task_start(&planning_task, &PlanningThread, nullptr);

  // pause
  while (break_flag == false) sched_yield();

  // cleanup
  printf("\n Deleting RT task ....");
  rt_task_delete(&driver_task);
  rt_task_delete(&control_task);
  rt_task_delete(&planning_task);

  printf("\n\n\t !! Controller Stopped!! \n");
  ecatmaster.deactivate();

  return 0;
}
