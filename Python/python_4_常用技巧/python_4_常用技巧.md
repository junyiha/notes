## 简介

+ python中常用的技巧

## python 执行scp命令

在 Python 中执行 SCP 命令可以使用 `paramiko` 库，这是一个用于SSH2的Python库，支持SSH会话和文件传输。以下是一个示例，演示如何使用 `paramiko` 实现在 Python 中执行 SCP 命令：

首先，确保你已经安装了 `paramiko` 库。如果没有安装，你可以使用 `pip` 来安装它：

```bash
pip install paramiko
```

接下来，以下是一个简单的 Python 示例代码，演示如何使用 `paramiko` 执行 SCP 命令：

```python
import paramiko

# 连接 SSH 服务器
ssh = paramiko.SSHClient()
ssh.load_system_host_keys()
ssh.connect('your_server_ip', username='your_username', password='your_password')

# 执行 SCP 命令，将本地文件复制到远程服务器
local_path = '/path/to/local/file.txt'
remote_path = '/path/to/remote/file.txt'

# 使用 SCPClient 实现文件传输
scp = ssh.open_scp()
scp.put(local_path, remote_path)  # 本地文件复制到远程服务器
scp.close()

# 关闭 SSH 连接
ssh.close()
```

上述代码中的 `your_server_ip` 是远程服务器的 IP 地址，`your_username` 是用于 SSH 登录的用户名，`your_password` 是对应的密码。`local_path` 是本地文件的路径，`remote_path` 是远程服务器上的目标路径。

这个示例展示了如何使用 `paramiko` 库创建一个 SSH 连接并使用 SCP 在本地和远程服务器之间传输文件。根据你的实际情况，你可能需要更改相应的路径和凭据信息。