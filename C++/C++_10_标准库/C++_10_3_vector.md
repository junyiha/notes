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

## std::vector::size()

`std::vector::size()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于返回 `std::vector` 容器中当前存储元素的数量（大小）。

在 C++ 中，`std::vector` 是一个动态数组，它能够自动调整大小，可以根据需要动态地增加或减少存储在其中的元素数量。`size()` 函数返回的是当前 `std::vector` 中的元素数量，即容器中元素的个数。

下面是一个简单的示例演示了如何使用 `std::vector::size()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的 std::vector 容器
    std::vector<int> vec;

    // 向容器中添加一些元素
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // 获取容器中元素的数量（大小）
    std::cout << "Vector的大小为：" << vec.size() << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个空的 `std::vector<int>` 容器 `vec`。
- 使用 `push_back` 方法向容器中添加了三个整数元素。
- 通过 `vec.size()` 获取了 `vec` 容器中元素的数量，并将结果打印出来。

`std::vector::size()` 对于获取 `std::vector` 中元素数量非常方便，它可以帮助你确定容器中元素的个数，从而进行后续的操作或逻辑处理。

## std::vector::capacity()

`std::vector::capacity()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于返回当前 `std::vector` 容器的容量大小。

在 C++ 中，`std::vector` 是一个动态数组，它能够自动调整大小，可以根据需要动态地增加或减少存储在其中的元素数量。`capacity()` 函数返回的是当前 `std::vector` 内部所分配内存空间的大小，即该容器在不分配新的内存的情况下能够容纳的元素数量。

下面是一个简单的示例演示了如何使用 `std::vector::capacity()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的 std::vector 容器
    std::vector<int> vec;

    // 向容器中添加一些元素
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
        std::cout << "Size: " << vec.size() << " Capacity: " << vec.capacity() << std::endl;
    }

    return 0;
}
```

在这个示例中：

- 创建了一个空的 `std::vector<int>` 容器 `vec`。
- 使用 `push_back` 方法向容器中循环添加了十个整数元素，并在每次添加后打印了当前容器的大小和容量。

`std::vector::capacity()` 是一个重要的函数，它可以用来观察 `std::vector` 容器当前的内存分配情况。当 `std::vector` 中的元素数量超过当前分配的容量时，`std::vector` 会自动重新分配更大的内存空间以容纳更多的元素，这个过程可能会导致容器大小和容量之间的不同步。

## std::vector::empty()

`std::vector::empty()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于检查 `std::vector` 容器是否为空。

当 `std::vector` 容器中不含有任何元素时，即容器的大小为零时，`empty()` 函数将返回 `true`；否则，如果容器中包含至少一个元素，则返回 `false`。

以下是一个简单的示例演示了如何使用 `std::vector::empty()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的 std::vector 容器
    std::vector<int> vec;

    // 检查容器是否为空
    if (vec.empty()) {
        std::cout << "容器为空" << std::endl;
    } else {
        std::cout << "容器不为空" << std::endl;
    }

    // 向容器中添加一个元素
    vec.push_back(10);

    // 再次检查容器是否为空
    if (vec.empty()) {
        std::cout << "容器为空" << std::endl;
    } else {
        std::cout << "容器不为空" << std::endl;
    }

    return 0;
}
```

在这个示例中：

- 创建了一个空的 `std::vector<int>` 容器 `vec`。
- 使用 `vec.empty()` 检查容器是否为空，并根据返回结果打印相应的消息。
- 使用 `push_back` 方法向容器中添加了一个整数元素。
- 再次使用 `vec.empty()` 检查容器是否为空，并根据返回结果打印相应的消息。

`std::vector::empty()` 是一个简单而常用的函数，用于确定 `std::vector` 容器是否为空，可以在需要检查容器是否含有元素时使用。

## std::vector::reserve()

`std::vector::reserve()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于预留 `std::vector` 容器的存储空间，但不会改变容器中元素的数量。

当你预先知道 `std::vector` 将要存储大量元素时，可以使用 `reserve()` 函数来预留足够的内存空间，避免多次重新分配内存，从而提高程序的性能。

以下是一个简单的示例演示了如何使用 `std::vector::reserve()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的 std::vector 容器
    std::vector<int> vec;

    // 打印容器当前的大小和容量
    std::cout << "当前大小: " << vec.size() << " 当前容量: " << vec.capacity() << std::endl;

    // 预留容器存储空间为 10 个元素
    vec.reserve(10);

    // 打印预留后的容器当前的大小和容量
    std::cout << "预留后大小: " << vec.size() << " 预留后容量: " << vec.capacity() << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个空的 `std::vector<int>` 容器 `vec`。
- 使用 `vec.reserve(10)` 预留了容器的存储空间为 10 个元素。
- 打印了预留前后容器的大小和容量。

需要注意的是，`reserve()` 函数只是预留了足够的存储空间，并没有改变容器的实际大小，容器的大小仍然是 0。容器的大小由实际插入的元素个数决定，而容器的容量则是实际分配的内存大小，`reserve()` 仅仅是为容器预留了更多的内存空间，以备将来的使用。

这个函数通常在你已经知道将要存储大量元素的情况下使用，以减少因重新分配内存而引起的开销。

## std::vector::at()

`std::vector::at()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于访问 `std::vector` 容器中指定位置的元素，并提供了边界检查。

与 `operator[]` 不同，`at()` 函数在访问容器元素时提供了边界检查，如果指定的位置超出了容器的范围，则会抛出 `std::out_of_range` 异常。

以下是一个简单的示例演示了如何使用 `std::vector::at()`：

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30, 40, 50};

    try {
        // 使用 at() 访问容器中的元素
        std::cout << "元素 at(2): " << vec.at(2) << std::endl; // 访问索引为 2 的元素
        std::cout << "元素 at(5): " << vec.at(5) << std::endl; // 尝试访问超出范围的索引
    }
    catch (const std::out_of_range& ex) {
        std::cout << "发生异常: " << ex.what() << std::endl; // 捕获并打印 out_of_range 异常信息
    }

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.at(2)` 获取了索引为 2 的元素值，并正常打印出来。
- 然后尝试使用 `vec.at(5)` 访问超出容器范围的索引，这会导致 `std::out_of_range` 异常被抛出，并被 `catch` 语句捕获并处理。

总的来说，`std::vector::at()` 是一个安全的访问元素的方法，可以在需要对访问进行边界检查的情况下使用，以防止意外访问超出容器范围的索引位置。

## std::vector::front()

`std::vector::front()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于返回 `std::vector` 容器中第一个元素的引用。

它提供了对 `std::vector` 容器中第一个元素的访问，类似于数组的第一个元素。如果 `std::vector` 容器为空，则调用 `front()` 函数将会导致未定义行为。

以下是一个简单的示例演示了如何使用 `std::vector::front()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // 访问容器中的第一个元素
    std::cout << "第一个元素是: " << vec.front() << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.front()` 获取了容器中的第一个元素值，并将其打印出来。

需要注意的是，调用 `std::vector::front()` 函数时，应确保 `std::vector` 容器不为空，否则在空容器上调用 `front()` 将导致未定义行为。因此，在调用 `front()` 函数之前，最好先检查 `std::vector` 是否包含元素，可以通过 `empty()` 函数进行检查。

## std::vector::back()

`std::vector::back()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于返回 `std::vector` 容器中最后一个元素的引用。

它提供了对 `std::vector` 容器中最后一个元素的访问。如果 `std::vector` 容器为空，则调用 `back()` 函数将会导致未定义行为。

以下是一个简单的示例演示了如何使用 `std::vector::back()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // 访问容器中的最后一个元素
    std::cout << "最后一个元素是: " << vec.back() << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.back()` 获取了容器中的最后一个元素值，并将其打印出来。

需要注意的是，调用 `std::vector::back()` 函数时，应确保 `std::vector` 容器不为空，否则在空容器上调用 `back()` 将导致未定义行为。因此，在调用 `back()` 函数之前，最好先检查 `std::vector` 是否包含元素，可以通过 `empty()` 函数进行检查。

## std::vector::data()

`std::vector::data()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于返回指向 `std::vector` 容器内部存储元素的指针。

这个函数返回一个指向 `std::vector` 内部数据存储区的指针，该指针可以用于直接访问容器中的元素。如果 `std::vector` 容器为空，则返回的指针可能为空指针。

以下是一个简单的示例演示了如何使用 `std::vector::data()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // 获取指向容器数据的指针
    int* ptr = vec.data();

    // 打印指针指向的元素
    std::cout << "第一个元素是: " << *ptr << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.data()` 获取了指向容器数据存储区的指针，并将其赋值给 `ptr`。
- 打印了指针所指向的第一个元素的值。

需要注意的是，`std::vector::data()` 返回的指针可以用于直接访问容器中的元素，但在修改容器中的元素时应格外小心，确保不会越界或者引起其它未定义的行为。此外，如果 `std::vector` 容器为空，则返回的指针可能为 `nullptr`。

## std::vector::push_back()

`std::vector::push_back()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于在 `std::vector` 容器的末尾添加一个新的元素。

这个函数将新的元素添加到 `std::vector` 容器的末尾，并使容器的大小增加 1。如果 `std::vector` 的容量不足以容纳新元素，则会自动重新分配更大的内存空间以适应新的元素。

以下是一个简单的示例演示了如何使用 `std::vector::push_back()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的 std::vector 容器
    std::vector<int> vec;

    // 向容器中添加一些元素
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // 打印容器中的元素
    std::cout << "容器中的元素: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个空的 `std::vector<int>` 容器 `vec`。
- 使用 `push_back()` 方法向容器中分别添加了三个整数元素。
- 使用循环遍历容器中的元素，并将它们打印出来。

`std::vector::push_back()` 是一个常用的函数，用于向 `std::vector` 容器的末尾添加新的元素，非常方便实用。

## std::vector::pop_back()

`std::vector::pop_back()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于移除 `std::vector` 容器中的最后一个元素。

该函数会将 `std::vector` 容器中最后一个元素移除，并且减少容器的大小（size）1。如果 `std::vector` 容器为空，则调用 `pop_back()` 函数将导致未定义行为。

以下是一个简单的示例演示了如何使用 `std::vector::pop_back()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // 移除容器中的最后一个元素
    vec.pop_back();

    // 打印容器中的元素
    std::cout << "移除后的容器中的元素: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.pop_back()` 移除了容器中的最后一个元素。
- 使用循环遍历容器中的元素，并将它们打印出来。

需要注意的是，调用 `std::vector::pop_back()` 之前最好检查容器是否为空，以避免在空容器上调用该函数而导致的未定义行为。这个函数通常用于从 `std::vector` 容器的末尾删除元素，可以方便地实现栈（stack）等数据结构的功能。

## std::vector::insert()

`std::vector::insert()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于在指定位置插入一个或多个元素到 `std::vector` 容器中。

这个函数允许在指定位置插入一个元素或一组元素。插入操作可能会导致所有在指定位置之后的元素被移动，因为 `std::vector` 是一个连续存储的容器。

下面是 `std::vector::insert()` 函数的基本语法：

```cpp
iterator insert (iterator position, const T& val); // 在 position 位置插入 val
iterator insert (iterator position, size_type n, const T& val); // 在 position 位置插入 n 个 val
iterator insert (iterator position, InputIterator first, InputIterator last); // 在 position 位置插入区间 [first, last) 内的元素
```

这里的 `position` 参数是一个迭代器，指示了插入元素的位置。`val` 是要插入的元素值，`n` 是要插入的元素数量，`first` 和 `last` 是表示要插入的元素范围的迭代器。

以下是一个简单的示例演示了如何使用 `std::vector::insert()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30};

    // 在容器的第二个位置插入一个元素 25
    auto it = vec.insert(vec.begin() + 1, 25);

    // 在容器的末尾插入两个元素，值分别为 40 和 50
    vec.insert(vec.end(), {40, 50});

    // 打印容器中的元素
    std::cout << "容器中的元素: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.insert(vec.begin() + 1, 25)` 在容器的第二个位置插入了一个值为 25 的元素。
- 使用 `vec.insert(vec.end(), {40, 50})` 在容器的末尾插入了两个值为 40 和 50 的元素。
- 使用循环遍历容器中的元素，并将它们打印出来。

`std::vector::insert()` 函数允许在 `std::vector` 容器的指定位置插入一个或多个元素，提供了灵活且方便的插入操作。

## std::vector::erase()

`std::vector::erase()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于从 `std::vector` 容器中移除一个或一段元素。

这个函数有多种用法，它可以删除单个元素，也可以删除一个范围内的元素。删除操作可能会导致被移除元素后面的元素向前移动，因为 `std::vector` 是一个连续存储的容器。

下面是 `std::vector::erase()` 函数的基本语法：

```cpp
iterator erase (iterator position); // 移除指定位置的元素
iterator erase (iterator first, iterator last); // 移除位于 [first, last) 区间的元素
```

这里的 `position` 是要移除的元素的位置的迭代器，`first` 和 `last` 表示一个范围，用来移除这个范围内的所有元素。

以下是一个简单的示例演示了如何使用 `std::vector::erase()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // 移除容器中的第二个元素
    vec.erase(vec.begin() + 1);

    // 移除容器中的第三个到第四个元素（迭代器范围 [vec.begin() + 2, vec.begin() + 4)）
    vec.erase(vec.begin() + 2, vec.begin() + 4);

    // 打印容器中的元素
    std::cout << "容器中的元素: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.erase(vec.begin() + 1)` 移除了容器中的第二个元素。
- 使用 `vec.erase(vec.begin() + 2, vec.begin() + 4)` 移除了容器中的第三个到第四个元素。
- 使用循环遍历容器中的元素，并将它们打印出来。

`std::vector::erase()` 函数允许从 `std::vector` 容器中移除指定位置或指定范围内的元素，提供了便捷的删除操作。

## std::vector::clear()

`std::vector::clear()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于清空 `std::vector` 容器中的所有元素。

当调用 `clear()` 函数时，`std::vector` 容器的大小变为零，即移除了容器中的所有元素。容器的内存空间不会被释放，但容器中的元素数量将变为零，即容器会变为空。

以下是一个简单的示例演示了如何使用 `std::vector::clear()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // 打印清空前容器中的元素数量
    std::cout << "清空前容器的大小: " << vec.size() << std::endl;

    // 清空容器
    vec.clear();

    // 打印清空后容器中的元素数量
    std::cout << "清空后容器的大小: " << vec.size() << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `vec.size()` 打印了清空前容器中的元素数量。
- 使用 `vec.clear()` 清空了容器中的所有元素。
- 再次使用 `vec.size()` 打印了清空后容器中的元素数量，这时应该为 0。

`std::vector::clear()` 函数是一种快速清空 `std::vector` 容器中的元素的方法，但并不释放容器的内存空间，仅将容器的大小设置为零，使得容器变为空。

## std::vector::swap()

`std::vector::swap()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于交换两个 `std::vector` 容器的内容。

这个函数接受另一个 `std::vector` 容器作为参数，并将调用它的容器和传入的容器进行内容交换。交换操作将使得两个容器中的元素互相交换，但它们的内存空间不会发生改变。

以下是 `std::vector::swap()` 函数的基本用法：

```cpp
void swap(vector& other);
```

这里的 `other` 是另一个 `std::vector` 容器，它的内容将与调用函数的容器进行交换。

以下是一个简单的示例演示了如何使用 `std::vector::swap()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建两个 std::vector 容器，并分别向其中添加一些元素
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};

    // 打印交换前两个容器中的元素
    std::cout << "交换前 vec1 中的元素: ";
    for (const auto& element : vec1) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "交换前 vec2 中的元素: ";
    for (const auto& element : vec2) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 使用 swap() 函数交换两个容器的内容
    vec1.swap(vec2);

    // 打印交换后两个容器中的元素
    std::cout << "交换后 vec1 中的元素: ";
    for (const auto& element : vec1) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "交换后 vec2 中的元素: ";
    for (const auto& element : vec2) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了两个 `std::vector<int>` 容器 `vec1` 和 `vec2`，并初始化了一些整数元素。
- 使用 `vec1.swap(vec2)` 对两个容器的内容进行了交换。
- 分别打印了交换前后两个容器中的元素。

`std::vector::swap()` 函数提供了一种快速交换两个 `std::vector` 容器内容的方法，不需要复制元素，只需交换指针。这对于需要在两个容器间交换数据时非常有用。

## std::vector::assign()

`std::vector::assign()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于重新分配 `std::vector` 容器的内容。

这个函数可以使用多种方式重新设置 `std::vector` 容器的内容：可以用新值替换已有的内容，也可以设置容器中的元素数量，或者使用一个范围内的值替换容器中的元素。

以下是 `std::vector::assign()` 函数的不同形式及其基本用法：

```cpp
void assign(size_type count, const T& value); // 设置容器中元素的数量为 count，并用 value 值替换所有元素
template <class InputIterator>
void assign(InputIterator first, InputIterator last); // 使用区间 [first, last) 内的元素替换容器的内容
void assign(std::initializer_list<T> il); // 使用初始化列表 il 内的元素替换容器的内容
```

这里的 `count` 表示新的元素数量，`value` 是要赋给新元素的值。`first` 和 `last` 是迭代器，表示一个范围，用来替换容器的内容。`il` 是一个初始化列表，用来替换容器的内容。

以下是一个简单的示例演示了如何使用 `std::vector::assign()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的 std::vector 容器
    std::vector<int> vec;

    // 使用 assign() 设置容器中的元素数量为 5，并用值 10 替换所有元素
    vec.assign(5, 10);

    // 打印容器中的元素
    std::cout << "容器中的元素: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个空的 `std::vector<int>` 容器 `vec`。
- 使用 `vec.assign(5, 10)` 设置容器中的元素数量为 5，并用值 10 替换了所有元素。
- 使用循环遍历容器中的元素，并将它们打印出来。

`std::vector::assign()` 函数提供了多种方式来重新设置 `std::vector` 容器的内容，使得容器可以被不同类型的数据重新填充。

## std::vector::resize()

`std::vector::resize()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于改变 `std::vector` 容器中的元素数量。

这个函数允许你改变 `std::vector` 容器中元素的数量。如果新的大小比当前大小大，将会增加元素数量并用默认构造函数的值初始化新的元素。如果新的大小比当前大小小，将会删除超出新大小的元素。

以下是 `std::vector::resize()` 函数的基本语法：

```cpp
void resize(size_type count); // 设置容器中的元素数量为 count
void resize(size_type count, const value_type& value); // 设置容器中的元素数量为 count，并用 value 值初始化新元素
```

这里的 `count` 是指定的新的元素数量，`value` 是可选的值，用于初始化新添加的元素。

以下是一个简单的示例演示了如何使用 `std::vector::resize()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的 std::vector 容器
    std::vector<int> vec;

    // 使用 resize() 设置容器中的元素数量为 5
    vec.resize(5);

    // 打印容器中的元素
    std::cout << "容器中的元素: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 使用 resize() 设置容器中的元素数量为 8，并用值 100 初始化新添加的元素
    vec.resize(8, 100);

    // 再次打印容器中的元素
    std::cout << "调整大小后的容器中的元素: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个空的 `std::vector<int>` 容器 `vec`。
- 使用 `vec.resize(5)` 设置容器中的元素数量为 5，默认使用默认构造函数进行初始化。
- 使用 `vec.resize(8, 100)` 将容器中的元素数量增加到 8，并用值 100 初始化新添加的元素。
- 分别使用循环遍历容器中的元素，并将它们打印出来。

`std::vector::resize()` 函数允许你在运行时动态调整 `std::vector` 容器的大小，并可以选择性地使用特定的值初始化新添加的元素。

## std::vector::shrink_to_fit()

`std::vector::shrink_to_fit()` 是 C++ 标准库中 `std::vector` 类的一个成员函数，用于要求 `std::vector` 容器减小其容量，使其容量和大小相匹配。

`std::vector` 容器会根据需要分配更多的内存空间以容纳新的元素。然而，当一些元素被删除后，`std::vector` 容器的实际大小可能小于其容量。`shrink_to_fit()` 函数就是用来释放容器多余的内存空间，将容器的容量减小到与其大小相匹配。

以下是 `std::vector::shrink_to_fit()` 函数的基本语法：

```cpp
void shrink_to_fit();
```

这个函数没有参数，调用它将使 `std::vector` 容器的容量减小到和当前元素数量相匹配的大小。但并不保证一定会成功减小容器的容量，因为具体实现可能会有所不同。

以下是一个简单的示例演示了如何使用 `std::vector::shrink_to_fit()`：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个 std::vector 容器，并向其中添加一些元素
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 移除容器中的最后两个元素
    vec.pop_back();
    vec.pop_back();

    // 调用 shrink_to_fit() 函数将容器的容量减小到与其大小相匹配
    vec.shrink_to_fit();

    // 打印容器的大小和容量
    std::cout << "容器的大小: " << vec.size() << std::endl;
    std::cout << "容器的容量: " << vec.capacity() << std::endl;

    return 0;
}
```

在这个示例中：

- 创建了一个 `std::vector<int>` 容器 `vec`，并初始化了一些整数元素。
- 使用 `pop_back()` 移除了容器中的最后两个元素。
- 使用 `shrink_to_fit()` 函数将容器的容量减小到与其大小相匹配。
- 使用 `size()` 和 `capacity()` 分别打印了容器的大小和容量。

`std::vector::shrink_to_fit()` 函数提供了一种手段来释放 `std::vector` 容器内多余的内存空间，使得容器的实际容量与其大小相匹配。但并不保证一定会成功减小容器的容量，具体情况取决于实现。

## std::vector::emplace_back() 函数 详解

`std::vector::emplace_back()` 是 C++ 中 `std::vector` 容器提供的一个函数，用于在容器的末尾直接构造元素，而不是先创建一个临时对象再进行拷贝或移动操作。这个函数允许你在容器中就地构造对象，从而避免额外的拷贝或移动开销。

以下是 `std::vector::emplace_back()` 的详细解释：

```cpp
namespace std {

template <class... Args>
void emplace_back(Args&&... args);

} // namespace std
```

- `emplace_back` 函数接受任意数量的参数，并将这些参数传递给容器中元素的构造函数，用于在容器的末尾直接构造一个新元素。

- 参数 `Args&&... args` 是一个可变参数模板，可以接受任意数量的参数。

使用 `emplace_back` 的典型用法是，直接在容器末尾构造一个元素，而不需要在代码中创建临时对象。这对于避免额外的拷贝或移动操作特别有用。

以下是一个简单的示例：

```cpp
#include <iostream>
#include <vector>

struct MyClass {
    int value;

    MyClass(int v) : value(v) {
        std::cout << "Constructing MyClass with value: " << value << std::endl;
    }
};

int main() {
    std::vector<MyClass> myVector;

    // 使用 emplace_back 直接在容器末尾构造元素
    myVector.emplace_back(42);

    // 使用 emplace_back 可以避免额外的拷贝或移动操作

    return 0;
}
```

在这个例子中，`emplace_back` 直接在 `std::vector` 的末尾构造了一个 `MyClass` 对象，而不需要先创建一个临时对象再进行拷贝操作。这样可以提高效率，特别是对于那些不支持移动语义的类。

## C++ std::vector 拷贝构造函数 详解

在 C++ 中，`std::vector` 是一个动态数组，它提供了在运行时大小可以动态变化的数组容器。拷贝构造函数是一种特殊的构造函数，用于创建一个对象的副本。`std::vector` 的拷贝构造函数用于创建一个新的 `std::vector` 对象，其元素与另一个 `std::vector` 对象完全相同。

以下是 `std::vector` 的拷贝构造函数的详细解释：

```cpp
// 默认构造函数
vector(const vector& other);
```

拷贝构造函数采用另一个 `std::vector` 对象作为参数，并创建一个新的 `std::vector` 对象，其中包含与参数相同的元素。这个构造函数通过复制另一个 `std::vector` 对象的所有元素来构造新的对象。

拷贝构造函数通常在以下情况下被调用：
1. 用一个 `std::vector` 对象初始化另一个 `std::vector` 对象。
2. 作为函数参数传递 `std::vector` 对象。
3. 从函数返回 `std::vector` 对象时。

下面是一个简单的示例，展示了如何使用拷贝构造函数：

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个原始的 std::vector 对象
    std::vector<int> originalVector = {1, 2, 3, 4, 5};

    // 使用拷贝构造函数创建一个新的 std::vector 对象
    std::vector<int> copiedVector(originalVector);

    // 输出新的 std::vector 对象的元素
    for (int i : copiedVector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在上面的示例中，`copiedVector` 对象使用了原始向量 `originalVector` 的拷贝构造函数创建了一个副本。