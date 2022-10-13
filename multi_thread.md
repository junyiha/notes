## 惊群效应(thundering herd)

+ 惊群效应，是指多进程（多线程）在同时阻塞等待同一个事件的时候（休眠状态），如果等待的这个事件发生，那么它就会唤醒等待的所有进程（或者线程），但是最终却只能有一个进程（线程）获得这个时间的“控制权”，对该事件进行处理，而其他进程（线程）获取“控制权”失败，只能重新进入休眠状态，这种现象和性能浪费就叫做惊群效应

## pthread_cond_wait()

+ `pthread_cond_wait()` : 用于阻塞当前线程，等待别的线程使用`pthread_cond_signal()`或者`pthread_cond_broadcast()`来唤醒
+ `pthread_cond_wait()`必须与`pthread_mutex`配套使用。`pthread_cond_wait()`函数一旦进入`wait`状态就会自动`release mutex`。当其他线程通过`pthread_cond_signal()`或者`pthread_cond_broadcast()`把该线程唤醒，使`pthread_cond_wait()`通过（返回）时，该线程又自动获得该`mutex`。

## pthread_cond_signal()

+ `pthread_cond_signal()`函数的作用是发送一个信号给另外一个正在处于阻塞等待状态的线程，使其脱离阻塞状态，继续执行，如果没有线程处在阻塞等待状态，`pthread_cond_signal`也会成功返回