## apt 家族

### apt

+ update
  - 从所有配置的源中下载包信息。其他的命令对这些数据进行操作

+ upgrade
  - upgrade 用于安装当前安装在系统上的所有软件包的可用升级，这些软件包来自于 sources.list(5) 配置的源的升级
  - 如果有需要满足的依赖关系，新的安装包将会被安装。但是现有的安装包永远都不会被删除。如果一个软件包的升级需要删除一个已安装的软件包，那么这个软件包的升级将不会被执行

+ full-upgrade
  - full-upgrade执行升级的功能，但如果需要升级系统，它将删除当前安装的软件包，如果需要这样做来升级整个系统的话。 

+ install, remove, purge
  - install, 安装软件包
  - remove, 仅删除软件包数据，会留下用户配置信息
  - purge, 会既删除软件包数据，也会删除用户配置信息 

+ autoremove
  - autoremove是用来删除那些自动安装的软件包，以满足依赖的软件包，但现在不再需要了，因为依赖关系改变了或需要它们的软件包在这期间被删除，因此不再需要。 

+ search
  - 搜索可以用来在可用的软件包列表中搜索给定包的列表中搜索，并显示匹配结果。 

+ show
  - 显示有关给定软件包的信息，包括它的依赖性、安装和下载大小、软件包的可用来源以及对它的描述和下载大小，软件包的可用来源，软件包内容的描述等等。包的内容描述等等。 

+ list
  - list与dpkg-query --list有点类似，它可以显示满足特定条件的满足特定条件的软件包列表。 

+ edit-sources
  - edit-sources 可以让你在你喜欢的文本编辑器中编辑 sources.list(5) 文件。同时也提供基本的智能检查。 

### apt-get 

+ update
+ upgrade

+ dist-upgrade
  - dist-upgrade除了执行升级的功能外，还能智能地处理新版本软件包的依赖关系变化；apt-get有一个 "智能 "的冲突解决系统，它将尝试升级最重要的软件包如果有必要的话，它会尝试升级最重要的软件包，而牺牲掉不那么重要的软件包。 

+ dselect-upgrade
  - dselect-upgrade与传统的Debian packaging前端，即 dselect(1)。 

+ install
+ remove
+ purge

+ source 
  - 获取源码包

+ build-dep
  - build-dep 导致 apt-get 安装/移除软件包，以满足一个源代码软件包的构建的依赖性。 

+ check
  - 检查是一个诊断工具；它更新软件包缓存并检查损坏的依赖关系。 

+ download
  - download将下载给定的二进制包到当前目录。

+ clean
  - 清理本地存储库中检索到的软件包文件。它删除了除锁文件外的所有文件都从 /var/cache/apt/archives/ 和/var/cache/apt/archives/partial/。 

+ autoclean
  - 和clean一样，autoclean也会清除本地仓库中检索到的软件包文件。不同的是不同的是，它只删除那些不能再被下载的软件包文件，并且基本上是无用的。 

+ changelog
  - changelog试图下载一个软件包的更新日志并通过sensible-pager。

+ indextargets
  - 默认情况下，显示一个deb822格式的所有数据文件的信息列表(又称索引目标) apt-get update 会下载。 

### apt-cache 

在Linux中，`apt-cache`是一个用于查询APT（Advanced Package Tool）软件包管理器缓存的命令行工具。它允许您查看已安装软件包和可用软件包的详细信息，以及搜索软件包的相关信息。

下面是一些常见的`apt-cache`命令选项和用法：

1. 查询软件包信息：
   - `apt-cache show <package>`：显示指定软件包的详细信息，包括版本、描述、作者、依赖关系等。
   - `apt-cache showpkg <package>`：显示软件包的包信息以及其相关的依赖关系和依赖它的软件包信息。

2. 搜索软件包：
   - `apt-cache search <pattern>`：根据模式搜索可用的软件包。模式可以是软件包名称、关键字或描述的一部分。
   - `apt-cache search <keyword1> <keyword2>`：根据多个关键字搜索软件包。这将返回同时包含这些关键字的软件包。
   - `apt-cache search --names-only <pattern>`：只搜索软件包的名称而不搜索描述或关键字。

3. 显示依赖关系：
   - `apt-cache depends <package>`：显示指定软件包的依赖关系，包括它所依赖的软件包和被它所依赖的软件包。
   - `apt-cache rdepends <package>`：显示依赖于指定软件包的其他软件包。

4. 清除软件包缓存：
   - `apt-cache clean`：清除APT软件包管理器的本地软件包缓存。这将删除已下载的软件包文件，但不会删除已安装的软件包。

这些是`apt-cache`命令的一些常见选项和用法。您可以使用`apt-cache`命令来获取关于软件包的信息、搜索软件包以及查看软件包的依赖关系。在使用这些命令时，请确保以管理员权限运行，例如使用`sudo`命令。

### apt-file

+ 查找包文件
  + `apt-file find libopenssh.so`

在Linux中，`apt-file`是一个用于查询软件包文件的命令行工具。它可以帮助您查找特定文件属于哪个软件包，并可以搜索软件包中的文件。

以下是一些常见的`apt-file`命令选项和用法：

1. 初始化数据库：
   在第一次使用`apt-file`之前，需要初始化文件数据库。使用以下命令进行初始化：
   ```bash
   sudo apt-file update
   ```

2. 查询文件所属的软件包：
   - `apt-file search <filename>`：查询指定文件所属的软件包。文件名可以是绝对路径或相对路径。
   - 例如：`apt-file search /bin/ls`将返回包含`/bin/ls`的软件包。

3. 列出软件包中的文件：
   - `apt-file list <package>`：列出指定软件包中的所有文件。
   - 例如：`apt-file list coreutils`将列出`coreutils`软件包中的所有文件。

4. 搜索文件名：
   - `apt-file search <pattern>`：根据模式搜索文件名。模式可以是文件名的一部分或关键字。
   - 例如：`apt-file search libstdc++.so`将返回包含`libstdc++.so`的软件包。

请注意，`apt-file`命令需要根据您的系统安装软件包文件的索引数据库。因此，在使用`apt-file`之前，需要确保数据库已经初始化并更新。您可以使用`sudo apt-file update`命令来更新数据库。

使用`apt-file`命令可以帮助您轻松地查找软件包文件和软件包中的文件。这对于解决缺少文件或查找特定文件所属的软件包非常有用。

### apt-mark

在Linux中，`apt-mark`是一个用于标记和操作APT软件包状态的命令行工具。它可以用于设置、清除和查询软件包的各种标记，以及管理软件包的状态。

以下是一些常见的`apt-mark`命令选项和用法：

1. 标记软件包状态：
   - `apt-mark hold <package>`：将指定软件包标记为"hold"状态，阻止其被升级或删除。
   - `apt-mark unhold <package>`：取消指定软件包的"hold"标记。

2. 设置软件包自动安装状态：
   - `apt-mark auto <package>`：将指定软件包标记为"auto"状态，允许APT自动安装和升级。
   - `apt-mark manual <package>`：将指定软件包标记为"manual"状态，阻止APT自动安装和升级。

3. 查询软件包状态：
   - `apt-mark showhold`：显示所有被标记为"hold"状态的软件包。
   - `apt-mark showauto`：显示所有被标记为"auto"状态的软件包。

4. 清除软件包状态：
   - `apt-mark unmarkauto <package>`：取消指定软件包的"auto"标记。
   - `apt-mark unmarkhold <package>`：取消指定软件包的"hold"标记。
   - `apt-mark unmarkall`：清除所有软件包的标记。

这些是`apt-mark`命令的一些常见选项和用法。您可以使用`apt-mark`命令来设置软件包的状态标记，以控制APT软件包管理器的行为。这对于防止软件包被升级或删除、手动管理软件包状态以及自定义软件包安装行为非常有用。请注意，在使用这些命令时，需要以管理员权限运行，例如使用`sudo`命令。

## aptitude 

`aptitude`是Linux系统中的一个交互式软件包管理器，用于安装、升级、删除和管理软件包。它提供了一个用户友好的命令行界面，可以方便地浏览、搜索和操作软件包。

下面是一些常见的`aptitude`命令选项和用法：

1. 浏览软件包列表：
   - `aptitude`：启动`aptitude`界面，显示可用软件包列表。
   - 使用箭头键或快捷键浏览软件包列表。
   - 输入软件包名或关键字进行搜索。

2. 安装和卸载软件包：
   - 使用`+`号标记软件包以进行安装。
   - 使用`-`号标记软件包以进行卸载。
   - 按下`g`键执行所有标记的操作。

3. 查看软件包详细信息：
   - 在软件包列表中选中一个软件包，按下`Enter`键以查看详细信息。
   - 显示软件包的描述、版本、依赖关系和其他相关信息。

4. 搜索软件包：
   - 按下`/`键进行搜索，然后输入要搜索的软件包名称或关键字。
   - 使用箭头键浏览搜索结果。

5. 进阶命令：
   - `aptitude update`：更新软件包列表。
   - `aptitude upgrade`：升级可用的软件包。
   - `aptitude dist-upgrade`：执行发行版升级，包括软件包和系统组件的升级。
   - `aptitude clean`：清理软件包缓存。
   - `aptitude autoclean`：清理旧版本的软件包。

请注意，`aptitude`命令提供了更多功能和选项，可以根据您的需求进行更高级的软件包管理操作。在使用`aptitude`时，请仔细阅读相关文档和手册，以了解更多命令和选项的详细信息。

总体而言，`aptitude`是一个功能强大且易于使用的软件包管理器，提供了交互式的方式来管理和控制Linux系统上的软件包。

## free

+ Linux free命令用于显示内存状态。
+ free指令会显示内存的使用情况，包括实体内存，虚拟的交换文件内存，共享内存区段，以及系统核心使用的缓冲区等。

+ 语法：
  + `free [-bkmotV][-s <间隔秒数>]`
+ 参数说明：
    + -b 　以Byte为单位显示内存使用情况。
    + -k 　以KB为单位显示内存使用情况。
    + -m 　以MB为单位显示内存使用情况。
    + -h 　以合适的单位显示内存使用情况，最大为三位数，自动计算对应的单位值。单位有：
        + B = bytes
        + K = kilos
        + M = megas
        + G = gigas
        + T = teras
    + -o 　不显示缓冲区调节列。
    + -s<间隔秒数> 　持续观察内存使用状况。
    + -t 　显示内存总和列。
    + -V 　显示版本信息。

+ 实例：
  + 以总和的形式显示内存的使用信息 : `free -t //以总和的形式查询内存的使用信息`
  + 周期性的查询内存使用信息 : `free -s 10 //每10s 执行一次命令`

## SSH

### 修改SSH配置文件

+ `sudo vim /etc/ssh/sshd_config`
+ 搜索`PermitRootLogin`，将一下配置：
  ```
    33 #LoginGraceTime 2m
    34 #PermitRootLogin prohibit-password
    35 #StrictModes yes
    36 #MaxAuthTries 6
    37 #MaxSessions 10
  ``` 
+ 修改为：
  ```
     LoginGraceTime 2m
     PermitRootLogin yes
     StrictModes yes
     #MaxAuthTries 6
     #MaxSessions 10
  ``` 

### 重启ssh，使配置生效

+ `sudo service ssh restart`

### Linux和Windows互相拷贝

+ 从Linux复制到Windows：
  + `scp /home/user/data/tmp.txt user@192.169.4.16:/C:Users/user/Desktop`

## 信号详情

|     名称      |    默认动作  |   说明    |
| :---         |  :---       |:---      |
| SIGHUP       |终止进程       |终端线路挂断|
| SIGINT       |终止进程       |中断进程|
| SIGQUIT      |建立CORE文件   |终止进程，并且生成core文件|
| SIGILL       |建立CORE文件   |非法指令|
| SIGTRAP      |建立CORE文件   |跟踪自陷|
| SIGBUS       |建立CORE文件   |总线错误|
| SIGSEGV      |建立CORE文件   |段非法错误|
| SIGFPE       |建立CORE文件   |浮点异常|
| SIGIOT       |建立CORE文件   |执行I/O自陷|
| SIGKILL      |终止进程       |杀死进程|
| SIGPIPE      |终止进程       |向一个没有读进程的管道写数据|
| SIGALARM     |终止进程       |计时器到时|
| SIGTERM      |终止进程       |软件终止信号|
| SIGSTOP      |停止进程       |非终端来的停止信号|
| SIGTSTP      |停止进程       |终端来的停止信号|
| SIGCONT      |忽略信号       |继续执行一个停止的进程|
| SIGURG       |忽略信号       |I/O紧急信号|
| SIGIO        |忽略信号       |描述符上可以进行I/O|
| SIGCHLD      |忽略信号       |当子进程停止或退出时通知父进程|
| SIGTTOU      |停止进程       |后台进程写终端|
| SIGTTIN      |停止进程       |后台进程读终端|
| SIGXGPU      |终止进程       |CPU时限超时|
| SIGXFSZ      |终止进程       |文件长度过长|
| SIGWINCH     |忽略信号       |窗口大小发生变化|
| SIGPROF      |终止进程       |统计分布图用计时器到时|
| SIGUSR1      |终止进程       |用户定义信号1|
| SIGUSR2      |终止进程       |用户定义信号2|
| SIGVTALRM    |终止进程       |虚拟计时器到时|

## trap 信号

### 1.1 简单使用

+ trap命令，用于指定在接收到信号后将要采取的动作。常见的用途是在脚本程序被中断时完成清理工作。

+ 历史上，shell总是用数字来代表信号，而新的脚本程序应该使用信号的名字，它们保存在用`#include`命令包含进来的`signal.h`头文件中，在使用信号名时需要省略`SIG`前缀
+ kill和trap等都可以看到信号编号及其关联的名称。“信号”是指那些被异步发送到一个程序的事件。默认情况下，它们通常会终止一个程序的运行。

+ 查看所有信号的：
  + `trap -l`

### 1.2 trap的使用

+ trap命令的参数分为两部分，前一部分是接收到指定信号时将要采取的行动，后一部分是要处理的信号名。
  + `trap command signal`

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

## read

+ 从命令行读取标准输入
+ 读取输入，保存到变量
  + `read -p "please input >>>" var`

在Linux中，`read`命令用于从标准输入读取用户输入并存储到一个或多个变量中。它通常用于脚本中，以便与用户进行交互并获取输入数据。

以下是`read`命令的一般语法：

```
read [-options] [variable...]
```

其中，`-options`是可选的一些选项，`variable`是要存储输入的一个或多个变量。

以下是一些常见的`read`命令选项和用法：

1. 读取单个变量：
   ```
   read variable
   ```

   此命令将提示用户输入，并将输入的值存储到`variable`变量中。

2. 读取多个变量：
   ```
   read variable1 variable2 ...
   ```

   此命令将按顺序提示用户输入，并将每个输入的值依次存储到相应的变量中。

3. 自定义提示符：
   ```
   read -p "Enter your name: " name
   ```

   此命令将显示自定义的提示符（在双引号中指定），并将输入的值存储到`name`变量中。

4. 设置超时：
   ```
   read -t 5 variable
   ```

   此命令将在等待用户输入时设置一个超时时间（5秒）。如果在超时时间内未收到输入，命令将继续执行并变量的值为空。

5. 读取行中的多个单词：
   ```
   read -a array
   ```

   此命令将读取一行输入，并将输入的单词存储到一个数组变量中。

`read`命令还有其他一些选项，如设置分隔符、禁止回显输入等，您可以通过`man read`命令查看完整的选项和用法说明。

请注意，`read`命令在交互式脚本中非常有用，可以用于获取用户输入并在脚本中进行处理。

## more

+ more, 一次显示一页

在Linux中，`more`命令用于逐页显示文本文件的内容。它允许您按页浏览文本文件，以便更好地查看和阅读长篇文本。

以下是`more`命令的一般语法：

```
more [options] [file]
```

其中，`options`是可选的一些选项，`file`是要显示的文本文件。

以下是一些常见的`more`命令选项和用法：

1. 逐页显示文件内容：
   ```
   more file.txt
   ```

   此命令将按一页一页地显示`file.txt`文件的内容。您可以使用空格键向下翻页，按`q`键退出。

2. 显示行号：
   ```
   more -n file.txt
   ```

   此命令将在每一行前显示行号。

3. 显示百分比：
   ```
   more -p file.txt
   ```

   此命令将在屏幕底部显示当前显示内容相对于整个文件的百分比。

4. 搜索文本：
   ```
   more -s file.txt
   ```

   此命令将禁止滚屏显示，只显示与搜索模式匹配的行。

5. 跳转到指定行：
   ```
   more +10 file.txt
   ```

   此命令将从第10行开始显示文件内容。

请注意，`more`命令仅支持向前翻页，无法向后翻页。如果您需要更强大和灵活的文本查看工具，可以考虑使用`less`命令，它提供了更多功能，如向前翻页、向后翻页、搜索等。

这些是`more`命令的一些常见选项和用法。您可以根据需要选择适合的选项来浏览和查看文本文件的内容。

## less

在Linux中，`less`命令用于逐页浏览文本文件的内容。它是对`more`命令的改进，提供了更多的功能和灵活性。

以下是`less`命令的一般语法：

```
less [options] [file]
```

其中，`options`是可选的一些选项，`file`是要显示的文本文件。

以下是一些常见的`less`命令选项和用法：

1. 逐页浏览文件内容：
   ```
   less file.txt
   ```

   此命令将按一页一页地显示`file.txt`文件的内容。您可以使用空格键向下翻页，按`b`键向上翻页，按`q`键退出。

2. 搜索文本：
   ```
   less -p pattern file.txt
   ```

   此命令将打开文件并搜索与`pattern`匹配的文本。按`n`键向下查找下一个匹配项，按`N`键向上查找上一个匹配项。

3. 显示行号：
   ```
   less -N file.txt
   ```

   此命令将在每一行前显示行号。

4. 显示文件大小和位置：
   ```
   less -m file.txt
   ```

   此命令将在屏幕底部显示当前显示内容相对于整个文件的百分比、文件大小和当前显示内容的行数。

5. 跳转到指定行：
   ```
   less +10 file.txt
   ```

   此命令将从第10行开始显示文件内容。

6. 从命令行读取输入：
   ```
   command | less
   ```

   此命令将从命令行输出中读取内容并使用`less`进行浏览。

`less`命令还支持其他一些选项和操作，如按字母排序、复制文本、显示特定行范围等。您可以使用`man less`命令查看完整的选项和用法说明。

总体而言，`less`命令是一个功能强大且灵活的文本浏览器，它可以帮助您浏览和查看大型文本文件，并提供了许多方便的功能。

## MD5校验

+ Windows下生成md5校验码: `certutil -hashfile filename MD5`
+ Linux下生成md5校验码:   `md5sum filename`

## nohup

<!-- + `nohup, no hang up`， 用于在系统后台不挂断地运行命令，退出终端不会影响程序的运行
+ 在默认情况下（非重定向时），会输出一个名叫`nohup.out`的文件在当前目录下，如果当前目录下文件不可写，输出重定向到`$HOME/nohup.out`文件中

+ 语法格式 -- `nohup Command [Arg ...] [ & ]`

+ 参数说明
  + `Command` -- 要执行的命令
  + `Arg` -- 一些参数，可以指定输出文件
  + `&` -- 让命令在后台执行，终端退出后命令仍旧执行 -->

在Linux中，`nohup`命令用于在后台运行程序，并忽略掉终端断开的信号（SIGHUP）。它允许您在终端退出后继续运行程序，同时将程序的输出重定向到指定的文件中。

以下是`nohup`命令的一般语法：

```
nohup command [arguments] [redirection]
```

其中，`command`是要运行的程序或命令，`arguments`是传递给程序的参数，`redirection`是输出重定向的选项。

以下是一些常见的`nohup`命令选项和用法：

1. 后台运行程序：
   ```
   nohup command &
   ```

   此命令将`command`程序在后台运行，并忽略终端断开信号。

2. 输出重定向到文件：
   ```
   nohup command > output.log 2>&1 &
   ```

   此命令将`command`程序的输出重定向到`output.log`文件中。`2>&1`将标准错误输出也重定向到相同的文件。

3. 指定日志文件：
   ```
   nohup command > output.log 2> error.log &
   ```

   此命令将标准输出重定向到`output.log`文件，将标准错误输出重定向到`error.log`文件。

4. 追加到日志文件：
   ```
   nohup command >> output.log 2>&1 &
   ```

   此命令将标准输出和标准错误输出追加到`output.log`文件中。

5. 查看输出：
   ```
   tail -f output.log
   ```

   使用`tail -f`命令实时查看`output.log`文件的内容，以便监控程序的输出。

请注意，`nohup`命令将程序放在后台运行，但它仍然会生成一个`nohup.out`文件，用于保存程序的输出。如果不想生成此文件，可以将输出重定向到其他文件。

使用`nohup`命令时，通常建议同时使用`&`符号将程序放在后台运行，并将输出重定向到文件，以确保程序在终端退出后继续运行，并且输出可以保存。

## split

+ 功能：将单个tar文件切割成多个tar文件
+ 命令：`split -b 4000M -a 1 -d nvidia.tar nvidia.tar`
+ 参数：
  + `-b`  --  指定生成的分割包大小
  + `-a`  --  设定序列的长度，默认为2，这里设置为1，生成的文件就为nvidia.tar1，
  + `-d`  --  指定生成的分割包后缀为数字的形式

在Linux中，`split`命令用于将一个大文件拆分成多个较小的文件。它可以按照文件大小、行数或指定的分割标准将文件分割成多个部分，方便处理和传输大型文件。

以下是`split`命令的一般语法：

```
split [options] input_file [output_file_prefix]
```

其中，`options`是可选的一些选项，`input_file`是要拆分的输入文件，`output_file_prefix`是输出文件的前缀。输出文件的名称将以前缀开头，后跟一个字母或数字来表示各个部分。

以下是一些常见的`split`命令选项和用法：

1. 按照文件大小拆分：
   ```
   split -b size input_file output_file_prefix
   ```

   此命令将根据指定的文件大小（`size`）将输入文件拆分成多个部分。`size`可以使用以下后缀表示：K（千字节）、M（兆字节）、G（千兆字节）等。

2. 按照行数拆分：
   ```
   split -l lines input_file output_file_prefix
   ```

   此命令将根据指定的行数（`lines`）将输入文件拆分成多个部分。

3. 自定义输出文件名格式：
   ```
   split --additional-suffix=suffix input_file output_file_prefix
   ```

   此命令将在输出文件的名称中添加指定的后缀（`suffix`），以自定义输出文件名的格式。

4. 拆分二进制文件：
   ```
   split -b size --binary input_file output_file_prefix
   ```

   如果要拆分二进制文件，可以使用`--binary`选项。

`split`命令还支持其他一些选项，如指定拆分文件的数量、保留原始文件等。您可以使用`man split`命令查看完整的选项和用法说明。

`split`命令对于处理大型文件或需要分割成较小部分的文件非常有用。它可以帮助您在处理和传输文件时更加高效地操作数据。

## 将`split`分割的压缩包合并

+ `cat nvidia.tar* > nvidia.tar | cat nvidia.tar01 nvidia.tar02 > nvidia.tar`

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

在Linux中，`mktemp`命令用于创建一个临时文件或临时目录，并返回其名称。临时文件和目录通常用于在脚本或程序中进行临时性的文件操作，并在使用完毕后自动删除。

以下是`mktemp`命令的一般语法：

```
mktemp [options] [template]
```

其中，`options`是可选的一些选项，`template`是用于生成临时文件名的模板。

以下是一些常见的`mktemp`命令选项和用法：

1. 创建一个临时文件：
   ```
   mktemp
   ```

   此命令将生成一个临时文件，并返回其完整的路径和文件名。

2. 创建一个临时目录：
   ```
   mktemp -d
   ```

   此命令将生成一个临时目录，并返回其完整的路径。

3. 自定义临时文件名模板：
   ```
   mktemp -t prefix.XXXXXX
   ```

   此命令将使用指定的前缀（`prefix`）和`XXXXXX`占位符作为模板生成临时文件名。`XXXXXX`将被自动生成的随机字符替换。

4. 指定临时文件或目录所在的目录：
   ```
   mktemp -p directory
   ```

   此命令将在指定的目录（`directory`）中创建临时文件或目录。

`mktemp`命令还支持其他一些选项，如设置临时文件的权限、创建多个临时文件等。您可以使用`man mktemp`命令查看完整的选项和用法说明。

使用`mktemp`命令可以方便地创建临时文件或目录，避免手动管理和清理临时文件的麻烦。

## wc

<!-- + `wc`,命令用于计算字数
+ 利用`wc`指令我们可以计算文件的Byte数，字数，或者是列数，如果不指定文件名称，或者是所给的文件名为`"-"`，则wc指令会从标准如入设备读取数据
+ 语法：`wc [-clw][--help][--version][files...]`
+ 参数：
  + `-c, -bytes, --chars`：只显示Bytes数
  + `-l， --lines`：显示行数
  + `-w, --words`：只显示字数
+ 查看某个目录下的文件数：`ls -l | grep "-" | wc -l` -->

在Linux中，`wc`命令用于计算给定文件或标准输入中的字节数、字数和行数。它是一个简单但功能强大的命令，经常用于统计文本文件的信息。

以下是`wc`命令的一般语法：

```
wc [options] [file...]
```

其中，`options`是可选的一些选项，`file`是要统计的文件。

以下是一些常见的`wc`命令选项和用法：

1. 统计文件中的字节数、字数和行数：
   ```
   wc file.txt
   ```

   此命令将输出文件`file.txt`中的字节数、字数和行数。

2. 只统计字节数：
   ```
   wc -c file.txt
   ```

   此命令将仅输出文件`file.txt`中的字节数。

3. 只统计字数：
   ```
   wc -w file.txt
   ```

   此命令将仅输出文件`file.txt`中的字数。

4. 只统计行数：
   ```
   wc -l file.txt
   ```

   此命令将仅输出文件`file.txt`中的行数。

5. 批量统计多个文件：
   ```
   wc file1.txt file2.txt file3.txt
   ```

   此命令将分别统计并输出多个文件的字节数、字数和行数。

6. 统计多个文件的总计：
   ```
   wc -l file1.txt file2.txt file3.txt
   ```

   此命令将统计多个文件的行数，并在最后输出总行数。

`wc`命令还支持其他一些选项，如统计最长行的长度、输出格式化结果等。您可以使用`man wc`命令查看完整的选项和用法说明。

总体而言，`wc`命令是一个方便的工具，用于统计文件中的字节数、字数和行数。它在处理文本文件时非常有用，可以提供对文件结构和内容的快速概览。

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

<!-- + lsmod - Show the status of modules in the Linux Kernel -->

在Linux中，`lsmod`命令用于列出当前加载的内核模块。内核模块是与内核相互独立的可加载程序，它们可以在运行时加载和卸载，以添加或删除特定的功能和驱动程序。

以下是`lsmod`命令的一般语法：

```
lsmod
```

使用`lsmod`命令时，它会直接输出已加载的内核模块的列表。每个模块的输出通常包括以下列：

1. Module：内核模块的名称。
2. Size：模块在内存中的大小（以字节为单位）。
3. Used by：使用该模块的进程或其他模块的列表。

例如，以下是`lsmod`命令的示例输出：

```
Module                 Size  Used by
nls_utf8               16384  1
isofs                  49152  1
usb_storage            77824  1
```

这个输出表示有三个内核模块被加载：`nls_utf8`、`isofs`和`usb_storage`。`nls_utf8`模块被一个进程或其他模块使用，`isofs`模块被一个进程或其他模块使用，而`usb_storage`模块仅被一个进程或其他模块使用。

`lsmod`命令常用于查看当前系统中加载的内核模块，以及它们之间的依赖关系。它对于诊断和调试与内核模块相关的问题非常有用。

希望这个简要的解释对您有帮助。如有任何进一步的问题，请随时提问。

## screen

<!-- + screen， 提供从单个SSH会话中使用多个shell窗口
+ 常用命令：
  + `screen -S name` : 创建会话并命名
  + `screen -r -S name` : 重新连接会话
  + `ctrl - a & d`   : 分离会话
  +  -->

在Linux中，`screen`命令用于创建和管理会话（session），它允许您在单个终端窗口中同时运行多个终端会话。`screen`命令提供了一种将会话分离和重新连接的机制，使您可以在需要时断开会话，并在稍后重新连接，而不会丢失会话的状态和进程。

以下是`screen`命令的一般语法：

```
screen [options] [command [args]]
```

其中，`options`是可选的一些选项，`command`是要运行的命令，`args`是传递给命令的参数。

以下是一些常见的`screen`命令选项和用法：

1. 创建新会话：
   ```
   screen
   ```

   此命令将创建一个新的`screen`会话。

2. 列出所有会话：
   ```
   screen -ls
   ```

   此命令将列出所有已经存在的`screen`会话。

3. 连接到会话：
   ```
   screen -r session_id
   ```

   此命令将连接到指定的会话，`session_id`是会话的唯一标识符。

4. 断开会话：
   在`screen`会话中按下`Ctrl + A`，然后按下`d`键。

   此命令将断开当前的`screen`会话，但会话仍在后台运行。

5. 重新连接会话：
   ```
   screen -r session_id
   ```

   此命令将重新连接之前断开的`screen`会话。

6. 指定会话名称：
   ```
   screen -S session_name
   ```

   此命令将创建一个具有指定名称的`screen`会话。

`screen`命令还支持其他一些选项和操作，如分割窗口、滚动缓冲区、复制粘贴等。您可以使用`man screen`命令查看完整的选项和用法说明。

`screen`命令对于在远程服务器上长时间运行的任务、会话的持久性以及同时管理多个终端会话非常有用。它提供了一种灵活和强大的方式来处理会话管理和终端复用。

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

## source  

+ source命令（从 C Shell而来）是`bash shell`的内置命令； `.` 点命令，就是一个点符号，是source的另一名称。这两个命令都以一个脚本为参数，该脚本将在当前shell的环境执行，即** 不会启动一个新的子shell** 。所有在脚本中设置的变量都将成为当前shell的一部分
+ source命令的妙用：
  + 在编译核心时，常常要反复输入一长串命令。这些命令即长又繁琐，而且有时候容易输错。
  + 如果把命令做成一个文件，让它自动执行，对于需要多次反复编译核心的用户来说，会很方便
  + 用source命令可以做到这一点。** 它的作用就是把一个文件的内容当成是shell来执行** 
+ `source filename, sh filename, ./filename`
  + 当shell脚本具有可执行权限时，用`sh filename`与`./filename`执行脚本没有区别。 `./filename`是因为当前目录没有在`PATH`, 所有`.` 都是用来表示当前目录的

在Linux中，`source`命令用于在当前Shell环境中执行指定的脚本文件，并将其内容加载到当前Shell会话中。它通常用于加载和执行Shell脚本，以便在当前Shell会话中设置环境变量、函数和其他Shell配置。

以下是`source`命令的一般语法：

```
source filename
```

或者可以使用点号(`.`)来代替`source`命令：

```
. filename
```

其中，`filename`是要执行的脚本文件的名称，可以是相对路径或绝对路径。

`source`命令的作用是将指定的脚本文件的内容作为当前Shell会话的一部分来执行，而不是在一个单独的子Shell中执行。这意味着在执行完脚本后，其中定义的变量、函数和别名将在当前Shell环境中保持可用。

使用`source`命令的一些常见用例包括：

1. 加载Shell配置文件：
   ```
   source ~/.bashrc
   ```

   此命令将加载用户主目录下的`.bashrc`文件中定义的配置，使得配置的环境变量、别名等在当前Shell会话中生效。

2. 执行Shell脚本：
   ```
   source script.sh
   ```

   此命令将执行`script.sh`脚本文件，并将脚本中的内容加载到当前Shell环境中。

需要注意的是，`source`命令是在当前Shell环境中执行脚本，因此需要确保脚本文件具有可执行权限。

使用`source`命令可以方便地在当前Shell会话中加载和执行脚本文件，将脚本中定义的变量、函数和其他配置设置直接应用于当前环境。

## tar 

+ tar(tape archive),命令用于备份文件
+ tar是用来建立,还原备份文件的工具程序,它可以加入,解开备份文件内的文件

+ tar命令 可以为linux的文件和目录创建档案。利用tar，可以为某一特定文件创建档案（备份文件），也可以在档案中改变文件，或者向档案中加入新的文件。tar最初被用来在磁带上创建档案，现在，用户可以在任何设备上创建档案。利用tar命令，可以把一大堆的文件和目录全部打包成一个文件，这对于备份文件或将几个文件组合成为一个文件以便于网络传输是非常有用的。

+ 首先要弄清两个概念：打包和压缩。打包是指将一大堆文件或目录变成一个总的文件；压缩则是将一个大的文件通过一些压缩算法变成一个小文件。
+ 为什么要区分这两个概念呢？
  + 这源于Linux中很多压缩程序只能针对一个文件进行压缩，这样当你想要压缩一大堆文件时，你得先将这一大堆文件先打成一个包（tar命令），然后再用压缩程序进行压缩（gzip bzip2命令）。

+ 语法：
  ```
    tar [-ABcdgGhiklmMoOpPrRsStuUvwWxzZ][-b <区块数目>][-C <目的目录>]
        [-f <备份文件>][-F <Script文件>][-K <文件>][-L <媒体容量>][-N <日期时间>]
        [-T <范本文件>][-V <卷册名称>][-X <范本文件>][-<设备编号><存储密度>]
        [--after-date=<日期时间>][--atime-preserve][--backuup=<备份方式>]
        [--checkpoint][--concatenate][--confirmation][--delete]
        [--exclude=<范本样式>][--force-local][--group=<群组名称>][--help]
        [--ignore-failed-read][--new-volume-script=<Script文件>][--newer-mtime]
        [--no-recursion][--null][--numeric-owner][--owner=<用户名称>][--posix]
        [--erve][--preserve-order][--preserve-permissions]
        [--record-size=<区块数目>][--recursive-unlink][--remove-files]
        [--rsh-command=<执行指令>][--same-owner][--suffix=<备份字尾字符串>]
        [--totals][--use-compress-program=<执行指令>][--version]
        [--volno-file=<编号文件>][文件或目录...]
  ``` 

+ 选项：
  + -A或--catenate：新增文件到以存在的备份文件；
  + -b<区块数目>或–blocking-factor=<区块数目>；
  + -B：设置区块大小；
  + -c或--create：建立新的备份文件；
  + -C <目录>：切换工作目录，先进入指定目录再执行压缩/解压缩操作，可用于仅压缩特定目录里的内容或解压缩到特定目录
  + -d或–diff或–compare 对比备份文件内和文件系统上的文件的差异。
  + -f<备份文件>或–file=<备份文件> 指定备份文件。
  + -F<Script文件>或–info-script=<Script文件> 每次更换磁带时，就执行指定的Script文件
  + -g或–listed-incremental 处理GNU格式的大量备份。
  + -G或–incremental 处理旧的GNU格式的大量备份。
  + -h或–dereference 不建立符号连接，直接复制该连接所指向的原始文件。
  + -i或–ignore-zeros 忽略备份文件中的0 Byte区块，也就是EOF。
  + -k或–keep-old-files 解开备份文件时，不覆盖已有的文件。
  + -K<文件>或–starting-file=<文件> 从指定的文件开始还原。
  + -l或–one-file-system 复制的文件或目录存放的文件系统，必须与tar指令执行时所处的文件系统相同，否则不予复制
  + -L<媒体容量>或-tape-length=<媒体容量> 设置存放每体的容量，单位以1024 Bytes计算。
  + -m或–modification-time 还原文件时，不变更文件的更改时间。
  + -M或–multi-volume 在建立，还原备份文件或列出其中的内容时，采用多卷册模式。
  + -N<日期格式>或–newer=<日期时间> 只将较指定日期更新的文件保存到备份文件里。
  + -o或–old-archive或–portability 将资料写入备份文件时使用V7格式。
  + -O或–stdout 把从备份文件里还原的文件输出到标准输出设备。
  + -p或–same-permissions 用原来的文件权限还原文件。
  + -P或–absolute-names 文件名使用绝对名称，不移除文件名称前的”/”号。
  + -r或–append 新增文件到已存在的备份文件的结尾部分。
  + -R或–block-number 列出每个信息在备份文件中的区块编号。
  + -s或–same-order 还原文件的顺序和备份文件内的存放顺序相同。
  + -S或–sparse 倘若一个文件内含大量的连续0字节，则将此文件存成稀疏文件。
  + -t或–list 列出备份文件的内容。
  + -T<范本文件>或–files-from=<范本文件> 指定范本文件，其内含有一个或多个范本样式，让tar解开或建立符合设置条件的文件。
  + -u或–update 仅置换较备份文件内的文件更新的文件。
  + -U或–unlink-first 解开压缩文件还原文件之前，先解除文件的连接。
  + -v或–verbose 显示指令执行过程。
  + -V<卷册名称>或–label=<卷册名称> 建立使用指定的卷册名称的备份文件。
  + -w或–interactive 遭遇问题时先询问用户。
  + -W或–verify 写入备份文件后，确认文件正确无误。
  + -x或--extract或--get：从备份文件中还原文件；
  + -t或--list：列出备份文件的内容；
  + -z或--gzip或--ungzip：通过gzip指令处理备份文件；
  + -Z或--compress或--uncompress：通过compress指令处理备份文件；
  + -<设备编号><存储密度>  设置备份用的外围设备编号及存放数据的密度。
  + --after-date=<日期时间> 此参数的效果和指定”-N”参数相同。
  + --atime-preserve 不变更文件的存取时间。
  + --backup=<备份方式>或–backup 移除文件前先进行备份。
  + --checkpoint 读取备份文件时列出目录名称。
  + --concatenate 此参数的效果和指定”-A”参数相同。
  + --confirmation 此参数的效果和指定”-w”参数相同。
  + --delete 从备份文件中删除指定的文件。
  + --exclude=<范本样式> 排除符合范本样式的问家。
  + --group=<群组名称>  把加入设备文件中的文件的所属群组设成指定的群组。
  + --help 在线帮助。
  + --ignore-failed-read 忽略数据读取错误，不中断程序的执行。
  + --new-volume-script=<Script文件>  此参数的效果和指定”-F”参数相同。
  + --newer-mtime 只保存更改过的文件。
  + --no-recursion  不做递归处理，也就是指定目录下的所有文件及子目录不予处理。
  + --null 从null设备读取文件名称。
  + --numeric-owner 以用户识别码及群组识别码取代用户名称和群组名称。
  + --owner=<用户名称> 把加入备份文件中的文件的拥有者设成指定的用户。
  + --posix 将数据写入备份文件时使用POSIX格式。
  + --preserve 此参数的效果和指定”-ps”参数相同。
  + --preserve-order 此参数的效果和指定”-A”参数相同。
  + --preserve-permissions 此参数的效果和指定”-p”参数相同。
  + --record-size=<区块数目> 此参数的效果和指定”-b”参数相同。
  + --recursive-unlink 解开压缩文件还原目录之前，先解除整个目录下所有文件的连接。
  + --remove-files 文件加入备份文件后，就将其删除。
  + --rsh-command=<执行指令> 设置要在远端主机上执行的指令，以取代rsh指令。
  + --same-owner 尝试以相同的文件拥有者还原问家你。
  + --suffix=<备份字尾字符串> 移除文件前先行备份。
  + --totals 备份文件建立后，列出文件大小。
  + --use-compress-program=<执行指令> 通过指定的指令处理备份文件。
  + --version 显示版本信息。
  + --volno-file=<编号文件> 使用指定文件内的编号取代预设的卷册编号。

+ 参数：文件或目录：指定要打包的文件或目录列表。
+ 实例：
  + `-z`：有gzip属性的
  + `-j`：有bz2属性的
  + `-Z`：有compress属性的
  + `-v`：显示所有过程
  + `-O`：将文件解开到标准输出


+ 下面的参数-f是必须的
  + -f: 使用档案名字，切记，这个参数是最后一个参数，后面只能接档案名。
  ```
    tar -cf all.tar *.jpg
    # 这条命令是将所有.jpg的文件打成一个名为all.tar的包。-c是表示产生新的包，-f指定包的文件名。

    tar -rf all.tar *.gif
    # 这条命令是将所有.gif的文件增加到all.tar的包里面去。-r是表示增加文件的意思。

    tar -uf all.tar logo.gif
    # 这条命令是更新原来tar包all.tar中logo.gif文件，-u是表示更新文件的意思。

    tar -tf all.tar
    # 这条命令是列出all.tar包中所有文件，-t是列出文件的意思

    tar -cfv archive.tar foo bar  # 从文件foo和bar创建archive.tar。
    tar -tvf archive.tar         # 详细列出archive.tar中的所有文件。
    tar -xf archive.tar          # 从archive.tar提取所有文件。
  ``` 

+ zip格式
  + 压缩： zip -r [目标文件名].zip [原文件/目录名]
  + 解压： unzip [原文件名].zip
  + 注：-r参数代表递归

+ tar格式（该格式仅仅打包，不压缩）
  + 打包：tar -cvf [目标文件名].tar [原文件名/目录名]
  + 解包：tar -xvf [原文件名].tar
  + 注：c参数代表create（创建），x参数代表extract（解包），v参数代表verbose（详细信息），f参数代表filename（文件名），所以f后必须接文件名。

+ tar.gz格式
  + 方式一：利用前面已经打包好的tar文件，直接用压缩命令。
    + 压缩：gzip [原文件名].tar
    + 解压：gunzip [原文件名].tar.gz
  + 方式二：一次性打包并压缩、解压并解包
    + 打包并压缩： tar -zcvf [目标文件名].tar.gz [原文件名/目录名]
    + 解压并解包： tar -zxvf [原文件名].tar.gz
    + 注：z代表用gzip算法来压缩/解压。

+ tar.bz2格式
  + 方式一：利用已经打包好的tar文件，直接执行压缩命令：
    + 压缩：bzip2 [原文件名].tar
    + 解压：bunzip2 [原文件名].tar.bz2
  + 方式二：一次性打包并压缩、解压并解包
    + 打包并压缩： tar -jcvf [目标文件名].tar.bz2 [原文件名/目录名]
    + 解压并解包： tar -jxvf [原文件名].tar.bz2
    + 注：小写j代表用bzip2算法来压缩/解压。

+ tar.xz格式
  + 方式一：利用已经打包好的tar文件，直接用压缩命令：
    + 压缩：xz [原文件名].tar
    + 解压：unxz [原文件名].tar.xz
  + 方式二：一次性打包并压缩、解压并解包
    + 打包并压缩： tar -Jcvf [目标文件名].tar.xz [原文件名/目录名]
    + 解压并解包： tar -Jxvf [原文件名].tar.xz
    + 注：大写J代表用xz算法来压缩/解压。

+ jar格式
  + 压缩：jar -cvf [目标文件名].jar [原文件名/目录名]
  + 解压：jar -xvf [原文件名].jar

+ 7z格式
  + 压缩：7z a [目标文件名].7z [原文件名/目录名]
  + 解压：7z x [原文件名].7z
  + 注：这个7z解压命令支持rar格式

## df 

<!-- + df(disk free),命令用于显示目前在Linux系统上的文件系统磁盘的使用情况统计 -->

+ 简介：
  + df 是一个用于显示文件系统磁盘空间使用情况的常用命令。它可以告诉您有关磁盘分区或文件系统的容量、已用空间、可用空间和挂载点等信息

+ 语法：
```bash 
df [选项] [文件|目录]
```

+ 选项：
  + -a：显示所有文件系统，包括系统特殊文件系统。
  + -h：以易读的方式显示磁盘空间大小，以人类可读的单位（如 GB、MB）替代以字节为单位的大小。
  + -T：显示文件系统类型。
  + -i：显示索引节点的使用情况而不是磁盘块的使用情况。
  + -x 文件系统类型：排除指定类型的文件系统

+ 示例：
```bash 
# 显示所有挂载的文件系统的磁盘空间使用情况
df

# 显示所有文件系统的磁盘空间使用情况（包括特殊文件系统）
df -a

# 以易读的方式显示磁盘空间使用情况：
df -h

# 显示指定目录的磁盘空间使用情况
df /path/to/directory

# 显示指定文件的磁盘空间使用情况：
df /path/to/file

# 显示指定文件系统类型的磁盘空间使用情况
df -t ext4
```

+ 详解：
  + df 命令的输出包含以下列
  + 文件系统：文件系统的设备名称或路径。
  + 容量：文件系统的总容量。
  + 已用：已使用的磁盘空间量。
  + 可用：可用的磁盘空间量。
  + 已用%：已用空间的百分比。
  + 挂载点：文件系统所挂载的目录

## 中文语言包 

+ `apt-get install language-pack-zh-hans`

## du 

+ du(disk usage),命令用于显示目录或文件的大小
+ du会显示指定的目录或文件所占用的磁盘空间

在Linux中，`du`命令用于计算目录或文件的磁盘使用情况。它会递归地遍历指定的目录，并计算每个文件和子目录所占用的磁盘空间大小。`du`命令常用于查看文件和目录的大小，以便进行磁盘空间管理和优化。

以下是`du`命令的一般语法：

```
du [options] [directory/file]
```

其中，`options`是可选的一些选项，`directory/file`是要计算磁盘使用情况的目录或文件。

以下是一些常见的`du`命令选项和用法：

1. 计算目录的磁盘使用情况：
   ```
   du directory/
   ```

   此命令将递归地计算指定目录及其子目录的磁盘使用情况，并显示每个目录的大小。

2. 计算文件的磁盘使用情况：
   ```
   du file
   ```

   此命令将计算指定文件的磁盘使用情况，并显示其大小。

3. 以人类可读的格式显示磁盘使用情况：
   ```
   du -h directory/
   ```

   此命令将以可读的单位（如KB、MB、GB）显示磁盘使用情况。

4. 仅显示总的磁盘使用情况：
   ```
   du -sh directory/
   ```

   此命令将只显示指定目录的总磁盘使用情况，而不显示每个子目录的详细信息。

5. 排除某些文件或目录：
   ```
   du --exclude=pattern directory/
   ```

   此命令将排除符合指定模式的文件或目录，不计算它们的磁盘使用情况。

`du`命令还支持其他一些选项，如限制递归深度、显示每个文件的磁盘使用情况等。您可以使用`man du`命令查看完整的选项和用法说明。

总体而言，`du`命令是一个非常有用的工具，用于计算文件和目录的磁盘使用情况。它可以帮助您查找磁盘空间占用较大的文件和目录，以便进行磁盘空间管理和优化。

## useradd 

+ useradd, 用于建立用户账号
+ useradd可用来建立用户账号,账号建好之后,再用passwd设定账号的密码,用userdel删除账号,
+ 示例:
  + `useradd tt # 添加一般用户`
  + `useradd -g root tt  # 为添加的用户指定相应的用户组`
  + `useradd -r tt  # 创建一个系统用户`
  + `useradd -d /home/myd tt  # 为新添加的用户指定home目录`
  + `useradd caojh -u 544  # 建立用户并制定id`

在Linux中，`useradd`命令用于创建新用户账号。它是用于管理用户的基本命令之一。

以下是`useradd`命令的一般语法：

```
useradd [options] username
```

其中，`options`是可选的一些选项，`username`是要创建的新用户的用户名。

以下是一些常见的`useradd`命令选项和用法：

1. 创建新用户：
   ```
   useradd username
   ```

   此命令将创建一个新用户账号，并使用指定的用户名。

2. 指定用户ID（UID）：
   ```
   useradd -u uid username
   ```

   此命令将为新用户指定一个特定的用户ID（UID）。如果未指定，系统会自动分配一个唯一的UID。

3. 指定用户所属的初始组：
   ```
   useradd -g groupname username
   ```

   此命令将指定新用户所属的初始组。如果未指定，将使用与用户名相同的组。

4. 指定用户的主目录：
   ```
   useradd -d homedir username
   ```

   此命令将为新用户指定一个特定的主目录。如果未指定，系统将创建一个与用户名相同的目录。

5. 创建用户并指定登录Shell：
   ```
   useradd -s shell username
   ```

   此命令将为新用户指定一个特定的登录Shell。如果未指定，将使用系统默认的Shell。

`useradd`命令还支持其他一些选项，如设置用户的密码、指定用户的备注信息等。您可以使用`man useradd`命令查看完整的选项和用法说明。

请注意，使用`useradd`命令仅创建用户账号，不会自动创建密码或设置用户的权限和访问控制。您可能需要使用其他命令，如`passwd`和`usermod`，来设置密码和修改用户的属性。

## userdel 

+ 命令用于删除用户账号
+ userdel可删除用户账号与相关的文件,若不加参数,则仅删除用户账号,而不删除相关文件
+ `userdel -r username`

在Linux中，`userdel`命令用于删除用户账号。它是用于管理用户的基本命令之一。

以下是`userdel`命令的一般语法：

```
userdel [options] username
```

其中，`options`是可选的一些选项，`username`是要删除的用户账号的用户名。

以下是一些常见的`userdel`命令选项和用法：

1. 删除用户账号：
   ```
   userdel username
   ```

   此命令将删除指定用户名的用户账号。注意，这只会删除用户账号本身，不会删除用户的主目录或其他相关文件。

2. 删除用户账号及其主目录：
   ```
   userdel -r username
   ```

   此命令将删除指定用户名的用户账号，并且同时删除用户的主目录及其内容。

`userdel`命令还支持其他一些选项，如指定用户的辅助组保留其文件、强制删除用户账号等。您可以使用`man userdel`命令查看完整的选项和用法说明。

请注意，删除用户账号可能会导致与该用户相关的文件和权限失效。在删除用户账号之前，请确保您了解其影响，并根据需要备份相关文件。

## usermod 

+ usermod,命令用于修改用户账号的各项设定
在Linux中，`usermod`命令用于修改用户账号的属性。它可以用于更改用户账号的各种设置，如用户名、用户ID、所属组、主目录等。

以下是`usermod`命令的一般语法：

```
usermod [options] username
```

其中，`options`是可选的一些选项，`username`是要修改属性的用户账号的用户名。

以下是一些常见的`usermod`命令选项和用法：

1. 修改用户名：
   ```
   usermod -l new_username username
   ```

   此命令将将指定用户名的用户账号修改为新的用户名。

2. 修改用户ID（UID）：
   ```
   usermod -u new_uid username
   ```

   此命令将为指定用户名的用户账号修改用户ID（UID）为新的UID。

3. 修改用户所属的初始组：
   ```
   usermod -g new_groupname username
   ```

   此命令将将指定用户名的用户账号修改为新的初始组。

4. 修改用户主目录：
   ```
   usermod -d new_homedir username
   ```

   此命令将将指定用户名的用户账号修改为新的主目录。

5. 修改用户的登录Shell：
   ```
   usermod -s new_shell username
   ```

   此命令将将指定用户名的用户账号修改为新的登录Shell。

`usermod`命令还支持其他一些选项，如设置密码过期时间、添加或删除用户的附加组、锁定或解锁用户账号等。您可以使用`man usermod`命令查看完整的选项和用法说明。

请注意，在修改用户账号属性之前，请谨慎操作，并确保了解其影响。某些修改可能会影响用户的文件和权限访问。

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

在Linux中，`grep`是一个强大的文本搜索工具，用于在文件中查找指定模式的文本行。`grep`命令通常与其他命令结合使用，以便在大量文本数据中过滤出所需的内容。

以下是`grep`命令的一般语法：

```
grep [options] pattern [file(s)]
```

其中，`options`是可选的一些选项，`pattern`是要搜索的模式，`file(s)`是要搜索的文件列表。

以下是一些常见的`grep`命令选项和用法：

1. 在单个文件中搜索模式：
   ```
   grep pattern file
   ```

   此命令将在指定的文件中搜索匹配指定模式的文本行，并将其输出到标准输出。

2. 在多个文件中搜索模式：
   ```
   grep pattern file1 file2
   ```

   此命令将在多个文件中搜索匹配指定模式的文本行，并将其输出到标准输出。

3. 递归地搜索目录中的文件：
   ```
   grep -r pattern directory
   ```

   此命令将递归地搜索指定目录中的所有文件，查找匹配指定模式的文本行。

4. 忽略大小写：
   ```
   grep -i pattern file
   ```

   此命令将在搜索时忽略模式的大小写。

5. 显示匹配行的行号：
   ```
   grep -n pattern file
   ```

   此命令将显示匹配行的行号。

6. 反向搜索（显示不匹配的行）：
   ```
   grep -v pattern file
   ```

   此命令将显示不匹配指定模式的文本行。

`grep`命令还支持其他一些选项和功能，如正则表达式匹配、显示匹配的上下文行、统计匹配的行数等。您可以使用`man grep`命令查看完整的选项和用法说明。

`grep`命令是一个非常强大和灵活的文本搜索工具，可用于在文件和目录中快速查找匹配特定模式的内容。

## eval 

+ eval,命令用于重新运算求出参数的内容
+ eval可读取一连串的参数,然后再依参数本身的特性来执行
+ 在shell脚本中,用eval加命令来执行linux命令

在Linux中，`eval`命令用于将参数作为Shell命令执行，并将结果返回到当前Shell环境中。它将参数解析为Shell表达式并执行，可以用于动态地生成和执行命令。

以下是`eval`命令的一般语法：

```
eval [options] command
```

其中，`options`是可选的一些选项，`command`是要执行的命令或表达式。

`eval`命令在执行时会对`command`进行两次解析。首先，它会对`command`进行参数展开、命令替换和变量替换。然后，将解析后的结果作为Shell命令执行。

以下是一些`eval`命令的常见用法：

1. 执行动态命令：
   ```
   eval "$command"
   ```

   此命令将执行存储在`$command`变量中的动态命令。变量中的命令将被解析并执行。

2. 执行包含变量的命令：
   ```
   eval "echo $var"
   ```

   此命令将对变量`$var`进行变量替换，并将结果作为命令执行。换句话说，它将打印出变量`$var`的值。

`eval`命令的主要用途是动态地构建和执行命令，可以在脚本中生成复杂的命令行操作。但需要注意，使用`eval`命令要谨慎，确保参数的来源可信，以避免安全风险。

## mount 

+ intr 参数:允许通知中断一个NFS调用.当服务器没有应答需要放弃的时候有用

在Linux中，`mount`命令用于将文件系统挂载到指定的挂载点上，使得文件系统中的内容可以被访问和使用。挂载是将存储设备或其他文件系统连接到文件树的过程。

以下是`mount`命令的一般语法：

```
mount [options] device_or_file mount_point
```

其中，`options`是可选的一些选项，`device_or_file`是要挂载的设备或文件，`mount_point`是挂载点，即文件系统将被挂载到的目录。

以下是一些常见的`mount`命令选项和用法：

1. 挂载设备：
   ```
   mount /dev/sdb1 /mnt
   ```

   此命令将将`/dev/sdb1`设备上的文件系统挂载到`/mnt`目录。

2. 挂载网络文件系统（NFS）：
   ```
   mount -t nfs server:/share /mnt
   ```

   此命令将将远程NFS服务器上的共享文件系统挂载到`/mnt`目录。

3. 挂载ISO映像文件：
   ```
   mount -o loop image.iso /mnt
   ```

   此命令将将名为`image.iso`的ISO映像文件挂载到`/mnt`目录。使用`-o loop`选项表示将ISO文件作为循环设备挂载。

`mount`命令还支持其他一些选项，如指定文件系统类型、设置挂载选项、设置权限等。您可以使用`man mount`命令查看完整的选项和用法说明。

使用`mount`命令可以在Linux系统中临时或永久地挂载文件系统，以便访问其内容。挂载的文件系统将在挂载点下可见，并可通过该挂载点进行文件和目录操作。

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

在Linux中，`export`命令用于设置环境变量。环境变量是在Shell会话中可用的全局变量，它们包含了对系统行为和配置起作用的值。

以下是`export`命令的一般语法：

```
export [option] variable=value
```

其中，`option`是可选的一些选项，`variable`是要设置的环境变量的名称，`value`是要分配给该环境变量的值。

以下是一些常见的`export`命令选项和用法：

1. 设置环境变量：
   ```
   export VARIABLE=value
   ```

   此命令将设置名为`VARIABLE`的环境变量，并将其值设置为`value`。

2. 查看当前环境变量：
   ```
   export
   ```

   此命令将列出当前所有已设置的环境变量及其值。

3. 设置多个环境变量：
   ```
   export VAR1=value1 VAR2=value2 VAR3=value3
   ```

   此命令将一次性设置多个环境变量，并为每个变量指定一个值。

环境变量在Shell会话中起作用，它们可以用于配置系统行为、定义路径、设置临时变量等。通过`export`命令设置的环境变量可以在当前Shell会话及其子进程中访问。

请注意，通过`export`命令设置的环境变量在Shell会话结束时会失效。如果您希望永久性地设置环境变量，可以将其添加到Shell配置文件（如`.bashrc`或`.profile`）中。

## awk  

+ AWK,是一种处理文本文件的语言,是一个强大的文本分析工具
+ 语法:`awk [选项参数] 'script' var=value file(s)` 或者 `awk [选项参数] -f scriptfile var=value file(s)`
+ 基本用法
  + `awk '{[pattern] action}' {filenames}` , 行匹配语句 `awk ''` 只能用单引号
  + `awk '{print $1, $4}' log.txt`, 每行按空格或TAB分割,输出文本的1,4项
  + `awk -F`, -F相当于内置变量FS,指定分割字符
  + `awk -v` ,设置变量
  + awk -f {awk脚本} {文件名}

在Linux中，`awk`命令是一种强大的文本处理工具，用于从文本文件中提取和处理数据。它读取输入文件的每一行，按照指定的模式进行匹配，并执行相应的操作。

以下是`awk`命令的一般语法：

```
awk 'pattern { action }' input_file
```

其中，`pattern`是用于匹配文本行的条件，`action`是要执行的操作，`input_file`是要处理的输入文件。

以下是一些常见的`awk`命令的用法：

1. 打印文件的某一列：
   ```
   awk '{ print $2 }' input_file
   ```

   此命令将打印输入文件中的每一行的第二列。

2. 使用条件过滤行：
   ```
   awk '$3 > 10 { print }' input_file
   ```

   此命令将打印输入文件中第三列大于10的行。

3. 计算行数、列数或总和：
   ```
   awk 'END { print NR }' input_file
   ```

   此命令将打印输入文件中的行数。

`awk`命令还支持其他一些高级功能，如使用正则表达式进行模式匹配、定义变量和函数、处理字段分隔符等。您可以根据需要使用更复杂的`awk`脚本进行数据处理。

请注意，`awk`命令可以与管道符号（`|`）和其他命令一起使用，以实现更复杂的数据处理任务。

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

在Linux中，`sed`命令是一种流编辑器，用于对文本进行流式处理和转换。它读取输入文本的每一行，根据指定的规则进行模式匹配和替换操作，并将处理后的文本输出到标准输出或指定的文件中。

以下是`sed`命令的一般语法：

```
sed [options] 'command' input_file
```

其中，`options`是可选的一些选项，`command`是要执行的`sed`命令，`input_file`是要处理的输入文件。

以下是一些常见的`sed`命令选项和用法：

1. 替换文本：
   ```
   sed 's/pattern/replacement/' input_file
   ```

   此命令将输入文件中的每一行，将匹配`pattern`的内容替换为`replacement`。

2. 删除行：
   ```
   sed '3d' input_file
   ```

   此命令将删除输入文件中的第三行。

3. 使用正则表达式进行匹配：
   ```
   sed -n '/pattern/p' input_file
   ```

   此命令将仅打印匹配正则表达式`pattern`的行。

`sed`命令还支持其他一些高级功能，如全局替换、插入、追加和删除文本行，条件执行等。您可以使用不同的`sed`命令和选项来完成各种文本处理任务。

请注意，`sed`命令是一种非交互式的编辑器，它将按照指定的命令对输入文本进行处理，并将结果输出到标准输出或指定的文件中。它不会修改原始文件，除非您使用重定向符号（`>`）将输出重定向到原始文件。

## whereis  

+ 检查二进制文件和库文件的位置
  + `whereis systemctl`

在Linux中，`whereis`命令用于定位可执行程序、源代码文件和帮助文档的位置。它提供了一个简单的方法来查找特定命令或文件在系统中的位置。

以下是`whereis`命令的一般语法：

```
whereis [options] command
```

其中，`options`是可选的一些选项，`command`是要查找的命令或文件。

以下是一些常见的`whereis`命令选项和用法：

1. 查找可执行程序：
   ```
   whereis ls
   ```

   此命令将显示`ls`命令的可执行程序位置。

2. 查找源代码文件：
   ```
   whereis grep
   ```

   此命令将显示`grep`命令的源代码文件位置。

3. 查找帮助文档：
   ```
   whereis man
   ```

   此命令将显示`man`命令的帮助文档位置。

`whereis`命令会搜索特定文件类型的位置，并显示相关信息，包括可执行程序、源代码和帮助文档的路径。它会搜索系统默认的搜索路径，如`/bin`、`/usr/bin`等。

请注意，`whereis`命令仅搜索已经建立索引的文件和路径，因此可能无法找到某些文件。另外，它不会搜索用户自定义的路径或目录。

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
 
在Linux中，`chown`命令用于修改文件或目录的所有者（owner）。它允许管理员将文件或目录的所有权转移给其他用户或用户组。

以下是`chown`命令的一般语法：

```
chown [options] owner[:group] file(s)
```

其中，`options`是可选的一些选项，`owner`是要设置的新所有者的用户名或用户ID，`group`是要设置的新所属组的组名或组ID，`file(s)`是要修改所有者的文件或目录列表。

以下是一些常见的`chown`命令选项和用法：

1. 修改文件所有者：
   ```
   chown user1 file.txt
   ```

   此命令将将`file.txt`文件的所有者设置为`user1`。

2. 修改文件所属组：
   ```
   chown :group1 file.txt
   ```

   此命令将将`file.txt`文件的所属组设置为`group1`，而不修改所有者。

3. 修改文件所有者和所属组：
   ```
   chown user1:group1 file.txt
   ```

   此命令将将`file.txt`文件的所有者设置为`user1`，所属组设置为`group1`。

`chown`命令还支持其他一些选项，如递归修改目录及其子文件的所有者、通过用户ID或组ID设置所有者等。

请注意，只有管理员或文件所有者才能使用`chown`命令修改文件的所有者。此外，一些特殊文件和目录（如系统文件）可能受到权限限制，不允许普通用户修改所有者。

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