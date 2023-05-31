## linux下，常用的查看动态库的符号链接工具

1. nm：nm 命令用于列出目标文件或共享库中的符号信息。可以使用 nm 命令来查看动态库中的符号链接。例如，要查看一个动态库文件（如libexample.so）中的符号链接，可以运行以下命令：
   ```
   nm -D libexample.so
   ```
   这将显示动态库中的所有符号及其链接信息。

2. objdump：objdump 命令用于显示目标文件或可执行文件的信息，包括符号表。可以使用 objdump 命令来查看动态库中的符号链接。例如，要查看一个动态库文件中的符号链接，可以运行以下命令：
   ```
   objdump -T libexample.so
   ```
   这将显示动态库中的符号链接表。

3. readelf：readelf 命令用于显示 ELF（Executable and Linkable Format）格式文件的信息，包括符号表。可以使用 readelf 命令来查看动态库中的符号链接。例如，要查看一个动态库文件中的符号链接，可以运行以下命令：
   ```
   readelf -s libexample.so
   ```
   这将显示动态库中的符号表，其中包含符号链接信息。

## readelf

+ readelf 是一个命令行工具，用于显示 ELF（Executable and Linkable Format）格式的文件的信息。ELF 是一种常用的二进制文件格式，用于可执行文件、共享库和目标文件。

+ 使用 readelf 命令可以查看和分析 ELF 文件的各种属性和部分内容，包括符号表、节表、段表、动态链接、重定位信息等。它提供了对 ELF 文件结构的详细解析和显示。

+ 以下是一些常用的 readelf 命令示例：

1. 查看 ELF 文件的头部信息：
   ```
   readelf -h executable
   ```

2. 查看 ELF 文件的节表信息：
   ```
   readelf -S executable
   ```

3. 查看 ELF 文件的符号表信息：
   ```
   readelf -s executable
   ```

4. 查看 ELF 文件的动态链接信息：
   ```
   readelf -d executable
   ```

5. 查看 ELF 文件的重定位信息：
   ```
   readelf -r executable
   ```

## 安装readelf

+ readelf 是 binutils 软件包的一部分，它通常预装在大多数 Linux 发行版中。如果你无法使用 readelf 命令，你可以尝试安装 binutils 软件包，以确保 readelf 工具可用。

+ 对于基于 Debian/Ubuntu 的系统，可以使用以下命令安装 binutils：
  ```
  sudo apt-get install binutils
  ```

+ 对于基于 Red Hat/CentOS 的系统，可以使用以下命令安装 binutils：
  ```
  sudo yum install binutils
  ```

+ 安装完成后，你就可以使用 readelf 命令来查看和分析 ELF 文件的信息了。请注意，安装软件包可能需要管理员权限，因此在安装时可能需要使用 sudo 或 root 用户身份运行命令。

+ 如果你的系统已经安装了 binutils 软件包，但仍然无法使用 readelf 命令，可能是因为它不在系统的 PATH 环境变量中。在这种情况下，你可以尝试使用绝对路径来运行 readelf，例如：
  ```
  /usr/bin/readelf -h executable
  ```

根据你的系统配置和安装方式，实际的 readelf 路径可能会有所不同。你可以使用 `which readelf` 命令来查找正确的路径。

这些命令示例只是 readelf 命令的一小部分功能演示，readelf 还提供了其他选项和功能，可以根据需要进行查看和分析 ELF 文件的更多细节。使用 `readelf --help` 命令可以查看 readelf 的完整选项列表和用法说明。

## Linux 常用命令全拼

+ 参考网站：`https://www.runoob.com/w3cnote/linux-command-full-fight.html`

## ldd（list dynamic dependencies）

+ 简介：
  + ldd命令用于打印程序或者库文件所依赖的共享库列表。

+ 语法
  + `ldd [参数] [文件]`

+ 参数
  + -v 详细信息模式，打印所有相关信息 
  + -u 打印未使用的直接依赖 
  + -d 执行重定位和报告任何丢失的对象 
  + -r 执行数据对象和函数的重定位，并且报告任何丢失的对象和函数 
  + --help 显示帮助信息

## eog

+ 简介：
  + 使用命令行查看图片

+ 示例：
  + `eog picturepath`

## watch

+ 简介：
  + watch命令是在Linux环境下，以固定时间间隔观察用户自定义命令运行情况的工具
  + 它暂时清除所有终端内容，并显示所附命令的输出，以及当前系统的日期和时间。
  + 它默认为每2秒更新一次所附命令的输出，`ctrl+c`用于退出
  + 当你需要监控一个命令输出随时间的变化时，watch命令很有用。这包括磁盘使用率、系统正常运行时间或跟踪错误。

+ 语法：
  + `watch [option] [command]`

+ 参数：
  + `[option]`  添加一个选项可以改变观察命令的行为方式
    + -n, --interval  允许你指定输出更新的时间间隔。
    + -d, --differences  突出了输出更新之间的差异。
    + -g, --chgexit  当用户定义的命令的输出发生变化时，退出监视命令
    + -t, --no-title  移除显示时间间隔、命令和当前时间及日期的标题。
    + -b, --beep  如果命令退出时出现错误，则播放声音警报（哔哔声）
    + -p, --precise  试图在-interval选项定义的确切秒数之后运行命令。
    + -e, --errexit  出错时停止输出更新，在按下一个键后退出命令。
    + -c, --color  解释ANSI颜色和样式序列。
    + -x, --exec  将用户定义的命令传递给exec，减少对额外引号的需要。
    + -w, --no-linewrap  关掉换行，截断长行。
    + -h, --help  显示帮助文本并退出
    + -v, --version  显示版本信息并退出

+ 示例
  + `watch -n 5 date`

## 查看linux服务器开机自启动服务

+ 命令：
  + `systemctl list-unit-files`

+ 参数：
  + 其中STATE显示为enable字样的服务，即可开机自启动的服务 

+ 查处的内容过多，可通过grep 命令进行筛选
  + `systemctl list-unit-files | grep firewalld`

## 开启或关闭开机自启动

+ 关闭开机自启动：
  + `systemctl disable  服务name`

+ 开启开机自启动：
  + `systemctl enable  服务name`

## unset

+ 简介：
  - Linux unset命令用于删除变量或函数
  - unset为shell内建指令，可删除变量或函数

+ 语法：
  -  `unset [-fv][变量或函数名称]`

+ 参数：
  - `-f`  仅删除函数
  - `-v`  仅删除变量 

## ln

+ 简介：
  - 它的功能是为某一个文件在另外一个位置建立一个同步的链接
  - 当我们需要在不同的目录，用到相同的文件时，我们不需要在每一个需要的目录下都放一个必须相同的文件，我们只要在某个固定的目录，放上该文件，然后在 其它的目录下用ln命令链接（link）它就可以，不必重复的占用磁盘空间。

+ 语法：
  - `ln [参数][源文件或目录][目标文件或目录]` 

+ 参数的格式为：
  - `[-bdfinsvF] [-S backup-suffix] [-V {numbered,existing,simple}]`
  - `[--help] [--version] [--]`

+ 详解：
  - Linux文件系统中，有所谓的链接(link)，我们可以将其视为档案的别名，而链接又可分为两种 : 硬链接(hard link)与软链接(symbolic link)，硬链接的意思是一个档案可以有多个名称，而软链接的方式则是产生一个特殊的档案，该档案的内容是指向另一个档案的位置。硬链接是存在同一个文件系统中，而软链接却可以跨越不同的文件系统。
  - 不论是硬链接或软链接都不会将原本的档案复制一份，只会占用非常少量的磁碟空间
  - 软链接：
    - 软链接，以路径的形式存在。类似于Windows操作系统中的快捷方式
    - 软链接可以 跨文件系统 ，硬链接不可以
    - 软链接可以对一个不存在的文件名进行链接
    - 软链接可以对目录进行链接
  - 硬链接
    - 硬链接，以文件副本的形式存在。但不占用实际空间。
    - 不允许给目录创建硬链接
    - 硬链接只有在同一个文件系统中才能创建

+ 参数
  + 必要参数
    - `--backup[=CONTROL]` 备份已存在的目标文件
    - `-b` 类似 --backup ，但不接受参数
    - `-d` 允许超级用户制作目录的硬链接
    - `-f` 强制执行
    - `-i` 交互模式，文件存在则提示用户是否覆盖
    - `-n` 把符号链接视为一般目录
    - `-s` 软链接(符号链接)
    - `-v` 显示详细的处理过程
  + 选择参数
    - `-S "-S<字尾备份字符串> "`或 `"--suffix=<字尾备份字符串>"`
    - `-V "-V<备份方式>"`或`"--version-control=<备份方式>"`
    - `--help` 显示帮助信息
    - `--version` 显示版本信息


## getconf

+ 简介：
  - 查询保存系统配置的变量
+ 参数
  - `-a` : 显示所有当前系统的配置变量和变量的值
  - `-v` : 
  - `system_var` : 查询指定配置变量的值
  - `path_var` : 参数是一个通过pathconf命令定义的系统配置变量

## 清空文件内容

+ 通过重定向到 Null 来清空文件内容
  + `> access.log`

+ 使用 ‘true’ 命令重定向来清空文件
  + 下面我们将使用 : 符号，它是 shell 的一个内置命令，等同于 true 命令，它可被用来作为一个 no-op（即不进行任何操作）
  + `: > access.log`
  + `true > access.log`

+ 使用 cat/cp/dd 实用工具及 /dev/null 设备来清空文件
  + 在 Linux 中， null 设备基本上被用来丢弃某个进程不再需要的输出流，或者作为某个输入流的空白文件，这些通常可以利用重定向机制来达到。
  + 所以 /dev/null 设备文件是一个特殊的文件，它将清空送到它这里来的所有输入，而它的输出则可被视为一个空文件。
  + 另外，你可以通过使用 cat 命令 显示 /dev/null 的内容然后重定向输出到某个文件，以此来达到清空该文件的目的。
  + `cat /dev/null > access.log`
+ 下面，我们将使用 cp 命令 复制 /dev/null 的内容到某个文件来达到清空该文件的目的，具体如下所示：
  + `cp /dev/null access.log`
+ 而下面的命令中， if 代表输入文件，of 代表输出文件。
  + `dd if=/dev/null of=access.log`

+ 使用 echo 命令清空文件
  + `echo "" > access.log`
  + `echo > access.log`
+ 注意：你应该记住空字符串并不等同于 null 。字符串表明它是一个具体的事物，只不过它的内容可能是空的，但 null 则意味着某个事物并不存在
+ 基于这个原因，当你将 echo 命令 的输出作为输入重定向到文件后，使用 cat 命令 来查看该文件的内容时，你将看到一个空白行（即一个空字符串）
+ 要将 null 做为输出输入到文件中，你应该使用 -n 选项，这个选项将告诉 echo 不再像上面的那个命令那样输出结尾的那个新行。

+ 使用 truncate 命令来清空文件内容
  + truncate 可被用来将一个文件缩小或者扩展到某个给定的大小
  + 你可以利用它和 -s 参数来特别指定文件的大小。要清空文件的内容，则在下面的命令中将文件的大小设定为 0:
    + `truncate -s 0 access.log`