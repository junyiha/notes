## 简介

+ C++ random标准库笔记

## C++ random标准库是什么 

C++ 标准库中的 `<random>` 头文件提供了用于生成随机数的工具和类。这个库提供了众多的随机数生成器和分布器，以支持高质量的随机数生成操作。使用 `<random>` 头文件可以生成各种类型的随机数，包括整数、浮点数以及其他分布的随机数。

以下是一些 `<random>` 头文件中常用的类和功能：

1. **随机数引擎（Random Number Engines）**：随机数引擎是一种生成随机数的算法。C++ 提供了几种不同的随机数引擎，例如 `std::default_random_engine`、`std::mt19937`（Mersenne Twister 引擎）等。

2. **分布器（Random Number Distributions）**：分布器用于将随机数引擎生成的随机数映射到指定的分布上，如均匀分布、正态分布等。常见的分布器有 `std::uniform_int_distribution`（生成整数均匀分布）、`std::uniform_real_distribution`（生成浮点数均匀分布）等。

3. **随机设备（Random Devices）**：`std::random_device` 是一个用于获取真随机数的设备，但其随机性取决于平台和实现。

使用 `<random>` 头文件，可以轻松地生成随机数，并根据需要控制其分布特性。例如，以下是一个简单的示例，展示了如何使用随机数引擎和分布器生成随机整数：

```cpp
#include <iostream>
#include <random>

int main() {
    // 创建随机数引擎和分布器
    std::random_device rd; // 随机设备
    std::mt19937 gen(rd()); // Mersenne Twister 引擎
    std::uniform_int_distribution<> dis(1, 100); // 生成1到100之间的均匀分布的随机整数

    // 生成随机数
    for (int i = 0; i < 10; ++i) {
        int random_number = dis(gen);
        std::cout << random_number << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

以上示例使用 Mersenne Twister 引擎和均匀整数分布器生成了10个1到100之间的随机整数。

`<random>` 标准库提供了灵活和强大的工具，可用于各种需要随机性的应用程序，例如模拟、密码学、游戏开发等。

## C++ <random>标准库 详解

`<random>` 是 C++ 标准库中用于生成随机数的头文件。它提供了一组类和函数，用于生成高质量的随机数，并支持不同的随机数引擎和分布。

下面是 `<random>` 头文件中一些重要的类和函数：

1. **随机数引擎（Random Number Engines）**：随机数引擎是一个产生随机数序列的算法。C++ 提供了多种随机数引擎，例如 `std::default_random_engine`、`std::mt19937`（Mersenne Twister 引擎）、`std::minstd_rand`（线性同余法引擎）等。你可以根据需要选择不同的引擎。

2. **随机数分布器（Random Number Distributions）**：随机数分布器用于将随机数引擎生成的随机数映射到指定的分布上。常用的分布器包括 `std::uniform_int_distribution`（生成整数均匀分布）、`std::uniform_real_distribution`（生成浮点数均匀分布）、`std::normal_distribution`（生成正态分布）、`std::poisson_distribution`（生成泊松分布）等。

3. **随机设备（Random Devices）**：`std::random_device` 是一个用于获取真随机数的设备。它可能会提供硬件随机数或者伪随机数，具体取决于实现和平台。可以用它来初始化随机数引擎，提供更好的随机性。

下面是一个简单示例，演示了如何使用 `<random>` 头文件生成随机数：

```cpp
#include <iostream>
#include <random>

int main() {
    // 创建随机设备和引擎
    std::random_device rd;
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎

    // 创建均匀分布器并生成随机整数
    std::uniform_int_distribution<> dis(1, 100); // 生成1到100之间的均匀分布的随机整数

    // 生成随机数
    for (int i = 0; i < 10; ++i) {
        int random_number = dis(gen);
        std::cout << random_number << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

这个示例使用 Mersenne Twister 引擎和均匀整数分布器生成了10个1到100之间的随机整数。

`<random>` 头文件提供了灵活且高效的随机数生成工具，可以满足各种应用程序对随机性的需求。当你需要生成随机数时，可以根据自己的需求选择合适的引擎和分布器。

## C++ std::random_device 是什么

`std::random_device` 是 C++ 标准库提供的类，用于获取真随机数。它被设计为一个可用于产生高质量随机数种子的设备，可以提供来自硬件和操作系统的真随机数，也可以提供伪随机数。

`std::random_device` 可以用作随机数引擎的种子（如 Mersenne Twister 引擎 `std::mt19937`）的初始化器，以提供更好的随机性。

然而，需要注意的是，`std::random_device` 并不是在所有平台和实现上都能提供真正的硬件随机数。在某些系统上，它可能会退化成伪随机数生成器，或者可能由于系统限制而无法提供高质量的随机数。

通常，`std::random_device` 是作为初始化随机数引擎的种子使用，而不是直接生成随机数序列。下面是一个简单的示例，演示了如何使用 `std::random_device` 初始化 Mersenne Twister 引擎：

```cpp
#include <iostream>
#include <random>

int main() {
    // 创建随机设备
    std::random_device rd;

    // 使用随机设备来初始化 Mersenne Twister 引擎
    std::mt19937 gen(rd());

    // 创建均匀分布器并生成随机整数
    std::uniform_int_distribution<> dis(1, 100); // 生成1到100之间的均匀分布的随机整数

    // 生成随机数
    for (int i = 0; i < 10; ++i) {
        int random_number = dis(gen);
        std::cout << random_number << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

这个示例中，`std::random_device` 用于初始化了 Mersenne Twister 引擎 `std::mt19937`，然后使用该引擎生成了10个1到100之间的随机整数。

## C++ std::random_device详解

`std::random_device` 是 C++ 标准库提供的类，用于获取随机数的设备。它旨在提供高质量的随机数种子，可用作随机数引擎的初始化器，以生成更好质量的随机数序列。

以下是关于 `std::random_device` 的详细说明：

1. **随机性**：
   - `std::random_device` 通常被设计为提供真随机数，但实现的随机性取决于底层操作系统和硬件设备的支持。
   - 在大多数情况下，`std::random_device` 会尝试获取来自硬件设备或操作系统的真随机数。但有些平台可能会将其实现为伪随机数生成器，特别是当没有真正的硬件随机数可用时，或者由于平台限制而无法提供真随机性。

2. **用途**：
   - 最常见的用途是作为随机数引擎的种子。它可以提供一个高质量的种子，用于初始化伪随机数生成器（如 Mersenne Twister 引擎 `std::mt19937`）。
   - 在生成密码学安全的随机数时，`std::random_device` 通常用作种子。

3. **生成随机数序列**：
   - `std::random_device` 并不直接生成随机数序列，而是产生用于初始化随机数引擎的种子。
   - 一般地，通过使用 `std::random_device` 初始化随机数引擎，然后再使用引擎生成随机数序列。

4. **初始化引擎**：
   - 初始化引擎时，通常将 `std::random_device` 作为种子参数传递给引擎构造函数或作为引擎对象的参数。
   - 例如：`std::mt19937 gen(rd());`，其中 `rd` 是 `std::random_device` 的一个实例。

5. **实现依赖性**：
   - `std::random_device` 在不同的平台和编译器实现中可能表现不同，有些平台可能无法提供真随机数，或者提供的随机性不足。

总的来说，`std::random_device` 是用于获取随机数种子的一种机制。在大多数情况下，它能够提供高质量的随机数种子，以供初始化伪随机数生成器。但在某些特定情况下，可能会受到平台限制或实现差异的影响。