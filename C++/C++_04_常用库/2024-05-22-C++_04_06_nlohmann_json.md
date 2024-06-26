---
category: Cpp
date: 2024-05-22 09:00:00 +0800
layout: post
title: C++_04_06_nlohmann_json
tag: CppLibrary
---
## 简介

+ nlohmann/json 库的相关笔记
+ nlohmann 是个人名,全称为 Niels Lohmann 尼尔斯-洛曼

## nlohmann/json 创建包含布尔值的数组

使用nlohmann/json库创建包含布尔值的数组非常简单。首先，确保你已经将该库包含到你的项目中。如果你使用CMake，可以将以下代码添加到你的CMakeLists.txt文件中：

```cmake
find_package(nlohmann_json REQUIRED)
```

然后，使用以下C++代码创建包含布尔值的数组：

```cpp
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    // 创建包含布尔值的数组
    nlohmann::json boolArray = {true, false, true, true, false};

    // 将JSON数组打印到控制台
    std::cout << boolArray << std::endl;

    return 0;
}
```

在上述示例中，我们首先包含了nlohmann/json库，然后创建了一个包含布尔值的数组 `boolArray`。最后，通过 `std::cout` 将JSON数组打印到控制台。

确保在项目中正确设置和使用nlohmann/json库，以便成功编译和运行这段代码。

## nlohmann/json 将std::vector作为值传给键

使用 nlohmann/json 库时，可以将 `std::vector` 作为 JSON 对象的值传递给键。下面是一个简单的示例：

```cpp
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 创建一个 JSON 对象，将 std::vector 作为值传递给键
    json jsonObject;
    jsonObject["myNumbers"] = numbers;

    // 将 JSON 对象转换为字符串输出
    std::string jsonString = jsonObject.dump();
    std::cout << "JSON String: " << jsonString << std::endl;

    return 0;
}
```

在这个例子中，`std::vector<int>` 中的数字被添加到了名为 `"myNumbers"` 的键中，并将整个向量作为 JSON 对象的值。`jsonObject.dump()` 将 JSON 对象转换为字符串，并使用 `std::cout` 输出到控制台。

你可以根据需要将不同类型的值存储在 JSON 对象中，并根据库的文档进行操作以满足你的特定需求。

## nlohmann/json 解析JSON字符串 将数组传递给std::vector

要使用 nlohmann/json 库解析包含数组的 JSON 字符串并将其传递给 `std::vector`，你可以使用 `from_json` 函数。以下是一个示例：

假设有如下的 JSON 字符串：

```json
{
    "myArray": [1, 2, 3, 4, 5]
}
```

在 C++ 中使用 nlohmann/json 库解析该 JSON 字符串并将数组传递给 `std::vector` 的示例：

```cpp
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

int main() {
    // JSON 字符串
    std::string jsonString = R"(
        {
            "myArray": [1, 2, 3, 4, 5]
        }
    )";

    // 解析 JSON 字符串
    json jsonObject = json::parse(jsonString);

    // 从 JSON 对象中获取数组并传递给 std::vector
    std::vector<int> myVector = jsonObject["myArray"].get<std::vector<int>>();

    // 输出 std::vector 中的值
    std::cout << "Values in vector: ";
    for (const auto& num : myVector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，`jsonObject["myArray"].get<std::vector<int>>()` 从 JSON 对象中获取名为 `"myArray"` 的数组，并使用 `.get<std::vector<int>>()` 将其转换为 `std::vector<int>` 类型。然后，将 `std::vector` 中的值输出到控制台。

这是一种使用 nlohmann/json 库解析 JSON 字符串并将数组值传递给 `std::vector` 的方法。

## 解析JSON文件

使用 nlohmann/json 库解析 JSON 文件非常简单。下面是一个简单的示例，演示了如何使用该库解析 JSON 文件：

```cpp
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

int main() {
    // 打开 JSON 文件
    std::ifstream file("data.json");
    
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }
    
    // 读取 JSON 数据
    nlohmann::json jsonData;
    file >> jsonData;
    
    // 关闭文件
    file.close();
    
    // 从 JSON 数据中提取所需的值
    std::string name = jsonData["name"];
    int age = jsonData["age"];
    
    // 打印提取的值
    std::cout << "姓名: " << name << std::endl;
    std::cout << "年龄: " << age << std::endl;
    
    return 0;
}
```

在这个示例中，我们首先使用 `ifstream` 打开一个名为 "data.json" 的 JSON 文件。然后，我们使用 `>>` 运算符将文件中的 JSON 数据读取到 `nlohmann::json` 对象 `jsonData` 中。最后，我们从 `jsonData` 中提取出 "name" 和 "age" 字段的值，并将其打印出来。

请确保在编译时链接 nlohmann/json 库。你可以通过在编译命令中添加 `-I` 选项指定头文件的搜索路径，以及 `-l` 选项指定库文件的链接。