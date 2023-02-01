## ethercat

### 1.1 启动，设置

+ ethercat都是在root用户下执行命令

+ 设置从站
  + ethercat alias -p 2 0:2

+ 启动ethercat
  + `/etc/init.d/ethercat start`

+ 查看状态
  + `ethercat slv`

### 1.2 公式

+ 编码器增量 enc 转换 关节位置 rad （弧度）
  + `rad = (double) (enc - offset) / (double) (gear_ratio * enc_size) * (2 * PI)`

+ 关节位置 rad （弧度） 转换 编码器增量 enc
  + `enc = (int) (rad) / (2.0 * PI) * (gear_ratio * enc_size) + offset`

+ 弧度 rad 和 角度 deg 的变换
  + `deg = rad * (180 / PI)`

+ 角度 deg 和 弧度 rad 的变换
  + `rad = deg * (PI / 180)`

### 1.2 启动测试程序

+ 可运行程序
  + `~/ArmController.taike/build/RobotArmController`

### 1.2 

+ `----status_word_:0x0,control_word:0x0---`
  + 输出的代码位置：
    + `arwen/include/ecat/ecat_taike.h` 39行

+ `I20230130 11:40:28.236125  5564 planning.cpp:504] No new point in buffer!` 
  + 输出代码位置：
    + `arwen/src/planning/planning.cpp` 504行

+ `Taike_POS: 5 , Taike_STATE: Fault` 
  + 输出代码位置：
    + `arwen/include/ecat/ecat_taike.h` 100行

+ `Command joint position lower overrun` 
  + 输出代码位置：
    + `arwen/src/planning/security_module.cpp` 32行

+ `Joint num : 3 Command joint position upper overrun!` 
  + 输出代码位置
    + `arwen/src/planning/security_module.cpp` 26行
  + 原因：安全模块检测到了下发的指令超出了约束
  + 解决办法：
    + 在文件：`arwen/src/protocol/configuration/manipulator.cpp` 中，把除以2的去掉就是关键可以转动正负180度

+ `The velocity is a negtive value:0` 
  + 输出代码位置：
    + `arwen/src/planning/curves/double_s_stop.cpp` 76行

+ `delta_pos.norm : 0.194793` 
  + 输出代码位置：
    + `arwen/src/planning/planner/move_line.cpp` 74行

+ `KDL error: The joint position increments are to small` 
  + 输出代码位置：
    + `arwen/src/dynamics/solver/ik_solver_pos_lma.cpp` 55行

+ `singular point! please choose another point!` 
  + 输出代码位置：
    + `arwen/src/planning/planning.cpp`  682行

---

## demo_webserver.cc 代码分析

### 读取从站信息

+ 每个从站，使用一个类`EcatTaike`的对象描述，六个从站放到一个存放数据类型为类`EcatTaike`类型的数组

+ planner 应该有获取机械臂当前状态信息的接口

### Planning

+ class Planning
+ 成员函数：
  + `Init()`
  + `ProcessFrame()`
  + `IsRunning()`
  + `MoveJ()`
  + `MoveL()`
  + `Stop()`
  + `SpeedJ()`
  + `SpeedL()`
  + `StopRelease()`
  + `getStopFlag()`
  + `SetVirtualWall()`

+ `const bool planner.IsRunning()` ： 判断机械臂是否在运行，
  + 如果在运行，就返回 true，这个时候就不能执行其他指令；
  + 如果不在运行，就返回 false，这个时候才可以执行其他指令

+ `const bool planner.getStopFlag()` ： 获取结束标志
  + 如果设置了结束标志，则返回 true，这个时候就表示机械臂已经停止工作，不能再执行其他指令
  + 如果没有设置结束标志，则返回 false，这个时候就表示机械臂还在工作，可以执行其他指令

+ `void setStopFlag(bool flag)` ： 设置结束标志
  + 如果传入的flag为true，表示设置了结束标志
  + 如果传入的flag为false，表示没有

---

### FkSolverPosKdl

+ `class arwen::dynamics::solver::FkSolverPosKdl`
+ 成员函数：
  + `Init()`
  + `JntToCart()`
    + 计算 机械臂从关节空间坐标到笛卡尔空间坐标的正运动学

### Frame

+ `class arwen::dynamics::common::Frame`
+ 该类表示相对于 {Ref} 的笛卡尔坐标 {Obj}。
+ 换句话说，它表示从 {Ref} 到 {Obj} 的齐次转换。齐次矩阵形式的帧为 frame {Ref} {Obj} = [旋转 {Ref} {Obj}， p{Ref} {Obj};0, 1]

### Rotation

+ `class arwen::dynamics::common::Rotation`
+ 该类表示笛卡尔空间中的旋转。
+ 旋转矩阵 rotate {Rel} {Obj} (我们称之为从 {Ref} 到 {Obj} 的旋转)表示 {Obj} 相对于 {Rel} 的方向。
+ 换句话说，它表示从 {Obj} 到 {Ref} 的旋转。具有以下属性:`旋转{A}{B} =旋转逆{B}{A} =旋转转置{B}{A}旋转{A}{C} =旋转{A}{B}*旋转{B}{C} p{A} = 旋转{A}{B}*p{B}`

## WebServer

### 1.1 架构设计

+ 功能 | 业务

+ 分层 | 分模块

+ 现在的设计思路：
  + 事件处理函数，事件监听函数都封装在了一个类中

+ 新的设计思路：
  + 暂时不封装成类，而是将使用到的函数都分开在不同的源文件中实现，统一在demo中调用

+ 启动服务，监听事件的发生
  + 输入：
    + 监听地址
    + struct mg_mgr
    + struct mg_connection
+ 事件处理函数
  + 处理的事件有：
    + WebSocket连接建立时
      + 创建一个实时线程`rt_task_create`，定时向客户端发送机械臂的状态信息
    + WebSocket连接断开时
      + 销毁该连接建立时创建的实时线程`rt_task_delete`
    + 接收到一个HTTP消息时
      + 当请求是`/websocket`时，升级该HTTP连接到WebSocket连接
      + 当请求是`/api/*`时，针对相应的接口，调用相应的函数处理请求

### 1.2 前后端通信

+ 前端发送一个ping
+ 后端接收，判断消息为ping之后，发向前端发送 flag = true，表示可以发送机械臂信息
+ 前端接收flag消息，如果为true，就发送一个目标点位置，
+ 后端接收的消息如果为目标点位置，就执行如下动作
  + 首先，启动一个线程，定时发送机械臂状态信息
  + 其次，调用moveJ使机械臂运动到目标点位置
  + 最后，如果运行完成，退出定时发送状态信息的线程，并发送flag = false

### 1.3 模块

#### 1.3.1 手动控制

+ HTTP通信，发送的数据为
  + `{"jointPosition":[10, 20, 30, 40, 50, 60]}`

#### 1.3.2 精确控制

+ WebSocket通信，发送的数据为
  + `{"jointSpace":[10, 20, 30, 40, 50, 60]}`