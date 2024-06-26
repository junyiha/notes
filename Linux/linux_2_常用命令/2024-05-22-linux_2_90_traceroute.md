---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_90_traceroute
tag: LinuxCommand
---
## 简介

+ linux traceroute命令 详解

## linux traceroute命令 详解

`traceroute` 命令用于追踪数据包从本地主机到目标主机的路径。它通过发送 ICMP 回显请求报文（ping）到目标主机，并记录每个经过的路由器的 IP 地址，以及到达目标主机的时间。以下是 `traceroute` 命令的一些常见用法和选项：

1. **基本用法**：
   ```bash
   traceroute <目标主机>
   ```
   这会启动一个追踪路由的过程，显示从本地主机到目标主机的路径信息。

2. **显示 IP 地址**：
   ```bash
   traceroute -n <目标主机>
   ```
   使用 `-n` 选项将显示 IP 地址，而不进行反向 DNS 查询。

3. **指定最大跃点数**：
   ```bash
   traceroute -m <最大跃点数> <目标主机>
   ```
   使用 `-m` 选项可以指定最大的跃点数（最大 TTL 值），以限制路由跟踪的跳数。

4. **使用 UDP 数据包**：
   ```bash
   traceroute -U <目标主机>
   ```
   使用 `-U` 选项可以指定使用 UDP 数据包而不是默认的 ICMP 回显请求。

5. **使用指定的端口号**：
   ```bash
   traceroute -p <端口号> <目标主机>
   ```
   使用 `-p` 选项可以指定发送数据包的目标端口号。

6. **设置报文发送间隔**：
   ```bash
   traceroute -z <间隔时间> <目标主机>
   ```
   使用 `-z` 选项可以设置发送报文之间的间隔时间。

`traceroute` 命令非常有用，可以用于诊断网络问题、分析网络路径以及调试网络配置。注意，不同系统版本可能会略有不同，因此建议查看相应版本的 `traceroute` 命令的文档以获取更多信息。