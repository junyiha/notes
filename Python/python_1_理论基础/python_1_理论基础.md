# 简介

+ Python编程语言的理论基础

## python3 str object is not callable

如果你在Python中遇到 "str object is not callable" 错误，通常是因为你意外地使用了内置函数的名称作为变量名。在Python中，避免使用内置函数名作为变量名是一个良好的实践。

例如，以下是一个可能导致该错误的示例：

```python
str = "Hello"
result = str(42)  # 这里会引发 "str object is not callable" 错误
print(result)
```

在这个例子中，`str`被重新赋值为一个字符串，然后试图调用它就会引发错误。为了避免这种情况，应该使用不同的变量名：

```python
my_str = "Hello"
result = str(42)  # 这里不会引发错误，因为 str 是内置函数
print(result)
```

确保不要覆盖内置函数和关键字的名称，以避免这种类型的错误。如果已经发生了这种情况，重新启动Python解释器并尽量避免使用与内置函数和关键字相同的变量名。

## python3 no module named requests

如果您在 Python 3 中遇到 "no module named requests" 错误，这意味着您的 Python 环境中缺少 `requests` 模块。`requests` 是一个用于发送 HTTP 请求的常用库，但它不是 Python 的标准库，因此您需要单独安装它。

要解决这个问题，您可以执行以下步骤来安装 `requests` 模块：

1. **使用 pip 安装 requests**：

   打开终端（命令行界面）并运行以下命令来使用 `pip` 安装 `requests` 模块：

   ```
   pip install requests
   ```

   请确保 `pip` 是与您的 Python 3 版本相关联的 pip，通常情况下，您可以使用 `pip3` 命令来确保安装到 Python 3：

   ```
   pip3 install requests
   ```

2. **验证安装**：

   安装完成后，您可以在 Python 中导入 `requests` 模块并验证是否成功。打开 Python 解释器或脚本，尝试运行以下代码：

   ```python
   import requests
   print(requests.__version__)
   ```

   如果没有出现错误，并且成功打印出 `requests` 版本号，那么说明安装已经成功。

请注意，如果您在虚拟环境中工作，请确保您的虚拟环境处于活动状态，以便 `requests` 模块安装到虚拟环境而不是全局 Python 环境。如果您使用的是 Python 3，`pip` 通常会默认安装到 Python 3 的环境中。

如果仍然遇到问题，可以提供更多详细信息，以便我更好地帮助您解决问题。

## python3 pip 常用命令 详解

`pip` 是 Python 的包管理工具，用于安装、卸载和管理 Python 包（也称为库或模块）。以下是一些常用的 `pip` 命令及其详细解释：

1. **安装包**：

   ```
   pip install package_name
   ```

   用于安装指定的 Python 包。`package_name` 是要安装的包的名称。可以使用这个命令来安装第三方库，例如 `numpy`、`requests`、`matplotlib` 等。可以使用 `-r` 选项从一个文本文件中安装一组包。

2. **卸载包**：

   ```
   pip uninstall package_name
   ```

   用于卸载指定的 Python 包。`package_name` 是要卸载的包的名称。

3. **查看已安装的包**：

   ```
   pip list
   ```

   显示已经安装的所有 Python 包的列表。

4. **查看包的详细信息**：

   ```
   pip show package_name
   ```

   显示指定包的详细信息，包括版本号、作者、描述等。

5. **升级包**：

   ```
   pip install --upgrade package_name
   ```

   用于升级已安装的包到最新版本。

6. **搜索包**：

   ```
   pip search search_term
   ```

   用于搜索 PyPI（Python Package Index）上的包。`search_term` 是您要搜索的包的关键字。

7. **创建 requirements 文件**：

   ```
   pip freeze > requirements.txt
   ```

   将当前环境中已安装的所有包及其版本号保存到 `requirements.txt` 文件中，通常用于共享项目的依赖信息。

8. **从 requirements 文件安装包**：

   ```
   pip install -r requirements.txt
   ```

   从 `requirements.txt` 文件中安装指定版本的包，用于在新环境中还原项目的依赖关系。

9. **查看包的依赖关系**：

   ```
   pip show --files package_name
   ```

   显示指定包的依赖关系和文件路径。

10. **安装包的特定版本**：

    ```
    pip install package_name==version
    ```

    安装指定版本的包，其中 `version` 是要安装的版本号。

这些是一些常用的 `pip` 命令，用于管理 Python 包。根据您的需求，您可以使用这些命令来安装、升级、卸载、查看和管理 Python 包。使用 `pip` 可以方便地管理Python项目的依赖关系。

## kwargs

在 Python 中，`kwargs` 是一个特殊的参数，用于接收传递给函数的关键字参数（Keyword Arguments）。`kwargs` 是一个字典（dictionary），其中包含了函数调用时传递的关键字参数及其对应的值。

使用 `**kwargs` 语法可以在函数定义中接收关键字参数，并将其作为字典传递给函数体内部。下面是一个示例：

```python
def my_function(**kwargs):
    for key, value in kwargs.items():
        print(f"{key}: {value}")

# 使用关键字参数调用函数
my_function(name="John", age=30, city="New York")
```

在上面的示例中，`my_function` 函数定义中的 `**kwargs` 表示可以接收任意数量的关键字参数。在函数体内部，`kwargs` 是一个字典，可以使用 `items()` 方法迭代其中的键值对，并对其进行处理。在函数调用中，传递的关键字参数会被收集到 `kwargs` 字典中。

运行上述代码，输出将是：

```
name: John
age: 30
city: New York
```

通过使用 `**kwargs`，函数能够接收灵活的关键字参数，并在函数内部以字典的形式进行处理。这使得函数可以处理各种不同的关键字参数，而无需预先指定它们的名称和数量。

## 源码编安装

+ 源码路径：`zjy-190/Software/Python-3.8.3.tgz`

+ 安装依赖包
  - `apt-get install -y libssl-dev openssl libffi-dev zlib1g-dev`

+ 编译安装
    + cd Python-3.8.0
    + ./configure --prefix=/usr/local/python3
    + make && make install

+ pip up

## zlib not available 是什么

"zlib not available" 是一个错误消息，通常在使用Python时出现，表示缺少 zlib 模块或库。zlib 是一个用于压缩和解压缩数据的库，通常用于处理压缩文件、网络传输中的数据压缩等。如果您遇到 "zlib not available" 错误，可能是因为您的Python环境没有正确安装或配置 zlib 库。

要解决这个问题，您可以采取以下步骤：

1. **安装 zlib 开发库**：首先，确保您的系统上已经安装了 zlib 开发库。在大多数Linux系统上，可以使用包管理器安装 zlib 开发库，例如：

   - 在Ubuntu上，可以运行以下命令安装 zlib 开发库：

     ```
     sudo apt-get install zlib1g-dev
     ```

   - 在CentOS上，可以运行以下命令安装 zlib 开发库：

     ```
     sudo yum install zlib-devel
     ```

   - 在其他Linux发行版上，请使用相应的包管理器安装 zlib 开发库。

2. **重新编译Python**：如果您已经安装了 zlib 开发库但仍然遇到问题，您可能需要重新编译Python，以便它可以正确地链接到 zlib 库。这可以通过以下步骤完成：

   - 下载Python源代码，如果尚未下载。

   - 进入Python源代码的目录。

   - 运行以下命令：

     ```
     ./configure
     make
     sudo make install
     ```

   这将重新编译Python，并确保它正确链接到 zlib 库。

3. **检查Python环境**：如果您使用的是虚拟环境，请确保虚拟环境中的Python正确配置并链接到 zlib 库。您可以使用以下命令检查虚拟环境的Python版本和 zlib 链接：

   ```
   which python
   python -c "import zlib; print(zlib)"
   ```

   确保这些命令返回正确的Python解释器和 zlib 模块。

# python3 日志处理 工具 推荐

在Python 3中，有许多优秀的日志处理工具可供选择，这些工具可以帮助你有效地记录和管理应用程序的日志信息。以下是一些常用的Python 3日志处理工具的推荐：

1. **Python内置的`logging`模块：**
   Python的标准库中包含了一个内置的`logging`模块，它提供了强大的日志记录功能。你可以使用这个模块来配置日志级别、输出目标和格式。它是一个常见的选择，因为它是Python的标准库的一部分，无需额外安装。

   ```python
   import logging

   logging.basicConfig(filename='app.log', level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
   ```

2. **Loguru：**
   Loguru是一个易于使用的第三方日志库，它提供了直观的API和强大的功能。它支持动态日志级别调整、日志旋转、多种输出格式等功能。

   ```python
   from loguru import logger

   logger.add("app.log", rotation="500 MB", level="INFO")
   ```

3. **structlog：**
   structlog是一个用于结构化日志记录的库，它允许你轻松地记录自定义字段，并支持多种输出格式。

   ```python
   import structlog

   structlog.configure(
       processors=[
           structlog.processors.JSONRenderer(),
           structlog.processors.TimeStamper(fmt="iso"),
       ],
       logger_factory=structlog.PrintLoggerFactory(),
   )
   ```

4. **Fluentd：**
   Fluentd是一个开源的日志收集和传输工具，它可以集成到Python应用程序中，并将日志发送到不同的目标，如文件、数据库或日志分析工具中。

5. **Loggly、Papertrail等云日志服务：**
   如果你的应用程序部署在云上，可以考虑使用云日志服务，如Loggly、Papertrail等。它们提供了强大的日志管理和分析功能，可以帮助你更轻松地处理日志。

选择哪个日志处理工具取决于你的具体需求和偏好。无论你选择哪一个，都应该根据项目的规模和要求来配置和管理日志，以确保你能够有效地监视和调试你的应用程序。

# 编码

+ 默认情况下，Python 3 源码文件以 UTF-8 编码，所有字符串都是 unicode 字符串。 当然你也可以为源码文件指定不同的编码

```python
# -*- coding: cp-1252 -*-
```

+ 上述定义允许在源文件中使用 Windows-1252 字符集中的字符编码，对应适合语言为保加利亚语、白俄罗斯语、马其顿语、俄语、塞尔维亚语。

# 标识符

+ 第一个字符必须是字母表中字母或下划线 _ 。
+ 标识符的其他的部分由字母、数字和下划线组成。
+ 标识符对大小写敏感。

+ 在 Python 3 中，可以用中文作为变量名，非 ASCII 标识符也是允许的了。

# python保留字

+ 保留字即关键字，我们不能把它们用作任何标识符名称。Python 的标准库提供了一个 keyword 模块，可以输出当前版本的所有关键字：
```python
>>> import keyword
>>> keyword.kwlist
['False', 'None', 'True', 'and', 'as', 'assert', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield']
```

# 注释

+ Python中单行注释以 # 开头，实例如下：
```python
#!/usr/bin/python3
 
# 第一个注释
print ("Hello, Python!") # 第二个注释
```

+ 多行注释可以用多个 # 号，还有 ''' 和 """：
```python
#!/usr/bin/python3
 
# 第一个注释
# 第二个注释
 
'''
第三注释
第四注释
'''
 
"""
第五注释
第六注释
"""
print ("Hello, Python!")
```

# 行与缩进

+ python最具特色的就是使用缩进来表示代码块，不需要使用大括号 {} 
+ 缩进的空格数是可变的，但是同一个代码块的语句必须包含相同的缩进空格数。实例如下
```python
if True:
    print ("True")
else:
    print ("False")
```

# 多行语句

+ Python 通常是一行写完一条语句，但如果语句很长，我们可以使用反斜杠 \ 来实现多行语句，例如：
```python
total = item_one + \
        item_two + \
        item_three
```

+ 在 [], {}, 或 () 中的多行语句，不需要使用反斜杠 \，例如：
```python
total = ['item_one', 'item_two', 'item_three',
        'item_four', 'item_five']
```

# 数字(Number)类型

+ python中数字有四种类型：整数、布尔型、浮点数和复数。
  + int (整数), 如 1, 只有一种整数类型 int，表示为长整型，没有 python2 中的 Long。
  + bool (布尔), 如 True。
  + float (浮点数), 如 1.23、3E-2
  + complex (复数), 如 1 + 2j、 1.1 + 2.2j

# 字符串(String)

+ Python 中单引号 ' 和双引号 " 使用完全相同。
+ 使用三引号(''' 或 """)可以指定一个多行字符串。
+ 转义符 \。
+ 反斜杠可以用来转义，使用 r 可以让反斜杠不发生转义。 如 r"this is a line with \n" 则 \n 会显示，并不是换行。
+ 按字面意义级联字符串，如 "this " "is " "string" 会被自动转换为 this is string。
+ 字符串可以用 + 运算符连接在一起，用 * 运算符重复。
+ Python 中的字符串有两种索引方式，从左往右以 0 开始，从右往左以 -1 开始。
+ Python 中的字符串不能改变。
+ Python 没有单独的字符类型，一个字符就是长度为 1 的字符串。
+ 字符串的截取的语法格式如下：变量[头下标:尾下标:步长]

```python
word = '字符串'
sentence = "这是一个句子。"
paragraph = """这是一个段落，
可以由多行组成"""
```

```python
#!/usr/bin/python3
 
str='123456789'
 
print(str)                 # 输出字符串
print(str[0:-1])           # 输出第一个到倒数第二个的所有字符
print(str[0])              # 输出字符串第一个字符
print(str[2:5])            # 输出从第三个开始到第六个的字符（不包含）
print(str[2:])             # 输出从第三个开始后的所有字符
print(str[1:5:2])          # 输出从第二个开始到第五个且每隔一个的字符（步长为2）
print(str * 2)             # 输出字符串两次
print(str + '你好')         # 连接字符串
 
print('------------------------------')
 
print('hello\nrunoob')      # 使用反斜杠(\)+n转义特殊字符
print(r'hello\nrunoob')     # 在字符串前面添加一个 r，表示原始字符串，不会发生转义
```

# 空行

+ 函数之间或类的方法之间用空行分隔，表示一段新的代码的开始。类和函数入口之间也用一行空行分隔，以突出函数入口的开始
+ 空行与代码缩进不同，空行并不是 Python 语法的一部分。书写时不插入空行，Python 解释器运行也不会出错。但是空行的作用在于分隔两段不同功能或含义的代码，便于日后代码的维护或重构。
+ 注
  + 空行也是程序代码的一部分。

# 等待用户输入

+ 执行下面的程序在按回车键后就会等待用户输入：
```python
#!/usr/bin/python3
 
input("\n\n按下 enter 键后退出。")
```

+ 以上代码中 ，\n\n 在结果输出前会输出两个新的空行。一旦用户按下 enter 键时，程序将退出。

# 同一行显示多条语句

+ Python 可以在同一行中使用多条语句，语句之间使用分号 ; 分割，以下是一个简单的实例：
```python
#!/usr/bin/python3
 
import sys; x = 'runoob'; sys.stdout.write(x + '\n')
```

# 多个语句构成代码组

+ 缩进相同的一组语句构成一个代码块，我们称之代码组
+ 像if、while、def和class这样的复合语句，首行以关键字开始，以冒号( : )结束，该行之后的一行或多行代码构成代码组
+ 我们将首行及后面的代码组称为一个子句(clause)
```python
if expression : 
   suite
elif expression : 
   suite 
else : 
   suite
```

# print 输出

+ print 默认输出是换行的，如果要实现不换行需要在变量末尾加上 end=""
```python
#!/usr/bin/python3
 
x="a"
y="b"
# 换行输出
print( x )
print( y )
 
print('---------')
# 不换行输出
print( x, end=" " )
print( y, end=" " )
print()
```

# import 与 from...import 

+ 在 python 用 import 或者 from...import 来导入相应的模块。
+ 将整个模块(somemodule)导入，格式为： import somemodule
+ 从某个模块中导入某个函数,格式为： from somemodule import somefunction
+ 从某个模块中导入多个函数,格式为： from somemodule import firstfunc, secondfunc, thirdfunc
+ 将某个模块中的全部函数导入，格式为： from somemodule import *

```python
import sys
print('================Python import mode==========================')
print ('命令行参数为:')
for i in sys.argv:
    print (i)
print ('\n python 路径为',sys.path)
```

```python
from sys import argv,path  #  导入特定的成员
 
print('================python from import===================================')
print('path:',path) # 因为已经导入path成员，所以此处引用时不需要加sys.path
```

# 基本数据类型

+ Python 中的变量不需要声明。每个变量在使用前都必须赋值，变量赋值以后该变量才会被创建。
+ 在 Python 中，变量就是变量，它没有类型，我们所说的"类型"是变量所指的内存中对象的类型。
+ 等号（=）用来给变量赋值。
+ 等号（=）运算符左边是一个变量名,等号（=）运算符右边是存储在变量中的值

# 标准数据类型

+ Python3 中常见的数据类型有：
  + Number（数字）
  + String（字符串）
  + bool（布尔类型）
  + List（列表）
  + Tuple（元组）
  + Set（集合）
  + Dictionary（字典）

+ Python3 的六个标准数据类型中：
  + 不可变数据（3 个）：Number（数字）、String（字符串）、Tuple（元组）
  + 可变数据（3 个）：List（列表）、Dictionary（字典）、Set（集合）。

# 数值运算

+ 注：
  1. Python可以同时为多个变量赋值，如a, b = 1, 2。
  2. 一个变量可以通过赋值指向不同类型的对象。
  3. 数值的除法包含两个运算符：/ 返回一个浮点数，// 返回一个整数。
  4. 在混合计算时，Python会把整型转换成为浮点数。

```python
>>> 5 + 4  # 加法
9
>>> 4.3 - 2 # 减法
2.3
>>> 3 * 7  # 乘法
21
>>> 2 / 4  # 除法，得到一个浮点数
0.5
>>> 2 // 4 # 除法，得到一个整数
0
>>> 17 % 3 # 取余 
2
>>> 2 ** 5 # 乘方
32
```

# List(列表)

+ List（列表） 是 Python 中使用最频繁的数据类型。
+ 列表可以完成大多数集合类的数据结构实现。列表中元素的类型可以不相同，它支持数字，字符串甚至可以包含列表（所谓嵌套）
+ 列表是写在方括号 [] 之间、用逗号分隔开的元素列表。
+ 和字符串一样，列表同样可以被索引和截取，列表被截取后返回一个包含所需元素的新列表
+ 列表截取的语法格式如下：
  + 变量[头下标:尾下标]

+ 注意：
  1. List写在方括号之间，元素用逗号隔开。
  2. 和字符串一样，list可以被索引和切片。
  3. List可以使用+操作符进行拼接。
  4. List中的元素是可以改变的。

# Tuple(元组)

+ 元组（tuple）与列表类似，不同之处在于元组的元素不能修改。元组写在小括号 () 里，元素之间用逗号隔开
+ 元组中的元素类型也可以不相同：
```python
#!/usr/bin/python3

tuple = ( 'abcd', 786 , 2.23, 'runoob', 70.2  )
tinytuple = (123, 'runoob')

print (tuple)             # 输出完整元组
print (tuple[0])          # 输出元组的第一个元素
print (tuple[1:3])        # 输出从第二个元素开始到第三个元素
print (tuple[2:])         # 输出从第三个元素开始的所有元素
print (tinytuple * 2)     # 输出两次元组
print (tuple + tinytuple) # 连接元组
```

+ 注意：
  1. 与字符串一样，元组的元素不能修改。
  2. 元组也可以被索引和切片，方法一样。
  3. 注意构造包含 0 或 1 个元素的元组的特殊语法规则。
  4. 元组也可以使用+操作符进行拼接。

# Set(集合)

+ Python 中的集合（Set）是一种无序、可变的数据类型，用于存储唯一的元素。
+ 集合中的元素不会重复，并且可以进行交集、并集、差集等常见的集合操作
+ 在 Python 中，集合使用大括号 {} 表示，元素之间用逗号 , 分隔
+ 另外，也可以使用 set() 函数创建集合
+ 注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。
+ 创建格式：
```python
parame = {value01,value02,...}
或者
set(value)
```

```python
#!/usr/bin/python3

sites = {'Google', 'Taobao', 'Runoob', 'Facebook', 'Zhihu', 'Baidu'}

print(sites)   # 输出集合，重复的元素被自动去掉

# 成员测试
if 'Runoob' in sites :
    print('Runoob 在集合中')
else :
    print('Runoob 不在集合中')


# set可以进行集合运算
a = set('abracadabra')
b = set('alacazam')

print(a)

print(a - b)     # a 和 b 的差集

print(a | b)     # a 和 b 的并集

print(a & b)     # a 和 b 的交集

print(a ^ b)     # a 和 b 中不同时存在的元素
```

# Dictionary(字典)

+ 字典（dictionary）是Python中另一个非常有用的内置数据类型
+ 列表是有序的对象集合，字典是无序的对象集合。两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。
+ 字典是一种映射类型，字典用 { } 标识，它是一个无序的 键(key) : 值(value) 的集合
+ 键(key)必须使用不可变类型。
+ 在同一个字典中，键(key)必须是唯一的

```python
#!/usr/bin/python3

dict = {}
dict['one'] = "1 - 菜鸟教程"
dict[2]     = "2 - 菜鸟工具"

tinydict = {'name': 'runoob','code':1, 'site': 'www.runoob.com'}


print (dict['one'])       # 输出键为 'one' 的值
print (dict[2])           # 输出键为 2 的值
print (tinydict)          # 输出完整的字典
print (tinydict.keys())   # 输出所有键
print (tinydict.values()) # 输出所有值
```

+ 构造函数 dict() 可以直接从键值对序列中构建字典如下：
```python
>>> dict([('Runoob', 1), ('Google', 2), ('Taobao', 3)])
{'Runoob': 1, 'Google': 2, 'Taobao': 3}
>>> {x: x**2 for x in (2, 4, 6)}
{2: 4, 4: 16, 6: 36}
>>> dict(Runoob=1, Google=2, Taobao=3)
{'Runoob': 1, 'Google': 2, 'Taobao': 3}
```

+ 字典类型也有一些内置的函数，例如 clear()、keys()、values() 等。
+ 注意：
  1. 字典是一种映射类型，它的元素是键值对。
  2. 字典的关键字必须为不可变类型，且不能重复。
  3. 创建空字典使用 { }

# bytes类型

+ 在 Python3 中，bytes 类型表示的是不可变的二进制序列（byte sequence）。
+ 与字符串类型不同的是，bytes 类型中的元素是整数值（0 到 255 之间的整数），而不是 Unicode 字符。
+ bytes 类型通常用于处理二进制数据，比如图像文件、音频文件、视频文件等等。在网络编程中，也经常使用 bytes 类型来传输二进制数据。
+ 创建 bytes 对象的方式有多种，最常见的方式是使用 b 前缀：
+ 此外，也可以使用 bytes() 函数将其他类型的对象转换为 bytes 类型。bytes() 函数的第一个参数是要转换的对象，第二个参数是编码方式，如果省略第二个参数，则默认使用 UTF-8 编码：
```python
x = bytes("hello", encoding="utf-8")
```

+ 与字符串类型类似，bytes 类型也支持许多操作和方法，如切片、拼接、查找、替换等等。同时，由于 bytes 类型是不可变的，因此在进行修改操作时需要创建一个新的 bytes 对象。例如：
```python
x = b"hello"
y = x[1:3]  # 切片操作，得到 b"el"
z = x + b"world"  # 拼接操作，得到 b"helloworld"
```

# 逻辑运算符

+ Python语言支持逻辑运算符，以下假设变量 a 为 10, b为 20:
+ and : x and y
  + 布尔"与" - 如果 x 为 False，x and y 返回 x 的值，否则返回 y 的计算值。
  + (a and b) 返回 20。

+ or : x or y
  + 布尔"或" - 如果 x 是 True，它返回 x 的值，否则它返回 y 的计算值。
  + (a or b) 返回 10。

+ not : not x
  + 布尔"非" - 如果 x 为 True，返回 False 。如果 x 为 False，它返回 True。
  + not(a and b) 返回 False

# 成员运算符

+ 除了以上的一些运算符之外，Python还支持成员运算符，测试实例中包含了一系列的成员，包括字符串，列表或元组

+ in 
  + 如果在指定的序列中找到值返回 True，否则返回 False。
  + x 在 y 序列中 , 如果 x 在 y 序列中返回 True。

+ not in
  + 如果在指定的序列中没有找到值返回 True，否则返回 False。
  + x 不在 y 序列中 , 如果 x 不在 y 序列中返回 True。

# 身份运算符

+ 身份运算符用于比较两个对象的存储单元

+ is
  + is 是判断两个标识符是不是引用自一个对象
  + x is y, 类似 id(x) == id(y) , 如果引用的是同一个对象则返回 True，否则返回 False

+ is not
  + is not 是判断两个标识符是不是引用自不同对象
  + x is not y ， 类似 id(x) != id(y)。如果引用的不是同一个对象则返回结果 True，否则返回 False。

# if语句

+ Python中if语句的一般形式如下所示：
```python
if condition_1:
    statement_block_1
elif condition_2:
    statement_block_2
else:
    statement_block_3
```

+ Python 中用 elif 代替了 else if，所以if语句的关键字为：if – elif – else。
+ 注意：
  1. 每个条件后面要使用冒号 :，表示接下来是满足条件后要执行的语句块。
  2. 使用缩进来划分语句块，相同缩进数的语句在一起组成一个语句块。
  3. 在 Python 中没有 switch...case 语句，但在 Python3.10 版本添加了 match...case，功能也类似

# match...case

+ Python 3.10 增加了 match...case 的条件判断，不需要再使用一连串的 if-else 来判断了
+ match 后的对象会依次与 case 后的内容进行匹配，如果匹配成功，则执行匹配到的表达式，否则直接跳过，_ 可以匹配一切。
+ 语法格式如下：
```python
match subject:
    case <pattern_1>:
        <action_1>
    case <pattern_2>:
        <action_2>
    case <pattern_3>:
        <action_3>
    case _:
        <action_wildcard>
```

+ case _: 类似于 C 和 Java 中的 default:，当其他 case 都无法匹配时，匹配这条，保证永远会匹配成功。
```python
def http_error(status):
    match status:
        case 400:
            return "Bad request"
        case 404:
            return "Not found"
        case 418:
            return "I'm a teapot"
        case _:
            return "Something's wrong with the internet"

mystatus=400
print(http_error(400))
```

# while循环

+ Python 中 while 语句的一般形式：
```python
while 判断条件(condition)：
    执行语句(statements)……
```

+ 同样需要注意冒号和缩进。另外，在 Python 中没有 do..while 循环。

+ 以下实例使用了 while 来计算 1 到 100 的总和：
```python
#!/usr/bin/env python3
 
n = 100
 
sum = 0
counter = 1
while counter <= n:
    sum = sum + counter
    counter += 1
 
print("1 到 %d 之和为: %d" % (n,sum))
```

+ 无限循环
  + 我们可以通过设置条件表达式永远不为 false 来实现无限循环，实例如下：
```python
#!/usr/bin/python3
 
var = 1
while var == 1 :  # 表达式永远为 true
   num = int(input("输入一个数字  :"))
   print ("你输入的数字是: ", num)
 
print ("Good bye!")
```

+ while 循环使用 else 语句
  + 如果 while 后面的条件语句为 false 时，则执行 else 的语句块。
  + 语法格式如下：
```python
while <expr>:
    <statement(s)>
else:
    <additional_statement(s)>
```
+ expr 条件语句为 true 则执行 statement(s) 语句块，如果为 false，则执行 additional_statement(s)。

# for 语句

+ Python for 循环可以遍历任何可迭代对象，如一个列表或者一个字符串
+ for循环的一般格式如下：
```python
for <variable> in <sequence>:
    <statements>
else:
    <statements>
```

+ 在 Python 中，for...else 语句用于在循环结束后执行一段代码。
```python
for item in iterable:
    # 循环主体
else:
    # 循环结束后执行的代码
```

+ 当循环执行完毕（即遍历完 iterable 中的所有元素）后，会执行 else 子句中的代码，如果在循环过程中遇到了 break 语句，则会中断循环，此时不会执行 else 子句。

# range()函数

+ 如果你需要遍历数字序列，可以使用内置 range() 函数。它会生成数列

# break 和 continue 语句及循环中的 else 子句

+ break 语句可以跳出 for 和 while 的循环体。如果你从 for 或 while 循环中终止，任何对应的循环 else 块将不执行。
+ continue 语句被用来告诉 Python 跳过当前循环块中的剩余语句，然后继续进行下一轮循环。

# pass 语句

+ Python pass是空语句，是为了保持程序结构的完整性。
+ pass 不做任何事情，一般用做占位语句，如下实例
```python
>>>while True:
...     pass  # 等待键盘中断 (Ctrl+C)
```

# end 关键字

+ 关键字end可以用于将结果输出到同一行，或者在输出的末尾添加不同的字符，实例如下：
```python
#!/usr/bin/python3
 
# Fibonacci series: 斐波纳契数列
# 两个元素的总和确定了下一个数
a, b = 0, 1
while b < 1000:
    print(b, end=',')
    a, b = b, a+b
```

# 推导式

+ Python 推导式是一种独特的数据处理方式，可以从一个数据序列构建另一个新的数据序列的结构体。
+ Python 支持各种数据结构的推导式：
  + 列表(list)推导式
  + 字典(dict)推导式
  + 集合(set)推导式
  + 元组(tuple)推导式

## 列表推导式

+ 列表推导式格式为：
```
[表达式 for 变量 in 列表] 
[out_exp_res for out_exp in input_list]

或者 

[表达式 for 变量 in 列表 if 条件]
[out_exp_res for out_exp in input_list if condition]
```

+ out_exp_res：列表生成元素表达式，可以是有返回值的函数。
+ for out_exp in input_list：迭代 input_list 将 out_exp 传入到 out_exp_res 表达式中。
+ if condition：条件语句，可以过滤列表中不符合条件的值。

## 字典推导式

+ 字典推导基本格式:
```
{ key_expr: value_expr for value in collection }

或

{ key_expr: value_expr for value in collection if condition }
```

## 集合推导式

+ 集合推导式基本格式：
```
{ expression for item in Sequence }
或
{ expression for item in Sequence if conditional }
```

## 元组推导式(生成器表达式)

+ 元组推导式可以利用 range 区间、元组、列表、字典和集合等数据类型，快速生成一个满足指定需求的元组
+ 元组推导式基本格式：
```
(expression for item in Sequence )
或
(expression for item in Sequence if conditional )
```

+ 元组推导式和列表推导式的用法也完全相同，只是元组推导式是用 () 圆括号将各部分括起来，而列表推导式用的是中括号 []，另外元组推导式返回的结果是一个生成器对象

# 迭代器与生成器

## 迭代器

+ 迭代是 Python 最强大的功能之一，是访问集合元素的一种方式。
+ 迭代器是一个可以记住遍历的位置的对象。
+ 迭代器对象从集合的第一个元素开始访问，直到所有的元素被访问完结束。迭代器只能往前不会后退。
+ 迭代器有两个基本的方法：iter() 和 next()。

## 生成器

+ 在 Python 中，使用了 yield 的函数被称为生成器（generator）。
+ yield 是一个关键字，用于定义生成器函数，生成器函数是一种特殊的函数，可以在迭代过程中逐步产生值，而不是一次性返回所有结果。
+ 跟普通函数不同的是，生成器是一个返回迭代器的函数，只能用于迭代操作，更简单点理解生成器就是一个迭代器。
+ 当在生成器函数中使用 yield 语句时，函数的执行将会暂停，并将 yield 后面的表达式作为当前迭代的值返回。
+ 然后，每次调用生成器的 next() 方法或使用 for 循环进行迭代时，函数会从上次暂停的地方继续执行，直到再次遇到 yield 语句。这样，生成器函数可以逐步产生值，而不需要一次性计算并返回所有结果。
+ 调用一个生成器函数，返回的是一个迭代器对象

# 函数

+ 函数是组织好的，可重复使用的，用来实现单一，或相关联功能的代码段。

+ 函数能提高应用的模块性，和代码的重复利用率。你已经知道Python提供了许多内建函数，比如print()。但你也可以自己创建函数，这被叫做用户自定义函数

+ 你可以定义一个由自己想要功能的函数，以下是简单的规则：
  + 函数代码块以 def 关键词开头，后接函数标识符名称和圆括号 ()。
  + 任何传入参数和自变量必须放在圆括号中间，圆括号之间可以用于定义参数。
  + 函数的第一行语句可以选择性地使用文档字符串—用于存放函数说明。
  + 函数内容以冒号 : 起始，并且缩进。
  + return [表达式] 结束函数，选择性地返回一个值给调用方，不带表达式的 return 相当于返回 None。

+ Python 定义函数使用 def 关键字，一般格式如下：
```
def 函数名（参数列表）:
    函数体
```

+ 定义一个函数：给了函数一个名称，指定了函数里包含的参数，和代码块结构。
+ 这个函数的基本结构完成以后，你可以通过另一个函数调用执行，也可以直接从 Python 命令提示符执行

## 参数传递

+ 在 python 中，类型属于对象，对象有不同类型的区分，变量是没有类型的：
```python
a=[1,2,3]

a="Runoob"
```
+ 以上代码中，[1,2,3] 是 List 类型，"Runoob" 是 String 类型，而变量 a 是没有类型，她仅仅是一个对象的引用（一个指针），可以是指向 List 类型对象，也可以是指向 String 类型对象

## 可更改(mutable)与不可更改(immutable)对象

+ 不可变类型：变量赋值 a=5 后再赋值 a=10，这里实际是新生成一个 int 值对象 10，再让 a 指向它，而 5 被丢弃，不是改变 a 的值，相当于新生成了 a。
+ 可变类型：变量赋值 la=[1,2,3,4] 后再赋值 la[2]=5 则是将 list la 的第三个元素值更改，本身la没有动，只是其内部的一部分值被修改了。

+ python 函数的参数传递：
  + 不可变类型：类似 C++ 的值传递，如整数、字符串、元组。如 fun(a)，传递的只是 a 的值，没有影响 a 对象本身。如果在 fun(a) 内部修改 a 的值，则是新生成一个 a 的对象。
  + 可变类型：类似 C++ 的引用传递，如 列表，字典。如 fun(la)，则是将 la 真正的传过去，修改后 fun 外部的 la 也会受影响

+ python 中一切都是对象，严格意义我们不能说值传递还是引用传递，我们应该说传不可变对象和传可变对象

## 参数

+ 以下是调用函数时可使用的正式参数类型：
  + 必需参数
  + 关键字参数
  + 默认参数
  + 不定长参数

### 必需参数

+ 必需参数须以正确的顺序传入函数。调用时的数量必须和声明时的一样。
+ 调用 printme() 函数，你必须传入一个参数，不然会出现语法错误：
```python
#!/usr/bin/python3
 
#可写函数说明
def printme( str ):
   "打印任何传入的字符串"
   print (str)
   return
 
# 调用 printme 函数，不加参数会报错
printme()
```

### 关键字参数

+ 关键字参数和函数调用关系紧密，函数调用使用关键字参数来确定传入的参数值。
+ 使用关键字参数允许函数调用时参数的顺序与声明时不一致，因为 Python 解释器能够用参数名匹配参数值。
+ 以下实例在函数 printme() 调用时使用参数名：
```python
#!/usr/bin/python3
 
#可写函数说明
def printme( str ):
   "打印任何传入的字符串"
   print (str)
   return
 
#调用printme函数
printme( str = "菜鸟教程")
```

### 默认参数

+ 调用函数时，如果没有传递参数，则会使用默认参数。以下实例中如果没有传入 age 参数，则使用默认值：
```python
#!/usr/bin/python3
 
#可写函数说明
def printinfo( name, age = 35 ):
   "打印任何传入的字符串"
   print ("名字: ", name)
   print ("年龄: ", age)
   return
 
#调用printinfo函数
printinfo( age=50, name="runoob" )
print ("------------------------")
printinfo( name="runoob" )
```

### 不定长参数

+ 你可能需要一个函数能处理比当初声明时更多的参数。这些参数叫做不定长参数，和上述 2 种参数不同，声明时不会命名。基本语法如下：
```python
def functionname([formal_args,] *var_args_tuple ):
   "函数_文档字符串"
   function_suite
   return [expression]
```

+ 加了星号 * 的参数会以元组(tuple)的形式导入，存放所有未命名的变量参数。
```python
#!/usr/bin/python3
  
# 可写函数说明
def printinfo( arg1, *vartuple ):
   "打印任何传入的参数"
   print ("输出: ")
   print (arg1)
   print (vartuple)
 
# 调用printinfo 函数
printinfo( 70, 60, 50 )
```

## 匿名函数

+ Python 使用 lambda 来创建匿名函数。
+ 所谓匿名，意即不再使用 def 语句这样标准的形式定义一个函数。
  + lambda 只是一个表达式，函数体比 def 简单很多。
  + lambda 的主体是一个表达式，而不是一个代码块。仅仅能在 lambda 表达式中封装有限的逻辑进去。
  + lambda 函数拥有自己的命名空间，且不能访问自己参数列表之外或全局命名空间里的参数。
  + 虽然 lambda 函数看起来只能写一行，却不等同于 C 或 C++ 的内联函数，内联函数的目的是调用小函数时不占用栈内存从而减少函数调用的开销，提高代码的执行速度。

### 语法

+ lambda 函数的语法只包含一个语句，如下：
```python
lambda [arg1 [,arg2,.....argn]]:expression
```

+ 设置参数 a 加上 10:
```python
x = lambda a : a + 10
print(x(5))
```

+ 我们可以将匿名函数封装在一个函数内，这样可以使用同样的代码来创建多个匿名函数。
+ 以下实例将匿名函数封装在 myfunc 函数中，通过传入不同的参数来创建不同的匿名函数：
```python
def myfunc(n):
  return lambda a : a * n
 
mydoubler = myfunc(2)
mytripler = myfunc(3)
 
print(mydoubler(11))
print(mytripler(11))
```

## return 语句

+ return [表达式] 语句用于退出函数，选择性地向调用方返回一个表达式。不带参数值的 return 语句返回 None。之前的例子都没有示范如何返回数值，以下实例演示了 return 语句的用法：
```python
#!/usr/bin/python3
 
# 可写函数说明
def sum( arg1, arg2 ):
   # 返回2个参数的和."
   total = arg1 + arg2
   print ("函数内 : ", total)
   return total
 
# 调用sum函数
total = sum( 10, 20 )
print ("函数外 : ", total)
```

## 强制位置参数

+ Python3.8 新增了一个函数形参语法 / 用来指明函数形参必须使用指定位置参数，不能使用关键字参数的形式。
+ 在以下的例子中，形参 a 和 b 必须使用指定位置参数，c 或 d 可以是位置形参或关键字形参，而 e 和 f 要求为关键字形参:
```python
def f(a, b, /, c, d, *, e, f):
    print(a, b, c, d, e, f)
```

+ 以下使用方法是正确的:
```python
f(10, 20, 30, d=40, e=50, f=60)
```

+ 以下使用方法会发生错误:
```python
f(10, b=20, c=30, d=40, e=50, f=60)   # b 不能使用关键字参数的形式
f(10, 20, 30, 40, 50, f=60)           # e 必须使用关键字参数的形式
```

# 模块

+ 在前面的几个章节中我们基本上是用 python 解释器来编程，如果你从 Python 解释器退出再进入，那么你定义的所有的方法和变量就都消失了。
+ 为此 Python 提供了一个办法，把这些定义存放在文件中，为一些脚本或者交互式的解释器实例使用，这个文件被称为模块。
+ 模块是一个包含所有你定义的函数和变量的文件，其后缀名是.py。模块可以被别的程序引入，以使用该模块中的函数等功能。这也是使用 python 标准库的方法。

## import 语句

+ 想使用 Python 源文件，只需在另一个源文件里执行 import 语句，语法如下：
```
import module1[, module2[,... moduleN]
```

+ 当解释器遇到 import 语句，如果模块在当前的搜索路径就会被导入。
+ 搜索路径是一个解释器会先进行搜索的所有目录的列表。如想要导入模块 support，需要把命令放在脚本的顶端：
```python
#!/usr/bin/python3
# Filename: support.py
 
def print_func( par ):
    print ("Hello : ", par)
    return
```

## from ... import 语句

+ Python 的 from 语句让你从模块中导入一个指定的部分到当前命名空间中，语法如下：
```
from modname import name1[, name2[, ... nameN]]
```

## from … import * 语句

+ 把一个模块的所有内容全都导入到当前的命名空间也是可行的，只需使用如下声明：
```
from modname import *
```

## __name__ 属性

+ 一个模块被另一个程序第一次引入时，其主程序将运行。如果我们想在模块被引入时，模块中的某一程序块不执行，我们可以用__name__属性来使该程序块仅在该模块自身运行时执行。
```python
#!/usr/bin/python3
# Filename: using_name.py

if __name__ == '__main__':
   print('程序自身在运行')
else:
   print('我来自另一模块')
```

+ 每个模块都有一个__name__属性，当其值是'__main__'时，表明该模块自身在运行，否则是被引入。
+ __name__ 与 __main__ 底下是双下划线， _ _ 是这样去掉中间的那个空格。

## dir() 函数

+ 内置的函数 dir() 可以找到模块内定义的所有名称。以一个字符串列表的形式返回:
```python
>>> import fibo, sys
>>> dir(fibo)
['__name__', 'fib', 'fib2']
>>> dir(sys)  
['__displayhook__', '__doc__', '__excepthook__', '__loader__', '__name__',
 '__package__', '__stderr__', '__stdin__', '__stdout__',
 '_clear_type_cache', '_current_frames', '_debugmallocstats', '_getframe',
 '_home', '_mercurial', '_xoptions', 'abiflags', 'api_version', 'argv',
 'base_exec_prefix', 'base_prefix', 'builtin_module_names', 'byteorder',
 'call_tracing', 'callstats', 'copyright', 'displayhook',
 'dont_write_bytecode', 'exc_info', 'excepthook', 'exec_prefix',
 'executable', 'exit', 'flags', 'float_info', 'float_repr_style',
 'getcheckinterval', 'getdefaultencoding', 'getdlopenflags',
 'getfilesystemencoding', 'getobjects', 'getprofile', 'getrecursionlimit',
 'getrefcount', 'getsizeof', 'getswitchinterval', 'gettotalrefcount',
 'gettrace', 'hash_info', 'hexversion', 'implementation', 'int_info',
 'intern', 'maxsize', 'maxunicode', 'meta_path', 'modules', 'path',
 'path_hooks', 'path_importer_cache', 'platform', 'prefix', 'ps1',
 'setcheckinterval', 'setdlopenflags', 'setprofile', 'setrecursionlimit',
 'setswitchinterval', 'settrace', 'stderr', 'stdin', 'stdout',
 'thread_info', 'version', 'version_info', 'warnoptions']
```

+ 如果没有给定参数，那么 dir() 函数会罗列出当前定义的所有名称:
```python
>>> a = [1, 2, 3, 4, 5]
>>> import fibo
>>> fib = fibo.fib
>>> dir() # 得到一个当前模块中定义的属性列表
['__builtins__', '__name__', 'a', 'fib', 'fibo', 'sys']
>>> a = 5 # 建立一个新的变量 'a'
>>> dir()
['__builtins__', '__doc__', '__name__', 'a', 'sys']
>>>
>>> del a # 删除变量名a
>>>
>>> dir()
['__builtins__', '__doc__', '__name__', 'sys']
>>>
```

## 标准模块

+ Python 本身带着一些标准的模块库，在 Python 库参考文档中将会介绍到（就是后面的"库参考文档"）。
+ 有些模块直接被构建在解析器里，这些虽然不是一些语言内置的功能，但是他却能很高效的使用，甚至是系统级调用也没问题。
+ 这些组件会根据不同的操作系统进行不同形式的配置，比如 winreg 这个模块就只会提供给 Windows 系统。
+ 应该注意到这有一个特别的模块 sys ，它内置在每一个 Python 解析器中。变量 sys.ps1 和 sys.ps2 定义了主提示符和副提示符所对应的字符串:
```python
>>> import sys
>>> sys.ps1
'>>> '
>>> sys.ps2
'... '
>>> sys.ps1 = 'C> '
C> print('Runoob!')
Runoob!
C> 
```

## 包

+ 包是一种管理 Python 模块命名空间的形式，采用"点模块名称"。

+ 比如一个模块的名称是 A.B， 那么他表示一个包 A中的子模块 B 。
+ 就好像使用模块的时候，你不用担心不同模块之间的全局变量相互影响一样，采用点模块名称这种形式也不用担心不同库之间的模块重名的情况。
+ 这样不同的作者都可以提供 NumPy 模块，或者是 Python 图形库。
+ 不妨假设你想设计一套统一处理声音文件和数据的模块（或者称之为一个"包"）。
+ 现存很多种不同的音频文件格式（基本上都是通过后缀名区分的，例如： .wav，:file:.aiff，:file:.au，），所以你需要有一组不断增加的模块，用来在不同的格式之间转换。
+ 并且针对这些音频数据，还有很多不同的操作（比如混音，添加回声，增加均衡器功能，创建人造立体声效果），所以你还需要一组怎么也写不完的模块来处理这些操作。
+ 这里给出了一种可能的包结构（在分层的文件系统中）:
```
sound/                          顶层包
      __init__.py               初始化 sound 包
      formats/                  文件格式转换子包
              __init__.py
              wavread.py
              wavwrite.py
              aiffread.py
              aiffwrite.py
              auread.py
              auwrite.py
              ...
      effects/                  声音效果子包
              __init__.py
              echo.py
              surround.py
              reverse.py
              ...
      filters/                  filters 子包
              __init__.py
              equalizer.py
              vocoder.py
              karaoke.py
              ...
```

+ 在导入一个包的时候，Python 会根据 sys.path 中的目录来寻找这个包中包含的子目录。
+ 目录只有包含一个叫做 __init__.py 的文件才会被认作是一个包，主要是为了避免一些滥俗的名字（比如叫做 string）不小心的影响搜索路径中的有效模块。
+ 最简单的情况，放一个空的 :file:__init__.py就可以了。当然这个文件中也可以包含一些初始化代码或者为（将在后面介绍的） __all__变量赋值。

+ 用户可以每次只导入一个包里面的特定模块，比如:
```python
import sound.effects.echo
```

+ 这将会导入子模块:sound.effects.echo。 他必须使用全名去访问:
```python
sound.effects.echo.echofilter(input, output, delay=0.7, atten=4)
```

+ 还有一种导入子模块的方法是:
```python
from sound.effects import echo
```

+ 这同样会导入子模块: echo，并且他不需要那些冗长的前缀，所以他可以这样使用:
```python
echo.echofilter(input, output, delay=0.7, atten=4)
```

+ 还有一种变化就是直接导入一个函数或者变量:
```python
from sound.effects.echo import echofilter
```

+ 同样的，这种方法会导入子模块: echo，并且可以直接使用他的 echofilter() 函数:
```python
echofilter(input, output, delay=0.7, atten=4)
```

+ 注意当使用 from package import item 这种形式的时候，对应的 item 既可以是包里面的子模块（子包），或者包里面定义的其他名称，比如函数，类或者变量。
+ import 语法会首先把 item 当作一个包定义的名称，如果没找到，再试图按照一个模块去导入。如果还没找到，抛出一个 :exc:ImportError 异常。
+ 反之，如果使用形如 import item.subitem.subsubitem 这种导入形式，除了最后一项，都必须是包，而最后一项则可以是模块或者是包，但是不可以是类，函数或者变量的名字。

# 输入输出

## 输出格式美化

+ Python两种输出值的方式: 表达式语句和 print() 函数。
+ 第三种方式是使用文件对象的 write() 方法，标准输出文件可以用 sys.stdout 引用。
+ 如果你希望输出的形式更加多样，可以使用 str.format() 函数来格式化输出值。
+ 如果你希望将输出的值转成字符串，可以使用 repr() 或 str() 函数来实现。
  + str()： 函数返回一个用户易读的表达形式。
  + repr()： 产生一个解释器易读的表达形式。

## 旧式字符串格式化

+ % 操作符也可以实现字符串格式化。 它将左边的参数作为类似 sprintf() 式的格式化字符串, 而将右边的代入, 然后返回格式化后的字符串. 例如:
```python
>>> import math
>>> print('常量 PI 的值近似为：%5.3f。' % math.pi)
常量 PI 的值近似为：3.142。
```

+ 因为 str.format() 是比较新的函数， 大多数的 Python 代码仍然使用 % 操作符。但是因为这种旧式的格式化最终会从该语言中移除, 应该更多的使用 str.format().

## 读取键盘输入

+ Python 提供了 input() 内置函数从标准输入读入一行文本，默认的标准输入是键盘。
```python
#!/usr/bin/python3

str = input("请输入：")
print ("你输入的内容是: ", str)
```

## 读和写文件

+ open() 将会返回一个 file 对象，基本语法格式如下:
```
open(filename, mode)
```
  + filename：包含了你要访问的文件名称的字符串值。
  + mode：决定了打开文件的模式：只读，写入，追加等。所有可取值见如下的完全列表。这个参数是非强制的，默认文件访问模式为只读(r)。

+ 以下实例将字符串写入到文件 foo.txt 中：
```python
#!/usr/bin/python3

# 打开一个文件
f = open("/tmp/foo.txt", "w")

f.write( "Python 是一个非常好的语言。\n是的，的确非常好!!\n" )

# 关闭打开的文件
f.close()
```
  + 第一个参数为要打开的文件名。
  + 第二个参数描述文件如何使用的字符。 mode 可以是 'r' 如果文件只读, 'w' 只用于写 (如果存在同名文件则将被删除), 和 'a' 用于追加文件内容; 所写的任何数据都会被自动增加到末尾. 'r+' 同时用于读写。 mode 参数是可选的; 'r' 将是默认值。

## 文件对象的方法

+ 本节中剩下的例子假设已经创建了一个称为 f 的文件对象。
+ f.read()
+ 为了读取一个文件的内容，调用 f.read(size), 这将读取一定数目的数据, 然后作为字符串或字节对象返回。
+ size 是一个可选的数字类型的参数。 当 size 被忽略了或者为负, 那么该文件的所有内容都将被读取并且返回。
+ 以下实例假定文件 foo.txt 已存在（上面实例中已创建）：
```python
#!/usr/bin/python3

# 打开一个文件
f = open("/tmp/foo.txt", "r")

str = f.read()
print(str)

# 关闭打开的文件
f.close()
```

+ f.readline()
+ f.readline() 会从文件中读取单独的一行。换行符为 '\n'。f.readline() 如果返回一个空字符串, 说明已经已经读取到最后一行。
```python
#!/usr/bin/python3

# 打开一个文件
f = open("/tmp/foo.txt", "r")

str = f.readline()
print(str)

# 关闭打开的文件
f.close()
```

+ f.readlines()
+ f.readlines() 将返回该文件中包含的所有行。
+ 如果设置可选参数 sizehint, 则读取指定长度的字节, 并且将这些字节按行分割。
```python
#!/usr/bin/python3

# 打开一个文件
f = open("/tmp/foo.txt", "r")

str = f.readlines()
print(str)

# 关闭打开的文件
f.close()
```

+ f.write()
+ f.write(string) 将 string 写入到文件中, 然后返回写入的字符数。
```python
#!/usr/bin/python3

# 打开一个文件
f = open("/tmp/foo.txt", "w")

num = f.write( "Python 是一个非常好的语言。\n是的，的确非常好!!\n" )
print(num)
# 关闭打开的文件
f.close()
```

+ f.tell()
+ f.tell() 返回文件对象当前所处的位置, 它是从文件开头开始算起的字节数。

+ f.seek()
+ 如果要改变文件指针当前的位置, 可以使用 f.seek(offset, from_what) 函数。
+ from_what 的值, 如果是 0 表示开头, 如果是 1 表示当前位置, 2 表示文件的结尾，例如：
  + seek(x,0) ： 从起始位置即文件首行首字符开始移动 x 个字符
  + seek(x,1) ： 表示从当前位置往后移动x个字符
  + seek(-x,2)：表示从文件的结尾往前移动x个字符
+ from_what 值为默认为0，即文件开头。下面给出一个完整的例子：
```python
>>> f = open('/tmp/foo.txt', 'rb+')
>>> f.write(b'0123456789abcdef')
16
>>> f.seek(5)     # 移动到文件的第六个字节
5
>>> f.read(1)
b'5'
>>> f.seek(-3, 2) # 移动到文件的倒数第三字节
13
>>> f.read(1)
b'd'
```

+ f.close()
+ 在文本文件中 (那些打开文件的模式下没有 b 的), 只会相对于文件起始位置进行定位。
+ 当你处理完一个文件后, 调用 f.close() 来关闭文件并释放系统的资源，如果尝试再调用该文件，则会抛出异常。
```python
>>> f.close()
>>> f.read()
Traceback (most recent call last):
  File "<stdin>", line 1, in ?
ValueError: I/O operation on closed file
```

+ 当处理一个文件对象时, 使用 with 关键字是非常好的方式。在结束后, 它会帮你正确的关闭文件。 而且写起来也比 try - finally 语句块要简短:
```python
>>> with open('/tmp/foo.txt', 'r') as f:
...     read_data = f.read()
>>> f.closed
True
```

## pickle 模块

+ python的pickle模块实现了基本的数据序列和反序列化。
+ 通过pickle模块的序列化操作我们能够将程序中运行的对象信息保存到文件中去，永久存储。
+ 通过pickle模块的反序列化操作，我们能够从文件中创建上一次程序保存的对象。

+ 基本接口：
```python
pickle.dump(obj, file, [,protocol])
```

# python3 OS 文件/目录 方法

+ os 模块提供了非常丰富的方法用来处理文件和目录。常用的方法如下表所示：
序号	方法及描述
1	
os.access(path, mode)


检验权限模式
2	
os.chdir(path)


改变当前工作目录
3	
os.chflags(path, flags)


设置路径的标记为数字标记。
4	
os.chmod(path, mode)


更改权限
5	
os.chown(path, uid, gid)


更改文件所有者
6	
os.chroot(path)


改变当前进程的根目录
7	
os.close(fd)


关闭文件描述符 fd
8	
os.closerange(fd_low, fd_high)


关闭所有文件描述符，从 fd_low (包含) 到 fd_high (不包含), 错误会忽略
9	
os.dup(fd)


复制文件描述符 fd
10	
os.dup2(fd, fd2)


将一个文件描述符 fd 复制到另一个 fd2
11	
os.fchdir(fd)


通过文件描述符改变当前工作目录
12	
os.fchmod(fd, mode)


改变一个文件的访问权限，该文件由参数fd指定，参数mode是Unix下的文件访问权限。
13	
os.fchown(fd, uid, gid)


修改一个文件的所有权，这个函数修改一个文件的用户ID和用户组ID，该文件由文件描述符fd指定。
14	
os.fdatasync(fd)


强制将文件写入磁盘，该文件由文件描述符fd指定，但是不强制更新文件的状态信息。
15	
os.fdopen(fd[, mode[, bufsize]])


通过文件描述符 fd 创建一个文件对象，并返回这个文件对象
16	
os.fpathconf(fd, name)


返回一个打开的文件的系统配置信息。name为检索的系统配置的值，它也许是一个定义系统值的字符串，这些名字在很多标准中指定（POSIX.1, Unix 95, Unix 98, 和其它）。
17	
os.fstat(fd)


返回文件描述符fd的状态，像stat()。
18	
os.fstatvfs(fd)


返回包含文件描述符fd的文件的文件系统的信息，Python 3.3 相等于 statvfs()。
19	
os.fsync(fd)


强制将文件描述符为fd的文件写入硬盘。
20	
os.ftruncate(fd, length)


裁剪文件描述符fd对应的文件, 所以它最大不能超过文件大小。
21	
os.getcwd()


返回当前工作目录
22	
os.getcwdb()


返回一个当前工作目录的Unicode对象
23	
os.isatty(fd)


如果文件描述符fd是打开的，同时与tty(-like)设备相连，则返回true, 否则False。
24	
os.lchflags(path, flags)


设置路径的标记为数字标记，类似 chflags()，但是没有软链接
25	
os.lchmod(path, mode)


修改连接文件权限
26	
os.lchown(path, uid, gid)


更改文件所有者，类似 chown，但是不追踪链接。
27	
os.link(src, dst)


创建硬链接，名为参数 dst，指向参数 src
28	
os.listdir(path)


返回path指定的文件夹包含的文件或文件夹的名字的列表。
29	
os.lseek(fd, pos, how)


设置文件描述符 fd当前位置为pos, how方式修改: SEEK_SET 或者 0 设置从文件开始的计算的pos; SEEK_CUR或者 1 则从当前位置计算; os.SEEK_END或者2则从文件尾部开始. 在unix，Windows中有效
30	
os.lstat(path)


像stat(),但是没有软链接
31	
os.major(device)


从原始的设备号中提取设备major号码 (使用stat中的st_dev或者st_rdev field)。
32	
os.makedev(major, minor)


以major和minor设备号组成一个原始设备号
33	
os.makedirs(path[, mode])


递归文件夹创建函数。像mkdir(), 但创建的所有intermediate-level文件夹需要包含子文件夹。
34	
os.minor(device)


从原始的设备号中提取设备minor号码 (使用stat中的st_dev或者st_rdev field )。
35	
os.mkdir(path[, mode])


以数字mode的mode创建一个名为path的文件夹.默认的 mode 是 0777 (八进制)。
36	
os.mkfifo(path[, mode])


创建命名管道，mode 为数字，默认为 0666 (八进制)
37	
os.mknod(filename[, mode=0600, device])
创建一个名为filename文件系统节点（文件，设备特别文件或者命名pipe）。

38	
os.open(file, flags[, mode])


打开一个文件，并且设置需要的打开选项，mode参数是可选的
39	
os.openpty()


打开一个新的伪终端对。返回 pty 和 tty的文件描述符。
40	
os.pathconf(path, name)


返回相关文件的系统配置信息。
41	
os.pipe()


创建一个管道. 返回一对文件描述符(r, w) 分别为读和写
42	
os.popen(command[, mode[, bufsize]])


从一个 command 打开一个管道
43	
os.read(fd, n)


从文件描述符 fd 中读取最多 n 个字节，返回包含读取字节的字符串，文件描述符 fd对应文件已达到结尾, 返回一个空字符串。
44	
os.readlink(path)


返回软链接所指向的文件
45	
os.remove(path)


删除路径为path的文件。如果path 是一个文件夹，将抛出OSError; 查看下面的rmdir()删除一个 directory。
46	
os.removedirs(path)


递归删除目录。
47	
os.rename(src, dst)


重命名文件或目录，从 src 到 dst
48	
os.renames(old, new)


递归地对目录进行更名，也可以对文件进行更名。
49	
os.rmdir(path)


删除path指定的空目录，如果目录非空，则抛出一个OSError异常。
50	
os.stat(path)


获取path指定的路径的信息，功能等同于C API中的stat()系统调用。
51	
os.stat_float_times([newvalue])
决定stat_result是否以float对象显示时间戳

52	
os.statvfs(path)


获取指定路径的文件系统统计信息
53	
os.symlink(src, dst)


创建一个软链接
54	
os.tcgetpgrp(fd)


返回与终端fd（一个由os.open()返回的打开的文件描述符）关联的进程组
55	
os.tcsetpgrp(fd, pg)


设置与终端fd（一个由os.open()返回的打开的文件描述符）关联的进程组为pg。
56	
os.tempnam([dir[, prefix]])


Python3 中已删除。返回唯一的路径名用于创建临时文件。
57	
os.tmpfile()


Python3 中已删除。返回一个打开的模式为(w+b)的文件对象 .这文件对象没有文件夹入口，没有文件描述符，将会自动删除。
58	
os.tmpnam()


Python3 中已删除。为创建一个临时文件返回一个唯一的路径
59	
os.ttyname(fd)


返回一个字符串，它表示与文件描述符fd 关联的终端设备。如果fd 没有与终端设备关联，则引发一个异常。
60	
os.unlink(path)


删除文件路径
61	
os.utime(path, times)


返回指定的path文件的访问和修改的时间。
62	
os.walk(top[, topdown=True[, onerror=None[, followlinks=False]]])


输出在文件夹中的文件名通过在树中游走，向上或者向下。
63	
os.write(fd, str)


写入字符串到文件描述符 fd中. 返回实际写入的字符串长度
64	
os.path 模块


获取文件的属性信息。
65	
os.pardir()


获取当前目录的父目录，以字符串形式显示目录名。
66	
os.replace()


重命名文件或目录。

# 错误和异常

+ Python 有两种错误很容易辨认：语法错误和异常。
+ Python assert（断言）用于判断一个表达式，在表达式条件为 false 的时候触发异常。

## 异常

+ 即便 Python 程序的语法是正确的，在运行它的时候，也有可能发生错误。运行期检测到的错误被称为异常。
+ 错误信息的前面部分显示了异常发生的上下文，并以调用栈的形式显示具体信息

## 异常处理 try/except

+ try 语句按照如下方式工作；
  + 首先，执行 try 子句（在关键字 try 和关键字 except 之间的语句）。
  + 如果没有异常发生，忽略 except 子句，try 子句执行后结束。
  + 如果在执行 try 子句的过程中发生了异常，那么 try 子句余下的部分将被忽略。如果异常的类型和 except 之后的名称相符，那么对应的 except 子句将被执行。
  + 如果一个异常没有与任何的 except 匹配，那么这个异常将会传递给上层的 try 中。

+ 一个 try 语句可能包含多个except子句，分别来处理不同的特定的异常。最多只有一个分支会被执行

+ 处理程序将只针对对应的 try 子句中的异常进行处理，而不是其他的 try 的处理程序中的异常。
+ 一个except子句可以同时处理多个异常，这些异常将被放在一个括号里成为一个元组

## try/except...else

+ try/except 语句还有一个可选的 else 子句，如果使用这个子句，那么必须放在所有的 except 子句之后

+ else 子句将在 try 子句没有发生任何异常的时候执行。

## try-finally 语句

+ try-finally 语句无论是否发生异常都将执行最后的代码。

## 抛出异常

+ Python 使用 raise 语句抛出一个指定的异常。
+ raise语法格式如下：
```python
raise [Exception [, args [, traceback]]]
```

+ raise 唯一的一个参数指定了要被抛出的异常。它必须是一个异常的实例或者是异常的类（也就是 Exception 的子类）。
+ 如果你只想知道这是否抛出了一个异常，并不想去处理它，那么一个简单的 raise 语句就可以再次把它抛出

## 用户自定义异常

+ 你可以通过创建一个新的异常类来拥有自己的异常。异常类继承自 Exception 类，可以直接继承，或者间接继承，例如:

## 定义清理行为

+ try 语句还有另外一个可选的子句，它定义了无论在任何情况下都会执行的清理行为。 例如:

## 预定义的清理行为

+ 一些对象定义了标准的清理行为，无论系统是否成功的使用了它，一旦不需要它了，那么这个标准的清理行为就会执行