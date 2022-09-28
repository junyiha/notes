## xenomai 3 组成结构

+ `xenomai3`于2015年正式发布，从`xenomai3`开始支持两种方式构建`linux`实时系统，分别是`cobalt`和`mercury`

+ `cobalt` : 
  + 添加一个实时内核，双核结构。具有实时内核`cobalt`，实时驱动模型`RTDM`，实时应用`POSIX`接口库`libcobalt`，然后再基于`libcobalt`实现的其他`API skins`

+ `mercury` ： 
  + 基于直接修改linux内核源代码的`PREEMPT RT`，应用空间在`glibc`之上，添加`xenomai API`库

+ `mercury`只是在`glibc`上加了一层；而`cobalt`从底层硬件驱动，内核空间到用户空间，保证了实时任务的实时性