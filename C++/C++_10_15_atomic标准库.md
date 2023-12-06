## 简介

+ C++ <atomic>标准库

## std::atomic

`std::atomic` 是 C++ 标准库 `<atomic>` 中定义的模板类，用于执行原子操作，提供了多线程环境下对共享变量的安全访问。`std::atomic` 类型的变量可以保证其操作的原子性，即对它们的操作不会被中断。

### 主要特性和操作：

1. **原子操作**：`std::atomic` 类型的变量支持多种原子操作，包括读取、写入和各种算术和逻辑操作。这些操作保证在多线程环境中的原子性，不会被其他线程的操作中断。

2. **内存顺序（Memory Order）**：原子操作可以指定内存顺序，即操作在多线程间的执行顺序，包括 `memory_order_relaxed`、`memory_order_acquire`、`memory_order_release` 等。

3. **支持的操作**：`std::atomic` 类型支持各种操作，如加载（load）、存储（store）、交换（exchange）、比较交换（compare_exchange_strong/compare_exchange_weak）等。

### 示例用法：

```cpp
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> counter(0);

void incrementCounter() {
    for (int i = 0; i < 10000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed); // 原子性地增加计数器值
    }
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl; // 输出计数器的值

    return 0;
}
```

在上述示例中，`std::atomic<int>` 类型的 `counter` 变量用于在两个线程中增加一个计数器的值。`fetch_add()` 函数用于原子性地增加计数器的值，保证了多线程环境下的安全访问。最终输出的 `counter` 值应该是 `20000`，因为两个线程各自增加了 `10000` 次。