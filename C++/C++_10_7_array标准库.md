## 简介

+ C++ <array>标准库笔记

## C++ <array>标准库 详解

`<array>` 标准库提供了 `std::array` 类模板，用于表示固定大小的数组。以下是一些关键点：

1. **固定大小：** `std::array` 的大小在创建时确定，并且无法改变。
2. **内存分配：** 与内置数组类似，`std::array` 在栈上分配内存，因此大小必须在编译时确定。
3. **元素访问：** 与内置数组类似，可以使用下标操作符 `[]` 来访问元素。也可以使用 `at()` 函数进行安全的边界检查。
4. **迭代器支持：** 提供迭代器支持，可以使用迭代器来遍历数组。
5. **容器功能：** 支持一些容器方法，如 `size()`、`empty()` 等。
6. **数组间的比较：** 支持数组之间的比较操作，可以使用 `==`、`!=`、`<`、`>` 等运算符进行比较。
7. **类型安全：** 提供了类型安全的数组访问和操作，因此可以更轻松地避免指针错误和越界访问。

使用 `std::array` 可以简化对数组的管理和操作，提供更多的安全性和方便性，是 C++ 中常用的容器之一。

## C++ <array>标准库常用函数

`<array>` 标准库中的 `std::array` 类提供了一些常用的函数和方法，以下是其中一些常见的：

1. **`at()`：** 以安全的方式访问指定位置的元素，并进行边界检查，如果索引超出范围，则抛出 `std::out_of_range` 异常。

2. **`operator[]`：** 使用下标操作符 `[]` 访问数组的特定元素。不进行边界检查，因此需要确保索引在合法范围内。

3. **`front()` 和 `back()`：** 分别返回数组的第一个元素和最后一个元素。

4. **`data()`：** 返回指向数组第一个元素的指针。

5. **`fill()`：** 将数组中的所有元素设置为特定的值。

6. **`empty()`：** 检查数组是否为空，即大小是否为零。

7. **`size()`：** 返回数组中元素的数量。

8. **`swap()`：** 交换两个数组的内容。

这些函数和方法使得 `std::array` 更加方便和易于使用，可以轻松地进行数组的访问、操作和管理。

## std::array::operator[]

`std::array::operator[]` 是 `std::array` 类中重载的下标访问操作符。它允许像普通数组一样使用 `[]` 运算符来访问数组中特定位置的元素，但不进行边界检查。

与 `std::array::at()` 不同，`std::array::operator[]` 不会检查索引是否超出数组边界。因此，如果使用 `[]` 运算符访问超出数组范围的索引，将导致未定义行为，可能会读取到未知的内存或导致程序崩溃。

示例代码如下：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    int value = arr[2]; // 访问数组索引为 2 的元素
    std::cout << "Value at index 2: " << value << std::endl;

    // 访问超出数组范围的索引，这可能导致未定义行为
    int out_of_range_value = arr[7];
    std::cout << "Value at index 7: " << out_of_range_value << std::endl; // 可能导致程序崩溃或未定义行为

    return 0;
}
```

在上面的例子中，`arr[2]` 访问了数组索引为 2 的元素，而 `arr[7]` 尝试访问了超出数组范围的索引。请注意，访问超出范围的索引可能会导致程序运行时的不可预测行为。

## std::array::front()

`std::array::front()` 是 `std::array` 类提供的成员函数之一，用于获取数组的第一个元素。

它类似于 `std::array` 的下标访问方式，但是 `front()` 更直观和语义化，专门用于访问数组的第一个元素。这个函数对于代码的可读性很有帮助，因为它清晰地表达了获取数组第一个元素的意图。

示例代码如下：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    int first_element = arr.front(); // 获取数组的第一个元素
    std::cout << "The first element is: " << first_element << std::endl;

    return 0;
}
```

在上述示例中，`arr.front()` 获取了数组 `arr` 的第一个元素，并将其存储在 `first_element` 变量中，然后将其打印输出。

## std::array::back

`std::array::back()` 是 `std::array` 类提供的成员函数之一，用于获取数组的最后一个元素。

与 `std::array::front()` 类似，`std::array::back()` 专门用于获取数组的最后一个元素，这样可以更清晰地表达获取最后一个元素的意图，提高代码的可读性。

以下是一个示例代码：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    int last_element = arr.back(); // 获取数组的最后一个元素
    std::cout << "The last element is: " << last_element << std::endl;

    return 0;
}
```

在上述示例中，`arr.back()` 获取了数组 `arr` 的最后一个元素，并将其存储在 `last_element` 变量中，然后将其打印输出。

## std::array::data()

`std::array::data()` 是 `std::array` 类提供的成员函数之一，用于获取指向数组首元素的指针。

它返回一个指向数组中第一个元素的指针，允许直接访问数组的底层数据。这个函数在需要以 C 风格的函数或需要传递数组数据的情况下很有用，因为它提供了指向数组数据的指针。

以下是一个示例代码：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    int* ptr = arr.data(); // 获取指向数组首元素的指针
    std::cout << "First element of the array: " << *ptr << std::endl;

    return 0;
}
```

在上述示例中，`arr.data()` 返回指向数组 `arr` 第一个元素的指针，并将其存储在 `ptr` 变量中。然后，`*ptr` 打印出指针所指向的第一个元素的值。

## std::array::fill()

`std::array::fill()` 是 `std::array` 类提供的成员函数之一，用于将数组中的所有元素设置为特定的值。

这个函数接受一个参数，用来指定要填充到数组中的值。调用 `fill()` 函数会将数组中的所有元素都设置为该指定值。

以下是一个示例代码：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    arr.fill(0); // 将数组中的所有元素设置为 0

    std::cout << "Array after filling with 0s: ";
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在上述示例中，`arr.fill(0)` 调用将数组 `arr` 中的所有元素都设置为 0。然后使用循环遍历数组并打印出填充后的数组元素。

## std::array::empty()

`std::array::empty()` 是 `std::array` 类提供的成员函数之一，用于检查数组是否为空。

对于 `std::array` 类型，它的大小是在编译时确定的，因此不会存在空数组的情况。`empty()` 函数对于 `std::array` 始终会返回 `false`，因为它不具备动态大小调整的能力，数组的大小在创建时已经固定。

下面是一个示例代码，展示了 `empty()` 函数的使用：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    if (arr.empty()) {
        std::cout << "Array is empty." << std::endl;
    } else {
        std::cout << "Array is not empty." << std::endl;
    }

    return 0;
}
```

尽管调用 `empty()` 函数并不会报错，但对于 `std::array` 类型，它永远返回 `false`，因为该类型的数组大小在创建时就被确定了，不允许为空。

## std::array::size()

`std::array::size()` 是 `std::array` 类提供的成员函数之一，用于获取数组中元素的数量。

它返回 `std::array` 中的元素个数，这个值是在编译时确定的，因为 `std::array` 是一个固定大小的数组容器。

以下是一个示例代码：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    std::cout << "Size of the array: " << arr.size() << std::endl;

    return 0;
}
```

在上述示例中，`arr.size()` 返回数组 `arr` 中元素的数量，即 5。这个函数对于确定数组的大小非常方便，可以在不需要硬编码数组大小的情况下获得数组的实际大小。

## std::array::swap()

`std::array::swap()` 是 `std::array` 类提供的成员函数之一，用于交换两个数组的内容。

这个函数接受另一个 `std::array` 作为参数，并交换调用该函数的数组对象和传入的数组对象的内容。要注意的是，这两个数组必须具有相同的大小和类型。

以下是一个示例代码：

```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    std::array<int, 5> arr2 = {10, 20, 30, 40, 50};

    std::cout << "Array 1 before swap:";
    for (int element : arr1) {
        std::cout << " " << element;
    }
    std::cout << std::endl;

    std::cout << "Array 2 before swap:";
    for (int element : arr2) {
        std::cout << " " << element;
    }
    std::cout << std::endl;

    arr1.swap(arr2); // 交换两个数组的内容

    std::cout << "Array 1 after swap:";
    for (int element : arr1) {
        std::cout << " " << element;
    }
    std::cout << std::endl;

    std::cout << "Array 2 after swap:";
    for (int element : arr2) {
        std::cout << " " << element;
    }
    std::cout << std::endl;

    return 0;
}
```

在上述示例中，`arr1` 和 `arr2` 的内容被交换。`arr1.swap(arr2)` 将数组 `arr1` 和 `arr2` 的内容互换，使得 `arr1` 包含原来的 `arr2` 内容，`arr2` 包含原来的 `arr1` 内容。