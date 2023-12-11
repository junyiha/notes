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

## STL 常用算法

STL（Standard Template Library）提供了许多常用的算法，这些算法分为多个类别，涵盖了各种操作，包括查找、排序、转换等。下面是一些常用的STL算法：

1. **非修改序列操作**：
   - `std::for_each`: 对容器中的每个元素执行指定操作。
   - `std::count`: 统计容器中满足指定条件的元素个数。
   - `std::find`: 在容器中查找指定元素，并返回第一个匹配到的位置。
   - `std::count_if`: 统计容器中满足指定条件的元素个数。

2. **修改序列操作**：
   - `std::copy`: 将一个容器中的元素复制到另一个容器中。
   - `std::transform`: 对容器中的元素应用指定的操作，并将结果存储到另一个容器中。
   - `std::replace`: 将容器中的指定值替换为另一个值。
   - `std::fill`: 将容器中的元素设置为指定值。

3. **排序和查找操作**：
   - `std::sort`: 对容器中的元素进行排序。
   - `std::binary_search`: 在已排序的容器中进行二分查找。
   - `std::merge`: 合并两个已排序的序列到一个新序列中。

4. **数值操作**：
   - `std::accumulate`: 对容器中的元素进行累积操作。
   - `std::min_element` / `std::max_element`: 找到容器中最小或最大的元素。
   - `std::inner_product`: 计算两个容器的内积。

这些算法仅是STL提供的众多算法中的一部分。它们都在 `<algorithm>` 头文件中定义。通过使用这些算法，可以简化代码并提高程序的效率，因为它们提供了可靠且经过优化的实现。

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

## std::for_each

`std::for_each` 是C++ STL提供的算法之一，用于对容器中的每个元素执行指定的操作。它允许你指定一个函数或者函数对象（也称为函数符或仿函数），然后对容器中的每个元素都应用这个函数。

`std::for_each` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// 一个函数对象（仿函数），用于输出容器中的元素
struct Print {
    void operator()(int elem) const {
        std::cout << elem << " ";
    }
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 std::for_each 对容器中的每个元素应用 Print 函数对象
    std::for_each(numbers.begin(), numbers.end(), Print());

    return 0;
}
```

在这个例子中，`Print` 是一个函数对象（仿函数），它重载了`operator()`来实现对容器中元素的输出操作。然后，`std::for_each` 将容器`numbers`中的每个元素传递给`Print()`，即函数对象的实例，最终实现对每个元素的输出。

你也可以使用 lambda 表达式作为 `std::for_each` 的参数，而无需定义函数对象：

```cpp
std::for_each(numbers.begin(), numbers.end(), [](int elem) {
    std::cout << elem << " ";
});
```

`std::for_each` 提供了一种简洁而有效的方式来对容器中的元素进行操作，适用于许多不同的场景，能够更轻松地处理容器元素。

## std::count

`std::count` 是C++ STL中的一个算法，用于计算容器中满足特定条件的元素个数。它接受两个迭代器参数，表示要进行计数的范围，以及一个要匹配的特定值。

`std::count` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 2, 3, 2, 4, 2, 5};

    // 计算容器中值为 2 的元素个数
    int countOfTwos = std::count(numbers.begin(), numbers.end(), 2);

    std::cout << "The count of 2s in the vector: " << countOfTwos << std::endl;

    return 0;
}
```

在这个例子中，`std::count` 被用来计算容器 `numbers` 中值为 2 的元素个数。它接收了三个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，以及要计数的特定值 2。最后，它返回匹配特定值的元素数量。

除了基本的数值比较外，`std::count` 也可以通过 lambda 表达式实现更加灵活的条件计数，例如：

```cpp
// 计算容器中大于 3 的元素个数
int countGreaterThanThree = std::count_if(numbers.begin(), numbers.end(), [](int x) {
    return x > 3;
});
```

这将返回容器 `numbers` 中大于 3 的元素的数量。`std::count_if` 允许你通过 lambda 表达式指定更复杂的条件来计数满足特定条件的元素个数。

## std::find

`std::find` 是C++ STL中的一个算法，用于在容器中查找特定值，并返回指向第一个匹配到的元素的迭代器。如果未找到匹配的元素，则返回指向容器末尾的迭代器。

`std::find` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 在容器中查找值为 3 的元素
    auto it = std::find(numbers.begin(), numbers.end(), 3);

    if (it != numbers.end()) {
        std::cout << "Element found: " << *it << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    return 0;
}
```

在这个例子中，`std::find` 被用来查找容器 `numbers` 中值为 3 的元素。它接收了三个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，以及要查找的特定值 3。如果找到了值为 3 的元素，`std::find` 将返回指向这个元素的迭代器；如果未找到匹配的元素，它将返回指向容器末尾的迭代器。

除了基本的数值比较外，`std::find` 也可以通过 lambda 表达式实现更加灵活的查找条件，例如：

```cpp
// 使用 lambda 表达式查找容器中大于 3 的第一个元素
auto it = std::find_if(numbers.begin(), numbers.end(), [](int x) {
    return x > 3;
});
```

这将返回容器 `numbers` 中第一个大于 3 的元素的迭代器。`std::find_if` 允许你通过 lambda 表达式指定更复杂的条件来查找满足特定条件的元素。

## std::find_if

`std::find_if` 是 C++ STL 中的一个算法，用于在给定范围内查找满足特定条件的第一个元素。

其函数签名如下：

```cpp
template< class InputIt, class UnaryPredicate >
InputIt find_if( InputIt first, InputIt last, UnaryPredicate p );
```

- `first` 和 `last` 是指定范围的迭代器，表示要查找的元素范围。
- `p` 是一个谓词（UnaryPredicate），它是一个函数或函数对象，用于指定查找的条件。

`std::find_if` 函数从给定范围 `[first, last)` 中查找第一个满足条件 `p` 的元素，并返回指向该元素的迭代器。如果没有找到满足条件的元素，则返回 `last`。

以下是一个简单的示例说明如何使用 `std::find_if` 函数：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

bool isEven(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> numbers = {1, 3, 5, 7, 4, 6, 9}; // 示例数据

    // 查找第一个偶数
    auto it = std::find_if(numbers.begin(), numbers.end(), isEven);

    if (it != numbers.end()) {
        std::cout << "找到第一个偶数: " << *it << std::endl;
    } else {
        std::cout << "未找到满足条件的元素" << std::endl;
    }

    return 0;
}
```

在这个示例中，`isEven` 是一个谓词函数，用于检查一个整数是否为偶数。`std::find_if` 函数被调用来在 `numbers` 容器中查找第一个偶数，如果找到了，则输出该元素的值，否则输出未找到满足条件的提示。

## std::count_if

`std::count_if` 是C++ STL中的一个算法，用于计算容器中满足特定条件的元素个数。它接受两个迭代器参数，表示要进行计数的范围，并使用一个谓词（predicate）作为条件。

`std::count_if` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 计算容器中大于 3 的元素个数
    int countGreaterThanThree = std::count_if(numbers.begin(), numbers.end(), [](int x) {
        return x > 3;
    });

    std::cout << "Count of elements greater than 3: " << countGreaterThanThree << std::endl;

    return 0;
}
```

在这个例子中，`std::count_if` 被用来计算容器 `numbers` 中大于 3 的元素个数。它接收了三个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，以及一个 lambda 表达式作为谓词。这个 lambda 表达式定义了条件，即判断元素是否大于 3。

`std::count_if` 将遍历容器中的每个元素，并使用指定的谓词对每个元素进行判断，然后返回满足条件的元素个数。

通过提供不同的谓词（即 lambda 表达式或者其他可调用对象），可以实现各种复杂的条件来计算满足特定条件的元素个数。

## std::copy

`std::copy` 是C++ STL中的一个算法，用于将一个容器中的元素复制到另一个容器中。它接受两个迭代器参数，表示要进行复制的范围，并将元素复制到目标容器的指定位置。

`std::copy` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination;

    // 使用 std::copy 将 source 容器中的元素复制到 destination 容器中
    std::copy(source.begin(), source.end(), std::back_inserter(destination));

    // 输出目标容器中的元素
    for (int elem : destination) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`std::copy` 被用来将容器 `source` 中的元素复制到容器 `destination` 中。它接收了三个参数：`source.begin()` 表示要复制的范围的起始迭代器，`source.end()` 表示范围的结束迭代器，以及目标容器的迭代器，使用 `std::back_inserter` 插入器将元素插入到目标容器的末尾。

`std::copy` 将遍历源容器中的元素，并将它们复制到目标容器中，最终完成元素的复制操作。

`std::copy` 使得在不同容器之间进行元素复制变得非常方便，可以在不同类型的容器之间灵活地进行数据传输。

## std::transform

`std::transform` 是C++ STL中的一个算法，用于将容器中的元素按照指定的操作进行转换，并将结果存储到另一个容器中。它接受两个源容器的迭代器作为输入范围，并使用一个目标容器的迭代器指定输出位置。此外，它还接受一个函数或函数对象，用于定义转换操作。

`std::transform` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination;

    // 使用 std::transform 将 source 容器中的元素加倍后存储到 destination 容器中
    std::transform(source.begin(), source.end(), std::back_inserter(destination), [](int x) {
        return x * 2;
    });

    // 输出目标容器中的元素
    for (int elem : destination) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`std::transform` 被用来将容器 `source` 中的元素加倍后存储到容器 `destination` 中。它接收了四个参数：`source.begin()` 表示要转换的范围的起始迭代器，`source.end()` 表示范围的结束迭代器，`std::back_inserter(destination)` 表示目标容器的迭代器，使用 `std::back_inserter` 插入器将转换后的元素插入到目标容器的末尾，以及一个 lambda 表达式作为转换操作。

`std::transform` 将遍历源容器中的每个元素，并使用指定的操作（在这里是 lambda 表达式中的乘以 2 操作），将转换后的结果存储到目标容器中。

`std::transform` 提供了一种方便的方式来对容器中的元素进行转换，并将结果存储到另一个容器中，非常适用于需要对元素进行变换操作的场景。

## std::replace

`std::replace` 是C++ STL中的一个算法，用于在容器中将指定值替换为另一个值。它接受两个迭代器参数，表示要进行替换的范围，并使用要替换的值和替换后的新值作为参数。

`std::replace` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 std::replace 将容器中的值为 3 的元素替换为 10
    std::replace(numbers.begin(), numbers.end(), 3, 10);

    // 输出替换后的容器中的元素
    for (int elem : numbers) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`std::replace` 被用来将容器 `numbers` 中的值为 3 的元素替换为 10。它接收了四个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，要被替换的旧值 3，以及替换后的新值 10。

`std::replace` 将遍历容器中的每个元素，并将与旧值相匹配的元素替换为新值。

`std::replace` 提供了一种简单而有效的方法，用于在容器中执行值的替换操作。

## std::fill

`std::fill` 是C++ STL中的一个算法，用于将容器中的所有元素都设置为指定的值。它接受两个迭代器参数，表示要进行填充的范围，并使用要填充的值作为参数。

`std::fill` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers(5); // 创建一个包含5个元素的向量

    // 使用 std::fill 将向量中的所有元素设置为值为 10
    std::fill(numbers.begin(), numbers.end(), 10);

    // 输出填充后的向量中的元素
    for (int elem : numbers) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`std::fill` 被用来将向量 `numbers` 中的所有元素设置为值为 10。它接收了三个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，以及要填充的新值 10。

`std::fill` 将遍历容器中的每个元素，并将每个元素设置为指定的新值。

`std::fill` 提供了一种便捷的方法，用于将容器中的所有元素都设置为特定的值，非常适用于需要初始化容器的情况。

## std::sort

`std::sort` 是C++ STL中的一个算法，用于对容器中的元素进行排序。它接受两个迭代器参数，表示要进行排序的范围，并按照默认的升序方式对这个范围内的元素进行排序。

`std::sort` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    // 使用 std::sort 对向量中的元素进行排序
    std::sort(numbers.begin(), numbers.end());

    // 输出排序后的向量中的元素
    for (int elem : numbers) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`std::sort` 被用来对向量 `numbers` 中的元素进行排序。它接收了两个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器。

`std::sort` 将对容器中的元素按照默认的升序方式进行排序。如果你想要进行自定义的排序方式，可以传入一个自定义的比较函数作为第三个参数。

`std::sort` 是一个高效的排序算法，在处理各种数据结构和数据类型时都能够提供良好的性能。

## std::binary_search

`std::binary_search` 是C++ STL中的一个算法，用于在已排序的序列（例如数组或有序容器）中进行二分查找。它接受两个迭代器参数，表示要进行查找的范围，并返回一个布尔值，指示是否找到了指定的元素。

`std::binary_search` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int target = 6;

    // 使用 std::binary_search 在有序向量中查找元素
    bool isFound = std::binary_search(numbers.begin(), numbers.end(), target);

    if (isFound) {
        std::cout << "Element " << target << " found!" << std::endl;
    } else {
        std::cout << "Element " << target << " not found!" << std::endl;
    }

    return 0;
}
```

在这个例子中，`std::binary_search` 被用来在已排序的向量 `numbers` 中查找元素 6。它接收了三个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，以及要查找的目标值 6。

`std::binary_search` 返回一个布尔值，指示是否在容器中找到了指定的元素。如果找到了元素，则返回 `true`；否则返回 `false`。

`std::binary_search` 使用二分查找算法来检查序列是否包含指定的值。在已排序的序列中，这个算法提供了较快的查找速度。

## std::merge

`std::merge` 是C++ STL中的一个算法，用于将两个已排序的序列合并成一个新的已排序序列。它接受四个迭代器参数，分别表示两个待合并序列的起始和结束位置，以及一个目标序列的起始位置。

`std::merge` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> first = {1, 3, 5, 7, 9};
    std::vector<int> second = {2, 4, 6, 8, 10};
    std::vector<int> result(first.size() + second.size());

    // 使用 std::merge 合并两个有序向量，并将结果存储到 result 向量中
    std::merge(first.begin(), first.end(), second.begin(), second.end(), result.begin());

    // 输出合并后的向量中的元素
    for (int elem : result) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`std::merge` 被用来将两个已排序的向量 `first` 和 `second` 合并成一个新的有序向量 `result`。它接收了五个参数：`first.begin()` 和 `first.end()` 表示第一个待合并序列的范围，`second.begin()` 和 `second.end()` 表示第二个待合并序列的范围，以及目标向量 `result` 的起始迭代器。

`std::merge` 将按照递增的顺序将两个已排序的序列合并到目标序列中。合并后的序列保持有序状态。

`std::merge` 是一个在合并已排序序列时非常有用的算法，它能够高效地合并两个有序序列到一个新的有序序列中。

## std::accumulate

`std::accumulate` 是C++ STL中的一个算法，用于对容器中的元素进行累加操作。它接受三个参数：范围的起始和结束迭代器，以及一个初始值，用于指定累加的起始值。

`std::accumulate` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 std::accumulate 对向量中的元素进行累加
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}
```

在这个例子中，`std::accumulate` 被用来对向量 `numbers` 中的所有元素进行累加操作。它接收了三个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，以及初始值 0 作为累加的起始值。

`std::accumulate` 将对范围内的所有元素进行累加，返回最终的累加结果。

除了简单的累加外，`std::accumulate` 也可以执行其他操作，如乘法累积、自定义操作等。它提供了灵活性，使得在容器中对元素进行各种累积操作变得非常方便。

## std::accumulate 自定义操作

当使用 `std::accumulate` 时，你可以提供一个自定义的二元函数来执行特定的累积操作。这个函数可以是加法、乘法、逻辑运算或任何你需要的二元操作。

以下是一个示例，展示了如何使用 `std::accumulate` 执行自定义操作：

```cpp
#include <iostream>
#include <vector>
#include <numeric>

// 自定义函数：将两个元素相乘
int customMultiply(int x, int y) {
    return x * y;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 std::accumulate 对向量中的元素进行自定义的累积操作
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, customMultiply);

    std::cout << "Product of elements: " << product << std::endl;

    return 0;
}
```

在这个例子中，`std::accumulate` 用于计算向量 `numbers` 中所有元素的乘积。`customMultiply` 是一个自定义的函数，用于定义累积操作。`std::accumulate` 接受了四个参数：`numbers.begin()` 表示范围的起始迭代器，`numbers.end()` 表示范围的结束迭代器，初始值为 1（因为乘法操作的初始值为 1），以及自定义的乘法函数 `customMultiply`。

这个示例中使用了乘法操作，但你可以根据需要提供不同的自定义函数来执行各种不同的累积操作。`std::accumulate` 的灵活性使得在容器中执行各种自定义操作变得非常方便。

## std::inner_product

`std::inner_product` 是C++ STL中的一个算法，用于计算两个序列的内积（dot product）。它接受四个迭代器参数，分别表示两个序列的起始和结束位置，以及两个序列的初始值。

`std::inner_product` 的基本语法如下所示：

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> first = {1, 2, 3, 4, 5};
    std::vector<int> second = {2, 4, 6, 8, 10};

    // 使用 std::inner_product 计算两个向量的内积
    int result = std::inner_product(first.begin(), first.end(), second.begin(), 0);

    std::cout << "Inner product of the vectors: " << result << std::endl;

    return 0;
}
```

在这个例子中，`std::inner_product` 被用来计算两个向量 `first` 和 `second` 的内积。它接收了四个参数：`first.begin()` 和 `first.end()` 表示第一个序列的范围，`second.begin()` 表示第二个序列的范围，以及初始值为 0。

`std::inner_product` 将对两个序列中对应位置的元素进行相乘并相加，最终得到内积的结果。

除了默认的内积计算外，`std::inner_product` 还可以接受自定义的二元函数来执行其他类型的累积操作。这使得它非常灵活，能够进行各种不同类型的序列计算。

## std::generate

`std::generate()` 是 C++ STL 中的一个算法，位于 `<algorithm>` 头文件中。它用于生成指定范围内的值，并将这些值放置到容器或数组中。

该函数的原型如下：

```cpp
template< class ForwardIt, class Generator >
void generate(ForwardIt first, ForwardIt last, Generator g);
```

这个函数接受一个范围 `[first, last)`，并使用生成器函数 `g` 来生成值，将这些值依次赋值给范围内的元素。

示例：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers(5);

    int counter = 1;
    std::generate(numbers.begin(), numbers.end(), [&counter]() {
        return counter++;
    });

    std::cout << "Generated Numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果将会是：
```
Generated Numbers: 1 2 3 4 5 
```

在这个例子中，`std::generate()` 函数使用 lambda 表达式作为生成器函数，从1开始生成值并填充到 `numbers` 容器中。这里利用了 lambda 表达式来捕获并递增 `counter` 变量的值，并将递增后的值赋给容器中的元素。

## std::make_heap

`std::make_heap()` 是 C++ STL 中的一个算法，位于 `<algorithm>` 头文件中。它用于将一个范围内的元素重新组织为一个堆数据结构。

堆是一种特殊的二叉树结构，其中每个父节点的值都大于或等于其子节点的值（最大堆），或每个父节点的值都小于或等于其子节点的值（最小堆）。STL 中的堆通常使用数组来表示。

`std::make_heap()` 函数的原型如下：

```cpp
template< class RandomIt >
void make_heap( RandomIt first, RandomIt last );
```

这个函数接受一个范围 `[first, last)`，其中的元素将会被重新组织成一个堆。默认情况下，这个函数会将范围 `[first, last)` 中的元素转换为最大堆。如果需要创建最小堆，可以使用 `std::make_heap(first, last, comp)` 并提供一个比较函数 `comp`。

示例：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    std::cout << "Original Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::make_heap(numbers.begin(), numbers.end());

    std::cout << "Heapified Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果将会是：
```
Original Vector: 3 1 4 1 5 9 2 6 
Heapified Vector: 9 5 4 6 1 3 2 1 
```

在这个例子中，`std::make_heap()` 函数将 `numbers` 容器转换为最大堆。`make_heap()` 函数会对范围 `[first, last)` 中的元素进行重新排列，使其满足堆的性质。

## std::push_heap

`std::push_heap()` 是 C++ STL 中的一个算法，位于 `<algorithm>` 头文件中。它用于将堆中的元素范围扩展，添加一个新元素，并保持堆的性质不变。

堆是一种特殊的二叉树结构，其中每个父节点的值都大于或等于其子节点的值（最大堆），或每个父节点的值都小于或等于其子节点的值（最小堆）。

`std::push_heap()` 函数的原型如下：

```cpp
template< class RandomIt >
void push_heap( RandomIt first, RandomIt last );
```

这个函数接受一个范围 `[first, last-1]`，表示已经形成了一个堆（[first, last-1]是一个有效的堆），然后将 `*(last-1)` 添加到堆中，并保持堆的性质。

示例：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9};

    std::cout << "Original Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::make_heap(numbers.begin(), numbers.end());

    std::cout << "Heapified Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 添加一个新元素到堆中
    numbers.push_back(6);
    std::push_heap(numbers.begin(), numbers.end());

    std::cout << "Heapified Vector after push_heap: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果将会是：
```
Original Vector: 3 1 4 1 5 9 
Heapified Vector: 9 5 4 1 1 3 
Heapified Vector after push_heap: 9 6 4 5 1 3 1 
```

在这个例子中，`std::push_heap()` 函数将一个新元素 `6` 添加到 `numbers` 容器的末尾，并将其保持为最大堆。`push_heap()` 函数确保堆的性质仍然得到维护。

## std::pop_heap

`std::pop_heap()` 是 C++ STL 中的一个算法，位于 `<algorithm>` 头文件中。它用于将堆中的最大（或最小）元素移到范围的末尾，并且在范围的前部保持一个堆。

堆是一种特殊的二叉树结构，其中每个父节点的值都大于或等于其子节点的值（最大堆），或每个父节点的值都小于或等于其子节点的值（最小堆）。

`std::pop_heap()` 函数的原型如下：

```cpp
template< class RandomIt >
void pop_heap( RandomIt first, RandomIt last );
```

这个函数接受一个范围 `[first, last]`，其中 `[first, last-1]` 应该表示一个有效的堆。然后它将堆中的最大元素（对于最大堆）或最小元素（对于最小堆）移到范围的末尾，并将 `[first, last-1]` 调整为一个新的堆。

示例：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9};

    std::cout << "Original Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::make_heap(numbers.begin(), numbers.end());

    std::cout << "Heapified Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 移除堆中的最大元素（在此为 9）
    std::pop_heap(numbers.begin(), numbers.end());
    std::cout << "Heap after pop_heap: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果将会是：
```
Original Vector: 3 1 4 1 5 9 
Heapified Vector: 9 5 4 1 1 3 
Heap after pop_heap: 5 1 4 1 3 9 
```

在这个例子中，`std::pop_heap()` 函数将 `numbers` 容器的第一个元素（即最大元素）移到了范围的末尾，并且重新将 `[first, last-1]` 调整为一个新的最大堆。

## std::min

在 C++ 标准库中，`std::min()` 是一个模板函数，位于 `<algorithm>` 头文件中。它用于比较两个值并返回其中较小的那个。

`std::min()` 有多个重载形式，可以接受不同类型的参数：

1. **两个参数形式：**
   ```cpp
   template< class T >
   const T& min( const T& a, const T& b );
   ```

   这个版本接受两个相同类型的参数 `a` 和 `b`，并返回其中较小的值。

2. **初始化列表形式：**
   ```cpp
   template< class T >
   T min( std::initializer_list<T> ilist );
   ```

   这个版本接受一个初始化列表，并返回列表中的最小值。

示例：

```cpp
#include <iostream>
#include <algorithm>

int main() {
    int x = 5;
    int y = 3;

    int smaller = std::min(x, y); // 返回较小的值

    std::cout << "The smaller value is: " << smaller << std::endl;

    return 0;
}
```

输出结果：
```
The smaller value is: 3
```

在上述示例中，`std::min()` 被用于比较 `x` 和 `y` 的值，并将较小的值赋给变量 `smaller`。根据参数的类型，`std::min()` 将返回一个具有较小值的变量或元素。

## std::max

在 C++ 标准库中，`std::max()` 是一个模板函数，位于 `<algorithm>` 头文件中。它用于比较两个值并返回其中较大的那个。

`std::max()` 有多个重载形式，可以接受不同类型的参数：

1. **两个参数形式：**
   ```cpp
   template< class T >
   const T& max( const T& a, const T& b );
   ```

   这个版本接受两个相同类型的参数 `a` 和 `b`，并返回其中较大的值。

2. **初始化列表形式：**
   ```cpp
   template< class T >
   T max( std::initializer_list<T> ilist );
   ```

   这个版本接受一个初始化列表，并返回列表中的最大值。

示例：

```cpp
#include <iostream>
#include <algorithm>

int main() {
    int x = 5;
    int y = 3;

    int larger = std::max(x, y); // 返回较大的值

    std::cout << "The larger value is: " << larger << std::endl;

    return 0;
}
```

输出结果：
```
The larger value is: 5
```

在上述示例中，`std::max()` 被用于比较 `x` 和 `y` 的值，并将较大的值赋给变量 `larger`。根据参数的类型，`std::max()` 将返回一个具有较大值的变量或元素。

## std::reverse

`std::reverse()` 是 C++ 标准库中的一个算法，位于 `<algorithm>` 头文件中。它用于将指定范围内的元素进行反转。

这个函数的原型如下：

```cpp
template< class BidirIt >
void reverse( BidirIt first, BidirIt last );
```

`std::reverse()` 接受一个范围 `[first, last)`，并将该范围内的元素进行反转。这个范围应该是一个双向迭代器范围，例如 `std::vector`、`std::list`、`std::deque` 等容器。

示例：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "Original Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::reverse(numbers.begin(), numbers.end());

    std::cout << "Reversed Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果将会是：
```
Original Vector: 1 2 3 4 5 
Reversed Vector: 5 4 3 2 1 
```

在这个例子中，`std::reverse()` 函数被用于反转 `numbers` 容器中的元素顺序。注意，`std::reverse()` 只是简单地颠倒元素的顺序，并不会改变容器中的元素值。

## std::rotate

`std::rotate()` 是 C++ 标准库中的一个算法，位于 `<algorithm>` 头文件中。它用于将容器中的元素按照指定的位置进行循环左旋。

这个函数的原型如下：

```cpp
template< class ForwardIt >
ForwardIt rotate( ForwardIt first, ForwardIt n_first, ForwardIt last );
```

`std::rotate()` 接受三个迭代器参数：`first`、`n_first` 和 `last`。它会将位于范围 `[first, last)` 中的元素从位置 `first` 开始，循环左旋到新的位置 `n_first`。也就是说，`n_first` 将成为新的起始位置。

示例：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "Original Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::rotate(numbers.begin(), numbers.begin() + 2, numbers.end());

    std::cout << "Rotated Vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

输出结果将会是：
```
Original Vector: 1 2 3 4 5 
Rotated Vector: 3 4 5 1 2 
```

在这个例子中，`std::rotate()` 函数被用于对 `numbers` 容器中的元素进行循环左旋。参数 `numbers.begin() + 2` 指定了旋转的新起始位置，将原来前两个元素移到了容器末尾。

## std::adjacent_difference

`std::adjacent_difference` 是 C++ STL 中的一个函数，用于计算一个序列中相邻元素的差值，并将结果存储到另一个序列中。

其函数签名如下：

```cpp
template< class InputIt, class OutputIt >
OutputIt adjacent_difference( InputIt first, InputIt last, OutputIt d_first );
```

- `first` 和 `last` 是输入序列的迭代器范围，表示要进行差值计算的元素范围。
- `d_first` 是输出序列的起始位置迭代器，用于存储相邻元素之间的差值结果。

以下是一个简单的示例说明 `std::adjacent_difference` 函数的用法：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 3, 5, 7, 9}; // 示例数据
    std::vector<int> differences(numbers.size()); // 用于存储相邻元素差值的容器

    // 计算相邻元素的差值
    std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());

    // 输出结果
    std::cout << "相邻元素的差值：";
    for (const auto& diff : differences) {
        std::cout << diff << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

这个示例中，`std::adjacent_difference` 函数计算了 `numbers` 中相邻元素的差值，并将结果存储在 `differences` 容器中。最后，通过迭代输出了相邻元素的差值。

需要注意的是，`std::adjacent_difference` 函数对于输入序列中的第一个元素会直接复制到输出序列中，而后续元素则会存储与前一个元素的差值。

## std::equal

`std::equal()` 是 C++ 标准模板库中的一个算法，用于检查两个序列是否相等。它比较两个序列中的对应元素，如果两个序列在相同位置上的元素都相等，则返回 `true`，否则返回 `false`。

### 语法：
```cpp
template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 );

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );
```

- `first1` 和 `last1` 是第一个序列的起始和结束迭代器。
- `first2` 是第二个序列的起始迭代器。
- `p` 是一个可选的谓词（函数对象或函数指针），用于比较两个元素。

### 参数：
- `first1`、`last1`：定义了第一个序列的范围，包括 `first1`，但不包括 `last1`。
- `first2`：定义了第二个序列的起始位置。
- `p`：如果提供了这个参数，将会用它来比较元素，否则将使用元素类型的 `operator==` 进行比较。

### 返回值：
- 如果两个序列在范围 `[first1, last1)` 中的相应元素都相等，则返回 `true`，否则返回 `false`。

示例：
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {1, 2, 3, 4, 5};

    bool isEqual = std::equal(vec1.begin(), vec1.end(), vec2.begin());

    if (isEqual) {
        std::cout << "两个序列相等" << std::endl;
    } else {
        std::cout << "两个序列不相等" << std::endl;
    }

    return 0;
}
```

在这个示例中，`std::equal()` 用于比较两个 `std::vector` 是否相等。由于它们包含相同的元素且相同顺序，因此会输出 "两个序列相等"。

## C++ std::equal 自定义操作

`std::equal` 可以接受一个自定义的操作（谓词），以便进行元素的比较。这个谓词可以是一个函数对象或者函数指针，用于执行元素间的自定义比较。

### 语法：
```cpp
template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );
```

- `first1` 和 `last1` 是第一个序列的起始和结束迭代器。
- `first2` 是第二个序列的起始迭代器。
- `p` 是一个二元谓词，用于比较两个元素。它接受两个参数，分别是两个要比较的元素，返回 `bool` 类型的结果。

### 参数：
- `first1`、`last1`：定义了第一个序列的范围，包括 `first1`，但不包括 `last1`。
- `first2`：定义了第二个序列的起始位置。
- `p`：用于比较两个元素的自定义二元谓词。

### 返回值：
- 如果两个序列在范围 `[first1, last1)` 中的相应元素使用谓词 `p` 进行比较都返回 `true`，则返回 `true`，否则返回 `false`。

示例：
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

// 自定义谓词，比较元素是否相差1
bool customPredicate(int a, int b) {
    return (a - b == 1);
}

int main() {
    std::vector<int> vec1 = {1, 3, 5, 7, 9};
    std::vector<int> vec2 = {2, 4, 6, 8, 10};

    bool isEqual = std::equal(vec1.begin(), vec1.end(), vec2.begin(), customPredicate);

    if (isEqual) {
        std::cout << "两个序列中对应元素相差1" << std::endl;
    } else {
        std::cout << "两个序列中对应元素不相差1" << std::endl;
    }

    return 0;
}
```

在这个示例中，`std::equal()` 使用了自定义的谓词 `customPredicate` 来比较两个序列的元素是否相差1。如果两个序列中对应位置的元素相差1，则输出 "两个序列中对应元素相差1"，否则输出 "两个序列中对应元素不相差1"。