# 简介

+ Python编程语言的理论基础

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