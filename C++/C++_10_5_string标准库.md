## 简介

+ <string>标准库

## C++ <string> 标准库

C++ 标准库中的 `<string>` 头文件提供了许多操作字符串的功能，包括创建、操作、处理和管理字符串。使用这个头文件，可以方便地使用字符串并执行各种操作，例如连接字符串、查找子串、截取部分字符串等。

以下是 `<string>` 标准库中一些常用的类和函数：

### 字符串类
- **`std::string`**: 提供了一个可变长度的字符序列，支持字符串的各种操作和方法，如插入、删除、查找、替换等。

### 字符串操作函数
- **`std::to_string()`**: 将基本数据类型转换为对应的字符串。
- **`std::stoi()`, `std::stol()`, `std::stoll()`, `std::stof()`, `std::stod()`, `std::stold()`**: 将字符串转换为对应的数值类型。
- **`std::getline()`**: 从输入流中读取一行数据到字符串中。

### 字符串操作方法
- **`size()`, `length()`**: 返回字符串的长度。
- **`append()`, `+=`**: 在字符串末尾追加内容。
- **`insert()`, `erase()`, `replace()`**: 插入、删除、替换子串。
- **`substr()`, `find()`, `rfind()`**: 提取子串、查找子串的位置。

### 字符串比较和转换
- **`compare()`**: 比较字符串。
- **`toupper()`, `tolower()`**: 转换为大写或小写。

### 字符串查询和搜索
- **`find()`, `rfind()`, `find_first_of()`, `find_last_of()`, `find_first_not_of()`, `find_last_not_of()`**: 查找字符串中特定子串或字符的位置。

### 其他实用函数
- **`c_str()`, `data()`**: 返回以 null 结尾的 C 风格字符串的指针。
- **`empty()`, `clear()`, `reserve()`, `shrink_to_fit()`**: 管理字符串的空间和大小。

示例代码：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, ";
    str += "world!"; // 连接字符串
    std::cout << str << std::endl;

    std::cout << "Length of str: " << str.length() << std::endl;

    // 查找子串
    if (str.find("world") != std::string::npos) {
        std::cout << "Substring 'world' found at position: " << str.find("world") << std::endl;
    }

    // 提取子串
    std::string sub = str.substr(7, 5);
    std::cout << "Substring: " << sub << std::endl;

    return 0;
}
```

以上代码演示了一些常见的字符串操作，包括字符串连接、长度获取、查找子串位置、提取子串等。 `<string>` 头文件提供了丰富的功能，用于处理字符串以及执行各种字符串操作。

## C++ <string>标准库 详解

C++ 标准库中的 `<string>` 头文件提供了丰富的字符串操作功能，使得在程序中处理字符串变得更加方便和灵活。以下是 `<string>` 标准库中一些常用的类和函数的详细解释：

### `std::string` 类
`std::string` 是 C++ 标准库中表示字符串的类。它提供了一系列的方法来操作和管理字符串。这些方法包括：

- **构造函数**：`std::string` 提供了多种构造函数，允许你用不同的方式初始化字符串。
  ```cpp
  std::string str1;                 // 初始化为空字符串
  std::string str2 = "Hello";       // 用 C 风格字符串初始化
  std::string str3(5, 'a');         // 初始化为重复字符的字符串，"aaaaa"
  ```

- **`size()` 和 `length()`**：返回字符串的长度。
  ```cpp
  std::string str = "Hello";
  std::cout << "Length of str: " << str.length() << std::endl; // 输出 5
  ```

- **字符串连接**：可以使用 `+` 运算符或 `append()` 方法来连接字符串。
  ```cpp
  std::string str1 = "Hello, ";
  std::string str2 = "world!";
  std::string result = str1 + str2; // 使用 + 运算符
  str1.append(str2);                // 使用 append() 方法
  ```

- **字符串比较**：使用 `compare()` 方法进行字符串的比较。
  ```cpp
  std::string str1 = "apple";
  std::string str2 = "banana";
  int result = str1.compare(str2);  // 返回值 < 0 表示 str1 小于 str2
  ```

- **提取子串**：使用 `substr()` 方法提取子串。
  ```cpp
  std::string str = "Hello, world!";
  std::string sub = str.substr(7, 5); // 提取从位置 7 开始的长度为 5 的子串 "world"
  ```

- **查找子串**：使用 `find()` 方法查找子串的位置。
  ```cpp
  std::string str = "Hello, world!";
  size_t pos = str.find("world"); // 查找子串 "world" 的位置，返回 7
  ```

- **转换为 C 风格字符串**：可以使用 `c_str()` 方法将 `std::string` 转换为以 null 结尾的 C 风格字符串。
  ```cpp
  std::string str = "Hello";
  const char* cstr = str.c_str(); // 返回以 null 结尾的 C 风格字符串
  ```

- **其他方法**：还有很多其他方法，如 `insert()` 插入子串、`erase()` 删除子串、`replace()` 替换子串等。

### 其他函数和功能
- **`std::to_string()`**：将数值转换为对应的字符串。
  ```cpp
  int num = 123;
  std::string str = std::to_string(num); // 将整数转换为字符串 "123"
  ```

- **字符串流**：`std::stringstream` 可以用于字符串和其他数据类型之间的转换。
  ```cpp
  #include <sstream>
  int num = 123;
  std::stringstream ss;
  ss << num;               // 将整数写入字符串流
  std::string str = ss.str(); // 从字符串流中获取字符串 "123"
  ```

这些只是 `<string>` 标准库中一部分功能，该库还提供了更多用于字符串处理和操作的功能。使用这些功能，可以更方便地对字符串进行操作、处理和管理。

## C++ <string>标准库 常用函数

C++ 标准库 `<string>` 中提供了许多常用的函数，用于处理和操作字符串。以下是一些常用的函数及其简要说明：

### 字符串长度和容量
- **`size()` 和 `length()`**: 返回字符串的长度。
- **`capacity()`**: 返回字符串当前分配的存储容量。

### 字符串操作
- **`append()`**: 在字符串末尾添加内容。
- **`insert()`**: 在指定位置插入内容。
- **`erase()`**: 从字符串中删除指定范围的内容。
- **`replace()`**: 替换指定范围的内容为另一个字符串。
- **`substr()`**: 提取子串。
- **`swap()`**: 交换两个字符串的内容。

### 字符串搜索和查找
- **`find()` 和 `rfind()`**: 查找子串的位置，`find()` 从前往后找，`rfind()` 从后往前找。
- **`find_first_of()` 和 `find_last_of()`**: 在字符串中查找字符序列中任意字符的第一个/最后一个匹配位置。
- **`find_first_not_of()` 和 `find_last_not_of()`**: 查找字符串中第一个/最后一个不在指定字符序列中的字符位置。

### 字符串比较和处理
- **`compare()`**: 比较两个字符串的大小。
- **`tolower()` 和 `toupper()`**: 将字符串转换为小写或大写。
- **`std::stoi()`, `std::stol()`, `std::stoll()`, `std::stof()`, `std::stod()`, `std::stold()`**: 将字符串转换为对应的数值类型。

### C 风格字符串处理
- **`c_str()`**: 返回以 null 结尾的 C 风格字符串的指针。
- **`data()`**: 返回指向字符串缓冲区的指针。

### 字符串空间管理
- **`reserve()`**: 设置字符串的预留空间。
- **`shrink_to_fit()`**: 请求释放未使用的内存空间，将容器的容量减小到与其大小相匹配。

### 其他实用函数
- **`std::getline()`**: 从输入流中读取一行数据到字符串中。
- **`std::to_string()`**: 将数值转换为对应的字符串。

这些函数提供了对字符串进行各种操作和处理的功能，可以轻松地执行字符串的连接、查找、替换、截取等操作，以及对字符串的大小、长度、容量进行管理。

## std::string::size()

`std::string::size()` 是 C++ 标准库中 `std::string` 类的成员函数，用于获取字符串的长度，即字符的个数。

这个函数返回一个 `size_t` 类型的无符号整数，代表字符串中字符的数量。这个字符数量不包括字符串末尾的 null 终止符。

示例用法如下：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, world!";
    size_t len = str.size(); // 获取字符串的长度

    std::cout << "字符串长度为: " << len << std::endl;

    return 0;
}
```

在这个示例中，`str.size()` 返回的值将是字符串 "Hello, world!" 中字符的总数，包括逗号、空格和感叹号在内。

## std::string::length()

`std::string::length()` 是 C++ 标准库中 `std::string` 类的成员函数之一，与 `size()` 函数类似，用于获取字符串的长度，即字符的个数。

这两个函数 `size()` 和 `length()` 在 `std::string` 类中是等价的，都用于返回字符串中字符的数量，不包括末尾的空字符（null terminator）。

示例用法如下：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, world!";
    size_t len = str.length(); // 或者使用 str.size() 获取字符串的长度

    std::cout << "字符串长度为: " << len << std::endl;

    return 0;
}
```

在这个示例中，`str.length()` 返回的值将是字符串 "Hello, world!" 中字符的总数，包括逗号、空格和感叹号在内。通常来说，`length()` 和 `size()` 都可用于获取字符串的长度，并且在 `std::string` 类中它们的功能是一样的。

## std::string::append()

`std::string::append()` 是 C++ 标准库中 `std::string` 类的成员函数之一，用于将指定的内容追加到字符串的末尾。

这个函数可以接受多种类型的参数来追加内容，包括：

- 另一个 `std::string` 对象
- 字符串的一部分（通过指定位置和长度）
- C 风格的字符串
- 字符或者重复的字符

以下是 `std::string::append()` 函数的几种重载形式：

```cpp
std::string& append(const std::string& str); // 将另一个字符串追加到末尾
std::string& append(const std::string& str, size_t pos, size_t len); // 将字符串的一部分追加到末尾
std::string& append(const char* s); // 将 C 风格的字符串追加到末尾
std::string& append(const char* s, size_t n); // 将指定长度的 C 风格字符串追加到末尾
std::string& append(size_t n, char c); // 将字符 c 重复追加 n 次到末尾
```

以下是一个简单的示例演示了如何使用 `std::string::append()`：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";
    
    // 追加另一个字符串到末尾
    str.append(" world!");

    // 追加字符串的一部分到末尾
    std::string anotherStr = " This is a test.";
    str.append(anotherStr, 0, 11); // 从另一个字符串的指定位置追加一部分内容

    // 追加重复的字符到末尾
    str.append(3, '!');

    std::cout << "结果字符串: " << str << std::endl;

    return 0;
}
```

在这个示例中，`std::string::append()` 函数被用于将不同类型的内容追加到字符串 `str` 的末尾，包括另一个字符串、另一个字符串的一部分以及重复的字符。最终输出的字符串将是 "Hello world! This is a test.!!!"。

## std::string::insert()

`std::string::insert()` 是 C++ 标准库中 `std::string` 类的成员函数之一，用于在指定位置插入内容到字符串中。

这个函数允许在字符串的特定位置插入另一个字符串、子串或字符。它的重载版本可以用于不同的插入操作，可以指定要插入的位置和内容。

以下是 `std::string::insert()` 函数的几种重载形式：

```cpp
std::string& insert(size_t pos, const std::string& str); // 在指定位置插入另一个字符串
std::string& insert(size_t pos, const std::string& str, size_t subpos, size_t sublen); // 在指定位置插入另一个字符串的一部分
std::string& insert(size_t pos, const char* s); // 在指定位置插入 C 风格的字符串
std::string& insert(size_t pos, const char* s, size_t n); // 在指定位置插入指定长度的 C 风格字符串
std::string& insert(size_t pos, size_t n, char c); // 在指定位置插入重复的字符
```

以下是一个简单的示例演示了如何使用 `std::string::insert()`：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello world!";
    
    // 在指定位置插入另一个字符串
    str.insert(5, "beautiful ");

    // 在指定位置插入重复的字符
    str.insert(6, 3, '*');

    std::cout << "结果字符串: " << str << std::endl;

    return 0;
}
```

在这个示例中，`std::string::insert()` 函数被用于在字符串 `str` 的指定位置进行插入操作。首先，在位置 5 插入了另一个字符串 "beautiful "，然后在位置 6 插入了重复的字符 '*'。最终输出的字符串将是 "Hello* * * beautiful world!"。

## std::string::erase()

`std::string::erase()` 是 C++ 标准库中 `std::string` 类的成员函数之一，用于从字符串中删除指定位置的字符或一段子串。

这个函数有多个重载版本，允许你指定要删除的位置和要删除的字符数。你可以删除单个字符、一段字符，或者从指定位置开始一直删除到字符串末尾。

以下是 `std::string::erase()` 函数的几种重载形式：

```cpp
std::string& erase(size_t pos = 0, size_t len = npos); // 从指定位置开始删除指定数量的字符
iterator erase(iterator position); // 删除指定位置处的字符
iterator erase(iterator first, iterator last); // 删除指定范围内的字符
```

示例代码如下：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, beautiful world!";

    // 删除指定位置开始的 7 个字符
    str.erase(7, 7); // 从位置 7 开始，删除 7 个字符

    // 从迭代器位置开始删除一段字符
    std::string::iterator it = str.begin() + 13;
    str.erase(it, str.end());

    std::cout << "结果字符串: " << str << std::endl;

    return 0;
}
```

在这个示例中，首先使用 `erase()` 函数从位置 7 开始删除了 7 个字符，然后使用迭代器指定的位置开始删除了一段字符，直到字符串的末尾。最终输出的字符串将是 "Hello, "。

## std::string::replace()

`std::string::replace()` 是 C++ 标准库中 `std::string` 类的成员函数之一，用于替换字符串中的部分内容。

这个函数允许你用另一个字符串、子串或字符序列替换指定位置和长度的内容。你可以选择性地替换指定位置开始的一定数量的字符，也可以替换整个字符串的一部分。

以下是 `std::string::replace()` 函数的几种重载形式：

```cpp
std::string& replace(size_t pos, size_t len, const std::string& str); // 用另一个字符串替换指定位置和长度的内容
std::string& replace(iterator i1, iterator i2, const std::string& str); // 用另一个字符串替换指定范围的内容
std::string& replace(size_t pos, size_t len, const std::string& str, size_t subpos, size_t sublen); // 用另一个字符串的一部分替换指定位置和长度的内容
std::string& replace(size_t pos, size_t len, const char* s); // 用 C 风格的字符串替换指定位置和长度的内容
std::string& replace(iterator i1, iterator i2, const char* s, size_t n); // 用指定长度的 C 风格字符串替换指定范围的内容
std::string& replace(size_t pos, size_t len, size_t n, char c); // 用重复的字符替换指定位置和长度的内容
```

以下是一个示例演示了如何使用 `std::string::replace()` 函数：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, beautiful world!";

    // 用另一个字符串替换指定位置和长度的内容
    str.replace(7, 9, "wonderful");

    // 用重复的字符替换指定位置和长度的内容
    str.replace(0, 6, 7, '*');

    std::cout << "结果字符串: " << str << std::endl;

    return 0;
}
```

在这个示例中，首先使用 `replace()` 函数将字符串中位置 7 开始、长度为 9 的部分替换为另一个字符串 "wonderful"，然后用重复的字符 '*' 替换了字符串的前 7 个字符。最终输出的字符串将是 "*******wonderful world!"。

## std::string::substr()

`std::string::substr()` 是 C++ 标准库中 `std::string` 类的成员函数之一，用于提取字符串的子串。

这个函数接受两个参数，第一个参数是子串的起始位置（索引），第二个参数是子串的长度。如果只提供一个参数，它将从指定位置开始提取直到字符串末尾的所有字符。

以下是 `std::string::substr()` 函数的形式：

```cpp
std::string substr(size_t pos, size_t len = npos) const;
```

- `pos` 是子串的起始位置（索引），从 0 开始计数。
- `len` 是子串的长度，默认值是 `npos`，表示提取从 `pos` 开始到字符串末尾的所有字符。

示例代码如下：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, world!";

    // 提取从索引为 7 开始的子串
    std::string sub1 = str.substr(7);
    std::cout << "子串1: " << sub1 << std::endl; // 输出 "world!"

    // 提取从索引为 0 开始，长度为 5 的子串
    std::string sub2 = str.substr(0, 5);
    std::cout << "子串2: " << sub2 << std::endl; // 输出 "Hello"

    return 0;
}
```

在这个示例中，`str.substr(7)` 提取了从索引 7 开始到字符串末尾的子串（"world!"），而 `str.substr(0, 5)` 提取了从索引 0 开始长度为 5 的子串（"Hello"）。