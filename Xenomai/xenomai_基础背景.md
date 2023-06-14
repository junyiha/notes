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

## xenomai内核解析之xenomai初探

+ 参考链接：
  + `https://www.cnblogs.com/wsg1100/p/12833126.html`

### xenomai3

+ xenomai3于2015年正式发布，从xenomai3开始支持两种方式构建linux实时系统，分别是cobalt 和 mercury。
  + cobalt ：添加一个实时内核核，双核结构。具有实时内核cobalt、实时驱动模型RTDM、实时应用POSIX接口库libcobalt，然后再基于libcobalt实现的其他API skins，如Alchemy API、VxWorks® emulator、pSOS® emulator等(具体查看应用编程接口文档`https://xenomai.org/documentation/xenomai-3/html/xeno3prm`)，即VxWorks、pSOS应用程序可稍微修改源码就可以在xenomai上编译运行。
    + 需要说明的是Alchemy API是xenomai除posix外的官方编程接口，提供了更接近于传统RTOS编程方式的编程接口，对于不熟悉linux应用开发的MCU开发人员也能很快上手。在xenomai2上Alchemy API是xenomai的原生编程接口，性能最好，posix API是在Alchemy API上实现的skin。在xenomai3相反，Alchemy API、VxWorks、pSOS均基于posix接口实现，也正因为这样诞生了mercury方式。
  + mercury ：基于直接修改linux内核源代码的PREEMPT RT，应用空间在glibc之上，添加xenomai API库，如下图所示。可以在不支持cobalt内核时，可使用该方法运行xenomai应用；也就是说你还可以通过mercury方式在PREEMPT RT上编译运行VxWorks、pSOS等接口的应用程序。 当然，也可不需要PREEMPT RT，直接使用linux，只是实时性就……

### xenomai各种接口应用编译

#### 编译参数获取

+ xenomai 3组成结构小节说到，xenomai库libcobalt提供了多种编程接口，这些接口编写的实时应用程序如何编译呢？xenomai提供了一个脚本工具`xeno-config`来生成各个接口的GCC编译链接参数：
  ```
    root@cor01:/usr/xenomai/bin# ./xeno-config --help
    Usage xeno-config OPTIONS
    Options :
            --help
            --v,--verbose
            --version
            --cc
            --ccld
            --arch
            --prefix
            --[skin=]posix|vxworks|psos|alchemy|rtdm|smokey|cobalt
            --auto-init|auto-init-solib|no-auto-init
            --mode-check|no-mode-check
            --cflags
            --ldflags
            --lib*-dir|libdir|user-libdir
            --core
            --info
            --compat
    root@cor01:/usr/xenomai/bin# ./xeno-config --v
    xeno-config --verbose
            --core=cobalt
            --version="3.2.1"
            --cc="gcc"
            --ccld="/usr/xenomai/bin/wrap-link.sh gcc"
            --arch="x86"
            --prefix="/usr/xenomai"
            --library-dir="/usr/xenomai/lib"
    root@cor01:/usr/xenomai/bin# 
  ``` 
+ 其中`--[skin=]`参数指定我们编译的应用程序是什么接口类型，例如编译一个POSIX接口的实时应用，指定接口`(skin)--posix`，同时使用参数`--cflags`来获取POSIX接口实时应用的编译参数：
  ```
    root@cor01:/usr/xenomai/bin# ./xeno-config --posix --cflags
    -I/usr/xenomai/include/cobalt -I/usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -fasynchronous-unwind-tables -D__COBALT__ -D__COBALT_WRAP__
  ``` 

####  链接参数获取

+ 获取链接参数，`--ldflags` 得到链接参数：
  ```
    root@cor01:/usr/xenomai/bin# ./xeno-config --posix --ldflags
    -Wl,--no-as-needed -Wl,@/usr/xenomai/lib/cobalt.wrappers -Wl,@/usr/xenomai/lib/modechk.wrappers  /usr/xenomai/lib/xenomai/bootstrap.o -Wl,--wrap=main -Wl,--dynamic-list=/usr/xenomai/lib/dynlist.ld -L/usr/xenomai/lib -lcobalt -lmodechk -lpthread -lrt  
  ``` 
+ 同样通过指定`--[skin=]`为vxworks、psos来编译VxWorks、psos实时应用程序到xenomai上运行。

### xenomai 内核系统调用

+ 参考链接：
  + `https://www.cnblogs.com/wsg1100/p/13160821.html`

#### 关于系统调用

+ 解析系统调用是了解内核架构最有力的一把钥匙。
+ 在Linux内核基础上加入xenomai实时系统内核后，在内核空间两个内核共存，实时任务需要xenomai内核来完成实时的服务，如果实时任务需要用到linux的服务，还可以调用linux内核的系统调用，你可能会好奇xenomai与linux两个内核共存后系统调用是如何实现的？

+ 为什么需要系统调用？现代操作系统中，处理器的运行模式一般分为两个空间：内核空间和用户空间，大部分应用程序运行在用户空间，而操作系统内核和设备驱动程序运行在内核空间，如果应用程序需要访问硬件资源或者需要内核提供服务，该怎么办？
+ 为了向用户空间上运行的应用程序提供服务，内核提供了一组接口。透过该接口，应用程序可以访问硬件设备和其他操作系统资源。这组接口在应用程序和内核之间扮演了使者的角色，应用程序发送各种请求，而内核负责满足这些请求，这些接口就是系统调用，它是用户空间和内核空间一个中间层。

+ 系统调用层主要作用有三个：
  + 它为用户空间提供了一种统一的硬件的抽象接口。比如当需要读些文件的时候，应用程序就可以不去管磁盘类型和介质，甚至不用去管文件所在的文件系统到底是哪种类型。
  + 系统调用保证了系统的稳定和安全。应用程序要访问内核就必须通过系统调用层，内核可以在系统调用层对应用程序的访问权限、用户类型和其他一些规则进行过滤，这避免了应用不正确地访问内核，保证了系统和各个应用程序的安全性。
  + 可移植性。可以让应用程序在不修改源代码的情况下，在不同的操作系统或拥有不同硬件架构的系统中重新编译运行。

+ 回到本文开头的问题，该问题细分为如下两个问题：
  + 双核共存时，如何区分应用发起的系统调用是xenomai内核调用还是linux内核调用？
  + 一个xenomai实时任务既可以调用xenomai内核服务，也可以调用linux内核服务，这是如何做到的？

#### 32位Linux系统调用

+ linux操作系统的API通常以C标准库的方式提供，比如linux中的libc库。C标准库中提供了POSIX的绝大部分API实现，glibc为了提高应用程序的性能，还对一些系统调用进行了封装。
+ 此外，由于32位系统系统调用使用软中断`int 0x80`指令实现，应用程序也可以通过汇编直接进行系统调用。软中断属于异常的一种，通过执行该指令陷入(trap)内核，trap在整理的文档x86 Linux中断系统有说明。内核初始化过程中，通过函数`tarp_init()`设置IDT（Interrupt Descriptor Table 记录每个中断异常处理程序的地址的一张表），有关`int 0x80`的IDT表项如下：
  ```
    static const __initconst struct idt_data def_idts[] = {
    	......
    	SYSG(IA32_SYSCALL_VECTOR,	entry_INT80_32),
    	......
    };
  ``` 
+ 当产生系统调用时，硬件根据向量号在 IDT 中找到对应的表项，即中断描述符，进行特权级检查，发现 DPL = CPL = 3 ，允许调用。然后硬件将切换到内核栈 (tss.ss0 : tss.esp0)。接着根据中断描述符的 segment selector 在 GDT / LDT 中找到对应的段描述符，从段描述符拿到段的基址，加载到 cs 。将 offset 加载到 eip。最后硬件将 ss / sp / eflags / cs / ip / error code 依次压到内核栈。于是开始执行entry_INT80_32函数，该函数在entry_32.S定义：
+ 在内核栈的最高地址端，存放的是结构 pt_regs，首先通过 push 和 SAVE_ALL 将当前用户态的寄存器，保存在栈中 pt_regs 结构里面.保存完毕后，关闭中断，将当前栈指针保存到 eax，即do_int80_syscall_32的参数1。
+ 调用do_int80_syscall_32=>do_syscall_32_irqs_on
+ 在这里，将系统调用号从pt_reges中eax 里面取出来，然后根据系统调用号，在系统调用表中找到相应的函数进行调用，并将寄存器中保存的参数取出来，作为函数参数。如果仔细比对，就能发现，这些参数所对应的寄存器，和 Linux 的注释是一样的。ia32_sys_call_table系统调用表生成后面解析(此图来源于网络)
+ 相关内核调用执行完后，一直返回到 do_syscall_32_irqs_on ，如果系统调用有返回值，会被保存到 regs->ax 中。接着返回 entry_INT80_32 继续执行，最后执行 INTERRUPT_RETURN 。 INTERRUPT_RETURN 在 arch/x86/include/asm/irqflags.h 中定义为 iret ，iret 指令将原来用户态保存的现场恢复回来，包含代码段、指令指针寄存器等。这时候用户态进程恢复执行。

#### 32位实时系统调用

+ xenomai+linux双内核架构下，通过I-pipe 拦截系统调用，并将系统调用定向到实现它们的系统。

## xenomai内核解析

+ 参考链接：`https://www.cnblogs.com/wsg1100/p/13836497.html`

### 什么是实时？

+ 实时系统是必须在设置的截止时间内对环境中的事件做出反应的系统，否则会产生严重的后果。

### 实时分类

+ 根据错过截止时间产生的后果，实时任务可以分为三类：
  + 硬实时(Hard real time system)
  + 强实时(Firm real time system)
  + 软实时(Soft real time system)

+ 硬实时(Hard real time system)
  + 如果在截止时间之后产生结果，可能对受控系统造成灾难性后果，则该任务是硬实时任务。
  + 硬任务的例子可以在安全关键系统中找到，并且通常与传感、驱动和控制活动有关，例如：
    + 汽车安全气囊的检测与控制；
    + 反导弹系统要求硬实时。反导弹系统由一系列硬实时任务组成。反导系统必须首先探测所有来袭导弹，正确定位反导炮，然后在导弹来袭之前将其摧毁。所有这些任务本质上都是硬实时的，如果反导弹系统有任何一个任务失败都将无法成功拦截来袭导弹。

+ 强实时(Firm real time system)
  + 如果在截止日期之后产生结果对系统无用，但不会造成任何损害，则该任务是强实时任务。
  + 在网络应用程序和多媒体系统中找到，在这些系统中，跳过一个数据包或一个视频帧比长时间延迟处理更重要。 因此，它们包括以下内容：
    + 视频播放；
    + 音/视频编解码中，没有在设置的码率时序范围内执行完，产生结果都是无用的丢弃即可，继续下一轮读取；
    + 在线图像处理；

+ 软实时(Soft real time system)
  + 如果实时任务在截止日期之后产生结果仍然对系统有用，尽管会导致性能下降，则该任务是软实时任务。
  + 软任务通常与系统-用户交互有关，有点延迟什么的并不影响，只是体验稍差点。 因此，它们包括：
    + 用户界面的命令解释器；
    + 处理来自键盘的输入数据；
    + 在屏幕上显示消息；
    + 网页浏览等；

### 常见的RTOS

+ 小型实时操作系统 UCOS、FreeRTOS、RT-Thread…
+ 大型实时操作系统 RT linux、VxWorks、QNX、sylixOS…

### latency 和 jitter

+ 硬实时系统是必须在设置的截止时间内对环境中的事件做出反应的系统。硬实时操作系统应具备的最重要特性之一是确定性、可预期性。
+ 操作系统的实时性能通常用`latency`或`jitter`来表示:
  + 事件预期发生与实际发生的时间之间的时间称为延迟(`latency`)，
  + 实际发生的最大时间与最小时间之间的差值称为抖动(`Jitter`)，两者均可表示实时性。 
+ 根据实时性的定义，延迟必须是确定的，不能超过`deadline`，否则将会产生严重的后果。

### 实时性的影响因素

+ 硬实时操作系统应具备的最重要特性之一是确定性、可预测性，系统应该保证满足所有关键时序约束。
+ 然而，这取决于一系列因素，这些因素涉及硬件的架构特征、内核中采用的机制和策略，以及用于实现应用程序的编程语言、软件设计等。
+ 根据实时性定义，计算机系统中所有导致程序执行时间不确定的因素，都是实时性影响因素。

#### 硬件 -- CPU架构

+ 硬件方面，第一个影响调度可预测性的是处理器本身。
+ 处理器的内部特性是不确定性的第一个原因，例如指令预取、流水线操作、分支预测、高速缓存存储器和直接存储器访问（DMA）机制。
+ 这些特性虽然改善了处理器的平均性能，但它们引入了非确定性因素，这些因素阻止了对最坏情况执行时间WCET（Worst-caseExecutionTime）的精确估计。
+ 高端CPU，如I5、I7实时性不一定有低端的赛扬、atom系列的好，芯片的设计本身定位就是高吞吐量而不是实时性，实时性与吞吐量不可兼得。

#### 硬件 -- Cache

+ CPU 里的 L1 Cache 或者 L2 Cache，访问延时是内存的 1/15 乃至 1/100，想要追求极限性能，需要尽可能地多从 CPU Cache 里面拿数据，减少cache miss，上面的分配CPU专门对实时任务服务就是对非共享的L1 、L2 Cache的充分优化。
+ 对于L3 Cache，多个cpu核与GPU共享，无法避免非实时任务及GUI争抢L3 Cache对实时任务的影响。

+ 为此intel 推出了资源调配技术(Intel RDT)，提供了两种能力：监控和分配。
+ Intel RDT提供了一系列分配(资源控制)能力，包括缓存分配技术(Cache Allocation Technology, CAT)，代码和数据优先级(Code and Data Prioritization, CDP) 以及 内存带宽分配(Memory Bandwidth Allocation, MBA)。
+ 该技术旨在通过一系列的CPU指令从而允许用户直接对每个CPU核心（附加了HT技术后为每个逻辑核心）的L2缓存、L3缓存（LLC--Last Level Cache ）以及内存带宽进行监控和分配。

+ RDT一开始是为解决云计算的问题，在云计算领域虚拟化环境中，宿主机的资源（包括CPU cache和内存带宽）都是共享的。这带来一个问题就是：如果有一个过度消耗cache的应用耗尽了L3缓存或者大量的内存带宽，将无法保障其他虚拟机应用的性能。这种问题称为 noisy neighbor。
+ 同样对于我们的实时系统也是类似：由于L3 Cache多核共享，如果有一个过度消耗cache的非实时应用耗尽了L3缓存或者大量的内存带宽，将无法保障xenomai实时应用的性能。
+ 以往虚拟化环境中解决方法是通过控制虚拟机逻辑资源(cgroup)但是调整粒度太粗，并且无法控制处理器缓存这样敏感而且稀缺的资源。为此Intel推出了RDT技术。在Intel中文网站的 通过英特尔® 资源调配技术优化资源利用视频形象介绍了RDT的作用。
+ Intel的Fenghua Yu在Linux Foundation上的演讲 Resource Allocation in Intel® Resource Director Technology 可以帮助我们快速了解这项技术。
+ 总的来说，RDT让我们实现了控制处理器缓存这样敏感而且稀缺的资源，对我们对实时性能提升有很大帮助(不仅限于xenomai，RTAI、PREEMPT-RT均适用)。

+ CAT（缓存分配技术，Cache Alocation Technology），对最后一级缓存（L3 Cache）实现分区，用户可以通过限制每个核心能够向其中分配缓存行的LLC数量，将LLC的部分分配给特定核心，使用该技术可以提升实时任务Cahe命中率，减少MSI延迟和抖动，进而提升实时性能。（不是所有intel处理器具有该功能，一开始只有服务器CPU提供该支持,据笔者了解，6代以后的CPU基本支持CAT。关于CAT 见github)，对于大多数Linux发行版，可直接安装使用该工具，具体的cache分配策略可根据后面的资源隔离情况进行。
  + `sudo apt-get install intel-cmt-cat`

#### 硬件 -- TLB

+ 与cache性质一致。

#### 硬件 -- 分支预测

+ 现代 CPU 的流水线级数非常长，一般都在10级以上，指令分支判断错误（Branch Mispredict）的时间代价昂贵。如果判断预测正确，可能只需要一个时钟周期；如果判断错误，就还是需要10-20 左右个时钟周期来重新提取指令。
+ 现代 CPU 的分支预测正确率已经可以在一般情况下维持在 95% 以上，所以当分支存在可预测的规律的时候，还是以性能测试的结果为最终的优化依据。

#### 硬件 -- Hyper-Threading

+ 人们对CPU的性能的追求是无止境的，在CPU性能不断优化提高过程中，对于单一流水线，最佳情况下，IPC 也只能到 1。无论做了哪些流水线层面的优化，即使做到了指令执行层面的乱序执行，CPU 仍然只能在一个时钟周期里面取一条指令。
+ 为使IPC>1，诞生了多发射（Mulitple Issue）和超标量（Superscalar）技术，伴随的是每个CPU流水线上各种运算单元的增加。但是当处理器在运行一个线程，执行指令代码时，一方面很多时候处理器并不会使用到全部的计算能力，另一方面由于CPU在代码层面运行前后依赖关系的指令，会遇到各种冒险问题，这样CPU部分计算能力就会处于空闲状态。
+ 为了进一步“压榨”处理器，那就找没有依赖关系的指令来运行好，即另一个程序:
  + 一个核可以分成几个逻辑核，来执行多个控制流程，这样可以进一步提高并行程度，这一技术就叫超线程，又称同时多线程（Simultaneous Multi-Threading，简称 SMT）。
+ 由于超线程技术通过双份的 PC 寄存器、指令寄存器、条件码寄存器，在逻辑层面伪装为2个CPU，但指令译码器和ALU是公用的，这就造成实时任务运行时在CPU执行层面的不确定性，造成非实时线程与实时线程在同一物理核上对CPU执行单元的竞争，影响实时任务实时性。

#### 硬件 -- Multi-Core

+ 接收 IRQ 的 CPU 可能不是响应者休眠的 CPU，在这种情况下，前者必须向后者发送重新调度请求，以便它恢复响应者。这通常是通过处理器间中断完成的，也就是IPI，IPI的发送和处理进一步增加了延迟。
+ 此外，多核LLC共享，NUMA架构远端内存访问等，均会导致访问延迟不确定。

#### 硬件 -- DMA

+ DMA突发传输不确定占用总线带宽，影响程序执行；
+ 总线动态调频省电等

#### 硬件 -- 其他

+ 其他影响因素有内存、散热。
+ 提升内存频率可降低内存访问延时；使用双通道内存，这两个内存CPU可分别寻址、读取数据，从而使内存的带宽增加一倍，数据存取速度也相应增加一倍（理论上），内存访问延时得到缩短，进而提升系统的实时性能；
+ 处理器散热设计不好，温度过高时会引发CPU降频保护，系统运行频率降低影响实时性，热设计应确保在高工作量时的温度不会引发降频。
+ 对于X86 CPU，双通道内存性能是单通道内存的2. 5倍以上；正确的热设计可使实时性提升1.4倍以上。

#### BISO （X86平台）

+ BISO需要针对实时系统进行配置。优化的BIOS设置与使用默认BISO设置的实时性能差距高达9倍。

#### 软件

+ 操作系统：调度算法，同步机制，信号量类型，内存管理策略，通信语义和中断处理，是否使用mmu等，OS的类型与定位已经决定了一些影响因素与实时之间的取舍。
+ 资源的分配隔离：分配CPU专门对实时任务服务、将多余中断隔离到非实时任务CPU上，分配CPU专门对实时任务服务可使L1 、L2 Cache只为实时任务服务。
+ 动态库运行时延迟绑定。
+ 内存分配算法时间不确定性。
+ 实时任务的设计，良好的软件设计能更好的发挥实时性能。
+ 其他，虚拟化、GUI等 。

#### GPU

+ 硬件上GPU与CPU共享L3 Cache ，因此GUI会影响实时任务的实时性。intel建议根据GUI任务的工作负载来固定GPU的运行频率，且频率尽可能低。减小GPU对实时任务实时性的影响。

### 优化措施

+ 原则：降低不确定性，提高可预期性，在此基础上，再提高速度，降低延时。

+ 硬件：
  + 除处理器外，内存方面，使用双通道内存，尽可能高的内存频率。
  + 散热当面，针对处理器工作负载设计良好的散热结构, 否则芯片保护会强制降频，频率调整CPU会停顿几十上百us。

#### Linux

+ xenomai基于linux，xenomai作为一个小的实时核与linux共存，xenomai并未提供完整的硬件管理机制，许多硬件配置是linux 驱动掌管的，必须让linux配置好，给xenomai提供一个好的硬件环境，让xenomai充分发挥其RTOS的优势，
+ 主要宗旨：尽可能的不让linux非实时部分影响xenomai，无论是软件还是硬件。

#### Linux -- Kernel CMDLINE

+ cpu隔离
+ 多核情况下，设置内核参数`isolcpus=[cpu列表]`,将列表中的CPU从linux内核SMP平衡和调度算法中剔除，将剔除的CPU用于RT应用。如4核CPU平台将第3、4核隔离来做RT应用。
+ CPU编号从"0"开始，列表的表示方法有三种：
  + `numA,numB,...,numN`
  + `numA-numN`
  + `numA,...,numM-numN`
+ 例如：
  + isolcpus=0,3,4-7表示隔离CPU0、3、4、5、6、7.
  + `GRUB_CMDLINE_LINUX="isolcpus=2,3"`
+ 以上只是linux不会调度普通任务到CPU2和3上运行,这是基础，此时还需要设置xenomai方面的CPU隔离，
  + 方法一，任务通过函数pthread_attr_setaffinity_np()设置xenomai任务只在CPU3和4上调度，隔离后的CPU的L1、L2缓存命中率相应的也会得到提高。
    ```
      cpu_set_t cpus;
      CPU_ZERO(&cpus);
      CPU_SET(2, &cpus);//将线程限制在指定的cpu2上运行
      CPU_SET(3, &cpus);//将线程限制在指定的cpu3上运行
      ret = pthread_attr_setaffinity_np(&tattr, sizeof(cpus), &cpus);
    ``` 
  + 方法二，向xenomai设置内核参数supported_cpus,指定xenomai支持的CPU，xenomai任务会自动放到cpu2、cpu3上运行，注意对于xenomai3.2以上版本，supported_cpus必须包含CPU0，否则xenomai内核无法启动！！。
    + xenomai 内核参数supported_cpus与linux不同，supported_cpus是一个16进制数，每bit置位表示支持该CPU，要支持CPU2、CPU3，需要置置位bit2、bit3，即supported_cpus=0x0c(00001100b）。
    + `GRUB_CMDLINE_LINUX="isolcpus=2,3 xenomai.supported_cpus=0x0C"`
+ 注：linux内核参数isolcpus=CPU编号列表是基础，否则若不隔离linux任务，后面的xenomai设置将没任何意义。

#### Linux -- Full Dynamic Tick

+ 将CPU2、CPU3作为xenomai使用后，由于xenomai调度是完全基于优先级的调度器，并且我们已将linux任务从这两个cpu上剔除，CPU上Tick也就没啥用了，避免多余的Tick中断影响实时任务的运行，需要将这两个cpu配置为Full Dynamic Tick模式，即关闭tick。通过添加linux内核参数`nohz_full=[cpu列表]`配置。
+ `nohz_full=[cpu列表]`在使用`CONFIG_NO_HZ_FULL = y`构建的内核中才生效。

+ 为什么是linux内核参数呢？
  + 双核下时间子系统中分析过，每个CPU的时钟工作方式是linux初始化并配置工作模式的，xenomai最后只是接管而已，所以这里是通过linux内核参数配置。
+ 注意：boot CPU(通常是0号CPU)会无条件的从列表中剔除。这是一个坑~

#### Linux -- Offload RCU callback

+ 从引导选择的CPU上卸载RCU回调处理,使用内核线程 `“rcuox / N”` 代替，通过linux内核参数`rcu_nocbs=[cpu列表]`指定的CPU列表设置。这对于HPC和实时工作负载很有用，这样可以减少卸载RCU的CPU上操作系统抖动。
+ `"rcuox / N"`,N表示CPU编号，
+ `‘x’：'b'`是RCU-bh的b,'p'是RCU-preempt，‘s’是RCU-sched。
+ `rcu_nocbs=[cpu列表]`在使用`CONFIG_RCU_NOCB_CPU=y`构建的内核中才生效。除此之外需要设置RCU内核线程rcuc/n和rcub/n线程的SCHED_FIFO优先级值RCU_KTHREAD_PRIO，RCU_KTHREAD_PRIO设置为高于最低优先级线程的优先级，也就是说至少要使该优先级低于xenomai实时应用的优先级，避免xenomai实时应用迁移到linux后，由于优先级低于RCU_KTHREAD的优先级而实时性受到影响，

#### 中断

+ xenomai用户态实时应用运行时，中断优先级最高，CPU必须响应中断，虽然有ipipe会简单将非实时设备中断挂起，但是频繁的非实时设备中断产生可能引入无限延迟，也会影响实时任务的运行。
+ 因此多，核情况下，通过内核参数`irqaffinity==[cpu列表]`，设置linux设备中断的亲和性，设置后，默认由这些cpu核来处理中断。避免了非实时linux中断影响cpu2、cpu3上的实时应用，将linux中断指定到cpu0、cpu1处理，添加参数：
  + `GRUB_CMDLINE_LINUX="isolcpus=2,3 xenomai.supported_cpus=0x0c nohz_full=2,3 rcu_nocbs=2,3 irqaffinity=0,1"`
+ 以上只是设置linux中断的affinity，只能确保运行实时任务的CPU2、cpu3不会收到linux非实时设备的中断请求，保证实时性。
+ 要指定cpu来处理xenomai实时设备中断，需要在实时驱动代码中通过函数xnintr_affinity()设置,绑定实时驱动中断由CPU2、CPU3处理代码如下。
+ 虽然ipipe会保证xenomai 实时中断在任何CPU都会优先处理，在实时设备中断比较少的场合，我觉得把linux中断与实时中断分开比较好；如果实时设备中断数量较多，如果隔离就会造成实时中断间相互影响中断处理的实时性，这时候不指定实时中断处理CPU比较好。
+ 编写xenomai实时设备驱动程序时，中断处理程序需要尽可能的短。

+ linux irqbalance 用于优化中断分配，它会自动收集系统数据以分析使用模式，并依据系统负载状况将工作状态置于 Performance mode 或 Power-save mode。简单来说irqbalance 会将硬件中断分配到各个CPU核心上处理。
  + 处于 Performance mode 时，irqbalance 会将中断尽可能均匀地分发给各个 CPU core，以充分利用 CPU 多核，提升性能。
  + 处于 Power-save mode 时，irqbalance 会将中断集中分配给第一个 CPU，以保证其它空闲 CPU 的睡眠时间，降低能耗。
+ 禁用irqbanlance，避免不相干中断发生在RT任务核。发行版不同，配置方式不同，以Ubuntu为例，停止/关闭开机启动如下。
  + `systemctl stop irqbalance.service`
  + `systemctl disable irqbalance.service`
+ 必要的话直接卸载irqbalance。
  + `apt-get remove irqbalance`
+ x86平台还可添加参数acpi_irq_nobalance禁用ACPI irqbalance.
  + `GRUB_CMDLINE_LINUX="isolcpus=2,3 xenomai.supported_cpus=0x0c nohz_full=2,3 rcu_nocbs=2,3 irqaffinity=0,1 acpi_irq_nobalance noirqbalance"`

#### intel 核显配置`[x86]`

+ 主要针对intel CPU的核显，配置intel核显驱动模块i915，内核参数如下。
  + `GRUB_CMDLINE_LINUX="i915.enable_rc6=0 i915.enable_dc=0 i915.disable_power_well=0  i915.enable_execlists=0 i915.powersave=0"`

#### nmi_watchdog `[x86]`

+ NMI watchdog是Linux的开发者为了debugging而添加的特性，但也能用来检测和恢复Linux kernel hang，现代多核x86体系都能支持NMI watchdog。
+ NMI（Non Maskable Interrupt）即不可屏蔽中断，之所以要使用NMI，是因为NMI watchdog的监视目标是整个内核，而内核可能发生在关中断同时陷入死循环的错误，此时只有NMI能拯救它。
+ Linux中有两种NMI watchdog，分别是I/O APIC watchdog（nmi_watchdog=1）和Local APIC watchdog（nmi_watchdog=2）。它们的触发机制不同，但触发NMI之后的操作是几乎一样的。一旦开启了I/O APIC watchdog（nmi_watchdog=1），那么每个CPU对应的Local APIC的LINT0线都关联到NMI，这样每个CPU将周期性地接到NMI，接到中断的CPU立即处理NMI，用来悄悄监视系统的运行。如果系统正常，它啥事都不做，仅仅是更改 一些时间计数；如果系统不正常（默认5秒没有任何普通外部中断），那它就闲不住了，会立马跳出来，且中止之前程序的运行。该出手时就出手。
+ 避免周期中断的NMI watchdog影响xenomai实时性需要关闭NMI watchdog，传递内核参数nmi_watchdog=0.
  + `GRUB_CMDLINE_LINUX="isolcpus=2,3 xenomai.supported_cpus=0x0c nohz_full=2,3 rcu_nocbs=2,3 irqaffinity=0,1 acpi_irq_nobalance noirqbalance i915.enable_rc6=0 i915.enable_dc=0 i915.disable_power_well=0  i915.enable_execlists=0 i915.powersave=0 nmi_watchdog=0"`

#### nosoftlockup

+ linux内核参数，禁用 soft-lockup检测器。
  + `GRUB_CMDLINE_LINUX="isolcpus=2,3 xenomai.supported_cpus=0x0c nohz_full=2,3 rcu_nocbs=2,3 irqaffinity=0,1 acpi_irq_nobalance noirqbalance i915.enable_rc6=0 i915.enable_dc=0 i915.disable_power_well=0  i915.enable_execlists=0 i915.powersave=0 nmi_watchdog=0 nosoftlockup"`

#### CPU特性`[x86]`

+ intel处理器相关内核参数：
  + nosmap
  + nohalt。告诉内核在空闲时,不要使用省电功能PAL_HALT_LIGHT。 这增加了功耗。但它减少了中断唤醒延迟，这可以提高某些环境下的性能，例如联网服务器或实时系统。
  + mce=ignore_ce,忽略machine checkerrors (MCE).
  + idle=poll,不要使用HLT在空闲循环中进行节电，而是轮询以重新安排事件。 这将使CPU消耗更多的功率，但对于在多处理器基准测试中获得稍微更好的性能可能很有用。 它还使使用性能计数器的某些性能分析更加准确。
  + clocksource=tsc tsc=reliable,指定tsc作为系统clocksource.
  + intel_idle.max_cstate=0 禁用intel_idle并回退到acpi_idle.
  + processor.max_cstate=0 intel.max_cstate=0 processor_idle.max_cstate=0 限制睡眠状态c-state。

+ `GRUB_CMDLINE_LINUX="isolcpus=2,3 xenomai.supported_cpus=0x0c nohz_full=2,3 rcu_nocbs=2,3 irqaffinity=0,1 acpi_irq_nobalance noirqbalance i915.enable_rc6=0 i915.enable_dc=0 i915.disable_power_well=0  i915.enable_execlists=0  nmi_watchdog=0 nosoftlockup processor.max_cstate=0 intel.max_cstate=0 processor_idle.max_cstate=0     intel_idle.max_cstate=0 clocksource=tsc tsc=reliable nmi_watchdog=0 nosoftlockup intel_pstate=disable idle=poll nohalt nosmap  mce=ignore_ce"`

#### 内核构建配置

+ 系统构建时，除以上提到的配置外（CONFIG_NO_HZ_FULL = y、CONFIG_RCU_NOCB_CPU=y、RCU_KTHREAD_PRIO=0），其他实时性相关配置如下：
  + `CONFIG_MIGRATION=n、CONFIG_MCORE2=y[x86]、CONFIG_PREEMPT=y、ACPI_PROCESSOR =n[x86]、CONFIG_CPU_FREQ =n、CONFIG_CPU_IDLE =n；`
+ 经过以上配置后可以使用latency测试，观察配置前后的变化。
+ 关于latency，需要注意的是，测试timer-IRQ的latency时，即用latency -t2命令来测试时，xenomai默认使用cpu0的timer，上面提到boot CPU(通常是0号CPU)会无条件的从`nohz_full=[cpu列表]`列表中剔除，所以latency -t2测试时你会发现没什么变化，还可能会变差了(最坏情况差不多一致，平均值变大了)，另外我们将linux中断affinity全都设置为CPU0处理，这些中断或多或少也会影响timer-IRQ的latency。

#### 软件方面

+ 使用静态编译语言
+ 编写高性能的代码
+ 尽量让分支有规律性，使用likely()/unlikely()或编写无分支代码
+ 利用cache局部性原理，防止伪共享
+ 合理分配任务优先级
+ 尽量使用静态库
+ 避免实时任务中进行动态内存分配
+ 驱动程序中断处理尽可能短等等

### 嵌入式实时linux概述

+ Linux系统作为一个GPOS（通用操作系统）发展至今已经非常成熟可靠了，并且由于遵循GPL协议，开放所有系统源代码，非常易于裁剪。更重要的是，与其他开源的GPOS或RTOS相比，Linux系统支持多种处理器、开发板，提供多种软件开发工具，同时Linux系统对网络和图形界面的支持非常出色。显然，选择Linux操作系统在产品的开发周期和成本控制方面都有巨大优势。
+ 虽然Linux系统功能强大、实用性强、易于软件的二次开发，并且提供编程人员熟悉的标准API。但是由于Linux系统一开始就被设计成GPOS（通用操作系统），它的目的是构建一个完整、稳定的开源操作系统，尽量缩短系统的平均响应时间，提高吞吐量，注重操作系统的整体功能需求，达到更好地平均性能。所以标准Linux并不提供硬实时性。

+ 为解决linux不具有硬实时的问题，诞生了几种基于Linux的硬实时解决方案，分为两类：
  + 1)**直接修改Linux内核源代码**。对Linux内核代码进行细微修改并不对内核作大规模的变动，在遵循GPL协议的情况下，直接修改内核源代码将Linux改造成一个完全可抢占的实时系统。其缺点是：通过修改Linux内核，难以保证实时进程的执行不会遭到非实时进程所进行的不可预测活动的干扰。该方法的代表是RT-patch(Real Preemption Patch)。
  + 2)**双内核法**。添加一个实时内核，在内核空间与linux内核并存，把标准的Linux内核作为一个普通进程在实时内核上调度。其优点是可以做到硬实时，并且能很方便地实现一种新的调度策略。常用的双内核法有RT-Linux、RTAI(Real-Time Application Interface)和 Xenomai，

+ 双核法具有较好的实时性。RT-Linux最早出现，开创了双核法的先河，是双核法的代表。基于一种成为实时硬件抽象的层技术RTHAL(Real Time Hardware Abstraction Layer)，且为该技术申请了专利，后RT-Linux被WindRiver 收购并商业化，WindRiver于2011年8月彻底停止对其更新和维护,现在 RT-linux 已经不再更新。

+ xenomai和RTAL同样借鉴RT-Linux，Xenomai项目始于2001年8月，Philippe Gerum是Adeos和Xenomai项目的创始人和维护者。2003年它和RTAI项目合并推出了RTAI/fusion。RTAI/fusion是Linux平台上的具有工业生产级别的实时自由软件开发平台，它基于Xenomai的抽象实时操作系统内核。2005年的时候RTAI/fusion项目又从RTAI中独立出来作为Xenomai项目。
+ 虽然xenomai和RTAL这两个项目基于同一本质的实时硬件抽象层技术ADEOS（Adoptive Domain Environment for Operating System），但是实际上他们有很多不同之处。这些不同之处主要是由他们不同的目标和各自不同的实现方式造成的。
  + RTAI项目致力于技术上可行的最低延迟；
  + Xenomai除此之外还很看重扩展性，可移植性以及可维护性。Xenoami项目不仅提供双核还对PREEMPT RT实时抢占补丁提供支持，这又是与RTAI项目的一个显著的不同。
  + 另外RT-Linux只允许以内核模块的形式提供实时应用；xenomai 更注重用户空间应用的实时性。
+ 综上，从实时性、硬件支持、社区活跃度、API和商业版权等方面综合考虑，xenomai无疑是Linux实时操作系统最好的选择。

### 编译安装

+ 参考连接：`https://www.cnblogs.com/wsg1100/p/12864199.html`