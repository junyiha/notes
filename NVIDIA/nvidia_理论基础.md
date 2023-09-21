## 简介

+ NVIDIA 相关理论基础知识

## NVIDIA 驱动安装

+ Ubuntu下安装NVIDIA驱动的三种方法：
  + 使用标准Ubuntu仓库进行自动安装
  + 使用PPA仓库进行自动化安装
  + 使用官方的NVIDIA驱动进行手动安装

+ 第一种方法操作最为简单，方便，第三种方法是最稳定，最常用的。

+ 使用标准Ubuntu 仓库进行自动安装
```bash
sudo ubuntu-drivers devices

sudo ubuntu-drivers autoinstall

# 完成后重启 就可完成安装NVIDIA驱动
```

+ 使用PPA仓库进行自动安装
```bash
sudo add-apt-repository ppa:graphics-drivers/ppa      //添加ppa库到系统中
sudo apt update         //  更新
 
sudo ubuntu-drivers devices // 显示可以安装的nvidia驱动


sudo apt install nvidia-xxx        //  xxx  代表你想安装的nVidia驱动的版本号
```

+ 使用官方的NVIDIA驱动进行手动安装
  + 先要搞清楚你的nvidia显卡是什么什么型号
```bash
lshw -numeric -C display

或者

lspci -vnn | grep VGA  // 查看nvidia显卡型号
```
  + 然后到NVIDIA官网下载对应你显卡型号的最新版本驱动进行下载  保存到你自己的路径文件夹
  + NVIDIA官网驱动下载地址： https://www.nvidia.com/zh-cn/           进入后选择最上面的驱动程序 就可以自行选择自己的显卡
```bash
//   这种方法安装nvidia驱动需要先停止图形界面

sudo telinit 3

//   之后进入一个新的命令行会话，使用当前的用户名密码登陆

用cd 进入你放nvidia驱动的路径

用 ./  或者  bash  进行安装

安装的过程如下：(按照以下步骤)

Accept License

The distribution-provided pre-install script failed! Are you sure you want to continue?
CONTINUE INSTALLATION

Would you like to run the nvidia-xconfig utility?
YES

之后执行
sudo reboot // 重启
```

+ 上面三种方法结束后，需要检验是否安装好了nvidia驱动。
```bash
sudo reboot  // 安装完了驱动需要重启

sudo nvidia-smi  //  检验是否安装好驱动
```