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
