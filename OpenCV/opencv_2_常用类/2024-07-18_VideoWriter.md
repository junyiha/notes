---
category: OpenCV
date: 2024-07-18 09:00:00 +0800
layout: post
title: VideoWrite
tag: OpenCV
---
## 简介

+ cv::VideoWrite类相关笔记

## OpenCV cv::VideoWriter 是什么

`cv::VideoWriter` 是 OpenCV 库中的一个类，用于视频文件的创建和写入。它允许你从图像序列中生成视频文件或从摄像头流中录制视频。该类提供了各种方法来设置视频的编码格式、帧率、帧大小等参数。

以下是 `cv::VideoWriter` 的一些主要功能和使用方法：

### 构造函数
`cv::VideoWriter` 的构造函数可以用来创建一个新的视频写入器对象。主要有两种常见的构造方式：

1. 使用默认构造函数，然后调用 `open` 方法：
   ```cpp
   cv::VideoWriter writer;
   writer.open(filename, fourcc, fps, frameSize, isColor);
   ```

2. 使用带参数的构造函数：
   ```cpp
   cv::VideoWriter writer(filename, fourcc, fps, frameSize, isColor);
   ```

### 参数解释
- `filename`：视频文件的名称，包含路径和扩展名。
- `fourcc`：视频编解码器的四字符代码。例如，使用 `cv::VideoWriter::fourcc('M', 'J', 'P', 'G')` 表示 Motion JPEG 编码。
- `fps`：视频的帧率（每秒帧数）。
- `frameSize`：每帧图像的大小（宽度和高度）。
- `isColor`：布尔值，指示视频是彩色还是灰度。`true` 表示彩色，`false` 表示灰度。

### 常用方法
- `open`：打开视频文件以进行写入。
- `isOpened`：检查视频文件是否已成功打开。
- `write`：将一帧图像写入视频文件。
- `release`：释放视频写入器并关闭文件。

### 示例代码
以下是一个简单的示例代码，演示如何使用 `cv::VideoWriter` 录制视频：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 视频文件名和编码格式
    std::string filename = "output.avi";
    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    double fps = 30.0;
    cv::Size frameSize(640, 480);

    // 创建 VideoWriter 对象
    cv::VideoWriter writer(filename, fourcc, fps, frameSize, true);

    // 检查 VideoWriter 是否成功打开
    if (!writer.isOpened()) {
        std::cerr << "Could not open the output video file to write" << std::endl;
        return -1;
    }

    // 打开摄像头
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Could not open the camera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        // 读取摄像头帧
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        // 写入帧到视频文件
        writer.write(frame);

        // 显示帧
        cv::imshow("Frame", frame);
        if (cv::waitKey(10) == 27) {
            break; // 按下 'Esc' 键退出
        }
    }

    // 释放资源
    cap.release();
    writer.release();
    cv::destroyAllWindows();

    return 0;
}
```

这个示例代码打开默认摄像头，将捕获的视频帧写入到名为 `output.avi` 的文件中，并实时显示捕获的帧。