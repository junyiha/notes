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