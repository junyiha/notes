---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_3_json模块
tag: Python
---
## 简介

+ json模块笔记

## python3 json 模块 详解

Python 3中的`json`模块是用于处理JSON（JavaScript Object Notation）数据的标准库。JSON是一种轻量级数据交换格式，通常用于数据序列化和跨语言数据传输。下面是对Python 3中的`json`模块的详细解释：

1. **加载和解析JSON数据**：
   - `json.loads(json_string)`：将JSON格式的字符串解析为Python数据结构，通常是字典或列表。
   - `json.load(file)`：从文件中读取JSON数据并解析为Python数据结构。

2. **将Python数据转换为JSON**：
   - `json.dumps(python_data)`：将Python数据（字典、列表等）转换为JSON格式的字符串。
   - `json.dump(python_data, file)`：将Python数据写入文件，以JSON格式进行序列化。

3. **格式化输出**：
   - `json.dumps(python_data, indent=4)`：以缩进格式输出JSON字符串，使其更易读。
   - `json.dump(python_data, file, indent=4)`：以缩进格式将JSON数据写入文件。

4. **自定义编码和解码**：
   - `json.JSONEncoder`：自定义JSON编码器，允许你扩展默认的JSON编码行为。
   - `json.JSONDecoder`：自定义JSON解码器，允许你处理JSON字符串中的特殊情况。

5. **处理特殊数据类型**：
   - `json.dumps(..., default=custom_function)`：允许你在将不支持的数据类型转换为JSON时使用自定义函数。
   - `json.loads(..., object_hook=custom_function)`：允许你在从JSON解析数据时使用自定义函数来处理特殊情况。

6. **异常处理**：
   - `json.JSONDecodeError`：用于捕获JSON解码期间可能发生的异常，如JSON格式不正确等。

7. **其他选项**：
   - `json.dumps(..., ensure_ascii=False)`：允许非ASCII字符在JSON字符串中保持原样，而不是进行转义。
   - `json.dumps(..., separators=(',', ':'))`：指定分隔符以节省生成的JSON字符串的空间。

下面是一个示例，展示如何使用`json`模块加载、解析、生成和格式化JSON数据：

```python
import json

# 创建一个Python字典
data = {
    "name": "John",
    "age": 30,
    "city": "New York"
}

# 将Python字典转换为JSON字符串
json_string = json.dumps(data, indent=4)

# 打印JSON字符串
print(json_string)

# 将JSON字符串解析为Python字典
parsed_data = json.loads(json_string)

# 访问解析后的数据
print(parsed_data["name"])  # 输出 "John"
```

`json`模块提供了在Python中处理JSON数据的强大功能，允许你在不同系统之间轻松交换数据，并在Python应用程序中进行数据序列化和反序列化。