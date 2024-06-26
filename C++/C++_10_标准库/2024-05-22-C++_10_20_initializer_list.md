---
category: Cpp
date: 2024-05-22 09:00:00 +0800
layout: post
title: C++_10_20_initializer_list
tag: CppSTL
---
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

## C++ <initializer_list>标准库 详解

`<initializer_list>` 是 C++11 引入的标准库头文件，其中定义了 `std::initializer_list` 类模板。它提供了初始化列表（initializer list）功能，允许以列表的形式初始化多个值，用于在构造函数或函数参数中传递多个值。

### `std::initializer_list` 概述：

- **头文件：** `<initializer_list>`
- **类模板：** `std::initializer_list<T>`

### 主要特点和用途：

1. **初始化列表的表示：**
   - `std::initializer_list` 是一个轻量级容器，用于保存多个同类型元素的列表。
   - 使用花括号 `{}` 包围元素来构造初始化列表。

2. **在函数参数中使用：**
   - 可以作为函数的参数，允许以初始化列表的形式传递多个值给函数。
   - 通过此特性可以轻松传递多个参数给函数，方便进行函数调用。

3. **类和容器中的应用：**
   - 类的构造函数可以接受 `std::initializer_list` 作为参数，允许通过初始化列表对类的成员进行初始化。
   - STL 容器如 `std::vector`、`std::array`、`std::map` 等也可以使用初始化列表来初始化元素。

4. **用于范围迭代：**
   - 提供了 begin() 和 end() 方法，允许通过迭代器访问初始化列表的元素。

### 示例代码：

```cpp
#include <iostream>
#include <initializer_list>

// 函数接受 initializer_list 作为参数
void printList(std::initializer_list<int> list) {
    for (auto elem : list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 初始化列表示例
    std::initializer_list<int> numbers = {1, 2, 3, 4, 5};

    // 使用 initializer_list 初始化对象
    std::cout << "Initialized list: ";
    printList({10, 20, 30});

    return 0;
}
```

`std::initializer_list` 在 C++ 中提供了一种便捷的方式来处理初始化列表，使得在构造函数或函数参数中传递多个值变得更加方便和直观。

## C++ <initializer_list>标准库 常用的类和函数

在 `<initializer_list>` 头文件中主要定义了 `std::initializer_list` 类模板，该模板提供了一些常用的函数和方法来操作初始化列表。下面是 `std::initializer_list` 常用的类和方法：

### 类：
- **`std::initializer_list<T>`：** 这是一个类模板，表示一个初始化列表，其中 `T` 是元素的类型。
  
### 主要方法和功能：
- **构造函数：**
  - `initializer_list` 的构造函数没有公开的构造函数。它是一个轻量级的容器类，由编译器隐式创建和管理。

- **成员函数：**
  - **`size()`：** 返回初始化列表中元素的数量。
  - **`begin()`：** 返回指向初始化列表第一个元素的指针或迭代器。
  - **`end()`：** 返回指向初始化列表末尾（最后一个元素之后）的指针或迭代器。
  
### 示例代码：

```cpp
#include <iostream>
#include <initializer_list>

void printList(const std::initializer_list<int>& list) {
    std::cout << "Size of list: " << list.size() << std::endl;
    std::cout << "Elements: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::initializer_list<int> numbers = {1, 2, 3, 4, 5};

    // 使用 size() 方法获取初始化列表的大小
    std::cout << "Size of numbers: " << numbers.size() << std::endl;

    // 使用 begin() 和 end() 方法进行迭代
    std::cout << "Elements of numbers: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 调用函数并传递初始化列表
    printList({10, 20, 30, 40, 50});

    return 0;
}
```

这个示例演示了如何使用 `std::initializer_list` 的 `size()`、`begin()` 和 `end()` 成员函数来访问和操作初始化列表的元素。

## std::initializer_list

`std::initializer_list` 是 C++ 标准库提供的模板类，位于 `<initializer_list>` 头文件中。它用于表示初始化列表，允许以列表的形式初始化多个值，通常用于构造函数或函数参数中传递多个值。

### std::initializer_list 概述：

- **头文件：** `<initializer_list>`
- **类模板：** `std::initializer_list<T>`

### 主要特点和用途：

1. **初始化列表的表示：**
   - `std::initializer_list` 是一个轻量级容器，用于保存多个同类型元素的列表。
   - 使用花括号 `{}` 包围元素来构造初始化列表。

2. **在函数参数中使用：**
   - 可以作为函数的参数，允许以初始化列表的形式传递多个值给函数。
   - 通过此特性可以轻松传递多个参数给函数，方便进行函数调用。

3. **类和容器中的应用：**
   - 类的构造函数可以接受 `std::initializer_list` 作为参数，允许通过初始化列表对类的成员进行初始化。
   - STL 容器如 `std::vector`、`std::array`、`std::map` 等也可以使用初始化列表来初始化元素。

4. **用于范围迭代：**
   - 提供了 `begin()` 和 `end()` 方法，允许通过迭代器访问初始化列表的元素。

### 示例代码：

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
    // 初始化列表示例
    std::initializer_list<int> numbers = {1, 2, 3, 4, 5};

    // 使用 initializer_list 初始化对象
    std::cout << "Initialized list: ";
    printList({10, 20, 30});

    return 0;
}
```

`std::initializer_list` 在 C++ 中提供了一种便捷的方式来处理初始化列表，使得在构造函数或函数参数中传递多个值变得更加方便和直观。