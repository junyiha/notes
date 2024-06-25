---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: video_process_Q_A
tag: ProjectOfVideoContentAnalysis
---

## Video_Process, Computing_node, Manager_node

+ `Computing_node`, `Manager_node`都与硬件无关
+ `Video_Process` 用来屏蔽硬件差异为`Computing_node`提供计算的基础服务，使`Computing_node`不需要关心各平台的硬件差异

### 管理节点

+ 面向用户，站在用户的角度
+ 管理节点就是一个完整的产品，它提供操作的界面，接收用户的所有操作，并将相应操作的结果返回给用户

### 算力节点

+ 接收命令，并进行计算

### Video_Process

+ 为算力节点提供计算功能
+ 算力节点从管理节点取出指令，根据指令向`vca`发送命令，并接收`vca`的结果，返回给管理节点

### 其他

+ 对用户来说的功能都是以逻辑单元为基准的，某一个模块提供了什么功能
  
+ 物理单元对用户是不可见的，而且用户也不关心，类似于公式和应用
  + 物理单元（例如显卡，CPU等），相当于公式，提供运算的规则
  + 逻辑单元（例如区域入侵检测功能），相当于公式的应用，利用某些公式，做排列组合，从而解决某一种问题

### 产品内数据传输

+ `Video_Process` 向 `Computing_node`传输数据（图片）：
  + `Video_Process`将数据（图片）放到redis的消息队列中，`Computing_node`从消息队列中取数据，进行处理并将处理后的结果放回到消息队列中

+ `Computing_node` 向 `Manager_node`传输数据：
  + `Computing_node`将数据放到消息队列中,`Manager_node`从消息队列中取到数据并将传输到前端

+ `Computing_node` 向 `Manager_node`传输数据，实现点播服务: 
  + `Computing_node`将数据（图片）放到redis的消息队列中，`Manager_node`从消息队列中取出数据，发给多个用户，实现多用户同时观看

+ `Computing_node`和`Manager_node`都是独立的项目，可以独立运行的
+ `Video_Process`早期也是一个独立的项目，其存在的时间比较早，到现在为止有五个版本
+ `Computing_node` , `Manager_node`, `Video_Process`共同组合成了一个产品，这个产品到目前为止有三个版本（2022.09.09）
  + 当前的改造计划是：mqtt更换为mjpeg， websocket更换为HTTP
  + 下一步的改造计划是：所见即所得，集群式，动态加载模型 

+ MC码 授权码 `machinecode.exe kms.exe`
  + MC码是由管理节点调用`VideoProcess/bin/machinecode.exe`生成的，
  + 在`static/json`目录下有一个`kms.json`文件，其存放的是授权码，相应的会由VideoProcess启动一个进程`kms.exe`
  + MC码的作用是在使用授权码时，进行识别的设备序列号，有相应的设备序列号，才能通过授权码绑定激活

## Redis

+ Redis是一个开源（BSD许可），内存存储的数据结构服务器，可用作数据库，高速缓存和消息队列代理。
+ 它支持字符串，哈系表，列表，集合，有序集合，位图，hyperloglogs等数据类型。内存复制，Lua脚本，LRU收回，事务以及不同级别磁盘持久化功能，同时通过`Redis Sentinel`提供高可用，通过`Redis Cluster`提供自动分区。

+ Redis是完全开源免费的，遵守BSD协议，是一个高性能的`key-value`数据库
+ 端口为`6379`

+ Redis是一个开源的使用ANSI C语言编写，遵守BSD协议，支持网络，可基于内存，分布式，可选持久性的键值对(`Key-Value`)存储数据库，并提供多种语言的API。
+ Redis通常被称为数据结构服务器，因为值(`value`)可以是字符串(`String`)，哈希(`Hash`)，列表(`list`)，集合(`set`)和有序集合(`sorted set`)等类型。

+ `Redis`与其它`key-value`缓存产品有以下三个特点：
  + Redis支持数据的持久化，可以将内存中的数据保存在磁盘中，重启的时候可以再次加载进行使用
  + Redis不仅仅支持简单的`key-value`类型的数据，同时还提供list, set, zset, hash等数据结构的存储。
  + Reids支持数据的备份，即`master-slave`模式的数据备份。

+ Redis优势：
  + 性能极高-Redis能读的速度是1100000次/s， 写的速度是81000次/s
  + 丰富的数据类型-Redis支持二进制案例的Strings, Lists, Hashes, Sets及Ordered Sets数据类型操作
  + 原子-Redis的所有操作的都是原子性的，意思就是要么成功执行要么失败完全部执行。单个操作是原子性的。多个操作也支持事务，即原子性，通过`MULTI`和`EXEC`指令包起来
  + 丰富的特性-Redis还支持`publish/subscribe`，通知， key过期等特性。

+ Redis与其他key-value存储有什么不同？
  + Redis有着更为复杂的数据结构并且提供对它们的原子性操作，这是一个不同于其他数据库的进化路径。Redis的数据类型都是基于基本数据结构的同时对程序员透明，无须进行额外的抽象
  + Redis运行在内存中，但是可以持久化到磁盘，所以在对不同数据集进行高速读写时需要权衡内存，因为数据量不能大于硬件内存。在内存数据库方面的另一个优点是，相比在磁盘上相同的复杂的数据结构，在内存中操作起来非常简单，这样Redis可以做很多内部复杂性很强的事情。同时，在磁盘格式方面他们是紧凑的以追加的方式产生的，因为它们并不需要进行随即访问。

## Nginx

+ Nginx是一款自由的，开源的，高性能的HTTP服务器和反向代理服务器；同时也是一个IMAP，POP3，SMTP代理服务器。Nginx可以作为一个HTTP服务器进行网站的发布处理，另外nginx可以作为反向代理进行负载均衡的实现

+ 代理
  + 所谓代理，就是一个代表，一个渠道
  + 代理，涉及到两个角色：一个是**被代理角色**，一个是**目标角色**。**被代理角色**通过这个代理访问**目标角色**完成一些任务的过程称为代理操作过程。（如同，生活中的专卖店：可以到abc专卖店买了一双鞋，这个专卖店就是代理，被代理角色就是abc厂家，目标角色就是用户）

+ 正向代理：
  + 在如今的网络环境下，我们如果由于技术需要去访问国外的某些网站，会发现是没有办法访问的。此时需要一个操作abc进行访问，abc的方式主要是找到一个可以访问国外网站的代理服务器，我们将请求发送给代理服务器，代理服务器去访问国外的网站，然后将访问的数据传递给我们。这样的代理模式称为**正向代理**
  + 正向代理的最大的特点是客户端非常明确要访问的服务器地址；服务器只需要清楚的知道来自哪个代理服务器，而不需要清楚的知道来自哪个具体的客户端。
  + 正向代理模式屏蔽或者隐藏了真实客户端信息。

+ 反向代理：
  + 例如某宝网站，每天同时连接到网站的访问人数很多，单个服务器远远不能满足，此时就出现了：分布式部署。也就是通过部署多台服务器来解决访问人数限制的问题（某宝网站中大部分功能也是直接使用nginx进行反向代理实现的，并且通过封装nginx和其他的组件并命名为Tengine
  + 反向代理具体通过什么方式实现分布式的集群操作？
    + 多个客户端给服务器发送请求，Nginx服务器接受到之后，按照一定的规则分发给了后端的业务处理服务器进行处理，此时请求的来源，也就是客户端是明确的，但是请求具体由哪台服务器处理就不明确了，此时Nginx扮演的就是一个反向代理角色
  + 反向代理，主要用于服务器集群分布式部署的情况下，反向代理隐藏了服务器的信息。

+ 负载均衡
  + 已经明确了代理服务器的概念，接下来，Nginx扮演了反向代理服务器的角色，它是以什么样的规则进行请求分发的呢？不同的项目应用场景，分发的规则是否可以控制呢？
  + 这里提到的客户端发送的，nginx反向代理服务器接收到的请求数量，就是我们所说的**负载量**
  + 请求数量按照一定的规则进行分发到不同的服务器处理所使用的规则，就是一种均衡规则
  + 所以，将服务器接收到的请求按照一定的规则分发的过程，就称为**负载均衡**
  + 负载均衡在实际项目操作过程中，有**硬件负载均衡**和**软件负载均衡**
    + 硬件负载均衡，也被称为硬负载，相对造价昂贵，成本较高，但是数据的稳定性，安全性等有非常好的保障。例如中国移动，中国联通这样的公司才会选择硬负载
    + **软件负载均衡是利用现有的技术结合主机硬件实现的一种消息队列分发机制**，成本较低，更多的公司会选择使用软件负载均衡
  + nginx支持的负载均衡调度算法方式如下：
    + `weight`轮询（默认）：接收到的请求按照顺序逐一分配到不同的后端服务器，即使在使用过程中，某一台后端服务器宕机，nginx会自动将该服务器踢出队列，请求受理情况不会受到影响。这种方式下，可以给不同的后端服务器设置一个权重值(weight)，用于调整不同的服务器上请求的分配律：权重数据越大，被分配到请求的几率越大；该权重值主要是针对实际工作环境中不同的后端服务器硬件配置进行调整的。
    + `ip_hash`：每个请求按照发起给客户端的`ip`的`hash`结果进行匹配，这样的算法，一个固定ip地址的客户端总会访问到同一个后端服务器，这也在一定程度上解决了集群部署环境下session共享的问题
    + `fair`：智能调整调度算法，动态的根据后端服务器的请求处理到响应的时间进行均衡分配，响应时间短，处理效率高的服务器分配到请求的概率高，响应时间长，处理效率低的服务器分配到的请求少；结合了前两者的优点的一种调度算法。但是需要注意的是nginx默认不支持fair算法，如果需要使用，安装`upstream_fair`模块
    + `url_hash`：按照访问的`url`的`hash`结果分配请求，每个请求的`url`会指向后端固定的某个服务器，可以在nginx作为静态服务器的情况下提高缓存效率，同样需要注意的是nginx默认不支持这种调度算法，需要安装nginx的hash软件包

## HTTP

+ （待补充）

# 问题与方法

## 修改ip地址

+ 首先连接到盒子上，然后切换到 `/etc/network/interfaces.d/` 目录下，如果在该路径下存在文件: `eth0` 和 `eth1` ，则直接修改文件 `eth0` 的内容，设置需要的`ip`地址。 如果在该路径下只存在文件:`eth1` ， 则将文件`eth1` 复制一份并重命名为`eth0` ，同时将`eth0`中的`eth1`字段 都修改为`eht0`，再设置需要的`ip`地址并保存。

## 软件著作权申请：环境信息

+ 开发硬件环境： x86_64工作站
+ 运行硬件环境： Aarch64 SoC
+ 开发该软件的操作系统： Ubuntu 16.04 以上
+ 软件开发环境/开发工具： VScode, Python, GCC, GDB, HTML
+ 该软件的运行平台/操作系统： Debian 9 以上
+ 软件运行支撑环境/支持软件： Redis, Nginx, Mqtt, Mysql, Supervisor

## 主机管理

+ 清除数据库`ManagerV3`下的`mysql`中的表`gh_t_gpu`和表`gh_t_server`
+ 主机ID存储在`/dagger/computing_node/etc/SystemID`下
+ 绑定平台要和算法的版本相对应，使用`/data/dagger/VideoProcess/bin/showdevice.exe --fmt 2 --out /data/dagger/computing_node/etc/devices.json`
  + `{"devices ": [{"id":1,"vendor":"BITMAINLAND","product":"1684-SOC","socket":0}]}`

## 任务管理

+ 存储在数据库`ManagerV3`下的表`gh_t_task`

## 大屏报警信息不对

+ 在`/etc/mysql/my.cnf`文件末尾添加:`[mysqld]  group_concat_max_len=102400`

## 启动容器脚本：

+ `docker run -itd --restart=always --privileged=true -p 8083:8083 -p 5678:5678 -v /system:/system -v /etc/localtime:/etc/localtime:ro -v /etc/timezone:/etc/timezone:ro -e LOCAL_USER_ID=id -u -e PYTHONPATH=/system/lib image:tag /bin/bash /etc/init.d/start_server.sh`
+ `docker run -itd --name vca-pure --restart=always --privileged=true -p 8083:8083 -p 5678:5678 -v /system:/system -v /etc/localtime:/etc/localtime:ro -v /etc/timezone:/etc/timezone:ro -e PYTHONPATH=/system/lib image:pure /bin/bash /etc/init.d/start_server.sh`

## 计算节点: `list index out of range`

+ `rm -rf /data/dagger/computing_node/etc/SystemId/`
+ `VideoProcess/bin/showdevices.exe --fmt 2 --out  /data/dagger/computing_node/etc/devices.json`

+ `delete from gh_t_face_db;`
  + 清除mysql数据

## KMS 服务未启动或未授权 || mqtt

+ 计算节点的kms的ip地址配置错误
  + `vim /data/dagger/computing_node/control/config/gh_settings.ini`
  + KMS_HOST=127.0.0.1

+ mqtt
  + 端口未映射，修改为:`127.0.0.1`

+ 系统时间不准确

## 设定区域范围，画区域

  1. 点击任务管理下的使能列表的内容，
  2. 在弹出来的界面选点击区域，
  3. 点击右上角的图标开始划线，图形可以是不规则图形，但需要是闭合的，最后选择内有效还是外有效
  4. 画完之后，点击保存，退回到使能配置，点击 submit 进行提交，
  5. 退回到任务界面，停止任务，待任务停止后再启动（这一步骤是为了更新任务参数）

## 修改算法功能

+ 模型名字修改之后，需要在模型配置文件`DETECT.conf`中修改参数`--file`
+ 修改`detector.json`文件
  + `name` : 用于显示算法名称
  + 算法功能的添加：在`protocol/model/detector.json`中查找需要的算法配置，拷贝过去
  + 算法功能的删除：删除相关的配置字段

## 测试视频：rtsp流视频

+ ffmpeg 流服务器
  + `address` : `ssh user@192.167.200.102`
  + `passwd` : `123456`
  + `file location` : `/home/user/Videos/ffserver.conf`
+ 使用方式：`rtsp://192.167.200.102/test_falling_1.mp4`

## 启动多个任务（八个任务）时，redis申请不到内存资源

+ 创建任务，启动任务，停止任务。如此反复，如果某些任务被停止或者删除了，其key所对应的redis资源没有被释放，就会占用内存资源，导致后续任务创建与启动失败。
  + 每个任务在`redis`都有一个key，而每一个key都对应一个命名空间，该命名空间存放的是该任务所申请到的资源。
  + 正常来讲，任务停止或者删除，key就会被删除，而key对应的命名空间就会被删除，占用的内存资源就会被释放

+ 连续创建任务，但是某个任务占用的cpu资源，IO资源或者内存资源过多，导致后续任务在创建时没有足够的资源

+ 总的来说，问题产生的原因可能有两种：
  + 申请的资源没有正确释放
  + 任务占用的资源太多

## 打包docker镜像

+ 打包`import`镜像，使用命令：`tar cvf image.tar --exclude=/system --exclude=/sys --exclude=/proc --exclude=/image.tar /`，先将容器中的所有文件归档，拷贝出来，如果主机和容器ping的通，可以直接拷贝到主机上
+ 再将归档文件使用命令`cat image.tar | docker import - image:fullscreen`导入
+ 最后使用命令`docker save -o image-fullscreen.tar vca-fullscreen`将镜像保存到本地，这样就可以在下次使用的时候直接使用命令`docker load --input image.tar`导入镜像，且导入的镜像名称和标签是`image:fullscreen`
+ 为什么现在容器中将文件打包出来，不直接使用`docker save -o vca-fullscreen`？
  + 因为在docker是以层级结构存储文件的，每一次操作都相当于加上了一层文件，最终在保存的时候文件只会越来越大

## 相机增加或者删除--告警部署列表

+ 在mysql数据库中有一个记录相机信息的数据表`gh_t_camera_info`
+ 字段`is_delete` ： 如果为1，就是已删除，如果为0，就是存在，
+ 前端调用接口，将返回的相机信息直接写到大屏上，所以需要这个接口在mysql数据库中取相机信息的时候，作`is_delete`字段的判断

## 字典，任务对应显式的文字

+ 数据库中任务信息其任务id对应的任务名称，在`manager_node/web_backend/config/gh_settings.ini`中有一栏`task_module`

## 源代码行数

+ 52 * 63 * 28 = 91728

## 视频流拉取不到，播放不出来视频

+ 检查视频源是视频文件还是实时视频流(rtsp)？

+ 使用vlc检查视频流是否可以正常播放？
  + 使用`ffprobe`检测视频流地址

+ 查看视频编码是H265 还是 H264？

+ 看看端口是否映射错误，任务正常运行，但是端口未正确映射，redis数据库中的信息就不能正常发送到前端

## 比特大陆硬件所支持的视频编解码格式一般有

+ `H.264  H.265 wmv mjpeg`

+ 其他的视频格式也可以支持，但使用cpu编解码，效率很低

## video_process 输出日志

+ `abcdk --logd`
+ 添加环境变量： `export ABCDK_LOG_CONSTGNEE`

## vca.exe 加载模型并创建任务

+ 4.x版本
  + `./vca.exe --model-conf  /tmp/Fire_BITMAINLAND/DETECT.conf  --id 1 --input-video-name "rtsp://192.167.15.58:554/yunshitu.mp4" --detector-conf "/--detector-models/2000003001_DETECT/xxxx/xxxx" --output-video-name "/tmp/aaa.mp4" --output-type 2`

+ 5.0.3版本
  + `./vca.exe --id 1 --detector-conf-inline --detector-conf "@--detector-models@/data/dagger/VideoProcess/bin/DETECT.conf@xxxx@"  --input-video-name rtsp://192.167.15.58:554/yunshitu.mp4 --output-type 2 --output-video-name /tmp/aaa.mp4`
  + 检测器和模型是两个层面，在检测器的配置中添加模型配置文件的路径，然后通过模型配置文件进入到模型层面
  + 参数
    + `--id 1` : 任务id
    + `--detector-conf-inline` : 启用检测器内联配置，后面跟的字符串就是参数，由分隔符切分为键和值
      + `@--detector-models@/data/dagger/VideoProcess/bin/DETECT.conf@` ： 检测器内联的参数，设定模型配置文件的路径
    + `--input-video_name` : 输入视频的文件名
    + `--output-type 2` : 设定输出模式为视频
    + `--output-video-name /tmp/aaa.mp4` : 设定输出视频文件的路径

## 归一化 -- sigmoid

+ 5.0.4版本
  + 归一化，可以在模型转换的时候，转换工具做这个工作；在vca中，也有归一化的功能
  + 由于比特大陆早期的转换工具都没有做归一化，所以在之前vca在加载模型时默认开启了归一化的功能，
  + 最新更新的比特大陆模型转换工具加上了归一化这个功能，所以在5.0.4版本加上了一个控制归一化开启或关闭的参数 `--disable-sigmoid`
  + 如果模型在使用转换工具进行转换时就做了归一化的工作，则在vca加载模型时就不能再做归一化；反之，如果模型在使用转换工具进行转换时没有做归一化的工作，则在vca加载模型时就需要做归一化的工作
  + 模型没有做归一化，和重复做归一化都会导致检测异常，目前出现的异常情况是：分数很高，检测的框很多 

<!-- ## 两个事务同时访问同一条数据， -->

## uwsgi 启动服务

+ 停止服务：
  + uwsgi.ini的目录下，会存在`*.pid`
  + 使用命令 `uwsgi --stop *.pid` 停止服务

+ 启动服务：
  + 使用命令 `uwsig --ini uwsgi.ini` 启动服务

## video_process环境变量配置

+ 3.1.18版本
  - `export LD_LIBRARY_PATH=/data/dagger/VideoProcess/lib:/data/dagger/VideoProcess/3party/abcdk/lib:/data/dagger/VideoProcess/3party/lapacke/lib:/data/dagger/VideoProcess/3party/libhiredis/lib/:/data/dagger/VideoProcess/3party/libjsoncpp/lib:/data/dagger/VideoProcess/3party/libuuid/lib:/data/dagger/VideoProcess/3party/libzmq/lib:$LD_LIBRARY_PATH`

+ 5.0.4版本
  - `export LD_LIBRARY_PATH=/data/dagger/VideoProcess/lib:/data/dagger/VideoProcess/3party/lib:$LD_LIBRARY_PATH`

## 测试需要更新的模型 -- 注意事项

+ 问清楚现场环境，包括
  - video_process 的版本是多少
  - 与新版本的差异

+ 本地搭建多个版本的测试环境

## 使用命令行启动服务，客户端启动多任务

+ 启动`kms.exe`服务，用来激活vca（未激活的vca，最多只能同时启动两个任务）
  - `./kms.exe --licence M6RT8H25-HWPT8H27-K6RS8H29-D6RT8H24-YXR3QAU7-BRR38H29-D6QSZF25-D6F38H29-D6RT8H29-D6RT9R49-VUEVQV69 --listen`
+ 参数：
  - `--licence`  --  激活密钥
  - `--listen  < ADDRESS >`   --  监听地址(IPV4:PORT | [IPV6]:PORT)。默认：0.0.0.0:17007

+ 启动`vca.exe`服务
  - `./vca.exe --device --kms-address --multi-task 1 --multi-task-limit-max 65 --multi-task-zmq-listen tcp://*:9102`
+ 参数：
  - `--device < NUMBER >`  --  设备。默认：0
  - `--kms-address < ADDRESS >`  --  KMS服务器地址。默认：127.0.0.1:17007
  - `--multi-task < TYPE >`  --  启动多任务模式，并设置指令的管道类型，默认：1 (1：ZMQ | 2：KAFKA) 
  - `--multi-task-limit-max < NUMBER >`  --  多任务模式最大任务数量。默认：10。
  - `--multi-task-zmq-listen < ADDRESS(ZMQ) >`  --  多任务模式ZMQ监听地址。默认：tcp://*:9102

+ 使用命令启动任务
  - `./vca.exe --server-order-protocol 1 --server-response-timeout --server-zmq-address tcp://127.0.0.1:9102 --mid 1 --cmd 2 --id 1 --detector-conf-inline --detector-conf @--detector-models@/data/models/zhuoer/DETECT.conf@xxxx@yyyy@  --input-video-name /home/user/Videos/forget_v1.mkv --output-type `
+ 参数：
  - `--server-order-protocol < TYPE >`      --  服务端指令协议。默认：1。(1：ZMQ | 2：KAFKA)
  - `--server-response-timeout < NUMBER >`  --  服务端响应超时(秒)。默认：86400
  - `--server-zmq-address < ADDRESS(ZMQ) >` --  服务端ZMQ地址。默认：tcp://127.0.0.1:9102
  - `--mid < NUMBER >`  --  消息ID
  + `--cmd  < COMMAND >`--  命令
    - 1  --  任务列表
    - 2  --  创建并启动任务
    - 3  --  停止任务
    - 4  --  删除任务
    - 5  --  更新任务
    - 6  --  任务状态

+ **notice**
  - 已经要先将模型测试一遍，输出结果保存为视频，查看是否成功加载模型，并检测

## rtsp视频流 直接拉取不稳定

+ `ffplay -rtsp_transport tcp -i rtsp://admin:a1234567@192.167.10.110:554`
  + 原本传输协议是UDP，不稳定

## 比特大陆的盒子添加硬盘

+ `/dev` 设备名
+ `fdisk` 配置分区信息
+ `mkfs.brfs`  初始化分区
+ 修改`fstab`，添加分区`/dev/disk/by-uuid`对应的`uuid`
  + 使用`mount`将`ro`设置为`rw`
  + 修改`fstab`

## 算力节点--手动killpython3，vca.exe, ice.exe

+ `sudo killall -s 9 python3 && sudo killall -s 9 vca.exe && sudo killall -s 9 ice.exe`

## 车牌检测 -- 命令

+ `./vca.exe --id 1 --detector-conf-inline --detector-conf "@--detect-type@1@--detector-models@/data/public/models/LP/DETECT_LP.conf@--detector-models@xxxx.conf@--detector-models@yyyy.conf@--detector-models@/data/public/models/LP/LPOCR.conf@" --input-video-name /home/user/2022-10-27-10-43-16-169.mp4 --output-type 2 --output-video-name /home/user/aaa.mp4`

+ `./vca.exe --id 1 --detector-conf-inline --detector-conf "@--detect-type@1@--detector-models@http://192.167.66.113:8084/models/LP_NVIDIA_1080/DETECT_LP.conf@--detector-models@xxxx.conf@--detector-models@yyyy.conf@--detector-models@http://192.167.66.113:8084/models/LP_NVIDIA_1080/LPOCR.conf@" --input-video-name /home/user/Videos/test_lp.mp4 --output-type 2 --output-video-name /home/user/aaa.mp4`

+ `./vca.exe --id 1 --detector-conf-inline --detector-conf "@--detect-type@1@--detector-models@http://192.169.4.113:8084/models/LP_BITMAINLAND/DETECT_LP.conf@--detector-models@xxxx.conf@--detector-models@yyyy.conf@--detector-models@http://192.169.4.113:8084/models/LP_BITMAINLAND/LPOCR.conf@" --input-video-name /home/user/Videos/test_lp.mp4 --output-type 2 --output-video-name /home/user/aaa.mp4`


### uwsgi 

+ 会检查系统变量`LD_LIBRARY_PATH`中的路径下的所有动态库，如果有错误，就报错

### tar

+ `tar cvf mjpeg_face_v6.tar --exclude=/sys --exclude=/system --exclude=/proc --exclude=/mjpeg_face_v6.tar --exclude=/data/dagger/Anaconda3-2021.04-Linux-aarch64.sh --exclude=/data/dagger/logs/supervisor/* --exclude=/data/dagger/logs/web_backend/* --exclude=/data/dagger/logs/warning_record/* --exclude=/data/dagger/computing_node/logs/control/* --exclude=/data/dagger/computing_node/logs/process/* --exclude=/data/dagger/manager_node/web_frontend/dist.backup* --exclude=/tmp/* /`

### docker run

+ `sudo docker run -itd --restart=always --privileged=true --name face  -p 8083:8083 -p 8084:8084 -p 16379:6379  -v /system:/system mjpeg:face-v4  /bin/bash /etc/init.d/start_server.sh`


## 增加HTTP协议，ZMQ，KAFKA默认关闭，如果需要，编译之前手动开启

+ 手动开启ZMQ，KAFKA命令
  + `export HAVE_ZMQ=yes`
  + `export HAVE_KAFKA=yes`

## 0310

1. 在视频前端，绘制检测区域失灵，不论是否在区域内部，都会被检测到 
	+ 遗留物检测，绘制检测区域失效，这边修复一下
2. 遗留物品检测，帧间阈值略低，窗外光线略微波动，就会被检测到，能否在前端修改阈值
	+ 可以，在大屏界面，使能配置区域，灵敏度调节
3. 每次开机之后，无法加载视频，都要手动远程修改，在群中说过，可能sql的bug
	+ mysql表 gh_t_task, gh_t_gpu, gh_t_server, gh_t_warning_record, gh_t_warning_event 清理
	+ vca可能打开成功，但是解码失败，vca如果解码成功，会推向redis队列，查看算力节点有没有处理redis队列中的数据
	+ 加载模型失败，路径都准确，vca没起来
4. 遗留物品检测改成每个一段时间自动更新背景的吧
	+ 可以更改，在定制算法包时,或者在配置文件添加参数 :`--fbd-bg-uptime`
    + `int uptime = opt.valtoi("--fbd-bg-uptime",999999999);`
5. 人脸识别部分，做到了人脸匹配，而不是人脸识别。人脸库中没有出现的人员，会识别为人脸库中与其相似度最高的人，不符合实际应用需求。如果人员不在人脸库中，应该报警为陌生人。                               