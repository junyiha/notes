## 简介

+ python 常用的编程技巧笔记

## python3 main函数接收外部参数并解析解析

如果您想要编写一个Python脚本，使其接收外部参数并进行解析，通常的做法是使用`sys.argv`来访问命令行参数，然后使用`argparse`或其他方法来解析这些参数。以下是一个示例，演示如何在Python中完成这个任务：

```python
import sys
import argparse

def main():
    # 创建ArgumentParser对象
    parser = argparse.ArgumentParser(description='一个命令行工具示例')

    # 添加命令行参数
    parser.add_argument('-f', '--file', required=True, help='指定文件名')
    parser.add_argument('-n', '--number', type=int, default=1, help='指定一个整数（默认为1）')
    parser.add_argument('--flag', action='store_true', help='设置此标志将为True，否则为False')

    # 解析命令行参数
    args = parser.parse_args()

    # 访问解析后的参数
    print('文件名:', args.file)
    print('整数值:', args.number)
    print('标志值:', args.flag)

if __name__ == '__main__':
    main()
```

在这个示例中，我们定义了一个`main()`函数，它包含参数解析的代码。然后，我们使用`if __name__ == '__main__':`来确保只有在直接运行脚本时才会执行`main()`函数，而不是在作为模块导入时执行。

然后，您可以在命令行中运行脚本，并传递参数，就像之前的示例一样：

```
python my_script.py -f myfile.txt -n 5 --flag
```

这将调用`main()`函数，解析命令行参数并执行相关操作。

这是一个基本的示例，您可以根据自己的需求扩展`main()`函数和命令行参数。`argparse`可以帮助您更灵活地定义和解析参数。

## python3 argparse 在python程序内部输出帮助信息

您可以在Python程序内部生成帮助信息，然后将其打印到控制台或保存到文件中，而不需要在命令行中使用`-h`或`--help`选项。要在程序内部输出帮助信息，您可以使用`argparse`的`print_help()`方法。以下是一个示例：

```python
import argparse

def main():
    # 创建ArgumentParser对象
    parser = argparse.ArgumentParser(description='一个命令行工具示例')

    # 添加命令行参数
    parser.add_argument('-f', '--file', required=True, help='指定文件名', default='default.txt')
    parser.add_argument('-n', '--number', type=int, help='指定一个整数', default=1)
    parser.add_argument('--flag', action='store_true', help='设置此标志将为True，否则为False', default=False)

    # 解析命令行参数
    args = parser.parse_args()

    # 访问解析后的参数
    print('文件名:', args.file)
    print('整数值:', args.number)
    print('标志值:', args.flag)

    # 输出帮助信息
    parser.print_help()

if __name__ == '__main__':
    main()
```

在上述示例中，我们在`main()`函数中使用`parser.print_help()`来生成帮助信息并将其打印到控制台。当您运行脚本时，它将首先输出解析后的参数值，然后再打印帮助信息。

运行脚本：

```
python my_script.py
```

这将输出解析后的参数值，然后打印帮助信息，让用户了解如何正确使用脚本。


## python3 OpenCV 矩形框的x,y,w,h 画在图像上

在 OpenCV 中，您可以使用 `cv2.rectangle` 函数来在图像上绘制一个矩形框，指定矩形的左上角坐标 `(x, y)` 和宽度 `w` 以及高度 `h`。以下是一个示例：

```python
import cv2
import numpy as np

# 创建一个空白图像
image = np.zeros((400, 400, 3), dtype=np.uint8)  # 创建一个 400x400 的黑色图像

# 定义矩形的左上角坐标 (x, y) 和宽度 (w)、高度 (h)
x, y, w, h = 100, 100, 200, 150

# 定义矩形的颜色 (BGR 格式)
color = (0, 255, 0)  # 绿色

# 在图像上绘制矩形
cv2.rectangle(image, (x, y), (x + w, y + h), color, thickness=2)

# 显示图像
cv2.imshow('Rectangle', image)

# 等待按下任意键然后关闭窗口
cv2.waitKey(0)
cv2.destroyAllWindows()
```

在上述示例中，我们首先创建了一个空白的黑色图像，然后使用 `cv2.rectangle` 函数绘制一个绿色的矩形框，指定左上角坐标 `(x, y)` 和右下角坐标 `(x + w, y + h)`，以及颜色和线条粗细。

您可以根据需要更改矩形的坐标、颜色和图像大小来适应您的需求。这只是一个基本示例，用于演示如何在 OpenCV 中绘制矩形。

## python3 OpenCV 接收二进制数据 保存为图片

要使用 Python 3 和 OpenCV 接收二进制数据并将其保存为图像，您可以按照以下步骤进行操作：

1. 导入必要的库：

```python
import cv2
import numpy as np
```

2. 接收二进制数据并将其转换为 NumPy 数组。假设您已经从某个地方（例如网络、文件等）接收到了二进制数据，您可以将其转换为 NumPy 数组：

```python
# 假设 binary_data 是包含二进制图像数据的变量
# 请替换为您自己的方式来获取二进制数据
binary_data = b'\xff\xd8\xff\xe0\x00\x10\x4a\x46\x49...'

# 将二进制数据转换为 NumPy 数组
image_data = np.frombuffer(binary_data, np.uint8)
```

3. 解码图像数据为 OpenCV 图像对象：

```python
# 解码二进制数据为图像对象
image = cv2.imdecode(image_data, cv2.IMREAD_COLOR)
```

上述代码假设您接收的二进制数据是JPEG格式的图像。如果数据是其他图像格式，您可能需要调整 `cv2.imdecode` 的参数。

4. 保存图像到文件：

```python
# 保存图像到文件
cv2.imwrite('output_image.jpg', image)
```

现在，您已经成功将接收的二进制数据保存为图像文件。请确保提供正确的图像文件路径和名称。

整个代码示例如下：

```python
import cv2
import numpy as np

# 假设 binary_data 是包含二进制图像数据的变量
# 请替换为您自己的方式来获取二进制数据
binary_data = b'\xff\xd8\xff\xe0\x00\x10\x4a\x46\x49...'

# 将二进制数据转换为 NumPy 数组
image_data = np.frombuffer(binary_data, np.uint8)

# 解码二进制数据为图像对象
image = cv2.imdecode(image_data, cv2.IMREAD_COLOR)

# 保存图像到文件
cv2.imwrite('output_image.jpg', image)
```

请注意，这只是一个简单的示例，假设您已经获取了包含二进制数据的变量。在实际应用中，您可能需要使用适当的方法来获取二进制数据，例如通过网络请求、文件读取等。

## python3 将二进制数据写入文件 示例 详解

在Python 3中，将二进制数据写入文件是一种常见的操作，通常用于保存图像、音频、视频文件以及其他二进制数据。以下是一个示例，演示了如何将二进制数据写入文件以及相关的详细解释：

```python
# 要写入文件的二进制数据
binary_data = b'\x48\x65\x6c\x6c\x6f\x2c\x20\x57\x6f\x72\x6c\x64\x21'

# 打开文件以二进制写入模式（'wb'表示二进制写入，如果文件不存在则创建，如果文件已存在则覆盖）
# 您可以指定文件路径和名称
file_path = "binary_data.bin"

# 使用with语句打开文件，以确保在完成写入后关闭文件
with open(file_path, 'wb') as file:
    # 将二进制数据写入文件
    file.write(binary_data)

# 文件现在已经写入，可以关闭

print(f"二进制数据已写入文件 {file_path}")
```

上述示例中的关键点包括：

1. 定义要写入文件的二进制数据`binary_data`。这是一个包含十六进制值的字节序列，代表了字符串"Hello, World!"的ASCII编码。

2. 使用`open`函数以二进制写入模式（'wb'）打开文件。在二进制写入模式下，文件以字节为单位进行写入，而不是以文本字符为单位。

3. 使用`with`语句打开文件，以确保在完成写入后自动关闭文件。这有助于防止资源泄漏。

4. 使用`file.write()`方法将二进制数据写入文件。

5. 最后，关闭文件，以确保操作的安全性。

文件`binary_data.bin`现在包含了指定的二进制数据。您可以根据需要修改`binary_data`变量以及文件路径和名称来适应您的实际需求。这种方法适用于将任何二进制数据写入文件。

## python3 base64 编解码 工具 详解

Base64 是一种二进制数据编码的方式，通常用于将二进制数据转换成可打印字符，以便在不损失数据的情况下进行传输和存储。Python 提供了内置的 `base64` 模块，可以用来进行 Base64 编码和解码操作。下面是关于 Python3 中 `base64` 模块的详细解释和示例：

### Base64 编码

Base64 编码将二进制数据转换为可打印字符。可以使用 `base64` 模块的 `b64encode` 函数来执行编码操作。

```python
import base64

# 要编码的二进制数据
binary_data = b'Hello, World!'

# 进行 Base64 编码
encoded_data = base64.b64encode(binary_data)

# 将编码后的数据转换为字符串
encoded_string = encoded_data.decode('utf-8')

print(encoded_string)
```

### Base64 解码

Base64 解码将 Base64 编码的字符串重新转换回原始的二进制数据。可以使用 `base64` 模块的 `b64decode` 函数来执行解码操作。

```python
import base64

# Base64 编码后的字符串
encoded_string = 'SGVsbG8sIFdvcmxkIQ=='

# 进行 Base64 解码
decoded_data = base64.b64decode(encoded_string)

# 打印解码后的二进制数据
print(decoded_data)
```

### URL 安全的 Base64 编解码

有时候，Base64 编码后的字符串需要在 URL 中传输，但标准的 Base64 编码字符串中包含一些特殊字符（如`+`和`/`）可能会引起问题。为了解决这个问题，可以使用 `base64` 模块的 `urlsafe_b64encode` 和 `urlsafe_b64decode` 函数，它们会将`+`和`/`字符替换为`-`和`_`。

```python
import base64

# 要编码的二进制数据
binary_data = b'Hello, World!'

# 进行 URL 安全的 Base64 编码
urlsafe_encoded_data = base64.urlsafe_b64encode(binary_data)

# 将编码后的数据转换为字符串
urlsafe_encoded_string = urlsafe_encoded_data.decode('utf-8')

print(urlsafe_encoded_string)

# 进行 URL 安全的 Base64 解码
decoded_data = base64.urlsafe_b64decode(urlsafe_encoded_string)

# 打印解码后的二进制数据
print(decoded_data)
```

这就是使用 Python3 中的 `base64` 模块进行 Base64 编码和解码的基本操作。请注意，在进行编码和解码操作时，要确保输入的数据类型是字节序列（`bytes`）。

## python3 将字符串写入文件

要将字符串写入文件，您可以使用Python的内置文件操作功能。以下是一个简单的示例，演示如何将字符串写入文件：

```python
# 要写入的字符串
my_string = "这是要写入文件的字符串。"

# 打开文件以写入模式（'w'表示写入，如果文件不存在则创建，如果文件已存在则覆盖）
# 您可以指定文件路径和名称
file_path = "my_file.txt"

# 使用with语句打开文件，以确保在完成写入后关闭文件
with open(file_path, 'w') as file:
    # 将字符串写入文件
    file.write(my_string)

# 文件现在已经写入，可以关闭

print(f"字符串已写入文件 {file_path}")
```

在这个示例中，我们首先定义要写入文件的字符串`my_string`，然后使用`open`函数打开文件以供写入（使用`'w'`模式）。然后，我们使用`with`语句来确保在完成写入后关闭文件，以避免资源泄漏。最后，我们使用`file.write()`方法将字符串写入文件，然后关闭文件。

注意：如果指定的文件路径已经存在一个文件，使用`'w'`模式会覆盖文件的内容。如果不想覆盖文件，可以使用`'a'`模式以附加方式写入。

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