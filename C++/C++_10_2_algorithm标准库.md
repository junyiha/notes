## 简介

+ <algorithm>标准库学习笔记

## C++ <algorithm>是什么

`<algorithm>` 是 C++ 标准库中提供了一系列泛型算法的头文件。这些算法可以用于对数据结构（如数组、容器、迭代器等）执行各种操作，包括搜索、排序、合并、变换等。

这个头文件包含了许多标准的算法，这些算法都是泛型的，意味着它们不仅适用于特定类型的数据，而且可以用于不同的数据类型。这些算法可以直接用于标准容器（如 vector、list、deque 等）中，也可以用于普通数组、迭代器等容器类型。

以下是 `<algorithm>` 头文件中一些常用的算法：

1. **排序算法**：如 `std::sort`、`std::stable_sort`、`std::partial_sort`、`std::nth_element` 等，用于对元素序列进行排序。

2. **搜索算法**：例如 `std::find`、`std::binary_search`、`std::lower_bound`、`std::upper_bound` 等，用于在序列中查找元素。

3. **数值算法**：如 `std::accumulate`、`std::count`、`std::min`、`std::max`、`std::accumulate` 等，用于对数值序列执行操作。

4. **集合算法**：包括 `std::merge`、`std::set_intersection`、`std::set_union`、`std::set_difference` 等，用于对集合执行操作。

5. **变换算法**：例如 `std::transform`、`std::copy`、`std::reverse`、`std::rotate` 等，用于对序列执行变换。

6. **比较和交换算法**：如 `std::swap`、`std::swap_ranges`、`std::equal`、`std::lexicographical_compare` 等，用于比较和交换元素。

这些算法提供了许多常见的操作，可以方便地对数据进行处理和操作。使用 `<algorithm>` 中的这些函数，可以使得编写 C++ 代码更加简洁、高效和易于理解。

## C++ <algorithm>标准库 std::sort 详解

`std::sort` 是 C++ 标准库 `<algorithm>` 中的一个函数，用于对指定范围内的元素进行排序。它采用快速排序（Quick Sort）或者其他高效的排序算法来实现。

以下是 `std::sort` 函数的详细说明：

### 函数签名：

```cpp
template <class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last);

template <class RandomAccessIterator, class Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

### 参数：

- `first`：要排序范围的起始位置（可以是迭代器）。
- `last`：要排序范围的结束位置（不包括结束位置的元素）。
- `comp`（可选）：可选的比较函数对象，用于定义排序顺序。如果不提供此参数，则默认使用 `<` 运算符进行元素比较。

### 功能：

- `std::sort` 函数用于对迭代器范围 `[first, last)` 中的元素进行排序。该函数可以用于数组或标准库容器（如 vector、deque、list 等）。

- 默认情况下，`std::sort` 会按升序对元素进行排序，但也可以通过传递自定义的比较函数对象来定义其他排序顺序。

### 使用示例：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5};

    std::cout << "Original Vector: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::sort(vec.begin(), vec.end()); // 默认按升序排序

    std::cout << "Sorted Vector: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 注意事项：

- `std::sort` 函数可以对整数、浮点数、字符串、自定义类型等元素进行排序。
- 对于自定义类型，如果没有提供自定义的比较函数，需要确保该类型的 `<` 操作符或者提供了可供 `std::sort` 使用的比较函数。
- 对于自定义排序顺序，可以传递一个自定义的比较函数对象作为 `comp` 参数。

`std::sort` 是一个高效的排序算法，其时间复杂度通常为 O(n log n)，对大多数情况下的排序操作都能提供较好的性能。

## C++ <algorithm>标准库 std::sort 自定义类型排序

当你想要对自定义类型的对象进行排序时，你可以通过提供比较函数或者重载对象的 `<` 操作符来告诉 `std::sort` 如何进行排序。下面是一个示例，展示了如何在自定义类中使用 `std::sort` 进行排序：

假设有一个自定义的 `Person` 类，具有姓名和年龄字段，你想按照年龄对 `Person` 对象进行排序：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// 定义 Person 类
class Person {
public:
    std::string name;
    int age;

    Person(const std::string& n, int a) : name(n), age(a) {}

    // 重载小于运算符，按照年龄升序排序
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

int main() {
    // 创建 Person 对象的 vector
    std::vector<Person> people = {
        {"Alice", 25},
        {"Bob", 20},
        {"Charlie", 30},
        {"David", 22}
    };

    std::cout << "Original Order: " << std::endl;
    for (const auto& person : people) {
        std::cout << person.name << " - " << person.age << std::endl;
    }

    // 使用 std::sort 对 Person 对象按年龄升序排序
    std::sort(people.begin(), people.end());

    std::cout << "\nSorted by Age: " << std::endl;
    for (const auto& person : people) {
        std::cout << person.name << " - " << person.age << std::endl;
    }

    return 0;
}
```

在上述代码中，`Person` 类中重载了 `<` 操作符，根据 `age` 成员变量的值进行比较。然后在 `main` 函数中，使用 `std::sort` 对 `Person` 对象的 `std::vector` 按照年龄进行排序。

这个示例展示了如何使用 `std::sort` 进行自定义类型的对象排序，只需确保提供了适当的比较方法，无论是重载 `<` 运算符还是提供自定义的比较函数对象。

## C++ <algorithm>标准库 std::sort 自定义类型排序 提供比较函数

当使用 `std::sort` 对自定义类型进行排序时，你可以通过提供一个自定义的比较函数来定义排序规则。这个自定义的比较函数将告诉 `std::sort` 如何比较两个自定义类型的对象。下面是一个示例，展示了如何使用比较函数对自定义类型进行排序：

假设有一个自定义的 `Book` 类，包含书名和出版年份字段，你想按照出版年份对 `Book` 对象进行排序：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// 定义 Book 类
class Book {
public:
    std::string title;
    int year;

    Book(const std::string& t, int y) : title(t), year(y) {}
};

// 自定义比较函数，按照出版年份升序排序
bool compareByYear(const Book& a, const Book& b) {
    return a.year < b.year;
}

int main() {
    // 创建 Book 对象的 vector
    std::vector<Book> books = {
        {"Book A", 2000},
        {"Book B", 1995},
        {"Book C", 2010},
        {"Book D", 1980}
    };

    std::cout << "Original Order: " << std::endl;
    for (const auto& book : books) {
        std::cout << book.title << " - " << book.year << std::endl;
    }

    // 使用 std::sort 对 Book 对象按出版年份升序排序
    std::sort(books.begin(), books.end(), compareByYear);

    std::cout << "\nSorted by Year: " << std::endl;
    for (const auto& book : books) {
        std::cout << book.title << " - " << book.year << std::endl;
    }

    return 0;
}
```

在上述代码中，我们定义了一个 `compareByYear` 比较函数，该函数接受两个 `Book` 对象并根据它们的出版年份进行比较。然后在 `main` 函数中，我们使用 `std::sort` 对 `Book` 对象的 `std::vector` 按照出版年份进行排序，并将 `compareByYear` 函数作为第三个参数传递给 `std::sort`。

这个示例展示了如何使用比较函数对自定义类型的对象进行排序，只需提供一个符合条件的比较函数，即可告诉 `std::sort` 如何排序这些对象。