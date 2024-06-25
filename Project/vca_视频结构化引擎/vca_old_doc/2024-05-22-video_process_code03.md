---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: video_process_code03
tag: ProjectOfVideoContentAnalysis
---

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
  + 实现特征引擎加载，图像特征提取，特征比对的功能

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

---------------------------------------------------------------------------------------------------------------

## `contrib/device.h`

+ 概述：
  + 查询设备信息

### device_query()

+ 功能：查询设备信息
+ 原型：`int device_query(Device *devs, int max);`
+ 参数：
  + `devs`  --  设备信息结构体指针
  + `max`   --  最大的设备数
+ 返回值：
  + 成功  --  返回查询到的设备数量
  + 失败  --
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_device_query() | bm_device_query()`
  + 不同平台的函数实现，又依赖于不同硬件平台提供的设备接口，例如`cudaGetDeviceCount(), cudaGetDeviceProperties()`

---------------------------------------------------------------------------------------------------------------

## `contrib/mutex.hpp`

+ 概述：
  + 互斥体
  + 资源访问管理工具，实现加锁，解锁，唤醒等功能

### `mutex`类

+ 命名空间：`aicontrib`
+ 功能：互斥体
+ 类属性：
  + 私有属性：
    + `m_cond`  --  条件锁  -- 变量
    + `m_mutex` --  互斥锁  -- 变量
    + `m_attr`  --  条件变量属性  -- 用于条件变量处理的数据结构
+ 类方法：
  + 公有方法：
    + `inline mutex();`  --  构造函数  --  其内部调用`init();`方法
    + `inline virtual ~mutex();`  --  虚析构函数  --  其内部调用`uninit();`方法
    + init()
      + 虚函数  --  初始化对象
      + 一
        + 功能：初始化对象
        + 原型：`inline virtual void init();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`pthread.h`文件下的函数
          + `pthread_condattr_init(), pthread_condattr_setclock(), pthread_cond_init(), pthread_mutex_init()`
    + uninit()
      + 虚函数  --  反初始化，释放所有对象
      + 一
        + 功能：反初始化，释放所有对象
        + 原型：`inline virtual void uninit();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`pthread.h`文件下的函数
          + `pthread_cond_destroy(), pthread_mutex_destory(), pthread_condattr_destroy()`
    + lock()
      + 虚函数  --  加锁
      + 一
        + 功能：加锁
        + 原型：`inline virtual void lock();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`pthread.h`文件下的函数
          + `pthread_mutex_lock()`
    + unlock()
      + 虚函数  --  解锁
      + 一
        + 功能：解锁
        + 原型：`inline virtual void unlock();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`pthread.h`文件下的函数
          + `pthread_mutex_unlock()`
    + wait()
      + 虚函数  --  等待事件发生
      + 一
        + 功能：等待事件发生
        + 原型：`inline virtual int wait(long timeout);`
        + 参数：
          + `timeout`  --  等待超时，为`-1`时，表示直到事件发生才返回
        + 返回值：
          + 成功  --  
        + 注意：
          + 其内部实现，依赖于`pthread_cond_wait(), clock_gettime(), pthread_cond_timedwait()`
    + wakeup()
      + 虚函数  --  唤醒
      + 一
        + 功能：唤醒
        + 原型：`inline virtual int wakeup(int broadcast);`
        + 参数：
          + `broadcast`  --  如果不是0，通知所有等待的
        + 返回值：
          + 成功  --  
          + 失败  -- 
        + 注意：
          + 其内部实现，依赖于`pthread_cond_broadcast(), pthread_cond_signal()`

### `autolocker`类

+ 命名空间：`aicontrib`
+ 功能：自动加锁？？？
+ 类属性：
  + 私有属性：
    + `m_mutex_p`  --  `mutex`类 数据类型变量
+ 类方法：
  + 公有方法：
    + `autolocker()` 
      + 功能：构造函数
      + 原型：`autolocker(mutex *mutex_p);`
      + 参数：
        + `mutex_p`  --  `mutex`类 数据类型变量
      + 返回值：无
      + 注意：
        + 其内部实现，将`mutex_p`赋值给类属性`m_mutex_p`，调用`mutex`类的`lock()`方法
    + `virtual ~autolocker()`
      + 功能：虚析构函数
      + 注意：
        + 其内部调用`mutex`类的`unlock()`方法

---------------------------------------------------------------------------------------------------------------

## `contrib/cache.hpp`

+ 概述：
  + 缓冲区管理

### `cache`模板类

+ 命名空间：`aicontrib`
+ 功能：缓冲区操作
+ 类属性：
  + 私有属性：
    + `m_locker`  --  同步锁  --  `mutex`类 类型变量
    + `m_cells`   --  缓存格子 --  存储数据类型为`T`的向量
    + `m_qwork`   --  工作队列 --  存储数据类型为`int`的队列
    + `m_qidle`   --  空闲队列 --  存储数据类型为`int`的队列
    + `m_enable_overflow`  --  溢出开关  --  布尔类型
    + `m_enable_invalid`   --  无效开关  --  布尔类型
+ 类方法：
  + 公有方法：
    + `cache()`  --  构造函数 
    + `virtual ~cache()`  --  虚析构函数
    + operator[]()
      + 功能：`[]`运算符重载
      + 原型：`T& operator[](int idx);`
      + 参数：
        + `idx`  --  
      + 返回值：
        + 成功  --  
      + 注意：
        + ？？？？
    + resize()
      + 虚函数  --  重置缓存
      + 一
        + 功能：重置缓存
        + 原型：`virtual void resize(int cells);`
        + 参数：
          + `cells`  --  缓存格子的数量，大于0时，表示重置的大小 | 小于0时，表示清空
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于向量的`resize(), clear(), empty(), size(), push()`方法
    + resume()
      + 虚函数  --  使有效（默认）
      + 一
        + 功能：使有效（默认）
        + 原型：`virtual void resume();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，将类属性`m_enable_invalid`设置为`false`，并调用`mutex`类的`m_locker.wakeup()`方法
    + cancel()
      + 虚函数  --  使无效
      + 一
        + 功能：使无效
        + 原型：`virtual void cancel();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，将类属性`m_enable_invalid`设置为`true`，并调用`mutex`类的`m_locker.wakeup()`方法
    + enable_overflow()
      + 虚函数  --  溢出使能（默认关闭）
      + 一
        + 功能：溢出使能（默认关闭）
        + 原型：`virtual void enable_overflow(bool enable);`
        + 参数：
          + `enable`  --  为真时， 打开溢出使能 | 为假时，关闭溢出使能
        + 返回值：空
        + 注意：
          + 其内部实现，将参数`enable`的值赋给类属性`m_enable_overflow`
    + unref()
      + 虚函数  --  
      + 一
        + 功能：将需要工作（忙）的线程放到工作队列，不需要工作（不忙）的线程放到空闲队列
        + 原型：`virtual void unref(int idx, bool to_busy);`
        + 参数：
          + `idx`  --  需要操作的线程id
          + `to_busy`  --  线程的状态
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于向量的`push()`方法
    + refer()
      + 虚函数  --  ？？
      + 一
        + 功能： ？？？ （暂时没看懂）
        + 原型：`virtual void refer(int& idx, bool from_busy, bool is_peek /*= false*/);`
        + 参数：
          + `idx`  --  需要操作的线程？？
          + `from_busy`  --  是否在忙？？
          + `is_peek`    --  是否在读数据？？
        + 返回值：空
        + 注意：
          + （没看懂）

---------------------------------------------------------------------------------------------------------------

## `contrib/file.hpp`

+ 概述：
  + 文件操作
  + 其类的方法的内部实现，都依赖于`general.h`文件下的函数

### `File`类

+ 命名空间：`aicontrib`
+ 功能：文件处理
+ 类属性：
  + 公有属性：
    + `m_file`  --  文件描述符
+ 类方法：
  + 公有方法：
    + File()
      + 一
        + 功能：构造函数  --  将`m_file`置为`-1`
        + 原型：`inline File();`
      + 二
        + 功能：打开指定路径的文件
        + 原型：`inline File(const char *file, bool read_only /*=true */, bool non_block /*=false */, bool try_create /*=false */);`
        + 参数：
          + `file`  --  文件路径
          + `read_only`  -- 以只读模式打开？
          + `non_block`  --  ??
          + `try_create` --  是否尝试创建文件
        + 返回值：无
        + 注意：
          + 其内部实现，依赖于`File`类的方法`Open()`
          + 而`Open()`方法的内部实现，又依赖于`general.h`文件下的`file_open()`函数
    + `virtual ~File();`  --  虚析构函数  --  其内部实现，依赖于类方法`Close()`
    + IsOpen()
      + 虚函数  --  判断文件是否打开
      + 一
        + 功能：判断文件是否打开
        + 原型：`virtual bool IsOpen();`
        + 参数：无
        + 返回值：
          + 打开   --  True
          + 未打开 --   False
        + 注意：
          + 其内部实现，通过判断类属性`m_file`
    + Close()
      + 虚函数  --  关闭文件
      + 一
        + 功能：关闭文件
        + 原型：`inline virtual void Close();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`general.h`文件下的`file_close()`函数
    + Open()
      + 虚函数  --  打开文件
      + 一
        + 功能：打开文件
        + 原型：`inline virtual void Open(const char *file, bool read_only /*=true */, bool non_block /*=false */, bool try_create /*=false */);`
        + 参数：
          + `file`  --  文件路径
          + `read_only`  -- 以只读模式打开？
          + `non_block`  --  ??
          + `try_create` --  是否尝试创建文件
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`Close()`方法和`general.h`文件下的`file_open()`函数
    + Write()
      + 虚函数  --  向文件写数据
      + 一
        + 功能：向文件写数据
        + 原型：`inline virtual ssize_t Write(const void *data, size_t size);`
        + 参数：
          + `data`  --  需要写入的数据
          + `size`  --  需要写入数据的大小
        + 返回值：
          + 成功  --  写入的数据大小
          + 失败  --  -1
        + 注意：
          + 其内部实现，依赖于`general.h`文件下的`file_write()`函数
    + Read()
      + 虚函数  --  读文件
      + 一
        + 功能：读取文件数据
        + 原型：`inline virtual ssize_t Read(void *data, size_t size);`
        + 参数：
          + `data`  --  存放读出来的数据
          + `size`  --  读取的数据大小
        + 返回值：
          + 成功  --  读取的数据大小
          + 失败  --  -1
        + 注意：
          + 其内部实现，依赖于`general.h`文件下的`file_read()`函数

---------------------------------------------------------------------------------------------------------------

## `contrib/flag.h`

+ 概述：
  + 设置，获取标记

### flag_set()

+ 功能：设置标记
+ 原型：`int64_t flag_set(uint8_t key, int64_t value);`
+ 参数：
  + `key`   --  键
  + `value` --  键值
+ 返回值：
  + 成功  --  
  + 失败  --  
+ 注意：
  + 其内部实现，依赖于abcdk工具下,`atomic.h`文件下的宏`abcdk_atomic_store()`
  + 而宏`abcdk_atomic_store()`又依赖于`__sync_val_compare_and_swap()`

### flag_get()

+ 功能：获取标记
+ 原型：`int64_t flag_get(uint8_t key);`
+ 参数：
  + `key`  --  需要查询的标记的键
+ 返回值：
  + 成功  --  返回需要查询的键，对应的值
  + 失败  -- 
+ 注意：
  + 其内部实现，依赖于abcdk工具下,`atomic.h`文件下的宏`abcdk_atomic_load+()`
  + 而宏`abcdk_atomic_load()`又依赖于`__sync_and_and_fetch`

---------------------------------------------------------------------------------------------------------------

## `contrib/stopwatch.hpp`

+ 概述：
  + 秒表，用来计时
  + 睡眠指定时间，记录睡眠的起始时间

### `stopwatch`类

+ 命名空间：`aicontrib`
+ 功能：计时
+ 类属性：
  + 私有属性：
    + `m_start`  --  
    + `m_point`  --  
+ 类方法：
  + 公有方法：
    + `stopwatch();`  --  构造函数  --  内部实现，依赖于`reset()`
    + `virtual ~stopwatch();`  --  虚析构函数 
    + reset()
      + 虚函数  --  重置时间
      + 一
        + 功能：重置时间
        + 原型：`inline virtual void reset();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于`general.h`文件下的`clock2tick()`，将其返回值赋给类属性`m_start, m_point`
    + dot()
      + 虚函数  --  
      + 一
        + 功能：打点计时
        + 原型：`inline virtual uint64_t dot(uint64_t *step /*=NULL */)`
        + 参数：
          + `step`  --  步长
        + 返回值：
          + 成功  --  返回已经走的时间
        + 注意：
          + 其内部实现，依赖于`general.h`文件下的`clock2tick()`函数
    + step()
      + 虚函数  --  
      + 一
        + 功能：？？？
        + 原型：`inline virtual uint64_t step();`
        + 参数：无
        + 返回值：
          + 成功  --  
        + 注意：
          + 其内部实现，依赖于`dot()`方法
    + FPSleep()
      + 虚函数  --  暂定指定时间（纳秒）
      + 一
        + 功能：暂定指定时间（纳秒）
        + 原型：`inline virtual uint64_t FPSleep(double fps, bool only_count /*=false */);`
        + 参数：
          + `fps`  --  需要暂停的时间
          + `only_count`  --  为真，只是计数，并不真正的暂停 | 为假，真正的暂停指定时间
        + 返回值：
          + 成功  --  暂停的时间（纳秒）
        + 注意：
          + 其内部实现，依赖于`step()`方法和`time.h`文件下的`nanosleep()`函数

---------------------------------------------------------------------------------------------------------------

## `contrib/video.h` 

+ 概述：
  + 视频流处理

### video_free()

+ 功能：删除视频流对象
+ 原型：`void video_free(VideoContext **ctx);`
+ 参数：
  + `ctx`  --  视频流对象（视频流环境句柄）
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_video_free() | bm_video_free()`
  + 不同平台的函数实现，其内部又依赖于不同类的方法，例如`Nvidia::NvVideoWriter::destory() | BitMainland::BmVideoWriter::destory()`

### video_alloc()

+ 功能：创建视频流对象
+ 原型：`VideoContext *video_alloc();`
+ 参数：无
+ 返回值：
  + 成功  --  返回视频流对象（环境句柄）
  + 失败  --  NULL
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_video_alloc() | bm_video_alloc()`
  + 不同平台的函数实现，其内部又依赖于`calloc()`

### video_close()

+ 功能：关闭视频流
+ 原型：`void video_close(VideoContext *ctx);`
+ 参数：
  + `ctx`  --  视频流对象
+ 返回值：空
+ 注意：
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_video_close() | bm_video_close()`
  + 不同平台的函数实现，其内部又依赖于不同类的方法，例如`Nvidia::NvVideoWriter::close() | BitMainland::BmVideoWriter::close()`

### video_open()

+ 功能：打开视频流
+ 原型：`int video_open(VideoContext *ctx);`
+ 参数：
  + `ctx`  --  视频流对象
+ 返回值：
  + 成功  --  0
  + 失败  --  -1
+ 注意：
  + 关闭后不支持重复打开
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_video_open() | bm_video_open()`
  + 不同平台的函数实现，其内部又依赖于不同类的方法，例如`Nvidia::NvVideoWriter::open() | BitMainland::BmVideoWriter::open()`

### video_read()

+ 功能：读取一帧图像
+ 原型：`int video_read(VideoContext *ctx, Image *img, int *video_idx, int *stream_idx, int64_t *frame_num, int64_t *frame_idx, int64_t *frame_mms);`
+ 参数：
  + `ctx`  --  视频流对象
  + `img`  --  保存从视频流读出来的图像
  + `video_idx`  --  视频索引？？
  + `stream_idx` --  视频流索引？？
  + `frame_num`  --  
  + `frame_idx`  --  
  + `frame_mms`  --  
+ 返回值：
  + 成功  --  大于等于0
  + 失败  --  -1
+ 注意：
  + 在`video_open()`之后调用
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_video_read() | bm_video_read()`
  + 不同平台的函数实现，其内部又依赖于不同类的方法，例如`Nvidia::NvVideoWriter::read() | BitMainland::BmVideoWriter::read()`

### video_write()

+ 功能：输出一帧图像
+ 原型：`int video_write(VideoContext *ctx, const Image *img, int stream_idx);`
+ 参数：
  + `ctx`  --  视频流对象
  + `img`  --  需要输出的图像，为NULL(0)时，表示输出结束。
  + `stream_idx`  --  流编号
+ 返回值：
  + 成功  --  大于等于0
  + 失败  --  -1
+ 注意：
  + 在video_open()之后调用。
  + 其内部实现，依赖于不同平台的函数实现，例如`nv_video_write() | bm_video_write()`
  + 不同平台的函数实现，其内部又依赖于不同类的方法，例如`Nvidia::NvVideoWriter::write() | BitMainland::BmVideoWriter::write()`

---------------------------------------------------------------------------------------------------------------

## `contrib/KAFKA.hpp`

+ 概述：
  + kafka， 消息通讯
  + 发数据  --  producer
  + 收数据  --  consumer

### `KAFKA`类

+ 命名空间：`aicontrib`
+ 功能：消息通讯
+ 类属性：
  + 公有属性：
    + `TYPE`
      + `enum TYPE{ CONSUMER = 1, PRODUCER = 2};`
  + 受保护属性：
    + `m_type`  --  类型
    + `m_errbuf`  --  保存错误信息的字符数组
    + `m_conf`  --  kafka配置信息结构体  --  `rd_kafka_conf_t`
    + `m_kafka` --  kafka结构体  --  `rd_kafka_t`
    + `m_topic` --  kafka主题结构体
    + `m_parition`  --  分区
+ 类方法：
  + 公有方法：
    + `KAFKA(TYPE type = PRODUCER);`  --  构造函数  --  初始化类属性
    + `virtual ~KAFKA();`  --  虚析构函数  --  调用`Stop()`方法
    + Stop()
      + 功能：
        + 如果是消费者，停止消费主题 `m_topic` 和 `m_partition` 分区的消息，清除当前在本地队列中的所有消息
        + 如果是生产者，等待所有消息发送完毕
        + 之后，销毁主题`m_topic`,销毁kafka句柄`m_kafka`
      + 原型：`inline void Stop();`
      + 参数：无
      + 返回值：空
      + 注意：
        + 其内部实现，依赖于`rdkafka.h`文件下的`rd_kafka_consume_stop(), rd_kafka_poll(), rd_kafka_outq_len(), rd_kafka_topic_destroy(), rd_kafka_destroy()`
    + Start()
      + 功能：
        + 如果是消费者，接收主题，生成句柄，开始收数据（消费）
        + 如果是生产者，？？？
        + 配置环境信息，创建主题配置文件和主题资源句柄
      + 原型：`inline bool Start(const char *brokerlist, const char *topic, int partition /*=0 */, const char *groupid /*=NULL */);`
      + 参数：
        + `brokerlist`  --  代理名单？？
        + `topic`       --  主题
        + `partition`   --  分区
        + `groupid`     --  组id
      + 返回值：
        + 成功  --  返回true
        + 失败  --  调用`Stop()`并返回false
      + 注意：
        + 其内部实现，依赖于`rdkafka.h`文件下的`rd_kafka_conf_set(), rd_kafka_new(), rd_kafka_brokers_add(), rd_kafka_topic_conf_new(), rd_kafka_topic_new(), rd_kafka_consume_start()`
    + Send()
      + 功能：发送消息
      + 原型：`inline bool Send(const void *data, long size, long timeout /*= -1*/);`
      + 参数：
        + `data`  --  需要发送的数据
        + `size`  --  发送的数据大小
        + `timeout`  --  超时时间？
      + 返回值：
        + 成功  --  返回true
        + 失败  --  返回false
      + 注意：
        + 其内部实现，依赖于`rdkafka.h`文件下的
        + `rd_kafka_produce();`  --  生成一条消息并将其发送给代理
        + `rd_kafka_poll();`  --  轮询提供的 kafka 句柄以获取事件，返回服务的事件数量
        + `rd_kafka_errno2err();`  --  错误信息输出
    + Recv()
      + 功能：接收消息
      + 原型：`inline bool Recv(void **data, long *size, long timeout /*= -1*/);`
      + 参数：
        + `data`  --  接收从主题解析出来的数据
        + `size`  --  接收的数据大小
        + `timeout`  --  等待接收消息的最长时间
      + 返回值：
        + 成功  --  true
        + 失败  --  false
      + 注意：
        + 其内部实现，依赖于`rdkafka.h`文件下的
        + `rd_kafka_consume();`  --  
          + 使用来自主题 `rkt` 的单个消息，分区 `timeout_ms` 是等待接收消息的最长时间。 
          + 返回值：
            + 成功  --  返回消息对象
            + 失败  --  返回NULL
        + `rd_kafka_message_destroy();`  --  释放 `rkmessage`(消息对象) 的资源并将所有权交还给 `rdkafka`
        + 通过`mem_dup();`函数将消息对象中的数据转储到`data`中

---------------------------------------------------------------------------------------------------------------

## `contrib/ZMQ.hpp`

+ 概述：
  + `ZeroMQ`（简称`ZMQ`）是一个基于消息队列的多线程网络库，其对套接字类型、连接处理、帧、甚至路由的底层细节进行抽象，提供跨越多种传输协议的套接字
  + `ZMQ`是网络通信中新的一层，介于应用层和传输层之间（按照`TCP/IP`划分），其是一个可伸缩层，可并行运行，分散在分布式系统间
  + `ZMQ`不是单独的服务，而是一个嵌入式库，它封装了网络通信、消息队列、线程调度等功能，向上层提供简洁的`API`，应用程序通过加载库文件，调用`API`函数来实现高性能网络通信

### `ZMQ`类

+ 命名空间：`aicontrib`
+ 功能：实现网络通信
+ 类属性：
  + 公有属性：
    + `enum TYPE{REQ = 1 /*客户端使用*/, REP = 2 /*服务端*/};`
  + 受保护属性：
    + `m_ctx`  --  环境句柄（上下文）
    + `m_user` --  使用者
+ 类方法：
  + 公有方法：
    + `ZMQ(TYPE type);`  --  构造函数  --  初始化环境，其内部实现，依赖于`zmq.h`文件下的`zmq_ctx_new(), zmq_socket()`函数
      + `zmq_ctx_new();`  --  创建`m_ctx`环境句柄（上下文）
      + `zmq_socket();`  --  创建zmq的socket套接字
    + `inline virtual ~ZMQ();`  --  虚析构函数  -- 其内部实现，依赖于`zmq.h`文件下的函数
      + `zmq_setsocketopt()`  --  设置ZMQ的socket属性
      + `zmq_close();`  --  关闭zmq
      + `zmq_ctx_shutdown();`  --  销毁`m_ctx`环境句柄（上下文）
      + `zmq_ctx_term();`  --  终止一个`m_ctx`环境句柄（上下文）
    + connect()
      + 虚函数  --  向指定的地址发起连接
      + 一
        + 功能：向指定的地址发起连接
        + 原型：`inline virtual bool connect(const char *addr);`
        + 参数：
          + `addr`  --  需要连接的地址
        + 返回值：
          + 成功  --  true
          + 失败  --  false
        + 注意：
          + 其内部实现，依赖于`zmq.h`文件下的`zmq_connect();` 
    + listen()
      + 虚函数  --  绑定，监听和接收
      + 一
        + 功能：对指定地址的套接字进行绑定，监听和接收
        + 原型：`inline virtual bool listen(const char *addr);`
        + 参数：
          + `addr`  --  需要监听的地址
        + 返回值：
          + 成功  --  true
          + 失败  --  false
        + 注意：
          + 其内部实现，依赖于`zmq.h`文件下的`zmq_bind()`函数
    + send()
      + 虚函数  --  发送
      + 一
        + 功能：发送指定大小的数据
        + 原型：`inline virtual bool send(const void *data, long size, long timeout /*=-1 */);`
        + 参数：
          + `data`  --  需要发送的数据
          + `size`  --  需要发送的数据大小
          + `timeout`  --  延迟时间
        + 返回值：
          + 成功  --  true
          + 失败  --  false
        + 注意：
          + 其内部实现，依赖于`zmq.h`文件下的
            + `zmq_poll()`
            + `zmq_msg_init_size()`
            + `zmq_msg_data()`  --  
            + `zmq_msg_send()`  --  发送消息
            + `zmq_msg_close()` --  关闭
    + recv()
      + 虚函数  --  接收
      + 一
        + 功能：接收指定大小的数据
        + 原型：`inline virtual bool recv(void **data, long *size, long timeout /*=-1 */);`
        + 参数：
          + `data`  --  存储接收到的消息数据
          + `size`  --  接收的消息大小
          + `timeout`  --  延时时间
        + 返回值：
          + 成功  --  true
          + 失败  --  false
        + 注意：
          + 其内部实现，依赖于`zmq.h`文件下的
            + `zmq_poll()`
            + `zmq_msg_init()`
            + `zmq_msg_recv()`  --  接收消息
            + `zmq_msg_data()`
            + `zmq_msg_size()`
            + `zmq_msg_close()`

---------------------------------------------------------------------------------------------------------------

## `contrib/redis.hpp`

+ 概述：
  + redis客户端

### `redis`类

+ 命名空间：`aicontrib`
+ 功能：redis客户端
+ 类属性：
  + 私有属性：
    + `m_connected_stable`  --  连接状态
    + `m_ctx`   --  上下文
    + `m_reply` --  回复对象，由`redisCommand()`返回
  + 公有属性：
    + enum REPLY_TPYE
      + `UNKNOWN`  --  -1
      + `STRING`   --  `REDIS_REPLY_STRING`
      + `ARRAY`    --  `REDIS_REPLY_ARRAY`
      + `INTEGER`  --  `REDIS_REPLY_INTEGER`
      + `NIL`      --  `REDIS_REPLY_NIL`
      + `STATUS`   --  `REDIS_REPLY_STATUS`
      + `ERROR`    --  `REDIS_REPLY_ERROR`
+ 类方法：
  + 公有方法：
    + `redis();`  --  构造函数  --  初始化类私有属性
    + `virtual ~redis();`  --  虚析构函数，调用类方法`disconnect()`
    + connected()
      + 虚函数  --  查看是否连接
      + 一
        + 功能：查看是否连接
        + 原型：`inline virtual bool connected();`
        + 参数：无
        + 返回值：
          + 连接  --  true
          + 未连接 --  false
        + 注意：
          + 其内部实现，返回类属性`m_connected_stable`
    + connect()
      + 虚函数  --  连接
      + 一
        + 功能：连接指定端口的地址
        + 原型：`inline virtual bool connect(const char *addr, uint16_t port, long timeout);`  
        + 参数：
          + `addr`  --  需要连接的地址
          + `port`  --  需要连接的端口号
          + `timeout`  --  超时时间
        + 返回值：
          + 成功  --  true
          + 失败  --  false
        + 注意：
          + 其内部实现，依赖于`hiredis.h`文件下的`redisConnectWithTimeout()`函数
    + disconnect()
      + 虚函数  -- 断开连接
      + 一
        + 功能：断开连接
        + 原型：`inline virtual void disconnect();`
        + 参数：无
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于类方法`free_reply(), free_connected()`
    + execv()
      + 虚函数  --  向Redis发命令
      + 一
        + 功能：向Redis发出命令
        + 原型：`inline virtual bool execv(const char *fmt, va_list ap);`
        + 参数：
          + `fmt`  --  发送的消息格式？
          + `ap`   --  参数,存储信息
        + 返回值：
          + 成功  --  true
          + 失败  --  false
        + 注意：
          + 其内部实现，依赖于类方法`free_reply()`和`hiredis.h`文件下的`redisvCommand()`函数
    + exec()
      + 虚函数  --  向Redis发送命令
      + 一
        + 功能：接收参数，并分析参数，向Redis发送命令
        + 原型：`inline virtual bool exec(const char *fmt, ...);`
        + 参数：
          + `fmt`  --  参数格式
        + 返回值：
          + 成功  --  true
          + 失败  --  false
        + 注意：
          + 其内部实现，依赖于`va_start(), va_end()`解析接收的参数，之后调用`execv()`类方法
    + fetch_reply_data()
      + 虚函数  --  获取回复数据
      + 一
        + 功能：获取回复数据
        + 原型：`inline virtual void fetch_reply_data(std::vector<std::tuple<REPLY_TYPE, int64_t, std::string>> &data, redisReply *reply /*=NULL */);`
        + 参数：
          + `data`  --  获取的数据
          + `reply` --  redis回复结构体
        + 返回值：空
        + 注意：
          + 其内部实现，依赖于STL的操作
  + 私有方法
    + free_reply()
      + 功能：释放redis回复对象
      + 原型：`void free_reply();`
      + 参数：无
      + 返回值：空
      + 注意：
        + 其内部实现，依赖于`hiredis.h`文件下的`freeReplyObject();`
    + free_connected()
      + 功能：断开redis连接
      + 原型：`void free_connected();`
      + 参数：无
      + 返回值：空
      + 注意：
        + 其内部实现，依赖于`hiredis.h`文件下的`redisFree();`