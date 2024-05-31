---
category: Python
date: 2024-05-22 09:00:00 +0800
layout: post
title: python_5_03_tornado
tag: Python
---
## 简介

+ Tornado框架相关笔记

## Tornado是什么

+ Python3 Tornado是一个基于Python语言的异步网络框架，它可以用于编写高性能的Web服务器和Web应用程序。Tornado的主要特点是其非阻塞的I/O模型，使得它在处理大量并发连接时能够表现出色。它也被广泛用于实时Web服务、长连接应用和WebSocket等场景。

## python3 Tornado详解

Python的Tornado框架是一个强大的异步网络库，它专注于高性能和可伸缩性。下面是对Tornado的一些详细解释：

1. **异步IO**：Tornado采用了异步的I/O模型，使用非阻塞的事件循环来处理并发连接。这意味着它可以在不同的客户端连接之间快速切换，而不会阻塞整个进程。

2. **Web框架**：Tornado提供了一个简单而灵活的Web框架，可以用于构建Web应用程序。它包含了路由、请求处理器、模板引擎等功能，使得开发Web应用变得更加容易。

3. **异步HTTP客户端和服务器**：除了作为Web框架，Tornado还提供了异步的HTTP客户端和服务器，可以用于构建各种类型的网络应用，包括代理、爬虫等。

4. **WebSocket支持**：Tornado支持WebSocket协议，这使得它可以用于构建实时的Web应用，如聊天应用、实时数据展示等。

5. **协程支持**：Tornado支持使用Python的协程来编写异步代码，这使得编写异步程序更加简单和直观。

6. **性能优化**：Tornado在设计上注重性能和可伸缩性，它的事件循环机制和非阻塞IO可以有效地处理大量的并发连接，使得应用程序可以轻松地应对高负载的情况。

总的来说，Tornado是一个功能丰富且性能出色的异步网络库，适用于构建各种类型的网络应用。

## python3 Tornado安装

安装 Tornado 可以通过 pip 工具来完成。如果你已经安装了 Python3 和 pip，只需在命令行中运行以下命令：

```
pip install tornado
```

这会自动下载并安装 Tornado 及其依赖项。安装完成后，你就可以在 Python 中使用 Tornado 框架了。

## python3 Tornado 示例

以下是一个简单的Python 3 Tornado示例，演示了如何创建一个简单的Web服务器，监听端口并返回 "Hello, World!" 消息给客户端：

```python
import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Hello, World!")

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
    ])

if __name__ == "__main__":
    app = make_app()
    app.listen(8888)
    print("Server is running at http://localhost:8888")
    tornado.ioloop.IOLoop.current().start()
```

在这个示例中，我们首先导入了Tornado的必要模块。然后，我们定义了一个名为`MainHandler`的请求处理器类，它继承自`tornado.web.RequestHandler`。在`MainHandler`类中，我们定义了一个`get()`方法来处理HTTP GET请求，并使用`self.write()`方法向客户端返回 "Hello, World!" 消息。

接着，我们定义了一个`make_app()`函数来创建Tornado应用程序对象。在这个函数中，我们通过`tornado.web.Application`类来创建一个应用程序实例，并指定了一个URL路由映射，将"/"路径映射到`MainHandler`类。

最后，在`if __name__ == "__main__":`块中，我们创建了应用程序对象，并通过`app.listen()`方法指定了服务器监听的端口（在这里是8888）。然后，我们启动了Tornado的事件循环，使得服务器可以一直运行并监听来自客户端的HTTP请求。

你可以运行这个示例代码，然后在浏览器中访问"http://localhost:8888"，就会看到 "Hello, World!" 消息返回给你。