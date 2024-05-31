---
category: BOOST
date: 2024-05-22 09:00:00 +0800
layout: post
title: message_generator
tag: boost.beast
---
## 简介

+ boost::beast::http::message_generator 类

## boost::beast::http::message_generator

`boost::beast::http::message_generator` 是 Boost.Beast 库中的一个类，用于生成 HTTP 消息（请求或响应）。这个类提供了一个方便的接口，使得创建符合 HTTP 规范的消息变得更加简单。

以下是对 `boost::beast::http::message_generator` 类的主要方面的简要说明：

1. **构造函数：**

   ```cpp
   template<bool isRequest, class Body, class Fields>
   explicit message_generator(message<isRequest, Body, Fields>& m);
   ```

   这个构造函数接受一个 `message` 对象引用，用于初始化 `message_generator`。

2. **成员函数：**

   - `begin()`：返回一个迭代器，指向消息的开始位置。
   - `end()`：返回一个迭代器，指向消息的结束位置。
   - `is_done()`：返回一个布尔值，表示消息是否已经生成完毕。

3. **使用场景：**

   - **简化 HTTP 消息的创建：** `message_generator` 提供了一个更高层次的接口，使得创建 HTTP 消息变得更加简单。你可以使用该类来构建 HTTP 请求或响应。

4. **示例：**

   ```cpp
   #include <boost/beast/core.hpp>
   #include <boost/beast/http.hpp>
   #include <iostream>

   namespace beast = boost::beast;
   namespace http = beast::http;

   int main() {
       // 创建 HTTP 请求消息
       http::request<http::string_body> req;
       req.method(http::verb::get);
       req.target("/");
       req.version(11);
       req.set(http::field::host, "www.example.com");

       // 使用 message_generator 生成 HTTP 请求消息
       http::message_generator<true, http::string_body, http::fields> reqGen(req);

       // 输出生成的 HTTP 请求消息
       std::cout << reqGen.begin() << std::endl;

       // 创建 HTTP 响应消息
       http::response<http::string_body> res;
       res.version(11);
       res.result(http::status::ok);
       res.set(http::field::server, "Boost.Beast");

       // 使用 message_generator 生成 HTTP 响应消息
       http::message_generator<false, http::string_body, http::fields> resGen(res);

       // 输出生成的 HTTP 响应消息
       std::cout << resGen.begin() << std::endl;

       return 0;
   }
   ```

   在这个示例中，首先创建了一个 HTTP 请求消息和一个 HTTP 响应消息，然后使用 `message_generator` 分别生成了这两个消息的字符串表示形式。

总的来说，`boost::beast::http::message_generator` 是一个用于生成 HTTP 消息的方便工具，简化了 HTTP 消息的创建过程。