## Linux下RTC时间：系统时间与RTC实时时钟时间

+ Linux系统下包含两个时间：**系统时间** 和 **RTC时间**
  + 系统时间：是由主芯片的定时器进行维护的时间，一般情况下都会选择芯片上最高精度的定时器作为系统时间的定时基准，以避免在系统运行较长时间后出现大的时间偏移。特点是掉电后不保存
  + RTC时间：是指系统中包含的RTC芯片内部所维护的时间。RTC芯片都有电池+系统电源的双重供电机制，在系统正常工作时由系统供电，在系统掉电后由电池进行供电。因此系统电源掉电后RTC时间仍然能够正常运行
+ 每次Linux系统启动后在启动过程中会检测和挂在RTC驱动，在挂在后会自动从RTC芯片中读取时间并设置到系统时间中去。此后如果没有显式的通过命令去控制RTC的读写操作，系统将不会再从RTC中获取或者同步设置时间
+ Linux命令中`date`和`time`等命令都是用来设置系统时间的；而`hwclock`命令是用来设置和读写RTC时间的

## date

+ `date`命令可以用来显示或设定系统的日期与时间

+ `date [OPTION]... [+FORMAT]`

+ `date [-u] [-d datestr] [-s datestr] [--utc] [--universal] [--date=datestr] [--set=datestr] [--help] [--version] [+FORMAT] [MMDDhhmm[[CC]YY][.ss]]`

+ 可选参数
  + `-r, --reference=FILE`：显示文件的上次修改时间
  + `-s, --set=STRING`：根据字符串设置系统时间。
  + `-u, --utc, --universal`：显示或设置协调世界时(UTC)
  + `-f, --file=DATEFILE`：类似于--date; 一次从DATEFILE处理一行
  + `-d, --date=STRING`：通过字符串显示时间格式，字符串不能是'now'

+ `date -s "01:01:01 2012-05-23"`   # 这样可以设置全部时间

## Linux内核RTC实时时钟配置查看与选择

+ 进入到内核根目录下，输入`make menuconfig`进入到内核配置菜单

## dmesg

+ dmesg, print or control the kernel ring buffer
  + dmesg is used to examine or control the kernel ring buffer. The default action is to display all messages from the kernel ring buffer.
+ `dmesg, display message`, 命令用于显示开机信息。`Kernel`会将开机信息存储在`ring buffer`中。如果开机时来不及查看信息，可利用`dmesg`来查看。开机信息也保存在`/var/log`目录中，名为`dmesg`的文件里。

## tmux

+ `<ctrl  b> + d` or `tmux detach` : 分离当前会话
+ `tmux attach -t 0` : 进入指定序号的会话

## sysstat

+ `Sysstat`包中包含许多商业Unix常用的各种程序，用于监视系统性能和使用活动:
  + `iostat`  :报告块设备和分区的CPU统计信息和输入/输出统计信息
  + `mpstat`  :报告单个或组合处理器相关的统计信息
  + `pidstat` :报告Linux任务（进程）的统计信息：`I/O, CPU, 内存`等
  + `tapestat`:报告连接到系统的磁盘机的统计信息
  + `cifsiostat`:报告CIFS统计数据
+ 安装:`sudo apt-get install -y sysstat`
+ `Sysstat`还包含可以通过`cron`或`systemd`计划收集和历史记录性能和活动数据的工具：
  + `sar` : 收集，报告和保存系统活动信息
  + `sadc`: 系统活动数据收集器，用作`sar`的后端
  + `sa1` : 在系统活动每日数据文件中收集和存储二进制数据。它是`sadc`的前端，设计用于从`cron`或`systemd`运行
  + `sa2` : 编写了一个汇总的每日活动报告。它是`sar`的前端，目的是从`cron`或`systemd`运行
  + `sadf`: 以多种格式(`CSV, XML, JSON等`)显示`sar`收集的数据，可用于与其他程序进行数据交换。此命令还可用于绘制`sar`使用`SVG`（可缩放矢量图形）格式收集的各种活动的图形
  + 默认采样间隔为10分钟，但可以修改

### iostat

+ 单独执行iostat，显示的结果为从系统开机到当前执行时刻的统计信息。
  + `avg-cpu`：总体CPU使用情况统计信息，对于多核cpu，这里为所有cpu的平均值
  + `Device`：各磁盘设备的IO统计信息
+ `iostat`命令生成两种类型的报告：CPU使用率报告和设备使用率报告

+ CPU 使用率报告：由`iostat`命令生成的第一个报告是CPU使用率报告。对于多处理器系统，CPU值是所有处理器之间的全局平均值。该报告具有以下格式：
  + `%nice`   : 显示以良好优先级在用户级别执行时发生的CPU使用率百分比
  + `%user`   : 显示在用户级别（应用程序）执行时发生的CPU使用率的百分比。
  + `%system` : 显示在系统级别（内核）执行时发生的CPU利用率百分比
  + `%iowait` : 显示一个CPU或多个CPU处于空闲状态且系统有未完成的磁盘I/O请求的百分比
  + `%steal`  : 显示虚拟机管理程序为另一个虚拟处理器提供服务时，一个虚拟CPU或者多个虚拟CPU在非自愿等待中花费的时间百分比
  + `%idle`   : 显示单个CPU或者多个CPU处于空闲状态且系统没有完成的磁盘I/O请求的时间百分比 

+ 设备使用率报告：设备报告提供基于每个物理设备或分区的统计信息。可以在命令行上输入要显式其统计信息的块设备和分区。如果未输入设备或者分区，则会显示系统使用的每个设备的统计信息，并提供内核为其维护统计信息。如果在命令行上给出了ALL关键字，则会显示系统定义的每个设备的统计信息，包括从未使用过的设备。
+ 默认情况下，传输速率以1k块显示，除非设置了环境变量`POSIXLY_CORRECT`,在这种情况下，将使用512字节块。报告可能会显示以下字段，具体取决于使用的标志：
+ `Device`中各列含义：
  + `Device`：以sdX形式显示的设备名称
  + `tps`：每秒进程下发的IO读，写请求数量
  + `Blk_read/s`：每秒读扇区数量（一扇区为512bytes)
  + `Blk_wrtn/s`：每秒写扇区数量
  + `Blk_read`：取样时间间隔内读扇区总数量
  + `Blk_wrtn`：取样时间间隔内写扇区总数量

+ 可以使用`-c`选项单独显示`avg-cpu`部分的结果，使用`-d`选项单独显示`Device`部分的信息

## fdisk

+ fdisk命令来自于英文词组`Partition table manipulator for Linux`的缩写，其功能是用于管理磁盘的分区信息。
+ 语法格式：`fdisk [参数][设备]`
+ 常用参数
  + `-b`：指定每个分区的大小
  + `-l`: 列出指定的外围设备的分区表状况
  + `-s`：将指定的分区大小输出到标准输出上，单位为区块
  + `-u`：搭配`-l`参数列表，会用分区数目取代柱面数目，来表示每个分区的起始地址
  + `-v`：显示版本信息

## mkfs.ext4

+ `mkfs.ext4`命令来自于英文词组`make filesystem Ext4`的缩写，其功能是用于对磁盘设备进行Ext4格式化的操作。
+ 语法格式：`mkfs.ext4 [参数]设备`
+ 常用参数：
  + `-c` : 格式化前检查分区是否有坏块
  + `-q` : 执行时不显示任何信息
  + `-b <block-size>` : 指定`block size`的大小
  + `-F` : 强制格式化

## fstab文件

+ `/etc/fstab`，是用来存放文件系统的静态信息的文件。当系统启动的时候，系统会自动地从这个文件读取信息，并且会自动将此文件中指定的文件系统挂载到指定的目录。
+ 字段定义
  + `/etc/fstab`文件包含了如下字段，通过空格或者Tab分隔
  + `<file system>` : 要挂载的分区或存储设备
  + `<dir>` : `<file system>`的挂载位置
  + `<type>` : 要挂载设备或者是分区的文件系统类型，支持许多种不同的文件系统
  + `<options>` : 挂载时使用的参数，注意有些mount参数是特定文件系统才有的，一些比较常用的参数有：
    + `auto` : 在启动时或键入了`mount -a` 命令时自动挂载
    + `noauto` : 只在你的命令下被挂载
    + `exec` : 允许执行此分区的二进制文件
    + `noexec` : 不允许执行此文件系统上的二进制文件
    + `ro` : 以只读模式挂载文件系统
    + `rw` : 以读写模式挂载文件系统
    + `user` : 允许任意用户挂载此文件系统，若无明显定义，隐含启用了`noexec, nosuid, nodev`参数
    + `users` : 允许所有`users`组中的用户挂载文件系统
    + `nouser`： 只能被root挂载
    + `owner` : 允许设备所有者挂载
    + `sync` : I/O同步进行
    + `async` : I/O异步进行
    + `dev` : 解析文件系统上的块特殊设备
    + `suid` : 允许suid操作和设定sgid位。这一参数通常用于一些特殊任务，使一般用户运行程序时临时提升权限
    + `nosuid`： 禁止suid操作和设定sgid位
    + `defaults` : 使用文件系统的默认挂载参数，例如`ext4`的默认参数为`rw, suid, dev, exec, auto, nouser, async`
  + `<dump>` : dump工具通过它决定何时做备份，dump会检查其内容，并且用数字来决定是否对这个文件系统进行备份。允许的数字是0和1， 0 表示忽略，1 则进行备份。大部分的用户是没有安装dump的，对它们而言dump应该设置为0
  + `<pass>` : `fsck`读取`<pass>`的数值来决定需要检查的文件系统的检查顺序。允许的数字是0， 1和2。根目录应当获得最高的优先权1， 其他所有需要被检查的设备设置为2， 0表示设备不会被`fsck`所检查

## 文件系统标识

+ 在`/etc/fstab`配置文件中你可以以三种不同的方法表示文件系统：内核名称，UUID或者label。
+ 使用UUID或者是label的好处再与它们与磁盘顺序无关。
+ 如果你在BIOS中改变了你的存储设备顺序，或者是重新拔插了存储设备，或是因为一些BIOS可能会随即地改变存储设备的顺序，那么用UUID或者是label来表示将更有效

+ 显示分区的基本信息：`lsblk -f`
+ 内核名称：`fdisk -l` 来获得内核名称，前缀是`dev`
+ `UUID`：所有分区和设备都有唯一的UUID。**它们由文件系统生成工具`(mkfs.*)`在创建文件系统时生成。**

+ 路径名有空格，可以使用`\040`转义字符来表示空格（以三位八进制数来进行表示）
  + `UUID=47FA-4071 /home/username/Camera\040Pictures vfat defaults, noatime 0 2`

+ `tmpfs`
  + `tmpfs`是一个临时文件系统，驻留于你的交换分区或者是内存中（取决于你的使用情况）。使用它可以提高文件访问速度，并能够保证重启时会自动清除这些文件
  + 经常使用`tmpfs`的目录有`/tmp, /var/lock, /var/run`。不要把tmpfs使用于`/var/tmp`，因为这一个目录中的临时文件在重启过程中需要被保留。
  + 默认情况下，tmpfs分区被和设置为总的内存的一半，当然可以自由设定

## POSIX API

+ POSIX，全称为**可移植性操作系统接口**，是一种关于信息技术的IEEE标准。它包括了系统应用程序的接口（API），以及实时扩展（C语言）
+ 该标准的目的是定义了标准的基于UNIX操作系统的系统接口和环境来支持源代码级的可移植性。现在，标准主要提供了依赖C语言的一系列标准服务，在将来的版本中，标准将致力于提供基于不同语言的规范。
+ 该标准对核心需求部分定义了一系列任何编程语言都通用的服务，这一部分服务主要从其功能需求方面阐述，而非定义依赖于编程语言的接口。
+ 语言规范主要由两部分组成
  + 一部分包括了访问核心服务的编程语言的标准接口，这些核心服务为标准中基于编程语言的核心需求部分所定义
  + 另一部分包含了一个特殊语言服务的标准接口。

+ 该标准一共被分为四个部分：
  + 陈述的范围和一系列标准参考
  + 定义和总概念
  + 各种接口设备
  + 头文件

## Linux下视频剪辑，录制工具

+ kazam 
  + 录制屏幕：`apt-get install -y kazam`
  + 缺点：保存的视频，在vlc打开看不到视频，传到手机剪影也不能剪辑

+ openshot
  + `apt-get install -y openshot-qt`
  + 和pr相似

+ **simplescreenrecorder**
  + 录制屏幕：`apt-get install -y simplescreenrecorder`
  + 优点：相比于kazam，其录制的视频，容量小，vlc支持播放

## 屏保命令和锁屏命令

+ `gnome-screensaver-command -a`  --  显示屏保但是不锁定，移动鼠标或敲击键盘后自动消失

+ `gnome-screensaver-command -l`  --  显示屏保并锁定，移动鼠标或敲击键盘弹出密码框

+ `sudo loginctl list-sessions`   -- 列出当前所有的会话（默认命令）

+ `sudo loginctl lock-session [ID]`   -- 锁定指定会话（如果会话支持屏幕锁）或者当前调用者的会话

+ `sudo loginctl unlock-session [ID]` -- 解锁指定会话（如果会话支持屏幕锁）或者当前调用者的会话

+ `sudo loginctl lock-sessions`  --  锁定全部会话

+ `sudo loginctl unlock-sessions` -- 解锁全部会话