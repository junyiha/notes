## 简介

+ <chrono>标准库相关笔记

## C++ <chrono>标准库是什么

C++ 标准库中的 `<chrono>` 是用于处理时间相关操作的头文件，提供了时间点（`time_point`）和持续时间（`duration`）的类模板，以及用于操作时间的各种函数和工具。

主要包括以下内容：

### 时间点（`time_point`）和持续时间（`duration`）：

- **`std::chrono::time_point`：** 代表时间的点，通常表示自某个特定时钟起的时间。例如，`std::chrono::system_clock::time_point` 表示系统时钟的时间点。
- **`std::chrono::duration`：** 表示时间间隔的持续时间，可以用于表示一段时间的长度。例如，`std::chrono::duration<int>` 表示以整数单位的时间段。

### 时钟（Clocks）：

- **`std::chrono::system_clock`：** 代表系统时钟，提供了从 Epoch（通常是 1970 年 1 月 1 日）起的时间点。
- **`std::chrono::steady_clock`：** 代表一个单调递增的时钟，不受系统时间调整影响，适合测量时间间隔。
- **`std::chrono::high_resolution_clock`：** 代表一个高分辨率的时钟，提供了更高精度的计时。

### 时间相关工具和函数：

- **时间单位转换：** 提供了 `duration_cast` 函数用于不同时间单位之间的转换。
- **时间点的算术运算：** 可以对时间点进行加减运算。
- **定时器操作：** 可以用于实现定时器，比如 `std::this_thread::sleep_for` 和 `std::this_thread::sleep_until`。
- **时钟的特性和属性：** 可以获取时钟的特性，如时钟的最小精度、是否稳定等。

### 示例：

```cpp
#include <iostream>
#include <chrono>

int main() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 时间点转换为时间戳
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // 打印当前时间
    std::cout << "Current time: " << std::ctime(&now_c);

    // 创建持续时间并延迟一段时间
    std::chrono::milliseconds delay(1000);
    std::this_thread::sleep_for(delay);

    return 0;
}
```

`<chrono>` 提供了一种标准化的时间处理方式，可用于测量和管理时间，执行定时操作以及进行时间单位转换。

## C++ <chrono>标准库 详解

`<chrono>` 是 C++ 标准库中用于处理时间相关操作的头文件，自 C++11 起引入。它提供了时间点（`time_point`）、持续时间（`duration`）、时钟（`clock`）以及与时间相关的函数和工具，使得在 C++ 中对时间进行精确测量和处理变得更加方便和标准化。

### 重要的类型和类：

- **`std::chrono::time_point`：** 表示时间的点，在特定时钟下的时间。例如，`std::chrono::system_clock::time_point` 表示系统时钟的时间点。
- **`std::chrono::duration`：** 表示时间间隔的持续时间，可以用于表示一段时间的长度。例如，`std::chrono::duration<int>` 表示以整数单位的时间段。

### 重要的时钟（Clocks）：

- **`std::chrono::system_clock`：** 代表系统时钟，提供了从 Epoch（通常是 1970 年 1 月 1 日）起的时间点。
- **`std::chrono::steady_clock`：** 代表一个单调递增的时钟，不受系统时间调整影响，适合测量时间间隔。
- **`std::chrono::high_resolution_clock`：** 代表一个高分辨率的时钟，提供了更高精度的计时。

### 主要函数和工具：

- **时间单位转换：** 提供了 `std::chrono::duration_cast` 函数用于不同时间单位之间的转换。
- **时间点的算术运算：** 可以对时间点进行加减运算。
- **定时器操作：** 可以用于实现定时器，比如 `std::this_thread::sleep_for` 和 `std::this_thread::sleep_until`。
- **获取时间点：** 提供了 `std::chrono::system_clock::now()` 用于获取当前时间点。

### 示例：

```cpp
#include <iostream>
#include <chrono>

int main() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 时间点转换为时间戳
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // 打印当前时间
    std::cout << "Current time: " << std::ctime(&now_c);

    // 创建持续时间并延迟一段时间
    std::chrono::milliseconds delay(1000);
    std::this_thread::sleep_for(delay);

    return 0;
}
```

`<chrono>` 提供了一种标准化的时间处理方式，可用于测量和管理时间，执行定时操作以及进行时间单位转换。它的引入使得在 C++ 中对时间进行处理更加方便和跨平台。