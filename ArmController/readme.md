## ethercat

### 1.1 启动，设置

+ ethercat都是在root用户下执行命令

+ 设置从站
  + ethercat alias -p 2 0:2

+ 启动ethercat
  + `/etc/init.d/ethercat start`

+ 查看状态
  + `ethercat slv`

### 1.2 启动测试程序

+ 可运行程序
  + `~/ArmController.taike/build/RobotArmController`

### 1.2 

+ `----status_word_:0x0,control_word:0x0---`输出的代码位置：
  + `arwen/include/ecat/ecat_taike.h` 39行

+ `I20230130 11:40:28.236125  5564 planning.cpp:504] No new point in buffer!` 输出代码位置：
  + `arwen/src/planning/planning.cpp` 504行

+ `Taike_POS: 5 , Taike_STATE: Fault` 输出代码位置：
  + `arwen/include/ecat/ecat_taike.h` 100行

---

## demo_webserver.cc 代码分析

### 读取从站信息

+ 每个从站，使用一个类`EcatTaike`的对象描述，六个从站放到一个存放数据类型为类`EcatTaike`类型的数组

### planner

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