## 简介

+ linux系统的常用技巧和方法

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