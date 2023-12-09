## 简介

+ C++ <initializer_list>标准库

## C++ <initializer_list>标准库

`<initializer_list>` 是 C++11 引入的头文件，用于支持初始化列表（Initializer List）功能。它提供了一个模板类 `std::initializer_list`，用于表示一个初始化列表，允许在容器和其他类型中以类似数组的形式初始化对象。

### std::initializer_list 概述
- `std::initializer_list` 是一个模板类，定义在 `<initializer_list>` 头文件中。
- 它提供了一种轻便的语法，允许用花括号 `{}` 列表初始化特定类型的对象。
- 这个类是一个轻量级的封装器，可以在构造函数或函数参数中方便地传递初始化列表。

### 基本用法示例：
```cpp
#include <iostream>
#include <initializer_list>

void printList(std::initializer_list<int> list) {
    for (auto elem : list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::initializer_list<int> numbers = {1, 2, 3, 4, 5};
    
    // 使用 initializer_list 初始化对象
    std::cout << "Initialized list: ";
    printList({10, 20, 30});

    return 0;
}
```

### 主要特点和用途：
- 允许以列表初始化的方式传递多个值给函数或容器。
- 用于简化容器、类或函数的构造函数，使得初始化更为方便。
- 可用于自定义函数或类的构造函数，以便更轻松地处理多个参数的初始化。

`std::initializer_list` 的出现使得初始化更加简洁和灵活，它适用于许多场景，例如容器初始化、函数参数传递等，使得代码更具可读性和易用性。