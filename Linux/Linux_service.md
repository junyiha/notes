## 开机启动服务/脚本

+ 系统启动时需要加载的配置文件
  + /etc/profile
  + /root/.bash_profile
  + /etc/bashrc
  + /root/.bashrc
  + /etc/profile.d/*.sh
  + /etc/sysconfig/
  + /etc/rc.local

+ 自定义服务文件，添加到系统服务，通过`Systemctl`管理
  + 写服务文件，例如nginx.service, redis.service, supervisord.service
    ```
        [Unit]      --  服务说明
        Description --  描述服务
        After       --  描述服务类别

        [Service]    -- 服务运行参数的设置
        Type=forking -- 为后台运行的形式
        ExecStart    -- 为服务的具体运行命令
        ExecReload   -- 为服务的重启命令
        ExecStop     -- 为服务的停止命令
        PrivateTmp=True  -- 表示给服务分配独立的临时空间
        注意：启动，重启，停止命令全部要求使用绝对路径

        [Install]    --  服务安装的相关设置，可设置为多用户
        WantedBy=multi-user.target
    ``` 

+ 文件保存在`/usr/lib/systemd/system/`路径下，权限为`754`

+ 设置开机自动启动
  + `systemctl enable nginx.service`

+ 停止开机自启动
  + `systemctl disable nginx.service`

+ 验证是否为开机自启动
  + `systemctl is-enabled nginx`

+ 查看所有已经启动的服务
  + `systemctl list-units --type=service`

# 什么是socks

+ socks是一种网络传输协议，主要用于客户端与外网服务器之间通讯的中间传递。SOCKS是SOCKets的缩写
+ 当防火墙后的客户端要访问外部的服务器时，就跟SOCKS代理服务器连接。这个代理服务器控制客户端访问外网的资格。允许的话，就将客户端的请求发往外部的服务器。这个协议最初由David Koblas开发，而后由NEC的Ying-Da Lee将其扩展到版本4。最新协议是版本5，与前一版相比，增加支持UDP，验证以及IPv6

## 共享目录

### linux之间建立共享目录

如何使A服务器的某个目录挂载到B服务器的某个目录下,使其达到B服务下的目录文件一旦变更,可以实时的在A服务器的目录下体现出来?

Linux的解决方式
+ 将B服务器的该目录,设置为共享文件夹
+ A服务器通过mount的方式,指定对应的远程主机所抛出来的共享文件夹进行连接.

原理:
+ 挂载,并非将远程服务的文件实时拷贝到目标文件夹中
+ A服务器每次对于自身挂载文件的访问,实际上都是发送了一次新的RPC请求,请求目标服务器将其对应的目录数据实时返回到A服务器的文件当中进行展示.
+ Linux中存在一个应用:NFS网络文件系统(Network File System),它是一种适用于分散式文件系统的协定,让应用程序在客户端通过网络访问位于磁盘中的数据,是在类Unix系统间实现对应的磁盘文件共享的一种方法.

NFS和RPC的关系:
+ NFS在文件传送或信息传送过程中依赖于RPC协议.
+ RPC,远程过程调用(Remote Procedure Call)是能使客户端执行其他系统中程序的一种机制.
+ NFS本身是没有提供信息传输的协议和功能,但是NFS却能让我们通过网络进行资料的分享,这是因为NFS使用了一些其他的传输协议.而这些传输协议用到这个RPC功能,可以说NFS本身就是使用RPC的一个程序.只要用到NFS的地方都要启动RPC服务,不论是NFS 服务器还是NFS客户端,因为这样服务器和客户端才能通过RPC来实现程序端口的对应.
+ 可以这么理解:NFS是一个文件系统,而RPC是负责信息的传输

### 安装并配置NFS服务

1. 安装nfs服务器端服务: `apt-get install nfs-kernel-server`        
2. 编辑`/etc/exports`下的配置文件: 
      1. `sudo vim /etc/exports`
      2. 添加配置信息:`/home/zjy/share_folder *(rw, sync, no_root_squash, no_subtree_check)`
            1. `/home/zjy/share_folder`:共享文件夹的路径
            2. `*` : 允许所有的网段访问,也可以使用具体的IP
            3. `rw` : 挂接此目录的客户端对该共享目录的权限:读,写
            4. `sync`:资料同步写入内存和硬盘
            5. `no_root_squash`:root用户具有对根目录的完全管理访问权限
            6. `no_subtree_check` : 不检查父目录的权限
3. 重启服务,将会自动映射端口:`sudo /etc/init.d/rpcbind restart`
4. 重启nfs服务:`sudo /etc/init.d/nfs-kernel-server restart`
5. 创建共享文件夹
6. 查看ip地址,准备给客户端挂载

客户端配置:
1. 创建用于存放挂载的目录:`sudo mkdir /opt/share_folder`
2. 挂载服务器端共享目录:`sudo mount -t nfs 192.167.15.5:/mnt/A311D_share_folder /opt/share_folder`
3. 取消挂载:`sudo umount /opt/share_folder`