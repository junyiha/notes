## 简介

+ cuda相关的理论基础

## cuda C 编程

+ CPU编程和GPU编程的主要区别是程序员对GPU架构的熟悉程度。用并行思维进行思考并对GPU架构有了基本的了解，会使你编写规模达到成百上千个核的并行程序，如同写穿行程序一样简单

+ CUDA中有内存层次和线程层次的概念，使用如下结构有助于你对线程进行更高层次的控制和调度
  + 内存层次结构
  + 线程层次结构

+ CUDA抽象了硬件细节，且不需要将应用程序映射到传统图形API上。CUDA核中有三个关键抽象
  + 线程组的层次结构
  + 内存的层次结构
  + 障碍同步

+ 目标应该是学习GPU架构的基础及掌握CUDA开发工具和环境

+ CUDA开发环境。NVIDIA为C和C++开发人员提供了综合的开发环境以创建GPU加速应用程序，包括以下几种
  + NVIDIA Nsight集成开发环境
  + CUDA—GDB命令行调试器
  + 用于性能分析的可视化和命令行分析器
  + CUDA—MEMCHECK内存分析其
  + GPU设备管理工具

## cuda编程结构

+ 一个典型的CUDA编程结构包括五个主要步骤
  + 分配GPU内存
  + 从CPU内存拷贝数据到GPU内存
  + 调用CUDA内核函数来完成程序指定的运算
  + 将数据从GPU拷回CPU内存
  + 释放GPU内存空间

+ CUDA编程模型使用由C语言扩展生成的主时代码在异构计算系统中执行应用程序。
+ 在一个异构环境中包含多个CPU和GPU，每个GPU和CPU的内存都由一条PCI-Express总线分隔开。因此需要注意区分以下内容
  + 主机: CPU及其内存(主机内存)
  + 设备: GPU及其内存(设备内存)

+ 从CUDA6.0开始，NVIDIA提出了名为"统一寻址(Unified Memory)"的编程模型的改进，它连接了主机内存和设备内存空间，可使用单个指针访问CPU和GPU内存，无序彼此之间手动拷贝数据。
+ 现在，主要的是应学会如何为主机和设备分配内存空间以及如何在CPU和GPU之间拷贝共享数据。这种程序员管理模式控制下的内存和数据可以优化应用程序并实现硬件系统利用率的最大化

+ 内核(kernel)是CUDA编程模型的一个重要组成部分，其代码在GPU上运行。作为一个开发人员，你可以串行执行核函数。在此背景下，CUDA的调度管理程序员在GPU线程上编写核函数。在主机上，基于应用程序数据以及GPU的性能定义如何让设备实现算法功能。这样做的目的是使你专注于算法的逻辑(通过编写串行代码)，且在创建和管理大量的GPU线程时不必拘泥于细节。

+ CUDA编程模型主要是异步的，因此在GPU上进行的运算可以与主机-设备通讯重叠。一个典型的CUDA程序包括由并行代码互补的串行代码。
  + 串行代码(及任务并行代码)在主机CPU上执行，而并行代码在GPU上执行。
  + 主机代码按照ANSI C 标准进行编写，而设备代码使用CUDA C进行编写
  + 你可以将所有的代码统一放在一个源文件中，也可以使用多个源文件来构建应用程序和库
  + NVIDIA的C编译器(nvcc)为主机和设备生成可执行代码

## cuda 内存管理

+ CUDA编程模型假设系统是由一个主机和一个设备组成的，而且各自拥有独立的内存。核函数是在设备上运行的。为使你拥有充分的控制权并使系统达到最佳性能，CUDA运行时负责分配和释放设备内存，并且在主机内存和设备内存之间传输数据

+ 用于执行GPU内存分配的是cudaMalloc函数，其函数原型为:
```c
cudaError_t cudaMalloc(void** devPtr, size_t size)
```
+ 该函数负责向设备分配一定字节的线性内存，并以devPtr的形式返回指向锁分配内存的指针。
+ cudaMalloc与标准C语言中的malloc函数几乎一样，只是次函数在GPU的内存里分配内存。

+ cudaMemcpy函数负责主机和设备之间的数据传输，其函数原型为:
```c
cudaError_t cudaMemcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind)
```
+ 次函数从src指向的源存储区复制一定数量的字节到dst指向的目标存储区。复制方向由kind指定，其中的kind有以下几种
  + cudaMemcpyHostToHost
  + cudaMemcpyHostToDevice
  + cudaMemcpyDeviceToHost
  + cudaMemcpyDeviceToDevice
+ 这个函数以同步方式执行，因为在cudaMemcpy函数返回以及传输操作完成之前主机应用程序是阻塞的

+ 除了内核启动之外的CUDA调用都会返回一个错误的枚举类型cudaError_t
  + 如果GPU内存分配成功，函数返回cudaSuccess
  + 否则返回cudaErrorMemoryAllocation
+ 可以使用CUDA运行时函数将错误代码转化为可读的错误消息
```c
char* cudaGetErrorString(cudaError_t error)
```

+ 在GPU内存层次结构中，最主要的两种内存是全局内存和共享内存。
  + 全局内存类似于CPU的系统内存
  + 共享内存类似于CPU的缓存
+ GPU的共享内存可以由CUDA C的内核直接控制

## cuda 线程管理

+ 当核函数在主机端启动时，它的执行会移动到设备上，此时设备中会产生大量的线程并且每个线程都执行由核函数指定的语句。

+ 由一个内核启动所产生的所有线程统称为一个网格。同一网格中的所有线程共享相同的全局内存空间。
+ 一个网格由多个线程块构成，一个线程块包含一组线程，同一线程快内的线程写作可以通过以下方式来实现
  + 同步
  + 共享内存
+ 不同块内的线程不能协作
+ 线程依靠以下两个坐标变量来区分彼此
  + blockIdx(线程块在线程格内的索引)
  + threadIdx(块内的线程索引)
+ 这些变量是核函数中需要预初始化的内置变量。当执行一个核函数时，CUDA运行时为每个线程分配坐标变量blockIdx和threadIdx。基于这些坐标，你可以将部分数据分配给不同的线程

## cuda cudnn tensorrt 之间存在什么关系

CUDA（Compute Unified Device Architecture）、cuDNN（CUDA Deep Neural Network）、和TensorRT（TensorRT）都是与GPU计算和深度学习相关的 NVIDIA 技术。

1. **CUDA（Compute Unified Device Architecture）**:
   - CUDA 是 NVIDIA 提供的并行计算平台和编程模型，允许开发者使用通用编程语言（如C/C++和Fortran）来编写支持GPU加速的程序。
   - CUDA 提供了 GPU 计算的基础设施，包括 GPU 内核函数、内存管理、线程调度等。

2. **cuDNN（CUDA Deep Neural Network）**:
   - cuDNN 是 NVIDIA 提供的深度学习库，专门用于 GPU 加速的深度神经网络训练和推理。
   - 它优化了深度学习算法的实现，提供了高性能的 GPU 实现，包括卷积、池化、归一化等操作，以加速深度学习模型的训练和推理过程。

3. **TensorRT（Tensor Runtime）**:
   - TensorRT 是 NVIDIA 提供的用于高性能深度学习推理的库。它通过对模型进行优化和精简，以减少推理时的延迟和提高推理性能。
   - TensorRT 可以与 cuDNN 结合使用，对深度学习模型进行加速，同时还支持 INT8 等低精度推理。

关系：
- CUDA 提供了底层的 GPU 计算基础架构，cuDNN 利用 CUDA 提供的加速功能实现深度学习操作的高性能实现。
- TensorRT 则建立在 CUDA 和 cuDNN 的基础上，专注于优化深度学习模型的推理过程，通过减少模型的计算负载和内存占用来提高推理性能。 TensorRT 还可以与 cuDNN 配合使用，以进一步优化深度学习模型的推理。
  
总体而言，CUDA 提供了底层的 GPU 编程能力，cuDNN 是在 CUDA 上构建的深度学习库，而 TensorRT 是专注于优化深度学习推理的高性能库。

## C++ cuda库是什么

在C++中，"CUDA库"通常指的是NVIDIA提供的CUDA（Compute Unified Device Architecture）工具包，它是用于并行计算的一组工具和API。CUDA库使得开发人员能够在NVIDIA GPU上进行通用目的的并行计算。

CUDA库包括以下主要组件：

1. **CUDA Runtime库：** 提供了一系列C语言风格的API，允许在CUDA设备（GPU）上执行并行计算。开发人员使用这些API来管理设备内存、启动GPU内核函数等。

2. **CUDA Driver库：** 提供了与硬件交互的低级别接口，允许对GPU进行更直接的控制。一般情况下，开发人员更常用CUDA Runtime库，而不是直接使用Driver库。

3. **cuBLAS：** 针对线性代数运算的CUDA库，提供了一组高性能的基本线性代数子程序（BLAS）。

4. **cuFFT：** 针对快速傅里叶变换（FFT）的CUDA库，用于高性能的FFT计算。

5. **cuDNN：** 深度神经网络库，提供了一组高性能的深度学习基本操作和算法，用于在GPU上进行深度学习推理和训练。

6. **NVRTC（NVIDIA Runtime Compiler）：** 允许在运行时将CUDA C源代码编译为GPU代码的库。

在使用CUDA库进行开发时，通常需要安装NVIDIA的GPU驱动、CUDA工具包以及适当版本的cuBLAS、cuFFT等库。开发人员可以使用CUDA C/C++编写GPU内核函数，并通过调用CUDA库中的API来执行并行计算任务。

以下是一个简单的示例，展示了在C++中使用CUDA Runtime库执行向量加法的基本步骤：

```cpp
#include <iostream>

// CUDA kernel函数，执行向量加法
__global__ void vectorAddition(float* a, float* b, float* result, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < size) {
        result[idx] = a[idx] + b[idx];
    }
}

int main() {
    const int size = 1024;
    const int blockSize = 256;

    // 分配主机内存
    float* hostA = new float[size];
    float* hostB = new float[size];
    float* hostResult = new float[size];

    // 初始化输入数据
    for (int i = 0; i < size; ++i) {
        hostA[i] = i;
        hostB[i] = 2 * i;
    }

    // 分配设备内存
    float* deviceA, *deviceB, *deviceResult;
    cudaMalloc(&deviceA, size * sizeof(float));
    cudaMalloc(&deviceB, size * sizeof(float));
    cudaMalloc(&deviceResult, size * sizeof(float));

    // 将输入数据从主机复制到设备
    cudaMemcpy(deviceA, hostA, size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, size * sizeof(float), cudaMemcpyHostToDevice);

    // 启动CUDA kernel
    vectorAddition<<<(size + blockSize - 1) / blockSize, blockSize>>>(deviceA, deviceB, deviceResult, size);

    // 将结果从设备复制到主机
    cudaMemcpy(hostResult, deviceResult, size * sizeof(float), cudaMemcpyDeviceToHost);

    // 打印结果
    for (int i = 0; i < 10; ++i) {
        std::cout << hostResult[i] << " ";
    }

    // 释放内存
    delete[] hostA;
    delete[] hostB;
    delete[] hostResult;
    cudaFree(deviceA);
    cudaFree(deviceB);
    cudaFree(deviceResult);

    return 0;
}
```

上述示例使用CUDA Runtime库执行向量加法，其中CUDA kernel函数在GPU上并行执行。请注意，CUDA开发涉及到更多的细节和概念，这里只是一个简单的入门示例。

## C++ cuda库 详解

CUDA（Compute Unified Device Architecture）是由NVIDIA提供的用于通用目的的并行计算框架。它允许开发人员使用C++或CUDA C等编程语言在NVIDIA GPU上执行并行计算任务。以下是关于CUDA库的一些详细信息：

### 主要组件：

1. **CUDA Runtime库：** 提供了一系列C语言风格的API，用于在CUDA设备上执行并行计算。这包括设备管理、内存分配和释放、CUDA核函数的启动等功能。开发人员通常使用这些API进行CUDA编程。

2. **CUDA Driver库：** 提供了更低级别的接口，允许直接与硬件进行交互。一般情况下，开发人员更多地使用CUDA Runtime库，而不是直接使用Driver库。

3. **cuBLAS（CUDA Basic Linear Algebra Subroutines）：** 面向线性代数操作的库，提供高性能的基本线性代数子程序（BLAS）。

4. **cuFFT（CUDA Fast Fourier Transform）：** 针对快速傅立叶变换（FFT）的库，用于高性能的FFT计算。

5. **cuRAND：** 提供随机数生成功能的库，包括伪随机数生成器、分布等。

6. **cuSPARSE：** 面向稀疏矩阵操作的库，提供高性能的稀疏矩阵运算。

7. **NVRTC（NVIDIA Runtime Compiler）：** 允许在运行时将CUDA C源代码编译为GPU代码的库。这对于动态生成GPU核函数是有用的。

### CUDA编程模型：

CUDA编程模型涉及在主机（CPU）和设备（GPU）之间进行数据传输，以及在GPU上并行执行核函数。以下是CUDA编程的一般步骤：

1. **分配设备内存：** 使用`cudaMalloc`等CUDA Runtime函数在GPU上分配内存。

2. **将数据从主机复制到设备：** 使用`cudaMemcpy`将数据从主机复制到GPU。

3. **定义并启动CUDA核函数：** 使用`__global__`修饰符定义CUDA核函数，并使用`<<<...>>>`语法启动并行执行。

4. **将数据从设备复制回主机：** 使用`cudaMemcpy`将计算结果从GPU复制回主机。

5. **释放设备内存：** 使用`cudaFree`等函数释放在GPU上分配的内存。

### 示例代码：

以下是一个简单的示例代码，展示了在CUDA中执行向量加法的基本步骤：

```cpp
#include <iostream>

__global__ void vectorAddition(float* a, float* b, float* result, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < size) {
        result[idx] = a[idx] + b[idx];
    }
}

int main() {
    const int size = 1024;
    const int blockSize = 256;

    float* hostA = new float[size];
    float* hostB = new float[size];
    float* hostResult = new float[size];

    // 初始化输入数据...

    float* deviceA, *deviceB, *deviceResult;
    cudaMalloc(&deviceA, size * sizeof(float));
    cudaMalloc(&deviceB, size * sizeof(float));
    cudaMalloc(&deviceResult, size * sizeof(float));

    cudaMemcpy(deviceA, hostA, size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, size * sizeof(float), cudaMemcpyHostToDevice);

    vectorAddition<<<(size + blockSize - 1) / blockSize, blockSize>>>(deviceA, deviceB, deviceResult, size);

    cudaMemcpy(hostResult, deviceResult, size * sizeof(float), cudaMemcpyDeviceToHost);

    // 处理结果...

    delete[] hostA;
    delete[] hostB;
    delete[] hostResult;
    cudaFree(deviceA);
    cudaFree(deviceB);
    cudaFree(deviceResult);

    return 0;
}
```

上述示例演示了在GPU上使用CUDA执行向量加法的步骤。这只是一个简单的入门示例，实际情况中可能涉及更复杂的计算任务和数据管理。确保参考CUDA文档和示例以获取更多详细信息。

## C++ cuda库 编译和链接

编译和链接使用CUDA库的C++代码通常需要遵循以下步骤。以下示例假设你已经安装了NVIDIA的GPU驱动、CUDA工具包和相应版本的cuBLAS、cuFFT等库。

### 编写CUDA C++代码

首先，编写包含CUDA核函数的C++源代码。在CUDA C++代码中，通常使用`__global__`修饰符定义在GPU上执行的核函数。

```cpp
// vectorAdd.cu
#include <iostream>

__global__ void vectorAddition(float* a, float* b, float* result, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < size) {
        result[idx] = a[idx] + b[idx];
    }
}

int main() {
    const int size = 1024;
    const int blockSize = 256;

    // ... 与上述示例相同的主机代码 ...

    // 在主机上调用 CUDA 核函数
    vectorAddition<<<(size + blockSize - 1) / blockSize, blockSize>>>(deviceA, deviceB, deviceResult, size);

    // ... 处理结果及释放内存 ...
}
```

### 编译CUDA C++代码

使用`nvcc`命令来编译CUDA C++代码。`nvcc`是NVIDIA CUDA Compiler的命令行工具。

```bash
nvcc -o your_executable vectorAdd.cu
```

此命令将源文件`vectorAdd.cu`编译为可执行文件`your_executable`。`nvcc`会负责将CUDA核函数编译为GPU二进制代码，并链接CUDA运行时库。

### 编译和链接其他C++文件

如果你的项目包含其他C++源文件，你可以使用常规的C++编译器（例如`g++`）来编译和链接这些文件。确保将CUDA头文件和库的路径包含到编译过程中，并链接相应的CUDA库。

```bash
g++ -o your_executable your_main.cpp -I/path/to/cuda/include -L/path/to/cuda/lib -lcudart -lcublas -lculibos -lcufft
```

在上述命令中，`/path/to/cuda/include`和`/path/to/cuda/lib`需要替换为你系统中实际的CUDA头文件和库文件的路径。

### 运行可执行文件

最后，运行生成的可执行文件。

```bash
./your_executable
```

请注意，确保CUDA库和头文件的路径正确设置，并且使用了正确的编译选项。在实际项目中，可能需要更详细的配置和管理依赖项。

## 课程笔记

+ 超标量，Superschalar

+ 指令调度，Scheduling

+ 寄存器重命名，Register Renaming   

+ 乱序执行，Out-of-Order(OoO)Execution
  + 重排指令，获得最大的吞吐率
  + 重排缓冲区

+ 存储器架构/层次，Memory Hierarchy
  + 存储器越大越慢
  + 粗略的估计
    + SRAM(L1, L2, L3)
    + DRAM(memory)
    + Flash(disk)
    + HDD(disk)

+ 缓存,Caching
  + 将数据放在尽可能接近的位置
  + 利用
    + 时间临近性，刚刚使用过的数据很可能会被再次使用
    + 空间临近性，倾向于使用周围的临近的数据
  + 缓存层次，Cache Hierarchy
    + 硬件管理
      + L1 Instruction/Data caches
      + L2 unified cache
      + L3 unified cache
    + 软件管理
      + Main memory
      + Disk

+ 存储器的另外设计考虑
  + 分区Banking  --  避免多端口
  + 一致性  Coherency
  + 控制器  Memory Controller

+ CPU内部的并行性
  + 指令级并行
    + 超标量
    + 乱序执行
  + 数据级并行
    + 矢量计算
  + 线程级并行
    + 同步多线程
    + 多核

+ 向量运算,Vectors Motivation
+ 数据级并行 Data=level Parallelism
  + 单指令多数据 Single Instruction Multiple Data(SIMD)
    + 执行单元(ALU)很宽

+ 线程级并行  Thread-Level-Parallelism

+ 多核 Multicore
  + 将流水线完整复制

+ 锁存，一致性和同一性
  + 问题：多线程读写同一块数据
    + 解决办法：加锁
  + 问题：谁的数据是正确的？
    + 解决办法：缓存一致性协议Coherence
  + 问题：什么样的数据是正确的Consistency
    + 解决方法：存储器同一性模型

+ 现实的困境：能量墙 Power Wall
+ 新时代的计算计数：并行计算
  + 常规传统单核处理器遇到物理约束，时钟频率(perf/clock)无法保持线性增长
+ 新摩尔定律
  + 处理器越来越胖
  + 单核的性能不会大幅度提升
+ 另外一堵墙：存储器墙
  + 处理器的存储器带宽无法满足处理能力的提升
+ 结论
  + CPU，为串行程序优化
    + Pipelines, branch prediction, superscalaer, OoO
    + Reduce execution time with high clock speeds and high utilization
  + 缓慢的内存带宽(存储器带宽)将会是大问题
  + 并行处理是方向

## 并行技术的概述

+ (数据)并行处理方法
+ 串行计算模式
  + 常规软件是串行的
    + 设计运行于一个中央处理器上(CPU)
    + 通过离散的指令序列完成一个问题的解决
    + 一条一条指令的执行
    + 同时只有一条指令在执行
+ 并行计算模式
  + 一句话：并行计算是同时应用多个计算资源解决一个计算问题
    + 设计多个计算资源或处理器
    + 问题被分解为多个离散的部分，可以同时处理(并行)
    + 每个部分可以由一系列指令完成
  + 每个部分的指令在不同的处理器上执行

+ 概念和名词
  + Flynn 矩阵， The matrix below defines the 4 possible classifications according to Flynn
    + SISD, Single Instruction, Single Data
    + SIMD, Single Instruction, Multiple Data
    + MISD, Multiple Instruction, Single Data
    + MIMD, Multiple Instruction, Multiple Data
+ 常见名词
  + Task，任务  --  可以得到完整结果的一个过程，一个或多个代码段
  + Parallel Task , 并行任务
  + Serial Execution， 串行执行
  + Parallel Execution Execution，并行执行
  + Shared Memory，共享存储
  + Distributed Memory，分布式存储  --  存储的东西放在不同的地方
  + Communications，通信
  + Synchronization，同步  --  
  + Granularity，粒度  --  划分任务的大小
  + Observed Speedup，加速比  -- 对比一个标志物，获得性能的提升
  + Parallel Overhead，并行开销  --  最主要是通讯的问题
  + Scalability，可扩展性  --  

+ 存储器架构
  + 共享存储(Shared Memory)
  + 分布式存储(Distributed Memory)
  + 混合分布式-共享式存储(Hybrid Distributed-Shared Memory)

+ 并行编程模型
  + 共享存储模型(Shared Memory Model)
  + 线程模型(Threads Model)
  + 消息传递模型(Message Passing Model)
  + 数据并行模型(Data Parallel Model)
+ 具体实例
  + OpenMP
  + MPI
  + Single Program Multiple Data(SPMD)
  + Multiple Program Multiple Data(MPMD)
+ 设计并行处理程序和系统
  + 自动和手动并行
  + 理解问题和程序
  + 分块分割
  + 通信
    + broadcast，广播
    + scatter，发散
    + gather，汇集
    + reduction，整合
  + 同步
  + 负载均衡  --  一核有难，七核围观 
  + 粒度
  + I/O
  + 成本
  + 性能分析和优化
+ 加速比：
  + speedup = 1/(p/N + S)
    + P = 并行部分
    + N = 处理器数码
    + S = 串行部分

## 搭建并行编程环境

+ cuda zone

+ sample/devicequery

### 五

+ 名词解释
  + FLOPS  --  FLoating -point OPerations per Second
  + GFLOPS  --  One billion FLOPS
  + TFLOPS  --  1000 GFLOPS

+ 为什么需要GPU？
  + 应用的需求越来越高
  + 计算机技术由应用推动

+ GPU(Graphic Processing Unit),是一个异构的多处理器芯片，为图形图像处理优化

+ 三种方法提升GPU的处理速度

+ GPU的存储器

+ 停滞
  + 大量的独立片元相互切换
  + 通过片元切换掩藏延迟

+ 上下文存储空间, Storing contexts
  + 上下文存储池
+ 上下文呢也可以软件也可以硬件管理

+ 如果只是一个ALU，只能称为一个计算单元，
+ ALU＋存储，是一个计算核心，简称核

+ Fermi架构细节
  + 480 stream processors("CUDA cores")
    + 一个stream processor，流处理器，理解上可以等同为一个ALU，计算单元

+ 存储和数据访问 --  访存
  + Recall:"CPU-style" core
    + memory hierarchy, 多级缓存
  + GPU型的吞吐处理核
    + 将存储器放在了外面
+ 访存带宽，是非常宝贵的资源
+ 带宽测试  --  
+ 带宽受限
  + 减少带宽需求
+ GPU，是异构 众核 处理器，针对吞吐优化
+ 高效的GPU任务具备的条件
  + 具有成千上万的独立工作
    + 尽量利用大量的ALU单元
    + 大量的片元切换掩藏延迟
  + 可以共享指令流
    + 适用于SIMD处理
  + 最好是计算密集的任务
    + 通信和计算开销比例合适
    + 不要受制于访问带宽

### 六

+ CPU-GPU交互
  + 各自的物理内存空间
  + 通过PCIE总线互连
  + 交互开销较大

+ 访存速度
  + Register
  + Shared Memory
  + Local Memory
  + Global Memory
  + Constant Memory
  + Texture Memory
  + Instruction Memory

+ 线程组织架构说明
  + 一个Kernel具有大量线程
  + 线程被划分成线程块 blocks
  + Kernel启动一个grid，包含若干线程块
  + 线程和线程块具有唯一的标识

+ 编程模型：
  + 常规意义的GPU用于处理图形图像
  + 操作于像素，每个像素的操作都类似
  + 可以应用SIMD，也可以认为是数据并行分割

+ CUDA编程模式：Extended C              

+ CUDA函数声明
  + __global__定义一个kernel函数：入口函数，CPU上调用，GPU上执行，必须返回void

### 7

+ 2007 -- NVIDIA发布CUDA
  + CUDA  --  全称 Compute Uniform Device  Architecture，统一计算设备架构

+ CUDA术语
  + Host  --  即主机端，通常指CPU。采用ANSI标准C语言编程
  + Device --  即设备端，通常指GPU（数据可并行）。采用ANSI 标准C的扩展语言编程
  + Host和Device拥有各自的存储器
  + CUDA编程：包括主机端和设备端两部分代码
  + Kernel  --  数据并行处理函数。通过调用kernel函数在设备端创建轻量级线程，线程由硬件负责创建并进行管理