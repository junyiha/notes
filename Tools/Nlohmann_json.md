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