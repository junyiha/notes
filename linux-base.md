## more

+ more, 一次显示一页

## MD5校验

+ Windows下生成md5校验码: `certutil -hashfile filename MD5`
+ Linux下生成md5校验码:   `md5sum filename`

## nohup

+ `nohup, no hang up`， 用于在系统后台不挂断地运行命令，退出终端不会影响程序的运行
+ 在默认情况下（非重定向时），会输出一个名叫`nohup.out`的文件在当前目录下，如果当前目录下文件不可写，输出重定向到`$HOME/nohup.out`文件中

+ 语法格式 -- `nohup Command [Arg ...] [ & ]`

+ 参数说明
  + `Command` -- 要执行的命令
  + `Arg` -- 一些参数，可以指定输出文件
  + `&` -- 让命令在后台执行，终端退出后命令仍旧执行


## `.7z` 文件

+ 使用`p7zip`软件解压
+ 参数：
  + `-d , --decompress --uncompress` : decompress file
  + `-c --stdout --to-stdout` : output data to stdout
  + `` 

## mktemp

+ mktemp, 创建临时的文件或文件夹
+ 参数：
  + `-d` , `--directory` : create a directory, not a file
  + `-u` , `--dry-run`   : do not create anything; merely print a name(unsafe)
  + `-q` , `--quiet`     : suppress diagnostics about file/dir-creation failure

## wc

+ `wc`,命令用于计算字数
+ 利用`wc`指令我们可以计算文件的Byte数，字数，或者是列数，如果不指定文件名称，或者是所给的文件名为`"-"`，则wc指令会从标准如入设备读取数据
+ 语法：`wc [-clw][--help][--version][files...]`
+ 参数：
  + `-c, -bytes, --chars`：只显示Bytes数
  + `-l， --lines`：显示行数
  + `-w, --words`：只显示字数
+ 查看某个目录下的文件数：`ls -l | grep "-" | wc -l`
## ar

+ ar命令，用于建立或修改备存文件，或者是从备存文件中抽取文件
+ ar可以集合许多文件，成为单一的备存文件。在备存文件中，所有成员文件皆保有原来的属性与权限
+ 语法
  + `ar [ -dmpqrtx ] [ cfosSuvV ] [ a<成员文件> ] [ b<成员文件> ] [ i<成员文件> ] [ 备存文件 ] [ 成员文件 ]`
+ 参数
  + `-d` : 删除备存文件中的成员文件
  + `-m` : 变更成员文件在备存文件中的次序
  + `-p` : 显示备存文件中的成员文件内容
  + `-q` : 将文件附加在备存文件末端
  + `-r` : 将文件插入备存文件中
  + `-t` : 显示备存文件中所包含的文件
  + `-x` : 自备存文件中取出成员文件
+ 选项参数：
  + `a<成员文件>` : 将文件插入备存文件中指定的成员文件之后
  + `b<成员文件>` : 将文件插入备存文件中指定的成员文件之前
  + `c` : **建立备存文件**
  + `f` : 为避免过场的文件名不兼容于其他系统的ar指令，因此可使用此参数，截掉要放入备存文件中过长的成员文件名称
  + `i<成员文件>` : 将文件插入备存文件中指定的成员文件之前
  + `o` : 保留备存文件中文件的日期
  + `s` : 若备存文件中包含了对象模式，可利用此参数建立备存文件的符号表
  + `S` : 不产生符号表
  + `u` : 只将日期较新文件插入备存文件中
  + `v` : 程序执行时显示详细的信息
  + `V` : 显示版本信息

## lsmod

+ lsmod - Show the status of modules in the Linux Kernel

## screen

+ screen， 提供从单个SSH会话中使用多个shell窗口
+ 常用命令：
  + `screen -S name` : 创建会话并命名
  + `screen -r -S name` : 重新连接会话
  + `ctrl - a & d`   : 分离会话
  + 

## 文件名通配符

+ `×`：与0个或多个任意的字符相匹配
+ `？`：只与单个任意的字符匹配，可以使用多个问号
+ `[]`：与`？`相似，只与一个字符匹配。区别在于：问号与任意一个字符匹配，而方括号只与方括号中列出的字符之一匹配。短横线（`-`）代表一个范围内的字符。注：只能是升序

## sudo  

+ sudo, superuser do

## source  

+ source命令（从 C Shell而来）是`bash shell`的内置命令； `.` 点命令，就是一个点符号，是source的另一名称。这两个命令都以一个脚本为参数，该脚本将在当前shell的环境执行，即** 不会启动一个新的子shell** 。所有在脚本中设置的变量都将成为当前shell的一部分
+ source命令的妙用：
  + 在编译核心时，常常要反复输入一长串命令。这些命令即长又繁琐，而且有时候容易输错。
  + 如果把命令做成一个文件，让它自动执行，对于需要多次反复编译核心的用户来说，会很方便
  + 用source命令可以做到这一点。** 它的作用就是把一个文件的内容当成是shell来执行** 
+ `source filename, sh filename, ./filename`
  + 当shell脚本具有可执行权限时，用`sh filename`与`./filename`执行脚本没有区别。 `./filename`是因为当前目录没有在`PATH`, 所有`.` 都是用来表示当前目录的


## tar 

+ tar(tape archive),命令用于备份文件
+ tar是用来建立,还原备份文件的工具程序,它可以加入,解开备份文件内的文件

## df 

+ df(disk free),命令用于显示目前在Linux系统上的文件系统磁盘的使用情况统计

## 中文语言包 

+ `apt-get install language-pack-zh-hans`

## du 

+ du(disk usage),命令用于显示目录或文件的大小
+ du会显示指定的目录或文件所占用的磁盘空间

## apt-file

+ 查找包文件
  + `apt-file find libopenssh.so`

## useradd 

+ useradd, 用于建立用户账号
+ useradd可用来建立用户账号,账号建好之后,再用passwd设定账号的密码,用userdel删除账号,
+ 示例:
  + `useradd tt # 添加一般用户`
  + `useradd -g root tt  # 为添加的用户指定相应的用户组`
  + `useradd -r tt  # 创建一个系统用户`
  + `useradd -d /home/myd tt  # 为新添加的用户指定home目录`
  + `useradd caojh -u 544  # 建立用户并制定id`

## userdel 

+ 命令用于删除用户账号
+ userdel可删除用户账号与相关的文件,若不加参数,则仅删除用户账号,而不删除相关文件
+ `userdel -r username`

## grep 

+ grep,命令用于查找文件里符合条件的字符串
+ grep指令用于查找内容包含指定的范本样式的文件,如果发现某文件的内容符合所指定的范本样式,预设grep指令会把含有范本样式的那一列显示出来
+ 若不指定任何文件名称,或是所给予的文件名为 - ,则grep指令会从标准输入设备读取数据.
+ 示例：
  + `grep -i -r -w -n cudnn ./*` 
    + `-i,--ignore-case` : 忽略大小写
    + `-r,--recursive` :递归查找每一个文件夹下的文件 
    + `-w,--word-regexp` : 仅查找包含全部字符的行
    + `-n,--line-number` : 输入每个文件所匹配的字符在的行，以1为基准

## eval 

+ eval,命令用于重新运算求出参数的内容
+ eval可读取一连串的参数,然后再依参数本身的特性来执行
+ 在shell脚本中,用eval加命令来执行linux命令

## usermod 

+ usermod,命令用于修改用户账号的各项设定

## mount 

+ intr 参数:允许通知中断一个NFS调用.当服务器没有应答需要放弃的时候有用

## tar

+ 解压文件:`tar -zxf filename -C destination-path`
+ 压缩文件:`tar -zcf filename`


## ip配置

+ 临时更改:`sudo ifconfig ip-address netmask mask`, 例如:`sudo ifconfig 192.167.0.92 netmask 255.255.0.0`
+ 永久更改:修改`/etc/network/interface`文件

## export

+ export,命令用于设置或显示环境变量
+ 在shell中执行程序时,shell会提供一组环境变量.
+ export可新增,修改或删除环境变量,供后续执行的程序使用
+ export的效力仅限于该次登录操作
+ 语法:`export [-fnp] [变量名称] = [变量设置值]`
  + `-f`:代表变量名称中为函数名称
  + `-n`:删除指定的变量.变量实际上并未删除,只是不会输出到后续指令的执行环境中
  + `-p`:列出所有的shell赋予程序的环境变量

## awk  

+ AWK,是一种处理文本文件的语言,是一个强大的文本分析工具
+ 语法:`awk [选项参数] 'script' var=value file(s)` 或者 `awk [选项参数] -f scriptfile var=value file(s)`
+ 基本用法
  + `awk '{[pattern] action}' {filenames}` , 行匹配语句 `awk ''` 只能用单引号
  + `awk '{print $1, $4}' log.txt`, 每行按空格或TAB分割,输出文本的1,4项
  + `awk -F`, -F相当于内置变量FS,指定分割字符
  + `awk -v` ,设置变量
  + awk -f {awk脚本} {文件名}

## 特殊字符  

+ `$#`, 传递到脚本或函数的参数个数
+ `$*`, 以一个单字符串显示所有向脚本传递的参数
+ `$$`, 脚本运行的当前进程ID号
+ `$!`, 后台运行的最后一个进程的ID号
+ `$@`, 与`$*`相同,但是使用时加引号,并在引号中返回每个参数
+ `$-`, 显示Shell使用的当前选项,与set命令功能相同
+ `$?`, 显示最后命令的退出状态,0表示没有错误,其他任何值表明有错误

## sed  

+ sed, 利用脚本来处理文本文件，主要用来自动编辑一个或多个文件，简化对文件的反复操作，编写转换程序等
+ sed [-hnV] [-e<script>][-f<script文件>][文本文件]
+ 参数说明
  + `-e<script>` : 以选项中指定的script来处理输入的文本文件
  + `-f<script 文件>` ：以选项中指定的script文件来处理输入的文本文件
  + `-h` ： 显示帮助
  + `-n` ： 仅显示script处理后的结果
+ 动作说明
  + `a` ： 新增，a的后面可以接字符串，这些字符串会在新的一行出现（目前的下一行）
  + `c` ： 取代，c的后面可以接字符串，这些字符串可以取代n1, n2之间的行
  + `d` ： 删除，因为是删除，所以d后面通常不接任何东西
  + `i` ： 插入，i的后面可以接字符串，而这些字符串会出现在新的一行（目前的上一行）
  + `p` ： 打印，将某个选择的数据打印
  + `s` :  取代，可以直接进行取代的工作，通常搭配正则表达式

## whereis  

+ 检查二进制文件和库文件的位置
  + `whereis systemctl`

## supervisor  

+ supervisor, 是一个客户端/服务器系统,它允许用户监视和控制类UNIX操作系统上的许多进程,是linux下一个便利的启动和监控服务的命令
+ Supervisor, 是用Python开发的一个client/server服务,是Linux/Unix系统下的一个进程管理工具,不支持Windows系统.它可以很方便的监听,启动,停止,重启一个或多个进程
+ 用Supervisor管理的进程,当一个进程意外被杀死,supervisor监听到进程死后,会自动将它重新拉起,很方便的做到进程自动恢复的功能,不再需要自己写shell脚本来控制.
+ 因为Supervisor是Python开发的,安装前先检查一下系统是否安装了Python2.4以上的版本
+ supervisor包括两个命令:supervisord, supervisorctl,分别是后台的守护进程以及命令行管理命令.
+ supervisor安装完成后会生成是三个执行程序:`supervisortd`, `supervisorctl`, `echo_supervisord_conf`
  + `supervisortd`, 用于管理supervisor本身服务
  + `supervisorctl`, 用于管理需要委托给supervisor工具的服务
  + `echo_supervisord_conf`, 用于生成supervisor的配置文件
  + supervisor的守护进程服务(用于接受进程管理命令),客户端(用于和守护进程通信,发送管理进程的指令)
+ 两个命令共用一个配置文件,默认是:`/etc/supervisor/supervisor.conf`,而`supervisor.conf`通过include来引入其他配置文件,一般放在`/etc/supervisor/conf.d`目录下

## wc  

+ wc, 用于计算字数
+ 利用wc指令可以计算文件的Byte数,字数或是列数,若不指定文件名称,或是所给予的文件名为`-`,则wc指令会从标准输入设备读取数据
+ 语法:`wc [-clw] [--help] [--version] [文件...]`
+ 参数:
  + `-c`或`--bytes`或`--chars` 只显示Bytes数
  + `-w`或`--words` 只显示字数
  + `-l`或`--lines` 显示行数
  + `--help` 在线帮助
  + `--version` 显示版本信息
+ 使用wc统计:
  + `wc testfile  # testfile文件的统计信息`
  + `3 92 598 testfile # testfile文件的行数为3, 单词数为92, 字节数为598`
  + 其中三个数字分别表示testfile文件的行数,单词数,以及该文件的字节数
+ 如果想同时统计多个文件的信息,例如同时统计testfile,testfile_1,testfile_2,可使用:`wc testfile testfile_1 testfile_2  # 统计三个文件的信息`

## chown  

+ chown,(change owner)命令用于设置文件所有者和文件关联组的命令
+ chwon需要超级用户root的权限才能执行此命令，非超级用户如需要设置关联组可能需要使用`chgrp`命令
+ 参数
  + `user` : 新的文件拥有者的使用者ID
  + `group`: 新的文件拥有着的使用者组（group）
  + `-c`   : 显示更改的部分的信息
  + `-f`   : 忽略错误信息
  + `-h`   : 修复符号链接
  + `-v`   : 显示详细的处理信息
  + `-R`   : 处理指定目录以及其子目录下的所有文件
 
## which  

+ which,用于输入命令的路径(locate a command)

## file  

+ 使用file命令,查看某个文件的类型信息

## stat  

+ 也可以使用stat命令, 查看某个文件的类型信息

## realpath  

+ 获取指定文件或目录的绝对路径

## redshift  

+ 护眼软件

## diff  

+ diff, 用于比较文件的差异
+ diff以逐行的方式,比较文本文件的异同处.如果指定要比较目录,则diff会比较目录中相同文件名的文件,但是不会比较其中子目录
+ 递归比较两个文件夹之间的差异:`diff -r -q folder1 folder2`
  + `-r` : 递归的比较
  + `-q` : 只有在文件有差异的情况下报告
+ `diff`,常常与`grep`一起使用,筛选出想要的结果

## patch  

+ patch, 用于修补文件,用于不同文件打补丁.
+ patch,常与diff配合使用,diff可以用来分辨两个版本之间的差异,将旧的文件升级为新的文件时:先比较旧版本的差异,病将差异档制作成补丁文件,再由补丁文件更新旧文件

## expr  

+ expr, 是一个手工命令行计数器,用于在Unix/Linux下求表达式变量的值,一般用于整数值,也可用于字符串
+ 语法:`expr 表达式`
+ 表达式说明:
  + 用空格隔开每个项
  + 用反斜杠`\`放在shell特定的字符前面
  + 对包含空格和其他特殊字符的字符串要用引号括起来

## dstat  

+ `versatile tool for generating system resource statistics.(多功能系统资源统计生成工具)`
+ 检测界面各参数含义（部分）
  + Procs
    + `r` : 运行的和等待（CPU时间片）运行的进程，这个值也可以判断是否需要增加CPU
    + `b` : 处于不可中断状态的进程数，常见的情况是由IO引起的
  + Memory
    + `swpd` : 切换到交换内存上的内存（默认以KB为单位）。如果swpd的值不为0，
    + `free` : 空闲的物理内存
    + `buff` : 作为buffer cache的内存，对块设备的读写进行缓冲
    + `cache`: 作为page cache 的内存，文件系统的cache。
  + Swap
    + `si` : 交换内存使用，由磁盘调入内存
    + `so` : 交换内存使用，由内存调入磁盘
  + 磁盘IO
    + `bi` : 从块设备读入的数据总量（读磁盘）
    + `bo` : 写入到块设备的数据总量 (写磁盘)
  + System
    + `in` : 每秒产生的中断次数
    + `cs` : 每秒产生的上下文切换次数
  + Cpu
    + `usr` : 用户进程消耗的CPU时间百分比
    + `sys` : 内核进程消耗的CPU时间百分比
    + `wai` : IO等待消耗的CPU时间百分比
    + `wai` : CPU处在空间状态时间百分比


## tail  

+ tail, 用于查看文件的内容，有一个常用的参数`-r`常用于查阅正在改变的日志文件
+ `tail -f filename` 会把`filename`文件里的最尾部的内容显示在屏幕上，并且不断刷新，只要filename更新就可以看到最新的文件内容
+ 参数
  + `-f` : 循环读取
  + `-q` : 不显示处理信息
  + `-v` : 显示详细的处理信息
  + `-c <数目>` : 显示的字节数
  + `-n <行数>` : 显示文件的尾部n行内容

## curl  

+ 在Linux中curl是一个利用URL规则在命令行下工作的文件传输工具。支持文件的上传和下载，是综合传输工具，但是按照传统，习惯称curl为下载工具
+ 参数
  + `-f / --fail` : 连接失败时不显示http错误
  + `-s / --silent` : 静音模式，不输出任何东西
  + `-S / --show-error` : 当与`-s`一起使用时，如果`curl`失败，`curl`将显示一条错误消息
  + `-L / --location` : （HTTP/HTTPS）跟踪重定向。如果服务器报告请求页面已移动到另一个位置，此选项将使curl在新位置上重做请求

## ip  

+ `ip`命令与`ifconfig`命令类似,但是比`ifconfig`命令更加强大,主要功能是用于显示或者设置网络设备,`ip`命令是Linux加强版的网络配置工具,用于代替`ifconfig`命令
+ 语法:`ip [options] object { command | help}`
  + object为常用对象,值可以是:`{ link | addr | addrlabel | route | rule | neigh | ntable | tunnel | maddr | mroute | mrule | monitor | xfrm | token}`
  + 常用对象的取值含义:
    + `link`:网络设备
    + `address`:设备上的协议(IP或IPv6)地址
    + `addrlabel`:协议地址选择的标签设置
    + `route`:路由表条目
    + `rule`:路由策略数据库中的规则
  + options为常用选项,值可以是:`{-V[version] | -s[tatistics] | -d[details] | -r[resolve] | -h[human-readable] -iec | -f[family] {inet6 | ipx | dnet | link } | -o[oneline] | -t[timestamp] | -b[batch] [filename] | -rc[rcvbuf] [size]}`
  + 常用选项的取值含义:
    + `-V`:显示命令的版本信息;
    + `-s`:输出更详细的信息;
    + `-f`:强制使用指定的协议族
    + `-4`:指定使用的网络层协议是IPv4协议;
    + `-6`:指定使用的网络层协议是IPv6协议
    + `-r`:显示主机时,不使用IP地址,而使用主机的域名
+ 示例:
  + `ip link show  # 显示网络接口信息`
  + `ip link set eth0 up  # 开启网卡`
  + `ip link set eth0 down # 关闭网卡`
  + `ip link set eth0 promisc on # 开启网卡的混合模式`
  + `ip link set eth0 promisc offi  # 关闭网卡的混合模式`
  + `ip link set eth0 txqueuelen 1200  # 设置网卡队列长度`
  + `ip link set eth0 mtu 1400  # 设置网卡最大传输单元`
  + `ip addr show  # 显示网卡IP信息`
  + `ip addr add 192.168.0.1/24 dev eth0  # 设置eth0网卡IP地址192.168.0.1`
  + `ip addr del 192.168.0.1/24 dev eth0  # 删除eth0网卡IP地址`
  + `ip route show  # 显示系统路由`
  + `ip route add default via 192.168.1.254  # 设置系统默认路由`
  + `ip route list  # 查看路由信息`
  + `ip route add 192.168.4.0/24 via 192.168.0.254 dev eth0  # 设置192.168.4.0网段的网关为192.168.0.254,数据走eth0接口`
  + `ip route add default via 192.168.0.254 dev eth0  # 设置默认网关为192.168.0.254`
  + `ip route del 192.168.4.0/24  # 删除192.168.4.0网段的网关`
  + `ip route delete 192.168.1.0/24 dev eth0  # 删除路由`

## xdg-user-dirs-upate  

+ 该命令会读取配置文件`/etc/xdg/user-dirs.defaults`,并在`$HOME`下创建一整套默认的经本地化的用户目录

## 压缩与解压  

+ 将文件压缩不只是为了节省硬盘空间,同时也可以节省网络传输时间,归档文件方便管理等
+ 压缩可分为无损压缩与有损压缩两种,但不管是采用何种技术模型,其本质内容都是一样的,即** 通过某种特殊的编码方式将数据信息中存在的重复度,冗余度有效地降低,从而达到数据压缩的目的** 
+ 在Linux中很多压缩程序只能针对一个文件进行压缩,当要压缩一大堆文件时,首先得先将一堆文件打成一个包(tar命令),然后再用压缩程序进行压缩(gzip, bzip2命令),就是说压缩会分为两步:先打包再压缩
+ 打包,tar命令可以将多个文件和目录创建一个档案(归档),tar最初是用来在磁带上创建档案;tar命令也可以修改档案中的文件,或者加入新的文件;使用tar程序打出来的包常称为tar包,tar包通常以`.tar`结尾
+ 归档的一般用途:
  + 把一大堆的文件和目录打包成一个tar包,便于网络传输
  + 生成tar包后,再用其他的程序进行压缩
+ 压缩
  + gzip,是GNUzip的缩写,它是一个GNU自由软件的文件压缩程序,文件经过它压缩以后以`.gz`为扩展名.
  + gzip不能用来压缩目录,需要先归档目录,然后再压缩,gzip和tar一起构成了Linux操作系统中流行的文件压缩格式(`.tar.gz`)

## 一切皆文件 

+ "一切皆文件"是Unix/Linux的基本哲学之一,它是指Linux系统中的所有的一切都可以通过文件的方式访问和管理,即使不是文件,也以文件的形式来管理.例如硬件设备,进程,套接字等都抽象成文件,使用统一的用户接口,虽然文件类型各不相同,但是对其提供的却是同一套操作
+ 这里的一切都是单项的,也即所有的东西都单向通过文件系统呈现,反向不一定可行.例如:通过新建文件的方式来创建磁盘设备是行不通的
+ 在Linux中共有7种类型的文件,分为3大类:
  + `-` : 普通文件,包括文本文件和二进制文件
  + `d` : 目录文件(文件夹文件)
  + 特殊文件
    + `l` : 链接文件
    + `c` : 字符设备文件
    + `s` : 套接字(Socket)文件,用于网络通讯,一般由应用程序创建
    + `p` : 命名管道文件
    + `b` : 块文件

## inode索引节点 

+ `inode` 是理解`Unix/Linux`文件系统和硬盘存储的基础
+ 理解`inode`,不仅有助于提高系统操作水平,还有助于体会Unix设计哲学,即如何把底层的复杂性抽象成一个简单概念,从而大大简化用户接口

+ `inode`是什么?
  - 理解`inode`,要从文件存储说起 -- 文件储存在硬盘上,硬盘的最小存储单位叫做**扇区(`Sector`)** ,每个扇区储存`512`字节(相当于`0.5KB`)
  - 操作系统读取硬盘的时候,不会一个扇区一个扇区地读取,这样效率太低.而是**一次性连续读取多个扇区,即一次性读取一个块(`block`)**,这种由多个扇区组成的**块** ,是文件存取的最小单位.**块** 的大小通常是`4KB`,即连续八个扇区(`sector`)组成一个块(`block`)
  - 文件数据都存储在块中,那么还需要一个地方储存文件的**元信息** ,比如文件的创建者,文件的创建日期,文件的大小等.**这种储存文件元信息的区域就叫做`inode`** ,中文译名为**索引节点** 
  - 每一个文件都有对应的inode,里面包含了与该文件有关的信息
  
+ `inode`的内容:
  - `inode`包含文件的元信息,具体来说有:
    + 文件的字节数
    + 文件拥有者的`User ID`
    + 文件用户组的`Group ID`
    + 文件的读,写,执行权限
    + 文件的时间戳,共有三个
      + `ctime`,指inode上一次变动的时间
      + `mtime`,指文件内容上一次变动的时间
      + `atime`,指文件上一次打开的时间
    + 链接数,即有多少文件名指向这个`inode`
    + 文件数据`block`的位置
  - 可以使用`stat`命令,查看某个文件的inode信息

+ `inode`的大小
  - `inode`也会消耗硬盘空间,所以在格式化硬盘的时候,操作系统自动将硬盘分成两个区域,一个是数据区,存放文件数据;另一个是`inode`区(`inode table`),存放`inode`所包含的信息
  - `inode`节点一般占用`128`字节或`256`字节.`inode`节点的总数,在格式化时会自动设定.一般是每`1KB`或每`2KB`就设置一个`inode`
+ inode号码
  - 每个`inode`都有一个号码,操作系统用`inode`号码来识别不同的文件.
  - **`Unix/Linux`系统内部不使用文件名,而是使用`inode`号码来识别文件**.对于系统来说,文件名只是inode号码便于识别的别称或者绰号.
  - 表面上,用户通过文件名打开文件.实际上,系统内部将这个过程分为三步:
    + 系统找到文件名对应的`inode`号码
    + 通过`inode`号码,获取`inode`信息
    + 根据`inode`信息,找到文件数据所在的`block`,读出数据
  - 通过命令`ls -i filename`查看文件名对应的inode号码
  
+ 目录文件
  - `Unix/Linux`系统中,目录(`directory`)也是一种文件.打开目录,实际上就是打开目录文件
  - 目录文件的结构非常简单,就是一系列目录项(`dirent`)的列表.每个目录项由两个部分组成:所包含文件的文件名,以及该文件名对应的`inode`号码
  - **所以在使用`ls -lh`命令查看文件夹大小时,所有的文件夹只有`4KB`大小**
+ `inode`的特殊作用
  - 由于`inode`号码与文件名分离,这种机制导致了一些`Unix/Linux`系统特有的现象
  - 当文件名包含特殊字符,无法正常删除时,可以删除`inode`节点,就能直接删除文件
  - 移动文件或重命名文件,只是改变文件名,不影响`inode`号码,所以在`Linux`中移动文件不论大小基本秒成
  - 打开一个文件后,系统就以`inode`号码来识别文件,不再考虑文件名.因此,系统无法从`inode`号码得知文件名.

## 硬链接和软链接 

+ 在Linux中有两种link(链接)的概念,一般称之为硬链接和软链接(或符号链接)
+ 硬链接
  + 一般情况下,文件名和inode号码是"一一对应"的关系,每个inode号码对应一个文件名(每个文件默认有一个硬链接).但是Unix/Linux系统允许多个文件名指向同一个inode号码
  + 这意味着,可以用不同的文件名访问同样的内容,对文件内容进行修改后,会影响所有文件名.但是,删除一个文件名,不影响另一个文件名的访问,这种情况就被称为"硬链接(hard link)"
  + 创建一个硬链接,就会为文件创建了一个新的文件名.硬链接有两个重要局限性:
    + 硬链接不能链接不在同一系统的文件,也就是说硬链接不能链接与文件不在同一磁盘分区上的文件;
    + 硬链接不能链接目录
  + 一个硬链接和文件本身没有什么区别.当列出一个包含硬链接的文件时,不会有特殊的链接指示说明.当一个硬链接被删除时,文件本身的内容仍然存在(也就是说,它所占用的磁盘空间不会被重新分配),直到所有关联这个文件的硬链接都删掉.
+ 软链接:
  + 创建软链接是为了克服硬链接的局限性
  + 软链接是通过创建一个特殊类型的文件(指针)链接到文件或目录,就像windows的快捷方式
  + 文件A和文件B的inode号码虽然不一样,但是文件A的内容是文件B的路径.读取文件A时,系统会自动将访问指向文件B.因此,无论打开哪一个文件,最终读取的都是文件B,但是,文件A依赖于文件B而存在,如果删除了文件B,打开文件A就会报错:"No such file or directory"
  + 软链接与硬链接最大的不同:文件A指向文件B的文件名,而不是文件B的inode号码

## 安全模型与权限 

+ 在linux系统中,所有的操作实质上都是在进行进程访问文件的操作.在访问文件之前需要取得相应的权限,而权限是通过Linux系统中的安全模型获得的.理论上进程所拥有的权限与执行它的用户的权限相同.其中涉及的一切内容,都是围绕这个核心进行的.
+ Linux系统中的安全模型,有两种类型:
  + Linux系统上最初的安全模型称为** 自主访问控制(DAC, Discretionary Access Control)** 
  + 后来又增加设计了一个新的安全模型叫** 强制访问控制(MAC, Mandatory Access Control)** 
  + MAC和DAC不是互斥的,DAC是最基本的安全模型,也是最常用的访问控制机制,是Linux必须具有的功能;而MAC是构建在DAC智商的加强安全机制,属于可选模块
+ 文件权限控制
  + 对文件的权限分三组进行控制:
    + `user`对文件属主设定的权限
    + `group`对文件属组设定的权限
    + `othre`对其他者设定的权限
  + 常用的可设定的权限值,包括:
    + `r` : 读权限
    + `w` : 写权限
    + `x` : 执行权限
    + `s` : 强制位权限
    + `t` : 粘滞位权限
    + `i` : 不可修改权限
    + `a` : 只追加权限

## 端口 

+ `netstat  -a  # 列出所有端口`
+ `netstat -at  # 列出所有tcp端口`
+ `netstat -au  # 列出所有udp端口`
+ `netstat -l   # 只显示监听端口`
+ `netstat -lt  # 只列出所有监听tcp端口`
+ `netstat -lu  # 只列出所有监听udp端口`

### 查看指定端口

+ `sudo netstat -tln | grep 8083`
+ `sudo lsof -i:8083`

## 终端,控制台和shell的区别 

+ 终端(terminal)
+ 控制台(console)
  + 控制台是计算机的基本设备,而终端是附加设备
+ Shell俗称壳(用来区别于核)
  + 软件shell,俗称壳,是读取并解释命令的程序.
  + Shell是一个用C语言编写的程序,它是用户使用Linux的桥梁,用户通过Shell访问操作系统内核的服务

## 启动服务 

+ 启动`mysql`
  + 使用`service`启动: `service mysql start`

## Linux系统启动过程 

+ Linux系统的启动过程可以分为五个阶段:
  + 内核的引导
    + 当计算机打开电源后,首先是`BIOS`开机自检,按照`BIOS`中设置的启动设备(通常是硬盘)来启动.
    + 操作系统接管硬件以后,首先读入`/boot`目录下的内核文件
  + 运行init
    + (init程序的类型)
      + SysV:init
      + Upstart:init
      + Systemd:systemd
    + `init`进程是系统所有进程的起点,可以把它比作系统所有进程的老祖宗,没有这个进程,系统中任何进程都不会启动.
  + 系统初始化
  + 建立终端
  + 用户登录系统