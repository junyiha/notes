## 简介

+ Windows下常用命令

## windows net 命令 详解

Windows的`net`命令是一个用于管理网络连接和资源的命令行工具。它提供了一系列的子命令，用于执行各种网络相关的任务。以下是一些常见的`net`命令及其功能的详解：

1. `net use`：用于连接或断开网络共享资源。它的一些常见用法包括：

   - `net use drive_letter: \\computer\share`：将网络共享连接到本地驱动器。
   - `net use \\computer\share /delete`：断开与网络共享的连接。
   - `net use`：显示当前的网络连接。

2. `net view`：用于查看本地或远程计算机上的共享资源。例如，`net view \\computer`将列出远程计算机上的共享文件夹。

3. `net user`：用于管理Windows用户账户。一些常见用法包括：

   - `net user username`：显示有关指定用户的信息。
   - `net user username password /add`：添加新用户。
   - `net user username /delete`：删除用户。

4. `net group`：用于管理用户组。例如，`net group Administrators`将显示有关Administrators组的信息。

5. `net share`：用于管理本地计算机上的共享资源。例如，`net share sharename=folder_path`将共享指定文件夹。

6. `net send`：用于向其他计算机发送消息。这个命令已经在较新版本的Windows中不再支持，因为它的安全性方面存在问题。

7. `net start`和`net stop`：用于启动和停止Windows服务。例如，`net start servicename`将启动指定的服务。

8. `net time`：用于显示或设置计算机的时间。例如，`net time \\computer`将显示远程计算机的时间。

9. `net statistics`：用于查看网络统计信息，如连接数和数据包传输情况。

10. `net localgroup`：用于管理本地组，如添加或删除组成员。

11. `net use`：用于查看、添加和删除持久网络映射。

这些只是`net`命令的一些常见用法，Windows的`net`命令提供了更多功能和选项，可以通过在命令提示符中输入`net /?`来查看帮助信息，以获取更多详细的命令说明和选项列表。

## 查看账户

+ 查看所有账户
  + net user 

+ 查看指定账户的所有信息
  + net user zhangjunyi

## 启动ssh服务

+ net start sshd

## 常用命令

在 Windows 系统下，命令行（命令提示符、PowerShell 或 Windows Terminal）提供了许多常用的命令，用于执行各种任务。以下是一些常用的 Windows 命令行命令：

1. 文件和目录管理：
   - `dir`: 列出当前目录中的文件和子目录。
   - `cd`: 更改当前目录。
   - `mkdir`: 创建新目录。
   - `rmdir`: 删除目录。
   - `del`: 删除文件。
   - `copy`: 复制文件或目录。
   - `move`: 移动文件或目录。
   - `ren`: 重命名文件。

2. 系统信息和配置：
   - `systeminfo`: 显示关于计算机系统的详细信息，如操作系统版本、内存等。
   - `ipconfig`: 显示当前的网络配置信息，包括 IP 地址、子网掩码等。

3. 进程管理：
   - `tasklist`: 列出当前运行的进程。
   - `taskkill`: 终止运行中的进程。

4. 网络相关：
   - `ping`: 测试与另一台计算机的连接。
   - `tracert`: 跟踪数据包到目标主机的路由路径。
   - `nslookup`: 查询 DNS 解析信息。

5. 文件查看和编辑：
   - `type`: 显示文本文件的内容。
   - `more`: 逐页查看文本文件的内容。
   - `find`: 在文本文件中搜索字符串。
   - `edit`: 打开 MS-DOS 编辑器（仅限旧版本的 Windows）。
   - `notepad`: 打开记事本应用程序。

6. 其他实用工具：
   - `help`: 显示帮助信息，了解其他命令的用法。例如，使用 `help dir` 查看 `dir` 命令的帮助。
   - `cls`: 清屏。
   - `echo`: 输出文本或环境变量的值。
   - `date`: 显示或设置系统日期。
   - `time`: 显示或设置系统时间。

这些只是 Windows 命令行中的一部分常用命令。还有许多其他命令可用于执行各种任务。您可以在命令提示符下键入 `help` 或者加上命令名称来获取有关特定命令的更多帮助信息，例如 `help dir` 或者 `dir /?`。