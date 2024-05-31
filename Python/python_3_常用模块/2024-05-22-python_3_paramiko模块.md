---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_3_paramiko模块
tag: Python
---
## 简介

+ paramiko模块笔记

## python3 Paramiko模块 详解

Paramiko 是一个用于 Python 的库，用于在远程服务器上执行操作，如 SSH 客户端连接、执行命令、文件传输等。它提供了许多功能，使得在 Python 中执行远程操作变得更加简单和灵活。

以下是使用 Python 3 中 Paramiko 模块的一些常见功能和用法：

### 安装 Paramiko
你可以使用 pip 来安装 Paramiko 模块：

```bash
pip install paramiko
```

### 使用 Paramiko 连接到远程服务器
```python
import paramiko

# 创建 SSH 客户端
ssh_client = paramiko.SSHClient()

# 设置策略自动添加未知主机的密钥
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

# 连接到远程服务器
ssh_client.connect(hostname='remote_host', username='username', password='password')

# 执行远程命令
stdin, stdout, stderr = ssh_client.exec_command('ls -l')
print(stdout.read().decode())

# 关闭 SSH 连接
ssh_client.close()
```

### 使用 SSH 密钥对连接
```python
import paramiko

# 创建 SSH 客户端
ssh_client = paramiko.SSHClient()

# 设置策略自动添加未知主机的密钥
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

# 使用密钥对进行身份验证
private_key = paramiko.RSAKey.from_private_key_file('/path/to/private_key')
ssh_client.connect(hostname='remote_host', username='username', pkey=private_key)

# 执行远程命令
stdin, stdout, stderr = ssh_client.exec_command('ls -l')
print(stdout.read().decode())

# 关闭 SSH 连接
ssh_client.close()
```

### 使用 SFTP 进行文件传输
```python
import paramiko

# 创建 SSH 客户端
ssh_client = paramiko.SSHClient()

# 设置策略自动添加未知主机的密钥
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

# 连接到远程服务器
ssh_client.connect(hostname='remote_host', username='username', password='password')

# 创建 SFTP 客户端
sftp_client = ssh_client.open_sftp()

# 从远程服务器下载文件
sftp_client.get('/remote/path/file.txt', '/local/path/file.txt')

# 关闭 SFTP 连接和 SSH 连接
sftp_client.close()
ssh_client.close()
```

以上是一些基本的示例，展示了如何使用 Paramiko 模块在 Python 3 中连接到远程服务器、执行命令和进行文件传输。通过 Paramiko，你可以轻松地在 Python 中管理和操作远程服务器。需要注意的是，使用 SSH 连接时，请谨慎处理凭据和密钥，并确保安全地管理和使用它们。