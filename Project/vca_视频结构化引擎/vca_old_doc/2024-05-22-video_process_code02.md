---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: video_process_code02
tag: ProjectOfVideoContentAnalysis
---

+ 概述：
  + 字典句柄的数据类型 `dict_handle_t` ， 其内部实际为`dictmap`类型，声明为`typedef std::map<std::string, std::string> dictmap;`
  + 换言之，字典句柄的实质为 键为`string`类型，键值为`string`类型的 `map`类型，

### dict_free()

+ 原型：`void dict_free(dict_handle_t *dict);`
+ 功能：删除字典
+ 参数：
  + `dict`  --  字典句柄
+ 返回值：空

### dict_set()

+ 原型：`void dict_set(dict_handle_t *dict, const char *key, const char *val,...);`
+ 功能：设置字典项
+ 参数：
  + `dict`  --  字典句柄
  + `key`   --  键
  + `val`   --  值，参考`sprintf()`
+ 返回值：空

### dict_get()

+ 原型：`int dict_get(dict_handle_t dict, const char *key, const char *val, ...);`
+ 功能：获取字典项
+ 参数：
  + `dict`  --  字典句柄  -- in
  + `key`   --  键
  + `val`   --  数据格式字符串，参考`sscanf()`
+ 返回值：
  + 成功  --  返回`value`个数
  + 失败  --  返回小于0的数
+ 注意：
  + 其内部实现，依赖于`vsscanf()`

### dict_copy()

+ 原型：`void dict_copy(dict_handle_t *dst, dict_handle_t src);`
+ 功能：复制字典
+ 参数：
  + `dst`  --  目标字典句柄
  + `src`  --  源字典句柄
+ 返回值：
  + 空
+ 注意：
  + 其内部实现，将`dict_handle_t`类型的指针转换为`dictmap*`类型的指针，然后拷贝指针

----------------------------------------------------------------------------------------------------

## `contrib/image.h`

+ 概述：
  + 图像的所有信息，都在内部，将指针转为各平台私有的数据类型指针，
  + 各项功能所实现的方法，都依赖于各平台各自命名空间下的函数或者类的方法

### image_free()

+ 原型：`void image_free(Image **img);`
+ 功能：删除`img`
+ 参数：
  + `img`  --  需要删除的图像句柄
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_free() | bm_image_free()`

### image_alloc()

+ 原型：`Image *image_alloc(int width, int height, int pixfmt, int align);`
+ 功能：创建图像
+ 参数：
  + `width`  --  图像宽度
  + `height` --  图像高度
  + `pixfmt` --  像素格式，参见FFmpeg相关定义
  + `align`  --  行的对其单位（字节）
+ 返回值：
  + 成功  --  图像指针
  + 失败  -- 
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_alloc() | bm_image_free()`

### image_data()

+ 原型：`uint8_t *image_data(const Image *img, int plane);`
+ 功能：获取图像数据指针
+ 参数：
  + `img`  --  图像指针
  + `plane`--  图层
+ 返回值：
  + 成功  --  图像`img`的数据指针
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_data() | bm_image_data()`

### image_stride()

+ 原型：`int image_stride(const Image *img, int plane);`
+ 功能：获取图像数据宽度步长（字节）
+ 参数：
  + `img`  --  图像指针
  + `plane`--  图层
+ 返回值：
  + 成功  --  图像数据宽度
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_stride() | bm_image_stride()`

### image_width()

+ 原型：`int image_width(const Image *img);`
+ 功能：获取图像宽度
+ 参数：
  + `img`  --  图像指针
+ 返回值：
  + 成功  --  图像宽度
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_width() | bm_image_width()`

### image_height()

+ 原型：`int image_height(const Image *img);`
+ 功能：获取图像高度
+ 参数：
  + `img`  --  图像指针
+ 返回值：
  + 成功  --  图像高度
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_height() | bm_image_height()`

### image_pixfmt()

+ 原型：`int image_pixfmt(const Image *img);`
+ 功能：获取图像像素格式
+ 参数：
  + `img`  --  图像指针
+ 返回值：
  + 成功  --  图像像素格式
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_pixfmt() | bm_image_pixfmt()`

### image_size()

+ 原型：`int image_size(const Image *img);`
+ 功能：获取图像占用的空间大小（字节）
+ 参数：
  + `img`  --  图像指针
+ 返回值：
  + 成功  --  图像占用的空间大小
  + 失败  --  -1
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_size() | bm_image_size()`

### image_color()

+ 原型：`void image_color(Image *dst, const Image *src);`
+ 功能：图像颜色格式转换
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_color() | bm_image_color()`
  + 不同平台的函数实现，又依赖于不同命名空间下的颜色转换函数，例如`Nvidia::NvColor() | BitMainland::BmColor()`

### image_copy()

+ 原型：`void image_copy(Image *dst, const Image *src);`
+ 功能：复制图像
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_copy() | bm_image_copy()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvImage::copy_from() | BitMainland::BmImage::copy_from()`

### image_copy_from_general()

+ 原型：`void image_copy_from_general(Image *dst, const Image *src, int src_in_host);`
+ 功能：复制图像
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `src_in_host`  --  !0源图像在主机内存， 0源图像在设备内存
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_copy_from_general() | bm_image_copy_from_general()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvImage::copy_from() | BitMainland::BmImage::copy_from()`

### image_copy_to_general()

+ 原型：`void image_copy_to_general(Image *dst, int dst_in_host, const Image *src);`
+ 功能：复制
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `dst_in_host`  --  !0目标图像在主机内存， 0目标图像在设备内存
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_copy_to_general() | bm_image_copy_to_general()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvImage::copy_to() | BitMainland::BmImage::copy_to()`

### image_resize()

+ 原型：`void image_resize(Image *dst, const Image *src, int roi_x, int roi_y, int roi_w, int roi_h, int flag);`
+ 功能：图像缩放
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `roi_x`  --  感兴趣区域 x 坐标
  + `roi_y`  --  感兴趣区域 y 坐标
  + `roi_w`  --  感兴趣区域宽度
  + `roi_h`  --  感兴趣区域高度
  + `flag`   --  插值补偿方法
    + flag == 1, Linear interpolation
    + flag == 2, Cubic interpolation
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_resize() | bm_image_resize()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvResize() | BitMainland::BmResize()`

### image_warp_perspective()

+ 原型：`void image_warp_perspective(Image *dst, const Image *src, int roi_x, int roi_y, int roi_w, int roi_h, double quad[4][2], int flag);`
+ 功能：矩型向四边型透视投影
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `roi_x`  --  感兴趣区域 x 坐标
  + `roi_y`  --  感兴趣区域 y 坐标
  + `roi_w`  --  感兴趣区域宽度
  + `roi_h`  --  感兴趣区域高度
  + `quad`   --  
    + `[0][]` 左上，`[1][]` 右上，`[2][]` 右下，`[3][]`左下
+ 返回值：空
+ 注意：
  + 源图像和目标图像的尺寸要相等
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_warp_perspective() | bm_image_warp_perspective()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvWarpPerspective() | BitMainland::BmWarpPerspective()`

### image_warp_perspective_back()

+ 原型：`void image_warp_perspective_back(Image *dst, const Image *src, int roi_x, int roi_y, int roi_w, int roi_h, double quad[4][2], int flag);`
+ 功能：四边型向矩型透视投影
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `roi_x`  --  感兴趣区域 x 坐标
  + `roi_y`  --  感兴趣区域 y 坐标
  + `roi_w`  --  感兴趣区域宽度
  + `roi_h`  --  感兴趣区域高度
  + `quad`   --  
    + `[0][]` 左上，`[1][]` 右上，`[2][]` 右下(BM左下)，`[3][]`左下(BM右下)
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_warp_perspective_back() | bm_image_warp_perspective_back()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvWarpPerspectiveBack() | BitMainland::BmWarpPerspectiveBack()`

### image_warp_affine_back()

+ 原型：`void image_warp_affine_back(Image *dst, const Image *src, int roi_x, int roi_y, int roi_w, int roi_h, double quad[4][2], int flag);`
+ 功能：四边型向矩型仿射投影
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `roi_x`  --  感兴趣区域 x 坐标
  + `roi_y`  --  感兴趣区域 y 坐标
  + `roi_w`  --  感兴趣区域宽度
  + `roi_h`  --  感兴趣区域高度
  + `quad`   --  
    + `[0][]` 左上，`[1][]` 右上，`[2][]` 右下(BM左下)，`[3][]`左下(BM右下)
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_warp_affine_back() | bm_image_warp_affine_back()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvWarpAffineBack() | BitMainland::BmWarpAffineBack()`

### image_darw_rectangle()

+ 原型：`void image_darw_rectangle(Image *img, int corner[], int corner_group, uint8_t color[3], int color_weight);`
+ 功能：画矩形框
+ 参数：
  + `img`  --  需要画的图像
  + `corner`  --  存放矩型框坐标点的数组
  + `corner_group`  --  矩形框的个数，或者说有几组矩形框坐标
  + `color`   --  画线的颜色
  + `color_weight`  --  
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_darw_rectangle() | bm_image_darw_rectangle()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvDarwRectangle() | BitMainland::BmDarwRectangle()`

### image_defog()

+ 原型：`void image_defog(Image *dst, const Image *src, float dack_m, uint8_t dack_a, float dack_w);`
+ 功能：除雾
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `dack_m`  --  默认为 0.35
  + `dack_a`  --  默认为 220
  + `dack_w`  --  默认为 0.9
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_defog() | bm_image_defog()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvDefog() | BitMainland::BmDefog()`

### image_light()

+ 原型：`void image_light(Image *dst, const Image *src, float alpha[3], float bate[3]);`
+ 功能：灯光
+ 参数：
  + `dst`  --  目标图像指针
  + `src`  --  源图像指针
  + `alpha` -- 
  + `bate`  --
    + `e[c]*alpha[c]+bate[c]`
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_image_light() | bm_image_light()`
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::Nvlight() | BitMainland::Bmlight()`

----------------------------------------------------------------------------------------------------

## `contrib/infer.h`

+ 概述：
  + 推理实现部分

### model2local()

+ 原型：`int model2local(dict_handle_t dictionary);`
+ 功能：模型转换
+ 参数：
  + `dictionary`  --  字典
    - `Verbose`:    是否打印详情。非 `0` 时打印，为 `0` 时不打印。默认：`0`。
    - `ModelType`： 模型类型。仅支持`ONNX`，`Caffe`。
    - `ModelFile`： 模型文件。
    - `DeployFile`：模型配置文件。`Caffe`模型有效。
    - `OutputTensorName-%d`：模型输出层名字。`Caffe`模型有效。
    - `EnableExplicitPrecision`：是否启用固定数量的批处理。`!0` 启用，`0` 禁用。默认：`!0` 。
    - `InputDIMs`：输入层维度定义(`NCHW`)。默认：`0,1,2,3`
    - `DataType`： 数据类型。32(`FP32`),16(`FP16`),8(`INT8`)。默认：32。
    - `BatchSize`：批处理大小。默认：1。
    - `DLA`：默认：-1。
    - `SaveFile`：保存转换后的模型文件。如果仅指定路径，则转换后的文件名自动生成。
    - `OverWriteSaveFileIfExist`：如果 `SaveFile` 指定的文件已经存在是否覆盖。`!0` 覆盖，`0` 不覆盖。默认：`0`。
    - `InputIsCHW` 输入数据格式(整型)。`!0` 输入数据为CHW格式，`0` 输入数据为HWC格式。默认：`!0`。
    - `InputSCALAR` 像素通道系数(浮点)。默认值：`1.0/255`, `1.0/255`, `1.0/255`
    - `InputMEAN` 像素通道均值(浮点)。默认值：`0, 0, 0`
    - `InputSTD` 像素通道方差(浮点)。默认值：`1.0, 1.0, 1.0`
    - `CalibratorDataset`：量化数据集(文件清单，以`'\n'`为换行符)，注1：数据仅支持`JPG`或`JPEG`格式，注2：`INT8`有效。
+ 返回值：
  + 成功  --  0
  + 失败  --  -1
+ 注意：
  + 其内部实现，只有`NVIDIA`平台 -- `nv_model2local()`
  + `nv_model2local()`内部实现，又依赖于`Nvidia`命名空间下的`NvInferConvert`类的方法`convert()`

### engine_clean()

+ 原型：`void engine_clean();`
+ 功能：引擎清理
+ 参数：无
+ 返回值：无
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_engine_clean() | bm_engine_clean()`

### engine_unload()

+ 原型：`void engine_unload(const char *name);`
+ 功能：引擎卸载
+ 参数：
  + `name`  --  需要卸载的引擎的名字
+ 返回值：无
+ 注意：
  + 正在使用的引擎会延时卸载，但不可再被引用。
  + 已经卸载的引擎被重新创建(相同的名字)也视为两个不同的引擎
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_engine_unload() | bm_engine_unload()`

### engine_load()

+ 原型：`int engine_load(const char *name, const void *model[], const long length[], const char *args);`
+ 功能：引擎加载
+ 参数：
  + `name`  --  名字
  + `model` --  模型，存放数据类型为`const void *`的元素的数组，换言之，可以加载多个模型
  + `length`--  数据长度。为0或者负数时，从文件加载
  + `args`  --  参数，可以为NULL(0)
+ 返回值：
  + 成功  --  0
  + 失败  --  !0
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_engine_load() | bm_engine_load()`
  + **重要部分**

### engine_load2()

+ 原型：`int engine_load2(const char *name, const char *model, const char *args);`
+ 功能：引擎加载（从文件加载）
+ 参数：
  + `name`  --  名字
  + `model` --  模型，存放数据类型为`const void *`的元素的数组，换言之，可以加载多个模型
  + `args`  --  参数，可以为NULL(0)
+ 返回值：
  + 成功  --  0
  + 失败  --  !0
+ 注意：
  + 其内部实现，定义`length`，并将其设置为`-1`，之后调用`engine_load()`

### engine_unload_cb

+ 声明：`typedef void (*engine_unload_cb)(const char *name);`
+ 功能：**卸载通知函数**

### engine_at_unload()

+ 原型：`int engine_at_unload(const char *name, engine_unload_cb unload_cb);`
+ 功能：注册卸载通知函数
+ 参数：
  + `name`  --  名字
  + `unload_cb`  --  卸载通知函数
+ 返回值：
  + 成功  --  0
  + 失败  --  !0
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_engine_at_unload() | bm_engine_at_unload()`

### infer_free()

+ 原型：`void infer_free(InferContext **ctx);`
+ 功能：销毁，销毁完成后，减少引擎的引用计数器
+ 参数：
  + `ctx`  --  **推理环境**
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_infer_free() | bm_infer_free()`
  + 不同平台的函数实现，依赖于`dictionary.h`文件下的`dict_free()`函数
  + 不同平台的函数实现，又依赖于不同命名空间下的图像类的方法，例如`Nvidia::NvInferContext::destory() | BitMainland::BmInferContext::destory()`

### infer_alloc()

+ 原型：`InferContext *infer_alloc(const char *engine_name);`
+ 功能：创建
+ 参数：
  + `engine_name`  --  引擎名字
+ 返回值：
  + 成功  --  推理环境指针
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_infer_alloc() | bm_infer_alloc()`
  + 不同平台的函数实现，又依赖于不同命名空间下的推理类的方法，例如`Nvidia::NvInferContext::create() | BitMainland::BmInferContext::create()`

### infer_tensor_info()

+ 原型：`int infer_tensor_info(const InferContext *ctx, InferTensorInfo info[1000], int fetch_input_info);`
+ 功能：查询输入输出结构信息
+ 参数：
  + `ctx`  --  推理环境
  + `info` --  推理张量信息
  + `fetch_input_info`  --  `!0` 查询输入结构，`0` 查询输出结构
+ 返回值：
  + 成功  --  数量
  + 失败  --  小于零
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_infer_tensor_info() | bm_infer_tensor_info()`

### infer_input_image_info()

+ 原型：`int infer_input_image_info(const InferContext *ctx, InferInputImageInfo info[1000]);`
+ 功能：查询输入图像信息
+ 参数：
  + `ctx`  --  推理环境
  + `info` --  推理张量信息
+ 返回值：
  + 成功  --  数量
  + 失败  --  小于零
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_infer_input_image_info() | bm_infer_input_image_info()`

----------------------------------------------------------------------------------------------------

## `contrib/nms.h`

+ 概述：
  + 检测框处理

### nms_compute()

+ 原型：`void nms_compute(int *keep_out, int *num_out, float *boxes_host, int boxes_num, float nms_overlap_thresh);`
+ 功能：处理检测框（非极大值抑制）
+ 参数：
  + `keep_out`  --  保留框的索引
  + `num_out`   --  保留框的数量
  + `boxes_host`--  输入框的坐标和类别。x1, y1, x2, y2, class
  + `boxes_num` --  输入框的数量
  + `nms_overlap_thresh`  --  交并比阈值
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_nms_compute() | bm_nms_compute()`
  + 不同平台的函数内部实现，又依赖于不同命名空间下的函数，例如`Nvidia::NMS_Compute() | `

----------------------------------------------------------------------------------------------------

## `contrib/BoxMat.hpp`

+ 概述：
  + 检测框信息的处理

### `BoxMat`类

+ 命名空间：`aicontrib`
+ 功能：处理（筛选）检测框
+ 类属性：
  + 公共属性：
    + `m_x1`  --  x坐标
    + `m_y1`  --  y坐标
    + `m_x2`  --
    + `m_y2`  --
    + `m_score`  --  检测框分数
    + `m_label`  --  检测框标签
    + `m_son`    --  子节点，或关键点
+ 类方法：
  + 公共类方法
    + BoxMat()
      + BoxMat()  --  构造函数
      + BoxMat(const BoxMat &src)  --  构造函数
    + virtual ~BoxMat()   -- 虚析构函数
    + operator=()
      + 原型：`BoxMat &operator=(const BoxMat &src);`
      + 功能：重载赋值运算符(=)，是BoxMat类类型的变量可以赋值
      + 参数：
        + `src`  --  源BoxMat类类型 变量
      + 返回值：
        + 返回`*this`
      + 注意：
        + 运算符重载，类赋值
    + x()
      + 原型：`double x();`
      + 功能：获取x坐标，
      + 参数：无
      + 返回值：
        + 返回公共属性 `m_x1`
    + y()
      + 原型：`double y();`
      + 功能：获取y坐标
      + 参数：无
      + 返回值：
        + 返回公共属性 `m_y1`
    + w()
      + 函数重载  --  获取/设置 检测框的宽度
      + 一
        + 原型：`double w();`
        + 功能：获取检测框宽度
        + 参数：无
        + 返回值：
          + 返回 `m_x2 - m_x1`
      + 二
        + 原型：`void w(double width);`
        + 功能：接收`width`，设置`m_x2`
        + 参数：
          + `width`  --  接收的宽度
        + 返回值：无
    + h()
      + 函数重载  --  获取/设置 检测框的高度
      + 一
        + 原型：`double h();`
        + 功能：获取检测框的高度
        + 参数：无
        + 返回值：
          + 返回`m_y2 - m_y1`
      + 二
        + 原型：`void h(double height);`
        + 功能：获取`height`,设置`m_y2`
        + 参数： 
          + `height`  --  接收的高度
        + 返回值：无
    + overlap_area()
      + 函数重载  --  计算两个矩型相交的面积
      + 一
        + 原型：`inline double overlap_area(double _x, double _y, double _w, double _h);`
        + 功能：接收输入的四个坐标信息，计算矩型相交面积
        + 参数：
          + `_x`  --  
          + `_y`  --
          + `_w`  --
          + `_h`  --
        + 返回值：
          + 成功  --  返回计算的面积
          + 失败  --  0.0
      + 二
        + 原型：`inline double overlap_area(const BoxMat &other);`
        + 功能：接收输入的BoxMat对象，计算矩型相交面积
        + 参数：
          + `other`  --  BoxMat 对象
        + 返回值：
          + 成功  --  返回计算的面积
          + 失败  --  0.0
        + 注意：
          + 其内部实现，依赖于第一个重载函数，将other属性当做参数输入
    + overlap_ratio()
      + 函数重载  --  计算两个矩型相交的面积与两个矩型的面积之和比
      + 一
        + 原型：`inline double overlap_ratio(double _x, double _y, double _w, double _h);`
        + 功能：接收输入的四个坐标信息，计算两个矩型相交的面积与两个矩型的面积之和比
        + 参数：
          + `_x`  --  
          + `_y`  --
          + `_w`  --
          + `_h`  --
        + 返回值：
          + 成功  --  返回计算的比值
          + 失败  --  0.0
      + 二
        + 原型：`inline double overlap_ratio(const BoxMat &other);`
        + 功能：接收输入的BoxMat对象，计算两个矩型相交的面积与两个矩型的面积之和比
        + 参数：
          + `other`  --  BoxMat对象
        + 返回值：
          + 成功  --  返回计算的比值
          + 失败  --  0.0
        + 注意：
          + 其内部实现，依赖于第一个重载函数，将other属性当做参数输入

### box_iou_nms()

+ 函数重载  --  筛选检测框，对存储源检测框的向量 做排序，生成按分数降序的目标检测框向量
+ 一
  + 原型：`inline void box_iou_nms(std::vector<BoxMat> &dst, std::vector<BoxMat> &src, float threshold);`
  + 功能：接收存放数据类型为`BoxMat`类类型的向量`src` ，根据阈值`threshold`，处理检测框，生成按分数降序的目标向量`dst`
  + 参数：
    + `dst`  --  存放检测框的目标向量
    + `src`  --  需要处理的存放检测框的源向量
    + `threshold`  --  阈值
  + 返回值：空
  + 注意：
    + 其内部实现，依赖于标准命名空间下的`sort()`方法和`nms.h`文件下的`nms_compute()`方法
+ 二
  + 原型：`inline void box_iou_nms(std::vector<BoxMat> &dst, std::map<double, std::vector<BoxMat>> &src, float threshold);`
  + 功能：接收多个BoxMat，根据阈值`threshold`，处理检测框，生成按分数降序的目标向量`dst`
  + 参数：
    + `dst`  --  存放检测框的目标向量
    + `src`  --  映射，存放多个BoxMat
    + `threshold`  --  阈值
  + 返回值：空
  + 注意：
    + 其内部实现，依赖于第一个重载函数，使用for循环，依次处理映射`src`中的BoxMat

----------------------------------------------------------------------------------------------------

## `contrib/Model.hpp`

+ 概述
  + 模型通用后处理
  + 基类

### `Model`类

+ 命名空间：`aicontrib`
+ 功能：完成模型后处理
+ 类属性：
  + 公共属性
    + `m_input_image_infos`  --  存放数据类型为`InferInputImageInfo`，即推理输入的图像信息的向量
    + `m_input_tensorts`     --  存放数据类型为`InferTensorInfo`，即推理张量信息的向量  --  输入的
    + `m_output_tensorts`    --  存放数据类型为`InferTensorInfo`，即推理张量信息的向量  --  输出的
    + `m_enable_sigmod`      --  布尔类型，是否打开归一化功能  --  真，打开 | 假，关闭
+ 类方法：
  + 公共方法：
    + `Model()`  --  构造函数
    + `virtual ~Model()`  --  虚析构函数
    + sigmoid()
      + 虚函数  --  归一化
      + 一
        + 原型：`virtual double sigmoid(double x);`
        + 功能：归一化功能
        + 参数：
          + `x`  --  需要处理的数据
        + 返回值：
          + 成功  --  处理后的数据
        + 注意：
          + 其内部实现，通过类属性`m_enable_sigmoid`判断是否归一化，依赖于`crt`文件下的`math_functions.hpp`文件中的函数`exp()`
    + clamp()
      + 虚函数  --  返回最小值
      + 一
        + 原型：`virtual float clamp(const float val, const float minVal, const float maxVal);`
        + 功能：返回最小值
        + 参数：
          + `val`  --
          + `minVal`  --
          + `maxVal`  --
        + 返回值：
          + 成功  --  minVal和val中最大的值 和 maxVal中最小的值
    + normalize_l2()
      + 虚函数  --  标准化
      + 一
        + 原型：`virtual void normalize_l2(float *data, int data_len);`
        + 功能：标准化
        + 参数：
          + `data`  --  需要处理的数据指针
          + `data_len`  --  数据长度
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`math.h`下的`sqrt()`函数 --  求平方根
    + in_net_n()
      + 虚函数  --  获取输入的推理张量 `0` 维的`layer`信息
      + 一
        + 原型：`virtual int in_net_n(int layer, int d = 0);`
        + 功能：获取输入的推理张量的`0` 维的`layer`
        + 参数：
          + `layer`  --  层数？？
          + `d`  
        + 返回值：
          + 成功  --  输入的推理张量的`0`维 的`layer`
    + in_net_c()
      + 虚函数  --  获取输入的推理张量 `1` 维的`layer`信息
      + 一
        + 原型：`virtual int in_net_c(int layer, int d = 1);`
        + 功能：获取输入的推理张量的`1` 维的`layer`
        + 参数：
          + `layer`  --  层数？？
          + `d`  
        + 返回值：
          + 成功  --  输入的推理张量的`1` 维的`layer`
    + in_net_h()
      + 虚函数  --  获取输入的推理张量 `2` 维的`layer`信息
      + 一
        + 原型：`virtual int in_net_h(int layer, int d = 2);`
        + 功能：获取输入的推理张量的`2` 维的`layer`
        + 参数：
          + `layer`  --  层数？？
          + `d`  
        + 返回值：
          + 成功  --  输入的推理张量的`2` 维的`layer`
    + in_net_w()
      + 虚函数  --  获取输入的推理张量 `3` 维的`layer`信息
      + 一
        + 原型：`virtual int in_net_w(int layer, int d = 3);`
        + 功能：获取输入的推理张量的`3` 维的`layer`
        + 参数：
          + `layer`  --  层数？？
          + `d`  
        + 返回值：
          + 成功  --  输入的推理张量的`3` 维的`layer`
    + img_Xfactor()
      + 虚函数  -- 获取X方向系数
      + 一
        + 原型：`virtual double img_Xfactor(int idx);`
        + 功能：获取索引为`idx`的X方向系数
        + 参数：
          + `idx`  --  索引
        + 返回值：
          + 成功  --  获取索引为`idx`的X方向系数
    + img_Yfactor()
      + 虚函数  -- 获取Y方向系数
      + 一
        + 原型：`virtual double img_Yfactor(int idx);`
        + 功能：获取索引为`idx`的Y方向系数
        + 参数：
          + `idx`  --  索引
        + 返回值：
          + 成功  --  获取索引为`idx`的Y方向系数
    + img_Xshift()
      + 虚函数  --  X方向移动
      + 一
        + 原型：`virtual double img_Xshift(int idx);`
        + 功能：X方向移动
        + 参数：
          + `idx`  --  索引
        + 返回值：
          + 成功  --  X方向移动
    + img_Yshift()
      + 虚函数  --  Y方向移动
      + 一
        + 原型：`virtual double img_Yshift(int idx);`
        + 功能：Y方向移动
        + 参数：
          + `idx`  --  索引
        + 返回值：
          + 成功  --  Y方向移动
    + img_w()
      + 虚函数  --  获取源图像的宽度
      + 一
        + 原型：`virtual int img_w(int idx);`
        + 功能：获取索引为`idx`的源图像的宽度
        + 参数：
          + `idx`  --  索引
        + 返回值：
          + 成功  --  索引为`idx`的源图像的宽度
    + img_h()
      + 虚函数  --  获取源图像的高度
      + 一
        + 原型：`virtual int img_h(int idx);`
        + 功能：获取索引为`idx`的源图像的高度
        + 参数：
          + `idx`  --  索引
        + 返回值：
          + 成功  --  索引为`idx`的源图像的高度
    + out_index()
      + 虚函数  --  获取输出图像的索引
      + 一
        + 原型：`virtual int out_index(int layer);`
        + 功能：获取源图像层数为`layer`的输出图像索引
        + 参数：
          + `layer`  -- 源图像层数
        + 返回值：
          + 成功  --  源图像层数为`layer`的输出图像索引
    + out_layer()
      + 虚函数  --  获取输出图像的层数
      + 一
        + 原型：`virtual int out_layer(const char *name);`
        + 功能：获取名为`name`的输出图像的层数
        + 参数：
          + `name`  --  需要查询的输出图像的名字
        + 返回值：
          + 成功  --  名为`name`的输出图像的层数
    + out_name()
      + 虚函数  --  获取输出图像的名字
      + 一
        + 原型：`virtual const char* out_name(int layer);`
        + 功能：获取层数为`layer`的输出图像的名字
        + 参数：
          + `layer`  --  输出图像的层数
        + 返回值：
          + 成功  --  层数为`layer`的输出图像的名字
    + out_n()
      + 虚函数  --  获取输出张量 第`0`维的`layer`
      + 一
        + 原型：`virtual int out_n(int layer, int d = 0);`
        + 功能：获取输出张量 `0` 维的图像`layer`
        + 参数：
          + `layer`  -- 
          + `d`
        + 返回值：
          + 输出张量 `0` 维的图像`layer`
    + out_c()
      + 虚函数  --  获取输出张量 第`1`维的`layer`
      + 一
        + 原型：`virtual int out_c(int layer, int d = 0);`
        + 功能：获取输出张量 `1` 维的图像`layer`
        + 参数：
          + `layer`  -- 
          + `d`
        + 返回值：
          + 输出张量 `1` 维的图像`layer`
    + out_h()
      + 虚函数  --  获取输出张量 第`2`维的`layer`
      + 一
        + 原型：`virtual int out_h(int layer, int d = 0);`
        + 功能：获取输出张量 `2` 维的图像`layer`
        + 参数：
          + `layer`  -- 
          + `d`
        + 返回值：
          + 输出张量 `2` 维的图像`layer`
    + out_w()
      + 虚函数  --  获取输出张量 第`3`维的`layer`
      + 一
        + 原型：`virtual int out_w(int layer, int d = 0);`
        + 功能：获取输出张量 `3` 维的图像`layer`
        + 参数：
          + `layer`  -- 
          + `d`
        + 返回值：
          + 输出张量 `3` 维的图像`layer`
    + out_data()
      + 虚函数  --  获取输出张量的数据
      + 一
        + 原型：`virtual const void* out_data(int layer);`
        + 功能：获取层数为`layer`的图像的数据
        + 参数：
          + `layer`  --  
        + 返回值：
          + 层数为`layer`的图像的数据
    + postreatment()
      + 虚函数  --  后处理
      + 一
        + 原型：`virtual void postreatment(std::vector<std::vector<aicontrib::BoxMat>> &objects, const std::vector<float> &min_prob, const std::vector<float> &nms_prob);`
        + 功能：接收多个检测框，多个阈值，筛选检测框
        + 参数：
          + `objects`  --  需要处理的检测框
          + `min_prob` --  阈值向量
          + `nms_prob` --  非极大值抑制的阈值向量
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于第二个重载函数 和 `aicontrib::box_iou_nms()`函数
      + 二
        + 原型：`virtual void postreatment(std::vector<std::map<double, std::vector<aicontrib::BoxMat>>> &objects, float min_prob);`
        + 功能：接收单个阈值 和 数据类型为存放数据类型为`map`的向量`objects`，筛选检测框
        + 参数：
          + `objects`  --  需要处理的检测框
          + `min_prob` --  阈值
        + 返回值：空
        + 注意：
          + **其内部实现，依赖于子类完成的虚函数**

----------------------------------------------------------------------------------------------------

## `contrib/Feature.h`

+ 概述：
  + 特征提取
  + 内部依赖于文件`ndarray.hpp`  --  多维数组

### `Feature`类

+ 命名空间：`aicontrib`
+ 功能：特征提取
+ 类属性：
  + 公共属性：
    + `m_normalize_l2_enable`  --  是否打开标签值标准化
    + `m_output_name`  --  输出名字
+ 类方法：
  + 公共方法：
    + `Feature()`  --  构造函数
    + `virtual ~Feature()`  --  虚析构函数
    + postreatment()
      + 虚函数 继承 --  后处理
      + 一
        + 原型：`inline void postreatment(std::vector<std::vector<float>> &objects);`
        + 功能：接收特征值（向量），进行筛选  --  特征模型的后处理
        + 参数：
          + `objects`  --  需要处理的特征值，也就是存放类型为`float`的二维向量
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于文件`ndarray.hpp`下的`out_data()`方法

----------------------------------------------------------------------------------------------------

## `contrib/matcher.h`

+ 概述：
  + 特征比对
  + `typedef void *_matcher_handle;`  -->  `void *` <==> `_matcher_handle`
  + 其内部将`matcher_handle`转为指向`matcher_t`结构体类型的指针,其包含`abcdk_mutex_t, faiss::Index`等

### matcher_destroy()

+ 原型：`void matcher_destroy(matcher_handle_t *handle);`
+ 功能：销毁
+ 参数：
  + `handle`  --  对外环境句柄
+ 返回值：空
+ 注意：
  + 还需要调用`abcdk_mutex_destroy()`

### matcher_info()

+ 原型：`void matcher_info(matcher_handle_t handle, int *dims, int *metric, int64_t *count);`
+ 功能：获取基础信息
+ 参数：
  + `handle`  --  对外环境句柄
  + `dims`    --  返回维度
  + `metric`  --  返回度量类型
  + `count`   --  返回特征数量
+ 返回值：空
+ 注意：
  + 返回的维度从内部的`matcher_t`中的成员`faiss::Index`的成员`d`
  + 返回的度量类型是从内部的`matcher_t`中的成员`faiss::Index`的成员`metric_type`
  + 返回的特征数量是从内部的`matcher_t`中的成员`faiss::Index`的成员`ntotal`

### matcher_save()

+ 原型：`int matcher_save(matcher_handle_t handle, const char *file);`
+ 功能：将基础信息保存到文件
+ 参数：
  + `handle`  --  对外环境句柄
  + `file`    --  需要保存数据的文件
+ 返回值：
  + 成功  --  0
  + 失败  --  !0
+ 注意：
  + 其内部实现，依赖于命名空间`faiss`下的`write_index()`函数

### matcher_load()

+ 原型：`matcher_handle_t matcher_load(const char *file);`
+ 功能：从文件加载数据
+ 参数：
  + `file`  --  需要加载的文件
+ 返回值：
  + 成功  --  对外环境句柄
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于命名空间`faiss`下的`read_index()`函数
  + 内部实现的日志打印，依赖于命名空间`faiss`下的`FaissException`类

### matcher_create()

+ 原型：`matcher_handle_t matcher_create(int dims, int metric);`
+ 功能：创建特征
+ 参数：
  + `dims`  --  维度
  + `metric`--  度量类型
+ 返回值：
  + 成功  --  返回对外环境句柄
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于命名空间`faiss`下的`index_factory()`函数
  + 内部实现的日志打印，依赖于命名空间`faiss`下的`FaissException`类

### matcher_cpu2gpu()

+ 原型：`matcher_handle_t matcher_cpu2gpu(matcher_handle_t handle, int device);`
+ 功能：从CPU环境复制到GPU环境
+ 参数：
  + `device`  --  GPU设备号
+ 返回值：
  + 成功  --  返回对外环境句柄
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于命名空间`faiss::gpu`下的`StandardGpuResources()`类和`index_cpu_to_gpu()`函数

### matcher_gpu2cpu()

+ 原型：`matcher_handle_t matcher_gpu2cpu(matcher_handle_t handle);`
+ 功能：从GPU环境复制到CPU环境
+ 参数：
  + `handle`  --  对外环境指针
+ 返回值：
  + 成功  --  对外环境指针
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于命名空间`faiss::gpu`下的`index_gpu_to_cpu()`函数

### matcher_search()

+ 原型：`void matcher_search(matcher_handle_t handle, int64_t count, const float *data, int64_t top, int64_t *ids, float *dts);`
+ 功能：检测  --  特征比对
+ 参数：
  + `handle`  --  对外环境指针
  + `count`   --  N个特征，`data[N*dims]`
  + `data`    --  数据？？
  + `top`     --  M个匹配，`ids[N*M]`，`dts[N*M]`
  + `ids`     --  输出标签
  + `dts`     --  输出成对距离
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于内部环境句柄`matcher_t`下的成员`faiss::Index`下的`search()`函数和`assign()`函数
  + `search()`
    + 原型：`virtual void faiss::Index::search(faiss::Index::idx_t n, const float *x, faiss::Index::idx_t k, float *distances, faiss::Index::idx_t *labels) const`
    + 功能：查询 `n` 个维度为 `d` 的向量到索引。 最多返回 `k` 个向量。 如果一个查询没有足够的结果，结果数组用 `-1` 填充。
    + 参数：
      + `n`  --  要搜索的输入向量个数
      + `x`  --  要搜索的输入向量，大小为`n * d`
      + `k`  -- 
      + `distances` -- 输出成对距离，大小为`n * k`
      + `labels`    --  NN的输出标签，大小为`n * k`
    + 返回值：空
  + `assign()`  
    + 原型：`virtual void faiss::Index::assign(faiss::Index::idx_t n, const float *x, faiss::Index::idx_t *labels, faiss::Index::idx_t k = 1L) const`
    + 功能：返回最接近查询 x 的 k 个向量的索引。 此功能与搜索相同，但仅返回邻居的标签
    + 参数：
      + `n`  --  要搜索的输入向量个数
      + `x`  --  要搜索的输入向量，大小为`n * d`
      + `labels`  --  NN的输出标签，大小为`n * k`
    + 返回值：空

### matcher_add()

+ 原型：`void matcher_add(matcher_handle_t handle, int64_t count, const float *data, const int64_t *ids);`
+ 功能：添加特征
+ 参数：
  + `handle`  --  对外环境句柄
  + `count`   --  N个特征，`data[N*dims]`
  + `data`    --  要添加的向量数据
  + `ids`     --  N个ID， NULL(0)忽略
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于内部环境句柄`matcher_t`下的成员`faiss::Index`下的`add_with_ids()`和`add()`
  + add()
    + 原型：`virtual void faiss::Index::add(faiss::Index::idx_t n, const float *x);`
    + 功能：将 n 个维度为 d 的向量添加到索引中。 向量被隐式分配标签 ntotal .. ntotal + n - 1 此函数将输入向量切成小于 blocksize_add 的块并调用 add_core。
    + 参数：
      + `n`  --  要添加的向量个数
      + `x`  --  输入矩阵
    + 返回值：空
  + add_with_ids()
    + 原型：`virtual void faiss::Index::add_with_ids(faiss::Index::idx_t n, const float *x, const faiss::Index::idx_t *xids);`
    + 功能：与 add 相同，但存储 xid 而不是顺序 id。 默认实现因断言而失败，因为并非所有索引都支持它
    + 参数：
      + `n`  --  要添加的向量个数
      + `x`  --  输入矩阵
      + `xids`  --  如果非空，为向量存储的 ids（大小 n）

### matcher_del_range()

+ 原型：`size_t matcher_del_range(matcher_handle_t handle, int64_t begin, int64_t count);`
+ 功能：删除指定范围的特征
+ 参数：
  + `handle`  --  对外环境指针
  + `begin`   --  开始
  + `count`   --  要删除的特征个数
+ 返回值：
  + 成功  --  返回删除的元素数
  + 失败  --  0
+ 注意：
  + 其内部实现，依赖于内部环境句柄`matcher_t`下的成员`faiss::Index`下的`remove_ids()`
  + remove_ids()
    + 原型：`virtual size_t faiss::Index::remove_ids(const faiss::IDSelector &sel);`
    + 功能：从索引中删除 ID。 并非所有都支持索引。 返回删除的元素数
    + 参数：
      + `sel`  --  结构体，选择索引范围
    + 返回值：
      + 成功  --  返回删除的元素数
      + 失败  --  0

### matcher_del_batch()

+ 原型：`size_t matcher_del_batch(matcher_handle_t handle, int64_t count, const int64_t *ids);`
+ 功能：删除批量的特征
+ 参数：
  + `handle`  --  对外环境指针
  + `ids`     --  
+ 返回值：
  + 成功  --  返回删除的元素数
  + 失败  --  0
+ 注意：
  + 其内部实现，依赖于内部环境句柄`matcher_t`下的成员`faiss::Index`下的`remove_ids()`