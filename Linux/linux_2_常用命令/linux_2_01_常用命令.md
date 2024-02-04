
## stty 查询中断按键

+ 不同的终端类型、Shell版本其中断的按键是不同的，甚至还可以自定义，这可通过stty命令查询：`sitty -a`
+ 注意：`^`是Ctrl的缩写

## 终端初始化脚本

+ 参考：
  + `https://www.cnblogs.com/yoyo-sincerely/p/5931245.html`

## 显示路径问题

+ `\w`  --  当前工作目录，例如`/home/user`
+ `\W`  --  当前工作目录的基名(basename)，例如`user`

+ 解决问题：终端显示路径太长，不易于阅读
+ 解决方法：将`.bashrc`中的`\w`更换为`\W`

## MD5校验

+ Windows下生成md5校验码: `certutil -hashfile filename MD5`
+ Linux下生成md5校验码:   `md5sum filename`


## 文件名通配符

+ `×`：与0个或多个任意的字符相匹配
+ `？`：只与单个任意的字符匹配，可以使用多个问号
+ `[]`：与`？`相似，只与一个字符匹配。区别在于：问号与任意一个字符匹配，而方括号只与方括号中列出的字符之一匹配。短横线（`-`）代表一个范围内的字符。注：只能是升序

## sudo  

+ sudo, superuser do

在Linux中，`sudo`是一种命令行工具，用于以超级用户（也称为root用户）的权限执行其他命令。它允许普通用户在需要执行特权操作时临时获得root权限，从而执行需要管理员权限的任务，而无需切换到root用户。

以下是`sudo`命令的一般语法：

```
sudo [options] command [arguments]
```

其中，`options`是可选的一些选项，`command`是要以root权限执行的命令，`arguments`是传递给命令的参数。

以下是一些常见的`sudo`命令选项和用法：

1. 以root权限执行命令：
   ```
   sudo command
   ```

   此命令将以root权限执行`command`命令。

2. 切换到root用户：
   ```
   sudo -i
   ```

   此命令将打开一个新的shell会话，并切换到root用户身份。

3. 以其他用户身份执行命令：
   ```
   sudo -u username command
   ```

   此命令将以指定用户（`username`）的权限执行`command`命令。

4. 查看sudo命令的使用情况：
   ```
   sudo -h
   ```

   此命令将显示`sudo`命令的帮助信息，包括选项和用法。

5. 列出当前用户的sudo权限：
   ```
   sudo -l
   ```

   此命令将列出当前用户可以使用`sudo`执行的命令列表。

通过使用`sudo`命令，系统管理员可以授予特定的权限给普通用户，使其能够执行有限的特权操作，同时避免了在整个会话中使用root权限的风险。这提供了更好的系统安全性和管理员对系统的更细粒度控制。

需要注意的是，只有在`/etc/sudoers`文件中明确配置了用户的sudo权限，用户才能使用`sudo`命令。只有具备sudo权限的用户才能成功执行以root权限执行的命令。

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



## which  

+ which,用于输入命令的路径(locate a command)

在Linux中，`which`命令用于定位可执行程序的路径。它用于确定给定命令的可执行文件的位置。

以下是`which`命令的一般语法：

```
which [options] command
```

其中，`options`是可选的一些选项，`command`是要查找的命令。

以下是一些常见的`which`命令选项和用法：

1. 查找命令的路径：
   ```
   which ls
   ```

   此命令将显示`ls`命令的可执行文件路径。

2. 查找多个命令的路径：
   ```
   which ls grep
   ```

   此命令将显示`ls`和`grep`命令的可执行文件路径。

`which`命令会搜索系统的`PATH`环境变量中列出的目录，以确定给定命令的可执行文件位置。它返回找到的第一个匹配的可执行文件路径。

请注意，`which`命令只能查找可执行程序的路径，无法查找其他类型的文件（如脚本文件或配置文件）的路径。

`which`命令在确定命令是否存在以及确定特定命令的完整路径时非常有用。它对于解决命令不存在或多个版本的命令存在时很有帮助。

## file  

<!-- + 使用file命令,查看某个文件的类型信息 -->

+ 简介：
  + file 命令是一个在 Linux 系统中用于确定文件类型的实用工具。它通过检查文件内容和一些特征来确定文件的类型，而不仅仅依赖于文件扩展名

+ 语法：
```bash
file [选项] 文件名
```

+ 选项：
  + -b 或 --brief：以简洁模式输出，只显示文件类型
  + -i 或 --mime：显示文件的 MIME 类型
  + -m <魔术文件> 或 --magic-file=<魔术文件>：指定自定义的魔术文件来识别文件类型
  + -z 或 --uncompress：对于压缩文件，显示原始文件类型

## stat  

+ 也可以使用stat命令, 查看某个文件的类型信息

在Linux中，`stat`命令用于显示文件或文件系统的详细信息。它提供了一种查看文件或目录的各种属性的方法，如文件大小、权限、最后访问时间、最后修改时间等。

以下是`stat`命令的一般语法：

```
stat [options] file(s)
```

其中，`options`是可选的一些选项，`file(s)`是要显示信息的文件或目录列表。

以下是一些常见的`stat`命令选项和用法：

1. 显示文件详细信息：
   ```
   stat file.txt
   ```

   此命令将显示`file.txt`文件的详细信息，包括文件大小、所属用户和组、权限等。

2. 显示文件的最后访问时间：
   ```
   stat -c %x file.txt
   ```

   此命令将仅显示`file.txt`文件的最后访问时间。

3. 显示文件的修改时间：
   ```
   stat -c %y file.txt
   ```

   此命令将仅显示`file.txt`文件的修改时间。

`stat`命令还支持其他一些选项，如自定义输出格式、显示文件系统信息等。

请注意，`stat`命令对于查看文件或目录的详细属性非常有用，特别是在需要获取文件元数据和状态信息时。它提供了比`ls`命令更详细和精确的信息。

## stat 详解

`stat` 命令用于获取文件或文件系统的详细信息，包括文件大小、权限、最后访问时间、最后修改时间等。下面是 `stat` 命令的常用选项的详细解释：

- `-c` 或 `--format=`：指定输出格式。可以使用 `%` 开头的占位符来表示不同的属性。例如 `%n` 表示文件名，`%s` 表示文件大小，`%a` 表示访问权限等。

- `-f`：以文件系统的方式显示信息，而不是文件的方式。

- `-t`：以简短的格式显示时间。

- `-L` 或 `--dereference`：对于符号链接文件，显示链接指向的文件的信息，而不是链接文件本身的信息。

- `-c` 或 `--changes`：仅显示发生更改的文件信息。

- `-r` 或 `--format=FORMAT`：指定自定义输出格式。可以使用 `--printf` 选项后跟一个格式字符串来指定输出的具体格式。

- `-s` 或 `--file-system`：显示文件系统的信息而不是文件的信息。

- `-x` 或 `--debug`：显示调试信息。

- `-h` 或 `--help`：显示帮助信息。

这些选项可以根据具体的使用需求进行组合和调整，以获取所需的文件或文件系统的信息。

例如，使用以下命令获取文件 `example.txt` 的详细信息：

```shell
$ stat example.txt
```

输出结果可能类似于：

```
  File: example.txt
  Size: 1024          Blocks: 8          IO Block: 4096   regular file
Device: 801h/2049d    Inode: 31474816    Links: 1
Access: (0644/-rw-r--r--)  Uid: ( 1000/   user)   Gid: ( 1000/   group)
Access: 2023-07-04 10:15:32.555555555 +0000
Modify: 2023-07-03 15:45:21.123456789 +0000
Change: 2023-07-03 15:45:21.123456789 +0000
 Birth: 2023-07-02 09:30:00.987654321 +0000
```

这个输出提供了文件的名称、大小、权限、所有者、创建时间、访问时间和修改时间等信息。

请注意，`stat` 命令的输出格式和选项可能会根据不同的操作系统和文件系统有所不同。可以通过 `man stat` 命令来查看详细的文档和选项说明。

---

## realpath  

+ 获取指定文件或目录的绝对路径

在Linux中，`realpath`命令用于获取给定路径的绝对路径。它会解析所有符号链接，并返回路径的规范化版本，消除任何冗余或相对路径。

以下是`realpath`命令的一般语法：

```
realpath [options] file(s)
```

其中，`options`是可选的一些选项，`file(s)`是要获取绝对路径的文件或目录列表。

以下是一些常见的`realpath`命令选项和用法：

1. 获取文件的绝对路径：
   ```
   realpath file.txt
   ```

   此命令将返回`file.txt`文件的绝对路径。

2. 获取目录的绝对路径：
   ```
   realpath /usr/local/bin
   ```

   此命令将返回`/usr/local/bin`目录的绝对路径。

`realpath`命令可以用于解析路径中的符号链接并返回规范化的绝对路径。它对于需要获取路径的确切位置和处理文件路径的任务非常有用。

请注意，`realpath`命令需要指定的路径存在才能返回绝对路径。如果路径不存在或无法访问，它会产生错误。

## redshift  

在Linux中，`redshift`是一种用于调整屏幕颜色温度的命令行工具。它可以通过减少屏幕的蓝光成分来减轻视觉疲劳，并在晚上或低光环境下提供更舒适的视觉体验。

下面是`redshift`命令的一些常见选项和用法：

1. 基本用法：
   - 启动`redshift`：`redshift`
   - 停止`redshift`：`redshift -x`

2. 调整颜色温度：
   - 使用`-t`选项指定颜色温度（单位为开尔文）：`redshift -t 4000`
   - 使用`-b`选项指定颜色温度并降低亮度：`redshift -b 0.8 -t 4000`

3. 调整定位信息：
   - 使用`-l`选项指定纬度和经度以计算日出和日落时间：`redshift -l LAT:LON`
   - 例如：`redshift -l 37.8:-122.4`（设定位置为旧金山）

4. 调整亮度：
   - 使用`-m`选项启用亮度调整模式：`redshift -m METHOD`
   - 方法包括`randr`（默认值）和`vidmode`

5. 调整亮度变化速度：
   - 使用`-r`选项指定亮度变化速度（单位为小时）：`redshift -r SPEED`

6. 自定义配置文件：
   - 使用`-c`选项指定自定义配置文件的路径：`redshift -c /path/to/config`

7. 显示调试信息：
   - 使用`-v`选项显示详细的调试信息：`redshift -v`

以上是一些常见的`redshift`命令选项和用法示例。请注意，`redshift`命令需要正确配置和运行，以便根据位置和时间自动调整屏幕颜色温度。您可以根据自己的需求和喜好来调整命令的参数，以达到最佳的视觉效果。

## diff  

+ diff, 用于比较文件的差异
+ diff以逐行的方式,比较文本文件的异同处.如果指定要比较目录,则diff会比较目录中相同文件名的文件,但是不会比较其中子目录
+ 递归比较两个文件夹之间的差异:`diff -r -q folder1 folder2`
  + `-r` : 递归的比较
  + `-q` : 只有在文件有差异的情况下报告
+ `diff`,常常与`grep`一起使用,筛选出想要的结果

在Linux中，`diff`命令用于比较两个文件的内容并显示它们之间的差异。它可以用于比较文本文件、目录以及其他类型的文件。

以下是`diff`命令的一般语法：

```
diff [options] file1 file2
```

其中，`options`是可选的一些选项，`file1`和`file2`是要比较的两个文件。

以下是一些常见的`diff`命令选项和用法：

1. 比较文本文件的差异：
   ```
   diff file1.txt file2.txt
   ```

   此命令将比较`file1.txt`和`file2.txt`两个文本文件的内容，并显示它们之间的差异。

2. 递归比较目录的差异：
   ```
   diff -r dir1 dir2
   ```

   此命令将递归比较`dir1`和`dir2`两个目录及其子目录中的文件，并显示它们之间的差异。

3. 生成可应用的补丁文件：
   ```
   diff -u file1.txt file2.txt > patch.diff
   ```

   此命令将比较`file1.txt`和`file2.txt`两个文件的内容，并生成一个可应用的补丁文件`patch.diff`，以便在其他系统上应用差异。

`diff`命令提供了多种选项，用于控制输出格式、忽略空格或空行、显示上下文等。

`diff`命令在版本控制系统和文件比较方面非常有用，可以帮助您查找文件之间的更改和差异。

## patch  

+ patch, 用于修补文件,用于不同文件打补丁.
+ patch,常与diff配合使用,diff可以用来分辨两个版本之间的差异,将旧的文件升级为新的文件时:先比较旧版本的差异,病将差异档制作成补丁文件,再由补丁文件更新旧文件

在Linux中，`patch`命令用于应用补丁文件到源文件，实现对源文件的修改或更新。补丁文件通常是通过`diff`命令生成的，其中包含了对源文件所做的更改。

以下是`patch`命令的一般语法：

```
patch [options] [originalfile [patchfile]]
```

其中，`options`是可选的一些选项，`originalfile`是要应用补丁的源文件，`patchfile`是补丁文件。

以下是一些常见的`patch`命令选项和用法：

1. 应用补丁到源文件：
   ```
   patch source.c patchfile.patch
   ```

   此命令将补丁文件`patchfile.patch`应用到源文件`source.c`，并进行相应的修改。

2. 从标准输入中读取补丁内容：
   ```
   patch -i patchfile.patch
   ```

   此命令将从标准输入中读取补丁文件内容，并将其应用到当前目录下的相应文件。

3. 显示补丁过程但不实际应用补丁：
   ```
   patch -p1 --dry-run -i patchfile.patch
   ```

   此命令将显示应用补丁的过程，但不会实际修改文件。这对于预览补丁的影响非常有用。

`patch`命令还支持其他选项，如备份原始文件、忽略空白行、处理多个补丁等。

使用`patch`命令可以方便地将补丁应用到源文件中，以更新或修复代码。它在软件开发、版本管理和打补丁等方面非常有用。

## expr  

+ expr, 是一个手工命令行计数器,用于在Unix/Linux下求表达式变量的值,一般用于整数值,也可用于字符串
+ 语法:`expr 表达式`
+ 表达式说明:
  + 用空格隔开每个项
  + 用反斜杠`\`放在shell特定的字符前面
  + 对包含空格和其他特殊字符的字符串要用引号括起来

在Linux中，`expr`命令用于执行基本的数学运算和字符串操作。它可以计算表达式的值并输出结果。

以下是`expr`命令的一般语法：

```
expr expression
```

其中，`expression`是要计算的表达式。

以下是`expr`命令常见的用法示例：

1. 计算两个数的和：
   ```
   expr 10 + 5
   ```

   此命令将计算10和5的和，并输出结果15。

2. 执行字符串连接：
   ```
   expr "Hello" : "He" "llo"
   ```

   此命令将字符串"Hello"的前缀"He"与后缀"llo"连接起来，并输出结果"Hello"。

3. 比较两个数的大小：
   ```
   expr 10 ">" 5
   ```

   此命令将比较10和5的大小，如果10大于5，则输出结果1；否则输出结果0。

`expr`命令还支持其他一些运算符和操作，如减法、乘法、除法、求余等。它还可以用于处理字符串长度、子字符串提取、正则表达式匹配等操作。

请注意，`expr`命令的参数和操作符之间需要使用空格进行分隔。如果表达式中包含特殊字符，需要使用引号或转义字符进行处理。

`expr`命令在Shell脚本和命令行环境中执行简单的数学计算和字符串操作时非常有用。

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

在Linux中，`dstat`命令用于实时监视系统资源的使用情况。它提供了对CPU、内存、磁盘、网络等资源的详细统计信息，并以交互式方式显示结果。

以下是`dstat`命令的一般语法：

```
dstat [options]
```

其中，`options`是可选的一些选项，用于指定要显示的资源和其他配置。

以下是一些常见的`dstat`命令选项和用法：

1. 显示默认的系统资源统计信息：
   ```
   dstat
   ```

   此命令将以默认配置显示实时的CPU、内存、磁盘和网络统计信息。

2. 指定要显示的资源：
   ```
   dstat -c -m -d
   ```

   此命令将只显示CPU使用情况、内存使用情况和磁盘活动的统计信息。

3. 指定刷新间隔：
   ```
   dstat -r 5
   ```

   此命令将每隔5秒刷新一次统计信息。

`dstat`命令还支持其他一些选项，如指定输出格式、显示进程统计信息、监视网络连接等。

使用`dstat`命令可以方便地监视系统资源的使用情况，帮助识别性能瓶颈和优化系统配置。它特别适用于在终端环境中实时查看系统的运行状态。

## tail  

+ tail, 用于查看文件的内容，有一个常用的参数`-r`常用于查阅正在改变的日志文件
+ `tail -f filename` 会把`filename`文件里的最尾部的内容显示在屏幕上，并且不断刷新，只要filename更新就可以看到最新的文件内容
+ 参数
  + `-f` : 循环读取
  + `-q` : 不显示处理信息
  + `-v` : 显示详细的处理信息
  + `-c <数目>` : 显示的字节数
  + `-n <行数>` : 显示文件的尾部n行内容

在Linux中，`tail`命令用于查看文件的末尾内容。它默认显示文件的最后10行，但也可以根据需要显示更多或更少的行数。

以下是`tail`命令的一般语法：

```
tail [options] file
```

其中，`options`是可选的一些选项，`file`是要查看的文件。

以下是一些常见的`tail`命令选项和用法：

1. 查看文件的最后10行：
   ```
   tail file.txt
   ```

   此命令将显示`file.txt`文件的最后10行内容。

2. 查看文件的指定行数：
   ```
   tail -n 20 file.txt
   ```

   此命令将显示`file.txt`文件的最后20行内容。

3. 实时监视文件的新增内容：
   ```
   tail -f file.txt
   ```

   此命令将持续显示`file.txt`文件的末尾内容，并随着文件的更新实时显示新增内容。

`tail`命令还支持其他选项，如显示文件的字节数、显示文件尾部的特定字节数、处理多个文件等。

`tail`命令在日志文件查看、实时监控文件变化等场景下非常有用。它可以帮助您快速定位文件的末尾内容，查找关键信息或进行实时追踪。

## curl  

+ 在Linux中curl是一个利用URL规则在命令行下工作的文件传输工具。支持文件的上传和下载，是综合传输工具，但是按照传统，习惯称curl为下载工具
+ 参数
  + `-f / --fail` : 连接失败时不显示http错误
  + `-s / --silent` : 静音模式，不输出任何东西
  + `-S / --show-error` : 当与`-s`一起使用时，如果`curl`失败，`curl`将显示一条错误消息
  + `-L / --location` : （HTTP/HTTPS）跟踪重定向。如果服务器报告请求页面已移动到另一个位置，此选项将使curl在新位置上重做请求

在Linux中，`curl`命令是一个功能强大的网络工具，用于与服务器进行数据交互。它支持多种协议，包括HTTP、HTTPS、FTP、SMTP等，并可以执行各种操作，如下载文件、发送请求、上传文件等。

以下是`curl`命令的一般语法：

```
curl [options] [URL]
```

其中，`options`是可选的一些选项，用于配置`curl`的行为，`URL`是要访问的目标地址。

以下是一些常见的`curl`命令选项和用法：

1. 发送HTTP GET请求并输出响应内容：
   ```
   curl http://example.com
   ```

   此命令将向`http://example.com`发送HTTP GET请求，并将响应内容输出到终端。

2. 下载文件到本地：
   ```
   curl -O http://example.com/file.txt
   ```

   此命令将从`http://example.com/file.txt`下载文件，并保存到当前目录下的`file.txt`文件。

3. 发送POST请求并传递参数：
   ```
   curl -d "param1=value1&param2=value2" -X POST http://example.com/api
   ```

   此命令将向`http://example.com/api`发送HTTP POST请求，并将参数`param1=value1&param2=value2`作为请求体发送。

`curl`命令还支持其他许多选项，如设置请求头、设置超时时间、处理重定向等。

使用`curl`命令可以方便地进行各种网络操作，如获取API数据、下载文件、测试网络连接等。它是一种非常强大和灵活的工具，广泛应用于开发、调试和自动化脚本等场景。

---

## curl --data-binary

`curl` 是一个命令行工具，用于进行 HTTP 请求。`--data-binary` 选项用于在 HTTP POST 请求中发送二进制数据作为请求体。以下是对该选项的详细解释：

当你在 `curl` 中使用 `--data-binary` 选项时，你需要提供要发送的数据作为请求体。这些数据可以是二进制数据，即可以包含非文本字符或不适合解释为纯文本的格式。例如，它可以是图像文件、视频文件或任何其他类型的二进制数据。

`--data-binary` 选项期望你在命令行上直接指定数据，通常需要使用引号将其括起来，以保留任何特殊字符或格式。以下是一个示例：

```shell
curl --data-binary "@文件名" URL
```

在上面的示例中，`@文件名` 表示包含要发送的二进制数据的文件路径。`@` 符号告诉 `curl` 读取文件的内容并将其用作请求体。

另外，你也可以直接在命令行上内联指定二进制数据，而无需使用文件：

```shell
curl --data-binary "二进制数据" URL
```

在上面的示例中，`"二进制数据"` 表示你要发送的实际二进制数据。如果需要，确保正确编码数据，特别是如果数据包含可能被命令行解释器解释为特殊字符的字符。

当 `curl` 使用 `--data-binary` 选项发送 HTTP 请求时，默认情况下会将 `Content-Type` 头设置为 `application/octet-stream`。这向服务器表明请求体包含未知或未指定类型的二进制数据。如果需要指定其他内容类型，可以使用 `--header` 选项设置适当的头部。

值得注意的是，`--data-binary` 与 `curl` 中的 `--data` 选项是不同的。`--data` 选项用于将数据作为请求体发送，但它将数据视为纯文本，进行字符编码和特殊字符解释。相比之下，`--data-binary` 保留了数据的二进制特性，没有进行任何修改。

请记得将 "文件名" 替换为实际的文件路径，或将 "二进制数据" 替换为要发送的二进制数据，并将 "URL" 替换为要发送请求的服务器的 URL。

---

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

在Linux中，`ip`命令是一个强大的网络工具，用于管理网络接口、路由表、地址配置等网络相关的操作。它取代了过时的`ifconfig`命令，并提供更多功能和灵活性。

以下是`ip`命令的一般语法：

```
ip [options] object command
```

其中，`options`是可选的一些选项，用于配置`ip`命令的行为，`object`表示要操作的网络对象（如接口、路由表、地址等），`command`表示要执行的具体命令。

以下是一些常见的`ip`命令选项和用法：

1. 查看网络接口信息：
   ```
   ip link show
   ```

   此命令将显示系统上所有网络接口的详细信息，包括名称、状态、MAC地址等。

2. 查看路由表信息：
   ```
   ip route show
   ```

   此命令将显示系统的路由表信息，包括目标网络、下一跳地址、接口等。

3. 配置网络接口IP地址：
   ```
   ip address add 192.168.1.10/24 dev eth0
   ```

   此命令将为`eth0`接口添加IP地址`192.168.1.10/24`。

4. 启用或禁用网络接口：
   ```
   ip link set eth0 up
   ip link set eth0 down
   ```

   第一个命令将启用`eth0`接口，使其可用；第二个命令将禁用`eth0`接口，使其不可用。

`ip`命令还支持其他许多选项和功能，如配置VLAN、设定路由、设置策略路由等。

使用`ip`命令可以方便地管理和配置网络相关的操作，从而实现网络接口、路由表和地址的管理和调整。它是Linux系统中网络管理的主要工具之一。

## xdg-user-dirs-upate  

+ 该命令会读取配置文件`/etc/xdg/user-dirs.defaults`,并在`$HOME`下创建一整套默认的经本地化的用户目录

`xdg-user-dirs-update`命令是一个用于更新用户目录的工具，它在Linux系统中用于管理用户的标准目录，例如桌面、下载、文档、音乐、图片等目录。

在Linux系统中，用户目录的路径通常存储在`~/.config/user-dirs.dirs`文件中。`xdg-user-dirs-update`命令用于根据配置文件中定义的规则，更新用户目录的路径和名称。

以下是`xdg-user-dirs-update`命令的一般语法：

```
xdg-user-dirs-update
```

运行`xdg-user-dirs-update`命令将读取`~/.config/user-dirs.dirs`文件中的配置信息，并根据配置更新用户目录的路径和名称。

`~/.config/user-dirs.dirs`文件的示例内容如下：

```
XDG_DESKTOP_DIR="$HOME/Desktop"
XDG_DOWNLOAD_DIR="$HOME/Downloads"
XDG_DOCUMENTS_DIR="$HOME/Documents"
XDG_MUSIC_DIR="$HOME/Music"
XDG_PICTURES_DIR="$HOME/Pictures"
XDG_VIDEOS_DIR="$HOME/Videos"
```

上述配置定义了标准的用户目录路径，如桌面、下载、文档、音乐、图片和视频目录。

运行`xdg-user-dirs-update`命令后，它将根据配置文件的内容，自动创建相应的目录，并将用户的默认目录路径设置为配置文件中定义的路径。

`xdg-user-dirs-update`命令通常在用户登录时自动执行，确保用户的标准目录存在且正确设置。