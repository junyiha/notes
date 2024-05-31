---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_core
tag: Mongoose
---
## 简介

+ mongoose核心api笔记

## struct mg_addr

+ 简介：
  + 该结构包含网络地址。它可以被认为`sockaddr`结构在Mongoose中的等价结构体

+ 原型：
```c
struct mg_addr {
  uint16_t port;    // TCP or UDP port in network byte order
  uint32_t ip;      // IP address in network byte order
  uint8_t ip6[16];  // IPv6 address
  bool is_ip6;      // True when address is IPv6 address
};
```

## struct mg_mgr 

+ 简介：
  + 它是一个事件管理结构体，能够保存一个正在活动的连接列表，以及一些维持管理的信息

+ 原型
```c
struct mg_mgr {
  struct mg_connection *conns;  // List of active connections  结构体数组
  struct mg_dns dns4;           // DNS for IPv4
  struct mg_dns dns6;           // DNS for IPv6
  int dnstimeout;               // DNS resolve timeout in milliseconds
  unsigned long nextid;         // Next connection ID
  void *userdata;               // Arbitrary user data pointer
};
```

## struct mg_connection

+ 简介：
  + 它是一个连接：可能是一个监听连接，或者是一个已接收连接，或者是一个出站连接

+ 原型
```c
struct mg_connection {
  struct mg_connection *next;  // Linkage in struct mg_mgr :: connections
  struct mg_mgr *mgr;          // Our container
  struct mg_addr loc;          // Local address
  struct mg_addr rem;          // Remote address
  void *fd;                    // Connected socket, or LWIP data
  unsigned long id;            // Auto-incrementing unique connection ID
  struct mg_iobuf recv;        // Incoming data
  struct mg_iobuf send;        // Outgoing data
  mg_event_handler_t fn;       // User-specified event handler function
  void *fn_data;               // User-specified function parameter
  mg_event_handler_t pfn;      // Protocol-specific handler function
  void *pfn_data;              // Protocol-specific function parameter
  char label[50];              // Arbitrary label
  void *tls;                   // TLS specific data
  unsigned is_listening : 1;   // Listening connection
  unsigned is_client : 1;      // Outbound (client) connection
  unsigned is_accepted : 1;    // Accepted (server) connection
  unsigned is_resolving : 1;   // Non-blocking DNS resolve is in progress
  unsigned is_connecting : 1;  // Non-blocking connect is in progress
  unsigned is_tls : 1;         // TLS-enabled connection
  unsigned is_tls_hs : 1;      // TLS handshake is in progress
  unsigned is_udp : 1;         // UDP connection
  unsigned is_websocket : 1;   // WebSocket connection
  unsigned is_hexdumping : 1;  // Hexdump in/out traffic
  unsigned is_draining : 1;    // Send remaining data, then close and free
  unsigned is_closing : 1;     // Close and free the connection immediately
  unsigned is_full : 1;        // Stop reads, until cleared
  unsigned is_resp : 1;        // Response is still being generated
  unsigned is_readable : 1;    // Connection is ready to read
  unsigned is_writable : 1;    // Connection is ready to write
};
```

## mg_mgr_init 

+ 简介：
  + 初始化事件管理器结构体变量，它所做的工作：
    + 将活动连接的列表设置为null
    + 设置IPv4和IPv6的默认DNS服务器
    + 设置默认DNS查找超时

+ 原型：
```c
void mg_mgr_init(struct mg_mgr *mgr);
```

+ 参数：
  + mgr : 需要初始化的`mg_mgr`结构体指针

+ 返回值：
  + 无

+ 示例：
```c
struct mg_mgr mgr;
mg_mgr_init(&mgr);
```

## mg_mgr_poll

+ 简介：
  + 在所有连接中迭代，接受新的连接，发送和接收数据，关闭连接并调用事件处理程序的功能，以适用于各自事件。
  + 执行一次池迭代(poll iteration)。对在`mgr->conns`列表中的每一个连接进行如下操作
    + 查看是否有传入数据。如果有，将数据读入到`c->recv`缓冲区，并发出一个`MG_EV_READ`事件
    + 查看`c->send`缓冲区是否有数据。如果有，写入数据，并发送`MG_EV_WRITE`事件
    + 如果一个连接处于监听状态，或已接收一个进入的连接状态，发送一个`MG_EV_ACCEPT`事件
    + 发送`MG_EV_POLL`事件

+ 原型：
```c
void mg_mgr_poll(struct mg_mgr *mgr, int ms);
```

+ 参数：
  + mgr :  使用的事件管理结构体
  + ms : 超时时间，单位为毫秒

+ 返回值：
  + 无

+ 示例：
```c
while (running == true) mg_mgr_poll(&mgr, 1000 /*1 second*/);
```

## mg_mgr_free

+ 简介：
  + 关闭所有连接，释放所有资源

+ 原型：
```c
void mg_mgr_free(struct mg_mgr *mgr);
```

+ 参数：
  + mgr : 需要被清除的事件管理结构体

+ 返回值：
  + 无

+ 示例：
```c
struct mg_mgr mgr;
mg_mgr_init(&mgr);
while (running == true) mg_mgr_poll(&mgr, 1000);   // Event loop
mg_mgr_free(&mgr);
```

## mg_listen 

+ 简介：
  + 创建一个监听连接，并将这个连接追加到`mgr->conns`连接列表中

+ 原型：
```c
struct mg_connection *mg_listen(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data);
```

+ 参数：
  + mgr : 使用的事件管理结构体
  + url : URL。指定监听的本地IP地址和端口，例如：`tcp://127.0.0.1:1234`或`udp://0.0.0.0:9000`
  + fn :  事件处理函数
  + fn_data : 一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中

+ 返回值：
  + 成功，返回创建的连接 
  + 失败，返回NULL

+ 示例：
```c
struct mg_connection *c = mg_listen(&mgr, "tcp://127.0.0.1:8080", fn, NULL);
```

## mg_connect

+ 简介：
  + 创建一个出站连接，并将这个连接追加到`mgr->conns`队列中

+ 原型：
```c 
struct mg_connection *mg_connect(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data);
```

+ 参数
  + mgr : 使用的事件管理结构体
  + url : URL，指定需要连接的远程IP地址和端口。例如：`http://a.com`
  + fn : 一个事件处理函数
  + fn_data :  一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中

+ 返回值：
  + 成功，返回创建的连接 
  + 失败，返回NULL

+ 示例：
```c
struct mg_connection *c = mg_connect(&mgr, "http://example.org", fn, NULL);
```

## mg_send 

+ 简介：
  + 将大小为`size`的数据追加到`c->send`缓冲区。返回追加的字节数

+ 原型
```c
int mg_send(struct mg_connection *c, const void *data, size_t size);
```

+ 参数：
  + c : 一个连接指针
  + data : 一个指向需要增加到输出缓冲区的数据指针
  + size : 数据大小

+ 返回值：
  + 成功， true
  + 失败， false

+ 详解：
  + 这个函数不会将数据推送到网络。它仅仅是将数据追加到输出缓冲区。
  + 只有当`mg_mgr_poll()`被调用时，才会将数据发送出去。
  + 如果`mg_send()`被多次调用，则输出缓冲区会增长

+ 示例
```c
mg_send(c, "hi", 2);  // Append string "hi" to the output buffer
```

## mg_printf

+ 简介：
  + 与`mg_send()`相同，但是使用`printf()`语义格式化数据。返回追加到输出缓冲区的字节数。有关支持格式规范列表，参见`mg_snprintf`

+ 原型：
```c
int mg_printf(struct mg_connection *, const char *fmt, ...);
```

+ 参数：
  + c : 一个连接指针
  + fmt : `printf()`语义中的格式字符串

+ 返回值：
  + 返回追加到输出缓冲区的字节数

+ 示例：
```c 
mg_printf(c, "Hello, %s!", "world"); // Add "Hello, world!" to output buffer
```

## mg_wrapfd

+ 简介：
  + 将给定的文件描述符`fd`包装到连接中，然后将该连接添加到事件管理器中。这个`fd`文件描述符必须支持`send(), recv(), select()`系统调用，而且是非阻塞的。Mongoose将把它当做TCP套接字使用。`c->rem`和`c->loc`地址将会变为空的

+ 原型：
```c
struct mg_connection *mg_wrapfd(struct mg_mgr *mgr, int fd, mg_event_handler_t fn, void *fn_data);
```

+ 参数：
  + fd : 需要包装的文件描述符
  + mgr : 一个事件管理结构体
  + fn : 一个指向事件处理函数的指针
  + ud : 一个用户数据指针。它将被当做`fn_data`参数传递给`fn`

+ 返回值：
  + 成功，返回创建的连接
  + 失败，返回NULL

## mg_mkpipe

+ 简介：
  + 创建两个互相连接的套接字，用于线程间通信。其中一个套接字被包装到一个Mongoose连接，并被添加到事件管理结构体中。另一个套接字将会被返回，且它应该被传递给工作线程。当一个工作线程使用`send()`发送任何数据到这个套接字，都将唤醒`mgr`和`fn`事件处理函数接收一个`MG_EV_READ`事件。另外，`fn`向工作线程发送的任何数据，都被由工作线程使用`recv()`接收

+ 原型
```c
int mg_mkpipe(struct mg_mgr *mgr, mg_event_handler_t fn, void *fn_data, bool udp);
```

+ 参数：
  + mgr : 一个事件管理结构体
  + fn : 一个指向事件处理函数的指针
  + fn_data : 一个指向用户数据的指针。它将会被当做`fn_data`参数传递给`fn`
  + udp : 告知创建一个UDP，还是创建一个TCP socketpair

+ 返回值：
  + 成功，返回创建的套接字
  + 失败，返回-1

+ 示例：
  + 参考examples/multi-threaded

## mg_hello 

+ 简介：
  + 便利功能，在给定的监听URL上启动一个简单的Web服务器。这个函数只有在接收到一个`/quit`请求才会返回。服务器处理以下URI
    + `/quit`  --  退出服务，且退出函数
    + `/debug` --  设置调试级别，作为POST负载，`{"level" : 3}`是有效的
    + 对其他所有的URI，都将返回一个`hi`作为响应

+ 原型：
```c
void mg_hello(const char *url);
```

+ 参数：
  + url : 一个监听的URL，例如：`http://0.0.0.0:8000`

+ 返回值：
  + 无