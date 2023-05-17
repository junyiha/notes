## 查看容器日志

+ `docker logs <container-id>`，查看日志
+ 示例：
  ```
    user@computer:test-docker$ docker logs 172
    root@1722c360945f:/# ls
    bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  src  srv  sys  tmp  usr  var
    root@1722c360945f:/# cd src
    root@1722c360945f:/src# ks
    bash: ks: command not found
    root@1722c360945f:/src# ls
    one.txt
    root@1722c360945f:/src# ls
    one.txt  two.txt
    root@1722c360945f:/src# cat two.txt
    root@1722c360945f:/src# ls
    two.txt
    root@1722c360945f:/src# ls
    two.txt
    root@1722c360945f:/src# pwd
    /src
    user@computer:test-docker$ 
  ``` 

## mount

+ `docker run -it --mount type=bind,src="$(pwd)"，target=/src ubuntu:18.04 bash` 

## docker 语言支持

+ node.js
+ python
+ java
+ go
+ c#

## docker中的overlay2

+ 在安装的docker系统中，删除了容器和镜像，但是docker/overlay2还是占用很大的磁盘空间

### docker/overlay2下的文件都是些什么

+ docker/overlay2目录下的文件名基本都是md5编码
+ overlay2是docker使用的文件存储驱动，也就是说，该目录下的文件都是docker使用的存储
  + overlay2是分层存储，每一层通过本层的md5作为文件夹名来命名，如果要存储的两个东西，例如两个镜像的底层中的几层内容是一样的，那么它们的md5也就是一样的，通过md5检验，确认它们这几层是一样的，那么在overlay2实际存储的时候，这几层就可以只存储一份，然后由这两个镜像共同使用，来达到节省空间的目的

### 根据这些md5目录名检查是哪个容器

+ `docker inspect xxx | grep merge`

### 如何处理overlay2

+ 真正要处理的不是这两个文件，是要检查正在跑的容器内的服务，有没有往容器本地写文件的行为，如果有，则要把写文件的路径挂载出来，或者直接在容器中删除文件

## docker 管理命令

### builder

+ manage builds

#### build

+ 命令：`docker builder build [OPTIONS] PATH | URL | -`
+ 简介：从Dockerfile创建一个镜像
+ 选项：
  + `--add-host` : 添加一个自定义的主机到IP的映射（host:ip）
  + `--build-arg` : 设置构建时的变量
  + `--cache-from` : 考虑作为缓存来源的镜像
  + `--cgroup-parent` : 容器的可选父级c组
  + `--compress` : 使用gzip压缩构建环境
  + `--cpu-period`
  + `--cpu-quota`
  + `--cpu-shares,-c`
  + `--cpuset-cpus`
  + `--cpuset-mems`
  + `--disable-content-true` : 跳过镜像验证，默认为true
  + `--file,-f` : Dockerfile的名称，默认为PATH/Dockerfile
  + `--force-rm` : 始终移除中间的容器
  + `--iidfile` : 将镜像的ID写入到文件中
  + `--isolation` : 容器隔离技术
  + `--label` : 设置镜像的元数据
  + `--memory,-m` : 内存限制
  + `--memory-swap` : 交换限制等于内存加交换：-1表示启用无限制交换。
  + `--network` : 在构建过程中为RUN指令设置网络模式
  + `--no-cache` : 在构建镜像的时候不要使用缓存
  + `--platform` : 如果服务器是多平台的，则设置平台
  + `--pull` : 始终尝试拉取一个较新版本的镜像
  + `--quiet,-q` : 过滤构建镜像的输出，仅在成功时输出镜像的ID
  + `--rm` : 构建成功后删除中间容器
  + `--security-opt` : 安全选项
  + `--shm-size` : /dev/shm的大小
  + `--squash` : 将新建的层压成一个新的层
  + `--tag,-t` : 名称和可选的标签，格式为name:tag
  + `--target` : 设置目标构建阶段为构建。
  + `--ulimit` : 限定选项

### run

+ 命令：`docker run [OPTIONS] IMAGE [COMMAND] [ARG...]`
+ 简介：docker run命令首先在指定的镜像上创建一个可写的容器层，然后用指定的命令启动它。也就是说，docker run相当于API中的/containers/create然后/containers/(id)/start。一个停止的容器可以用docker start来重新启动，其之前的所有变化都是完整的。
+ 选项：
  + `--add-host` : 添加一个自定义的主机到IP的映射（host:ip）
  + `--attach,-a` : 附加到STDIN、STDOUT或STDERR上
  + `--blkio-weight` : 区块IO（相对权重），在10和1000之间，或0表示禁用（默认为0）。
  + `--blkio-weight-device` : 块状IO重量（相对设备重量）
  + `--cap-add` : 	增加Linux功能
  + `--cap-drop` : 	降低Linux的能力
  + `--cgroup-parent` : 容器的可选父级c组
  + `--cgroupns`
  + `--cidfile` : 将容器ID写到文件中
  + `--cpu-count` : CPU计数，仅支持Windows
  + `--cpu-percent` : 
  + `--cpu-period` 
  + `--cpu-quota`
  + `--cpu-rt-period`
  + `--cpu-rt-runtime`
  + `--cpu-shared,-c`
  + `--cpus` : cpu的数量
  + `--cpuset-cpus`
  + `--cpuset-mems`
  + `--detach,-d` : 在后台运行容器并打印容器ID
  + `--detach-keys` : 覆盖脱离容器的按键顺序
  + `--device` : 在容器中添加一个主机设备
  + `--device-cgroup-rule` : 在cgroup允许的设备列表中添加一条规则
  + `--device-read-bps` : 限制从一个设备上的读取速率（每秒字节数）。
  + `--device-read-iops` : 限制从一个设备的读取率（每秒的IO）。
  + `--device-write-bps`
  + `--device-write-iops`
  + `--disable-content-trust` : 跳过镜像验证，默认为true
  + `--dns` : 设置自定义的DNS服务器
  + `--dns-option` : 设置DNS选项
  + `--dns-search` : 设置自定义DNS搜索域
  + `--domainname` : 容器NIS域名
  + `--entrypoint` : 覆盖镜像的默认ENTRYPOINT
  + `--env,-e` : 设置环境变量
  + `--env-file` : 读取环境变量的文件
  + `--expose` : 暴露一个端口或一系列的端口
  + `--gpus` : 要添加到容器中的GPU设备（'全部'用于传递所有GPU）。
  + `--group-add`
  + `--health-cmd` : 运行命令以检查健康状况
  + `--health-interval` : 运行检查的间隔时间（ms|s|m|h）（默认为0s）。
  + `--health-retries`
  + `--health-start-period`
  + `--health-timeout`
  + `--help` : 输出帮助信息
  + `--hostname,-h` : 容器主机名称
  + `--init` : 在容器内运行一个init，转发信号并收割进程
  + `--interactive,-i` : 保持STDIN开放，即使没有连接
  + `--io-maxbandwidth` : 系统驱动器的最大IO带宽限制（仅Windows）。
  + `--io-maxiops` : 系统驱动器的最大IOps限制（仅Windows）。

## 常用命令

## `docker images, docker image ls`

+ 列出本地主机上的镜像
  - `repository` : 表示镜像的仓库源
  - `tag` : 镜像的标签
  - `image id` : 镜像id
  - `created` : 镜像创建时间
  - `size` : 镜像大小
  
## `docker rmi helloworld`

+ 删除镜像
  
## `docker run -it ubuntu /bin/bash`

+ 使用ubuntu镜像启动一个容器,参数为以命令模式进入该容器
  - `-i` : 交互操作
  - `-t` : 终端
  - `ubuntu` : ubuntu镜像
  - `/bin/bash` : 放在镜像名后的是命令,这里是希望有个交互式shell
  
## `docker run -itd --name ubuntu-test ubuntu /bin/bash`

+ 后台运行容器
  - `-d` : 默认不会进入容器,想要进入容器需要使用指令`docker exec`

## `docker ps`

+ 语法：`docker ps [options]`
+ 作用：列出容器
+ `[options]`
  - `--all, -a` : 显示所有容器(默认仅显示正在运行的)。(Show all containers(default shows just running))
  - `--filter, -f` : 基于指定的条件过滤输出信息。(Filter output based on conditions provided)
  - `--format` : 使用go模板输出
  - `--last, -n` : 显示n个最后创建的容器。(Show n last created containers(includes all states))
  - `--no-trunc` : 不截断输出。(Don't truncate output)
  - `--quiet, -q` : 仅显示容器ID。(Only display container IDs)
  - `--size, -s` : 显示总文件大小。(Display total file sizes)
  
## `docker start id`

+ 启动一个已停止的容器
  
## `docker stop`

+ 语法：`docker stop [options] container [container...]`
+ 作用：停止一个容器
+ `[options]`:
  - `--time, -t` : 在杀死容器之前等待停止的时间，默认为10秒
  
## `docker restart id`

+ 重启一个容器

## docker attach, docker exec

+ 进入容器:在使用`-d`参数时,容器启动后会进入后台,此时想要进入容器,通过以下指令:
  - docker attach: `docker attach id`
  - docker exec:推荐使用此命令,因为使用它退出容器终端,但是不会导致容器的停止,`docker exec -it id /bin/bash`

## docker export, docker import, docker commit

### docker export

+ `docker export`命令不会导出与容器关联的卷的内容。如果卷安装在容器中现有目录的顶部，则`docker export`将导出底层目录的内容，而不是卷的内容
+ 功能：将容器的文件系统导出为tar存档
+ `docker export 容器id > 容器名称.tar , docker export 容器id --output 容器名称.tar`
  - 导出本地某个容器到tar包
+ 参数
  - `--output, -o` : 写入一个文件，而不是`stdout`

### docker import

+ 语法：`docker import [options] file|URL|- [REPOSITORY[:TAG]]`
+ 作用：从一个tar包导入文件数据并创建一个文件系统镜像
+ `[options]` :
  - `--change, -c` : 应用于创建镜像的dockerfile 指示
  - `--message, -m` : 为导入的镜像设置提交信息
+ `cat docker/ubuntu.tar | docker import - test/ubuntu:v1`
  - 通过管道和标准输入的方式导入容器快照

### docker load

+ 导入镜像文件：`docker load --input imagePath`

### docker commit

+ 更新镜像:通过命令`docker commit`来提交容器副本,Warning:使用此命令保存镜像，会以层的概念保存，每一次保存都会增加一层，镜像会越来越大
  + 示例:`docker commit -m="has update" -a="runoob" e218edb10161 runoob/ubuntu:v2`
  + 参数说明:
    - `-m`:提交的描述信息
    - `-a`:指定镜像作者
    - `e218edb10161` : 容器ID
    - `runoob/ubuntu:v2` : 指定要创建的目标镜像名
  
## docker tag

+ 修改镜像标签:`docker tag image-id name:tag`

## 镜像的上传和拉取

+ 登录docker 
  + `docker login`

+ 修改镜像命名
  + 修改镜像的repository，使之与Docker Hub账号匹配
  + Docker Hub为了区分不同用户的同名镜像，镜像的`registry`中要包含用户名，完整的格式为:`[username]/xxx:tag`
  + Docker官方自己维护的镜像没有用户名

+ 镜像上传
  + 通过`docker push`将镜像上传到`Docker Hub`

+ 镜像的拉取
  + 上传的是公共镜像仓库，任何人都可以下载使用

## docker kill

+ 语法：`docker kill [options] container [container...]`
+ 作用：杀死一个或者多个正在运行的容器
+ `[options]`
  - `--signal, -s` : 发送到容器的信号。(Signal to send to the container)
  - `SIGHUB` , 信号，网络编程

## docker pause

+ 语法：`docker pause container [container...]`
+ 作用：暂停一个或多个容器中的所有进程

## docker unpause

+ 语法：`docker unpause container [container...]`
+ 作用：不暂停一个或多个容器中的所有进程

## docker rename

+ 语法：`docker rename container new_name`
+ 作用：重命名一个容器

## 目录映射

+ `-p`:指定端口映射，格式为：主机（宿主）端口：容器端口
+ `--privileged=true`:关闭安全权限，否则容器操作文件没有权限
+ `-v`:挂在目录为：主机目录：容器目录，在创建前容器是没有指定目录时，docker容器会自己创建
+ 端口映射:`-p 8083:8083 -p 5678:5678`
+ 目录映射以宿主机为主，换句话说，容器中原本存在的文件一旦进过挂载，就一定会被宿主机覆盖

## docker system

+ 语法：`docker system COMMAND`
+ 作用：管理docker(Manage Docker)

### docker system prune

+ 语法：`docker system prune [options]`
+ 作用：清除缓存
+ `[options]`
  - `-all, -a` : 删除所有未使用的镜像，不只是闲置的。(Remove all unused images not just dangling ones)
  - `--filter` : 提供数值过滤，例如：`label=<key>=<value>`。(Provide filter values)
  - `--force, -f` : 不提示确认。(Do not prompt for confirmation)
  - `--volumes` : 清除卷。(Prune volumes)

+ `docker system prune --volumes`
+ 该命令清除：
  - 所有停止的容器
  - 所有不被任何一个容器使用的网络
  - 所有不被任何一个容器使用的volume
  - 所有无实例的镜像

### docker system df

+ 语法：`docker system df [options]`
+ 作用：显示docker磁盘的使用情况(show docker disk usage)
+ `options` :
  - `--format` : 使用go模板打印更好的图像
  - `--verbose, -v` : 显示空间使用的详细信息

### docker system info

+ 语法：`docker system info [options]`
+ 作用：显示全部系统的信息
+ `[options]`:
  - `--format, -f` : 以指定的go模板格式化输出

## docker stats

+ 显示容器资源的使用情况，包括：CPU，内存，网络I/O等
+ 语法：`docker stats [options] [container...]`
+ `[options]`:
  - `-all, -a` : 显示所有的容器，包括未运行的
  - `--format` : 指定返回值的模板文件
  - `-no-stream` : 展示当前状态就直接退出了，不再实时更新
  - `--no-trunc` : 不截断输出
+ 输出详情：
  - `CONTAINER ID` ， `NAME` : 容器ID，名称
  - `CPU%, MEM%` : 容器使用的CPU和内存的百分比
  - `MEM USAGE/LIMIT` : 容器正在使用的总内存，以及允许使用的内存总量
  - `NET I/O` : 容器通过其网络接口发送和接受的数据量
  - `BLOCK I/O` : 容器从主机上的块设备读取和写入的数据量
  - `PIDs` : 容器创建的进程或线程数

## docker history

+ 语法：`docker history [options] IMAGE`
+ 作用：显示一个镜像的历史
+ `[options]`:
  - `--format` : 使用go模板输出
  - `--human, -H` : 以人习惯的阅读方式输出
  - `--no-trunc` : 不截断输出
  - `--quiet, -q` : 仅显示镜像IDs
  
## 保存镜像

+ 使用命令：`tar cvf image.tar --exclude=/proc --exclude=/image.tar /`， 在容器里打包系统所需要的文件，
  - 记录以下：`tar cvf image.tar --exclude=/system --exclude=/sys --exclude=/proc --exclude=/image.tar /`
+ `sudo docker cp containerID:/image.tar ./` , 将容器中打包的文件拷贝到主机中
+ `cat image.tar | sudo docker import - image:v1`, 导入镜像

## linux下重启,启动,关闭docker服务

+ `sudo systemctl start docker` : 启动
+ `sudo systemctl daemon-reload`: 守护进程重启
+ `sudo systemctl restart docker` or `sudo service docker restart` : 重启docker服务
+ `sudo service docker stop` or `sudo systemctl stop docker` : 关闭docker

## 以非root用户身份管理

+ Docker守护程序绑定到Unix套接字而不是TCP端口，默认情况下，Unix套接字的用户有root，其它用户只能使用sudo来访问。 Docker守护程序始终以root用户身份运行
+ 不想使用sudo，创建docker的Unix组，将用户添加到改组
  - `sudo groupadd docker`
  - `sudo usermod -aG docker $USER`
  - `newgrp docker`

---

## docker底层原理

+ 第一次接触docker概念，都会见到或者听见一句话：**docker技术比虚拟技术更为方便，快捷，docker容器本质上是进程**

+ 所有容器共享宿主机的cpu，磁盘，网络，内存等：
  - **实现了进程隔离**，每个服务独立运行
  - **文件系统隔离**，容器目录修改不影响主机目录
  - **资源隔离**，CPU内存，磁盘，网络资源相互独立
+ Docker容器的实现原理就是通过Namespace命名空间进行进程隔离，Unionfilesystem联合文件系统实现文件系统隔离，ControlGroups控制组实现资源隔离。
+ 其底层原理涉及到`linux namespace`，Linux Namespace 是Linux提供的一种内核级别环境隔离的方法。 Unix有`chroot`，提供了一种简单的模式：`chroot`内部的文件系统无法访问外部的内容。`Linux Namespace`在此基础上，提供了对`UTS, IPC, mount, PID, network, User`等的隔离机制
  - `https://lwn.net/Articles/531114/`
+ Linux Namespace, 有几个种类：`Mount namespaces`, `UTS namespaces`, `IPC namespaces`, `PID namespaces`, `Network namespaces`, `User namespaces`
+ 主要是三个系统调用：
  - `clone()`, 实现线程的系统调用，用来创建一个新的进程，并且可以通过设计上述参数达到隔离
  - `unshare()`, 使某个进程脱离某个`namespace`
  - `setns()`, 把某进程加入到某个`namespace`

## Docker exec 的实现原理

+ `Linux Namespace`创建的隔离空间是虚拟的，一个进程的`Namespace`信息在宿主机上是真实存在的，并且是以一个文件的方式存在。
+ 一个进程，可以选择加入到某个进程已有的`Namespace`当中，从而达到“进入”这个进程所在容器的目的，这正是`docker exec`的实现原理
+ 通过`setns()`可以将当前进程加入到已有的`namespace`中。

## 镜像启动容器的本质

+ 首先，需要明确Docker内的文件系统是如何工作的，Docker镜像被存储在一系列的**只读层**。
+ **Docker镜像是由多个文件系统（只读层）叠加而成，当启动一个容器的时候，Docker会加载只读层并在其上（镜像栈顶部）添加一个读写层**
+ 如果运行中的容器修改了现有的一个已经存在的文件，那么该文件将会从读写层下面的只读层复制到读写层，该文件的只读版本仍然存在，只是已经被读写层中该文件的副本所隐藏。当删除Docker容器，并通过该镜像重启的时候，之前的修改将会丢失
+ 在Docker中，只读层和顶部的读写层的组合被称为**联合文件系统(Union File System)**
+ Docker镜像可以理解成多个只读文件叠加而成，因此镜像是只读的，**当镜像运行起来时，就相当于在只读的镜像外面包裹了一层读写层变成了容器。**
+ 当删除容器之后，使用镜像重新创建一个容器时，此时的镜像的只读层和原来一样，只是在读写层的修改会全部丢失
+ 所以，docker的数据持久化说的就是：**数据不随容器的删除而消失。**

## 数据卷Volume

+ Docker的数据卷Volume能够让容器从宿主机中读取文件或持久化数据到宿主机内，让容器与容器产生的数据分离开来。
+ 可以简单的把Volume理解为Linux服务器上的挂载点，一个容器可以挂载多个不同的目录
+ Volume的生命周期是独立于容器的声明周期之外的，即使容器删除，Volume也会保留下来，Docker也不会因为这个Volume没有被容器使用而回收。在容器中，添加或修改这个文件夹中的文件也不会影响容器的联合文件系统。
+ Volume数据卷不是用分层文件系统，这对经常读取和写入的数据很有用。在开发过程中，可以将代码目录挂载到容器中，这样如果更改代码容器会实时地得到文件修改的返回文件。

## Docker数据管理-数据库容器化并持久化：数据卷概念，创建数据卷的两种方式，docker volume用法

### Docker数据管理

+ 在生产环境中使用Docker的过程，往往需要对数据进行持久化，或者需要在多个容器之间进行数据共享，这必然涉及容器的数据管理操作
+ 所谓Docker的数据持久化，即：数据不随着容器的结束而结束。在Docker中，要想实现数据的持久化，需要将数据从宿主机挂载到容器中
+ 容器中管理数据主要有两种方式：
  - 数据卷(Data Volumes)：容器内数据直接映射到本地主机环境
  - 数据卷容器(Data Volume Containers)：使用特定容器维护数据卷

## Docker核心概念：镜像，容器，仓库，架构核心设计理念

### Docker核心概念

+ **镜像**，通俗地讲，**它是一个只读的文件和文件夹组合**。
+ 它包含了容器运行时所需要的所有基础文件和配置信息，是容器启动的基础。所以想启动一个容器，那首先必须要有一个镜像。镜像是Docker容器启动的先决条件
+ 如果想要使用一个镜像，一般有两种方式：
  - 自己创建镜像。通常情况下，一个镜像是基于一个基础镜像构建的，可以在基础镜像上添加一些用户自定义的内容。形成业务镜像。
  - 从功能镜像仓库拉取别人制作好的镜像

+ **容器**，是Docker的另一个核心概念。
+ 通俗地讲，容器是镜像的运行实体。镜像是静态的只读文件，而容器带有运行时需要的可写文件层，并且容器中的进程属于运行状态。即容器运行着真正的应用进程
+ 虽然容器的本质上是主机上运行的一个进程，但是容器有自己独立的命名空间隔离和资源限制。也就是说，**在容器内部，无法看到主机上的进程，环境变量，网络等信息，这是容器于直接运行在主机上进程的本质区别。**

+ **仓库**，Docker的镜像仓库类似于代码仓库，用来存储和分发Docker镜像。
+ 镜像仓库分为公有镜像仓库和私有镜像仓库

### Docker架构

+ **相关背景知识**----容器的发展史
  - 容器技术随着Docker的出现变得炙手可热，所有公司都在积极拥抱容器技术。此时市场上除了有Docker容器，还有很多其他的容器技术，例如：CoresOS的rkt， lxc等。容器技术百花齐放是好事，但是也出现了很多问题，比如容器技术的标准到底是什么？
  - 可能会说，Docker已经成为了事实标准，把Docker作为容器技术的标准不可以吗？事实并没有想象的那么简单。因为那个时候不仅有容器标准之争，编排技术之争也十分激烈。当时的编排技术有三大主力，分别是：`Docker Swarm, Kubernetes, Mesos`。在这样的背景下，为了形成统一的标准，**OCI应运而生**。
  - OCI全称为开放容器标准(`Open Container Initiative`)，它是一个轻量级，开放的治理结构。OCI组织在Linux基金会的大力支持下，于2015年6月分正式注册成立。基金会旨在为用户围绕工业化容器的格式和镜像运行时，制定一个开放的容器标准。目前主要有两个标准文档：**容器运行时标准(`runtime spec`)和容器镜像标准(`image spec`)
  - 正是由于容器的战争，才导致Docker不得不改变了一些技术架构。最终，Docker整体架构采用C/S（客户端/服务器）模式，主要由客户端和服务端两大部分组成。客户端负责发送操作指令，服务端负责接受和处理指令。客户端和服务端通信有多种方式，既可以在通一台机器上通过UNIX套接字通信，也可以通过网络连接远程通信。

+ **Docker客户端**
  - Docker客户端其实是一种泛称。其中docker命令是Docker用户与Docker服务端交互的主要方式。
  - 除了使用docker命令的方式，还可以使用直接请求REST API的方式与Docker服务端交互，甚至还可以使用各种语言的SDK与Docker服务端交互

+ **Docker服务端**
  - Docker服务端是Docker所有后台服务的统称。
  - 其中`dockerd`是一个非常重要的后台管理进程，它负责相应和处理来自Docker客户端的请求，然后将客户端的请求转换为Docker的具体操作。例如镜像，容器，网络和挂载卷等具体对象的管理和操作。
  - Docker从诞生到现在，服务端经历了多次架构重构。起初，服务端的组件是全部集成在docker二进制里，但是从1.11版本开始，`dockerd`已经成了独立的二进制，此时的容器也不是直接由`dockerd`来启动了，而是继承了`containerd, runC`等多个组件
  - 虽然Docker的架构在不停重构，但是各个模块的基本功能和定位并没有变化。它和一般的C/S架构系统一样，Docker服务端模块负责和Docker客户端交互，并管理Docker的容器，镜像，网络等资源。

* **Docker重要组件**
  + Docker目前已经有了非常多的组件和工具。Docker的两个至关重要的组件：**`runC`和`containerd`**
    - `runC`是Docker官方按照OCI容器运行时标准的一个实现。通俗地讲，**`runC`是一个用来运行容器的轻量级工具，是真正用来运行容器的。**
    - `containerd`是Docker服务端的一个核心组件，它是从`dockerd`中剥离出来的，它的诞生完全遵循OCI标准，是容器标准化后的产物。**`containerd`通过`containerd-shim`启动并管理`runC`，可以说`containerd`真正管理了容器的生命周期**。
  + `dockerd`通过`gRPC`与`containerd`通信，由于`dockerd`与真正的容器运行时，`runC`中间有了`containerd`这一OCI标准层，使的`dockerd`可以确保接口向下兼容
    - `gRPC`是一种远程服务调用
  + `containerd-shim`的意思是垫片，类似于拧螺丝时夹在螺丝和螺母之间的垫片。`containerd-shim`的主要作用是：**将`containerd`和真正的容器进程解耦，使用`containerd-shim`作为容器进程的父进程，从而实现重启`dockerd`不影响已经启动的容器进程
  + 事实上，`dockerd`启动的时候，`containerd`就随之启动了，`dockerd`与`containerd`一直存在。当执行`docker run`命令时，`containerd`会创建`containerd-shim`充当"垫片"进程，然后启动容器的真正进程。（**`containerd-shim`是真正容器的进程的父进程，这么做为了不让真正的容器进程作为`containerd`的子进程，从而可以实现重启`containerd`而不影响已经运行的容器**）