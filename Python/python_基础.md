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