## `advance/spp_easy.h`

+ 概述：
  + 包含具有特征提取，特征比对的结构，换言之，输入一张或多张图片，返回一组id和一组分数
  + 它是在`spp.h`的基础上抽象了一层

### spp_easy_add()

+ 功能：添加，添加`Image`结构体指针的方式和与其绑定的id
+ 原型：`void spp_easy_add(spp_handle_t handle, int32_t lable, int8_t index, const Image *img);`
+ 参数：
  + `handle`  --  环境句柄
  + `lable`   --  标签，大于0时有效
  + `index`   --  底图索引，大于0时有效
  + `img`     --  绑定的图像结构体指针
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于`spp_add()`

### spp_easy_add2()

+ 功能：添加，添加图像路径的方式和与其绑定的id
+ 原型：`int spp_easy_add2(spp_handle_t handle, int32_t lable, int8_t index, const char *img);`
+ 参数：
  + `handle`  --  环境句柄
  + `lable`   --  标签，大于0时有效
  + `index`   --  底图索引，大于0时有效
  + `img`     --  绑定的图像路径
+ 返回值：
  + 成功  --  0
  + 是爱  --  !0
+ 注意：
  + 其内部实现，通过函数`image_load()` 加载指定路径的图片，之后调用`spp_easy_add()`

### spp_easy_del()

+ 功能：删除
+ 原型：`int spp_easy_del(spp_handle_t handle, int32_t lable, int8_t index);`
+ 参数：
  + `handle`  --  环境句柄
  + `lable`   --  需要删除的图像标签
  + `index`   --  需要删除的图像索引
+ 返回值：
  + 成功  --  0
  + 失败  --  !0， 标签或索引不存在
+ 注意：
  + 其内部实现，依赖于`spp_del()`
  + `id = ((id << 8) | index);` ??

### spp_easy_search()

+ 功能：检索，接收的图像格式为`Image`结构体指针
+ 原型：`void spp_easy_search(spp_handle_t handle, const Image *img, int top, int32_t *lables);`
+ 参数：
  + `handle`  --  环境句柄
  + `img`     --  需要检索的图片结构体指针 
  + `top`     --  最佳匹配数量，换言之，需要返回前top数量的图像
  + `lables`  --  匹配的标签数组， -1 --  无效  --  output
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于`spp_search()`
  + 内部，实现了 提取标签，去掉索引和对标签的去重

### spp_easy_search2()

+ 功能：检索，接收的图像格式为图像的路径
+ 原型：`int spp_easy_search2(spp_handle_t handle, const char *img, int top, int32_t *lables);`
+ 参数：
  + `handle`  --  环境指针
  + `img`     --  图像路径
  + `top`     --  最佳匹配数量，换言之，需要返回前top数量的图像
  + `lables`  --  匹配的标签数组， -1 --  无效  --  output
+ 返回值：
  + 成功  --  0
  + 失败  --  !0
+ 注意：
  + 其内部实现，通过`image_load()`函数将`img`指向的图像加载到内存，转化为`Image`结构体指针
  + 之后，调用`spp_easy_search()`函数

---------------------------------------------------------------------------------------------------------------

## `advance/spp.h`

+ 概述：


### spp_destroy()

+ 功能：销毁（环境）
+ 原型：`void spp_destroy(spp_handle_t *handle);`
+ 参数：
  + `handle`  --  环境句柄
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于`Touch.hpp`文件中的`Destroy()`和`matcher.h`文件下的`matcher_destroy()`函数

### spp_save()

+ 功能：保存到文件
+ 原型：`int spp_save(spp_handle_t handle, const char *file);`
+ 参数：
  + `handle`  --  环境句柄
  + `file`    --  需要保存数据的文件
+ 返回值：
  + 成功  --  0
  + 失败  --  !0
+ 注意：
  + 其内部实现，依赖于`matcher_save()`

### spp_create()

+ 功能：创建，如果加载快照文件，则快照保存的数据结构和特征引擎输出的结构必须一置
+ 原型：`spp_handle_t spp_create(const char *engine, const char *snapshot);`
+ 参数：
  + `engine`  --  特征引擎名字，换言之，`DETECT.conf`文件
  + `snapshot`  --  快照文件，NULL 忽略
+ 返回值：
  + 成功  --  返回环境句柄
  + 失败  --  NULL
+ 注意：
  + ` --feature-metric < TYPE >` 度量类型，见`matcher_metric_t`
  + 其内部实现，引擎加载依赖于`Touch.hpp`的`Create(), GetFeature()`
  + 快照文件加载依赖于`matcher_load(), matcher_info, matcher_create()`

### spp_search()

+ 功能：检索，通过输入`Image`结构体指针的方式
+ 原型：`void spp_search(spp_handle_t handle, const Image *img, int top, int64_t *ids, float *dts);`
+ 参数：
  + `handle`  --  环境句柄
  + `img`     --  图像结构体指针
  + `top`     --  最佳匹配数量，换言之，需要返回top个id
  + `ids`     --  返回的一组id
  + `dts`     --  返回的一组分数，与id一一对应
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于`Touch.hpp`文件下的`GetFeature()`函数 和 `matcher.h`文件下的`matcher_search()`

### spp_search2()

+ 功能：检索，通过输入图像路径的方式
+ 原型：`int spp_search2(spp_handle_t handle, const char *img, int top, int64_t *ids, float *dts);`
+ 参数：
  + `handle`  --  环境句柄
  + `img`     --  图像文件路径
  + `top`     --  返回的最佳匹配数量，换言之，需要返回top个id
  + `ids`     --  返回的一组id
  + `dts`     --  返回的一组分数，与id一一对应
+ 返回值：
  + 成功  --  0 
  + 失败  --  !0
+ 注意：
  + 其内部实现，依赖于`image_load()`将`img`指定的图像文件加载到内存，转换为`Image`结构体指针，之后调用`spp_search()`   

### spp_add()

+ 功能：添加，通过输入`Image`结构体指针的方式
+ 原型：`void spp_add(spp_handle_t handle, const Image *img, int64_t id);`
+ 参数：
  + `handle`  --  环境句柄
  + `img`     --  图像结构体指针
  + `id`      --  需要与图像绑定的id
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于`Touch.hpp`文件下的`GetFeature()`函数，提取输入图像的特征值，之后通过`matcher.h`文件下的`matcher_add()`将图像特征值和id绑定在一起

### spp_add2()

+ 功能：添加，通过输入图像路径的方式
+ 原型：`int spp_add2(spp_handle_t handle, const char *img, int64_t id);`
+ 参数：
  + `handle`  --  环境句柄
  + `img`     --  输入图像的路径
  + `id`      --  需要与图像绑定的id
+ 返回值：
  + 成功  --  0 
  + 失败  --  !0
+ 注意：
  + 其内部实现，依赖于`image_load()`将`img`指向的图像文件加载到内存，转化为`Image`结构体指针，之后调用`spp_add()`函数

### spp_del()

+ 功能：删除
+ 原型：`size_t spp_del(spp_handle_t handle, int64_t id);`
+ 参数：
  + `handle`  --  环境句柄
  + `id`      --  需要删除的图像id， 相同id的图像都将被删除
+ 返回值：
  + 成功  --  被删除的图像的数量
  + 失败  --  
+ 注意：
  + 其内部实现，依赖于`matcher.h`文件中的`matcher_del_batch()`函数