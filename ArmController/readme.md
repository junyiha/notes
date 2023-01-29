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

## demo_webserver.cc 代码分析

### 读取从站信息

+ 每个从站，使用一个类`EcatTaike`的对象描述，六个从站放到一个存放数据类型为类`EcatTaike`类型的数组

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