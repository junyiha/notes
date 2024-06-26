---
category: Cpp
date: 2024-05-22 09:00:00 +0800
layout: post
title: C++_10_38_unordered_map
tag: CppSTL
---
## 简介

+ unordered_map 标准库

## C++ <unordered_map>标准库 详解

在C++中，`<unordered_map>` 标准库提供了无序关联容器 `std::unordered_map`，它是一个键值对的容器，类似于有序关联容器 `std::map`，但 `std::unordered_map` 中的元素没有特定的顺序。它使用哈希表来实现快速的元素检索。

以下是一些 `std::unordered_map` 的重要特性和用法：

### 1. 基本用法

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // 创建一个std::unordered_map
    std::unordered_map<int, std::string> myMap;

    // 插入键值对
    myMap[1] = "One";
    myMap[2] = "Two";
    myMap[3] = "Three";

    // 访问元素
    std::cout << "Value for key 2: " << myMap[2] << std::endl;

    // 遍历元素
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}
```

### 2. 插入和删除元素

使用 `insert` 函数可以插入元素，使用 `erase` 函数可以删除元素。

```cpp
std::unordered_map<int, std::string> myMap;

// 插入元素
myMap.insert({4, "Four"});
myMap[5] = "Five";

// 删除元素
myMap.erase(2);
```

### 3. 查找元素

使用 `find` 函数可以在 `std::unordered_map` 中查找元素，如果元素存在，返回指向该元素的迭代器，否则返回 `end()`。

```cpp
auto it = myMap.find(3);
if (it != myMap.end()) {
    std::cout << "Element found: " << it->second << std::endl;
} else {
    std::cout << "Element not found" << std::endl;
}
```

### 4. 哈希函数和键比较

为了使用自定义类型作为键，你需要提供一个哈希函数和一个相等比较函数。这可以通过定义这两个函数或使用标准库中的 `std::hash` 和 `std::equal_to` 来完成。

```cpp
struct MyKey {
    int value1;
    int value2;

    bool operator==(const MyKey& other) const {
        return (value1 == other.value1) && (value2 == other.value2);
    }
};

namespace std {
    template <>
    struct hash<MyKey> {
        std::size_t operator()(const MyKey& key) const {
            // 自定义哈希函数
            return std::hash<int>()(key.value1) ^ std::hash<int>()(key.value2);
        }
    };
}

int main() {
    std::unordered_map<MyKey, std::string> myMap;

    MyKey key1{1, 2};
    myMap[key1] = "Value";

    return 0;
}
```

上述代码演示了如何定义自己的哈希函数和相等比较函数，以便将自定义类型 `MyKey` 用作 `std::unordered_map` 的键。

总的来说，`std::unordered_map` 提供了一个快速的无序关联容器，适用于需要高效查找和插入元素的场景。注意，与有序关联容器相比，无序关联容器不会维护元素的特定顺序。