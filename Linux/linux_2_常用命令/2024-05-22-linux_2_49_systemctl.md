---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_49_systemctl
tag: LinuxCommand
---
## 简介

+ systemctl命令

## linux systemctl命令 详解

`systemctl` 是 Linux 系统中用于管理系统服务（system services）和套接字（sockets）的命令。它是 systemd 系统管理守护进程的一部分，负责启动、停止、重启和管理系统服务。以下是一些常用的 `systemctl` 命令以及它们的详解：

1. **启动一个服务：**
   ```bash
   systemctl start <service_name>
   ```
   启动指定名称的服务。

2. **停止一个服务：**
   ```bash
   systemctl stop <service_name>
   ```
   停止指定名称的服务。

3. **重启一个服务：**
   ```bash
   systemctl restart <service_name>
   ```
   重启指定名称的服务。

4. **查看服务状态：**
   ```bash
   systemctl status <service_name>
   ```
   显示指定名称的服务的当前状态，包括是否正在运行以及相关的信息。

5. **启用服务开机自启：**
   ```bash
   systemctl enable <service_name>
   ```
   设置指定名称的服务在系统启动时自动启动。

6. **禁用服务开机自启：**
   ```bash
   systemctl disable <service_name>
   ```
   取消指定名称的服务在系统启动时自动启动。

7. **显示所有已加载的服务：**
   ```bash
   systemctl list-units --type=service
   ```
   列出所有已加载的服务及其状态。

8. **显示所有已启用的服务：**
   ```bash
   systemctl list-unit-files --type=service | grep enabled
   ```
   列出所有已启用的服务。

9. **显示服务的依赖关系：**
   ```bash
   systemctl list-dependencies <service_name>
   ```
   显示指定服务的依赖关系。

10. **重新加载服务配置：**
    ```bash
    systemctl reload <service_name>
    ```
    重新加载指定服务的配置文件，不会停止服务。

11. **显示系统的引导目标（target）：**
    ```bash
    systemctl get-default
    ```
    显示系统当前的引导目标。

12. **更改系统的引导目标：**
    ```bash
    systemctl set-default <target_name>
    ```
    设置系统的引导目标。

这些是一些常见的 `systemctl` 命令，可以帮助你管理和维护系统服务。通过结合这些命令，你可以轻松地启动、停止、重启服务，管理它们的开机自启设置，并查看相关的状态和依赖关系。

## linux systemctl命令 常用技巧

除了基本的 `systemctl` 命令之外，以下是一些常用的技巧和进阶用法：

1. **模糊搜索服务：**
   ```bash
   systemctl list-units --type=service | grep <keyword>
   ```
   使用 `grep` 命令结合 `list-units` 来进行模糊搜索服务，替换 `<keyword>` 为你感兴趣的关键字。

2. **显示服务的详细信息：**
   ```bash
   systemctl show <service_name>
   ```
   显示指定服务的详细信息，包括配置文件路径、依赖关系等。

3. **查看引导目标的详细信息：**
   ```bash
   systemctl show default.target
   ```
   显示当前引导目标的详细信息。

4. **过滤显示服务状态：**
   ```bash
   systemctl --state=active
   ```
   使用 `--state` 选项过滤显示服务的状态，例如，只显示正在运行的服务。

5. **查看服务的日志：**
   ```bash
   journalctl -u <service_name>
   ```
   使用 `journalctl` 命令查看指定服务的日志，替换 `<service_name>` 为你感兴趣的服务。

6. **查看最近的引导日志：**
   ```bash
   journalctl -xe
   ```
   查看最近的引导日志，用于排查系统启动时可能遇到的问题。

7. **查看引导目标的依赖关系：**
   ```bash
   systemctl list-dependencies multi-user.target
   ```
   显示指定引导目标的依赖关系。

8. **使用通配符进行操作：**
   ```bash
   systemctl restart 'nginx*'
   ```
   使用通配符 `*` 来一次性操作符合条件的多个服务。

9. **查看系统启动时间：**
   ```bash
   systemd-analyze
   ```
   查看系统的启动时间及关键步骤，可以使用 `systemd-analyze blame` 查看各个服务的启动耗时。

10. **启动失败服务的故障排查：**
    ```bash
    systemctl status <service_name> -l
    ```
    使用 `-l` 选项显示更多详细的日志信息，有助于排查启动失败的服务问题。

11. **使用用户级服务：**
    ```bash
    systemctl --user start <service_name>
    ```
    对于用户级服务，可以使用 `--user` 选项来管理。

这些技巧可以帮助你更高效地使用 `systemctl` 命令，进行服务管理和故障排查。记住在使用系统管理命令时要小心，确保了解命令的影响和安全性。

## linux systemctl命令 高级技巧

以下是一些 `systemctl` 命令的高级技巧，适用于更深入的系统管理和故障排查：

1. **使用 `--quiet` 选项：**
   ```bash
   systemctl --quiet start <service_name>
   ```
   使用 `--quiet` 选项可以使 `systemctl` 命令输出更加简洁，只显示关键信息。

2. **使用 `--failed` 选项查看失败的服务：**
   ```bash
   systemctl --failed
   ```
   列出所有启动失败的服务，方便快速定位问题。

3. **查看服务的所有相关日志：**
   ```bash
   journalctl -u <service_name> --no-pager
   ```
   使用 `--no-pager` 选项可以直接在终端中显示所有相关日志，而不是通过分页器。

4. **手动启动服务：**
   ```bash
   systemctl --no-pager --quiet start <service_name>
   ```
   使用 `--no-pager` 选项可以避免 `systemctl` 命令使用分页器，而 `--quiet` 则可以减少输出。

5. **显示服务的详细依赖树：**
   ```bash
   systemctl list-dependencies --all <service_name>
   ```
   显示服务的详细依赖树，包括所有被依赖的服务。

6. **使用 `--force` 选项强制操作：**
   ```bash
   systemctl --force restart <service_name>
   ```
   使用 `--force` 选项可以强制执行某些操作，如强制重启服务。

7. **查看系统引导的时间线：**
   ```bash
   systemd-analyze plot > timeline.svg
   ```
   生成引导时间线图，以 SVG 格式保存在文件中，用于可视化系统引导的整个过程。

8. **查看服务启动的时间线：**
   ```bash
   systemd-analyze critical-chain <service_name>
   ```
   查看指定服务启动所花费的时间和关键步骤。

9. **查看用户单元的状态：**
   ```bash
   systemctl --user status
   ```
   查看用户级服务单元的状态，包括用户自定义的服务。

10. **查看服务单元的所有属性：**
    ```bash
    systemctl show <service_name> --all
    ```
    显示指定服务单元的所有属性，包括默认值和用户自定义值。

11. **使用 `systemd-cgtop` 监控进程和资源：**
    ```bash
    sudo systemd-cgtop
    ```
    以实时方式监控系统中的控制组（cgroup）信息，包括进程数、CPU 使用情况等。

这些高级技巧可以帮助你更深入地理解和利用 `systemctl` 命令，用于更复杂的系统管理任务和故障排查。请确保在使用这些命令时理解其影响，并根据需要适度使用。

## systemctl 

Systemd 是 Linux 系统中广泛使用的 init 系统和服务管理器。`systemctl` 是 Systemd 的主要命令，用于管理系统服务。下面是一些常用的 `systemctl` 命令及其功能：

1. 启动和停止服务：
   - 启动一个服务：`sudo systemctl start servicename`
   - 停止一个服务：`sudo systemctl stop servicename`
   - 重启一个服务：`sudo systemctl restart servicename`
   - 查看服务的状态：`sudo systemctl status servicename`

2. 禁用和启用服务的自启动：
   - 禁用一个服务的自启动：`sudo systemctl disable servicename`
   - 启用一个服务的自启动：`sudo systemctl enable servicename`

3. 查看服务列表：
   - 列出所有运行中的服务：`sudo systemctl list-units --type=service --state=running`
   - 列出所有已启用的服务：`sudo systemctl list-unit-files --type=service --state=enabled`

4. 查看日志：
   - 查看一个服务的日志：`sudo journalctl -u servicename`
   - 查看系统日志：`sudo journalctl`

5. 查看和切换系统运行级别（target）：
   - 查看当前运行级别：`sudo systemctl get-default`
   - 切换运行级别到图形界面：`sudo systemctl set-default graphical.target`
   - 切换运行级别到多用户文本界面：`sudo systemctl set-default multi-user.target`

6. 重新加载 Systemd 配置：
   - 重新加载 Systemd 配置：`sudo systemctl daemon-reload`

这些是一些常见的 `systemctl` 命令及其功能。`systemctl` 命令还有其他一些选项和功能，你可以使用 `man systemctl` 命令来查看完整的 `systemctl` 命令手册。

Systemd 提供了强大的服务管理功能，可以帮助你启动、停止、管理和监控系统服务。使用 `systemctl` 命令可以方便地执行这些操作，并管理系统的运行级别和自启动行为。