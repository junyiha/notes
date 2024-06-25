---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: video_process_code01
tag: ProjectOfVideoContentAnalysis
---

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

## `advance/image.h`

+ 概述：
  + 图像操作

### image_load

+ 功能：加载图像  -- 源数据从文件中读取
+ 原型：`Image *image_load(const char *file);`
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

+ 功能：加载图像  -- 源数据从内存中读取
+ 原型：`Image *image_load2(const char *data,size_t size);`
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

+ 功能：保存图片  -- 输出到文件，返回一个文件名
+ 原型：`int image_save(Image *img, const char *file);`
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

+ 功能：保存图片  -- 输出到内存中，返回一个指向数据内存块的二级指针
+ 原型：`int image_save2(Image *img,void **out_data, int *out_size);`
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

+ 功能：卸载引擎
+ 原型：`void engine_conf_free(engine_conf_handle_t *handle);`
+ 参数：
  + `handle`  -- engine_conf_handle_t结构体类型的指针，引擎资源句柄
+ 返回值：
  + 空
+ 需求：
  + 头文件：`contrib/infer.h`
+ 注意:
  + 要理解引擎和模型的关系

### engine_conf_alloc

+ 功能：加载引擎
+ 原型：`engine_conf_handle_t engine_conf_alloc(const char *conf,int retry);`
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

+ 功能：获取引擎的状态信息
+ 原型：`int engine_conf_state(engine_conf_handle_t handle);`
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

## `contrib/jpeg.h`

+ 概述：
  + JPEG编码器

### jcodec_free()

+ 功能：删除编解码器
+ 原型：`void jcodec_free(JPEGCodec **ctx);`
+ 参数：
  + `ctx`  --  JPEG编解码器环境句柄
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`Nvidia  nv_jcodec_free() | BitMainland  bm_jcodec_free()`
  + 不同平台的函数实现，又依赖于不同平台的类方法，例如`Nvidia::NvJPEGDecode::destory(), Nvidia::NvJPEGEncode::destory() | BitMainland::BmJPEGDecode::destory(), BitMainland::BmJPEGEncode::destory()`

### jcodec_alloc()

+ 功能：创建编解码器
+ 原型：`JPEGCodec *jcodec_alloc()`
+ 参数：无
+ 返回值：
  + 成功  --  返回JPEG编解码器环境句柄
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`Nvidia nv_jcodec_alloc() | BitMainland bm_jcodec_alloc()`
  + 不同平台的函数实现，其内部调用了`calloc()`

### jcodec_encode()

+ 功能：编码
+ 原型：`int jcodec_encode(JPEGCodec *ctx, const Image *in_img, void **out_data, int *out_size);`
+ 参数：
  + `ctx`  --  JPEG编解码器环境句柄
  + `in_img`   --  输入的需要编码的图像结构
  + `out_data` --  输出编码后的码流数据
  + `out_size` --  编码后的码流数据报的大小
+ 返回值：
  + 成功  --  >= 0
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`Nvidia nv_jcodec_encode() | BitMainland bm_jcodec_encode()`
  + 不同平台的函数实现，又依赖于不同平台的类方法，例如`Nvidia::NvJPEGEncode::encode() | BitMainland::BmJPEGEncode::encode()`

### jcodec_decode()

+ 功能：解码
+ 原型：`int jcodec_decode(JPEGCodec *ctx, const void *in_data, const int in_size, Image *out_img);`
+ 参数：
  + `ctx`  --  JPEG编解码器环境句柄
  + `in_data`  --  输入的需要解码的码流数据报
  + `in_size`  --  需要解码的数据长度
  + `out_img`  --  解码后的图像
+ 返回值：
  + 成功  --  >= 0
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`Nvidia nv_jcodec_decode() | BitMainland bm_jcodec_decode()`
  + 不同平台的函数实现，又依赖于不同平台的类方法，例如`Nvidia::NvJPEGEncode::decode() | BitMainland::BmJPEGEncode::decode()`

### jcodec_encode2file()

+ 功能：编码写入文件
+ 原型：`int jcodec_encode2file(JPEGCodec *ctx, const Image *in_img, const char *out_file);`
+ 参数：
  + `ctx`  --  编解码器环境句柄
  + `in_img`   --  输入需要编码的图像
  + `out_file` --  需要接收编码码流数据的文件
+ 返回值：
  + 成功  --  >= 0
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于`jcodec_encode()`将图像编码，之后使用`fopen(), fwrite()`将编码后的码流写入到文件`out_file`

### jcodec_decode_file()

+ 功能：从文件中解码
+ 原型：`int jcodec_decode_file(JPEGCodec *ctx, const char *in_file, Image *out_img);`
+ 参数：
  + `ctx`  --  编解码器环境句柄
  + `in_file`  --  存放需要解码的码流数据的文件
  + `out_img`  --  解码后的图像
+ 返回值：
  + 成功  --  >= 0
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于 `open() fstat() mmap()` 将文件中的码流数据映射到内存中，之后调用`jcodec_decode()`解码

---------------------------------------------------------------------------------

## `advance/Touch.hpp`

+ 概述：
  + 模型的处理，加载，卸载等操作

### `Touch` 类

+ 命名空间：`aicontrib`
+ 功能：推理部分的实现
+ 类属性：
  + 公共属性：
    + `m_ctx`  --  推理环境
    + `m_fetch_p`  --  类`Model`的实例
  + 受保护属性：
    + `m_engine_type`  --  引擎类型名
    + `m_label_normalize_map`  --  字典类型，用于标签标准化
    + `m_ignore_getbbox_post`  --  调试参数，是否忽略GetBBox后处理：!0 忽略， 0 正常
+ 类方法：
  + 公共类方法：
    + `Touch()`  --  构造函数， 初始化类属性
    + `~Touch()` --  虚析构函数，调用类方法`Destory()`
    + `GetType()`
      + 功能：获取引擎类型
      + 原型：`const char* GetType();`
      + 参数：无
      + 返回值：
        + 成功  --  返回一个指向保存引擎类型的C字符串指针
        + 失败  --  返回空
    + `IsOpen()`
      + 功能：判断引擎是否加载成功
      + 原型：`bool IsOpen();`
      + 参数：无
      + 返回值：
        + 成功  -- 返回True，表示引擎已成功加载
        + 失败  -- 返回False，表示引擎未成功加载
    + `Destory()`
      + 功能：销毁引擎
      + 原型：`void Destory();`
      + 参数：无
      + 返回值：无
      + 注意：
        + 其内部实现是基于 `infer.cpp`
        + 能够加载不同类型的模型并运行的原理是，为每一个类型的模型都创建一个类，通过判断操作不同的类实例
    + `Create()`
      + 功能：创建一个引擎环境
      + 原型：`bool Create(const char* engine);`
      + 参数：
        + `engine`  --  引擎名
      + 返回值：
        + 成功 -- 返回True
        + 失败 -- 返回False
      + 注意：
        + 其内部实现是基于 `infer.cpp`
        + 能够加载不同类型的模型并运行的原理是，为每一个类型的模型都创建一个类，通过判断操作不同的类实例
    + `Execute()`
      + 虚函数  --  执行推理
      + 一
        + 功能：执行推理功能
        + 原型：`virtual void Execute(Image* imgs[], int count /*=1 */);`
        + 参数：
          + `imgs`  --  保存数据类型为Image结构体的数组
          + `count` --  图片的数量
        + 返回值：无
        + 注意：
          + 其内部实现是调用 `infer.cpp` 下的 `infer_execute()` 函数
      + 二
        + 原型：`virtual void Execute(std::vector<Image *> &imgs);`
        + 功能：执行推理功能
        + 参数：
          + `imgs`  --  保存数据类型为Image结构体类型的向量容器
        + 返回值：无
        + 注意：
          + 其内部实现是调用函数重载一
    + `GetBBox()`
      + 虚函数 --  获取目标检测框
      + 一
        + 原型：`virtual void GetBBox(std::vector<std::vector<aicontrib::BoxMat>> &objects, const std::vector<float> &min_prob, const std::vector<float> &nms_prob);`
        + 功能：根据输入的阈值，获取检测框的位置信息
        + 参数：
          + `objects`   --  存储检测框的位置信息的二维向量，其是指向存储数据类型为`aicontrib::BoxMat`类 类型的二维向量的指针
          + `min_prob`  --  存储阈值的向量，指向存储数据类型为`float`的向量指针
          + `nms_prob`  --  存储非最大抑制阈值的向量，指向存储数据类型为`float`的向量指针
        + 返回值：无
        + 注意：
          + 这个重载函数是最底部，被调用的
      + 二
        + 原型：`virtual void GetBBox(std::vector<std::vector<aicontrib::BoxMat>> &objects, std::vector<Image *> &imgs, const std::vector<float> &min_prob, const std::vector<float> &nms_prob);`
        + 功能：根据输入的多张图像和多个阈值，获取检测框的位置信息
        + 参数：
          + `objects`  --  存储检测框的位置信息的二维向量，其是指向存储数据类型为`aicontrib::BoxMat`类 类型的二维向量的指针
          + `imgs`     --  存储被检测图片的向量，其是指向存储数据类型为指向`Image`结构体的指针类型的向量的指针
          + `min_prob` --  存储阈值的向量，指向存储数据类型为`float`的向量指针
          + `nms_prob`  --  存储非最大抑制阈值的向量，指向存储数据类型为`float`的向量指针
        + 返回值：无
        + 注意：
          + 其图片输入的方式是存放`Image`结构体指针的向量
          + 检测多张图片，多个阈值的重载函数
      + 三
        + 原型：`virtual void GetBBox(std::vector<aicontrib::BoxMat> &objects, Image *img, float min_prob, float nms_prob);`
        + 功能：根据输入的单张图像和单个阈值，获取检测框的位置信息
        + 参数：
          + `objects`  --  存储检测框的位置信息的向量，其是指向存储数据类型为`aicontrib::BoxMat`类 类型的向量指针
          + `img`      --  被检测的图片，其是指向`Image`结构体的指针
          + `min_prob` --  检测阈值
          + `nms_prob` --  非最大抑制阈值
        + 返回值：无
        + 注意：
          + 检测单张图片，单个阈值的重载函数
    + `GetOCR`
      + 虚函数  --  获取目标检测信息
      + 一
        + 原型：`virtual void GetOCR(std::vector<std::vector<int32_t>> &objects, const std::vector<float> &min_prob);`
        + 功能：根据输入的阈值，检测文字信息
        + 参数：
          + `objects`  --  存储检测到的文字信息，其是指向存储`int32_t`数据类型的二维向量的指针
          + `min_prob` --  存储多个阈值，其是指向存储`float`数据类型的向量的指针
        + 返回值：无
        + 注意：
          + 此重载函数，是实现部分，也就是说，下面两个重载函数是依赖于这个函数实现的
      + 二
        + 原型：`virtual void GetOCR(std::vector<std::vector<int32_t>> &objects, std::vector<Image *> &imgs, const std::vector<float> &min_prob);`
        + 功能：根据输入的多张图片和多个阈值，检测文字信息
        + 参数：
          + `objects`  --  存储检测到的文字信息，其是指向存储`int32_t`数据类型的二维向量的指针
          + `imgs`     --  存储多张图片信息，其是指向存储`Image`结构体指针的向量的指针
          + `min_prob` --  存储多个阈值，其是指向存储`float`数据类型的向量的指针
        + 返回值：无
        + 注意：
          + 其内部实现是基于第一个重载函数
      + 三
        + 原型：`virtual void GetOCR(std::vector<int32_t> &objects, Image *img, float min_prob);`
        + 功能：根据输入的单张图片和单个阈值，检测文字信息
        + 参数：
          + `objects`  --  存储检测到的文字信息，其是指向存储`int32_t`数据类型的向量的指针
          + `img`      --  图片信息，其是指向`Image`结构体的指针
          + `min_prob` --  阈值
        + 返回值：无
        + 注意：
          + 其内部实现，是创建一个图片向量，接收传入的图片，并调用第二个重载函数
    + `GetFeature` 
      + 虚函数  --  获取检测目标的特征信息
      + 一
        + 原型：`virtual void GetFeature(std::vector<std::vector<float>> &objects);`
        + 功能：获取特征信息
        + 参数：
          + `objects`  --  存储特征信息，其是指向存储`float`数据类型的二维向量的指针
        + 返回值：无
        + 注意：
          + 此重载函数是实现部分，换言之，下面两个重载函数都是基于这个函数实现的
      + 二
        + 原型：`virtual void GetFeature(std::vector<std::vector<float>> &objects, std::vector<Image *> &imgs);`
        + 功能：接收多张图片，获取特征信息
        + 参数：
          + `objects`  --  存储特征信息，其是指向存储`float`数据类型的二维向量的指针
          + `imgs`     --  存储多张图片信息，其是指向存储`Image`结构体指针的向量的指针
        + 返回值：无
        + 注意：
          + 其内部实现，是基于第一个重载函数
      + 三
        + 原型：`virtual void GetFeature(std::vector<float> &objects, Image *img);`
        + 功能：接收单张图片，获取特征信息
        + 参数：
          + `objects`  --  存储特征信息，其是指向`float`数据类型的向量的指针
          + `img`      --  图片信息，其是指向`Image`结构体的指针
        + 返回值：无
        + 注意：
          + 其内部实现，是创建一个二维向量，存储接收的单张图片，并调用第二个重载函数
    + `GetSort`
      + 虚函数  --  获取排序后的数据
      + 一
        + 原型：`virtual void GetSort(std::vector<std::vector<std::pair<int, float>>> &objects);`
        + 功能：获取排序数据
        + 参数：
          + `objects`  --  存储排序结果，其是指向存储数据类型为`pair`（对组）的三维向量的指针
        + 返回值：无
        + 注意：
          + 此重载函数是实现部分，换言之，下面两个重载函数都是基于此函数
      + 二
        + 原型：`virtual void GetSort(std::vector<std::vector<std::pair<int, float>>> &objects, std::vector<Image *> &imgs);`
        + 功能：接收多张图片，获取排序结果
        + 参数：
          + `objects`  --  存储排序结果，其是指向存储数据类型为`pair`（对组）的三维向量的指针
          + `imgs`     --  多张图片，其是指向存储`Image`结构体指针的向量的指针
        + 返回值：无
        + 注意：
          + 其内部实现，是基于第一个重载函数
      + 三
        + 原型：`virtual void GetSort(std::vector<std::pair<int, float>> &objects, Image *img);`
        + 功能：接收单张图片，获取排序结果
        + 参数：
          + `objects`  --  存储排序结果，其是指向存储数据类型为`pair`(对组)的二维向量的指针
          + `imgs`     --  单张图片信息，其是`Image`结构体指针
        + 返回值：无
        + 注意：
          + 其内部实现，是创建一个三维向量，存储接收的单张图片，并调用第二个重载函数

-----------------------------------------------------------------------------------------------------------

## `contrib/args.hpp`

+ 概述：
  + 参数解析器，处理接收的参数

### `args` 类

+ 命名空间：`aicontrib`
+ 功能：参数解析器
+ 类属性：
  + 私有属性：
    + `m_key_prefix`  --  保存键的字符串
    + `m_data`        --  数据，map数据类型，一个键绑定一个存储`string`数据类型的向量
+ 类方法：
  + 公共方法：
    + `inline args::args(const char *key_prefix = "--");`  --  构造函数，内部实现是基于`reset()`方法,传入
    + `inline args::~args();`  -- 虚析构函数
    + `copy_from()`
      + 原型：`inline void args::copy_from(const args &src);`
      + 功能：从参数`src`拷贝，换言之，将参数`src`中的键和数据拷贝到`m_key_prefix`和`m_data`
      + 参数：
        + `src`  --  需要拷贝的数据，其是`args`类的实例
      + 返回值：无
    + `copy_to()`
      + 原型：`inline void args::copy_to(args &dst);`
      + 功能：将数据拷贝到参数`dst`，换言之，将`m_key_prefix`和`m_data`拷贝到`dst`
      + 参数：
        + `dst`  -- 要拷贝到的目标对象，其是`args`类的实例
      + 返回值：无
    + `reset()`
      + 原型：`inline void args::reset(const char *key_prefix /*="--" */);`
      + 功能：重置默认键前缀，默认为`--`
      + 参数：
        + `key_prefix`  --  指向键前缀的字符指针
      + 返回值：无
    + `dump()`
      + 虚函数  --  参数转储到文件
      + 一
        + 原型：`inline virtual ssize_t args::dump(void *buf, size_t size);`
        + 功能：将内存中的指定长度的数据存储到文件中
        + 参数：
          + `buf`  --  数据内存块指针
          + `size` --  数据内存块大小
        + 返回值：
          + 成功  --  1
          + 失败  --  0
        + 注意：
          + 其内部调用重载函数`dump()`
      + 二
        + 原型：`inline virtual ssize_t args::dump(FILE *output /*=stderr */);`
        + 功能：将键和值的数据写入文件`output`
        + 参数：
          + `output`  --  要写入的文件句柄
        + 返回值：
          + 成功  --  1
          + 失败  --  0
        + 注意：
          + C++11 for循环 迭代 `for(auto &tmp : m_data)`
      + 三
        + 原型：`inline virtual ssize_t args::dump(const char *pathfile);`
        + 功能：将键和值的数据写入文件`pathfile`
        + 参数：
          + `pathfile`  --  要写入的文件路径
        + 返回值：
          + 成功  --  1
          + 失败  --  0
        + 注意：
          + 其内部实现是基于第二个重载函数，这个重载函数使用`fopen()`打开一个文件，然后符合第二个重载函数的参数格式
    + `parse()`
      + 虚函数  --  参数分析
      + 一
        + 原型：`inline virtual void args::parse(int argc, char *argv[]);`
        + 功能：接收输入参数，并分析
        + 参数：
          + `argc`  --  参数个数
          + `argv`  --  参数，其是存储多个参数信息的字符数组指针
        + 返回值：无
        + 注意：
          + 这个重载函数，是接收函数调用方式传入的参数
      + 二
        + 原型：`inline virtual void args::parse(FILE *file, const char *argv0 /*=NULL*/, int delim /*= '\n' */);`
        + 功能：从文件中读取参数，并分析
        + 参数：
          + `file`  --  存储参数信息的文件指针
          + `argv0` --  字符指针
          + `delim` --  自定义字符，默认为换行符 `\n`
        + 返回值：无
        + 注意：
          + 其内部调用了 `general.h` 文件下的函数 `getdelim_with_note()` 和 `strtrim_both()`
      + 三
        + 原型：`inline virtual void args::parse(const void *data, int size, const char *argv0 /*= NULL */, int delim /*= '\n' */);`
        + 功能：从内存块中读取参数信息，并分析
        + 参数：
          + `data`  --  保存参数信息的内存块指针
          + `size`  --  内存块大小
          + `argv0` --  字符指针， 保存参数
          + `delim` --  自定义字符，默认为换行符`\n`
        + 返回值：无
        + 注意：
          + 其从内存块读取参数信息，保存到文件中，然后调用第二个重载函数
      + 四
        + 原型：`inline virtual void args::parse(const char *pathfile, const char *argv0 /*=NULL */, int delim /*= '\n' */);`
        + 功能：从指定文件路径读取文件参数信息，并分析
        + 参数：
          + `pathfile`  --  文件路径
          + `argv0` --  字符指针， 保存参数
          + `delim` --  自定义字符，默认为换行符`\n`
        + 返回值：无
        + 注意：
          + 其内部实现为，通过`fopen()`打开文件，生成文件句柄，然后调用第二个重载函数
    + `remove()`
      + 虚函数  --  删除指定键和对应的数值
      + 一
        + 原型：`inline virtual void args::remove(const char *key, int idx /*=0 */);`
        + 功能：根据指定的键，删除对应的键值
        + 参数：
          + `key`  --  要删除的键
          + `idx`  --  索引？？？？？？？
        + 返回值：无
        + 注意：
          + 当idx小于0时，直接删除key对应的值
    + `upset()`
      + 虚函数  -- 增加指定的键和值
      + 一
        + 原型：`inline virtual void args::upset(const char *key, const char *value);`
        + 功能：接收键和值，增加到`m_data`中
        + 参数：
          + `key`  -- 要增加的键
          + `value`-- 要增加的值
        + 返回值：无
    + `count()`
      + 虚函数  --  查找键所对应的值的位置
      + 一
        + 原型：`inline virtual int args::count(const char *key);`
        + 功能：查找对应键，返回其在容器中的位置
        + 参数：
          + `key`  --  要查找的键
        + 返回值：
          + 成功  --  返回键对应的值在容器中的位置
          + 失败  --  -1
    + `exist()`
      + 虚函数  --  判断对应的键是否存在
      + 一
        + 原型：`inline virtual bool args::exist(const char *key);`
        + 功能：判断对应的键是否已经存在
        + 参数：
          + `key`  -- 要判断的键
        + 返回值：
          + 存在  --  
          + 不存在--  
    + `value()`
      + 虚函数  --  取键对应的值
      + 一
        + 原型：`inline virtual const char *args::value(const char *key, const char *default_val, int idx /*=0 */);`
        + 功能：根据输入的键，查找对应的值并返回
        + 参数：
          + `key`  --  要查找的键
          + `default_val`  --  默认值
          + `idx`  --  索引？？
        + 返回值：
          + 成功  --  对应值的字符指针
          + 失败  --  默认值的字符指针
    + `valtoi()`
      + 虚函数  --  将键对应的值转换为整数
      + 一
        + 原型：`inline virtual int args::valtoi(const char *key, int default_val, int idx /*=0 */);`
        + 功能：根据接收的键，查找对应的键值，转换为整数并返回
        + 参数：
          + `key`  --  键
          + `default_val`  -- 默认值
          + `idx`  --  索引
        + 返回值：
          + 成功  --  返回键值转换后的整数
          + 失败  --  返回默认值
        + 注意：
          + 其内部实现依赖于`stdlib.h`文件下的`atoi()`函数
    + `valtol()`
      + 虚函数  --  将键对应的值转换为长整数
      + 一
        + 原型：`inline virtual long args::valtol(const char *key, long default_val, int idx /*=0 */);`
        + 功能：根据参数`key`键，查找对应的键值，转换为长整型整数并返回
        + 参数：
          + `key`  --  键
          + `default_val`  --  默认值
          + `idx`  --  索引
        + 返回值：
          + 成功  --  返回键值转换后的长整型整数
          + 失败  --  返回默认值
        + 注意：
          + 返回的是长整型数据
          + 其内部实现依赖于 `stdlib.h` 文件下的 `atol()` 函数
    + `valtof()`
      + 虚函数  --  将键对应的值转换为双精度浮点数
      + 一
        + 原型：`inline virtual double args::valtof(const char *key, double default_val, int idx /*=0 */);`
        + 功能：将键对应的值转换为双精度浮点数，并返回
        + 参数：
          + `key`  -- 键
          + `default_val`  --  默认值
          + `idx`  -- 索引
        + 返回值：
          + 成功  --  返回键值转换后的双精度浮点数
          + 失败  --  返回零(0.0)
        + 注意：
          + 返回的是双精度浮点数
          + 其内部实现依赖于 `stdlib.h` 文件下的 `atof()` 函数

-----------------------------------------------------------------------------------------------------------

## `contrib/general.h`

+ 概述：
  + 实现基础的工具组件

### clock2tick()

+ 功能：获取当前时间，并转换到指定`precision`精度
+ 原型：`uint64_t clock2tick(int8_t type, uint8_t precision);`
+ 参数：
  + `type`  --  时钟ID
  + `precision`  --  精度
+ 返回值：
  + 成功  --  返回转换精度之后的时间
  + 失败  --  返回0
+ 注意：
  + 其内部实现依赖于`time.h`文件下的`clock_gettime()` 和 `mathcalls.h` 文件下的`powl()`

### getdelim_with_note()

+ 功能：从文件中读取流数据到内存中，直到定界符`delim`结束
+ 原型：`int getdelim_with_note(char **line, size_t *length, int delim, FILE *file, char note);`
+ 参数：
  + `line`  --  指向初始缓冲区或空指针的指针
  + `length`--  指向初始缓冲区大小的指针
  + `delim` --  定界线字符
  + `file`  --  有效输入流，由`fopen()`打开
  + `note`  --  
+ 返回值：
  + 成功  --  返回缓冲区的大小
  + 失败  --  返回-1
+ 注意：
  + 其内部实现依赖于`stdio.h`文件下的`getdelim()`函数 和 `ctype.h`文件下的`iscntrl()`函数

### strtrim_right()

+ 功能：右边
+ 原型：`char* strtrim_right(char* string, uint8_t c);`
+ 参数：
  + `string`  --  输入的字符指针
  + `c`       --  
+ 返回值：
  + 成功  --  返回一个字符指针
  + 失败  --  返回NULL

### strtrim_left()

+ 功能：左边
+ 原型：`char* strtrim_left(char* string, uint8_t c);`
+ 参数：
  + `string`  --  输入的字符指针
  + `c`       --  
+ 返回值：
  + 成功  --  返回一个字符指针
  + 失败  --  返回NULL

### strtrim_both()

+ 功能：左右两边
+ 原型：`char* strtrim_both(char* string, uint8_t c);`
+ 参数：
  + `string`  --  输入的字符指针
  + `c`       --  
+ 返回值：
  + 成功  --  返回一个字符指针
  + 失败  --  返回NULL

### mem_dup()

+ 功能：将一块内存上的数据转储到另一块内存
+ 原型：`void* mem_dup(const void* data, long len);`
+ 参数：
  + `data`  --  需要转储的内存块指针
  + `len`   --  内存块的大小
+ 返回值：
  + 成功  --  返回新的内存块指针
  + 失败  --  返回NULL
+ 注意：
  + 其内部实现，是基于`memcpy()`函数

### mkpath()

+ 功能：创建权限为`mode`的目录文件`path`
+ 原型：`void mkpath(const char* path, uint32_t mode);`
+ 参数：
  + `path`  --  文件路径
  + `mode`  --  文件权限
+ 返回值：无
+ 注意：
  + 其内部实现，依赖于`strlen(), strdup(), access(), mkdir(), chmod()`

### file_close()

+ 功能：关闭文件`file`
+ 原型：`void file_close(int* file);`
+ 参数：
  + `file`  --  需要关闭的文件的文件描述符
+ 返回值：无
+ 注意：
  + 其内部实现，依赖于`close()`

### file_open()

+ 功能：打开指定文件
+ 原型：`int file_open(const char* pathfile, int read_only, int non_block, int try_create);`
+ 参数：
  + `pathfile`  --  需要操作的文件
  + `read_only` --  设置为只读模式
  + `non_block` --  设置为非阻塞模式
  + `try_create`--  尝试创建文件
+ 返回值：
  + 成功  --  
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于`open()`

### file_reopen()

+ 功能：将已经打开的文件，重复打开
+ 原型：`int file_reopen(int file, const char* pathfile, int read_only, int non_block, int try_create);`
+ 参数：
  + `file`  --  需要重复打开的文件描述符
  + `pathfile`  --  需要操作的文件
  + `read_only` --  设置为只读模式
  + `non_block` --  设置为非阻塞模式
  + `try_create`--  如果文件不存在，尝试创建文件
+ 返回值：
  + 成功  --  返回重复打开的文件描述符
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于`file_open(), dup2()`

### file_write()

+ 功能：将大小为`size`的数据`data`写入到文件`file`
+ 原型：`long file_write(int file, const void *data, long size);`
+ 参数：
  + `file`  --  要写入数据的文件
  + `data`  --  要写入的数据
  + `size`  --  要写入的数据的大小
+ 返回值：
  + 成功  --  返回写入的数字
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于`write()`

### file_read()

+ 功能：将大小为`size`的数据从文件`file`读取到内存地址为`data`中
+ 原型：`long file_read(int file, void* data, long size);`
+ 参数：
  + `file`  --  要被读取数据的文件
  + `data`  --  存放数据的内存块指针
  + `size`  --  要读取的数据大小
+ 返回值：
  + 成功  --  返回读取的读取的数字
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于`read()`

### file_mmap()

+ 功能：将文件`file`中大小为`size`映射到内存中
+ 原型：`void* file_mmap(int file, size_t *size);`
+ 参数：
  + `file`  --  需要映射数据的文件
  + `size`  --  需要映射的数据大小
+ 返回值：
  + 成功  --  实际映射地址
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于`mmap()`

### dirname_dup()

+ 功能：返回文件`pathfile`的目录部分
+ 原型：`char* dirname_dup(const char* pathfile);`
+ 参数：
  + `pathfile`  --  需要查找目录的文件
+ 返回值：
  + 成功  --  文件所在的目录
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于`dirname(), strdup()`

### basename_dup()

+ 功能：去掉文件`pathfile`的前缀，只保存文件名(input string:/data/test.cpp , output string:test.cpp)
+ 原型：`char* basename_dup(const char *pathfile);`
+ 参数：
  + `pathfile`  --  需要操作的文件
+ 返回值：
  + 成功  --  文件名
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于`basename()`

### proc_pathfile()

+ 功能：获取当前运行程序的绝对路径，存储到`pathfile`，并返回
+ 原型：`char* proc_pathfile(char* pathfile);`
+ 参数：
  + `pathfile`  --  存储程序的绝对路径
+ 返回值：
  + 成功  --  返回运行程序的绝对路径指针
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于`readlink()` 和 `/proc/self/exe`

### proc_path()

+ 功能：截取文件名
+ 原型：`char* proc_path(char* path);`
+ 参数：
  + `path`  --  要处理的文件
+ 返回值：
  + 成功  --  截取成功的文件名
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于`strrchr()`

### proc_name()

+ 功能：处理文件名
+ 原型：`char* proc_name(char* name);`
+ 参数：
  + `name`  --  文件名
+ 返回值：
  + 成功  --  处理过的文件名
  + 失败  --  NULL

### proc_popen()

+ 功能：创建输入，输出管道，操作文件
+ 原型：`int proc_popen(const char* cmd, int* in_pipe, int* out_pipe, int* err_pipe);`
+ 参数：
  + `cmd`  --  `/bin/sh`要执行的命令
  + `in_pipe`  --  
  + `out_pipe` -- 
  + `err_pipe` -- 
+ 返回值：
  + 成功  --  返回子进程
  + 失败
+ 注意：
  + 其内部实现，依赖于上面所有文件基础操作函数和`pipe(), fork(), execl(), _exit()`

### freep()

+ 功能：释放二级指针`pptr`
+ 原型：`void freep(void **pptr);`
+ 参数：
  + `pptr`  --  需要释放的二级指针
+ 返回值：空

### download_file()

+ 功能：下载文件
+ 原型：`int download_file(const char *src, const char *dst, char err[1000]);`
+ 参数：
  + `src`  --  
  + `dst`  -- 
  + `err`  -- 
+ 返回值：
  + 成功  --  0
  + 失败  --  
+ 注意：
  + 其内部实现，依赖于以上所有基础操作函数和`fork(), waitpid()`，下载文件的命令依赖于`wget`命令

### download_tmpfile()

+ 功能：下载临时文件
+ 原型：`int download_tmpfile(const char *src, char *dst, char err[1000]);`
+ 参数：
  + `src`  --  
  + `dst`  -- 
  + `err`  -- 
+ 返回值：
  + 成功  --  0
  + 失败  --  
+ 注意：
  + 其内部实现，依赖于`download_file()`和`mkstemp()`

### log_open()

+ 功能：打开日志功能
+ 原型：`void log_open(uint16_t service, int copy2stderr, int verbose);`
+ 参数：
  + `service`  --  服务ID
  + `copy2stderr`  --  
  + `verbose`  --  冗余
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于`openlog(), setlogmask()`和`abcdk_log_open(), abcdk_log_mask()`

### log_vprintf()

+ 功能：格式化输出日志信息
+ 原型：`void log_vprintf(int priority, const char *fmt, va_list ap);`
+ 参数：
  + `priority`  --  类型
  + `fmt`       --  格式
  + `ap`        --  可变参数
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于`abcdk_log_vprintf()`

### log_printf()

+ 功能：打印日志信息
+ 原型：`void log_printf(int priority, const char *fmt,...);`
+ 参数：
  + `priority`  --  类型
  + `fmt`       --  格式
+ 返回值：空
+ 注意：
  + 其内部实现依赖于`log_vprintf()`

-----------------------------------------------------------------------------------------------------------

## `contrib/ndarray.hpp`

+ 概述：
  + 多维数组

### `ndarray`模板类

+ 命名空间：`aicontrib`
+ 功能：多维数组的计算和处理
+ 类属性：
  + 公有属性：
    + `m_data`   --  
    + `m_format` --  格式
    + `m_blocks` --  块，
    + `m_height` --  高度
    + `m_width`  --  宽度
    + `m_pitch`  --  宽步长`bytes`
    + `m_depth`  --  深度
+ 类方法：
  + 公有方法：
    + `ndarray()`
      + 构造函数，初始化环境
      + 一
        + 功能：初始化环境，将公有属性初始化
        + 原型：`ndarray()；`
      + 二
        + 功能：使用接收到的参数，初始化类
        + 原型：`ndarray(T *data, ndarray_format fmt, uint32_t blocks, uint32_t depth, uint32_t height, uint32_t width, uint32_t align);`
        + 参数：
          + `data`   --  数据指针，换言之，数组要存放的数据
          + `fmt`    --  格式
          + `blocks` --  块，
          + `depth`  --  深度
          + `height` --  高度
          + `width`  --  宽度
          + `align`  --  宽步长 `bytes`
    + `virtual ~ndarray()`  --  虚析构函数
    + size_align()
      + 虚函数  --  字节对齐
      + 一
        + 功能：字节对齐
        + 原型：`virtual size_t size_align(size_t size, size_t align);`
        + 参数：
          + `size`  --  
          + `align` -- 
        + 返回值：
          + 成功  --  对其的字节数？？？
    + set()
      + 虚函数  --  设置类属性
      + 一
        + 功能：接收参数，初始化类属性
        + 原型：`virtual void set(T *data, ndarray_format fmt, uint32_t blocks, uint32_t depth, uint32_t height, uint32_t width, uint32_t align);`
        + 参数：
          + `data`   --  数据指针，换言之，数组要存放的数据
          + `fmt`    --  格式
          + `blocks` --  块，
          + `depth`  --  深度
          + `height` --  高度
          + `width`  --  宽度
          + `align`  --  宽步长 `bytes`
        + 返回值：空
        + 注意：
          + 其内部实现，调用了`set_pitch()`
    + set_pitch()
      + 虚函数  --  ？？？
      + 一
        + 功能：
        + 原型：`virtual void set_pitch(uint32_t align);`
        + 参数：
          + `align`  --  宽步长
        + 返回值：空
        + 注意： 
          + 其内部调用了`size_align()`
    + seek_p()
      + 虚函数  --  查找？？
      + 一
        + 功能：
        + 原型：`virtual const T *seek_p(uint32_t n, uint32_t x, uint32_t y, uint32_t z);`
        + 参数：
          + `n`  -- 
          + `x`  -- 
          + `y`  --
          + `z`  --
        + 返回值：
          + 成功  --  
          + 失败  --  NULL
        + 注意：
          + 其内部实现，依赖于`general.h`文件下的宏`NCHW_SEEK`
    + seek()
      + 虚函数  --  
      + 一
        + 功能：
        + 原型：`virtual T seek(uint32_t n, uint32_t x, uint32_t y, uint32_t z);`
        + 参数：
          + `n`  -- 
          + `x`  -- 
          + `y`  --
          + `z`  --
        + 返回值：
          + 成功  --  
          + 失败  --  NULL
        + 注意：
          + 其内部实现，依赖于`seek_p()`