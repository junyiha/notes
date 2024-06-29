---
category: Books
date: 2024-05-22 09:00:00 +0800
layout: post
title: UnixNetworkProgramming02
tag: book
---
## 简介

### 1.1 概述

+ IPC，是进程间通信(interprocess communication)的简称。传统上该术语描述的是运行在某个操作系统之上的不同进程间各种消息传递(message passing)的方式

+ 在Unix操作系统过去三十年的演变史中，消息传递经历了如下几个发展阶段：
  + 管道(pipe，第四章)，是第一个广泛使用的IPC形式，既可在程序中使用，也可从shell中使用。管道的问题在于它们只能在具有共同祖先（指父子进程关系）的进程间使用，不过该问题已随有名管道(named pipe)既FIFO（第四章）的引入而解决了
  + System V消息队列(System V message queue，第六章)，是在20世纪80年代早期加到System V内核中的。它们可用在同一主机上有亲缘关系或无亲缘关系的进程之间。（谈论Unix进程时，有亲缘关系(related)的说法意味着所论及的进程具有某个共同的祖先。说的更明白点，这些有亲缘关系的进程是从该祖先进程经过一次或多次fork派生来的。我们还得注意，从理论上来说，所有Unix进程与init进程都有亲缘关系，它是系统自举时启动所有初始化进程的祖先进程。然而从实践上说，进程亲缘关系开始于一个登录shell（称为一个会话）以及由该shell派生的所有进程
  + Posix消息队列（Posix消息队列，第五章），是由Posix实时标准加入的，它们可用在同一主机上有亲缘关系和无亲缘关系的进程之间
  + 远程过程调用（Remote Procedure Call，简称RPC，第五部分），出现在20世纪80年代中期，它是从一个系统（客户主机）上某个程序调用另一个系统（服务器主机）上某个函数的一种方法，是作为显式网络编程的一种替换方法开发的。既然客户和服务器之间通常传递一些信息（被调用函数的参数与返回值），而且RPC可用在同一主机上的客户和服务器之间，因此可认为RPC是另一种形式的消息传递

+ 看一看由Unix提供的各种同步形式的演变同样颇有效益
  + 需要某种同步形式（往往是为了防止多个进程同时修改同一文件）的早期程序使用了文件系统的诡秘特性
  + 记录上锁（record locking，第九章），是在20世纪80年代早期加到Unix内核中的，然后在1988年由Posix.1标准化的
  + System V信号量（System V semaphore，第十一章），是在System V消息队列加入System V内核的同时（20世纪80年代早期）伴随System V共享内存区(System V shared memory)加入的。当今多数版本的Unix都支持它们
  + Posix信号量（Posix semaphore，第十章）和Posix共享内存区（Posix shared memory，第十三章）也由Posix实时标准加入
  + 互斥锁(mutex)和条件变量(condition variable，第七章)，是由Posix线程标准定义的两种同步形式。尽管往往用于线程间的同步，它们也能提供不同进程间的同步
  + 读写锁(read-write lock，第八章)，是另一种形式的同步。它们还没有被Posix标准化，不过也许不久后会被标准化

### 1.2 进程，线程与信息共享

+ 按照传统的Unix编程模型，我们在一个系统上运行多个进程，每个进程都有各自的地址空间
+ Unix进程间的信息共享可以有多种方式，总结：
  + 两个进程共享存留于文件系统中某个文件上的某些信息。为访问这些信息，每个进程都得穿越内核（例如read，write，lseek等）。当一个文件有待更新时，某种形式的同步是必要的，这样既可保护多个写入者，防止互相串扰，也可保护一个或多个读出者，防止写入者的干扰
  + 两个进程共享驻留于内核中的某些信息。管道是这种共享类型的一个例子，System V消息队列和System V信号量也是。现在访问共享信息的每次操作涉及对内核的一次系统调用
  + 两个进程有一个双方都能访问的共享内存区。每个进程一旦设置好该共享内存区，就能根本不涉及内核而访问其中的数据。共享该内存区的进程需要某种形式的同步
+ 需要注意的是，没有任何东西限制任何IPC技术只能使用两个进程。我们讲述的技术适用于任意数目的进程

+ 虽然Unix系统中进程的概念已使用了很久，一个给定进程内多个线程（thread）的概念却相对较新。Posix.1线程标准（称为Pthreads）是于1995年通过的。
+ 从IPC角度看来，一个给定进程内的所有线程共享同样的全局变量（也就是说共享内存区的概念对这种模型来说是内存在）。然而我们必须关注的是各个线程间对全局数据的同步访问。同步尽管不是一种明确的IPC形式，但它确实伴随许多形式的IPC使用，以控制对某些共享数据的访问

+ 本书中，我们讲述进程间的IPC和线程间的IPC。我们假设有一个线程环境，并作类似如下形式的陈述：如果管道为空，调用线程就阻塞在它的read调用上，直到某个线程往该管道写入数据。要是你的系统不支持线程，那你可以将该句子中的”线程“替换成”进程“，从而提供“阻塞在对空管道的read调用上”的经典Unix定义。
+ 然而在支持线程的系统上，只有对空管道调用read的那个线程阻塞，同一进程中的其余线程才可以继续执行。向该空管道写入数据的工作既可以由同一进程中的另一个线程去做，也可以由另一个进程中的某个线程去做

### 1.3 IPC对象的持续性

+ 我们可以把任意类型的IPC的持续性(persistence)定义成该类型的一个对象一直存在多长时间。以下有三种类型的持续性：
  + 随进程持续的(process-persistent)IPC对象，一直存在到打开着该对象的最后一个进程关闭该对象为止。例如管道和FIFO就是这种对象。
  + 随内核持续的(kernel-persistent)IPC对象，一直存在到内核重新自举或显式删除该对象为止。例如System V的消息队列，信号量和共享内存区就是此类对象。Posix的消息队列，信号量和共享内存区必须至少是随内核持续的，但也可以是随文件系统持续的，具体取决于实现
  + 随文件系统持续的(filesystem-persistent)IPC对象，一直存在到显式删除该对象为止。即使内核重新自举了，该对象还是保持其值。Posix消息队列，信号量和共享内存区如果是使用映射文件实现的（不是必需条件），那么它们就是随文件系统持续的

### 1.4 名字空间

+ 当两个或多个无亲缘关系的进程使用某种类型的IPC对象来彼此交换信息时，该IPC对象必须有一个某种形式的名字(name)或标识符(identifier)，这样其中一个进程（往往是服务器）可以创建该IPC对象，其余进程则可以指定同一个IPC对象
+ 管道没有名字（因此不能用于无亲缘关系的进程间），但是FIFO有一个在文件系统中的Unix路径名作为其标识符（因此可用于无亲缘关系的进程间）。
+ 对于一种给定的IPC类型，其可能的名字的集合称为它的名字空间(name space)。名字空间非常重要，因为对于除普通管道以外的所有形式的IPC来说，名字是客户与服务器彼此连接以交换消息的手段

### 1.4

+ 为分析各种特性，全书主要使用了三种交互模式：
  + 文件服务器：客户-服务器应用程序，客户向服务器发送一个路径名，服务器把该文件的内容返回给客户
  + 生产者-消费者：一个或多个线程或进程（生产者）把数据放到一个共享缓冲区种，另有一个或多个线程或进程（消费者）对该共享缓冲区种的数据进行操作
  + 序列号持续增1：一个或多个线程或进程给一个共享的序列号持续增1.该序列号有时在一个共享文件中，有时在共享内存区种
+ 第一个例子分析各种形式的消息传递，另外两个例子则分析各种类型的同步和共享内存区

### 1.5 小结

+ IPC传统上是Unix中一个杂乱不堪的领域，虽然有了各种各样的解决办法，但没有一个是完美的。我们的讨论分成四个主要领域：
  + 消息传递（管道，FIFO，消息队列）
  + 同步（互斥锁，条件变量，读写锁，信号量）
  + 共享内存区（匿名共享内存区，有名共享内存区）
  + 过程调用（Solaris门，Sun RPC）

## Posix IPC

### 1.1 概述

+ 以下三种类型的IPC合称为 Posix IPC
  + Posix消息队列（第五章）
  + Posix信号量（第十章）
  + Posix共享内存区（第十三章）

### 1.2 小结

+ 三种类型的Posix IPC：消息队列，信号量，共享内存区，都是用路径名标识的。但是这些路径名既可以是文件系统中的实际路径名，也可以不是，而这一点不一致性会导致一个移植性问题。全书采用的解决办法是使用我们自己的px_ipc_name函数
+ 当创建或打开一个IPC对象时，我们指定一组类似于open函数所用的标志。创建一个新的IPC对象时，我们必须给这个新对象指定访问呢权限，所用的是同样由open函数使用的S_xxx常值

## System V IPC

### 1.1 概述

+ 以下三种类型的IPC合称为System V IPC
  + System V消息队列（第六章）
  + System V信号量（第十一章）
  + System V共享内存区（第十四章）
+ 这个称谓作为这三种IPC机制的通常是因为它们源自System V Unix

## 管道和FIFO

### 1.1 概述

+ 管道是最初的Unix IPC形式，可追溯到1973的Unix第三版。
+ 尽管对于许多操作来说很有用，但它们的根据局限在于没有名字，从而只能由有亲缘关系的进程使用。这一点随FIFO的加入在System III Unix（1982年）中得以改正。FIFO有时称为有名管道(named pipe)。管道和FIFO都是使用通常的read和write函数访问的
+ 技术上讲，自从可以在进程间传递描述符后，管道也能用于无亲缘关系的进程间。然而现实中，管道通常用于具有共同祖先的进程间

### 1.2 管道

+ 所有式样的Unix都提供管道。它由pipe函数创建，提供一个单路（单向）数据流
+ 声明：
  + `#include <unistd.h>`
  + `int pipe(int fd[2]);`
+ 该函数返回两个文件描述符：fd[0]和fd[1]。前者打开来读，后者打开来写
+ 有些版本的Unix提供全双工管道，也就是说这些管道的两端都是即可用于读，也可用于写。创建一个全双工IPC管道的另一种方法是使用UNPV1的14.3节中讲述的socketpair函数，它在大多数现行Unix系统上都能工作。然而管道的最常见用途是用在各种shell中，这种情况下半双工管道足够了

+ 尽管管道是由单个进程创建的，它却很少在单个进程内使用。管道的典型用途是以下述方式为两个不同进程（一个是父进程，一个是子进程）提供进程间的通信手段。
  + 首先，由一个进程（它将成为父进程）创建一个管道后调用fork派生一个自身的副本
  + 接着，父进程关闭这个管道的读出端，子进程关闭同一管道的写入端。这就在父子进程间提供了一个单向数据流
+ 我们在某个Unix shell中输入一个像如下这样的命令时：`who | sort|lp`，该shell将执行上述步骤创建三个进程和其间的两个管道。它还把每个管道的读出端复制到相应进程的标准输入，把每个管道的写入端复制到相应进程的标准输出

+ 到此为止所示的所有管道都是半双工的即单向的，只提供一个方向的数据流。当需要一个双向数据流时，我们必须创建两个管道，每个方向一个。实际步骤如下：
  + 创建管道1(fd1[0]和fd1[1])和管道2(fd2[0]和fd2[1])
  + fork
  + 父进程关闭管道1的读出端(fd1[0])
  + 父进程关闭管道2的写入端(fd2[1])
  + 父进程关闭管道1的写入端(fd1[1])
  + 父进程关闭管道2的读出端(fd2[0])

### 1.3 FIFO

+ FIFO，指代先进先出(first in, first out)，Unix中的FIFO类似于管道。它是一个单项（半双工）数据流。不同于管道的是，每个FIFO有一个路径名与之关联，从而允许无亲缘关系的进程访问同一个FIFO。FIFO也称为有名管道(named pipe)
+ FIFO由mkfifo函数创建
+ 声明：
  + `#include <sys/types.h>`
  + `#include <sys/stat.h>`
  + `int mkfifo(const char *pathname, mode_t mode);`
+ 其中pathname，是一个普通的Unix路径名，它是该FIFO的名字
+ mode参数，指定文件权限位，类似于open的第二个参数
+ mkfifo函数，已隐含指定O_CREAT | O_EXCL。也就是说，它要么创建一个新的FIFO，要么返回一个EEXIST错误（如果所指定名字的FIFO已经存在）
+ 在创建出一个FIFO后，它必须或者打开来读，或者打开来写。所用的可以是open函数，也可以是某个标准I/O打开函数
+ 对管道或FIFO的write总是往末尾添加数据，对他们的read则总是从开头返回数据。如果对管道或FIFO调用lseek，那就返回ESPIPE错误

### 1.4 管道和FIFO的额外属性

+ 我们需要就管道和FIFO的打开，读出和写入更为详细地描述它们的某些属性。
+ 首先，一个描述符能以两种方式设置成非阻塞
  + 调用open时可指定O_NONBLOCK标志
  + 如果一个描述符已经打开，那么可以调用fcntl以启用O_NONBLOCK标志。对于管道来说，必须使用这种技术，因为管道没有open调用，在pipe调用中也无法指定O_NONBLOCK标志。使用fcntl时，我们先使用F_GETFL命令获取当前文件状态标志，将它与O_NONBLOCK标志按位或后，再使用F_SETFL命令存储这些文件状态标志

+ 关于管道或FIFO的读出与写入的若干额外规则：
  + 如果请求读出的数据量多余管道或FIFO中当前可用数据量，那么只返回这些可用的数据。我们必须准备好处理来自read的小于所请求数目的返回值
  + 如果请求写入的数据的字节数小于或等于PIPE_BUF（一个Posix限制值），那么write操作保证是原子的。这意味着，如果有两个进程差不多同时往同一个管道或FIFO写，那么或者先写入来自第一个进程的所有数据，再写入来自第二个进程的所有数据，或者颠倒过来。系统不会互相混杂来自这两个进程的数据。然而，如果请求写入的数据的字节数大于PIPE_BUF，那么write操作不能保证是原子的。（Posix.1要求PIPE_BUF至少为512字节）
  + O_NONBLOCK标志的设置对write操作的原子性没有影响--原子性完全由所请求字节数是否小于等于PIPE_BUF决定的。然而当一个管道或FIFO设置成非阻塞时，来自write的返回值取决于待写的字节数以及该管道或FIFO中当前可用空间的大小。
    + 如果待写的字节数小于等于PIPE_BUF：
      + 如果该管道或FIFO中有足以存放所请求字节数的空间，那么所有数据字节都写入
      + 如果该管道或FIFO中没有足以存放所请求字节数的空间，那么立即返回一个EAGAIN错误。既然设置了O_NONBLOCK标志，调用进程就不希望自己被投入睡眠中。但是内核无法在接受部分数据的同时仍保证write操作的原子性，于是它必须返回一个错误告诉调用进程以后再试
    + 如果待写的字节数大于PIPE_BUF;
      + 如果该管道或FIFO中至少有1字节空间，那么内核写入该管道或FIFO能容纳数目的数据字节，概述同时作为来自write的返回值
      + 如果该管道或FIFO已满，那么立即返回一个EAGAIN错误
  + 如果向一个没有为读打开着的管道或FIFO写入，那么内核将产生一个SIGPIPE信号：
    + 如果调用进程既没有捕获也没有忽略该SIGPIPE信号，所采取的默认行为就是终止该进程
    + 如果调用进程忽略了该SIGPIPE信号，或者捕获了该信号并从其信号处理程序中返回，那么write返回一个EPIPE错误

### 1.5 字节流与消息

+ 到此为止所给出的使用管道和FIFO的例子都使用字节流I/O模型，这是Unix的原生I/O模型。这种模型不存在记录边界，也就是说读写操作根本不检查数据。
+ 举例来说，从某个FIFO中读出100个字节的进程无法判定往该FIFO中写入这100个字节的进程执行了单个100字节的写操作，5个20字节的写操作，2个50字节的写操作还是另外某种总共为100字节的写操作的组合。一个进程往该FIFO中写入55个字节后，另一个进程再写入45字节，这样的情况同样是可能的。
+ 这样的数据是一个字节流(byte stream)，系统不对它作解释。如果需要某种解释，写进程和读进程就得先验地同意这种解释，并亲自去做。（由原因推结果）

+ 有时候应用希望对所传送的数据加上某种结构。当数据由长度可变消息构成，并且读出者必须知道这些消息的边界以判定何时已读出单个消息时，这种需求可能发生。下面三种技巧经常用于这个目的：
  + 带内特殊终止序列：许多Unix应用程序使用换行符来分隔消息。写进程会给每个消息添加一个换行符，读进程则每次读出一行。这种技巧一般要求数据中任何出现分隔符处都作转义处理（也就是说以某种方式把它们标志成数据，而不是作为分隔符）。许多因特网应用程序（FTP, SMTP, HTTP, NNTP）使用由一个回车符后跟一个换行符构成双字符序列（CT/LF）来分隔文本记录
  + 显式长度：每个记录前冠以它的长度。我们将马上使用这种技巧。当用在TCP上时，Sun RPC也使用这种技巧。这种技巧的优势之一是不再需要通过转义出现在数据中的分隔符，因为接收者不必扫描整个数据以寻找每个记录的结束位置
  + 每次连接一个记录：应用通过关闭与其对端的连接（网络应用时为TCP连接，IPC应用时为IPC连接）来指示一个记录的结束，。这要求为每个记录创建一个新连接，HTTP1.0就使用这一技术

+ 也可以更见更为结构化的消息，这种能力是由Posix消息队列和System V消息队列提供的。我们将看到每个消息有一个长度和一个优先级（System V成后者为类型）。长度和优先级是由发送者指定的，消息被读出后，这两者都返回给读出者。每个消息是一个记录(record)，类似于UDP数据报

### 1.6 管道和FIFO限制

+ 系统加于管道和FIFO的唯一限制为：
  + OPEN_MAX  一个进程在任意时刻打开的最大描述符（Posix要求至少为16）
  + PIPE_BUF  可原子地写往一个管道或FIFO的最大数据量（Posix要求至少为512）
+ 我们马上会看到OPEN_MAX的值可通过调用sysconf函数查询。它通常可通过执行ulimit命令或limit命令从shell中修改，它也可以通过调用setrlimit函数从一个进程中修改
+ PIPE_BUF的值通常定义在`<limits.h>`头文件中，但是Posix认为它是一个路径名变量(pathname variable)。这意味着它的值可以随所指定的路径名而变化（只对FIFO而言，因为管道没有名字），因为不同的路径名可以落在不同的文件系统上，而这些文件系统可能有不同的特征。于是PIPE_BUF的值可在运行时通过调用pathconf或fpathconf取得

### 1.7 小结

+ 管道和FIFO，是许多应用程序的基本构建模块。管道普遍用于shell中，不过也可以从程序中使用，往往是用于从子进程向父进程回传消息。使用管道时涉及的某些代码(pipe, fork, close, exec, waitpid)可通过使用popen和pclose来避免，由它们处理具体细节并激活一个shell
+ FIFO与管道类似，但是它们使用mkfifo创建的，之后需要open打开。打开管道时必须小心，因为有许多规则制约着open的阻塞与否
+ 管道和FIFO的特征之一，是它们的数据是一个字节流，类似于TCP连接。把这种字节流分隔成各个记录的任何方法都得由应用程序来实现

## Posix消息队列 

### 1.1 概述

+ 消息队列可认为是一个消息链表。有足够写权限的线程可往队列中放置消息，有足够读权限的线程可从队列中取走消息。每个消息都是一个记录，它由发送者赋予一个优先级。在某个进程往一个队列写入消息之前，并不需要另外某个进程在该队列上等待消息的到达。这跟管道和FIFO是相反的，对于后者来说，除非读出者已存在，否则先有写入者是没有意义的。
+ 一个进程可以往某个队列写入一些消息，然后终止，再让另外一个进程在以后某个时刻读出这些消息。我们说过消息队列具有随内核的持续性，这跟管道和FIFO不一样。我们在第四章中说过，当一个管道或FIFO的最后一次关闭发生时，仍在该管道或FIFO上的数据将被丢弃

### 1.2 mq_open, mq_close, mq_unlink函数

+ mq_open函数，创建一个新的消息队列或打开一个已存在的消息队列
+ 声明：
  + `#include <mqueue.h>`
  + `mqd_t mq_open(const char *name, int oflag, ... /* mode_t mode, struct mq_attr *attr*/);`
+ 在2.2节描述过有关name参数的规则
+ oflag参数，是O_RDONLY, O_WRONLY, O_RDWR之一，可能按位或上O_CREAT, O_EXCL, O_NONBLOCK
+ 当实际操作是创建一个新队列时（已指定O_CREAT标志，且所请求的消息队列尚未存在），mode和attr参数是需要的。attr参数，用于给新队列指定某些属性。如果它为空指针，那就使用默认属性
+ mq_open的返回值，称为消息队列描述符(message queue descriptor)，但它不必是（而且很可能不是）像文件描述符或套接字描述符这样的短整数。这个值用作其余7个消息队列函数的第一个参数

+ 已打开的消息队列是由mq_close关闭的
+ 声明：
  + `#include <mqueue.h>`
  + `int mq_close (mqd_t mqdes);`
+ 其功能与关闭一个已打开的close函数类似：调用进程可以不再使用该描述符，但其消息队列并不从系统中删除。一个进程终止时，它的所有打开着的消息队列都关闭，就像调用了mq_close一样

+ 要从系统中删除用作mq_open的第一个参数的某个name，必须调用mq_unlink
+ 声明：
  + `#include <mqueue.h>`
  + `int mq_unlink(const char *name);`
+ 每个消息队列有一个保存其当前打开着描述符数的引用计数器（就像文件一样），因而本函数能够实现类似于unlink函数删除一个文件的机制：当一个消息队列的引用计数仍大于0时，其name就能删除，但是该队列的析构（这与从系统中删除其名字不同）要到最后一个mq_close发生时才进行
+ Posix消息队列至少具备随内核的持续性。这就是说，即使当前没有进程打开着某个消息队列，该队列及其上的各个消息也将一直存在，直到调用mq_unlink并让它的引用计数达到0以删除该队列为止

### 1.3 mq_getattr和mq_setattr函数

+ 每个消息队列有四个属性，mq_getattr返回所有这些属性，mq_setattr则设置其中某个属性
+ 声明：
  + `#include <mqueue.h>`
  + `int mq_getattr (mqd_t mqdes, struct mq_attr *attr);`
  + `int mq_setattr (mqd_t mqdes, const struct mq_attr *attr, struct mq_attr *oattr);`
+ mq_attr结构含有以下属性：
   ```
    struct mq_attr {
        long mq_flags;    /* message queue flag: 0, O_NONBLOCK */
        long mq_maxmsg;   /* max number of messages allowed on queue */
        long mq_msgsize;  /* max size of a message (in bytes) */
        long mq_curmsgs;  /* number of messages currently on queue */
    };
   ```
+ mg_getattr把所指定队列的当前属性填入由attr指向的结构
+ mg_setattr给所指定队列设置属性，但是只使用由attr指向的mq_attr结构的mq_flags成员，以设置或清除非阻塞标志。该结构的另外三个成员被忽略：
  + 每个队列的最大消息数和每个消息的最大字节数只能在创建队列时设置
  + 队列中的当前消息数则只能获取而不能设置

### 1.4 mq_send和mq_receive函数

+ 这两个函数分别用于往一个队列中放置一个消息和从一个队列中取走一个消息。每个消息有一个优先级，它是一个小于MQ_PRIO_MAX的无符号整数。Posix要求这个上限至少为32
+ 声明：
  + `#include <mqueue.h>`
  + `int mq_send(mqd_t mqdes, const char *ptr, size_t len, unsigned int prio);`
  + `ssize_t mq_receive(mqd_t mqdes, char *ptr, size_t len, unsigned int *priop);`
+ mq_receive总是返回所指定队列中最高优先级的最早消息，而且该优先级能随该消息的内容及其长度一同返回
+ 这两个函数的前三个参数分别与write和read的前三个参数类似
+ mq_receive的len参数的值不能小于能加到所指定队列中的消息的最大大小（该队列mq_attr结构的mq_msgsize成员）。要是len小于该值，mq_receive就立即返回EMSGSIZE错误。
  + 这意味着使用Posix消息队列的大多数应用程序必须在打开某个队列后调用mq_getattr确定最大消息大小，然后分配一个或多个那样大小的读缓冲区。通过要求每个缓冲区总是足以存放队列中的任意消息，mq_receive就不必返回消息是否大于缓冲区的通知
+ mq_send的prio参数是待发送消息的优先级，其值必须小于MQ_PRIO_MAX。如果mq_receive的priop参数是一个非空指针，所返回消息的优先级就通过该指针存放。如果应用不必使用优先级不同的消息，那就给mq_send指定值为0的优先级，给mq_receive指定一个空指针作为其最后参数
+ 待发送消息的大小和优先级必须作为命令行参数指定。所用缓冲区使用calloc分配，该函数会把该缓冲区初始化为0

### 1.5 消息队列限制

+ 我们已遇到任意给定队列的两个限制，它们都是在创建该队列时建立的
  + mq_maxmsg  队列中的最大消息数
  + mq_msgsize 给定消息的最大字节数

+ 消息队列的实现定义了另外两个限制：
  + MQ_OPEN_MAX    一个进程能够同时拥有的打开着消息队列的最大数目（Posix要求它至少为8）
  + MQ_PRIO_MAX    任意消息的最大优先级值加1（Posix要求它至少为32）
+ 这两个常值往往定义在`<unistd.h>`头文件中，也可以在运行时通过调用sysconf函数获取

### 1.6 mq_notify函数

+ 第六章中讨论的System V消息队列的问题之一，是无法通知一个进程何时在某个队列中放置了一个消息。
+ 我们可以阻塞在msgrcv调用中，但那将阻止我们在等待期间做其他任何事。如果给msgrcv指定非阻塞标志（IPC_NOWAIT），那么尽管不阻塞了，但必须持续调用该函数以确定何时有一个消息到达。我们说过着称为轮询(polling)，是对CPU时间的一种浪费。我们需要一种方法，让系统告诉我们何时有一个消息放置到了先前为空的某个队列中

+ Posix消息队列允许异步事件通知(asynchronous event notification)，以告知何时有一个消息放置到了某个空消息队列中。这种通知有两种方式可供选择：
  + 产生一个信号
  + 创建一个线程来执行一个指定的函数
+ 这种通知通过调用mq_notify建立
+ 声明：
  + `#include <mqueue.h>`
  + `int mq_notify (mqd_t mqdes, const struct sigevent *notification);`
+ 该函数为指定队列建立或删除异步事件通知。sigevent结构是随Posix.1实时信号新加的。该结构以及本章中引入的所有新的信号相关的常值都定义在`<signal.h>`头文件中
+ 一些普遍适用于该函数的若干规则
  + 如果notification参数非空，那么当前进程希望在有一个消息到达所指定的先前为空的队列时得到通知。我们说：该进程被注册为接收该队列的通知
  + 如果notification参数为空指针，而且当前进程目前被注册为接收所指定队列的通知，那么已存在的注册将被撤销
  + 任意时刻只有一个进程可以被注册为接收某个给定队列的通知
  + 当有一个消息到达某个先前为空的队列，而且已有一个进程被注册为接收该队列的通知时，只有在没有任何线程阻塞在该队列的mq_receive调用中的前提下，通知才会阿初。这就是说，在mq_receive调用中的阻塞比任何通知的注册都优先
  + 当该通知被发送给它的注册进程时，其注册即被撤销。该进程必须再次调用mq_notify以重新注册（如果想要的话）

+ 更为简易（并且可能更为高效）的办法之一，是阻塞在某个函数中，仅仅等待该信号的递交，而不是让内核执行一个只为设置一个标志的信号处理程序。sigwait提供了这种能力
+ 声明：
  + `#include <signal.h>`
  + `int sigwait (const sigset_t *set, int *sig);`
+ 调用sigwait前，我们阻塞某个信号集。我们将这个信号集指定为set参数。sigwait然后一直阻塞到这些信号中有一个或多个待处理，这时它返回其中一个信号。该信号值通过指针sig存放，函数的返回值则为0.这个过程称为：同步地等待一个异步事件。我们是在使用信号，但没有涉及异步信号处理程序

### 1.7 实时信号

+ 在过去几十年中，Unix信号经历了多次重大的演变。信号可划分为两个大组
  + 其值在SIGRTMIN和SIGRTMAX之间（包括两者在内）的实时信号。Posix要求至少提供PTSIG_MAX这种实时信号，而该常值的最小值为8
  + 所有其他信号：SIGALRM, SIGINT, SIGKILL，等等

### 1.8 小结

+ Posix消息队列比较简单：
  + mq_open创建一个新队列或打开一个已存在的队列
  + mq_close关闭队列
  + mq_unlink则删除队列名。
  + 往一个队列中放置消息使用mq_send，从一个队列中读出消息使用mq_receive。
  + 队列属性的查询与设置使用mq_getattr和mq_setattr，
  + 函数mq_notify则允许我们注册一个信号或线程，它们在有一个消息被放置到某个空队列上时发送（信号）或激活（线程）。队列中的每个消息被赋予一个小整数优先级，mq_receive每次被调用时总是返回最高优先级的最早消息

+ rnq_notify的使用给我们引入了Posix实时信号，它们在SIGRTMIN和SIGRTMAX之间。当设置SA_SIGINFO标志来安装这些信号的处理程序时
  + 这些信号是排队的
  + 排了队的信号是以FIFO顺序递交的
  + 给信号处理程序传递两个额外的参数

+ 最后，使用内存映射I/O以及一个Posix互斥锁和一个Posix条件变量，以约500行C代码实现了Posix消息队列的大多数特性。该实现展示了处理新队列的创建中存在的一个竞争状态

## 互斥锁和条件变量

### 1.1 概述

+ 从本章开始关于同步的讨论：怎样同步多个线程或多个进程的活动。为允许在线程或进程间共享数据，同步通常是必需的。互斥锁和条件变量是同步的基本组成部分
+ 互斥锁和条件变量出自Posix.1线程标准，它们总是可用来同步一个进程内的各个线程的。如果一个互斥锁或条件变量存放多个进程间共享的某个内存区中，那么Posix还允许它用于这些进程间的同步

### 1.2 互斥锁：上锁与解锁

+ 互斥锁指代互相排斥(mutual exclusion)，它是最基本的同步形式。互斥锁用于保护临界区(critical region)，以保证任何时刻只有一个线程在执行其中的代码（假设互斥锁由多个线程共享），或者任何时刻只有一个进程在执行其中的代码（假设互斥锁由多个进程共享）

### 1.3 对比上锁与等待

+ 现在展示互斥锁用于上锁(locking)而不能用于等待(waiting)

### 1.4 条件变量：等待与信号发送

+ 互斥锁用于上锁，条件变量则用于等待。这两种不同类型的同步都是需要的
+ 条件变量是类型为pthread_cond_t的变量，以下两个函数使用了这些变量：
  + `#include <pthread.h>`
  + `int pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);`
  + `int pthread_cond_singal(pthread_cond_t *cptr);`
+ 这两个函数所等待或由之得以通知的条件，其定义由我们选择：我们在代码中测试这种条件

### 1.5 小结

+ 互斥锁用于保护代码临界区，从而保证任何时刻只有一个线程在临界区内执行。有时候一个线程获得某个互斥锁后，发现自己需要等待某个条件变为真。如果是这样，该线程就可以等待在某个条件变量上。条件变量总是有一个互斥锁与之关联。把调用线程投入睡眠的pthread_cond_wait函数在这么做之前先给所关联的互斥锁解锁，以后某个时刻唤醒该线程前再给该互斥锁上锁。该条件变量由另外某个线程向它发送信号，而这个发送信号的线程即可以只唤醒一个线程(pthread_cond_signal)，也可以唤醒等待相应条件变为真的所有线程(pthread_cond_broadcast)

+ 互斥锁和条件变量可以静态分配并静态初始化。它们也可以动态分配，那要求动态地初始化它们。动态初始化允许我们指定进程间共享属性，从而允许在不同进程间共享某个互斥锁或条件变量，其前提是该互斥锁或条件变量必须存放在由这些进程共享的内存区中

## 读写锁

## 记录上锁

### 1.1 小结

+ fcntl记录上锁提供了对一个文件的劝告性或强制性上锁功能，而我们是通过该文件打开着的描述符来访问它的。这些锁用于不同进程间的上锁，而不是同一进程内不同线程间的上锁。
+ 术语“记录”是个不确切的名字，因为Unix内核没有文件内记录的概念。更好的称谓是“范围上锁(range locking)”，因为我们上锁或解锁的是文件内的一个字节范围。这类记录上锁几乎都用作写作进程之间的劝告性锁，因为即使强制性上锁也会导致不一致数据

## Posix信号量

### 1.1 概述

+ 信号量(semaphore)，是一种用于提供不同进程间或一个给定进程的不同线程间同步手段的原语。本书讨论三种类型的信号量：
  + Posix有名信号量：使用Posix IPC名字标识，可用于进程或线程间的同步
  + Posix基于内存的信号量：存放在共享内存区中，可用于进程或线程间的同步
  + System V信号量：在内核中维护，可用于进程或线程间的同步

### 1.2 小结

+ Posix信号量是计数信号量，它提供以下三种基本操作：
  + 创建一个信号量；
  + 等待一个信号量的值变为大于0，然后将它的值减一；
  + 给一个信号量的值加1，并唤醒等待该信号量的任意线程，以此挂出该信号量
+ Posix信号量可以是有名的，也可以是基于内存的。有名信号量总是能够在不同进程间共享，基于内存的信号量则必须在创建时指定成是否在进程间共享。这两类信号量的持续性也有差别，有名信号量至少有随内核的持续性，基于内存的信号量则具有随进程的持续性

## System V信号量

## 共享内存区介绍

### 1.1 概述

+ 共享内存区是可用IPC形式中最快的。一旦这样的内存区映射到共享它的进程的地址空间，这些进程间数据的传递就不再涉及内核。然而往该共享内存区存放消息或从中取走消息的进程间通常需要某种形式的同步。我们在第三部分讨论了各种形式的同步：互斥锁，条件变量，读写锁，记录锁，信号量
+ 这里说的“不再涉及内核”的含义是：进程不再通过执行任何进入内核的系统调用来彼此传递数据。显然，内核必须建立允许各个进程共享该内存区的内存映射关系，然后一直管理该内存区

+ 考虑用来传递各种类型消息的一个实例客户-服务器文件复制程序中涉及的通常步骤：
  + 服务器从输入文件读。该文件的数据由内核读入自己的内存空间，然后从内核复制到服务器进程
  + 服务器往一个管道，FIFO或消息队列以一条消息的形式写入这些数据。这些IPC形式通常需要把这些数据从进程复制到内核
  + 客户从该IPC通道读出这些数据，这通常需要把这些数据从内核复制到进程
  + 最后，将这些数据从由write函数的第二个参数指定的客户缓冲区复制到输出文件
+ 这里通常需要总共四次数据复制。而且这四次复制是在内核和某个进程间进行的，往往开销很大。
+ 这些IPC形式（管道，FIFO和消息队列）的问题在于，两个进程要交换信息时，这些信息必须经由内核传递

+ 通过让两个或多个进程共享一个内存区，共享内存区这种IPC形式提供了绕过上述问题的办法。当然，这些进程必须协调或同步对该共享内存区的使用。第三部分讲述的任何技巧都可用于这样的同步目的。前面的客户-服务器例子现在涉及的步骤如下：
  + 服务器使用（例如）一个信号量取得访问某个共享内存区对象的权力
  + 服务器将数据从输入文件读入到该共享内存区对象。read函数的第二个参数所指定的数据缓冲区地址指向这个共享内存区对象
  + 服务器读入完毕时，使用一个信号量通知客户
  + 客户将这些数据从该共享内存区对象写出到输入文件中

### 1.2 mmap， munmap和msync函数

+ mmap函数，把一个文件或一个Posix共享内存区对象映射到调用进程的地址空间。使用该函数有三个目的：
  + 使用普通文件以提供内存映射I/O
  + 使用特殊文件以提供匿名内存映射
  + 使用shm_open以提供无亲缘关系进程间的Posix共享内存区
+ 声明：
  + `#include <sys/mman.h>`
  + `void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);`
+ 其中addr可以指定描述符fd应被映射到的进程内空间的起始地址。它通常被指定为一个空指针，这样告诉内核自己去选择起始地址。无论哪种情况下，该函数的返回值都是描述符fd所映射到内存区的起始地址
+ len是映射到调用进程地址空间中的字节数，它从被映射文件开头起第offset个字节处开始算。offset通常设置为0
+ 内存映射区的保护由prot参数指定。该参数的常见值是代表读写访问的PROT_READ | PROT_WRITE
  + PROT_READ  数据可读
  + PROT_WRITE 数据可写
  + PROT_EXEC  数据可执行
  + PROT_NONE 数据不可访问
+ flags使用常值指定。MAP_SHARED或MAP_PRIVATE这两个标志必须指定一个，并可有选择地或上MAP_FIXED
  + 如果指定了MAP_PRIVATE，那么调用进程对被映射数据所作的修改只对该进程可见，而不改变其底层支撑对象（或者是一个文件对象，或者是一个共享内存区对象）
  + 如果指定了MAP_SHARED，那么调用进程对被映射数据所作的修改对于共享该对象的所有基础南横都可见，而且确实改变了其底层支撑对象

+ 为从某个进程的地址空间删除一个映射关系，我们调用munmap
+ 声明：
  + `#include <sys/mman.h>`
  + `int munmap(void *addr, size_t len);`
+ 其中addr参数是由mmap返回的地址，len是映射区的大小

+ 如果我们修改了处于内存映射到某个文件的内存区中某个位置的内容，那么内核将在稍后某个时刻相应地更新文件。然而有时候我们希望确信硬盘上的文件内容与内存映射去中的内容一致，于是调用msync来执行这种同步
+ 声明：
  + `#include <sys/mman.h>`
  + `int msync (void *addr, size_t len, int flags);`
+ 其中addr和len参数通常指代内存中的整个内存映射区，不过也可以指定该内存区的一个子集
+ flags参数是常值的组合
  + MS_ASYNC    执行异步写
  + MS_SYNC     执行同步写
  + MS_INVALIDATE 使高速缓存的数据失效
  + MS_ASYNC和MS_SYNC这两个常值中必须指定一个，但不能都指定。它们的差别使，一旦写操作已由内核排入队列，MS_ASYNC即返回，而MS_SYNC则要等到写操作完成后才返回。如果还指定了MS_INVALIDATE，那么与其最终副本不一致的文件数据的所用内存中副本都失效，后续的引用将从文件中读取数据

+ 我们如此详尽地讨论mmap的理由有两个：
  + 一是文件的内存映射是一种很有用的技巧
  + 二是Posix共享内存区也使用mmap
+ Posix还定义了处理内存管理的四个额外函数：
  + mlockall函数会使调用进程的整个内存空间常驻内存。munlockall则撤销这种锁定
  + mlock会使调用进程地址空间的某个指定范围常驻内存，该函数的参数指定了这个范围的起始地址以及从该地址算起的字节数。munlock则撤销某个指定内存区的锁定

## Posix共享内存区

### 1.1 概述

+ Posix.1提供了两种在无亲缘关系进程间共享内存区的方法：
  + 内存映射文件(memory-mapped file)：由open函数打开，由mmap函数把得到的描述符映射到当前进程地址空间中的一个文件
  + 共享内存区对象(shared-memory object)：由shm_open打开一个Posix.1 IPC名字（也许是在文件系统中的一个路径名），所返回的描述符由mmap函数映射到当前进程的地址空间
+ 这两种技术都需要调用mmap，差别在于作为mmap的参数之一的描述符的获取手段：通过open或通过shm_open。Posix把两者合称为内存区对象(memory object)

## System V 共享内存区

## 门

### 1.1 概述

+ 当讨论客户-服务器情形和过程调用时，存在着三种不同类型的过程调用：
  + 本地过程调用(local procedure call)。被调用的过程（函数）与调用过程处于同一个进程中。典型的情况是，调用者通过执行某条机器指令把控制传给新进程，被调用过程保存机器寄存器的值，并在栈顶分配存放其本地变量的空间
  + 远程过程调用(remote procedure call, 简称RPC)：被调用过程和调用过程处于不同的进程中。我们通常称调用者为客户，称被调用者的过程为服务器。门(door)所提供的能力：一个进程调用同一台主机上另一个进程中的某个过程(函数)。通过给本进程内的某个过程创建一个门，一个进程（服务器）就使得该过程能为其他进程（客户）所调用
  + RPC通常允许一台主机上的某个客户调用另一台主机上的某个服务器过程。只要这两台主机以某种形式的网络连接着

+ 本地过程调用是同步的：调用者直到被调用过程返回后才重新获得控制。
+ 线程可认为是提供了某种形式的异步过程调用：有一个函数被调用(pthread_create的第三个参数)，该函数和调用者看起来在同步执行。调用者可通过调用pthread_join等待这个新线程的完成。
+ 远程过程调用可能是同步的，也可能是异步的，不过我们将看到门调用是同步的

+ 在进程（客户或服务器）内部，门是用描述符标识的。在进程以外，门可能是用文件系统中路径名标识的。
+ 一个服务器通过调用`door_create()`创建一个门，传递给该函数的参数是将与该门关联的过程的一个指针，该函数的返回值是新创建的门的一个描述符。
+ 该服务器然后通过调用`fattach`给这个门描述符关联一个路径名。一个客户通过调用open来打开一个门，传递给该函数的参数是该门的服务器关联在其上的路径名，该函数的返回值是本客户访问该门的描述符。该客户然后通过调用door_call调用服务器过程。自然，某个门的服务器可以是另一个门的客户

### 1.2 door_create函数

+ 服务器进程通过调用door_create建立一个服务器过程
+ 声明：
  + `#include <door.h>`
  + `typedef void Door_server_proc(void *cookie, char *dataptr, size_t datasize, door_desc_t *descptr, size_t ndesc);`
  + `int door_create(DOor_server_proc *proc, void *cookie, u_int attr);`
+ 在上述的声明中，我们加上了自己的typedef，这样简化了服务器过程的函数原型。这个typedef语句说，们服务器过程是以五个参数调用的，不返回任何值

### 1.3 door_return函数

+ 服务器过程完成工作时通过调用door_return返回。这会使客户中相关联的door_call调用返回
+ 声明
  + `#include <door.h>`
  + `int door_return(char *dataptr, size_t datasize, door_desc_t *descptr, size_t *ndesc);`
+ 数据结果由dataptr和datasize指定，描述符结果由descptr和ndesc指定

### 1.4 door_cred函数

+ 门有一个很不错的特性：服务器过程能够获取每个调用对应的客户凭证。这是由door_cred函数完成的。
+ 声明：
  + `#include <door.h>`
  + `int door_cred(door_cred_t *cred);`
+ 其中由cread指向的door_cred_t结构将在返回时填入客户的凭证

### 1.5 door_info函数

+ 我们刚才描述的door_cred函数给服务器提供关于客户的信息。客户也可通过调用door_info函数找出有关服务器的信息
+ 声明
  + `#include <door.h>`
  + `int door_info(int fd, door_info_t *info);`
+ 其中fd指定一个已打开的门。由info指向的door_info_t结构将在返回时填入关于服务器的信息

### 1.6 小结

+ 门提供了调用同一台主机上另一个进程中某个过程的能力。下一章中我们将对这种远程过程调用概念加以扩展，讲述如何调用另一台主机上另一个过程中的某个进程
+ 基本的API函数比较简单。服务器调用door_create创建一个门，并给他关联一个服务器过程，然后调用fattach给该门附接一个文件系统中的路径名。客户对该路径名调用open，然后调用door_call以调用服务器进程中的服务器进程。该服务器过程通过调用door_return返回
+ 门允许从客户向服务器以及从服务器向客户传递描述符。这是一个非常有用的技巧，因为Unix中描述符代表着许多访问手段：
  + 访问文件以进行文件或设备I/O
  + 访问套接字或XTI以进行网络通信
  + 访问门以进行远程过程调用

## Sun RPC

### 1.1 概述

+ 构筑一个应用程序时，我们首先在以下两者之间做出选择：
  + 构建一个庞大的单一程序，完成全部工作
  + 把整个应用程序散步在彼此通信的多个进程中
+ 如果我们选择后者，接下去的抉择是：
  + 假设所有进程运行在同一台主机上（允许IPC用于这些进程间的通信）；
  + 假设某些进程会运行在其他主机上（要求使用进程间某种形式的网络通信）

+ 本书的大部分关注的是：使用消息传递，共享内存区，并可能使用某种形式的同步来进行同一台主机上的进程间IPC。同一进程内不同线程间的IPC以及不同进程内各个线程间的IPC只是这种情况的特殊情况
+ 不同部分之间需要网络通信的应用程序大多数是使用显示网络编程(explicit network programming)方式编写的，也就是直接调用套接字API或XTI API。使用套接字API时，客户调用socket，connect，read和write；服务器则调用socket，bind，listen，accept，read和write。我们熟悉的大多数应用程序（Web浏览器，web服务器，Telnet客户，Telnet服务器等程序）就是以这种方式编写的。
+ 编写分布式应用程序的另一种方式是使用隐式网络编程(implicit network programming)。远程过程调用（RPC）提供了这样的一个工具

### 1.2 小结

+ Sun RPC允许我们编写分布式应用程序，让客户运行在一台主机上，服务器运行在另一台主机上。

## 后记

### 1.1 

+ 本书详细讲述了用于进程间通信(IPC)的四种不同技术：
  + 消息传递（管道，FIFO，Posix和System V消息队列）
  + 同步（互斥锁，条件变量，读写锁，文件和记录锁，Posix和System V信号量）
  + 共享内存区（匿名共享内存区，有名Posix共享内存区，有名System V共享内存区）
  + 过程调用（Solaris门，Sun RPC）

+ 消息队列和过程调用往往单独使用，也就是说它们通过提供了自己的同步机制。相反，共享内存区通常需要某种由应用程序提供的同步形式才能正确工作。同步技术有使用单独使用，也就是说不涉及其他形式的IPC

+ 讨论了共十六章的细节后，很显然的一个问题是：解决某个待定问题应使用哪种形式的IPC？
+ 遗憾的是不存在关于IPC的简单判定。Unix提供的类型如此之多的IPC表明，不存在解决全部（或者甚至于大部分）问题的单一方法。
+ 你能做的仅仅是：逐渐熟悉各种IPC形式提供的机制，然后根据特定应用的要求比较它们的特性
+ 我们首先列出必须考虑的四个前提，因为它们对于你的应用程序相当重要：
  + 连网的(networked)还是非连网的(nonnetworked)。我们假设已作出这个决定，IPC就是用于单台主机上的进程或线程间的。如果应用程序有可能散布堕胎主机上，那就考虑使用套接字代替IPC，从而简化以后向连网的应用程序转移的工作
  + 可移植性(portability)。几乎所有Unix系统都支持Posix管道，Posix FIFO和Posix记录上锁。几乎所有Unix系统都可使用Sun RPC，门则是Solaris特有的特性
  + 性能(performance)。如果性能是应用程序设计中的一个关键前提，那就在你自己的系统上运行附录A中开发的程序。更好的做法是，把这些程序修改称模拟待定应用的实际环境，再再这样的环境中测量它们的性能
  + 实时调度(realtime scheduling)。如果你的应用需要这一特性，而且你的系统支持Posix实时调度选项，那就考虑使用Posix的消息传递和同步函数（消息队列，信号量，互斥锁，条件变量）。举例来说，当某个线程挂出一个有多个线程阻塞在其上的信号量时，待解阻塞的线程是以一种适合于所阻塞线程的调度策略和参数的方式选择的。相反，System V信号量不能保证实时调度

+ 为了帮助理解各种类型IPC的一些特性和局限，我们汇总了它们的一些主要差异：
  + 管道和FIFO是字节流，没有消息边界。Posix消息和System V消息则有从发送者向接收者维护的记录边界。（TCP是没有记录边界的字节流，UDP则提供具有记录边界的消息）
  + 当有一个消息放置到一个空队列中时，Posix消息队列可向一个进程发送一个信号，或者启动一个新的线程。System V
  + 消息队列不提供类似的通知形式。这两种消息队列都不能直接跟select和poll一起使用，不过我们分别在图5-14和6.9节中提供了间接的方法
  + 管道或FIFO中的数据字节是先进先出的。Posix消息和System V消息具备由发送者赋予的优先级。从一个Posix消息队列读出消息时，首先返回的总是具有最高优先级的消息。从一个System V消息队列读出时，读出者可以请求所想要的任意优先级的消息
  + 当有一个消息放置到一个Posix或System V消息队列，或者写到一个管道胡FIFO时，只有一个副本递交给刚好一个线程。这些IPC形式不存在窥探能力（即类似于套接字API的MSG_PEEK标志，UNPV1的13.7节），它们的消息不能广播或多播到多个接收者（这对于使用UDP协议的套接字程序和XTI程序时可能的，UNPv1第十八章和第十九章
  + 互斥锁，条件变量和读写锁都是无名的，也就是说，它们是基于内存的。它们能够很容易地在单个进程内的不同线程间共享。然而只有当它们存放在不同进程间共享的内存区中时，它们才有可能为这些进程所共享。而Posix信号量就有两种形式：有名的和基于内存的。有名信号量总能在不同进程间共享（因为它们是用Posix IPC名字标识的），基于内存的信号量也能在不同进程间共享，条件是必须村房子这些进程间共享的内存区中。System V信号量也是有名的，不过所用的是key_t数据类型，它往往是从某个文件的路径名获取的。这些信号量能够很容易地在不同进程间共享
  + 如果持有某个锁的进程没有释放它就终止，内核就自动释放fcntl记录锁。System V信号量将这一特性作为一个选项提供。互斥锁，条件变量，读写锁和Posix信号量不具备该特性
  + 每个fcntl锁都与通过其相应描述符访问的文件中的某个字节范围（我们称之为一个“记录”）相关联。读写锁则不与任何类型的记录关联
  + Posix共享内存区和System V共享内存区都具有随内核的持续性。它们一直存在到被显式地删除为止，即使当前没有任何进程在使用它们也这样
  + Posix共享内存区对象的大小可在其使用期间扩张。System V共享内存区的大小则是在创建时固定下来的
  + System V IPC所存在的三种内核限制往往需要系统管理员对它们进行调整，因为它们的默认值通常不能满足现实应用的需要（3.8节）。Posix IPC所存在的三种内核限制则通常根本不需要调整
  + 有关System V IPC对象的信息（当前大小，属主ID，最后修改时间等等）可使用三个XXXctl函数的IPC_STAT命令获取，也可执行ipcs命令获取。有关Posix IPC对象的信息则不存在标准的获取方式。如果这些对象是用文件系统中的文件实现的，而且我们知道从Posix IPC名字到路径名的映射关系，那么这些对象的信息可使用stat函数或ls命令获取。但是如果这些对象不是使用文件实现的，那么可能获取不了这样的信息
  + 在众多的同步技术--互斥锁，条件变量，读写锁，记录锁，Posix信号量和System V信号量中，可从信号处理程序中调用的函数只有sem_post和fcntl
  + 在众多的消息传递技术：管道，FIFO，Posix消息队列和System V消息队列中，可从一个信号处理程序中调用的函数只有read和write（适用于管道和FIFO）
  + 在所有的消息传递技术中，只有门向服务器准确地提供了客户的标识（15.5节）.在5.4节中我们提到过，另外两种消息传递类型也标识客户：BSD/OS在使用Unix域套接字时提供这种标识（UNPv1的15.2节），SVR4则在通过某个管道传递一个描述符时通过同一个管道传递发送者的标识

## 性能测量

### 1.1 概述

+ 本书讨论了六种类型的消息传递：
  + 管道
  + FIFO
  + Posix消息队列
  + System V消息队列
  + 门
  + Sun RPC
+ 五种类型的同步
  + 互斥锁和条件变量
  + 读写锁
  + fcntl记录上锁
  + Posix信号量
  + System V信号量
+ 我们现在开发一些简单的程序来测量这些IPC类型的性能，这样有助于我们就何时该使用某种特定形式的IPC做出明智的决策

+ 比较不同形式的消息传递时，我们感兴趣的是以下两种测量尺度：
  + 带宽(bandwidth)：数据通过IPC通道转移的速度。为测量该值，我们从一个进程向另一个进程发送大量数据（几百万字节）。我们还给不同大小的I/O操作测量该值，期待发现带宽随每个I/O操作数据量的增长而增长的规律
  + 延迟(latency)：一个小的IPC消息从一个进程到另一个进程再返回所花的时间。我们测量的是只有一个字节的消息从一个进程到另一个进程再回来的时间（往返时间）
+ 在现实世界中，带宽高速我们大块数据通过一个IPC通道发送出去需花多长时间，然而IPC也由于传送小的控制信息，系统处理这些小消息所需的时间就由延迟提供。这两个数都很重要。