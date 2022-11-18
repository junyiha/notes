## 概述

+ 异步操作(asynchronous operation)
  - 是由于很多计算机系统事件会在不可预测的事件，以不可预测的顺序发生而产生的

+ 并发(concurrency)
  - 是指在相同的时间帧内对资源的共享
  - 并发实体，可以是单个程序内部的执行线程或者其他抽象的对象
  - 并发可能发生在单CPU系统，共享相同内存的多CPU系统，或者运行在网络上的独立系统中

+ 通信(communication)
  - 将一个实体的信息传送给另一个实体
  - 程序在李处磁盘这样的本地设备的I/O的同时，还必须要处理网络I/O（网络通信）

+ 上下文切换时间(context-switch time)
  + 是指从执行一个进程转换到执行另一个进程所花费的时间

+ 时间片(quantum)
  + 大致上就是在一个进程不得不让出处理器让其他进程运行之前，分配给这个进程的CPU时间总量

+ 多道程序设计(multiprogramming)
  + 指由于处理时间上的悬殊差异，采取有多个进程准备好要执行，操作系统挑选一个已经准备好的进程来执行，当哪个进程需要等待资源时，操作系统保存从停止处回复此进程所需的所有信息，并选择另一个准备好的进程执行

+ 一次资源请求会引起一次对操作系统的请求（即一次系统调用）
+ 系统调用(system call)
  + 是对操作系统服务的一次请求，它会使正常的CPU周期中断，并将控制权交给操作系统，然后，操作系统就可以切换到另一个进程了

+ 分时(timesharing)
  + 但物理CPU，并发

+ 多处理器系统(multiprocessor systems)
  + 几个处理器都访问一个共享的内存

+ 硬件层并发
  + 由于有多台设备要同时操作
  + 处理器中有内部的并行机制，可以同时处理几条指令，系统中有多个处理器，而且系统通过网络通信进行交互

+ 应用层并发
  + 在信号处理中，I/O与其他处理的重叠中，在通信过程中，在进程间或同一进程的不同线程间的资源共享中，都存在应用层的并发

+ 中断(interrupt)
  + 在常规机器层(conventional machine level)程序中，单指令的执行是处理器指令周期(processor instruction cycle)的结果
  + 在处理器指令周期的正常执行过程中，处理器从程序计数器中检索出一个地址，并执行这个地址上的指令。
  + **在常规机器层出现并发**，是因为外围设备会产生一种被称为中断的电信号，在处理器内部设置一个硬件标志符。
  + 检测中断是指令周期自身的一部分。在每个指令周期中，处理器都检查硬件标识。
  + 如果处理器察觉有中断发生，它就保存程序计数器的当前值，并装载一个新的值，这个新的值是一个被称为中断服务例程(interrupt service routine)或中断处理程序(interupt handler)的特殊函数的地址

+ 异步(asynchronous)
  + 如果一个事件发生的时间不是由某个实体确定的，那么这个事件就是异步于这个实体的。
    + （外部硬件设备产生的中断通常都异步于系统中执行的程序）

+ 同步(synchronous)
  + 如果向指令提供相同的数据，那么，像被零除这样的错误事件，就总是在执行某个特殊指令的时候发生，从这种意义上来说，错误事件是同步的

+ 设备驱动程序(device driver)
  + 被称为设备驱动程序的操作系统例程，通常用来处理外围设备产生的中断。
  + 然后这些驱动程序会通过信号这样的软件机制，来通知相关的进程事件已经发生了

+ 定时器(timer)
  + 操作系统也用中断来实现分时。
  + 大多数计算机都有一个被称为定时器的设备，它可以在一段指定的时间间隔后产生中断。
  + 为了执行用户程序，操作系统在设备程序计数器之前启动定时器。定时器到时的时候，它就产生一个中断，使CPU转而执行定时器中断服务例程。中断服务例程将操作系统代码的地址写入程序计数器，这样，操作系统又获得了控制权

+ 信号(signal)
  + 是事件的软件通知
  + 通常，信号是操作系统对中断（硬件事件）的响应
  + 例如，按下`Ctrl-C`键会使处理键盘的设备驱动程序产生一个中断。驱动程序将这些字符当做中断字符，并发送信号来通知与这个中断相关的进程
  + 当引发信号的那个事件发生时，信号就产生了(generate)了  --  信号可以同步产生，也可以异步产生
    + 如果信号由接收它的进程或线程产生，这个信号就是同步产生的。执行非法指令都会产生同步信号
    + 在键盘上输入`Ctrl-C`会产生一个异步信号

+ 捕捉(catch)
  + 进程执行信号的处理程序时，它就捕捉到了信号
  + 捕捉信号的程序至少有两个并发的部分，主程序和信号处理程序

+ 进程，线程和资源共享
  + 在UNIX中实现并发执行的一种传统方法是：用户通过调用`fork()`函数创建多个进程。
  + 有相同祖先的进程可以通过管道(pipe)进行通信
  + 没有共同祖先的进程可以通过信号，FIFO，信号量，共享的地址空间或消息进行通信
  + 在进程内部可以通过多个执行线程提供并发。
  + 程序执行时，CPU用程序计数器来确定下一步要执行哪条指令。得到的指令流被称为程序的执行线程(thread of execution)。它是进程的控制流

+ 分布式计算
  + 并发和通信共同形成新的应用程序
  + 在分布式计算中使用最广泛的模型是客户端-服务器模型(client-server model)。这个模型中的基本实体
    + 有管理资源的服务器进程，
    + 和需要对共享资源进行访问的客户机进程
  + 基于对象的模型(object-based model)是分布式计算的另一种模型
    + 系统中的每种资源都被看作一个带有消息处理接口的对象，这样就可以用统一的方式来访问所有的资源
    + 基于对象的模型允许进行受控的增量开发和代码重用

+ 缓冲区溢出(buffer overflow)
  + 当程序将数据拷贝到一个没有为其分配足够空间的变量中去的时候，就会发生缓冲区溢出

+ 缓冲区溢出的后果
  + 要理解缓冲区溢出时会发生什么情况，就要理解程序在内存中是如何布局的
    + 大多数程序代码都在带有自动局部变量的函数中执行
    + 虽然在不同的机器上实现的细节有所不同，程序通常都在程序栈上分配自动变量
  + 在典型系统中，栈都是从高端内存向低端内存扩展的
  + 调用一个函数时
    + 栈的低端部分包括传递的参数和返回地址
    + 栈中较高的部分（内存地址比较小的部分）用来存放局部自动变量
  + 栈可以用来存储其他值，也可能包含根本不为程序所用的间隙
  + 一个很重要的事实是：
    + 每次函数调用的返回地址通常都存储在自动变量后面的内存中（存储在地址比较大的内存中）
  + 当程序向栈中变量的范围之外写入时，回复阿生缓冲区溢出。额外的字节可能会重写未使用的空间，其他变量，返回地址或该程序不能合法访问的其他内存。
  + 结果可能是没什么影响，也可能会造成程序崩溃，信息转储以及不可预测的行为

## 程序，进程和线程

+ 程序(program)
  + 指的是为了完成特定的任务而准备好的一个指令序列

+ C编译器将每个源文件翻译成一个目标文件，然后编译器将这些单个的目标文件同必须的一些库链接，形成一个可执行模块(executable module)。程序运行或执行(execute)时，操作系统将可执行模块拷贝到主存储器的程序映像(program image)中去

+ 进程(process)
  + 是一个正在执行的程序实例
  + 每个实例都有自己的地址空间和执行状态
  + 操作系统记录进程ID和相应的进程状态，并用这些信息来分配和管理系统资源。操作系统还要对进程占用的内存和可分配的内存进行管理
  + 当操作系统向内核数据结构中添加了适当的信息，并为运行程序代码分配了必要的资源之后，程序就变成了进程。
  + 程序拥有地址空间（它可以访问的内存）和至少一个被称为线程的控制流
  + 进程，以执行一个指令序列的控制流开始。处理器程序计数器记录处理器（CPU）要执行的下一条指令。CPU读取一条指令后，对程序计数器的值进行增量运算，并且在指令的执行过程中，比如，在出现分支的时候，还会对其做进一步的修改。
  + 可能有多个进程驻存在内存中并发地执行，他们基本上都互相独立。如果进程要进行通信或互相合作，它们就必须显式地通过文件系统，管道，共享内存或网络这样的操作系统结构来交互

+ 线程和执行线程(thread of execution)
  + 程序执行时，由进程程序计数器的值来决定下面该执行哪一条进程指令。得到的指令流被称为执行线程
  + 它可以用程序代码执行期间为程序计数器指定的指令地址序列来表示
  + 执行线程中的指令序列对进程来说，就像是一条不间断的地址流。但从处理器的观点来看，来自不同进程的执行线程是混在一起的。
  + 执行从一个进程切换到另一个进程的点被称作上下文切换(context switch)
  + 线程，是代表了进程内执行线程的一种抽象数据类型。线程有自己的执行栈，程序计数器值，寄存器组和状态
  + 通常在一个进程范围内声明多个进程，程序员可以编写出以很低的开销获得并行性的程序。
  + 尽管这些线程提供了低开销的并行性，但由于它们驻留在相同的进程地址空间并共享进程资源，因此，可能还需要对它们进行额外的同步。
    + 由于启动进程所需要的工作量大，有些人将进程称作是重量级(heavyweight)
    + 与之相反，线程有时被称作轻量级进程(lightweight processes)

+ 程序映像的布局
  + 加载之后，可执行程序看起来占据了一个连续的内存块，这个连续的内存块被称为程序映像(program image)
  + 程序映像有几个不同的分区。程序文本或代码显示在内存低端地址中。在映像中已经初始化和未初始化的静态变量也有自己的分区。其他的分区包括堆，栈和环境
  + 活动记录(activation record)
    + 指的是在进程栈顶端分配的一个内存块，用来装载调用过程中函数的执行上下文。
    + 每次函数调用都在栈上创建一个新的活动记录
  + 除了静态变量和自动变量之外，程序映像中还包括了`argc`和`argv`占用的空间以及`malloc`分配的空间。
  + `malloc`函数族在一个被称为堆(`heap`)的空闲内存池中分配存储空间
    + 在堆上分配的存储空间一直存在，直到它被释放或程序退出为止
    + 如果一个函数调用了`malloc`，那么在这个函数返回值后，存储空间仍保持已分配状态。
    + 除非程序有一个在函数返回值后仍然可以访问的，指向该存储空间的指针，否则，返回后的程序就不能访问它
  + 在声明时，没有显式初始化的静态变量在运行时被初始化为0
  + 在程序映像中，已初始化的静态变量和未初始化的静态变量占据不同的分区
    + 通常，已初始化的静态变量是磁盘上可执行模块的一部分，而未初始化的静态变量则不是
    + 自动变量不是可执行模块的一部分，因为只有当定义它们的程序块被调用时，它们才会被分配。除非程序显式地对自动变量进行初始化，否则，它们的初始值是不确定的
  + 对线程化的执行来说，静态变量会使程序变得不安全。
  + 连续调用一个引用了静态变量的函数会出现意料不到的情况，因此，外部静态变量也使得代码的调试更加困难。
  + 出于这些原因，除非是在受控的情况下，否则应该避免使用静态变量
  + 尽管程序映像看起来占据了一个连续的内存块，但实际上，操作系统将程序映像映射到不一定连续的物理内存块中。
  + 通常的映射将程序映像划分成相同大小的片，这些片被称为页(`page`)
    + 操作系统将这些页加载到内存中，当处理器引用某页上的内存时，操作系统会从一个表中查找这一页的物理位置。
    + 这种映射方式允许栈和堆有很大的逻辑地址空间。
    + 操作系统隐藏了这种底层映射的存在，这样即使有些页实际上并没有驻留字内存中，程序员也可以认为程序映像在逻辑上是连续的

+ 函数返回值和错误
  + 错误处理是编写可靠系统程序中的一个关键问题
  + 处理UNIX程序中错误的标准方法有如下几种
    + 打印出错误消息并退出程序（仅在main函数中）
    + 返回`-1`或`NULL`，并设置`errno`这样的错误提示符
    + 返回错误码
  + 总的来说，函数永远也不能自己退出，而是应该向调用它的程序报告错误
  + 函数内部的错误消息在调试阶段可能会很有用，但通常不应该出现在最终版本中。
  + 处理调试信息有一种很好的方法：
    + 将调试打印语句包含在一个条件编译块中，这样在需要的时候可以将其重新激活

+ 参数数组(argument array)
  + 是一个指向字符串的指针数组
  + 数组的结尾由一个包含NULL指针的条目来标识。