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