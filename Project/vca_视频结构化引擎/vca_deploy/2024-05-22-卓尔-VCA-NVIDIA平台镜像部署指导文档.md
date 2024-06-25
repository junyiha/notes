---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: 卓尔-VCA-NVIDIA平台镜像部署指导文档
tag: ProjectOfVideoContentAnalysis
---

### 1.1 安装环境

+ 安装的主机环境：
  + ubuntu 系统
  + nvidia-smi(英伟达显卡驱动)
  + docker(>=version19.03)
  + nvidia-container-toolkit 

+ 安装docker
  + `sudo apt-get install docker-ce docker-ce-cli containerd.io`

+ 安装nvidia-container-toolkit
  + 官方链接
    + `https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html`
  + Add the package repositories
    - `distribution=$(. /etc/os-release;echo $ID$VERSION_ID)`
    - `curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -`
  + `curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list`
  + 该命令成功后可以查看`cat /etc/apt/sources.list.d/nvidia-docker.list`
  + `sudo apt-get update && sudo apt-get install -y nvidia-container-toolkit`
  + `sudo systemctl restart docker`

---

+ VideoProcess sdk docker image : `nvidia_vca_v3.tar`

### 1.2 部署 docker 并启动容器

+ 安装 docker image ： `docker load --input ./nvidia_vca_v3.tar`
  + 查看加载好的镜像：`docker image ls`
    + `REPOSITORY         TAG       IMAGE ID       CREATED        SIZE`
    + `nvidia/vca         v3.0      c804f2e83f0b   6 weeks ago    12.2GB`

+ 启动容器 ： `docker run -it --gpus all --name nvidia_vca nvidia/vca:v3.0 /bin/bash`
  - `--gpus all` : 将nvidia的硬件驱动映射到容器中，使在容器中能够使用硬件资源
  - `--name nvidia_vca` : 设置容器名称

+ 拷贝英伟达视频编解码动态库（执行完启动容器的命令，此时终端已经在容器中）
  + 另外打开一个终端，在目录 `/usr/lib/x86_64-linux-gnu`下找到两个动态库文件：`libnvcuvid.so.470.141.03`， `libnvidia-encode.so.470.141.03`。（注：这两个动态库文件后面的版本号与英伟达显卡驱动版本相关，不同版本的驱动，动态库文件名不同，但前面是相同的`libnvcuvid.so.*`， `libnvidia-encode.so.*`）
  + 将两个动态库文件拷贝到第二步创建的容器中对应目录：
    + 拷贝libnvcuvid.so : `docker cp /usr/lib/x86_64-linux-gnu/libnvcuvid.so.470.141.03 nvidia_vca:/usr/lib/x86_64-linux-gnu/libnvcuvid.so.470.141.03`
    + 拷贝libnvidia-encode.so : `docker cp /usr/lib/x86_64-linux-gnu/libnvidia-encode.so.470.141.03 nvidia_vca:/usr/lib/x86_64-linux-gnu/libnvidia-encode.so.470.141.03`

+ 在创建的docker容器中，创建英伟达视频编解码动态的软连接
  + libnvcuvid.so.*:
    + `ln -s /usr/lib/x86_64-linux-gnu/libnvcuvid.so.470.141.03 /usr/lib/x86_64-linux-gnu/libnvcuvid.so.1`
    + `ln -s /usr/lib/x86_64-linux-gnu/libnvcuvid.so.1 ln -s /usr/lib/x86_64-linux-gnu/libnvcuvid.so`
  + libnvidia-encode.so.*:
    + `ln -s /usr/lib/x86_64-linux-gnu/libnvidia-encode.so.470.141.03 /usr/lib/x86_64-linux-gnu/libnvidia-encode.so.1`
    + `ln -s /usr/lib/x86_64-linux-gnu/libnvidia-encode.so.1 ln -s /usr/lib/x86_64-linux-gnu/libnvidia-encode.so`

### 1.3 拷贝SDK到容器中，设置环境变量，测试SDK

+ 使用`docker cp VideoProcess nvidia_vca:/data/dagger/`命令将SDK拷贝到容器中

+ 设置环境变量
  + `export LD_LIBRARY_PATH=/data/dagger/VideoProcess/lib:/data/dagger/VideoProcess/3party/lib:/usr/local/TensorRT/lib:/usr/local/cuda-11/lib64:`