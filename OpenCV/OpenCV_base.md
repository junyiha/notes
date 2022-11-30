## OpenCV概念

+ 图像处理(Image Processing)是用计算机对图像进行分析，以达到所需要的结果的技术，又称影像处理。

+ 图像处理技术一般包括：图像压缩，增强和复原，匹配，描述和时别。
+ 图像处理一般指数字图像处理(Digital Image Processing)。其中，数字图像是指工业相机，摄像机，扫描仪等设备经过拍摄得到的一个大的**二维数组**。该数组的元素称为像素，其值称为灰度值。而数字图像处理是通过计算机对图像进行去除噪声，增强，复原，分割，提取特征等处理的方法和技术。

## OpenCV整体架构

+ 在`/usr/local/include/opencv4/opencv2`目录下的`opencv_modules.hpp`的文件中，存放OpenCV中与新模块构造相关的说明代码，打开可以发现其定义的是OpenCV所有组件的宏
+ 官方文档：`https://docs.opencv.org/4.x/`

### calib3d

+ `Calibration（校准）`和`3D`这两个词的组合缩写。
+ 这个模块主要是相机校准和三维重建相关的内容，包括基本的多视觉几何算法，单个立体摄像头标定，物体姿态估计，立体相似性算法，3D信息的重建等。

### core

+ 核心功能模块
+ 包含内容：
  + OpenCV基本数据结构
  + 动态数据结构
  + 绘图函数
  + 数组操作相关函数
  + 辅助功能与系统函数和宏
  + 与`OpenGL`的交互操作

### features2d

+ 2D Features Framework

+ 人类视觉系统倾向于从给定场景中提取主要特征，然后记住它，这样便于后续的检索。为了模仿这一点，人们开始设计各种特征提取器，用于从给定的图像中提取出这些特征点
+ 流行的算法包括尺度不变特征变换(Scale Invariant Feature Transform, 简称SIFT)，加速鲁棒特征(Speeded Up Robust Features, 简称SURF)和加速分段测试特征(Features From Accelerated Segment Test, 简称FAST)
  
+ Features2D,即2D功能框架，包含如下内容：
  + 特征检测和描述
  + 特征检测器通用接口(Feature Detectors)
  + 描述符提取器通用接口(Descriptor Extractors)
  + 描述符匹配器通用接口(Descriptor Matchers)
  + 通用描述符匹配器通用接口(Generic Descriptor)
  + 关键点描绘函数和匹配功能绘制函数

### flann

+ Clustering and Search in Multi-Dimensional Spaces

+ `Fast Library for Approximate Nearest Neighbors`, 高维的近似近邻快速搜索算法库，包含：快速近似最近邻搜索和聚类

### highgui

+ 高层`GUI`图形用户界面，可用于处理所有高级用户界面操作，包含媒体的输入输出，视频捕捉，图像和视频的编码解码，图形交互界面的接口等内容
+ 它有一个等待功能，可以等按下键盘上的一个键才进行下一步，还有一个可以检测鼠标事件的功能，在开发交互式应用程序时非常有用

#### 接口

+ 地址：`https://docs.opencv.org/4.x/d4/dd5/highgui_8hpp.html`

+ 功能：Displays an image in the specified window
+ 原型：`void cv::imshow(const String &winname, InputArray mat);`

+ 功能：Creates a window
+ 原型：`void cv::nameWindow(const String &winname, int flags=WINDOW_AUTOSIZE);`

### imgcodecs

+ Image file reading and writing

#### 接口

+ 功能：Loads an image from a file
+ 原型：`Mat cv::imread(const String &filename, int flags=IMREAD_COLOR);`

+ 功能：Saves an image to a specified file
+ 原型：`cv::imwrite(const String &filename, InputArray img, const std::vector<int> &params=std::vector<int>())'`

### imgproc

+ Image Processing

+ `Image`和`Process`这两个单词的缩写组合，图像处理模块
+ 包含如下内容：
  + 线性和非线性的图像滤波
  + 图像的几何变换
  + 其他图像转换
  + 直方图相关
  + 结构分析和形状描述
  + 运动分析和对象跟踪
  + 特征检测
  + 目标检测等内容
+ 可以执行诸如图像过滤，形态学操作，几何变换，颜色转换，图像绘制，直方图，形状分析，运动分析，特征检测等操作

### ml

+ `Machine Learning`， 机器学习模块，基本上是统计模型和分类算法
+ 包含如下内容：
  + 统计模型(Statistical Models)
  + 一般贝叶斯分类器(Normal Bayes Classifier)
  + K-近邻(K-Nearest Neighbors)
  + 支持向量机(Support V)

### videoio

+ Video I/O, 视频输入和输出

### video

+ Video Analysis，视频分析

### stitching

+ Images stitching

### objdetect

+ Object Detection， 目标检测


### photo

+ Computational Phtotgraphy

### dnn

+ Deep Neural Network module， 深度神经网络模块

### gapi

+ Graph API