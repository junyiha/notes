## cmake 编译安装

+ `cmake -DCMAKE_INSTALL_PREFIX=/home/user/zjy-190/Documents/OpenCV/4.5.2/install -DCMAKE_TYPE=RELEASE -DWITH_FFMPEG=OFF -DOPENCV_EXTRA_MODULES_PATH=/mnt/remote/190-mnt/zhangjunyi/Documents/OpenCV/4.5.2/opencv-4.5.2/modules ..`
+ 参数：
  + `CMAKE_INSTALL_PREFIX` : 设置安装路径
  + `CMAKE_TYPE` : 设置编译类型
  + `WITH_FFMPEG` : 设置是否带有ffmpeg，因为ffmpeg版本不对应，安装会失败，所以关掉了
  + `OPENCV_EXTRA_MODULES_PATH` : 设置OpenCV扩展模块路径 opencv_contrib

## 安装opencv

+ 安装依赖环境
    ```
    sudo apt-get install build-essential
    sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev 
    sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
    ```
  + **找不到` libjasper-dev`**
    ```
    sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
    sudo apt update
    sudo apt install libjasper1 libjasper-dev
    ```

+ 下载源码，解压缩，创建build文件夹
    1. ` cmake -D CMAKE_INSTALL_PREFIX=/usr/local CMAKE_BUILD_TYPE=Release  OPENCV_GENERATE_PKGCONFIG=ON  OPENCV_ENABLE_NONFREE=True .. `
    2. ` sudo make -j6 `
    3. ` sudo make install`

+ 环境配置
  + 修改`/etc/bash.bashrc`,增加内容：
    ```
    PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
    export PKG_CONFIG_PATH
    ```
  + 更新： ` sudo updatedb && source /etc/bash.bashrc `
  + 修改动态库` /etc/ld.so.conf.d/opencv.conf` (如果没有，就创建)
    `/usr/local/lib`
  + 更新：` sudo ldconfig` 