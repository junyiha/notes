## ssh 安装与配置

+ 一般ubuntu都会默认安装openssh-client,但是没有安装openssh-server
+ 安装ssh服务器:
  + `sudo apt-get install openssh-server`
+ 安装ssh客户端:
  + `sudo apt-get install openssh-client`
+ 查看端口:
  + `netstat -tunpl | grep 22`
+ 查看ssh状态:
  + `service sshd status`
+ 重启ssh服务:
  + `service sshd restart` | `sudo /etc/init.d/ssh restart`   
+ ssh配置文件:
  + `/etc/ssh/ssh_config` | `/etc/ssh/sshd_config`
  + `PasswordAuthentication yes`
  + `PermitRootLogin yes`
  + `# PermitRootLogin prohibit-password`

## SSH 基础知识

+ SSH的全称为`Secure Shell`，即安全外壳协议，是一种加密的网络传输协议。它能够在公开的网络环境中提供安全的数据传输环境，通常用于登陆远程主机和推拉代码。

+ 同样一个SSH公钥文件，如果添加至某一个代码仓库，则称为部署公钥，配置后默认拥有读项目的只读权限，支持新增读写权限；
+ 如果添加至团队设置中心，则称为团队部署公钥，仅拥有只读权限；
+ 如果添加至个人账户，称为账户SSH公钥，配置后拥有账户内所有代码仓库的读写权限。
+ 同一个SSH公钥无法即作为部署公钥，又作为个人账户SSH公钥

+ 生成公钥 -- 使用`ssh-keygen`工具生成SSH公钥
  + `ssh-keygen -m PEM -t ed25519 -C "your.email@example.com"  // 创建新的SSH私钥和公钥对

+ 添加至部署公钥
  + 打开生成的密钥对的地址，通常为`~/.ssh 文件夹` , 找到后缀为`pub`的文件