## 简介

+ C++ <iomanip>标准库

## C++ <iomanip>标准库

`<iomanip>` 是 C++ 标准库中的头文件，提供了与格式化输入输出相关的工具和操作符。这个头文件主要包含了用于控制输入输出格式的类和函数。

### 主要内容：
1. **操纵符（Manipulators）：**
   - `std::setw(int n)`: 设置域宽（用于下一个输出项）。
   - `std::setprecision(int n)`: 设置浮点数的精度。
   - `std::setfill(char c)`: 设置填充字符。
   - `std::left`, `std::right`, `std::internal`: 控制输出对齐方式。
   - `std::boolalpha`: 将布尔值输出为 "true" 或 "false"。
   - `std::hex`, `std::dec`, `std::oct`: 控制输出的进制。
   - 等等。

2. **流控制：**
   - `std::fixed`, `std::scientific`: 控制浮点数输出的格式。
   - `std::showpoint`: 总是显示小数点。
   - `std::noshowpoint`: 不显示小数点。
   - `std::uppercase`: 使用大写字母表示科学计数法中的指数。
   - `std::nouppercase`: 使用小写字母表示科学计数法中的指数。
   - 等等。

### 示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 123;
    double pi = 3.14159;

    std::cout << std::setw(10) << num << std::endl; // 设置域宽为 10
    std::cout << std::setprecision(3) << pi << std::endl; // 设置浮点数的精度为 3
    std::cout << std::setfill('*') << std::setw(8) << num << std::endl; // 设置域宽为 8，填充字符为 '*'
    std::cout << std::left << std::setw(8) << num << std::endl; // 左对齐
    std::cout << std::scientific << pi << std::endl; // 科学计数法输出

    return 0;
}
```

这个示例展示了 `<iomanip>` 中一些常用的格式化输出操作，如设置域宽、设置精度、设置填充字符、对齐方式、科学计数法输出等。这些操作可用于控制输入输出的格式，使输出更易读、更美观。

## C++ <iomanip>标准库 详解

`<iomanip>` 是 C++ 标准库中的头文件，提供了用于格式化输入输出的工具和操作符。它包含了多种操纵符（manipulators）、流控制器（stream control）、标志（flags）和函数，用于调整输出的格式以及控制流的行为。

### 主要内容：
1. **操纵符（Manipulators）：**
   - `std::setw(int n)`: 设置下一个输出项的宽度。
   - `std::setprecision(int n)`: 设置浮点数的输出精度。
   - `std::setfill(char c)`: 设置填充字符。
   - `std::left`, `std::right`, `std::internal`: 控制对齐方式。
   - `std::boolalpha`: 将布尔值以文本形式输出。
   - `std::hex`, `std::dec`, `std::oct`: 控制整数的输出进制。
   - 等等。

2. **流控制器（Stream Control）：**
   - `std::fixed`, `std::scientific`: 控制浮点数的输出格式。
   - `std::showpoint`: 总是显示小数点。
   - `std::noshowpoint`: 不显示小数点。
   - `std::uppercase`: 使用大写字母表示科学计数法中的指数部分。
   - `std::nouppercase`: 使用小写字母表示科学计数法中的指数部分。
   - 等等。

3. **标志（Flags）：**
   - `std::ios::fmtflags`: 标志位，用于控制输入输出流的格式状态。
   - `std::ios::flags()`: 设置或查询格式标志位。
   - `std::ios::setf()`, `std::ios::unsetf()`: 设置或取消设置格式标志位。
   - 等等。

4. **函数：**
   - `std::setiosflags()`, `std::resetiosflags()`: 设置或重置格式标志位。
   - `std::get_money()`, `std::put_money()`: 对货币值进行输入输出。
   - `std::get_time()`, `std::put_time()`: 对时间进行输入输出。
   - 等等。

### 示例：
```cpp
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

int main() {
    int num = 123;
    double pi = 3.14159;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::cout << std::setw(10) << num << std::endl; // 设置域宽为 10
    std::cout << std::setprecision(3) << pi << std::endl; // 设置浮点数的精度为 3
    std::cout << std::setfill('*') << std::setw(8) << num << std::endl; // 设置域宽为 8，填充字符为 '*'
    std::cout << std::left << std::setw(8) << num << std::endl; // 左对齐
    std::cout << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << std::endl; // 输出时间

    return 0;
}
```

以上示例展示了 `<iomanip>` 头文件中一些常用操作的使用方法，如设置域宽、设置精度、设置填充字符、对齐方式、时间输出等。这些操作可以用于调整输出格式以及处理特定类型的输入输出。

## C++ <iomanip>标准库 常用类和函数

`<iomanip>` 标准库提供了多种类和函数，用于格式化输入输出。以下是其中一些常用的类和函数：

### 常用操纵符（Manipulators）：
- **`std::setw(int n)`**：设置下一个输出项的宽度为 `n`。
- **`std::setprecision(int n)`**：设置浮点数的输出精度为 `n`。
- **`std::setfill(char c)`**：设置填充字符为 `c`。
- **`std::left`, `std::right`, `std::internal`**：控制对齐方式。
- **`std::boolalpha`**：以文本形式输出布尔值（true/false）。
- **`std::hex`, `std::dec`, `std::oct`**：控制整数的输出进制。
- **`std::fixed`, `std::scientific`**：控制浮点数的输出格式。
- **`std::showpoint`**：总是显示小数点。
- **`std::uppercase`**：使用大写字母表示科学计数法中的指数。
- 等等。

### 流控制器（Stream Control）：
- **`std::ios::fmtflags`**：用于控制输入输出流的格式状态。
- **`std::ios::flags()`**：设置或查询格式标志位。
- **`std::ios::setf()`, `std::ios::unsetf()`**：设置或取消设置格式标志位。
- **`std::setiosflags()`, `std::resetiosflags()`**：设置或重置格式标志位。
- 等等。

### 函数：
- **`std::get_money()`**, **`std::put_money()`**: 对货币值进行输入输出。
- **`std::get_time()`**, **`std::put_time()`**: 对时间进行输入输出。
- 等等。

这些类和函数可用于控制输入输出流的格式，包括对宽度、精度、对齐方式、填充字符、数字格式、时间格式等进行设置和调整。

## std::setw()

`std::setw()` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于设置下一个输出项的宽度。

### 函数签名：
```cpp
std::setw(int n);
```

- `n`：整数值，用于设置下一个输出项的宽度为 `n`。
- 返回值：`std::setw()` 不返回任何值。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 123;
    double pi = 3.14159;

    // 设置域宽为 10
    std::cout << std::setw(10) << num << std::endl;
    std::cout << std::setw(10) << pi << std::endl;

    return 0;
}
```

在上面的示例中，`std::setw(10)` 用于设置输出项的宽度为 10。这意味着下一个输出的内容将在占用的字符宽度上占据 10 个字符位置。如果实际内容不足以填充这个宽度，空格将被用作填充字符。

## std::setprecision()

`std::setprecision()` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于设置浮点数的输出精度。

### 函数签名：
```cpp
std::setprecision(int n);
```

- `n`：整数值，用于设置浮点数的输出精度为 `n`。
- 返回值：`std::setprecision()` 不返回任何值。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159;

    // 设置浮点数的输出精度为 3
    std::cout << std::setprecision(3) << pi << std::endl;

    return 0;
}
```

在上面的示例中，`std::setprecision(3)` 用于设置输出浮点数的小数位精度为 3。这意味着浮点数在输出时将只显示到小数点后 3 位。

## std::setfill()

`std::setfill()` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于设置填充字符。

### 函数签名：
```cpp
std::setfill(char c);
```

- `c`：字符类型，表示要设置的填充字符。
- 返回值：`std::setfill()` 不返回任何值。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 123;

    // 设置填充字符为 '*'
    std::cout << std::setfill('*') << std::setw(8) << num << std::endl;

    return 0;
}
```

在上面的示例中，`std::setfill('*')` 用于设置填充字符为星号 `*`，而 `std::setw(8)` 则用于设置输出项的宽度为 8。这意味着如果实际输出项的字符数少于 8 个，则用星号填充空余位置。

## std::left()

`std::left` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于左对齐输出。

### 使用方法：
```cpp
std::left
```

`std::left` 被应用于输出流之后，将使得后续的输出项（例如使用 `std::setw()` 设置宽度后的输出）左对齐显示。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 123;

    // 左对齐输出
    std::cout << std::left << std::setw(8) << num << std::endl;

    return 0;
}
```

在上面的示例中，`std::left` 用于设置输出的左对齐。`std::setw(8)` 则用于设置输出项的宽度为 8，如果实际输出项的字符数少于 8 个，则在右侧填充空余位置以保持左对齐输出。

## std::right()

`std::right` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于右对齐输出。

### 使用方法：
```cpp
std::right
```

`std::right` 被应用于输出流之后，将使得后续的输出项（例如使用 `std::setw()` 设置宽度后的输出）右对齐显示。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 123;

    // 右对齐输出
    std::cout << std::right << std::setw(8) << num << std::endl;

    return 0;
}
```

在上面的示例中，`std::right` 用于设置输出的右对齐。`std::setw(8)` 则用于设置输出项的宽度为 8，如果实际输出项的字符数少于 8 个，则在左侧填充空余位置以保持右对齐输出。

## std::internal()

`std::internal` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于内部对齐输出。

### 使用方法：
```cpp
std::internal
```

`std::internal` 被应用于输出流之后，将使得后续的输出项（例如使用 `std::setw()` 设置宽度后的输出）在输出时，数字等内部对齐。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = -123;

    // 内部对齐输出
    std::cout << std::internal << std::setw(8) << num << std::endl;

    return 0;
}
```

在上面的示例中，`std::internal` 用于设置输出的内部对齐。`std::setw(8)` 用于设置输出项的宽度为 8。对于带有符号的整数，使用内部对齐时，会在数字之前打印符号，并将数字右对齐。

## std::boolalpha()

`std::boolalpha` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于控制布尔值的输出格式。

### 使用方法：
```cpp
std::boolalpha
```

`std::boolalpha` 被应用于输出流之后，将使得后续的布尔值输出为文本形式，即 `true` 或 `false`，而非默认的整数值输出（1 或 0）。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    bool status = true;

    // 设置布尔值的输出为文本形式
    std::cout << std::boolalpha << status << std::endl;

    return 0;
}
```

在上面的示例中，`std::boolalpha` 被用于设置布尔值的输出为文本形式，所以 `status` 的值 `true` 将以文本形式输出。

## std::hex()

`std::hex` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于控制整数输出的进制为十六进制。

### 使用方法：
```cpp
std::hex
```

`std::hex` 被应用于输出流之后，将使得后续的整数输出为十六进制形式。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 255;

    // 设置整数输出为十六进制形式
    std::cout << std::hex << num << std::endl;

    return 0;
}
```

在上面的示例中，`std::hex` 被用于设置整数输出为十六进制形式，所以 `num` 的值 255 将以十六进制形式输出为 `ff`。

## std::dex()

`std::dec` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于将整数的输出进制设置为十进制。

### 使用方法：
```cpp
std::dec
```

`std::dec` 被应用于输出流之后，将使得后续的整数输出为十进制形式。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 255;

    // 设置整数输出为十六进制形式
    std::cout << std::hex << num << std::endl;

    // 设置整数输出为十进制形式
    std::cout << std::dec << num << std::endl;

    return 0;
}
```

在上面的示例中，首先使用 `std::hex` 将整数输出设置为十六进制形式输出 `num` 的值为 `ff`，然后使用 `std::dec` 将整数输出设置回十进制形式输出 `num` 的值为 `255`。

## std::oct()

`std::oct` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于将整数输出的进制设置为八进制。

### 使用方法：
```cpp
std::oct
```

`std::oct` 被应用于输出流之后，将使得后续的整数输出为八进制形式。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    int num = 255;

    // 设置整数输出为八进制形式
    std::cout << std::oct << num << std::endl;

    return 0;
}
```

在上面的示例中，`std::oct` 被用于设置整数输出为八进制形式，所以 `num` 的值 `255` 将以八进制形式输出为 `377`。

## std::fixed()

`std::fixed` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于控制浮点数的输出格式为固定点表示法（fixed-point notation）。

### 使用方法：
```cpp
std::fixed
```

`std::fixed` 被应用于输出流之后，将使得后续的浮点数输出使用固定的小数点位数（小数部分不会自动省略）。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    double value = 123.456789;

    // 设置浮点数输出为固定点表示法
    std::cout << std::fixed << value << std::endl;

    return 0;
}
```

在上面的示例中，`std::fixed` 被用于设置浮点数的输出格式为固定点表示法，因此 `value` 的值 `123.456789` 将以固定的小数点位数输出为 `123.456789`。

## std::scientific

`std::scientific` 是 `<iomanip>` 标准库中的操纵符（manipulator），用于控制浮点数的输出格式为科学计数法（scientific notation）。

### 使用方法：
```cpp
std::scientific
```

`std::scientific` 被应用于输出流之后，将使得后续的浮点数输出使用科学计数法表示。

### 用法示例：
```cpp
#include <iostream>
#include <iomanip>

int main() {
    double value = 123456.789;

    // 设置浮点数输出为科学计数法
    std::cout << std::scientific << value << std::endl;

    return 0;
}
```

在上面的示例中，`std::scientific` 被用于设置浮点数的输出格式为科学计数法，因此 `value` 的值 `123456.789` 将以科学计数法形式输出为 `1.234568e+05`。

## std::showpoint()

`std::showpoint()` 是 C++ 中用于控制输出浮点数的标志之一。它用于在输出浮点数时始终显示小数点，并显示末尾的零。在使用它后，无论小数部分是否为零，都会显示小数点和末尾的零。

在中文中，`std::showpoint()` 可以翻译为 "显示小数点"，用于指示程序在输出浮点数时应始终显示小数点及其后的零。

## std::noshowpoint()

`std::noshowpoint()` 是 C++ 中用于控制浮点数输出的标志之一。它用于取消使用 `std::showpoint()` 设置，即停止在输出浮点数时始终显示小数点及其后的零。

在中文中，`std::noshowpoint()` 可以翻译为 "不显示小数点"，用于指示程序在输出浮点数时不显示小数点及其后的零。

## std::uppercase

`std::uppercase` 是 C++ 中用于控制输出的标志之一，它用于设置输出中的字母部分为大写字母。通常，它与输出十六进制数字时一起使用，以确保字母部分以大写形式显示。

例如，当使用输出操作符 `<<` 将整数以十六进制格式输出时，设置了 `std::uppercase` 标志后，输出的字母部分（A-F）将以大写字母显示。

在中文中，`std::uppercase` 可以翻译为 "大写"，表示将输出转换为大写形式。

## std::nouppercase

`std::nouppercase` 是 C++ 中用于控制输出的标志之一，它用于取消设置输出中字母部分为大写字母的状态，即停止将输出的字母部分强制转换为大写形式。

通常情况下，`std::nouppercase` 用于取消之前设置的 `std::uppercase` 标志，使得输出的字母部分恢复到默认的小写形式。

在中文中，`std::nouppercase` 可以翻译为 "不大写"，表示取消将输出转换为大写形式的设置。

## std::ios::fmtflags

`std::ios::fmtflags` 是 C++ 中的一种数据类型，用于表示输入/输出流的格式标志。它是 `std::ios` 类的一部分，用于存储各种控制输出格式的标志位，比如用于控制流的各种格式设置，如对齐、小数点精度、数制、浮点数的显示方式等等。

这个类型通常用于控制输出格式的相关设置，例如 `std::ios::hex` 用于设置输出流的进制为十六进制，`std::ios::scientific` 用于设置输出流的科学计数法等等。

它是一个位掩码枚举类型，意味着它的值可以是多个位的组合。通过将各种格式标志进行按位或操作，可以创建包含多个格式标志的组合。

例如：
```cpp
#include <iostream>

int main() {
    std::ios::fmtflags flags = std::cout.flags(); // 获取当前输出流的格式标志

    flags |= std::ios::hex; // 设置输出流的进制为十六进制
    flags &= ~std::ios::dec; // 取消输出流的十进制设置

    std::cout.flags(flags); // 应用新的格式标志

    return 0;
}
```

这里的 `std::ios::fmtflags` 用于存储输出流的格式标志，可以随后使用按位操作符进行修改，并通过 `std::cout.flags()` 和 `std::cout.flags(flags)` 方法来获取和设置流的格式标志。

## std::ios::flags

`std::ios::flags` 是 C++ 中的一个成员函数，而非数据类型。这个函数用于设置流的格式标志（flags），它属于 `std::ios` 类的一部分，用于控制输入/输出流的格式。

这个成员函数的作用是设置流的格式控制标志。它接受一个参数，该参数是一个 `std::ios::fmtflags` 类型的值，这个值包含了要设置的格式标志的组合。

例如，可以使用 `std::ios::hex` 标志将输出流的进制设置为十六进制。示例代码如下：

```cpp
#include <iostream>

int main() {
    std::cout.setf(std::ios::hex); // 设置输出流的进制为十六进制
    std::cout << 255 << std::endl; // 输出 255 的十六进制表示

    return 0;
}
```

在这个例子中，`std::cout.setf(std::ios::hex)` 用于设置输出流的格式标志为十六进制格式。接下来的 `std::cout << 255 << std::endl` 将以十六进制形式输出整数 255。

`std::ios::flags` 函数主要用于设置输出流的格式标志，以控制输出流的显示格式，比如控制进制、对齐方式、浮点数的显示方式等等。

## std::ios::setf()

`std::ios::setf()` 是 C++ 中用于设置流的格式标志的成员函数之一。它属于 `std::ios` 类的一部分，用于控制输入/输出流的格式。

这个函数允许你设置指定的格式标志，接受一个参数，即格式标志的组合。你可以使用这个函数来设置需要的格式标志，例如设置浮点数的显示方式、数制、对齐方式等等。

示例代码如下：

```cpp
#include <iostream>

int main() {
    std::cout.setf(std::ios::hex); // 设置输出流的进制为十六进制
    std::cout << 255 << std::endl; // 输出 255 的十六进制表示

    return 0;
}
```

在这个例子中，`std::cout.setf(std::ios::hex)` 被用来设置输出流的格式标志为十六进制格式。接下来的 `std::cout << 255 << std::endl` 将以十六进制形式输出整数 255。

`std::ios::setf()` 函数是 `std::ios` 类中用于设置格式标志的函数之一，用于控制输出流的显示格式。

## std::ios::unsetf()

`std::unsetf()` 是 C++ 中用于取消流的格式标志的成员函数之一，属于 `std::ios` 类的一部分。它允许你取消特定的格式标志，将其从流的当前格式状态中移除。

这个函数接受一个参数，即要取消的格式标志。它可以取消先前通过 `std::ios::setf()` 或其他设置格式标志的方式设置的标志。

示例代码如下所示：

```cpp
#include <iostream>

int main() {
    std::cout.setf(std::ios::hex); // 设置输出流的进制为十六进制
    std::cout << 255 << std::endl; // 输出 255 的十六进制表示

    std::cout.unsetf(std::ios::hex); // 取消输出流的十六进制格式标志

    std::cout << 255 << std::endl; // 输出 255 的默认十进制表示

    return 0;
}
```

在这个例子中，首先使用 `std::cout.setf(std::ios::hex)` 设置了输出流的格式标志为十六进制格式。接下来的 `std::cout << 255 << std::endl` 输出了整数 255 的十六进制表示。

然后使用 `std::cout.unsetf(std::ios::hex)` 取消了输出流的十六进制格式标志。最后的 `std::cout << 255 << std::endl` 输出了整数 255 的默认十进制表示，因为已取消了十六进制格式标志。

`std::ios::unsetf()` 函数用于取消先前设置的特定格式标志，以便在输出流的格式状态中移除该标志。

## std::setiosflags()

`std::setiosflags()` 是 C++ 中用于设置流格式标志的函数之一，用于控制输入/输出流的格式。这个函数可以设置指定的格式标志，其效果类似于 `std::ios::setf()`。

```cpp
#include <iostream>

int main() {
    std::cout << std::setiosflags(std::ios::hex); // 设置输出流的进制为十六进制
    std::cout << 255 << std::endl; // 输出 255 的十六进制表示

    return 0;
}
```

在这个例子中，`std::setiosflags(std::ios::hex)` 被用来设置输出流的格式标志为十六进制格式。接下来的 `std::cout << 255 << std::endl` 将以十六进制形式输出整数 255。

`std::setiosflags()` 可以用于设置指定的格式标志，与 `std::ios::setf()` 类似，允许控制输出流的显示格式。

## std::resetiosflags()

`std::resetiosflags()` 是 C++ 中用于重置流的格式标志的函数之一，用于控制输入/输出流的格式。它的作用是取消指定的格式标志，将其从流的当前格式状态中移除。

这个函数接受一个参数，即要重置的格式标志。它可以用来取消先前通过 `std::ios::setf()`、`std::setiosflags()` 或其他设置格式标志的方式设置的标志。

示例代码如下所示：

```cpp
#include <iostream>
#include <iomanip>

int main() {
    std::cout.setf(std::ios::hex); // 设置输出流的进制为十六进制
    std::cout << 255 << std::endl; // 输出 255 的十六进制表示

    std::cout << std::resetiosflags(std::ios::hex); // 重置输出流的十六进制格式标志

    std::cout << 255 << std::endl; // 输出 255 的默认十进制表示

    return 0;
}
```

在这个例子中，首先使用 `std::cout.setf(std::ios::hex)` 设置了输出流的格式标志为十六进制格式。接下来的 `std::cout << 255 << std::endl` 输出了整数 255 的十六进制表示。

然后使用 `std::cout << std::resetiosflags(std::ios::hex)` 重置了输出流的十六进制格式标志。最后的 `std::cout << 255 << std::endl` 输出了整数 255 的默认十进制表示，因为已经重置了十六进制格式标志。

`std::resetiosflags()` 函数用于取消先前设置的特定格式标志，以便从输出流的格式状态中移除该标志。

## std::get_money()

`std::get_money()` 是 C++ 标准库 `<iomanip>` 头文件中提供的一个函数，用于将字符串解析为货币值，并将其存储到 `std::money_get` 类型对象返回的结果中。它通常与 `std::put_money()` 一起使用，后者用于将货币值以指定的格式输出到输出流中。

这个函数的声明如下：

```cpp
std::money_get<charT, InputIterator> get_money(
    T &val, bool intl = false);
```

其中：

- `charT` 是字符类型。
- `InputIterator` 是输入迭代器类型。
- `val` 是要存储货币值的对象。
- `intl` 是一个布尔值，指示货币值是否采用国际化格式（如果为 `true`，则表示使用国际化货币格式）。

例如，可以使用 `std::get_money()` 将字符串解析为货币值，然后将其输出到输出流中。示例代码如下：

```cpp
#include <iostream>
#include <iomanip>
#include <locale>

int main() {
    std::string input = "123.45"; // 要解析的字符串
    std::stringstream ss(input); // 创建字符串流

    double value;
    std::locale loc(std::locale(), new std::moneypunct<char, false>);
    std::moneypunct_byname<char, false> const& mpunct = std::use_facet<std::moneypunct_byname<char, false>>(loc);

    std::ios_base::iostate err;
    ss.imbue(loc);
    ss >> std::get_money(value, false);

    if (ss.fail()) {
        std::cout << "Parsing failed\n";
    } else {
        std::cout << "Parsed value: " << value << '\n';
    }

    return 0;
}
```

在这个例子中，字符串 "123.45" 被解析为货币值，存储在 `value` 中，并输出到标准输出流中。需要注意的是，这是一个简化的示例，实际的用法可能涉及更多的设置和错误处理。

## std::put_money()

`std::put_money()` 是 C++ 标准库 `<iomanip>` 头文件中提供的一个函数，用于将货币值以指定的格式输出到输出流中。通常与 `std::get_money()` 一起使用，后者用于将字符串解析为货币值。

这个函数的声明如下：

```cpp
std::money_put<charT, OutputIterator> put_money(
    std::basic_ostream<charT>& os, bool intl, T val);
```

其中：

- `charT` 是字符类型。
- `OutputIterator` 是输出迭代器类型。
- `os` 是要写入的输出流。
- `intl` 是一个布尔值，指示货币值是否采用国际化格式（如果为 `true`，则表示使用国际化货币格式）。
- `val` 是要输出的货币值。

例如，可以使用 `std::put_money()` 将货币值以指定的格式输出到输出流中。示例代码如下：

```cpp
#include <iostream>
#include <iomanip>
#include <locale>

int main() {
    double value = 123.45; // 要输出的货币值

    std::cout.imbue(std::locale("en_US.UTF-8")); // 设置本地化信息
    std::cout << "Formatted output: " << std::put_money(value, true) << std::endl;

    return 0;
}
```

在这个例子中，货币值 123.45 被以国际化的货币格式输出到标准输出流中。这是一个简化的示例，实际的用法可能涉及更多的设置和本地化信息的处理。

## std::get_time()

`std::get_time()` 是 C++ 中 `<iomanip>` 头文件中提供的函数，用于将字符串解析为时间对象 `std::tm`。这个函数允许你从字符串中提取日期和时间信息，并将其存储在 `std::tm` 结构中。

这个函数的声明如下：

```cpp
std::istreambuf_iterator<charT> get_time(
    std::istreambuf_iterator<charT>& s,
    const charT* fmt,
    std::tm* tmb);
```

其中：

- `charT` 是字符类型。
- `s` 是指向输入流的迭代器。
- `fmt` 是描述日期和时间格式的 C 字符串。
- `tmb` 是指向 `std::tm` 结构的指针，用于存储解析后的日期和时间信息。

示例代码如下所示：

```cpp
#include <iostream>
#include <iomanip>
#include <ctime>

int main() {
    std::tm tmb;
    std::istringstream ss("2023-12-09 15:30:00"); // 要解析的时间字符串
    ss >> std::get_time(&tmb, "%Y-%m-%d %H:%M:%S"); // 解析时间字符串并存储到 std::tm 结构中

    if (ss.fail()) {
        std::cout << "Parsing failed\n";
    } else {
        std::cout << "Parsed date and time: "
                  << std::put_time(&tmb, "%Y-%m-%d %H:%M:%S") << std::endl;
    }

    return 0;
}
```

在这个例子中，字符串 "2023-12-09 15:30:00" 被解析为时间对象 `std::tm`，并存储在 `tmb` 中。然后，`std::put_time()` 被用于格式化输出解析后的日期和时间信息。如果解析失败，将输出 "Parsing failed"。这是一个简化的示例，实际的用法可能涉及更多的错误处理和格式化字符串。

## std::put_time()

`std::put_time()` 是 C++ 中 `<iomanip>` 头文件中提供的一个函数，用于将时间对象 `std::tm` 按照指定的格式输出为字符串。

这个函数的声明如下：

```cpp
std::ostreambuf_iterator<charT> put_time(
    const std::tm* tmb,
    const charT* fmt);
```

其中：

- `tmb` 是指向 `std::tm` 结构的指针，包含要格式化的时间信息。
- `fmt` 是描述日期和时间格式的 C 字符串。

示例代码如下：

```cpp
#include <iostream>
#include <iomanip>
#include <ctime>

int main() {
    std::tm timeinfo = {}; // 初始化时间结构
    timeinfo.tm_year = 2023 - 1900; // 年份减去1900
    timeinfo.tm_mon = 11; // 月份，0-11 表示一月到十二月
    timeinfo.tm_mday = 9; // 日
    timeinfo.tm_hour = 15; // 时
    timeinfo.tm_min = 30; // 分
    timeinfo.tm_sec = 0; // 秒

    std::cout << "Formatted time: " << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;

    return 0;
}
```

在这个示例中，`std::put_time()` 被用于格式化输出 `std::tm` 结构中的时间信息。指定的格式字符串 `"%Y-%m-%d %H:%M:%S"` 代表了年月日时分秒的格式。这样的调用将会把时间信息格式化为字符串，并输出到标准输出流中。

需要注意的是，`std::put_time()` 在 C++11 中引入，用于便捷地格式化时间信息并输出为字符串。