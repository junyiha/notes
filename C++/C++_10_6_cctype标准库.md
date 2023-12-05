## 简介

+ <cctype> 标准库相关笔记

## C++ <cctype>标准库

C++ 标准库 `<cctype>` 提供了一组用于对字符进行分类和简单字符处理的函数。这些函数在 `<cctype>` 头文件中声明，并且是 C++ 中处理字符的标准方式。

以下是 `<cctype>` 头文件中常用的一些函数：

### 字符分类函数：
- `std::isalnum(int c)`: 检查字符是否是字母或数字。
- `std::isalpha(int c)`: 检查字符是否是字母。
- `std::isdigit(int c)`: 检查字符是否是十进制数字。
- `std::islower(int c)`: 检查字符是否是小写字母。
- `std::isupper(int c)`: 检查字符是否是大写字母。
- `std::isspace(int c)`: 检查字符是否是空格或类似的空白字符。
- `std::iscntrl(int c)`: 检查字符是否是控制字符。
- `std::ispunct(int c)`: 检查字符是否是标点符号。
- `std::isprint(int c)`: 检查字符是否是可打印字符。
- `std::isxdigit(int c)`: 检查字符是否是十六进制数字。

### 字符转换函数：
- `std::tolower(int c)`: 将字符转换为小写形式。
- `std::toupper(int c)`: 将字符转换为大写形式。

### 其他函数：
- `std::tolower()` 和 `std::toupper()` 还有版本可用于处理字符的宽字符版本 `wchar_t`，其函数名为 `std::towlower()` 和 `std::towupper()`。

这些函数都接受一个整数参数，通常是 `int` 类型，表示要检查或转换的字符。函数返回值为 `int` 类型，通常表示一个非零值（真）或零值（假）来指示检查的条件是否满足。

这些函数通常用于检查或转换字符，例如，检查一个字符是否是字母、数字，或者将字符转换为大写或小写形式。

```cpp
#include <iostream>
#include <cctype>

int main() {
    char ch = 'A';

    if (std::isupper(ch)) {
        std::cout << "字符 " << ch << " 是大写字母" << std::endl;
    }

    char lowercase = std::tolower(ch);
    std::cout << "将字符 " << ch << " 转换为小写形式为: " << lowercase << std::endl;

    return 0;
}
```

以上示例演示了 `std::isupper()` 函数检查一个字符是否为大写字母，以及 `std::tolower()` 函数将一个字符转换为小写形式。

## std::tolower()

`std::tolower()` 是 C++ 标准库中 `<cctype>` 头文件中提供的函数，用于将单个字符转换为小写形式。

### 函数原型：
```cpp
int tolower(int c);
```

### 参数：
- `c`：要转换为小写的字符。

### 返回值：
- 如果 `c` 是大写字母，则返回对应的小写字母，否则返回 `c` 本身。

### 示例：
```cpp
#include <iostream>
#include <cctype>

int main() {
    char uppercase = 'A';
    char lowercase = std::tolower(uppercase);

    std::cout << "大写字母 " << uppercase << " 转换为小写字母为: " << lowercase << std::endl;

    return 0;
}
```

### 输出：
```
大写字母 A 转换为小写字母为: a
```

在这个示例中，`std::tolower('A')` 将大写字母 'A' 转换为小写字母 'a'。

## std::toupper()

`std::toupper()` 是 C++ 标准库中 `<cctype>` 头文件中提供的函数之一，用于将字符转换为大写形式。

### 函数原型：
```cpp
int toupper(int c);
```

### 参数：
- `c`：要转换为大写的字符。

### 返回值：
- 如果 `c` 是小写字母，则返回对应的大写字母；否则返回 `c` 本身。

### 示例：
```cpp
#include <iostream>
#include <cctype>

int main() {
    char lowercase = 'a';
    char uppercase = std::toupper(lowercase);

    std::cout << "小写字母 " << lowercase << " 转换为大写字母为: " << uppercase << std::endl;

    return 0;
}
```

### 输出：
```
小写字母 a 转换为大写字母为: A
```

在这个示例中，`std::toupper('a')` 将小写字母 'a' 转换为大写字母 'A'。