---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_3_logging模块
tag: Python
---
## 简介

+ logging模块笔记

## python3 logging模块 输出到文件并且输出到终端

在Python中，使用`logging`模块可以方便地进行日志记录。要将日志同时输出到文件和终端，你可以配置两个不同的`Handler`，一个用于文件输出，另一个用于控制台输出。以下是一个示例：

```python
import logging

# 创建Logger对象
logger = logging.getLogger('my_logger')
logger.setLevel(logging.DEBUG)

# 创建文件处理器，并设置日志级别为DEBUG
file_handler = logging.FileHandler('my_log_file.log')
file_handler.setLevel(logging.DEBUG)

# 创建控制台处理器，并设置日志级别为DEBUG
console_handler = logging.StreamHandler()
console_handler.setLevel(logging.DEBUG)

# 创建日志格式器
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')

# 将格式器添加到处理器
file_handler.setFormatter(formatter)
console_handler.setFormatter(formatter)

# 将处理器添加到Logger对象
logger.addHandler(file_handler)
logger.addHandler(console_handler)

# 记录一些日志信息
logger.debug('This is a debug message')
logger.info('This is an info message')
logger.warning('This is a warning message')
logger.error('This is an error message')
logger.critical('This is a critical message')
```

在上面的示例中，首先创建了一个`Logger`对象，然后创建了一个文件处理器(`FileHandler`)和一个控制台处理器(`StreamHandler`)。每个处理器都设置了日志级别，并将日志格式器添加到处理器中。最后，将处理器添加到`Logger`对象中。

在记录日志时，`logger.debug()`, `logger.info()`, `logger.warning()`, `logger.error()`, 和 `logger.critical()` 分别对应不同的日志级别。这些消息将根据其级别分别被发送到文件和终端。

请根据实际需求修改文件名、日志级别、日志格式等参数。

## python3 logging模块 详解

Python的`logging`模块是一个用于记录日志信息的标准库工具，它提供了强大的日志记录功能，允许你在应用程序中添加日志记录，以便于调试、监视和故障排除。以下是Python 3中`logging`模块的详解：

### 基本日志记录示例

首先，让我们看一个基本的`logging`模块的使用示例：

```python
import logging

# 配置日志记录器
logging.basicConfig(filename='app.log', level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# 记录日志信息
logging.debug('This is a debug message.')
logging.info('This is an info message.')
logging.warning('This is a warning message.')
logging.error('This is an error message.')
logging.critical('This is a critical message.')
```

上述代码中，我们首先通过`basicConfig`函数配置了一个日志记录器。配置中的参数包括：
- `filename`：指定日志输出到的文件。
- `level`：设置最低的日志级别，只有达到这个级别或更高级别的日志信息才会被记录。
- `format`：指定日志记录的格式，可以包含时间、日志级别、消息等信息。

然后，我们使用`logging`模块的不同函数来记录不同级别的日志信息。日志级别从低到高依次为：DEBUG、INFO、WARNING、ERROR、CRITICAL。

### 日志处理器（Handlers）

`logging`模块允许你将日志信息发送到不同的目标，这些目标被称为“处理器（Handlers）”。常见的处理器包括：

- **StreamHandler：** 将日志信息输出到控制台（标准输出流）。
- **FileHandler：** 将日志信息写入文件。
- **RotatingFileHandler：** 类似于FileHandler，但可以在日志文件达到一定大小时自动切分成多个文件。
- **SMTPHandler：** 将日志信息通过邮件发送。
- **SocketHandler：** 将日志信息发送到网络套接字。
- **SysLogHandler：** 将日志信息发送到系统日志。

你可以根据需要选择一个或多个处理器，并将它们添加到日志记录器中，以便将日志信息发送到多个目标。例如：

```python
import logging

# 创建日志记录器
logger = logging.getLogger('my_logger')

# 配置日志记录器
logger.setLevel(logging.DEBUG)

# 创建处理器并添加到日志记录器
console_handler = logging.StreamHandler()
file_handler = logging.FileHandler('app.log')

# 配置处理器的日志级别和格式
console_handler.setLevel(logging.INFO)
file_handler.setLevel(logging.DEBUG)

formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
console_handler.setFormatter(formatter)
file_handler.setFormatter(formatter)

logger.addHandler(console_handler)
logger.addHandler(file_handler)

# 记录日志信息
logger.debug('This is a debug message.')
logger.info('This is an info message.')
```

### 日志过滤器（Filters）

日志过滤器允许你更精细地控制哪些日志记录应该被处理器处理。你可以定义自己的过滤器函数，并将它们添加到处理器或日志记录器中。过滤器函数可以基于日志消息内容、日志级别等条件来决定是否处理某条日志记录。

### 自定义日志记录器

你可以创建多个不同的日志记录器，每个日志记录器可以有不同的配置、处理器和过滤器，以满足不同模块或组件的日志记录需求。这样可以更好地组织和管理日志信息。

```python
import logging

# 创建两个不同的日志记录器
logger1 = logging.getLogger('module1_logger')
logger2 = logging.getLogger('module2_logger')

# 配置日志记录器
logger1.setLevel(logging.DEBUG)
logger2.setLevel(logging.INFO)

# 创建处理器并添加到日志记录器
file_handler1 = logging.FileHandler('module1.log')
file_handler2 = logging.FileHandler('module2.log')

logger1.addHandler(file_handler1)
logger2.addHandler(file_handler2)

# 记录日志信息
logger1.debug('This is a debug message from module 1.')
logger2.info('This is an info message from module 2.')
```

总之，`logging`模块是Python中强大而灵活的日志记录工具，可以帮助你有效地记录和管理日志信息，以便更好地监视和维护你的应用程序。通过适当地配置处理器、过滤器和日志记录器，你可以满足各种不同的日志记录需求。