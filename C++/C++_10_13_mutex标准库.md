## 简介

+ C++ <mutex>标准库

## std::mutex

`std::mutex` 是 C++ 标准库 `<mutex>` 中定义的类，用于提供互斥量功能，确保在多线程环境中对共享资源的安全访问。

### 主要操作和函数：

1. **lock() 和 unlock()**：`std::mutex` 提供了 `lock()` 和 `unlock()` 函数用于手动锁定和解锁互斥量。

    ```cpp
    std::mutex mtx;

    mtx.lock(); // 锁定互斥量
    // 对共享资源进行操作
    mtx.unlock(); // 解锁互斥量
    ```

2. **std::lock_guard**：`std::lock_guard` 是一个 RAII（资源获取即初始化）类，用于自动管理 `std::mutex` 的锁定和解锁。

    ```cpp
    std::mutex mtx;

    {
        std::lock_guard<std::mutex> lock(mtx); // 在作用域中自动锁定互斥量
        // 对共享资源进行操作
    } // 在作用域结束时自动解锁互斥量
    ```

3. **try_lock()**：尝试锁定互斥量，如果不能立即获得锁，`try_lock()` 函数会立即返回，而不会阻塞线程。

    ```cpp
    std::mutex mtx;

    if (mtx.try_lock()) {
        // 成功获得锁，对共享资源进行操作
        mtx.unlock(); // 解锁互斥量
    } else {
        // 未能立即获得锁，执行其他操作
    }
    ```

4. **递归互斥量**：`std::recursive_mutex` 类是 `std::mutex` 的变种，允许同一线程多次对互斥量进行加锁操作，适用于特定场景。

### 示例用法：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void threadFunction(int id) {
    mtx.lock(); // 锁定互斥量
    std::cout << "Thread " << id << " is executing..." << std::endl;
    mtx.unlock(); // 解锁互斥量
}

int main() {
    std::thread t1(threadFunction, 1);
    std::thread t2(threadFunction, 2);

    t1.join();
    t2.join();

    return 0;
}
```

在这个示例中，`std::mutex` 被用来保护对共享资源（在这里是标准输出流 `std::cout`）的访问。线程函数通过调用 `mtx.lock()` 和 `mtx.unlock()` 来手动锁定和解锁互斥量，确保每个线程在访问共享资源时的独占性。

