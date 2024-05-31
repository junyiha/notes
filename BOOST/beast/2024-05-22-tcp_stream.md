---
category: BOOST
date: 2024-05-22 09:00:00 +0800
layout: post
title: tcp_stream
tag: boost.beast
---
## 简介

+ tcp_stream类

## boost::beast::tcp_stream 详解

`boost::beast::tcp_stream` 是 Boost.Beast 库中的一个类，用于简化基于 TCP 的异步通信。它提供了对底层 TCP 连接进行操作的功能，同时集成了 Boost.Asio 的异步操作模型。

以下是对 `boost::beast::tcp_stream` 的一些主要方面的简要说明：

1. **构造函数：** `tcp_stream` 的构造函数通常需要一个 `boost::asio::io_context` 对象，以便进行异步操作。可以通过构造函数或 `open()` 函数来设置底层的 `boost::asio::ip::tcp::socket`。

    ```cpp
    boost::asio::io_context io_context;
    boost::beast::tcp_stream stream(io_context);
    ```

2. **成员函数：**
   - `async_connect()`：用于异步发起连接。
   - `async_read()` 和 `async_write()`：用于异步读取和写入数据。
   - `expires_after()` 和 `expires_at()`：用于设置超时时间。
   - `close()`：用于关闭连接。

3. **使用示例：** 以下是一个简单的使用示例，演示了如何使用 `tcp_stream` 进行异步连接和数据传输：

    ```cpp
    #include <boost/beast/core.hpp>
    #include <boost/beast/ssl.hpp>
    #include <boost/beast/websocket.hpp>
    #include <boost/asio/connect.hpp>
    #include <boost/asio/ip/tcp.hpp>
    #include <iostream>

    namespace beast = boost::beast;
    namespace asio = boost::asio;
    namespace ssl = boost::asio::ssl;
    using tcp = boost::asio::ip::tcp;

    int main() {
        try {
            asio::io_context io_context;
            tcp::resolver resolver(io_context);
            tcp::socket socket(io_context);
            tcp::resolver::results_type results = resolver.resolve("www.example.com", "http");

            // 使用 tcp_stream 进行异步连接
            boost::beast::tcp_stream stream(socket);
            stream.expires_after(std::chrono::seconds(5));
            asio::async_connect(stream.next_layer(), results.begin(), results.end(), [&](boost::system::error_code ec, const tcp::endpoint&) {
                if (!ec) {
                    std::cout << "Connected to server" << std::endl;

                    // 异步写入数据
                    stream.async_write(asio::buffer("GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n"), [&](boost::system::error_code ec, std::size_t) {
                        if (!ec) {
                            std::cout << "Data sent successfully" << std::endl;

                            // 异步读取响应
                            boost::beast::flat_buffer buffer;
                            stream.async_read(buffer, [&](boost::system::error_code ec, std::size_t) {
                                if (!ec) {
                                    std::cout << "Received response:\n" << beast::make_printable(buffer.data()) << std::endl;
                                } else {
                                    std::cerr << "Error in async_read: " << ec.message() << std::endl;
                                }
                            });
                        } else {
                            std::cerr << "Error in async_write: " << ec.message() << std::endl;
                        }
                    });
                } else {
                    std::cerr << "Error in async_connect: " << ec.message() << std::endl;
                }
            });

            io_context.run();
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

        return 0;
    }
    ```

    请注意，此示例中的 `tcp_stream` 用于异步连接和数据传输。在实际应用中，可能需要根据需要进行更复杂的错误处理和数据处理。此外，上述示例中使用了 Boost.Beast 的 `flat_buffer` 用于存储读取的数据。