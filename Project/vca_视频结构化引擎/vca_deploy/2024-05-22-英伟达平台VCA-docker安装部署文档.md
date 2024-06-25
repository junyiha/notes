---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: 英伟达平台VCA-docker安装部署文档
tag: ProjectOfVideoContentAnalysis
---

+ 环境依赖安装包：
  + `apt install -y libgomp1 libzmq5 libjsoncpp1 libhiredis0.13 libsdl2-2.0-0 liblapacke libatlas-base-dev libuuid1 zlib1g librdkafka1 libeigen3-dev libx264-152 libx265-146 libopenjp2-7  libmp3lame0 librtmp1 libssh-4 libxcb-shape0 libfontconfig1 libgl1 libxv1 libjpeg8 libtiff5 libopenexr22`

  + `apt install -y libssl-dev openssl libffi-dev zlib1g-dev wget`
+ nvidia软件包：
  + `cuda_11.4.4_470.82.01_linux`
  + `cudnn-11.4-linux-x64-v8.2.4.15`
  + `TensorRT-8.2.5.1.Linux.x86_64-gnu.cuda-11.4.cudnn8.2`

--------------------------------------------------------------------------------------------------------------------

+ docker 镜像
  + nvidia docker容器中devel runtime base 三种文件的区别
  + **base版本**
    + 该版本是从cuda9.0开始，包含了部署预构建cuda应用程序的最低限度，如果用户需要自己安装自己需要的cuda包，可以选择使用这个版本
  + **runtime版本**
    + 该版本通过添加cuda工具包中的所有共享库，扩展基本的镜像。如果使用多个cuda库的预构建应用程序，可使用这个版本的镜像，但是如果想借助cuda中的头文件对自己的工程进行编译，则会出现找不到文件的错误
  + **devel版本**
    + 通过添加编译器工具链，测试工具，头文件和静态库来扩展运行的镜像，使用这个版本的镜像可以从源代码编译cuda程序

+ 从`docker hub`拉取官方镜像
  + `docker pull nvidia/cuda:11.4.2-cudnn8-devel-ubuntu18.04`
  + `docker pull nvidia/cuda:11.4.2-cudnn8-runtime-ubuntu18.04`
  + `docker pull nvidia/cuda:11.4.2-cudnn8-base-ubuntu18.04`

+ 加载docker镜像：
  + `nvidia_cuda_v1-import.tar` : `cat nvidia_cuda_v1-import.tar | docker import - nvidia_cuda:v1.0`
  + `nvidia_cuda_v1.tar` : `docker load --input nvidia_cuda_v1.tar`
  
--------------------------------------------------------------------------------------------------------------------

## 安装python38

+ 下载python3.8压缩包
  - wget https://www.python.org/ftp/python/3.8.3/Python-3.8.3.tgz

+ 解压python3.8
  - tar xvf Python-3.8.3.tgz

+ 需依赖
  - sudo apt-get install -y libssl-dev openssl libffi-dev zlib1g-dev

+ 安装
  - cd Python-3.8.0
  - ./configure --prefix=/usr/local/python38  --enable-optimizations
  - make && make install

+ 建立软链接
  - ln -s /usr/local/python38/bin/python3.8 /usr/bin/python38
  - ln -s /usr/local/python38/bin/pip3.8 /usr/bin/pip38

+  查看安装是否成功 
  - /usr/bin/python38 或 pip38 -V

## cuda (cuda_11.4.4_470.82.01_linux)

+ cuda文件：`cuda_11.4.4_470.82.01_linux.run`
  + 本地安装，在docker中安装，不要选择安装驱动，需要将宿主机中的驱动映射到docker容器中才能使用

## cudnn (cudnn-11.4-linux-x64-v8.2.4.15)

+ cudnn-8.2.4 : `https://developer.nvidia.com/rdp/cudnn-archive` 

+ 下载(deb包安装方式)
  - `libcudnn8_8.2.4.15-1+cuda11.4_amd64.deb`
  - `libcudnn8-dev_8.2.4.15-1+cuda11.4_amd64.deb`
  - `libcudnn8-samples_8.2.4.15-1+cuda11.4_amd64.deb`
+ 安装顺序
  - `libcudnn8_8.2.4.15-1+cuda11.4_amd64.deb`
  - `libcudnn8-dev_8.2.4.15-1+cuda11.4_amd64.deb`
  - `libcudnn8-samples_8.2.4.15-1+cuda11.4_amd64.deb`

+ `sudo cp /usr/include/cudnn.h /usr/local/cuda/include/cudnn.h && sudo chmod a+x /usr/local/cuda/include/cudnn.h`

## TensorRT (TensorRT-8.2.5.1.Linux.x86_64-gnu.cuda-11.4.cudnn8.2)

+ TensorRT-8.2.5 : `https://developer.nvidia.cn/nvidia-tensorrt-8x-download`

+ EA -- 体验版
+ GA -- 稳定版

+ 创建 `/usr/local/TensorRT`

+ 安装步骤
  + 下载tar压缩包，并解压，将解压后得到的文件夹复制到`/usr/local/`下，并重命名为`TensorRT`
  + 切换到`/usr/local/TensorRT/python`目录，执行命令`sudo pip38 install tensorrt-8.2.1.8-cp38-none-linux_x86_64.whl`
    + 自带的python有3.6和2.7，但是该目录下没有支持这两个版本的whl文件，要重新编译和安装python38
  + 切换到`/usr/local/TensorRT/graphsurgeon`目录，执行命令`sudo pip38 install graphsurgeon-0.4.5-py2.py3-none-any.whl`
  + 配置`~/.bashrc`文件
    ```
      # for CUDA
      export PATH="/usr/local/cuda-11/bin/:${PATH}"
      export LD_LIBRARY_PATH="/usr/local/cuda-11/lib64:${LD_LIBRARY_PATH}"

      # for TensorRT
      export CUDA_INSTALL_DIR="/usr/local/cuda-11"
      export CUDNN_INSTALL_DIR="/usr/local/cuda-11"
      export LD_LIBRARY_PATH="/usr/local/TensorRT/lib:${LD_LIBRARY_PATH}"
    ```

--------------------------------------------------------------------------------------------------------------------

## nvidia-container-toolkit

+ 官方链接
  + `https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html`

+ Add the package repositories
  - `distribution=$(. /etc/os-release;echo $ID$VERSION_ID)`
  - `curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -`

+ `curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list`

+ 该命令成功后可以查看`cat /etc/apt/sources.list.d/nvidia-docker.list`

+ `sudo apt-get update && sudo apt-get install -y nvidia-container-toolkit`

+ `sudo systemctl restart docker`

--------------------------------------------------------------------------------------------------------------------

## 从镜像启动容器，并检查硬件

```
  docker run -it --gpus all --privileged=true --restart=always --name nvidia  \
    -v /usr/lib/x86_64-linux-gnu/libnvcuvid.so.470.141.03:/usr/lib/x86_64-linux-gnu/libnvcuvid.so.470.141.03 \
    -v /usr/lib/x86_64-linux-gnu/libnvcuvid.so.1:/usr/lib/x86_64-linux-gnu/libnvcuvid.so.1  \
    -v /usr/lib/x86_64-linux-gnu/libnvcuvid.so:/usr/lib/x86_64-linux-gnu/libnvcuvid.so \

    -v /usr/lib/x86_64-linux-gnu/libnvidia-encode.so.470.141.03:/usr/lib/x86_64-linux-gnu/libnvidia-encode.so.470.141.03 \
    -v /usr/lib/x86_64-linux-gnu/libnvidia-encode.so.1:/usr/lib/x86_64-linux-gnu/libnvidia-encode.so.1  \
    -v /usr/lib/x86_64-linux-gnu/libnvidia-encode.so:/usr/lib/x86_64-linux-gnu/libnvidia-encode.so \
    nvidia_cuda:v1.0 /bin/bash`
```
  - `--gpus all` : 将nvidia的硬件驱动映射到容器中，使在容器中能够使用硬件资源，依赖于`nvidia-container-toolkit`工具
  ~~~- `-v` : 将宿主机中的`libnvcuvid.so`和`libnvidia-encode.so`相关文件和链接映射到docker容器中，不同驱动的库文件版本不同，根据实际文件名设置~~~
  - `--name nvidia` : 设置容器名称

+ 注意：
  + `-v`是将目录映射到容器中，使用这个方法会造成宿主机中的两个`libnvcuvid.so`和`libnvidia-encode.so`文件变成目录，从而不可用
  + 解决办法：
    + 使用dockerfile，将以上两个文件拷贝到容器中，再创建软连接，需要解决的问题：不同nvidia驱动的文件名不同，如何无差别的拷贝？
    + **手动拷贝和创建软连接**

+ `nvidia-smi, NVIDIA System Management Interface program` : 默认查看详细的gpu信息
  + `nvidia-smi -L` : 通过uuid查看每个gpu信息
  + `watch nvidia-smi` : 在一个窗口动态查看gpu信息
  + `nvidia-smi -l`  : 刷新gpu信息

## 配置环境变量并启动测试vca

+ `export LD_LIBRARY_PATH=/data/dagger/VideoProcess/lib:/data/dagger/VideoProcess/3party/lib:/usr/local/TensorRT/targets/x86_64-linux-gnu/lib:$LD_LIBRARY_PATH`

+ `/data/dagger/VideoProcess/bin/vca.exe --help`