## 简介

+ zmq库中常用的函数

## C++ zmq::socket_t::set()函数 详解

在 ZeroMQ 的 C++ 绑定中，`zmq::socket_t::set()` 函数用于设置套接字选项。它允许你在运行时修改 ZeroMQ 套接字的行为，以满足特定的需求。这个函数的签名通常是这样的：

```cpp
template<typename T>
socket_t& set(zmq::sockopt::opt<T> option, const T& value);
```

其中，`option` 是一个枚举类型，表示要设置的选项，`value` 是相应选项的值。

下面是一些常用的套接字选项以及它们的用途：

1. **ZMQ_SUBSCRIBE/ZMQ_UNSUBSCRIBE**：用于设置订阅的消息过滤器。在订阅者套接字上调用 `set()` 函数并传递 `ZMQ_SUBSCRIBE` 选项可以指定要订阅的消息前缀，而 `ZMQ_UNSUBSCRIBE` 用于取消订阅。

2. **ZMQ_LINGER**：设置套接字关闭时等待未发送消息的时间。如果未设置，套接字在关闭时将立即丢弃未发送的消息。可以通过设置这个选项来等待一段时间，以确保消息被发送。

3. **ZMQ_SNDHWM/ZMQ_RCVHWM**：设置套接字的发送和接收高水位标记。当队列中的消息数量达到这个水位标记时，后续的发送操作将被阻塞（发送者）或丢弃（接收者）。

4. **ZMQ_SNDTIMEO/ZMQ_RCVTIMEO**：设置发送和接收操作的超时时间。当设置了这个选项后，发送和接收操作将在超时时间内等待，如果超时则返回错误。

5. **ZMQ_TCP_KEEPALIVE/ZMQ_TCP_KEEPALIVE_CNT/ZMQ_TCP_KEEPALIVE_IDLE/ZMQ_TCP_KEEPALIVE_INTVL**：用于设置 TCP 连接的保持活动参数。

6. **ZMQ_ROUTER_MANDATORY**：在 ROUTER 套接字上设置此选项，如果无法路由消息，则立即报告错误。

等等。

需要注意的是，不是所有的选项都适用于所有类型的套接字，而且某些选项的行为可能因 ZeroMQ 版本而异。因此，在使用 `set()` 函数设置选项时，建议参考 ZeroMQ 文档和版本说明以确保选项的行为符合预期。

## zmq::socket_t::set() 函数

+ 这个函数是zmq::socket_t的父类zmq::socket_base中的成员函数，其函数声明为
```cpp
// Set array socket option, e.g.
// `socket.set(zmq::sockopt::plain_username, "foo123")`
template<int Opt, int NullTerm>
void set(sockopt::array_option<Opt, NullTerm>, const char *buf)
{
    set_option(Opt, buf, std::strlen(buf));
}
```

+ 其中，第一个参数是一个枚举值，用来表示该连接的属性，其值如下
  + zmq::sockopt::subscribe
+ 第二个参数是字符串，用来标记该连接