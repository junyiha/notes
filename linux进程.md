## ps

+ ps命令用于报告当前系统的进程状态，可以搭配kill指令随时中断，删除不必要的程序。
+ ps明星是最基本的同时也是非常强大的进程查看命令，使用该命令可以确定有哪些进程正在运行和运行的状态，进程是否结束，进程有没有僵死，哪些进程占用了过多的资源等等
+ 参数
  + `a` : 显示当前终端下的所有进程信息，包括其他用户的进程
  + `u` : 使用以用户为主的格式输出进程信息
  + `x` : 显示当前用户在所有终端下的进程
+ 字段解释
  + `USER` : 启动该进程的用户账号名称
  + `PID`  : 该进程的ID号,在当前系统中是唯一的
  + `%CPU` : CPU占用的百分比
  + `%MEM` : 内存占用的百分比
  + `VSZ`  : 占用虚拟内存(swap空间)的大小
  + `RSS`  : 占用常驻内存(物理内存)的大小
  + `TTY`  : 该进程在哪个终端上运行. `"?"`表示未知或不需要终端
  + `STAT` : 显示了进程当前的状态
    + `S , interruptible sleep (waiting for an event to complete` : 休眠
    + `R , running or runnable (on run queue)` : 运行
    + `Z , defunct("zombie") process, terminated but not reaped by its parent` : 僵死, 对于僵死状态的进程应该手动终止
    + `< , high-priority (not nice to other users)` : 高优先级
    + `N , low-priority (nice to other users)` : 低优先级
    + `s , is a session leader` : 父进程
    + `+ , is in the foreground process group` : 前台进程
    + `l , is multi-threaded(using CLONE_THREAD, like NPTL pthreads do)`:多线程
  + `START`: 启动该进程的时间
  + `TIME` : 该进程占用CPU的时间
  + `COMMAND`: 启动该进程的命令的名称
+ 参数
  + `e` : 显示系统内的所有进程信息
  + `l` : 使用长(long)格式显示进程信息
  + `f` : 使用完整的(full)格式显示进程信息

## top

+ top, 以全屏交互式的界面显示进程排名,及时跟踪包括CPU,内存等系统资源占用情况,默认情况下每三秒刷新一次,其作用基本类似于Windows系统中的任务管理器
+ 字段解释:
  + `Tasks` : 系统任务信息
  + `total` : 总进程数
  + `running` : 正在运行的进程数
  + `sleeping` : 休眠的进程数
  + `stopped`  : 终止的进程数
  + `zombie`  : 僵死无响应的进程数

+ 常用命令
  + `top ` 回车之后再输入c，会显示进程详细信息

## pstree

+ pstree,以树状图的方式展现进程之间的派生关系,显示效果比较直观
+ 参数
  + `a` : 显示每个程序的完整指令,包含路径,参数或者是常驻服务的标示
  + `c` : 不使用精简表示法
  + `G` : 使用VT100终端机的列绘图字符
  + `n` : 用程序识别码排序,预设是以程序名称来排序
  + `p` : 显示程序识别码
  + `u` : 显示用户名称

## 查看指定端口

+ `sudo netstat -tln | grep 8083`
+ `sudo lsof -i:8083`

## 杀死指定进程

+ `kill -9 process_pid`