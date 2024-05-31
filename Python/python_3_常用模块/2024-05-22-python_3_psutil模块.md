---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_3_psutil模块
tag: Python
---
## 简介

+ psutil模块笔记

## python3 psutil 模块 详解

`psutil` 是一个用于检索有关系统进程和系统利用率（CPU、内存、磁盘、网络等）的 Python 模块。它提供了一个简单且跨平台的接口，使得在不同操作系统上获取系统信息变得更加容易。以下是对 `psutil` 模块的一些常见用法的详解：

### 安装

你可以使用以下命令来安装 `psutil` 模块：

```bash
pip install psutil
```

### 基本用法

1. **获取 CPU 信息:**

```python
import psutil

# 获取 CPU 核心数量
cpu_count = psutil.cpu_count(logical=False)  # 物理核心数
logical_cpu_count = psutil.cpu_count(logical=True)  # 逻辑核心数

# 获取 CPU 使用率
cpu_usage = psutil.cpu_percent(interval=1)  # 指定时间间隔内的 CPU 使用率
print(f"Physical CPU Count: {cpu_count}, Logical CPU Count: {logical_cpu_count}")
print(f"CPU Usage: {cpu_usage}%")
```

2. **获取内存信息:**

```python
# 获取内存使用情况
memory_info = psutil.virtual_memory()

print(f"Total Memory: {memory_info.total} bytes")
print(f"Available Memory: {memory_info.available} bytes")
print(f"Used Memory: {memory_info.used} bytes")
print(f"Memory Usage Percentage: {memory_info.percent}%")
```

3. **获取磁盘信息:**

```python
# 获取磁盘分区信息
disk_partitions = psutil.disk_partitions()

for partition in disk_partitions:
    print(f"Device: {partition.device}, Mount Point: {partition.mountpoint}")

# 获取磁盘使用情况
disk_usage = psutil.disk_usage('/')
print(f"Total Disk Space: {disk_usage.total} bytes")
print(f"Used Disk Space: {disk_usage.used} bytes")
print(f"Free Disk Space: {disk_usage.free} bytes")
print(f"Disk Usage Percentage: {disk_usage.percent}%")
```

4. **获取网络信息:**

```python
# 获取网络接口信息
net_interfaces = psutil.net_if_addrs()

for interface, addresses in net_interfaces.items():
    print(f"Interface: {interface}")
    for address in addresses:
        print(f"  - Address Family: {address.family}, Address: {address.address}")

# 获取网络连接信息
net_connections = psutil.net_connections(kind='inet')
for conn in net_connections:
    print(f"Local Address: {conn.laddr}, Remote Address: {conn.raddr}, Status: {conn.status}")
```

5. **获取进程信息:**

```python
# 获取当前运行的所有进程
all_processes = psutil.process_iter()

for process in all_processes:
    print(f"Process ID: {process.pid}, Name: {process.name()}")
```

这只是 `psutil` 模块的一小部分用法，该模块提供了许多其他方法和属性，用于更详细地获取系统信息。你可以参考 [psutil 官方文档](https://psutil.readthedocs.io/) 获取更多详细信息。
