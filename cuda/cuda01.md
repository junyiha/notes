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