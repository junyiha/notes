## 简介

+ Linux系统下理论基础知识笔记

## 特殊字符  

+ `$#`, 传递到脚本或函数的参数个数
+ `$*`, 以一个单字符串显示所有向脚本传递的参数
+ `$$`, 脚本运行的当前进程ID号
+ `$!`, 后台运行的最后一个进程的ID号
+ `$@`, 与`$*`相同,但是使用时加引号,并在引号中返回每个参数
+ `$-`, 显示Shell使用的当前选项,与set命令功能相同
+ `$?`, 显示最后命令的退出状态,0表示没有错误,其他任何值表明有错误

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

## linux build-essential是什么

`build-essential` 是一个针对 Linux 系统的软件包集合，旨在提供编译和构建软件所需的基本工具和库。它通常包括一些核心的开发工具，如 `gcc` 编译器、`g++` 编译器、`make` 构建工具等。这些工具对于编译和构建大多数软件项目都是必需的。

在许多基于 Debian 的发行版（比如 Ubuntu）中，可以通过包管理器如 `apt` 来安装 `build-essential`。在安装了这个软件包之后，你就能够开始在你的 Linux 系统上编译和构建各种 C、C++ 或其他语言的程序。

## linux build-essential详解

`build-essential` 是针对 Debian 和基于 Debian 的 Linux 发行版（如 Ubuntu）的一个元包（meta-package），它捆绑了一系列用于软件编译和构建的基本工具和库。这个软件包的安装通常是在开始开发或编译源代码之前需要进行的一个重要步骤。

以下是 `build-essential` 软件包通常包含的一些主要组件：

1. **编译器**：
   - `gcc`：GNU Compiler Collection，用于编译 C 代码。
   - `g++`：GNU C++ 编译器，用于编译 C++ 代码。

2. **构建工具**：
   - `make`：一种自动化构建工具，通过 Makefile 文件管理源代码的编译和构建过程。
   - `dpkg-dev`：包含了构建 Debian 软件包所需的工具。

3. **库文件**：
   - `libc6-dev`：C 语言标准库的头文件和其他开发文件。
   - 其他可能需要的开发库文件，具体依赖于项目的需求。

安装 `build-essential` 软件包可以简化软件开发和编译过程，因为它提供了必要的工具和库，使用户能够在系统上直接编译和构建源代码而无需手动安装每个单独的组件。通过包管理器（如 `apt`）安装 `build-essential` 是相对简单和方便的。

要安装 `build-essential` 软件包，在终端中执行以下命令（假设你的系统使用的是 `apt` 包管理器）：

```bash
sudo apt update
sudo apt install build-essential
```

这样做会自动安装 `build-essential` 及其所包含的工具和库，使你可以立即开始进行软件开发、编译和构建工作。