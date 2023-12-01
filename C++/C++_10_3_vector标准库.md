## 简介

+ <vector>标准库相关笔记

## C++ <vector>标准库是什么

`<vector>` 是 C++ 标准库提供的头文件之一，用于包含 C++ 标准库中的向量（`vector`）容器类的定义。向量是一个动态数组，它能够以连续的内存空间存储元素，并提供了灵活的大小调整和高效的随机访问。

`std::vector` 是一个模板类，可以存储任意类型的元素，并具有以下特性：

1. **动态大小：** 向量可以根据需要动态增长或缩小其大小，可以通过 `push_back`、`pop_back` 等方法在尾部添加或删除元素。
2. **随机访问：** 支持通过索引快速访问和修改元素，时间复杂度为 O(1)。
3. **连续内存存储：** 向量的元素在内存中是连续存储的，这有助于提高数据的访问速度。
4. **尾部插入和删除的高效性：** 在尾部插入或删除元素的操作通常是高效的，时间复杂度为平摊 O(1)。

以下是一个简单的示例，演示了如何使用 `<vector>` 头文件中的 `std::vector` 类：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个整数向量
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 在向量尾部添加元素
    vec.push_back(6);

    // 遍历输出向量中的元素
    std::cout << "Vector Elements: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

`<vector>` 头文件中的 `std::vector` 类是 C++ 中常用的标准容器之一，它提供了方便的动态数组功能，并且在许多情况下都是一种方便且高效的数据结构选择。

## C++ <vector>标准库 详解

`<vector>` 是 C++ 标准库提供的头文件之一，包含了 `std::vector` 类的定义，这是 C++ 中最常用的容器之一。

### `std::vector` 类

`std::vector` 是一个动态数组，它能够存储一系列同类型的元素，并且可以动态地调整其大小。以下是 `std::vector` 类的一些重要特性和函数：

1. **动态大小：** 向量的大小可以根据需要动态增长或缩小。通过 `push_back()` 在尾部添加元素、`pop_back()` 删除尾部元素，或者直接使用 `resize()` 调整大小。

2. **随机访问：** 可以通过索引快速访问和修改向量中的元素，支持使用 `operator[]` 实现随机访问。

3. **连续内存存储：** 向量中的元素在内存中是连续存储的，因此支持高效的随机访问，并且迭代器可用于遍历元素。

4. **内存管理：** 向量会自动处理内存的分配和释放，使得在尾部插入或删除元素的操作通常是高效的。

5. **元素访问：** 提供了 `at()` 方法和 `operator[]`，`front()` 和 `back()` 方法用于访问首尾元素。

6. **迭代器支持：** 支持使用迭代器进行遍历，如 `begin()` 和 `end()` 返回的迭代器用于遍历容器元素。

7. **其他方法：** 包括 `empty()`、`size()`、`clear()`、`erase()` 等方法用于检查空、获取大小、清空内容和删除元素等。

下面是一个简单示例，展示了如何使用 `<vector>` 中的 `std::vector`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个整数向量并初始化
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 在向量尾部添加元素
    vec.push_back(6);

    // 使用迭代器遍历输出向量中的元素
    std::cout << "Vector Elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

`<vector>` 头文件提供了 `std::vector` 类，它是一个常用的容器，能够满足动态数组的需求，支持高效的元素访问、插入和删除操作，是 C++ 中非常实用的数据结构之一。

## C++ <vector>标准库中 std::vector模板类详解

`std::vector` 是 C++ 标准库提供的动态数组容器，属于序列容器的一种。它以连续的内存空间存储元素，并支持动态增长和收缩。以下是 `std::vector` 的一些重要特性和使用方法：

### 特性：

1. **动态大小：** `std::vector` 允许在运行时根据需要动态地增加或减少其大小。通过 `push_back()` 在尾部添加元素，`pop_back()` 删除尾部元素，或者直接使用 `resize()` 调整大小。

2. **随机访问：** 可以通过索引快速访问和修改向量中的元素。支持使用 `operator[]` 实现随机访问，其时间复杂度为 O(1)。

3. **连续内存存储：** 向量的元素在内存中是连续存储的，这有助于提高数据的访问速度，并且迭代器可用于遍历元素。

4. **尾部插入和删除的高效性：** 在尾部插入或删除元素的操作通常是高效的，时间复杂度为平摊 O(1)。

5. **迭代器支持：** 提供了迭代器，如 `begin()` 和 `end()` 返回的迭代器用于遍历容器元素。

6. **元素访问：** 可以使用 `at()` 方法、`operator[]`、`front()` 和 `back()` 方法来访问元素。

7. **其他方法：** 包括 `empty()`、`size()`、`clear()`、`erase()` 等方法，用于检查空、获取大小、清空内容和删除元素等。

### 示例：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个整数向量并初始化
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 在向量尾部添加元素
    vec.push_back(6);

    // 使用迭代器遍历输出向量中的元素
    std::cout << "Vector Elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

以上代码演示了 `std::vector` 的一些常见操作，包括初始化、在尾部添加元素、迭代器遍历输出元素等。`std::vector` 是 C++ 标准库中常用的容器之一，提供了便捷且高效的动态数组功能。

## C++ <vector>标准库中 std::vector模板类所有成员函数

`std::vector` 类是 C++ 标准库中的动态数组容器，提供了许多成员函数用于管理其内部的元素。以下是 `std::vector` 类的一些主要成员函数：

### 容量相关操作：

- **`size()`：** 返回向量中元素的个数。
- **`capacity()`：** 返回当前向量的容量（即分配的内存大小）。
- **`empty()`：** 检查向量是否为空。
- **`reserve(size_type new_cap)`：** 尝试预分配足够的内存以存储指定数量的元素。

### 访问元素操作：

- **`operator[]`：** 通过索引访问向量中的元素。
- **`at(size_type pos)`：** 通过索引访问向量中的元素，提供了边界检查。
- **`front()`：** 返回向量中第一个元素的引用。
- **`back()`：** 返回向量中最后一个元素的引用。
- **`data()`：** 返回指向向量内部数组的指针。

### 修改容器内容操作：

- **`push_back(const T& value)`：** 在向量尾部添加一个元素。
- **`pop_back()`：** 删除向量中最后一个元素。
- **`insert(iterator pos, const T& value)`：** 在指定位置插入一个元素。
- **`erase(iterator pos)`：** 删除指定位置的元素。
- **`clear()`：** 删除向量中的所有元素。

### 其他操作：

- **`swap(vector& other)`：** 交换两个向量的内容。
- **`assign(count, value)`：** 用新值替换向量的内容。
- **`resize(size_type new_size)`：** 改变向量的大小。
- **`shrink_to_fit()`：** 要求释放多余的容量。

此外，`std::vector` 还具有迭代器相关的成员函数，如 `begin()`、`end()` 用于迭代访问容器的元素。以上列出的成员函数并非全部，但是是 `std::vector` 常用的一些成员函数，能够对向量的大小、容量、元素访问和修改等进行有效管理。

## C++ std::vector::swap() 函数 详解 

`std::vector::swap()` 是 C++ 标准库中 `std::vector` 类的成员函数，用于交换两个 vector 的内容，即交换它们所包含的元素。

### 函数签名：

```cpp
void swap(std::vector& x);
```

### 参数：

- `x`：另一个 `std::vector` 对象，其内容将与调用该函数的 vector 对象进行交换。

### 功能：

- `std::vector::swap()` 函数用于交换两个 vector 对象的元素内容，使得调用该函数的 vector 与参数 `x` 所包含的元素互换。

### 示例：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};

    std::cout << "Vector 1: ";
    for (int num : vec1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector 2: ";
    for (int num : vec2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    vec1.swap(vec2); // 交换两个 vector 的内容

    std::cout << "\nAfter Swap:" << std::endl;
    std::cout << "Vector 1: ";
    for (int num : vec1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector 2: ";
    for (int num : vec2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 注意事项：

- `std::vector::swap()` 函数非常高效，因为它只是交换了两个 vector 内部的数据结构指针，而不是复制每个元素。
- 交换后，两个 vector 对象的大小和容量可能会发生变化，但其所包含的元素会完全交换。
- 该函数是 `std::vector` 类的成员函数，所以需要使用一个已经存在的 vector 对象来调用该函数。

`std::vector::swap()` 是一个很有用的函数，特别是在需要交换两个 vector 的元素内容时，可以避免进行元素的逐个复制。