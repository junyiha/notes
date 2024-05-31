---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_3_numpy模块
tag: Python
---
## 简介

+ numpy库相关笔记

## python3 numpy库 详解

NumPy（Numerical Python）是Python中用于数值计算的核心库之一。它提供了强大的多维数组对象（例如ndarray）、用于数组操作的基本函数、线性代数运算、傅立叶变换以及随机数生成等功能。以下是NumPy库的一些详解：

1. **多维数组对象（ndarray）**：NumPy的核心是多维数组对象（ndarray），它是一个具有固定大小的同类数据项的数组。这意味着在ndarray中的所有元素必须是相同类型的，这使得NumPy非常高效。ndarray可以是一维、二维或更高维度的数组，它可以表示矩阵、张量等数据结构。

2. **数组操作**：NumPy提供了许多用于数组操作的函数，例如索引、切片、形状操作、数组拼接、数组分裂等。这些操作使得在NumPy中进行数组操作变得非常方便。

3. **数学函数**：NumPy包含了许多常用的数学函数，例如三角函数、指数函数、对数函数等。这些函数可以直接应用于ndarray对象，也可以用于逐元素操作。

4. **线性代数运算**：NumPy提供了一组用于执行线性代数运算的函数，例如矩阵乘法、求逆矩阵、求解线性方程组等。这些函数使得在NumPy中进行线性代数计算变得非常方便。

5. **傅立叶变换**：NumPy提供了用于执行傅立叶变换的函数，包括离散傅立叶变换（DFT）和傅立叶逆变换。这些函数对信号处理和频域分析非常有用。

6. **随机数生成**：NumPy包含了用于生成随机数的函数，例如生成服从特定分布的随机数、随机抽样等。这些函数可以用于模拟、蒙特卡罗方法等。

总之，NumPy是Python中用于数值计算的重要库，它提供了丰富的功能和高效的数组操作，使得在Python中进行科学计算变得非常方便和高效。

## python3 numpy库 常用技巧

NumPy库提供了许多强大的功能和技巧，使得在处理数值数据时更加高效和便捷。以下是一些常用的NumPy技巧：

1. **创建数组**：使用`np.array()`函数可以从Python列表或元组创建NumPy数组。另外，NumPy还提供了一些便捷的函数来创建特定类型的数组，如`np.zeros()`、`np.ones()`、`np.arange()`、`np.linspace()`等。

```python
import numpy as np

# 从Python列表创建数组
arr = np.array([1, 2, 3, 4, 5])

# 创建全零数组
zeros_arr = np.zeros((3, 3))

# 创建全一数组
ones_arr = np.ones((2, 2))

# 创建等间隔数组
range_arr = np.arange(0, 10, 2)

# 创建线性空间数组
lin_space_arr = np.linspace(0, 1, 5)
```

2. **数组操作**：NumPy提供了许多用于数组操作的函数，如索引、切片、形状操作、数组拼接、数组分裂等。

```python
import numpy as np

arr = np.array([[1, 2, 3],
                [4, 5, 6],
                [7, 8, 9]])

# 获取数组形状
shape = arr.shape

# 获取数组维度
dim = arr.ndim

# 获取数组元素类型
dtype = arr.dtype

# 获取数组元素数量
size = arr.size

# 数组切片
slice_arr = arr[0:2, 1:3]

# 数组拼接
concat_arr = np.concatenate((arr, arr), axis=0)

# 数组分裂
split_arr = np.split(arr, 3)
```

3. **数学函数**：NumPy提供了丰富的数学函数，如三角函数、指数函数、对数函数等。

```python
import numpy as np

arr = np.array([0, np.pi/4, np.pi/2])

# 正弦函数
sin_arr = np.sin(arr)

# 指数函数
exp_arr = np.exp(arr)

# 自然对数函数
log_arr = np.log(arr)
```

4. **线性代数运算**：NumPy提供了一组用于执行线性代数运算的函数，如矩阵乘法、求逆矩阵、求解线性方程组等。

```python
import numpy as np

A = np.array([[1, 2],
              [3, 4]])

B = np.array([[5, 6],
              [7, 8]])

# 矩阵乘法
mat_mul = np.dot(A, B)

# 求逆矩阵
inv_mat = np.linalg.inv(A)

# 求解线性方程组
x = np.linalg.solve(A, np.array([1, 2]))
```

这些只是NumPy库中一些常用的技巧和功能。NumPy还提供了许多其他功能，如统计函数、随机数生成、广播等，可以根据具体需求选择合适的函数和方法。

## python3 numpy.transpose() 函数 详解

`numpy.transpose()` 函数是 NumPy 库中用于对数组进行转置操作的函数。转置操作是将数组的维度重新排列，即将数组的行和列互换位置。

### 语法
```python
numpy.transpose(a, axes=None)
```

- `a`: 输入的数组。
- `axes`: 指定转置操作后的维度顺序。如果不指定，则默认将数组的维度逆序。

### 返回值
返回转置后的数组。

### 示例
```python
import numpy as np

arr = np.array([[1, 2, 3],
                [4, 5, 6]])

transposed_arr = np.transpose(arr)
print(transposed_arr)
```
输出：
```
[[1 4]
 [2 5]
 [3 6]]
```

在这个例子中，原始数组 `arr` 是一个 2x3 的数组。调用 `np.transpose(arr)` 后，得到一个 3x2 的数组，即将原数组的行和列互换了位置。

### 指定轴顺序
```python
import numpy as np

arr = np.array([[1, 2, 3],
                [4, 5, 6]])

transposed_arr = np.transpose(arr, axes=(1, 0))
print(transposed_arr)
```
输出：
```
[[1 4]
 [2 5]
 [3 6]]
```

在这个示例中，我们通过 `axes=(1, 0)` 指定了转置后的轴顺序，结果与未指定时相同。