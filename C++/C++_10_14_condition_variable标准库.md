## 简介

+ C++ <condition_variable>标准库

## std::condition_variable

`std::condition_variable` 是 C++ 标准库 `<condition_variable>` 中定义的类，用于线程间的条件变量通信和同步。

它通常与 `std::mutex` 结合使用，实现线程的等待和唤醒操作，以在多线程环境中进行同步和通信。

### 主要操作和函数：

1. **wait()**：线程等待条件变量满足。在等待时，线程会释放与互斥量关联的锁，直到另一个线程通过 `notify_one()` 或 `notify_all()` 唤醒它。

    ```cpp
    std::condition_variable cv;
    std::mutex mtx;

    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck); // 等待条件变量满足
    ```

2. **notify_one() 和 notify_all()**：用于唤醒一个或所有等待条件变量的线程。

    ```cpp
    std::condition_variable cv;
    std::mutex mtx;

    cv.notify_one(); // 唤醒一个等待条件变量的线程
    // 或
    cv.notify_all(); // 唤醒所有等待条件变量的线程
    ```

### 示例用法：

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void workerThread() {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [] { return ready; }); // 等待条件变量为 true

    std::cout << "Worker thread is processing..." << std::endl;
    // 执行工作...
}

int main() {
    std::thread worker(workerThread); // 创建新线程

    // 做一些其他工作...

    // 等待一段时间后，设置条件变量为 true
    std::this_thread::sleep_for(std::chrono::seconds(2));
    {
        std::lock_guard<std::mutex> lck(mtx);
        ready = true;
    }
    cv.notify_one(); // 唤醒等待的线程

    worker.join(); // 等待线程执行完毕

    return 0;
}
```

在这个示例中，`std::condition_variable` 被用于在工作线程等待一个条件变量为 `true` 的信号，主线程在一定条件下唤醒工作线程。工作线程在等待期间会释放锁，只有当条件满足时才会被唤醒继续执行。主线程通过 `notify_one()` 唤醒等待的工作线程。