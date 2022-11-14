## 惊群效应(thundering herd)

+ 惊群效应，是指多进程（多线程）在同时阻塞等待同一个事件的时候（休眠状态），如果等待的这个事件发生，那么它就会唤醒等待的所有进程（或者线程），但是最终却只能有一个进程（线程）获得这个时间的“控制权”，对该事件进行处理，而其他进程（线程）获取“控制权”失败，只能重新进入休眠状态，这种现象和性能浪费就叫做惊群效应

## pthread_cond_wait()

+ `pthread_cond_wait()` : 用于阻塞当前线程，等待别的线程使用`pthread_cond_signal()`或者`pthread_cond_broadcast()`来唤醒
+ `pthread_cond_wait()`必须与`pthread_mutex`配套使用。`pthread_cond_wait()`函数一旦进入`wait`状态就会自动`release mutex`。当其他线程通过`pthread_cond_signal()`或者`pthread_cond_broadcast()`把该线程唤醒，使`pthread_cond_wait()`通过（返回）时，该线程又自动获得该`mutex`。

## pthread_cond_signal()

+ `pthread_cond_signal()`函数的作用是发送一个信号给另外一个正在处于阻塞等待状态的线程，使其脱离阻塞状态，继续执行，如果没有线程处在阻塞等待状态，`pthread_cond_signal`也会成功返回

## std::thread

+ 构造函数
  + 默认构造函数，创建一个空的 `std::thread` 执行对象
  + 初始化构造函数，创建一个 `std::thread` 对象，该 `std::thread` 对象可被 `joinable`，新产生的线程会调用 `fn` 函数，该函数的参数由 `args` 给出

+ 其他成员函数：
  + `get_id`: 
    + 获取线程 `ID`，返回一个类型为 `std::thread::id` 的对象。
  + `joinable`: 
    + 检查线程是否可被 `join`
    + 检查当前的线程对象是否表示了一个活动的执行线程，由默认构造函数创建的线程是不能被 `join` 的。
    + 另外，如果某个线程 已经执行完任务，但是没有被 `join` 的话，该线程依然会被认为是一个活动的执行线程，因此也是可以被 `join` 的
  + `detach`: 
    + `Detach` 线程
    + 将当前线程对象所代表的执行实例与该线程对象分离，使得线程的执行可以单独进行。
    + 一旦线程执行完毕，它所分配的资源将会被释放
    + 调用 `detach` 函数之后
      + `*this` 不再代表任何的线程执行实例
      + `joinable() == false`
      + `get_id() == std::thread::id()`
  + `swap`: 
    + `Swap` 线程，交换两个线程对象所代表的底层句柄(`underlying handles`)
  + `native_handle`: 
    + 返回 `native handle`
    + （由于 `std::thread` 的实现和操作系统相关，因此该函数返回与 `std::thread` 具体实现相关的线程句柄
  + `hardware_concurrency [static]`: 
    + 检测硬件并发特性，返回当前平台的线程实现所支持的线程并发数目，但返回值仅仅只作为系统提示(hint)

### std::this_thread 命名空间中相关辅助函数介绍

+ `get_id`: 获取线程 `ID`

+ `yield`: 当前线程放弃执行，操作系统调度另一线程继续执行

+ `sleep_until`: 线程休眠至某个指定的时刻(`time point`)，该线程才被重新唤醒

+ `sleep_for`: 线程休眠某个指定的时间片(`time span`)，该线程才被重新唤醒，不过由于线程调度等原因，实际休眠时间可能比 `sleep_duration` 所表示的时间片更长