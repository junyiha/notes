## 简介

+ python 常用的编程技巧笔记

## python3 启动新的线程

在 Python 3 中，您可以使用 `threading` 模块来启动新的线程。以下是一个简单的示例，演示如何创建和启动一个新线程：

```python
import threading

# 定义一个简单的函数，作为新线程的任务
def print_numbers():
    for i in range(1, 6):
        print(f"Number: {i}")

# 创建一个新线程并指定要运行的函数
new_thread = threading.Thread(target=print_numbers)

# 启动新线程
new_thread.start()

# 主线程继续执行其他任务
for letter in 'abcde':
    print(f"Letter: {letter}")
```

在这个示例中，我们首先导入 `threading` 模块。然后，我们定义了一个名为 `print_numbers` 的函数，它将在新线程中运行，简单地打印数字 1 到 5。接下来，我们使用 `threading.Thread` 类创建一个新线程，将 `print_numbers` 函数作为目标（`target`）传递给新线程。最后，我们通过调用 `start()` 方法启动新线程，它将在后台运行。

主线程继续执行其他任务，因此您会看到数字和字母的输出交替出现，表明新线程和主线程在并发执行。

请注意，线程是轻量级的执行单元，可以同时运行多个线程，但需要谨慎处理线程之间的共享数据和同步问题，以避免竞争条件和其他线程相关的问题。在复杂的多线程应用程序中，确保线程安全性非常重要。如果需要更多的线程控制和同步，Python 3 还提供了 `threading` 模块中的各种工具。

## python 解析JSON文件

在Python中解析JSON文件通常是一个非常常见的任务，你可以使用内置的`json`模块来完成这个任务。以下是一个基本的JSON文件解析示例：

假设你有一个名为`data.json`的JSON文件，内容如下：

```json
{
    "name": "John",
    "age": 30,
    "city": "New York"
}
```

你可以使用以下代码来解析这个JSON文件：

```python
import json

# 打开JSON文件并读取数据
with open('data.json', 'r') as file:
    data = json.load(file)

# 访问JSON中的数据
name = data['name']
age = data['age']
city = data['city']

# 打印解析后的数据
print(f"Name: {name}")
print(f"Age: {age}")
print(f"City: {city}")
```

运行这段代码将会读取`data.json`文件并将其解析为Python字典对象。然后你可以像访问字典一样访问其中的数据。

如果你要解析的JSON文件包含一个JSON数组，你可以使用`json.load()`来解析整个数组，然后在Python中进一步处理。例如：

假设你有一个名为`data.json`的JSON文件，内容如下：

```json
[
    {
        "name": "John",
        "age": 30,
        "city": "New York"
    },
    {
        "name": "Alice",
        "age": 25,
        "city": "Los Angeles"
    }
]
```

你可以使用以下代码来解析包含多个对象的JSON数组：

```python
import json

# 打开JSON文件并读取数据
with open('data.json', 'r') as file:
    data = json.load(file)

# 遍历JSON数组中的对象
for person in data:
    name = person['name']
    age = person['age']
    city = person['city']
    
    print(f"Name: {name}")
    print(f"Age: {age}")
    print(f"City: {city}")
```

这将会遍历JSON数组中的每个对象，并分别访问它们的属性。

## python3 发送网络请求

在Python 3中，你可以使用标准库中的`requests`模块来发送网络请求。以下是一些示例，展示如何发送不同类型的网络请求：

**1. 发送HTTP GET请求：**

```python
import requests

# 发送GET请求
response = requests.get('https://www.example.com')

# 检查响应状态码
if response.status_code == 200:
    print('请求成功')
    print(response.text)  # 打印响应内容
else:
    print(f'请求失败，状态码：{response.status_code}')
```

上述代码发送一个HTTP GET请求到`https://www.example.com`，并打印响应内容。

**2. 发送HTTP POST请求：**

```python
import requests

# POST请求的数据
data = {'key1': 'value1', 'key2': 'value2'}

# 发送POST请求
response = requests.post('https://www.example.com/api', data=data)

# 检查响应状态码
if response.status_code == 200:
    print('请求成功')
    print(response.text)  # 打印响应内容
else:
    print(f'请求失败，状态码：{response.status_code}')
```

上述代码发送一个HTTP POST请求到`https://www.example.com/api`，并附带数据作为表单数据发送。

**3. 发送HTTP请求并处理JSON响应：**

```python
import requests

# 发送GET请求
response = requests.get('https://api.example.com/data')

# 检查响应状态码
if response.status_code == 200:
    print('请求成功')
    json_data = response.json()  # 将JSON响应解析为Python字典或列表
    print(json_data)
else:
    print(f'请求失败，状态码：{response.status_code}')
```

上述代码发送一个HTTP GET请求，然后使用`.json()`方法将JSON响应解析为Python数据结构。

以上是使用`requests`库发送HTTP请求的基本示例。在实际应用中，你还可以添加请求头、处理异常、处理重定向、使用认证等高级功能，具体取决于你的需求。确保在使用`requests`模块时，你已经安装了它，你可以使用`pip`来安装它：

```
pip install requests
```

## python3 通过POST请求发送JSON数据

你可以使用Python 3中的`requests`库发送POST请求并附加JSON数据。以下是一个示例，展示如何发送带有JSON数据的POST请求：

```python
import requests
import json

# 定义要发送的JSON数据
data = {
    "name": "John",
    "age": 30,
    "city": "New York"
}

# 将JSON数据转换为字符串
json_data = json.dumps(data)

# 设置请求头，指明发送的数据是JSON格式
headers = {'Content-Type': 'application/json'}

# 发送POST请求
response = requests.post('https://www.example.com/api', data=json_data, headers=headers)

# 检查响应状态码
if response.status_code == 200:
    print('请求成功')
    print(response.text)  # 打印响应内容
else:
    print(f'请求失败，状态码：{response.status_code}')
```

上述代码首先将Python字典转换为JSON格式的字符串，然后设置请求头以指明发送的数据是JSON格式。接下来，它使用`requests.post`方法发送POST请求到`https://www.example.com/api`，并附带JSON数据作为请求正文。

确保替换URL为你要发送请求的目标URL，以及替换`data`变量中的JSON数据为你要发送的实际数据。这样，你就可以通过POST请求发送JSON数据了。

## python3 解析JSON 判断字段类型 遍历数组

要解析JSON并根据字段类型进行判断以及遍历JSON数组，你可以使用Python 3的`json`模块来解析JSON数据，然后根据需要进行类型检查和遍历。以下是一个示例：

假设你有一个JSON文件`data.json`，其中包含一个JSON数组，如下所示：

```json
[
    {
        "name": "John",
        "age": 30,
        "city": "New York"
    },
    {
        "name": "Alice",
        "age": null,
        "city": "Los Angeles"
    },
    {
        "name": "Bob",
        "age": "25",
        "city": "Chicago"
    }
]
```

你可以使用以下Python 3代码来解析JSON，检查字段类型并遍历数组：

```python
import json

# 打开JSON文件并读取数据
with open('data.json', 'r') as file:
    data = json.load(file)

# 遍历JSON数组中的对象
for person in data:
    name = person['name']
    age = person['age']
    city = person['city']

    # 检查字段类型
    if isinstance(age, int):
        age_str = str(age)  # 将年龄转换为字符串
        age_type = 'int'
    elif age is None:
        age_str = 'N/A'  # 如果年龄字段为null，则将其标记为N/A
        age_type = 'null'
    elif isinstance(age, str):
        age_str = age
        age_type = 'string'
    else:
        age_str = 'Unknown'
        age_type = 'unknown'

    # 打印信息
    print(f"Name: {name}")
    print(f"Age: {age_str} (Type: {age_type})")
    print(f"City: {city}")
    print()
```

上述代码会遍历JSON数组中的每个对象，并检查年龄字段的类型。根据字段类型，它会打印相应的信息。

这个示例中，我们假设年龄字段可能是整数、字符串、null或其他未知类型，然后根据实际类型执行相应的操作。你可以根据自己的JSON数据结构和字段类型进行适当的调整。