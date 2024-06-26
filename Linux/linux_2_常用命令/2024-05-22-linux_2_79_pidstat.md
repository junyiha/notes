---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_79_pidstat
tag: LinuxCommand
---
## 简介

+ pidstat命令

## linux pidstat命令 详解

`pidstat` 是一个 Linux 性能分析工具，用于监视进程的 CPU 使用情况、内存使用情况和其他系统资源。它属于 `sysstat` 工具包的一部分。以下是关于 `pidstat` 命令的详细解释：

### 1. **基本用法：**
```bash
pidstat [options] [interval] [count]
```
- `options`: 可选的命令选项，用于指定要监视的资源和显示的信息。
- `interval`: 指定输出的时间间隔，以秒为单位。
- `count`: 指定输出的次数，如果未指定，则会无限次输出。

### 2. **常用选项：**
- **CPU 相关：**
  - `-u` 或 `--cpu`: 显示 CPU 使用情况。
  - `-p PID` 或 `--pid=PID`: 仅监视指定进程ID的 CPU 使用情况。

- **内存相关：**
  - `-r` 或 `--memory`: 显示内存使用情况。

- **I/O 相关：**
  - `-d` 或 `--disk`: 显示磁盘 I/O 情况。
  - `-w` 或 `--io`: 显示 I/O 等待情况。

- **网络相关：**
  - `-n` 或 `--network`: 显示网络使用情况。

### 3. **示例用法：**
1. **显示所有进程的 CPU 使用情况：**
    ```bash
    pidstat -u
    ```

2. **显示指定进程ID的 CPU 使用情况：**
    ```bash
    pidstat -u -p PID
    ```

3. **显示所有进程的内存使用情况：**
    ```bash
    pidstat -r
    ```

4. **显示所有进程的磁盘 I/O 情况：**
    ```bash
    pidstat -d
    ```

5. **以指定时间间隔和次数显示 CPU 使用情况：**
    ```bash
    pidstat -u 2 5
    ```
    上述命令每2秒输出一次 CPU 使用情况，共输出5次。

### 4. **其他选项：**
- **`-h` 或 `--help`：** 显示帮助信息，列出可用的选项和参数。
- **`-V` 或 `--version`：** 显示 `pidstat` 的版本信息。

### 注意事项：
- `pidstat` 通常需要 `sysstat` 包的安装。在许多 Linux 发行版中，可以通过包管理器安装它。

`pidstat` 提供了丰富的信息，可以帮助你监视进程的性能，并及时发现潜在的性能问题。在使用时，根据具体的监控需求选择合适的选项。

## linux pidstat命令 常用技巧

以下是一些在使用 `pidstat` 命令时常用的技巧：

### 1. **监视指定进程的 CPU 使用情况：**
```bash
pidstat -u -p <PID>
```
通过指定 `-p` 选项和进程ID，可以监视特定进程的 CPU 使用情况。

### 2. **监视多个进程的 CPU 使用情况：**
```bash
pidstat -u -p <PID1,PID2,PID3>
```
通过逗号分隔的方式，可以同时监视多个进程的 CPU 使用情况。

### 3. **按指定时间间隔和次数输出结果：**
```bash
pidstat -u -r -p <PID> 2 5
```
此命令每2秒输出一次指定进程的 CPU 使用情况和内存使用情况，共输出5次。

### 4. **显示所有进程的 CPU 使用情况和命令行参数：**
```bash
pidstat -u -C <command>
```
通过 `-C` 选项，可以显示指定命令行参数的所有进程的 CPU 使用情况。

### 5. **显示指定用户的进程信息：**
```bash
pidstat -u -U <username>
```
使用 `-U` 选项，可以显示指定用户的所有进程的 CPU 使用情况。

### 6. **显示指定进程的线程信息：**
```bash
pidstat -t -p <PID>
```
通过 `-t` 选项，可以显示指定进程的线程信息，包括每个线程的 CPU 使用情况。

### 7. **输出到文件：**
```bash
pidstat -u -r -p <PID> 2 5 > output.txt
```
通过使用输出重定向，可以将 `pidstat` 的输出保存到文件中，以供后续分析。

### 8. **显示帮助信息：**
```bash
pidstat -h
```
使用 `-h` 选项可以查看 `pidstat` 命令的帮助信息，列出所有可用选项和参数。

### 9. **查看 `pidstat` 的版本信息：**
```bash
pidstat -V
```
使用 `-V` 选项可以显示 `pidstat` 的版本信息。

### 10. **使用交互式模式：**
```bash
pidstat -I
```
通过使用 `-I` 选项，可以启动交互式模式，允许用户在运行时切换显示的统计信息。

这些技巧可以帮助你更灵活地使用 `pidstat` 命令，根据具体需求选择合适的选项，并监视系统中进程的性能。

## Linux pidstat命令 详解

`pidstat` 是 Linux 系统上的一个性能分析工具，用于监视进程的资源使用情况。它属于 sysstat 工具包，通过收集和显示各个进程的统计信息，帮助系统管理员和开发人员了解系统上的进程行为和性能状况。以下是对 `pidstat` 命令的详细解释：

### 1. 安装 sysstat 工具包

在大多数 Linux 发行版上，`pidstat` 都是 sysstat 工具包的一部分。如果尚未安装，可以使用以下命令安装：

```bash
sudo apt-get install sysstat    # 对于 Debian/Ubuntu
sudo yum install sysstat        # 对于 CentOS/RHEL
```

### 2. `pidstat` 基本语法

```bash
pidstat [options] [interval [count]]
```

- **options**: `pidstat` 的各种选项，用于指定输出的格式和内容。
- **interval**: 采样的时间间隔（以秒为单位），表示 `pidstat` 将在这个时间间隔内对系统进行一次采样。
- **count**: 采样的次数，表示 `pidstat` 将在指定次数的采样后停止。

### 3. 常用选项

以下是一些常用的 `pidstat` 选项：

- **-u**: 显示 CPU 使用情况。
- **-r**: 显示内存使用情况。
- **-d**: 显示磁盘 I/O 情况。
- **-w**: 显示上下文切换和进程切换情况。
- **-p PID**: 指定要监视的进程ID，可以指定多个 PID。

### 4. 使用示例

#### 4.1 显示 CPU 使用情况

```bash
pidstat -u
```

#### 4.2 显示内存使用情况

```bash
pidstat -r
```

#### 4.3 显示磁盘 I/O 情况

```bash
pidstat -d
```

#### 4.4 显示上下文切换和进程切换情况

```bash
pidstat -w
```

#### 4.5 指定要监视的特定进程

```bash
pidstat -u -p PID
```

### 5. 输出解释

`pidstat` 的输出包含多列信息，其中一些关键列如下：

- **PID**: 进程ID。
- **%usr**: 用户空间 CPU 使用百分比。
- **%system**: 内核空间 CPU 使用百分比。
- **%CPU**: 进程的总 CPU 使用百分比。
- **minflt/s**: 每秒的次缺页错误数。
- **majflt/s**: 每秒的主缺页错误数。
- **VSZ**: 进程的虚拟内存大小（KB）。
- **RSS**: 进程的驻留集大小（KB）。
- **Command**: 进程的命令名称。

### 6. 其他信息

- `pidstat` 还支持许多其他选项，可以通过 `man pidstat` 命令查看完整的手册。

- 可以使用 `pidstat` 来监视系统上运行的各个进程，以便及时发现和解决性能问题。

这只是 `pidstat` 命令的基本介绍，更详细的信息可以参考 `man pidstat` 或者 `pidstat --help`。