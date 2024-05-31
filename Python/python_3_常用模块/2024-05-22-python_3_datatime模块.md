---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_3_datatime模块
tag: Python
---
## 简介

+ datetime模块笔记

## python3 datetime模块 详解

`datetime` 模块是 Python 标准库中用于处理日期和时间的重要模块。它提供了各种类和函数，允许你在 Python 中执行日期和时间操作。以下是 `datetime` 模块的一些重要类和函数，以及它们的详细说明：

1. **datetime 类**：

   `datetime` 类是 `datetime` 模块的核心，用于表示日期和时间的对象。它包含年、月、日、时、分、秒和微秒等信息。你可以使用 `datetime` 类来执行日期和时间的各种操作，例如创建日期时间对象、格式化日期时间、执行算术运算等。

   ```python
   from datetime import datetime

   # 获取当前日期时间
   now = datetime.now()

   # 创建自定义日期时间对象
   custom_date = datetime(2023, 5, 15, 10, 30)

   # 格式化日期时间为字符串
   formatted_date = now.strftime("%Y-%m-%d %H:%M:%S")

   # 执行日期时间算术操作
   delta = custom_date - now
   ```

2. **date 类**：

   `date` 类用于表示日期信息，不包括具体时间。它包含年、月和日信息。

   ```python
   from datetime import date

   # 创建日期对象
   today = date.today()

   # 访问日期的年、月、日
   year = today.year
   month = today.month
   day = today.day
   ```

3. **time 类**：

   `time` 类用于表示时间信息，不包括日期。它包含时、分、秒和微秒信息。

   ```python
   from datetime import time

   # 创建时间对象
   current_time = time(14, 30, 0)

   # 访问时间的时、分、秒
   hour = current_time.hour
   minute = current_time.minute
   second = current_time.second
   ```

4. **timedelta 类**：

   `timedelta` 类用于表示时间间隔，可以用于执行日期时间的算术运算，如加法和减法。

   ```python
   from datetime import timedelta

   # 创建时间间隔
   delta = timedelta(days=5, hours=2, minutes=30)

   # 执行日期时间的算术运算
   future_date = now + delta
   ```

5. **strftime 和 strptime 函数**：

   `strftime` 函数用于将日期时间对象格式化为字符串，而 `strptime` 函数用于将字符串解析为日期时间对象。

   ```python
   from datetime import datetime

   formatted_date = now.strftime("%Y-%m-%d %H:%M:%S")
   parsed_date = datetime.strptime("2023-05-15 10:30:00", "%Y-%m-%d %H:%M:%S")
   ```

这只是 `datetime` 模块的一部分功能。你可以使用这些类和函数来执行日期和时间相关的各种操作，包括日期时间的比较、格式化、时区处理、日历计算等。这个模块非常强大，适用于各种日期时间处理需求。
