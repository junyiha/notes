## 简介

+ C++ <cstring>标准库

## std::memcpy

`std::memcpy` 是 C++ 标准库 `<cstring>` 头文件中定义的函数，用于在内存块之间复制一定数量的字节。

其基本原型如下：

```cpp
void* memcpy(void* dest, const void* src, std::size_t count);
```

- `dest`：目标内存块的起始地址，数据将被复制到这个地址。
- `src`：源内存块的起始地址，数据将从这个地址复制到目标内存块。
- `count`：要复制的字节数。

`std::memcpy` 主要用于进行内存的原始字节级别的拷贝操作。它是一种直接的、快速的内存拷贝方式，通常用于复制大块的内存数据。

以下是一个简单的示例：

```cpp
#include <iostream>
#include <cstring>

int main() {
    char source[] = "Hello, world!";
    char destination[20];

    std::memcpy(destination, source, std::strlen(source) + 1); // 复制 source 到 destination

    std::cout << "Copied string: " << destination << std::endl;

    return 0;
}
```

在这个示例中，`std::memcpy` 用于将源字符串 `source` 复制到目标字符串 `destination`，包括字符串结尾的 null 终止符。要确保目标内存块足够大以容纳源内存块的数据。

## std::memset()

`std::memset()` 是 C++ 标准库 `<cstring>` 头文件中定义的函数，用于设置指定内存区域的内容为指定的值。

其基本原型如下：

```cpp
void* memset(void* dest, int value, std::size_t count);
```

- `dest`：要设置值的内存区域的起始地址。
- `value`：要设置的值，通常是一个整数（`int` 类型），会被转换为无符号字符进行设置。
- `count`：要设置的字节数。

`std::memset()` 将 `value` 的值复制到 `dest` 指向的内存区域的前 `count` 个字节。通常情况下，它用于初始化内存块为特定的值，比如初始化数组、清除缓冲区等。

示例：

```cpp
#include <iostream>
#include <cstring>

int main() {
    char buffer[10];

    std::memset(buffer, 'A', sizeof(buffer)); // 将 buffer 内存区域的内容设置为字符 'A'

    std::cout << "Buffer after memset: " << buffer << std::endl;

    return 0;
}
```

在这个示例中，`std::memset()` 将字符 `'A'` 设置到 `buffer` 内存区域的每个字节中。要注意，`std::memset()` 是按字节进行操作，并不会处理字符数组或字符串的结尾 null 终止符。