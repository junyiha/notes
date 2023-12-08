## 简介

+ C++ <mutex>标准库

## C++ <mutex>标准库

`<mutex>` 是 C++ 标准库提供的头文件，其中定义了一些用于多线程编程的基本互斥量和锁（mutexes和locks）。

### 主要类和功能：

1. **`std::mutex`**：
   - 互斥量，提供了基本的互斥访问，用于保护共享资源。
   - 可以使用 `lock()` 和 `unlock()` 方法来手动锁定和解锁。
   - 通常与 `std::lock_guard` 或 `std::unique_lock` 结合使用，实现自动的锁定和解锁。

2. **`std::lock_guard`**：
   - 提供了一种简单的方式来管理互斥量的锁定和解锁。
   - 在构造时锁定互斥量，在作用域结束时自动解锁。

3. **`std::unique_lock`**：
   - 类似于 `std::lock_guard`，提供对互斥量的锁定和解锁操作。
   - 拥有更多的灵活性，可以手动控制锁的范围，也可以手动解锁并重新锁定。

4. **`std::recursive_mutex`**：
   - 递归互斥量，允许同一线程多次对其进行加锁，避免死锁。

5. **`std::timed_mutex`**：
   - 有超时功能的互斥量，在尝试锁定超时后会返回失败。

6. **`std::recursive_timed_mutex`**：
   - 有超时功能的递归互斥量。

### 示例：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment_shared_data() {
    std::lock_guard<std::mutex> lock(mtx);
    ++shared_data;
}

int main() {
    std::thread t1(increment_shared_data);
    std::thread t2(increment_shared_data);

    t1.join();
    t2.join();

    std::cout << "Shared data: " << shared_data << std::endl;

    return 0;
}
```

在此示例中，`std::mutex` 用于保护共享资源 `shared_data`。`std::lock_guard` 用于在作用域内锁定互斥量，确保对 `shared_data` 的增加操作是线程安全的。通过使用互斥量，可以确保多个线程不会同时访问共享资源，避免了竞态条件（race condition）的发生。

## C++ <mutex>标准库 详解

`<mutex>` 是 C++ 标准库中的头文件，提供了用于多线程编程的互斥量（mutex）和锁（lock）的基本支持。

### 主要类和功能：

1. **`std::mutex`**：
   - 互斥量类，用于保护共享资源，防止多个线程同时访问。
   - 成员函数有 `lock()`（锁定互斥量）、`try_lock()`（尝试锁定互斥量，避免阻塞）、`unlock()`（解锁互斥量）等。

2. **`std::lock_guard`**：
   - 提供自动管理互斥量的锁定和解锁。
   - 在构造时锁定互斥量，在作用域结束时自动解锁。

3. **`std::unique_lock`**：
   - 与 `std::lock_guard` 类似，提供对互斥量的锁定和解锁。
   - 拥有更多的灵活性，允许手动控制锁的范围，也可以手动解锁和重新锁定。

4. **`std::recursive_mutex`**：
   - 递归互斥量，允许同一线程多次对其进行加锁，避免死锁。

5. **`std::timed_mutex`**：
   - 有超时功能的互斥量，在尝试锁定超时后会返回失败。

6. **`std::recursive_timed_mutex`**：
   - 有超时功能的递归互斥量。

### 锁类型选择：
- `std::lock_guard` 适用于简单的互斥量锁定，作用域结束时自动释放锁。
- `std::unique_lock` 更灵活，允许手动控制锁的生命周期和多次锁定和解锁。
- `std::timed_mutex` 和 `std::recursive_timed_mutex` 适用于需要超时特性的情况。

### 示例：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment_shared_data() {
    std::lock_guard<std::mutex> lock(mtx);
    ++shared_data;
}

int main() {
    std::thread t1(increment_shared_data);
    std::thread t2(increment_shared_data);

    t1.join();
    t2.join();

    std::cout << "Shared data: " << shared_data << std::endl;

    return 0;
}
```

在此示例中，`std::mutex` 用于保护共享资源 `shared_data`。`std::lock_guard` 用于在作用域内锁定互斥量，确保对 `shared_data` 的增加操作是线程安全的。通过使用互斥量，可以确保多个线程不会同时访问共享资源，避免了竞态条件（race condition）的发生。

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

## std::lock_guard

`std::lock_guard` 是 C++ 标准库中的一个模板类，用于管理互斥量的锁定和解锁操作。它提供了一种简单的方式，在作用域内锁定互斥量，并在作用域结束时自动释放锁。

### 主要特性和用法：

1. **自动锁定和解锁**：`std::lock_guard` 在构造时锁定互斥量，在作用域结束时自动释放锁。
2. **简化代码**：使用 `std::lock_guard` 可以避免手动调用 `mutex` 的 `lock()` 和 `unlock()` 方法。
3. **RAII（资源获取即初始化）**：充分利用了 RAII 的机制，确保在异常或作用域提前退出时，锁都能正确释放，防止死锁和资源泄漏。

### 示例：

以下是一个简单的示例，展示了 `std::lock_guard` 的使用方法：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment_shared_data() {
    std::lock_guard<std::mutex> lock(mtx); // 在此处锁定互斥量

    // 对共享资源进行操作
    ++shared_data;
    std::cout << "Shared data incremented by 1." << std::endl;

    // 在 lock 对象超出作用域时，自动解锁互斥量
}

int main() {
    std::thread t1(increment_shared_data);
    std::thread t2(increment_shared_data);

    t1.join();
    t2.join();

    std::cout << "Final shared data value: " << shared_data << std::endl;

    return 0;
}
```

在此示例中，`std::lock_guard` 类型的对象 `lock` 在构造时锁定了互斥量 `mtx`，在作用域结束时，`lock` 对象超出作用域范围，自动调用析构函数，从而自动解锁了 `mtx` 互斥量。这确保了 `shared_data` 的增加操作是在互斥访问下进行的，避免了多线程环境下的竞态条件。

## std::unique_lock

`std::unique_lock` 是 C++ 标准库中提供的一个模板类，用于管理互斥量（`std::mutex`）的锁定和解锁操作。它提供了更灵活的锁管理机制，相比于 `std::lock_guard`，`std::unique_lock` 提供了更多的功能。

### 主要特性和用法：

1. **灵活性**：`std::unique_lock` 对象的锁定和解锁不仅限于作用域的进入和退出，可以手动控制锁的范围。
2. **构造和析构**：`std::unique_lock` 对象在构造时锁定互斥量，在析构时自动解锁。
3. **锁定和解锁**：可通过 `lock()` 和 `unlock()` 方法手动锁定和解锁互斥量。
4. **所有权转移**：支持将 `std::unique_lock` 对象的所有权转移给另一个对象，提供了移动语义。

### 示例：

以下是一个简单示例，演示了 `std::unique_lock` 的基本用法：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void someFunction() {
    std::unique_lock<std::mutex> lock(mtx); // 在此处锁定互斥量

    // 做一些工作
    std::cout << "Doing some work within a critical section." << std::endl;
    
    // 在 lock 超出作用域时自动解锁
}

int main() {
    std::thread t(someFunction);

    // 执行其他操作

    t.join();

    return 0;
}
```

在这个示例中，`std::unique_lock` 对象 `lock` 在构造时锁定了互斥量 `mtx`，当 `lock` 超出作用域时，会自动解锁互斥量。这种机制保证了在 `std::unique_lock` 对象生命周期内，互斥量的锁定状态始终得到正确管理。

`std::unique_lock` 的另一个优点是，可以手动控制锁的范围，例如使用 `lock()` 和 `unlock()` 方法，允许在需要时手动进行锁定和解锁操作，提供更多灵活性。

此外，`std::unique_lock` 也支持将其所有权转移给另一个 `std::unique_lock` 对象，这种特性可用于实现更复杂的锁管理场景，比如资源的安全移交。

## std::recursive_mutex

`std::recursive_mutex` 是 C++ 标准库中提供的一个互斥量类，它与 `std::mutex` 类似，但允许同一个线程对互斥量多次进行锁定。这种特性允许同一线程在已经锁定的情况下再次对其进行锁定，避免了死锁的可能性。

### 主要特点和用法：

1. **递归锁定**：`std::recursive_mutex` 允许同一个线程对它进行多次锁定。
2. **避免死锁**：递归锁可以使得同一个线程在持有锁的情况下再次对其进行锁定，避免了由于同一线程多次锁定导致的死锁。
3. **使用方法**：与 `std::mutex` 类似，使用 `lock()` 和 `unlock()` 方法进行锁定和解锁。

### 示例：

以下是一个简单的示例，演示了 `std::recursive_mutex` 的基本用法：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex r_mtx;
int shared_data = 0;

void increment_shared_data() {
    std::lock_guard<std::recursive_mutex> lock(r_mtx);
    ++shared_data;
    std::cout << "Shared data incremented by 1." << std::endl;
}

void recursive_function(int count) {
    std::lock_guard<std::recursive_mutex> lock(r_mtx);
    if (count > 0) {
        std::cout << "Count: " << count << std::endl;
        recursive_function(count - 1); // 递归调用
    }
}

int main() {
    std::thread t1(increment_shared_data);
    std::thread t2(recursive_function, 3);

    t1.join();
    t2.join();

    std::cout << "Final shared data value: " << shared_data << std::endl;

    return 0;
}
```

在此示例中，`std::recursive_mutex` 类型的对象 `r_mtx` 被用于保护共享资源 `shared_data`。在函数 `recursive_function()` 中，`r_mtx` 被同一线程多次锁定，并通过递归调用自身来展示 `std::recursive_mutex` 的递归特性。通过递归锁定，同一线程可以多次对 `r_mtx` 进行加锁，避免了死锁的可能性。

## std::timed_mutex

`std::timed_mutex` 是 C++ 标准库提供的一个互斥量类，它是 `std::mutex` 的变种，提供了超时功能。`std::timed_mutex` 允许线程尝试锁定互斥量，但在一段时间内无法成功锁定时，可以设置超时机制，以避免无限期等待。

### 主要特点和用法：

1. **超时锁定**：`std::timed_mutex` 允许线程尝试锁定互斥量，并在超时后返回结果，避免线程无限期等待。
2. **`try_lock_for()` 和 `try_lock_until()`**：提供了超时版本的 `try_lock()`，允许线程在一段时间内尝试锁定互斥量。
3. **`lock()` 和 `unlock()`**：与 `std::mutex` 类似，用于手动锁定和解锁互斥量。
4. **超时策略**：可以使用 `std::chrono` 中的时间点或时间段，设置超时时间。

### 示例：

以下是一个简单的示例，演示了 `std::timed_mutex` 的基本用法：

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex t_mtx;
int shared_data = 0;

void try_lock_function() {
    if (t_mtx.try_lock_for(std::chrono::milliseconds(100))) {
        // 成功锁定互斥量
        ++shared_data;
        std::cout << "Shared data incremented by 1." << std::endl;
        t_mtx.unlock();
    } else {
        // 未能在指定时间内锁定互斥量
        std::cout << "Could not acquire lock within specified time." << std::endl;
    }
}

int main() {
    std::thread t(try_lock_function);

    t.join();

    std::cout << "Final shared data value: " << shared_data << std::endl;

    return 0;
}
```

在此示例中，`std::timed_mutex` 类型的对象 `t_mtx` 用于保护共享资源 `shared_data`。`try_lock_function()` 函数尝试在100毫秒内锁定 `t_mtx`，如果在超时时间内成功获得了锁，则增加 `shared_data` 的值，否则在未获得锁时输出一条提示信息。这样可以避免线程无限期等待互斥量的锁定，提高程序的鲁棒性。

## std::recursive_timed_mutex

`std::recursive_timed_mutex` 是 C++ 标准库提供的一个互斥量类，结合了 `std::recursive_mutex` 和 `std::timed_mutex` 的特性，允许同一个线程多次对其进行锁定，并提供了超时功能。

### 主要特点和用法：

1. **递归和超时**：`std::recursive_timed_mutex` 允许同一个线程对互斥量多次进行锁定，并在一定时间内尝试锁定互斥量，提供了递归性和超时性。
2. **`try_lock_for()` 和 `try_lock_until()`**：提供了超时版本的 `try_lock()`，允许线程在一段时间内尝试锁定互斥量。
3. **`lock()` 和 `unlock()`**：与 `std::recursive_mutex` 类似，用于手动锁定和解锁互斥量。

### 示例：

以下是一个简单的示例，演示了 `std::recursive_timed_mutex` 的基本用法：

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::recursive_timed_mutex rt_mtx;
int shared_data = 0;

void recursive_lock_function(int count) {
    std::unique_lock<std::recursive_timed_mutex> lock(rt_mtx, std::defer_lock);

    if (count > 0) {
        if (lock.try_lock_for(std::chrono::milliseconds(100))) {
            // 成功锁定互斥量
            ++shared_data;
            std::cout << "Shared data incremented by 1." << std::endl;
            lock.unlock();
        } else {
            // 未能在指定时间内锁定互斥量
            std::cout << "Could not acquire lock within specified time." << std::endl;
        }
        recursive_lock_function(count - 1); // 递归调用
    }
}

int main() {
    recursive_lock_function(3);

    std::cout << "Final shared data value: " << shared_data << std::endl;

    return 0;
}
```

在此示例中，`std::recursive_timed_mutex` 类型的对象 `rt_mtx` 用于保护共享资源 `shared_data`。`recursive_lock_function()` 函数尝试在100毫秒内锁定 `rt_mtx`，如果在超时时间内成功获得了锁，则增加 `shared_data` 的值，并在解锁后进行递归调用。这样，线程可以多次锁定同一个 `std::recursive_timed_mutex` 对象，并提供了超时机制。