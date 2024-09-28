---
category: OpenCV
date: 2024-08-29 09:00:00 +0800
layout: post
title: VideoCapture
tag: OpenCV
---
## 简介

+ OpenCV中 VideoCapture类学习笔记

## VideoCapture的功能

+ 一个用于从视频文件，图片序列或者相机捕获视频的类
+ 包含的头文件
```cpp
#include <opencv2/videoio.hpp>
```

## 公有成员函数

+ 默认构造函数
```cpp
VideoCapture()
```

+ 打开一个视频文件，或者是捕获设备或网络视频流通过API引用和参数进行视频捕获
```cpp
VideoCapture(const String &filename, int apiPreference, const std::vector<int> &params)
```

+ 打开一个视频文件，或者是捕获设备或网络视频流通过API引用进行视频捕获
```cpp
VideoCapture(const String &filename, int apiPreference = CAP_ANY)
```

+ 打开一个相机，通过API引用和参数进行视频捕获
```cpp
VideoCapture(int index, int apiPerference, const std::vector<int> &params)
```

+ 打开一个相机用于视频捕获
```cpp
VideoCapture(int index, int apiPerference = CAP_ANY)
```

+ 默认析构函数
```cpp
virtual ~VideoCapture()
```

+ 返回指定VideoCapture属性
```cpp
virtual double get(int propild) const;
```

+ 返回使用的后端API名字
```cpp
String getBackendName() const;
```

+ 查询异常模式是否激活
```cpp
bool getExceptionMode() const;
```

+ 从视频文件或者捕获设备获取下一帧数据
```cpp
virtual bool grab();
```

+ 如果视频捕获对象已经被初始化，则返回true
```cpp
virtual bool isOpened() const;
```

+ 打开一个视频文件，或者是捕获设备或网络视频流通过API引用和参数进行视频捕获
```cpp
virtual bool open(const String &filename, int apiPreference, const std::vector<int> &params);
```

+ 打开一个视频文件，或者是捕获设备或网络视频流通过API引用进行视频捕获
```cpp
virtual bool open(const String &filename, int apiPreference = CAP_ANY);
```

+ 打开一个相机，通过API引用和参数进行视频捕获
```cpp
virtual bool open(int index, int apiPreference, const std::vector<int> &params);
```

+ 打开一个相机用于视频捕获
```cpp
virtual bool open(int index, int apiPreference = CAP_ANY);
```

+ 用于读取下一个视频帧的流操作符
```cpp
virtual VideoCapture & operator>>(Mat &image);
virtual VideoCapture & operator>>(UMat &image);
```

+ 获取，解码并返回下一个视频帧
```cpp
virtual bool read(OutputArray image);
```

+ 关闭视频文件或者捕获设备
```cpp
virtual void release();
```

+ 解码并返回获取的视频帧
```cpp
virtual bool retrieve(OutputArray image, int flag = 0);
```

+ 在VideoCapture设置一个属性
```cpp
virtual bool set(int propld, double value)
void setExceptionMode(bool enable)
```