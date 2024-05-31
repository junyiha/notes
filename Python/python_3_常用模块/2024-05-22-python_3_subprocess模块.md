---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_3_subprocess模块
tag: Python
---
## 简介

+ subprocess模块笔记

## python3 subprocess模块 详解

`subprocess` 模块是 Python 标准库中的一个工具，用于创建和管理新的进程，并与它们进行交互。它提供了许多功能，允许在 Python 程序中执行外部命令、启动新进程、与这些进程进行通信等。

以下是 `subprocess` 模块的一些主要功能和常用函数：

### 执行外部命令
- `subprocess.run(args, *, stdin=None, input=None, stdout=None, stderr=None, shell=False, check=False)`：运行指定的命令，并等待其完成。该函数返回一个 `CompletedProcess` 对象，包含了命令的执行结果。参数 `args` 是要执行的命令和参数，`shell=True` 可以用于执行包含通配符或管道的命令。

### 创建新进程
- `subprocess.Popen(args, bufsize=-1, executable=None, stdin=None, stdout=None, stderr=None, preexec_fn=None, shell=False, cwd=None, env=None, universal_newlines=False, encoding=None, errors=None, text=None, **other_options)`：启动一个新进程，并返回一个 `Popen` 对象，可用于与新进程进行交互。

### 进程间通信
- `Popen.communicate(input=None, timeout=None)`：与新进程进行交互，发送数据到标准输入并获取标准输出和标准错误。可以设置 `input` 参数来发送数据给新进程，也可以使用 `timeout` 参数设置超时时间。

### 等待进程结束
- `Popen.wait(timeout=None)`：等待进程结束，并返回退出状态码。可以选择设置超时时间以避免无限等待。

### 其他函数和属性
- `subprocess.check_output(args, *, stdin=None, stderr=None, shell=False, universal_newlines=False)`：执行命令并返回输出结果，如果命令执行失败则抛出异常。
- `subprocess.check_call(args, *, stdin=None, stdout=None, stderr=None, shell=False)`：执行命令，如果命令执行失败则抛出异常。
- `Popen.pid`：获取新进程的进程 ID。
- 等等。

`subprocess` 模块提供了许多方法来执行外部命令，创建和管理新进程，并与这些进程进行交互。它在执行系统命令、启动子进程、执行 shell 脚本等方面非常有用。需要注意的是，在执行外部命令时应当格外小心，以防止不必要的安全风险，尤其是在使用 `shell=True` 时需谨慎防范命令注入问题。