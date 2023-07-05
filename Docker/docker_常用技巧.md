## 简介

+ docker常用技巧

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

## 根据这些md5目录名检查是哪个容器

+ `docker inspect xxx | grep merge`


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
