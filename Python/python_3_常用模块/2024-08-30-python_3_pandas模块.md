---
category: Python
date: 2024-08-30 09:01:00 +0800
layout: post
title: python_3_pandas模块
tag: Python
---
## 简介

+ pandas模块相关笔记

## python3 pandas模块 详解

Pandas 是 Python 数据分析中最常用的库之一，它提供了数据结构和数据分析工具，尤其擅长处理表格数据。以下是 Pandas 模块的一些详细介绍。

### 1. 安装 Pandas
在使用 Pandas 之前，你需要确保已经安装了它。可以使用以下命令进行安装：

```bash
pip install pandas
```

### 2. 导入 Pandas
导入 Pandas 通常使用 `pd` 作为别名：

```python
import pandas as pd
```

### 3. 核心数据结构

#### 3.1 Series
`Series` 是 Pandas 的基本数据结构之一，它是一维的，类似于 Python 中的列表或字典。

```python
import pandas as pd

# 创建一个简单的 Series
s = pd.Series([1, 3, 5, 7, 9])
print(s)
```

#### 3.2 DataFrame
`DataFrame` 是 Pandas 中最重要的数据结构，它是一个二维的表格数据结构，可以理解为一个“表格”或“电子表格”。

```python
# 创建一个简单的 DataFrame
data = {
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Age': [25, 30, 35],
    'City': ['New York', 'Los Angeles', 'Chicago']
}

df = pd.DataFrame(data)
print(df)
```

### 4. DataFrame 基本操作

#### 4.1 查看数据
- **头部和尾部**：使用 `head()` 和 `tail()` 方法可以查看数据的前几行和最后几行。

```python
print(df.head())  # 默认前5行
print(df.tail(2))  # 最后2行
```

- **数据概览**：使用 `info()` 和 `describe()` 方法可以获取 DataFrame 的基本信息和统计摘要。

```python
print(df.info())  # 数据结构信息
print(df.describe())  # 数值列的统计信息
```

#### 4.2 选择数据
- **选择列**：可以通过列名选择特定列。

```python
print(df['Name'])  # 返回 Name 列
print(df[['Name', 'Age']])  # 返回 Name 和 Age 列
```

- **选择行**：使用 `loc` 和 `iloc` 方法选择特定的行。

```python
# 根据标签选择
print(df.loc[0])  # 返回第0行

# 根据索引选择
print(df.iloc[0])  # 返回第0行
```

#### 4.3 条件筛选
Pandas 提供了强大的条件筛选功能。

```python
# 筛选 Age 大于 30 的行
filtered_df = df[df['Age'] > 30]
print(filtered_df)
```

### 5. 数据清理

#### 5.1 缺失值处理
- **检测缺失值**：使用 `isnull()` 和 `notnull()` 可以检测缺失值。

```python
print(df.isnull())  # 检查所有数据的缺失情况
```

- **填充缺失值**：使用 `fillna()` 方法可以填充缺失值。

```python
df_filled = df.fillna(0)  # 将缺失值填充为 0
```

- **删除缺失值**：使用 `dropna()` 方法可以删除含有缺失值的行或列。

```python
df_dropped = df.dropna()  # 删除含有缺失值的行
```

#### 5.2 数据转换
- **修改数据类型**：使用 `astype()` 可以转换数据类型。

```python
df['Age'] = df['Age'].astype(float)
```

- **字符串操作**：可以使用 `.str` 访问字符串方法。

```python
df['Name'] = df['Name'].str.upper()  # 将 Name 列的值全部转换为大写
```

### 6. 数据分析

#### 6.1 排序
使用 `sort_values()` 方法可以对 DataFrame 进行排序。

```python
df_sorted = df.sort_values(by='Age', ascending=False)  # 按 Age 降序排列
```

#### 6.2 分组操作
使用 `groupby()` 方法可以对数据进行分组，并对每组数据进行聚合操作。

```python
grouped = df.groupby('City')['Age'].mean()  # 按 City 分组，并计算 Age 的平均值
print(grouped)
```

#### 6.3 合并数据
Pandas 提供了 `merge()`、`concat()` 和 `join()` 等方法来合并数据。

```python
# 合并两个 DataFrame
df1 = pd.DataFrame({'key': ['A', 'B', 'C'], 'value': [1, 2, 3]})
df2 = pd.DataFrame({'key': ['A', 'B', 'D'], 'value': [4, 5, 6]})

merged_df = pd.merge(df1, df2, on='key', how='inner')  # 内连接
print(merged_df)
```

### 7. 数据输入输出

- **读取 CSV 文件**：使用 `read_csv()` 方法可以从 CSV 文件读取数据。

```python
df = pd.read_csv('data.csv')
```

- **写入 CSV 文件**：使用 `to_csv()` 方法可以将 DataFrame 保存为 CSV 文件。

```python
df.to_csv('output.csv', index=False)
```

### 8. 可视化
Pandas 可以与 Matplotlib、Seaborn 等库结合使用来生成图表。

```python
import matplotlib.pyplot as plt

df['Age'].plot(kind='hist')
plt.show()
```

### 9. 高级功能

#### 9.1 透视表
使用 `pivot_table()` 方法可以生成透视表。

```python
pivot = df.pivot_table(values='Age', index='City', columns='Name', aggfunc='mean')
print(pivot)
```

#### 9.2 时间序列分析
Pandas 提供了强大的时间序列处理功能。

```python
# 将列转换为日期格式
df['Date'] = pd.to_datetime(df['Date'])

# 设置索引为日期
df.set_index('Date', inplace=True)

# 进行重采样
df_resampled = df.resample('M').mean()  # 按月重采样
```

### 10. 实用技巧

- **链式操作**：Pandas 支持链式操作，可以将多个操作链式连接在一起，代码更简洁。

```python
result = df.dropna().sort_values(by='Age').reset_index(drop=True)
```

- **使用 `.apply()` 函数**：`apply()` 函数可以对 Series 或 DataFrame 应用自定义函数。

```python
df['Age_plus_one'] = df['Age'].apply(lambda x: x + 1)
```

以上是 Pandas 模块的简要详解，Pandas 功能丰富，在实际应用中还可以深入学习更多高级用法。