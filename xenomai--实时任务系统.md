## xenomai 3 组成结构

+ `xenomai3`于2015年正式发布，从`xenomai3`开始支持两种方式构建`linux`实时系统，分别是`cobalt`和`mercury`

+ `cobalt` : 
  + 添加一个实时内核，双核结构。具有实时内核`cobalt`，实时驱动模型`RTDM`，实时应用`POSIX`接口库`libcobalt`，然后再基于`libcobalt`实现的其他`API skins`

+ `mercury` ： 
  + 基于直接修改linux内核源代码的`PREEMPT RT`，应用空间在`glibc`之上，添加`xenomai API`库

+ `mercury`只是在`glibc`上加了一层；而`cobalt`从底层硬件驱动，内核空间到用户空间，保证了实时任务的实时性

+ 在标准linux基础上添加一个实时内核Cobalt，得益于基于`ADEOS(Adaptive Domain Environment for Operating System)`，使Cobalt在内核空间于linux内核共存，并把标准的Linux内核作为实时内核中的一个idle进程在实时内核上调度

+ `ADEOS(Adaptive Domain Environment for Operating System)`，提供了一个灵活的环境，可以在多个操作系统之间或单个OS的多个实例之间共享硬件资源，从而使多个优先级域可以同时存在于同一硬件上。
+ 其核心思想是`Domain`,也就是范围的意思，linux内核有linux内核的范围，cobalt内核有bobalt内核的范围
  + 两个内核管理各自范围内的应用，驱动，中断
  + 两个domain之间有优先级之分，cobalt内核优先级高于linux内核
  + I-pipe优先处理高优先级域的中断，来保证高优先级域的实时性
  + 高优先级域可以通过I-pipe向低优先级域发送各类事件等。

+ **在用户空间**，添加针对实时应用优化的库--`libcobalt`，它提供POSIX接口给应用空间实时任务使用，应用通过`libcobalt`让实时内核`cobalt`提供服务

+ **驱动方面，**`xenomai`提供实时驱动框架模型`RTDM(Real-Time Driver Model)`，专门用于`Cobalt`内核，基于`RTDM`进行实时设备驱动开发，为实时应用提供实时驱动。RTDM将驱动分为两类：字符设备，协议设备

+ **中断方面，**`I-pipe(interrupt Pipeline)`分发Linux和Xenomai之间的中断，并以Domain优先级顺序传递中断。I-pipe传递中断，对于实时内核注册的中断，中断产生后能够直接得到处理，保证实时性。对于linux的中断，先将中断记录在i-log,等实时任务让出CPU后，linux得到运行，该中断才得到处理。