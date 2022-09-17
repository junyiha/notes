## cuda10.2

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
+ `source ~/.bashrc`

--------------------------------------------------------------------------------------------------------------------

## cuda 11.4

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

## cudnn 

+ cudnn-8.2.4 : `https://developer.nvidia.com/rdp/cudnn-archive`
+ `sudo cp /usr/include/cudnn.h /usr/local/cuda/include/cudnn.h && sudo chmod a+x /usr/local/cuda/include/cudnn.h`

## TensorRT