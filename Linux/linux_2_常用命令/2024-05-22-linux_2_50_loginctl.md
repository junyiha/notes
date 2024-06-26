---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_50_loginctl
tag: LinuxCommand
---
## 简介

+ loginctl命令

## linux loginctl命令 详解

`loginctl` 是一个用于查看和管理用户登录会话的 systemd 工具。它提供了一种方式来检查和控制登录到系统的用户，以及相关的会话和底层的 seat、控制组（cgroup）等信息。以下是一些常用的 `loginctl` 命令以及它们的详解：

1. **列出当前登录的用户：**
   ```bash
   loginctl list-sessions
   ```
   列出当前系统上的用户登录会话。

2. **显示所有座位（seat）信息：**
   ```bash
   loginctl list-seats
   ```
   列出系统上所有的座位，一个座位通常对应一个物理控制台或虚拟控制台。

3. **显示指定用户的登录会话信息：**
   ```bash
   loginctl show-session <session_id>
   ```
   显示指定用户登录会话的详细信息，其中 `<session_id>` 是登录会话的 ID。

4. **显示座位的详细信息：**
   ```bash
   loginctl show-seat <seat_id>
   ```
   显示指定座位的详细信息，其中 `<seat_id>` 是座位的 ID。

5. **显示用户的座位信息：**
   ```bash
   loginctl show-user <user_name>
   ```
   显示指定用户的座位信息，其中 `<user_name>` 是用户名。

6. **显示所有活动的座位和登录会话：**
   ```bash
   loginctl list-users
   ```
   列出当前系统上所有活动的用户及其座位信息。

7. **结束用户的登录会话：**
   ```bash
   loginctl terminate-session <session_id>
   ```
   结束指定用户的登录会话，其中 `<session_id>` 是登录会话的 ID。

8. **结束座位上的所有登录会话：**
   ```bash
   loginctl terminate-seat <seat_id>
   ```
   结束指定座位上的所有登录会话，其中 `<seat_id>` 是座位的 ID。

9. **显示控制组（cgroup）信息：**
   ```bash
   loginctl show-session <session_id> -p ControlGroup
   ```
   显示指定用户登录会话所属的 cgroup。

10. **显示登录会话的相关进程信息：**
    ```bash
    loginctl session-status <session_id>
    ```
    显示指定用户登录会话的进程和资源信息。

11. **以树状结构显示用户登录信息：**
    ```bash
    loginctl tree
    ```
    以树状结构显示用户登录信息，包括座位、用户和登录会话的层次结构。

`loginctl` 提供了一种方便的方式来查看和管理用户登录会话，尤其在多用户环境中或涉及到控制台切换的情况下非常有用。通过这些命令，管理员可以实时监控用户的登录情况，同时也可以进行会话的管理和控制。

## linux loginctl命令 常用技巧

以下是一些在使用 `loginctl` 命令时的常用技巧：

1. **结合 `--output` 选项显示指定字段：**
   ```bash
   loginctl show-session <session_id> --output=FIELD
   ```
   使用 `--output` 选项可以只显示指定的字段，替换 `<session_id>` 为相应的登录会话 ID，`FIELD` 为要显示的字段，例如 `State`、`User`、`Seat` 等。

2. **使用 `--value` 选项仅显示值而不显示字段名：**
   ```bash
   loginctl show-session <session_id> --value
   ```
   使用 `--value` 选项可以只显示字段的值而不显示字段名。

3. **显示详细的用户信息：**
   ```bash
   loginctl show-user <user_name> --all
   ```
   使用 `--all` 选项可以显示更详细的用户信息，包括座位、UID、GID 等。

4. **过滤显示活动用户的座位信息：**
   ```bash
   loginctl list-users --property=Seats
   ```
   使用 `--property` 选项可以过滤显示用户信息中的特定属性，如 `Seats`。

5. **结合 `grep` 进行筛选：**
   ```bash
   loginctl list-sessions | grep <filter_condition>
   ```
   使用 `grep` 命令结合 `list-sessions` 可以根据某个条件过滤显示登录会话。

6. **使用 `--quiet` 选项减少输出：**
   ```bash
   loginctl list-users --quiet
   ```
   使用 `--quiet` 选项可以减少输出，仅显示关键信息。

7. **显示登录会话的最近活动时间：**
   ```bash
   loginctl show-session <session_id> -p IdletimeHint
   ```
   使用 `-p` 选项可以指定显示特定属性，例如 `IdletimeHint` 显示登录会话的最近空闲时间。

8. **显示用户登录会话的进程信息：**
   ```bash
   loginctl session-status <session_id> --full
   ```
   使用 `--full` 选项可以显示更详细的用户登录会话进程信息。

9. **以 JSON 格式输出信息：**
   ```bash
   loginctl --quiet --output=json list-users
   ```
   使用 `--output=json` 选项可以以 JSON 格式输出信息，方便后续处理。

10. **结合 `watch` 实时监控：**
    ```bash
    watch -n 1 loginctl list-sessions
    ```
    使用 `watch` 命令可以实时监控登录会话的变化，每秒更新一次。

这些技巧可以帮助你更灵活地使用 `loginctl` 命令，根据实际需求定制输出，过滤信息，以及实时监控用户登录情况。记住根据具体情况选择合适的选项和参数。

## loginctl 

`loginctl` 是一个用于管理登录会话和用户登录状态的命令行工具。它是 systemd 的一部分，用于控制 Linux 系统上的用户登录和会话管理。

以下是一些常用的 `loginctl` 命令及其功能：

- `loginctl list-sessions`：列出当前活动的登录会话。它会显示每个会话的 ID、用户、登录时间等信息。
- `loginctl show-session <session_id>`：显示指定会话的详细信息，包括会话状态、登录用户、登录时间等。
- `loginctl list-users`：列出当前活动的用户。它会显示每个用户的 ID、用户名等信息。
- `loginctl show-user <user_id>`：显示指定用户的详细信息，包括用户状态、默认会话、上次登录时间等。
- `loginctl session-status`：显示当前登录用户的会话状态和详细信息。
- `loginctl user-status`：显示当前用户的状态和详细信息。
- `loginctl lock-session`：锁定当前会话。这会使屏幕进入锁定状态，要解锁屏幕，需要提供用户密码。
- `loginctl unlock-session`：解锁当前会话。这会解除屏幕锁定状态。

除了上述命令之外，`loginctl` 还提供其他一些管理登录会话和用户的功能，如关闭用户会话、终止登录会话、设置默认会话等。你可以通过 `man loginctl` 命令查看更多详细信息和可用选项。

需要注意的是，`loginctl` 命令需要 root 或具有适当权限的用户才能执行。它在使用 systemd 作为 init 系统的 Linux 发行版中可用。