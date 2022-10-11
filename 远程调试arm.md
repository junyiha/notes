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

挂载目录:
+ 工具:nfs, sshfs, 

挂载(mount):
+ Mounting takes place before a computer can any kind of storage device (suc as a hard drive, CD-ROM, or network share). The user or their operating system must make it accessible through the computer's file system. A user can only access files on mounted media.
      + "挂载"发生在计算机想要使用任何类型的存储设备(如硬盘,CD-ROM,网络设备)之前,操作系统必须讲这个设备纳入自己的文件系统中
+ `mount -t type device dir` : This tells the kernel to arrach the filesystem found on device(which is of type type) at the directory dir.
      + 挂载操作,实际上是把设备(device)中的文件系统附加到dir上,可以通过访问dic来访问这个设备
      + 其本质就是针对某一设备,分析出其文件系统结构,并根据其文件系统类型调用linux中相应的驱动,处理该设备的元数据,将这些信息附加到linux的目录树上,并呈现出来.