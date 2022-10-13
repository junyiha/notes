## 概念

+ 视频文件，是一个容器，里面有多个数据流，例如视频流，音频流，字幕流等
+ 一般为了方便填充，每一个流都分成一个个段，通常称为帧

+ 对于一张图片，一定要知道的信息 ： 宽， 高， 步长， 层级
+ 因为在硬件上，对图像处理进行加速的操作，一般是以块为单位，而不是以像素为单位


+ 为什么设计成宏开关？
  + 有一种情况：在一台机器上有`nvidia`和`bitmainland`两种显卡，所以早期有一个想法是设计为一次编译，两个平台都能使用。
  + 但是，`bitmainland`所使用的的opencv是定制化的，所以和nvidia不能共用，不能实现预期目标
  + 后来，设计为分离编译，不同的硬件平台编译不同的版本
  
## Video

+ 视频信息的结构体
  + `is_writer` -- 判断是推流还是拉流
  + `apiPreference` -- 判断是使用ffmpeg还是HKMVS
  + `dictionary` -- 字典，在`ffmpeg`字典的基础上，存放视频配置参数信息

+ `metadate` -- 元数据，视频的描述性信息

## 接口函数

### `video_process/contrib/ffmpeg_utils.h`

+ `ffmpeg_pixfmt_name()`
  + 功能：获取像素格式
  + 函数原型:`int ffmpeg_pixfmt_bits(int pixfmt, int fetch_padded);`
  + 内部实现：`av_get_pix_fmt_name()`

### `video_process/contrib/nvidia/nv_export_image.hpp`

+ 