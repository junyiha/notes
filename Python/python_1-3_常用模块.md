## 简介

+ python常用的模块，第三方工具

## python3 threading 模块 详解

`threading` 模块是 Python 3 中用于多线程编程的标准库模块，它提供了一种方便的方式来创建和管理线程。多线程允许在同一程序中同时执行多个任务，可以提高程序的并发性和性能。以下是有关 `threading` 模块的详细解释和示例：

**线程的创建**：

1. `threading.Thread` 类：`Thread` 类是创建线程的主要工具。您可以通过创建 `Thread` 类的实例来定义一个新线程，并将要执行的任务（通常是一个函数）传递给 `target` 参数。

   ```python
   import threading

   def my_function():
       # 执行任务的代码

   my_thread = threading.Thread(target=my_function)
   ```

2. 启动线程：使用 `start()` 方法来启动线程，它将在后台执行线程的任务。

   ```python
   my_thread.start()
   ```

**线程的控制**：

1. `threading.Thread.is_alive()`：检查线程是否处于活动状态（正在运行）。

   ```python
   if my_thread.is_alive():
       print("Thread is alive")
   ```

2. `threading.Thread.join()`：等待线程执行完毕。主线程可以使用 `join()` 方法等待其他线程的完成。

   ```python
   my_thread.join()
   ```

**线程同步**：

1. `threading.Lock` 类：`Lock` 类用于创建锁，以确保多个线程之间的互斥访问共享资源。

   ```python
   my_lock = threading.Lock()

   def my_thread_function():
       with my_lock:
           # 访问共享资源的代码
   ```

2. `threading.Event` 类：`Event` 类用于线程之间的事件通知和等待。

   ```python
   my_event = threading.Event()

   def waiting_thread():
       my_event.wait()  # 等待事件被设置
       # 事件被设置后执行的代码

   def setting_thread():
       # 执行某些操作
       my_event.set()  # 设置事件
   ```

**线程间通信**：

1. 使用队列：`queue` 模块提供了线程安全的队列（`queue.Queue`）用于在线程之间安全地传递数据。

   ```python
   import threading
   import queue

   my_queue = queue.Queue()

   def producer():
       # 生产数据
       my_queue.put(data)

   def consumer():
       # 消费数据
       data = my_queue.get()
   ```

**线程池**：

`threading` 模块还提供了 `ThreadPoolExecutor` 类，它允许您管理线程池，以便在应用程序中管理和重复使用线程。这对于需要执行多个任务的情况非常有用。

```python
import concurrent.futures

def my_function():
    # 执行任务的代码

with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
    future = executor.submit(my_function)
    # 更多任务提交和管理
```

**注意事项**：

- Python 中的全局解释器锁（Global Interpreter Lock，GIL）限制了同一时间只能执行一个线程中的 Python 代码。这意味着多线程在 CPU 密集型任务中可能无法充分利用多核处理器。但对于 I/O 密集型任务，多线程通常仍然有用。

- 线程在共享数据时可能会引发竞争条件和死锁等问题，因此在多线程编程中需要小心谨慎，使用适当的同步工具。

总之，`threading` 模块提供了方便的工具来创建、管理和同步线程，允许您实现并发性和并行性，但需要注意线程安全和共享资源的管理问题。对于更高级的并发任务，您还可以考虑使用 `multiprocessing` 模块，它允许您创建多个进程以利用多核处理器。

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