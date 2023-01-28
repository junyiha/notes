## 微信文章 --  

### top

+ 与进程相关的两个指标：VIRT Virtual Memory, 虚拟内存 和 RES Resident Memory，常驻内存，通常称为物理内存
  + 虚拟内存，是指整个进程申请的内存，包括程序本身占用的内存，new或者malloc分配的内存等
  + 物理内存，就是这个进程在主板上内存条中占用的内存
+ 所以，通过top查看进程内存时，如果发现VIRT占用很大，说明这个程序用new或者malloc等分配了很多内存，但如果RES不是很大，那就不要慌，可能这只是程序的一个缓存优化，实际程序占用的物理内存并不大，但如果RES也很高，那可能就有点慌了

### 内存泄漏

+ 内存泄漏是导致进程内存持续上涨最常见的原因，而这是C++中常见但不好处理的问题。
+ 解决这个问题没有什么通用的快捷的办法，只能根据实际业务处理

+ 第一，从业务上，能不能重现内存泄漏。
  + 例如，做游戏，加入玩家不停地登录，就会导致内存不断上涨，那就说明问题就在登录游戏，把整个流程拆分，一个个屏蔽测试，最终找出问题

+ 第二，从部署上，能不能定位内存泄漏。
  + 例如，最近更新了一个版本，发现内存占用变得很高，那就可以确定，是这个版本的修改出现了问题，一个版本的代码量终究是有限的，查找起来也比较容易

+ 第三，使用valgrind memcheck。如果能够复现内存泄漏，但无法定位是哪个逻辑，那就可以用valgrind memcheck。复现内存泄漏，这个通常比较难实现，一般是线下测试无法复现，线上用户量大，运行久了才会复现，而valgrind会导致程序运行很慢，无法支撑线上测试，因此这个选项不太适用于线上

+ 第四，使用Visual Leak Detector.valgrind使linux下的，如果程序可以跨平台，或者只在windows下，可以试试这个

+ 第五，重载new,delete。
  + 可以简单加个计数，用于平时预防泄漏，也可更深入一些，记录内存的分配，得到内存泄漏的堆栈，但是这个是否能够支撑线上debug，不一定

+ 第六，使用自己的内存分配函数，每一个内存分配，都是用自己的函数，每一个STL的容器，都传入自己的分配器，然后分别记录这些内存分配的大小。
  + 这个方法看起来很不现实，但如果能够使用并实现，对内存统计，查找有很大的帮助，而且支持线上debug。
  + 查找内存，只需要打印每个分配器分配的内存大小基本上可以得到结论是哪个分配器除了问题。
  + 唯一的问题是它增加了开发难度，而且不能像valgrind那样不需要修改程序即可使用

+ 第七，使用valgrind massif。valgrind memcheck需要复现内存泄漏，所以不容易找出问题。它会定时记录分配内存的各个堆栈以及分配内存的量，当出现内存泄漏时，根据分配内存的量检查各个堆栈，应该可以找到问题的。
  + massif也会导致程序运行满，但比memcheck要快，能不能线上debug，这个依然需要看具体情况

+ 第八，使用第三方内存分配器，例如jemalloc。并不是说使用第三方内存分配器就解决问题了，而是jemalloc自带了一大堆工具，其中jeprof可以得到内存的大小以及堆栈等信息，对查找内存泄漏有很大帮助
  + 不过开启prof后，效率如何，能不能在线上使用，不一定

### 内存碎片

+ 加入找不到内存泄漏，也许本来就没有内存泄漏，这时不妨考虑内存碎片的问题
+ 以linux下的ptmalloc为例

### 内存利用率

+ 如果一个进程占用的内存远高于预期，但没有持续上涨，还需要考虑下是不是内存使用率的问题。
+ 当使用new分配一块内存时，系统需要为这次分配记录大小，地址，分配的内存也需要对其。
+ 加入分配的内存很小，例如1b，那系统最终需要消耗的内存是远大于1b的