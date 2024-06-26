---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_06_open_ssh
tag: LinuxCommand
---
## 简介

+ openssh 相关工具的笔记

## OpenSSH 详解

OpenSSH（Open Secure Shell）是一个用于安全远程登录和文件传输的开源工具套件，提供了加密的网络通信协议和相关的命令行工具。它是SSH协议的实现之一，广泛用于Linux、Unix和其他类Unix系统上。

以下是OpenSSH的一些主要特点和功能：

1. 安全远程登录：OpenSSH提供了ssh命令，可以通过安全的加密通道远程登录到其他计算机，并在远程终端上执行命令。这使得用户可以远程管理和访问远程服务器，而不必直接物理接触远程计算机。

2. 文件传输：OpenSSH提供了scp和sftp命令，用于在本地计算机和远程服务器之间安全地传输文件和目录。这使得用户可以轻松地复制文件、上传和下载文件，以及进行远程文件管理。

3. SSH密钥认证：OpenSSH支持使用SSH密钥对进行身份认证，而不是传统的基于密码的认证方式。用户可以生成公钥和私钥，将公钥部署到服务器上，从而实现免密码登录。这提供了更高的安全性和方便性。

4. 端口转发和隧道：OpenSSH支持本地和远程端口转发，以及创建安全的隧道连接。这使得用户可以安全地访问远程计算机上的服务，甚至通过防火墙和网络限制。

5. X11转发：OpenSSH支持X11转发，允许用户在远程计算机上运行图形化应用程序，并将其显示到本地计算机上。这使得用户可以远程访问图形界面应用程序，而不必直接在远程计算机上操作。

6. 其他功能：OpenSSH还提供了许多其他功能，如代理转发、多因子认证、登录日志记录等，以增强安全性和用户管理能力。

总的来说，OpenSSH是一个功能强大、安全可靠的工具套件，为用户提供了远程访问和文件传输等功能，并通过加密通信和身份认证提供了强大的安全性保障。它在服务器管理、系统维护和远程协作等场景中得到广泛应用。

## Linux和Windows互相拷贝

+ 从Linux复制到Windows：
  + `scp /home/user/data/tmp.txt user@192.169.4.16:/C:Users/user/Desktop`

## 修改SSH配置文件

+ `sudo vim /etc/ssh/sshd_config`
+ 搜索`PermitRootLogin`，将一下配置：
  ```
    33 #LoginGraceTime 2m
    34 #PermitRootLogin prohibit-password
    35 #StrictModes yes
    36 #MaxAuthTries 6
    37 #MaxSessions 10
  ``` 
+ 修改为：
  ```
     LoginGraceTime 2m
     PermitRootLogin yes
     StrictModes yes
     #MaxAuthTries 6
     #MaxSessions 10
  ``` 

## 重启ssh，使配置生效

+ `sudo service ssh restart`


## linux openssh是什么

OpenSSH（Open Secure Shell）是一个用于提供加密的通信会话的免费开源实现，它包括SSH协议的实现和相关的工具。SSH（Secure Shell）是一种用于在网络上安全传输数据的协议，通常用于远程登录和执行命令，以及安全地传输文件。

以下是 OpenSSH 的主要组件和功能：

1. **SSH服务器 (`sshd`)：** OpenSSH 包括一个 SSH 服务器，用于接受远程用户的连接，并提供安全的远程访问。通过 SSH 协议，用户可以在远程系统上执行命令或进行其他操作，而通信过程是经过加密的，确保数据的机密性和完整性。

2. **SSH客户端 (`ssh`)：** OpenSSH 提供了一个 SSH 客户端，用于建立到远程服务器的加密连接。通过 SSH 客户端，用户可以远程登录到其他系统，执行命令，传输文件等。用户可以在命令行中使用 `ssh` 命令，也可以使用图形界面工具。

3. **SCP 和 SFTP：** OpenSSH 提供了用于安全文件传输的工具，包括 SCP（Secure Copy Protocol）和 SFTP（Secure File Transfer Protocol）。SCP 允许在网络上安全地传输文件，而 SFTP 则提供了一个交互式的文件传输协议，类似于 FTP，但使用 SSH 进行加密。

4. **SSH密钥对：** OpenSSH 支持使用密钥对进行身份验证，以替代传统的基于密码的身份验证方式。用户可以生成公钥和私钥，将公钥部署到远程服务器上，从而实现更安全的身份验证方式。

5. **端口转发：** OpenSSH 支持端口转发，允许用户在加密的通道上传输其他网络流量，如通过 SSH 安全地访问远程数据库或内部网络服务。

OpenSSH 是许多操作系统中默认安装的标准 SSH 实现，包括许多 Linux 发行版和 BSD 系统。其开源性质使得用户可以审查和修改代码以满足特定需求，并且它广泛用于安全的远程系统管理和文件传输。

## linux openssh详解

OpenSSH 是一个用于提供安全网络通信的开源实现，它主要实现了 SSH（Secure Shell）协议。SSH 是一种加密的协议，用于在不安全的网络中提供安全的远程访问、文件传输以及命令执行。以下是 OpenSSH 的一些详细信息：

### 组件和功能：

1. **sshd（SSH 服务器）：**
   - `sshd` 是 OpenSSH 中的服务器端程序，用于接受来自客户端的连接请求。
   - 它负责验证用户身份、建立安全通道，并处理用户的远程命令或文件传输请求。

2. **ssh（SSH 客户端）：**
   - `ssh` 是 OpenSSH 中的客户端程序，用于建立到远程 SSH 服务器的加密连接。
   - 通过 `ssh` 命令，用户可以登录远程系统、执行命令、传输文件等。

3. **SCP 和 SFTP：**
   - SCP（Secure Copy Protocol）和 SFTP（Secure File Transfer Protocol）是用于在网络上安全传输文件的工具。
   - SCP 提供命令行方式的文件传输，而 SFTP 提供了一个类似于 FTP 的交互式文件传输协议。

4. **SSH 密钥对：**
   - OpenSSH 支持基于密钥对的身份验证，其中用户生成公钥和私钥。
   - 用户将公钥部署到远程服务器，而私钥保留在本地。这样可以实现更安全的身份验证，避免传统密码登录的风险。

5. **端口转发：**
   - OpenSSH 支持端口转发，使用户能够通过 SSH 通道安全地传输其他网络流量。
   - 通过端口转发，用户可以访问远程服务器上的本地服务，或者将远程服务映射到本地端口。

### 配置文件：

OpenSSH 的配置文件通常是 `/etc/ssh/sshd_config`（服务器端）和 `~/.ssh/config`（客户端）。这些文件包含了各种配置选项，允许用户自定义 SSH 行为。

### 安全性：

OpenSSH 通过使用加密技术，包括对称加密、非对称加密和哈希算法，提供了通信的机密性和完整性。这使得它成为安全远程管理和文件传输的首选工具之一。

### 使用案例：

1. **远程登录：** 使用 `ssh` 客户端通过命令行或图形界面安全地登录到远程系统。

2. **文件传输：** 使用 SCP 或 SFTP 完成文件传输，确保文件在传输过程中得到加密保护。

3. **远程命令执行：** 使用 `ssh` 客户端执行远程系统上的命令，而不必直接登录到系统。

4. **安全传输其他服务：** 使用端口转发，通过 SSH 通道安全地访问和传输其他网络服务，如数据库服务。

总体而言，OpenSSH 是一个功能强大、安全可靠的工具，被广泛用于各种 Linux 和 UNIX 系统上，以及其他操作系统中。

## linux ssh服务器详解

在 Linux 系统上，SSH（Secure Shell）服务器主要由 OpenSSH 软件包提供，它是一个用于提供加密的远程登录和文件传输服务的开源实现。下面详细介绍 Linux 上的 SSH 服务器的相关概念和配置：

### OpenSSH 服务器 (`sshd`)：

1. **服务启动：**
   - `sshd` 是 OpenSSH 中的服务器端程序，负责监听 SSH 连接请求并处理用户的远程登录和文件传输。
   - 在大多数 Linux 发行版中，你可以通过以下命令启动或停止 SSH 服务：
     ```bash
     sudo service ssh start  # 启动服务
     sudo service ssh stop   # 停止服务
     ```

2. **配置文件：**
   - SSH 服务器的主要配置文件通常位于 `/etc/ssh/sshd_config`。这个文件包含了各种配置选项，用于定义服务器的行为、安全性设置和认证方式等。
   - 修改配置文件可能需要超级用户权限，你可以使用编辑器（如 `nano` 或 `vi`）来进行编辑：
     ```bash
     sudo nano /etc/ssh/sshd_config
     ```

3. **重要配置选项：**
   - 一些常见的配置选项包括：
     - `Port`: 指定 SSH 服务器监听的端口，默认为 22。
     - `PermitRootLogin`: 允许或禁止 root 用户通过 SSH 登录。
     - `PasswordAuthentication`: 启用或禁用密码身份验证。
     - `PubkeyAuthentication`: 启用或禁用公钥身份验证。
     - `AllowUsers` 或 `AllowGroups`: 限制哪些用户或组可以登录。
     - `Protocol`: 指定使用的 SSH 协议版本。

4. **身份验证方式：**
   - SSH 服务器支持多种身份验证方式，包括密码、公钥和基于主机的身份验证。管理员可以根据安全需求配置适当的身份验证方式。

5. **重启服务：**
   - 在修改了 `sshd_config` 文件后，需要重启 SSH 服务以使更改生效：
     ```bash
     sudo service ssh restart
     ```

6. **日志文件：**
   - SSH 服务器的活动和错误信息通常记录在 `/var/log/auth.log` 或 `/var/log/secure` 文件中，可以通过这些日志文件来监视服务器的活动。

7. **安全性建议：**
   - 定期更新 SSH 服务器和操作系统，以确保安全性。
   - 禁用不安全的身份验证方式，如密码身份验证，而使用公钥身份验证。
   - 配置防火墙规则以限制对 SSH 服务器的访问。

### 例子：

一个简单的 `sshd_config` 配置示例：

```plaintext
Port 22
PermitRootLogin no
PasswordAuthentication yes
PubkeyAuthentication yes
AllowUsers username
```

在这个例子中，SSH 服务器监听默认端口 22，禁止 root 用户直接登录，启用密码和公钥身份验证，只允许特定的用户（`username`）登录。

请注意，实际配置应根据具体的安全需求和网络环境进行调整。

## linux ssh客户端详解

在 Linux 系统上，SSH（Secure Shell）客户端通常由 OpenSSH 软件包提供。SSH 客户端允许用户建立加密连接到远程服务器，执行命令、传输文件以及进行其他远程操作。以下是关于 Linux 上 SSH 客户端的一些详细信息：

### OpenSSH 客户端 (`ssh`)：

1. **连接远程服务器：**
   - 使用 `ssh` 命令可以轻松地建立到远程服务器的 SSH 连接。语法为：
     ```bash
     ssh username@hostname
     ```
     其中，`username` 是目标服务器上的用户名，而 `hostname` 是目标服务器的主机名或 IP 地址。

2. **身份验证方式：**
   - SSH 客户端支持多种身份验证方式，包括密码和公钥身份验证。当使用密码登录时，系统会要求用户输入密码。而在使用公钥身份验证时，客户端会使用预先生成的密钥对进行身份验证。
     ```bash
     # 使用密码身份验证
     ssh username@hostname

     # 使用公钥身份验证
     ssh -i /path/to/private_key username@hostname
     ```

3. **文件传输：**
   - 使用 `scp` 命令可以在本地系统和远程服务器之间传输文件。语法为：
     ```bash
     # 从本地到远程
     scp local_file username@hostname:/remote/path

     # 从远程到本地
     scp username@hostname:/remote/file /local/path
     ```

4. **SSH 配置文件 (`~/.ssh/config`)：**
   - 用户可以在 `~/.ssh/config` 文件中配置 SSH 客户端的行为。这个文件允许你定义主机别名、身份验证方式、端口等设置，以简化 SSH 连接的管理。
     ```bash
     # 示例 ~/.ssh/config 文件
     Host myserver
       HostName example.com
       User username
       Port 2222
       IdentityFile ~/.ssh/private_key
     ```

5. **端口转发：**
   - SSH 客户端支持端口转发，允许用户安全地传输其他网络流量。这通常用于访问远程服务器上的本地服务。
     ```bash
     ssh -L local_port:remote_host:remote_port username@hostname
     ```

6. **代理跳板：**
   - 通过 SSH 客户端，用户可以设置代理跳板，从而通过一个中间服务器访问目标服务器。这对于连接到内部网络的服务器很有用。
     ```bash
     ssh -J jumpbox_username@jumpbox_hostname username@target_hostname
     ```

7. **执行远程命令：**
   - 通过在 `ssh` 命令后添加要执行的命令，可以在远程服务器上执行命令而不必手动登录。
     ```bash
     ssh username@hostname 'command_to_run'
     ```

8. **SSH Agent：**
   - SSH 客户端可以与 SSH Agent 配合使用，以避免在每次连接时重新输入密码或解锁私钥。
     ```bash
     # 添加私钥到 SSH Agent
     ssh-add /path/to/private_key
     ```

以上是一些基本的 SSH 客户端使用方式和功能。SSH 客户端非常灵活，可以通过不同的选项和配置满足各种需求，提供安全的远程访问和文件传输。

## linux scp命令详解

`scp`（Secure Copy Protocol）是一个用于在本地系统和远程系统之间进行安全文件传输的命令行工具。它使用 SSH 协议来提供加密的数据传输，确保传输的安全性。以下是关于 Linux 上 `scp` 命令的详解：

### `scp` 语法：

```bash
scp [选项] source destination
```

- **source：** 要传输的文件或目录的路径。可以是本地文件或远程服务器上的文件。
- **destination：** 文件或目录的目标位置。可以是本地路径或远程服务器的路径。

### 常用选项：

1. **-r：**
   - 递归复制，用于传输目录及其内容。
   ```bash
   scp -r local_directory username@remote_host:/remote/path
   ```

2. **-P：**
   - 指定远程服务器的端口号，默认为 22。
   ```bash
   scp -P 2222 local_file username@remote_host:/remote/path
   ```

3. **-i：**
   - 指定用于身份验证的私钥文件。
   ```bash
   scp -i /path/to/private_key local_file username@remote_host:/remote/path
   ```

4. **-v：**
   - 启用详细模式，显示调试信息。
   ```bash
   scp -v local_file username@remote_host:/remote/path
   ```

### 示例用法：

1. **从本地传输到远程：**
   ```bash
   scp local_file username@remote_host:/remote/path
   ```

2. **从远程传输到本地：**
   ```bash
   scp username@remote_host:/remote/file /local/path
   ```

3. **本地到远程目录：**
   ```bash
   scp -r local_directory username@remote_host:/remote/path
   ```

4. **从远程到本地目录：**
   ```bash
   scp -r username@remote_host:/remote/directory /local/path
   ```

### 注意事项：

- `scp` 使用 SSH 协议，因此你需要在远程服务器上启用 SSH 服务。
- 对于远程服务器路径，如果省略了用户名，则默认使用当前登录用户。
- `scp` 的工作方式类似于 `cp` 命令，但它使用 SSH 进行加密传输，因此数据在传输过程中是安全的。
- 在使用 `scp` 时，确保你有正确的权限来读取本地文件和写入远程目标路径。

`scp` 是一个非常实用的工具，能够在本地系统和远程服务器之间轻松传输文件，而且通过使用 SSH 进行加密，确保了数据的安全传输。

## linux sftp命令详解

`sftp`（Secure File Transfer Protocol）是一个基于 SSH 协议的安全文件传输工具，它允许用户通过命令行交互式地在本地系统和远程服务器之间传输文件。与传统的 FTP 不同，`sftp` 使用 SSH 进行加密，提供更安全的文件传输方式。以下是关于 Linux 上 `sftp` 命令的详细解释：

### `sftp` 语法：

```bash
sftp [选项] [username@]host[:path]
```

- **username：** 远程服务器上的用户名，如果省略，则使用当前登录用户。
- **host：** 远程服务器的主机名或 IP 地址。
- **path：** 远程服务器上的路径，如果省略，则默认为用户的主目录。

### `sftp` 命令：

1. **连接到远程服务器：**
   ```bash
   sftp username@remote_host
   ```

2. **退出 `sftp`：**
   - 在 `sftp` 交互式模式下，可以使用 `exit` 或 `quit` 命令退出。
   ```bash
   exit
   ```

3. **上传文件到远程服务器：**
   ```bash
   put local_file
   ```

4. **下载文件到本地系统：**
   ```bash
   get remote_file
   ```

5. **列出远程目录内容：**
   ```bash
   ls
   ```

6. **改变远程目录：**
   ```bash
   cd remote_directory
   ```

7. **删除远程文件：**
   ```bash
   rm remote_file
   ```

8. **创建远程目录：**
   ```bash
   mkdir remote_directory
   ```

9. **重命名远程文件：**
   ```bash
   rename old_name new_name
   ```

### 选项：

- **-i：** 指定用于身份验证的私钥文件。
  ```bash
  sftp -i /path/to/private_key username@remote_host
  ```

- **-P：** 指定远程服务器的端口号，默认为 22。
  ```bash
  sftp -P 2222 username@remote_host
  ```

### 注意事项：

- `sftp` 是一个交互式的命令行工具，用户可以在交互模式下输入命令。
- 文件上传和下载时，文件的路径和名称可以在本地和远程之间指定。
- `sftp` 提供了类似于 FTP 的命令，但是由于使用了 SSH 进行加密，传输过程更加安全。
- 可以使用 `help` 命令在 `sftp` 中查看可用的命令。

`sftp` 是一个灵活且安全的文件传输工具，适用于需要通过 SSH 加密传输文件的场景。在使用 `sftp` 时，请确保你有正确的权限来读取本地文件和写入远程服务器上的目标路径。

## linux ssh密钥对详解

在 Linux 系统中，SSH 密钥对是一种用于身份验证和安全传输的机制。密钥对包括公钥和私钥，这两者一起工作以确保安全的通信。以下是关于 Linux 中 SSH 密钥对的详细解释：

### SSH 密钥对的组成：

1. **公钥 (`id_rsa.pub`)：**
   - 公钥是可以公开分享的部分，用于验证与私钥配对的身份。它通常保存在用户的 `~/.ssh/` 目录下，文件名为 `id_rsa.pub`。
   - 公钥是一串文本，类似于以下示例：
     ```
     ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQC+6czkGk...
     ```

2. **私钥 (`id_rsa`)：**
   - 私钥是必须保持安全的部分，只有拥有私钥的用户可以使用它来进行身份验证。私钥通常保存在用户的 `~/.ssh/` 目录下，文件名为 `id_rsa`。
   - 私钥是二进制数据，通常不会直接以文本形式显示。

### 生成 SSH 密钥对：

可以使用 `ssh-keygen` 命令生成 SSH 密钥对。默认情况下，生成的密钥对将保存在用户的 `~/.ssh/` 目录下。

```bash
ssh-keygen -t rsa -b 2048
```

上述命令将生成一个 RSA 类型的密钥对，位数为 2048。根据需要，可以选择其他密钥类型和位数。

### 将公钥部署到远程服务器：

1. **手动复制：**
   - 使用 `ssh-copy-id` 或手动将公钥内容复制到远程服务器的 `~/.ssh/authorized_keys` 文件中。
     ```bash
     ssh-copy-id username@remote_host
     ```

2. **复制到剪贴板：**
   - 使用 `xclip` 或 `pbcopy` 将公钥复制到剪贴板，然后粘贴到远程服务器上的 `~/.ssh/authorized_keys` 文件中。
     ```bash
     cat ~/.ssh/id_rsa.pub | xclip -sel clip
     ```

### 使用 SSH 密钥对进行身份验证：

1. **在登录时指定私钥：**
   - 在 `ssh` 命令中使用 `-i` 选项指定私钥文件：
     ```bash
     ssh -i /path/to/private_key username@remote_host
     ```

2. **使用 SSH Agent：**
   - 将私钥添加到 SSH Agent 中，以免在每次连接时输入密码：
     ```bash
     ssh-add /path/to/private_key
     ```

### 注意事项：

- **私钥安全性：**
  - 私钥应该始终保持安全，不要与他人共享，以免被滥用。
  - 私钥文件的权限应设置为只有拥有者可读写 (`chmod 600 ~/.ssh/id_rsa`)。

- **公钥部署：**
  - 将公钥部署到所有需要访问的远程服务器上，以实现无密码或密钥登录。
  - 在远程服务器上的 `~/.ssh/authorized_keys` 文件中可以包含多个公钥，每行一个。

SSH 密钥对提供了一种强大且安全的身份验证机制，适用于远程登录、文件传输等场景。密钥对的生成和使用都涉及到一些注意事项，确保密钥的安全和正确配置是使用 SSH 密钥对的关键。

## Could not open a connection to your authentication agent 错误

如果您在执行 `ssh-add` 命令时收到 "Could not open a connection to your authentication agent" 错误，这通常意味着SSH Agent并未在当前的Shell会话中运行。以下是一些可能的原因和解决方法：

1. **SSH Agent未启动：** 请确保SSH Agent已经启动。您可以通过运行以下命令来启动SSH Agent：

    ```bash
    eval "$(ssh-agent -s)"
    ```

2. **Shell环境问题：** 如果您在新的Shell窗口中运行 `ssh-add`，请确保您的SSH Agent环境变量已经被正确设置。您可以通过运行以下命令来检查：

    ```bash
    echo $SSH_AGENT_PID
    ```

    如果没有输出，或者输出为空，可能需要重新启动SSH Agent。

3. **SSH Agent自动启动问题：** 如果您在每次登录时都遇到此问题，可能是因为SSH Agent没有在登录时自动启动。您可以将SSH Agent启动命令添加到您的shell配置文件中（例如，`.bashrc` 或 `.zshrc`）。

   在文件末尾添加以下行：

    ```bash
    if [ -z "$SSH_AUTH_SOCK" ] ; then
        eval "$(ssh-agent -s)"
        ssh-add
    fi
    ```

   这将在每次登录时检查SSH Agent是否运行，如果没有，则启动并添加私钥。

4. **重新启动SSH Agent：** 如果以上步骤都没有解决问题，可以尝试重新启动SSH Agent。首先，停止当前运行的SSH Agent：

    ```bash
    ssh-agent -k
    ```

    然后重新启动SSH Agent：

    ```bash
    eval "$(ssh-agent -s)"
    ```

尝试这些步骤后，您应该能够成功将私钥添加到SSH Agent中。如果问题仍然存在，请提供更多详细信息，以便我能够提供更具体的帮助。

## Linux openssh端口转发详解

在 Linux 下，OpenSSH 提供了强大的端口转发功能，可以通过 SSH 通道安全地传输其他网络流量。端口转发（Port Forwarding）允许你在本地计算机和远程服务器之间建立加密的通信通道，从而访问远程网络服务或将本地服务映射到远程服务器上。有两种主要类型的端口转发：本地端口转发（Local Port Forwarding）和远程端口转发（Remote Port Forwarding）。

### 1. 本地端口转发（Local Port Forwarding）：

本地端口转发允许你将本地计算机上的端口转发到远程服务器上。通常用于访问远程服务器上的服务，如数据库或内部网站。

```bash
ssh -L local_port:remote_host:remote_port username@remote_server
```

- `local_port`：本地计算机上监听的端口。
- `remote_host`：远程服务器上服务的主机名或 IP 地址。
- `remote_port`：远程服务器上服务的端口。

示例：将本地计算机的本地端口 8080 转发到远程服务器的 80 端口（Web 服务器）：

```bash
ssh -L 8080:localhost:80 username@remote_server
```

现在，可以在本地浏览器中访问 `http://localhost:8080` 来访问远程服务器上的 Web 服务。

### 2. 远程端口转发（Remote Port Forwarding）：

远程端口转发允许你将远程服务器上的端口转发到本地计算机上。通常用于暴露本地服务，使其可以通过远程服务器访问。

```bash
ssh -R remote_port:local_host:local_port username@remote_server
```

- `remote_port`：远程服务器上监听的端口。
- `local_host`：本地计算机上服务的主机名或 IP 地址。
- `local_port`：本地计算机上服务的端口。

示例：将远程服务器的远程端口 8888 转发到本地计算机的 22 端口（SSH 服务）：

```bash
ssh -R 8888:localhost:22 username@remote_server
```

现在，可以在远程服务器上通过 `ssh -p 8888 localhost` 来访问本地计算机上的 SSH 服务。

### 注意事项：

1. **防火墙设置：**
   - 确保本地计算机和远程服务器的防火墙允许相应的端口访问。

2. **SSH 服务器配置：**
   - 在远程服务器上，确保 SSH 服务器的配置文件允许相应的端口转发。

   ```bash
   # /etc/ssh/sshd_config
   AllowTcpForwarding yes
   ```

3. **安全性：**
   - 使用端口转发时，务必注意安全性。不要将本地服务直接暴露到公共网络上，应仅限制访问到必要的主机。

4. **通道保持活跃：**
   - 添加 `-N` 选项可以防止 `ssh` 命令打开 shell，从而只建立端口转发通道而不登录到远程服务器。

```bash
ssh -N -L local_port:remote_host:remote_port username@remote_server
```

端口转发是 SSH 功能中非常有用的一部分，它可以使你在不直接暴露服务的情况下安全地访问远程服务器上的服务。

## OpenSSH 相关命令

OpenSSH是一个用于安全远程登录的开源工具套件，提供了一系列命令和协议用于远程访问和管理Linux系统。以下是一些常用的OpenSSH相关命令：

1. ssh：远程登录到服务器或执行远程命令。
```
ssh user@hostname
```
其中，`user`是远程服务器的用户名，`hostname`是远程服务器的主机名或IP地址。

2. scp：安全地复制文件和目录到远程服务器。
```
scp source_file user@hostname:destination_path
```
其中，`source_file`是本地文件路径，`user`是远程服务器的用户名，`hostname`是远程服务器的主机名或IP地址，`destination_path`是远程服务器上的目标路径。

3. sftp：使用类似FTP的方式在本地系统和远程服务器之间传输文件。
```
sftp user@hostname
```
通过此命令进入sftp会话后，可以执行一系列文件传输操作。

4. ssh-keygen：生成和管理SSH密钥对。
```
ssh-keygen -t rsa
```
该命令用于生成RSA密钥对，可以使用其他选项指定密钥类型和文件名等。

5. ssh-agent：管理SSH代理，用于管理私钥并免密码登录。
```
eval $(ssh-agent)
```
该命令启动ssh-agent代理，并将其相关环境变量设置为当前shell的环境变量。

6. ssh-add：将私钥添加到ssh-agent代理中。
```
ssh-add ~/.ssh/id_rsa
```
该命令将指定的私钥添加到ssh-agent代理中，以便在进行SSH身份验证时使用。

这些命令是OpenSSH套件中的一部分，用于实现安全远程登录和文件传输等功能。请根据具体需求和情况选择适当的命令使用。

---

## ssh_exchange_identification: read: Connection reset by peer 错误

当你在使用SSH连接时，出现"ssh_exchange_identification: read: Connection reset by peer"错误，通常表示SSH连接被对方终止了。这可能是由于以下几个原因导致的：

1. 网络连接问题：这可能是由于网络中断、丢包或不稳定的连接导致的。请确保你的网络连接正常，并尝试重新连接。

2. SSH服务器配置问题：可能是SSH服务器配置有问题，导致连接被终止。你可以尝试重新启动SSH服务器或检查其配置文件以查找潜在的问题。

3. 防火墙或安全设置：防火墙或其他安全设置可能会阻止SSH连接。确保你的防火墙设置允许SSH流量通过，并且服务器端没有任何限制。

4. SSH版本不匹配：如果你使用的SSH客户端和服务器端之间的SSH协议版本不匹配，可能会导致连接被重置。尝试使用兼容的SSH版本，或者更新SSH客户端和服务器端以确保版本一致。

5. SSH服务器负载过高：如果SSH服务器负载过高，可能无法处理新的连接请求，从而导致连接被重置。尝试在负载较低的时间重新连接。

如果以上方法都无效，你可以尝试使用其他SSH客户端或与SSH服务器管理员联系以获取更多支持和故障排除。

---

## ssh 允许root登录

+ 文件：/etc/ssh/sshd_config
  + `PermitRootLogin yes`

---

## ssh 安装与配置

+ 一般ubuntu都会默认安装openssh-client,但是没有安装openssh-server
+ 安装ssh服务器:
  - `sudo apt-get install openssh-server`
+ 安装ssh客户端:
  - `sudo apt-get install openssh-client`
+ 查看端口:
  - `netstat -tunpl | grep 22`
+ 查看ssh状态:
  - `service sshd status`
+ 重启ssh服务:
  - `service sshd restart` | `sudo /etc/init.d/ssh restart`   
+ ssh配置文件:
  - `/etc/ssh/ssh_config` | `/etc/ssh/sshd_config`
  - `PasswordAuthentication yes`
  - `PermitRootLogin yes`
  - `# PermitRootLogin prohibit-password`

## SSH 基础知识

+ SSH的全称为`Secure Shell`，即安全外壳协议，是一种加密的网络传输协议。它能够在公开的网络环境中提供安全的数据传输环境，通常用于登陆远程主机和推拉代码。

+ 同样一个SSH公钥文件，如果添加至某一个代码仓库，则称为部署公钥，配置后默认拥有读项目的只读权限，支持新增读写权限；
+ 如果添加至团队设置中心，则称为团队部署公钥，仅拥有只读权限；
+ 如果添加至个人账户，称为账户SSH公钥，配置后拥有账户内所有代码仓库的读写权限。
+ 同一个SSH公钥无法即作为部署公钥，又作为个人账户SSH公钥

+ 生成公钥 -- 使用`ssh-keygen`工具生成SSH公钥
  - `ssh-keygen -m PEM -t ed25519 -C "your.email@example.com"  // 创建新的SSH私钥和公钥对

+ 添加至部署公钥
  - 打开生成的密钥对的地址，通常为`~/.ssh 文件夹` , 找到后缀为`pub`的文件

---

## ssh-keygen

`ssh-keygen`命令是Linux系统中用于生成SSH密钥对的工具。SSH密钥对由一对公钥和私钥组成，用于身份验证和安全通信。

下面是`ssh-keygen`命令的一些常见选项和用法：

1. 生成RSA密钥对：
```
ssh-keygen -t rsa
```
这将生成一个RSA密钥对，默认情况下，公钥文件为`id_rsa.pub`，私钥文件为`id_rsa`。

2. 生成DSA密钥对：
```
ssh-keygen -t dsa
```
这将生成一个DSA密钥对，默认情况下，公钥文件为`id_dsa.pub`，私钥文件为`id_dsa`。

3. 生成ECDSA密钥对：
```
ssh-keygen -t ecdsa
```
这将生成一个ECDSA密钥对，默认情况下，公钥文件为`id_ecdsa.pub`，私钥文件为`id_ecdsa`。

4. 生成ED25519密钥对：
```
ssh-keygen -t ed25519
```
这将生成一个ED25519密钥对，默认情况下，公钥文件为`id_ed25519.pub`，私钥文件为`id_ed25519`。

5. 指定密钥文件名：
```
ssh-keygen -f <filename>
```
使用`-f`选项可以指定生成的密钥文件的文件名。例如，`ssh-keygen -f mykey`将生成`mykey`作为文件名的密钥对。

6. 设置密钥密码：
```
ssh-keygen -p
```
使用`-p`选项可以更改已有密钥文件的密码。

7. 查看密钥指纹：
```
ssh-keygen -lf <public_key_file>
```
使用`-lf`选项可以查看公钥文件的指纹。

以上是一些常见的`ssh-keygen`命令选项和用法。生成密钥对后，可以将公钥文件部署到服务器上，以便进行SSH身份验证。私钥文件应该妥善保管，不应与他人共享。