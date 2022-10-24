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

--------------------------------------------------------------

## `/advance/image.h`

### image_load

+ 原型：`Image *image_load(const char *file);`
+ 功能：加载图像  -- 源数据从文件中读取
+ 参数：
  + `file` -- 文件名
+ 返回值：
  + 成功 -- 返回一个`Image`结构体指针
  + 失败 -- 
+ 需求：
  + 头文件：`contrib/image.h`
+ 注意：
  + 仅支持jpeg格式

### image_load2

+ 原型：`Image *image_load2(const char *data,size_t size);`
+ 功能：加载图像  -- 源数据从内存中读取
+ 参数：
  + `data` -- 图像数据指针
  + `size` -- 图像数据尺寸
+ 返回值：
  + 成功 -- 返回一个`Image`结构体指针
  + 失败 -- 
+ 需求：
  + 头文件：`contrib/image.h`
+ 注意：
  + 仅支持jpeg格式

### image_save

+ 原型：`int image_save(Image *img, const char *file);`
+ 功能：保存图片  -- 输出到文件，返回一个文件名
+ 参数：
  + `img`  -- Image结构体指针
  + `file` -- 所保存的文件名
+ 返回值：
  + 成功 -- 0
  + 失败 -- !0
+ 需求：
  + 头文件：`contrib/image.h`
+ 注意：
  + 仅支持jpeg格式

### image_save2

+ 原型：`int image_save2(Image *img,void **out_data, int *out_size);`
+ 功能：保存图片  -- 输出到内存中，返回一个指向数据内存块的二级指针
+ 参数：
  + `img`  --  Image结构体指针
  + `out_data` -- 图像数据二级指针
  + `out_size` -- 输出图像数据尺寸  ？？？
+ 返回值：
  + 成功 -- 0
  + 失败 -- !0
+ 需求：
  + 头文件：`contrib/image.h`
+ 注意：
  + 仅支持jpeg格式

## `advance/infer.h`

### engine_conf_free

+ 原型：`void engine_conf_free(engine_conf_handle_t *handle);`
+ 功能：卸载引擎
+ 参数：
  + `handle`  -- engine_conf_handle_t结构体类型的指针，引擎资源句柄
+ 返回值：
  + 空
+ 需求：
  + 头文件：`contrib/infer.h`
+ 注意:
  + 要理解引擎和模型的关系

### engine_conf_alloc

+ 原型：`engine_conf_handle_t engine_conf_alloc(const char *conf,int retry);`
+ 功能：加载引擎
+ 参数：
  + `conf`  -- 引擎配置文件
  + `retry` -- ·重试加载的次数，在加载失败时有效
+ 返回值：
  + 成功 -- 返回引擎环境指针， engine_conf_handle_t结构体
  + 失败 -- NULL
+ 需求：
  + 头文件：`contrib/infer.h`
+ 注意：
  + 异步加载

### engine_conf_state

+ 原型：`int engine_conf_state(engine_conf_handle_t handle);`
+ 功能：获取引擎的状态信息
+ 参数：
  + `handle`  -- 引擎环境指针， engine_conf_handle_t 结构体
+ 返回值：
  + 1   --   未加载 或 加载中
  + 2   --   已加载
  + 3   --   失败
+ 需求：
  + 头文件：`contrib/infer.h`
+ 注意：

---------------------------------------------------------------------------------

## `advance/Touch.hpp`

### Touch类

+ 命名空间：`aicontrib`
+ 