## 简介

+ C++ <cmath>标准库

## C++ <cmath>标准库

在C++中，`<cmath>`是一个标准库头文件，它提供了许多数学函数的声明，这些函数可以用于执行各种数学计算。这个头文件中包含了常见的数学函数，如三角函数、对数函数、指数函数、幂函数等。

以下是一些`<cmath>`头文件中常见的函数：

1. **三角函数**：
    - `sin()`, `cos()`, `tan()`: 计算正弦、余弦、正切值。
    - `asin()`, `acos()`, `atan()`: 计算反正弦、反余弦、反正切值。

2. **对数和指数函数**：
    - `log()`, `log10()`: 计算自然对数和以10为底的对数。
    - `exp()`: 计算自然指数。
    - `pow()`: 计算一个数的幂。

3. **取整函数**：
    - `ceil()`: 向上取整。
    - `floor()`: 向下取整。
    - `round()`: 四舍五入。

4. **其他函数**：
    - `sqrt()`: 计算平方根。
    - `abs()`: 计算绝对值。

这些函数可以用于各种数学计算，例如科学计算、几何计算、物理学计算等。使用这些函数需要包含`<cmath>`头文件，并且调用时要注意函数参数的类型和返回值。

## C++ <cmath>标准库 详解

`<cmath>` 是 C++ 标准库中提供的一个头文件，用于数学运算。这个头文件中包含了一系列数学函数的声明，可以进行常用的数学计算，比如三角函数、对数函数、指数函数等。

以下是 `<cmath>` 头文件中常见函数的详细说明：

### 1. 三角函数：

- `double sin(double arg)`, `float sinf(float arg)`, `long double sinl(long double arg)`: 计算正弦值。
- `double cos(double arg)`, `float cosf(float arg)`, `long double cosl(long double arg)`: 计算余弦值。
- `double tan(double arg)`, `float tanf(float arg)`, `long double tanl(long double arg)`: 计算正切值。
  
  这些函数的参数是角度（弧度制），返回值是对应的三角函数值。

- `double asin(double arg)`, `float asinf(float arg)`, `long double asinl(long double arg)`: 计算反正弦值。
- `double acos(double arg)`, `float acosf(float arg)`, `long double acosl(long double arg)`: 计算反余弦值。
- `double atan(double arg)`, `float atanf(float arg)`, `long double atanl(long double arg)`: 计算反正切值。

### 2. 对数和指数函数：

- `double log(double arg)`, `float logf(float arg)`, `long double logl(long double arg)`: 计算自然对数。
- `double log10(double arg)`, `float log10f(float arg)`, `long double log10l(long double arg)`: 计算以10为底的对数。

  这些函数的参数是正数，返回值是对数值。

- `double exp(double arg)`, `float expf(float arg)`, `long double expl(long double arg)`: 计算自然指数。

### 3. 幂函数：

- `double pow(double base, double exponent)`, `float powf(float base, float exponent)`, `long double powl(long double base, long double exponent)`: 计算幂。

  这些函数的参数是底数和指数，返回值是底数的指定次幂。

### 4. 取整函数：

- `double ceil(double arg)`, `float ceilf(float arg)`, `long double ceill(long double arg)`: 向上取整。
- `double floor(double arg)`, `float floorf(float arg)`, `long double floorl(long double arg)`: 向下取整。
- `double round(double arg)`, `float roundf(float arg)`, `long double roundl(long double arg)`: 四舍五入。

### 5. 其他函数：

- `double sqrt(double arg)`, `float sqrtf(float arg)`, `long double sqrtl(long double arg)`: 计算平方根。
- `int abs(int arg)`, `long int labs(long int arg)`, `long long int llabs(long long int arg)`: 计算整数的绝对值。

这些函数是C++标准库提供的一小部分数学函数。它们可以被用于各种数学计算和科学计算的场景中。函数名称可能有细微的变化，这取决于使用的参数类型（`float`、`double`、`long double`）和函数的重载。

## sin()

`sin()` 函数是 `<cmath>` 头文件中包含的一个三角函数，用于计算给定角度的正弦值。在数学中，正弦函数表示一个角的对边与斜边的比值，通常使用弧度制来表示角度。

在 C++ 中，`sin()` 函数的原型有多个变种，以适应不同数据类型的参数。其中一种原型可能是：

```cpp
double sin(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算正弦值的角度（以弧度为单位）。
- 返回值是参数 `arg` 的正弦值（`double` 类型）。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double angle = 30.0; // 角度为30度
    double radians = angle * M_PI / 180.0; // 将角度转换为弧度

    double sinValue = sin(radians); // 计算角度为30度的正弦值
    std::cout << "Sin of " << angle << " degrees is: " << sinValue << std::endl;

    return 0;
}
```

在这个示例中，程序首先将角度从度转换为弧度（因为 `sin()` 函数接受弧度作为参数），然后使用 `sin()` 函数计算给定角度的正弦值，并输出结果。

## cos()

`cos()` 函数是 `<cmath>` 头文件中的另一个三角函数，用于计算给定角度的余弦值。在数学中，余弦函数表示一个角的邻边与斜边的比值，通常使用弧度制来表示角度。

在 C++ 中，`cos()` 函数的原型可能是：

```cpp
double cos(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算余弦值的角度（以弧度为单位）。
- 返回值是参数 `arg` 的余弦值（`double` 类型）。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double angle = 45.0; // 角度为45度
    double radians = angle * M_PI / 180.0; // 将角度转换为弧度

    double cosValue = cos(radians); // 计算角度为45度的余弦值
    std::cout << "Cos of " << angle << " degrees is: " << cosValue << std::endl;

    return 0;
}
```

在这个示例中，程序将角度从度转换为弧度（因为 `cos()` 函数接受弧度作为参数），然后使用 `cos()` 函数计算给定角度的余弦值，并输出结果。

## tan()

`tan()` 函数是 `<cmath>` 头文件中的三角函数，用于计算给定角度的正切值。在数学中，正切函数表示一个角的正弦值与余弦值的比值，通常使用弧度制来表示角度。

在 C++ 中，`tan()` 函数的原型可能是：

```cpp
double tan(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算正切值的角度（以弧度为单位）。
- 返回值是参数 `arg` 的正切值（`double` 类型）。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double angle = 60.0; // 角度为60度
    double radians = angle * M_PI / 180.0; // 将角度转换为弧度

    double tanValue = tan(radians); // 计算角度为60度的正切值
    std::cout << "Tan of " << angle << " degrees is: " << tanValue << std::endl;

    return 0;
}
```

在这个示例中，程序将角度从度转换为弧度（因为 `tan()` 函数接受弧度作为参数），然后使用 `tan()` 函数计算给定角度的正切值，并输出结果。

## asin()

`asin()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的反正弦值，返回值表示角度（以弧度为单位）。反正弦函数是正弦函数的反函数，它接受一个值并返回对应的角度。

在 C++ 中，`asin()` 函数的原型可能是：

```cpp
double asin(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算反正弦值的值，其范围应在 -1 到 1 之间。
- 返回值是参数 `arg` 的反正弦值（以弧度为单位），范围在 -π/2 到 π/2 之间。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 0.5; // 输入值为0.5

    double asinValue = asin(value); // 计算值为0.5的反正弦值
    double degrees = asinValue * 180.0 / M_PI; // 将弧度转换为角度

    std::cout << "Arcsine of " << value << " is: " << asinValue << " radians or " << degrees << " degrees" << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `asin()` 函数计算值为 0.5 的反正弦值，并将其转换为角度制进行输出。需要注意的是，输入的参数值应该在 -1 到 1 的范围内，否则结果可能会出现错误。

## acos()

`acos()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的反余弦值，返回值表示角度（以弧度为单位）。反余弦函数是余弦函数的反函数，它接受一个值并返回对应的角度。

在 C++ 中，`acos()` 函数的原型可能是：

```cpp
double acos(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算反余弦值的值，其范围应在 -1 到 1 之间。
- 返回值是参数 `arg` 的反余弦值（以弧度为单位），范围在 0 到 π 之间。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 0.5; // 输入值为0.5

    double acosValue = acos(value); // 计算值为0.5的反余弦值
    double degrees = acosValue * 180.0 / M_PI; // 将弧度转换为角度

    std::cout << "Arccosine of " << value << " is: " << acosValue << " radians or " << degrees << " degrees" << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `acos()` 函数计算值为 0.5 的反余弦值，并将其转换为角度制进行输出。需要注意的是，输入的参数值应该在 -1 到 1 的范围内，否则结果可能会出现错误。

## atan()

`atan()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的反正切值，返回值表示角度（以弧度为单位）。反正切函数是正切函数的反函数，它接受一个值并返回对应的角度。

在 C++ 中，`atan()` 函数的原型可能是：

```cpp
double atan(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算反正切值的值。
- 返回值是参数 `arg` 的反正切值（以弧度为单位），范围在 -π/2 到 π/2 之间。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 1.0; // 输入值为1.0

    double atanValue = atan(value); // 计算值为1.0的反正切值
    double degrees = atanValue * 180.0 / M_PI; // 将弧度转换为角度

    std::cout << "Arctangent of " << value << " is: " << atanValue << " radians or " << degrees << " degrees" << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `atan()` 函数计算值为 1.0 的反正切值，并将其转换为角度制进行输出。函数返回的是参数值的反正切值，表示为弧度制。

## log()

`log()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的自然对数。自然对数是以常数 e（自然对数的底）为底的对数。

在 C++ 中，`log()` 函数的原型可能是：

```cpp
double log(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算自然对数的值。
- 返回值是参数 `arg` 的自然对数值。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 10.0; // 输入值为10.0

    double logValue = log(value); // 计算值为10.0的自然对数
    std::cout << "Natural log of " << value << " is: " << logValue << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `log()` 函数计算值为 10.0 的自然对数，并将结果输出。自然对数函数 `log()` 以 e 为底进行计算，返回给定参数的自然对数值。

## log10()

`log10()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的以 10 为底的对数。

在 C++ 中，`log10()` 函数的原型可能是：

```cpp
double log10(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算以 10 为底的对数的值。
- 返回值是参数 `arg` 的以 10 为底的对数值。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 1000.0; // 输入值为1000.0

    double log10Value = log10(value); // 计算值为1000.0的以10为底的对数
    std::cout << "Log base 10 of " << value << " is: " << log10Value << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `log10()` 函数计算值为 1000.0 的以 10 为底的对数，并将结果输出。`log10()` 函数返回给定参数的以 10 为底的对数值。

## exp()

`exp()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的自然指数。自然指数是常数 e（自然对数的底）的幂次方。

在 C++ 中，`exp()` 函数的原型可能是：

```cpp
double exp(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算自然指数的幂次方。
- 返回值是常数 e 的 `arg` 次幂。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 2.0; // 输入值为2.0

    double expValue = exp(value); // 计算e的2.0次幂
    std::cout << "Exponential value of " << value << " is: " << expValue << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `exp()` 函数计算 e 的 2.0 次幂，并将结果输出。`exp()` 函数返回 e 的给定次幂的值。

## pow()

`pow()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的幂次方。

在 C++ 中，`pow()` 函数的原型可能是：

```cpp
double pow(double base, double exponent);
```

- `base` 是一个 `double` 类型的参数，表示要计算幂次方的底数。
- `exponent` 是一个 `double` 类型的参数，表示要计算的指数。
- 返回值是 `base` 的 `exponent` 次幂。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double base = 2.0; // 底数为2.0
    double exponent = 3.0; // 指数为3.0

    double result = pow(base, exponent); // 计算2.0的3.0次幂
    std::cout << base << " raised to the power of " << exponent << " is: " << result << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `pow()` 函数计算 2.0 的 3.0 次幂，并将结果输出。`pow()` 函数返回给定底数和指数的幂次方值。

## ceil()

`ceil()` 函数是 `<cmath>` 头文件中的一个函数，用于向上取整，即返回不小于参数的最小整数值。

在 C++ 中，`ceil()` 函数的原型可能是：

```cpp
double ceil(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要进行向上取整的值。
- 返回值是不小于参数 `arg` 的最小整数值，以 `double` 类型返回。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 3.14; // 输入值为3.14

    double ceilValue = ceil(value); // 进行向上取整
    std::cout << "Ceiling value of " << value << " is: " << ceilValue << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `ceil()` 函数对值 3.14 进行向上取整，并将结果输出。`ceil()` 函数返回不小于参数的最小整数值。

## floor()

`floor()` 函数是 `<cmath>` 头文件中的一个函数，用于向下取整，即返回不大于参数的最大整数值。

在 C++ 中，`floor()` 函数的原型可能是：

```cpp
double floor(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要进行向下取整的值。
- 返回值是不大于参数 `arg` 的最大整数值，以 `double` 类型返回。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 4.8; // 输入值为4.8

    double floorValue = floor(value); // 进行向下取整
    std::cout << "Floor value of " << value << " is: " << floorValue << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `floor()` 函数对值 4.8 进行向下取整，并将结果输出。`floor()` 函数返回不大于参数的最大整数值。

## round()

`round()` 函数是 `<cmath>` 头文件中的一个函数，用于四舍五入到最接近的整数。

在 C++ 中，`round()` 函数的原型可能是：

```cpp
double round(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要进行四舍五入的值。
- 返回值是参数 `arg` 最接近的整数值，以 `double` 类型返回。

请注意，在 C++11 中，还引入了另一个函数 `std::round()`, 它使用 `std::round()` 名称并位于 `<cmath>` 头文件中。这个函数的使用方式与上述示例相同。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 4.5; // 输入值为4.5

    double roundedValue = round(value); // 进行四舍五入
    std::cout << "Rounded value of " << value << " is: " << roundedValue << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `round()` 函数对值 4.5 进行四舍五入，并将结果输出。`round()` 函数返回最接近参数的整数值。

## sqrt()

`sqrt()` 函数是 `<cmath>` 头文件中的一个函数，用于计算给定参数的平方根。

在 C++ 中，`sqrt()` 函数的原型可能是：

```cpp
double sqrt(double arg);
```

- `arg` 是一个 `double` 类型的参数，表示要计算平方根的值。
- 返回值是参数 `arg` 的平方根，以 `double` 类型返回。

示例代码：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double value = 25.0; // 输入值为25.0

    double sqrtValue = sqrt(value); // 计算25.0的平方根
    std::cout << "Square root of " << value << " is: " << sqrtValue << std::endl;

    return 0;
}
```

在这个示例中，程序使用 `sqrt()` 函数计算值为 25.0 的平方根，并将结果输出。`sqrt()` 函数返回给定参数的平方根值。

## abs()

`abs()` 函数是 `<cstdlib>` 或 `<cmath>` 头文件中的一个函数，用于返回整数或浮点数的绝对值。

在 C++ 中，`abs()` 函数可以用于整数类型（如 `int`、`long`、`long long` 等）和浮点数类型（如 `float`、`double`）。

对于整数类型：

```cpp
#include <iostream>
#include <cstdlib>

int main() {
    int num = -10; // 输入值为-10

    int absValue = abs(num); // 计算-10的绝对值
    std::cout << "Absolute value of " << num << " is: " << absValue << std::endl;

    return 0;
}
```

对于浮点数类型：

```cpp
#include <iostream>
#include <cmath>

int main() {
    double num = -7.5; // 输入值为-7.5

    double absValue = std::abs(num); // 计算-7.5的绝对值
    std::cout << "Absolute value of " << num << " is: " << absValue << std::endl;

    return 0;
}
```

在这两个示例中，`abs()` 函数分别用于整数和浮点数，返回给定参数的绝对值。在整数情况下，可以使用 `<cstdlib>` 头文件中的 `abs()` 函数，而对于浮点数，则使用 `<cmath>` 头文件中的 `std::abs()` 函数。