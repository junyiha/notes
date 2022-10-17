## ubuntu-18.04-x86_64-NVIDIA 环境依赖包

+ 环境依赖安装包：
  + `apt install -y libgomp1 libzmq5 libjsoncpp1 libhiredis0.13 libsdl2-2.0-0 liblapacke libatlas-base-dev libuuid1 zlib1g librdkafka1 libeigen3-dev libx264-152 libx265-146 libopenjp2-7  libmp3lame0 librtmp1 libssh-4 libxcb-shape0 libfontconfig1 libgl1 libxv1 libjpeg8 libtiff5 libopenexr22`

+ `cuda_11.4.4_470.82.01_linux`
  
+ `cudnn-11.4-linux-x64-v8.2.4.15`
  
+ `TensorRT-8.2.5.1.Linux.x86_64-gnu.cuda-11.4.cudnn8.2`

--------------------------------------------------------------------------------------------------------------------

## docker 镜像

+ nvidia docker容器中devel runtime base 三种文件的区别

+ **base版本**
  + 该版本是从cuda9.0开始，包含了部署预构建cuda应用程序的最低限度，如果用户需要自己安装自己需要的cuda包，可以选择使用这个版本

+ **runtime版本**
  + 该版本通过添加cuda工具包中的所有共享库，扩展基本的镜像。如果使用多个cuda库的预构建应用程序，可使用这个版本的镜像，但是如果想借助cuda中的头文件对自己的工程进行编译，则会出现找不到文件的错误

+ **devel版本**
  + 通过添加编译器工具链，测试工具，头文件和静态库来扩展运行的镜像，使用这个版本的镜像可以从源代码编译cuda程序

+ `apt-file` : 通过文件名查找deb包
  
--------------------------------------------------------------------------------------------------------------------


+ `docker pull nvidia/cuda:11.4.2-cudnn8-devel-ubuntu18.04`

+ `docker pull nvidia/cuda:11.4.2-cudnn8-runtime-ubuntu18.04`

+ `docker pull nvidia/cuda:11.4.2-cudnn8-base-ubuntu18.04`

--------------------------------------------------------------------------------------------------------------------

## cuda (cuda_11.4.4_470.82.01_linux)

+ cuda-11.4 : `https://developer.nvidia.com/cuda-11-4-0-download-archive?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=18.04&target_type=deb_local`

  ```
    wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-ubuntu1804.pin
    sudo mv cuda-ubuntu1804.pin /etc/apt/preferences.d/cuda-repository-pin-600
    wget https://developer.download.nvidia.com/compute/cuda/11.4.0/local_installers/cuda-repo-ubuntu1804-11-4-local_11.4.0-470.42.01-1_amd64.deb
    sudo dpkg -i cuda-repo-ubuntu1804-11-4-local_11.4.0-470.42.01-1_amd64.deb
    sudo apt-key add /var/cuda-repo-ubuntu1804-11-4-local/7fa2af80.pub
    sudo apt-get update
    sudo apt-get -y install cuda
  ```

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

## 从镜像启动容器，并检查硬件

+ `docker run -it --gpus all --name nvidia nvidia_cuda:v1.0 /bin/bash`
  + `--gpus all` : 将nvidia的硬件驱动映射到容器中，使在容器中能够使用硬件资源

+ `nvidia-smi, NVIDIA System Management Interface program` : 默认查看详细的gpu信息
  + `nvidia-smi -L` : 通过uuid查看每个gpu信息
  
--------------------------------------------------------------------------------------------------------------------

## vca.exe 加载模型并创建任务

+ 4.x版本
  + `./vca.exe --model-conf  /tmp/Fire_BITMAINLAND/DETECT.conf  --id 1 --input-video-name "rtsp://192.167.15.58:554/yunshitu.mp4" --detector-conf "/--detector-models/2000003001_DETECT/xxxx/xxxx" --output-video-name "/tmp/aaa.mp4" --output-type 2`

+ 5.0.3版本
  + `./vca.exe --detector-conf --detector--models /tmp/Fire_BITMAINLAND/DETECT.conf --id 1 --input-video-name "rtsp://192.167.15.58:554/test_fire_smoke.mp4" --detector-conf "@--detector-models@/tmp/Model/NVIDIA GeForce RTX 2080/COCO/DETECT.conf@xxxx@yyyy" --output-video-name "/tmp/aaa.mp4" --output-type 2 --detector-conf-inline`

--------------------------------------------------------------------------------------------------------------------


<!-- ## cuda10.2

+ cuda-10.2 : `https://developer.nvidia.com/cuda-10.2-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1804&target_type=deblocal`

```
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-ubuntu1804.pin 
sudo mv cuda-ubuntu1804.pin /etc/apt/preferences.d/cuda-repository-pin-600
wget https://developer.download.nvidia.com/compute/cuda/10.2/Prod/local_installers/cuda-repo-ubuntu1804-10-2-local-10.2.89-440.33.01_1.0-1_amd64.deb 
sudo dpkg -i cuda-repo-ubuntu1804-10-2-local-10.2.89-440.33.01_1.0-1_amd64.deb
sudo apt-key add /var/cuda-repo-10-2-local-10.2.89-440.33.01/7fa2af80.pub
sudo apt-get update
sudo apt-get -y install cuda
```

## cudnnn

+ `https://developer.nvidia.com/rdp/cudnn-archive` 下载相关deb包，ubuntu18需要下载三个,依次安装
  ```
    libcudnn7_7.6.5.32-1+cuda10.2_amd64.deb
    libcudnn7-dev_7.6.5.32-1+cuda10.2_amd64.deb
    libcudnn7-doc_7.6.5.32-1+cuda10.2_amd64.deb
  ```

## TensorRT

+ 使用zar包安装，不是deb包安装。
+ `https://developer.nvidia.com/nvidia-tensorrt-6x-download`
+ 解压下载的压缩包，将该文件夹复制到想要安装的地方`sudo cp -R ./TensorRT /usr/local`
+ 然后切换到该文件夹下的python文件夹，使用pip安装 `sudo pip2 install tensorrt-6.0.1.8-cp27-none-linux_x86_64.whl`, 切换到`TensorRT/graphsurgeon`目录，使用pip安装`sudo pip2 install graphsurgeon-0.4.1-py2.py3-none-any.whl`
+ 配置`~/.bashrc`文件
    ```
    # for CUDA
    export PATH="/usr/local/cuda-10.2/bin:$PATH"
    export LD_LIBRARY_PATH="/usr/local/cuda-10.2/lib64:$LD_LIBRARY_PATH"

    # for TensorRT
    export CUDA_INSTALL_DIR="/usr/local/cuda-10.2"
    export CUDNN_INSTALL_DIR="/usr/local/cuda-10.2"
    export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/TensorRT-6.0.1.8/lib"
    ```
+ `source ~/.bashrc` -->