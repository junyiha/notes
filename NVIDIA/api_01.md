## 英伟达API

### nvjpegDecode()

+ 功能：
  + 解码单幅图像。API是后端不可知的。它将决定在内部使用哪个实现。目标缓冲区应该足够大，能够存储指定格式的输出。
  + 对于每个颜色平面，可以使用`nvjpegGetImageInfo()`检索图像大小，每个平面所需的最小内存缓冲区是`nPlaneHeight*nPlanePitch`，
  + 其中`nPlanePitch >= nPlaneWidth`用于平面输出格式，`nPlanePitch >= nPlaneWidth*nOutputComponents`用于交错输出格式。
  + `IN/OUT`句柄:库句柄。
    + `INT/OUT jpeg_handle`:解码的jpeg图像状态句柄。
    + `IN data`:指向包含要解码的jpeg图像的缓冲区的指针。
    + `IN length`: jpeg图像缓冲区的长度。
    + `IN output_format`:输出数据格式。
    + 参见`nvjpegOutputFormat_t`了解`IN/OUT`目的地:指向带有输出缓冲区信息结构的指针。
    + 参见`nvjpegImage_t description`。
    + `IN/OUT`流:提交所有`GPU`工作的`CUDA`流

+ 原型：`nvjpegStatus_t nvjpegDecode(nvjpegHandle_t handle, nvjpegJpegState_t jpeg_handle, const unsigned char *data, size_t length, nvjpegOutputFormat_t output_format, nvjpegImage_t *destination, cudaStream_t stream)`

+ 返回值：
  + `NVJPEG_STATUS_SUCCESS`  --  成功

### cudaStreamSynchronize()

+ 功能：阻塞任务流，直到流完成所有操作。如果 device 设置了`cudaDeviceScheduleBlockingSync`标识，主机线程在它完成所有的任务之前，会一直阻塞
+ 原型：`cudaError_t cudaStreamSynchronize(cudaStream_t stream);`
+ 参数：
  + `stream`  --  流标识符
+ 返回值：
  + 成功  --  返回`cudaSuccess`
  + 失败  --  返回`cudaErrorInvalidResourceHandle`

### cudaStreamCreateWithFlags()

+ 功能：创建一个新的异步的流,通过参数`flags`来设置流的属性  
  + `Create an asynchronous stream Creates a new asynchronous stream.`
  + `The flags argument determines the behaviors of the stream.`
+ 原型：`cudaError_t cudaStreamCreateWithFlags(cudaStream_t *pStream, unsigned int flags);`
+ 参数：
  + `pStream`  --  指向流标识符的指针
  + `flags`    --  创建流的参数,有效的参数为：
    + `cudaStreamDefault`  --  默认标识
    + `cudaStreamNonBlocking`  --   异步流，异步于NULL流
+ 返回值：
  + 成功  --  cudaSuccess
  + 失败  --  cudaErrorInvalidValue

### cudaGetDeviceCount()

+ 功能：获取可用算能设备的数量
+ 原型：`cudaError_t cudaGetDeviceCount(int *count);`
+ 参数：
  + `count`  --  具有计算能力的设备数字
+ 返回值：
  + 成功  --  cudaSuccess

### cudaGetDevice()

+ 功能：返回当前正在使用的设备
+ 原型：`cudaError_t cudaGetDevice(int *device);`
+ 参数：
  + `device`  --  正在工作的主机线程所执行的设备代码
+ 返回值：
  + 成功  --  cudaSuccess
  + 失败  --  cudaErrorInvalidValue

### cudaSetDevice()

+ 功能：设置GPU运行的设备
+ 原型：`cudaError_t cudaSetDevice(int device);`
+ 参数：
  + `device`  --  调用这个函数的主机线程要执行设备代码的设备
+ 返回值：
  + 成功  --  cudaSuccess
  + 失败  --  cudaErrorInvalidDevice  | cudaErrorDeviceAlreadyInUse
+ 注意：
  + 随后任何设备由`cudaMalloc(), cudaMallocPitch(), cudaMallocArray()`申请的设备内存都会分配到对应device的物理设备
  + 任何主机线程通过`cudaMallocHost(), cudaHostAlloc(), cudaHostRegister()`申请的主机内存都会将它们的生命周期与设备device关联起来
  + 任何通过主机线程创建的流或事件都会和设备device关联起来
  + 任何通过主机线程由`cudaLaunchKernel()`发生的内核调用都会在设备device上执行
  + 这个调用可能在任何时间，由任何主机线程在任何设备上调用。
+ 返回值：
  + 成功  --  cudaSuccess
  + 失敗  --  cudaErrorInvalidDevice | cudaErrorDeviceAlreadyInUse