## 1.1 概述

+ 使用方式
  + 添加`mongoose.h`和`mongoose.c`文件

+ 两个基本数据结构
  + `struct mg_mgr`  --  持有所有运行连接的事件管理
  + `struct mg_connection`  --  单个连接描述符。换言之，每个连接都通过结构mg_connection结构来描述

+ 事件处理，每一个连接有两个事件处理函数：`c->fn`和`c->pfn`
  + `c->fn`，是由用户自定义的事件处理函数
  + `c->pfn`，是一个特定于协议的处理程序函数，被隐式设置。例如，`mg_http_listen()`将`c->pfn`设置为mongoose的HTTP事件处理程序。
+ 在特定于用户的处理程序之前调用特定于协议的处理程序。它解析传入数据，并可能调用特定于协议的事件，例如`MG_EV_HTTP_MSG`

+ 注意：
  + 由于Mongoose的核心不受并发访问的保护，因此请确保从同一线程或RTOS任务调用所有`mg_*` API函数

+ 发送和接收缓冲区，每一个连接有一个发送和接收缓冲区：`struct mg_connection::send`, `struct mg_connection::recv`
  + `struct mg_connection::send` : 将发送到对端的数据
  + `struct mg_connection::recv` : 从对端接收的数据
+ 当数据到达时，mongoose将接收到的数据追加到`recv`并触发一个`MG_EV_READ`事件。
+ 用户可以通过调用输出函数之一来发送数据，例如`mg_send()`，`mg_printf()`或类似于`mg_ws_send()`的协议特定函数。
+ 输出函数将数据追加到`send`缓冲区。当mongoose成功将数据写入套接字中时，它会将数据从结构体`mg_connection::send`中丢掉并且发送一个`MG_EV_WRITE`事件

+ 每个连接都有与之关联的事件处理函数，该功能必须由用户实现。事件处理函数是mongoose的关键要素，因为它定义了连接的行为
+ 事件处理函数示例：
  ```
    // Event handler function defines connection's behavior
    static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
      if (ev == MG_EV_READ) {
        mg_send(c, c->recv.buf, c->recv.len);   // Implement echo server
        c->recv.len = 0;                        // Delete received data
      }
    }
  ``` 
+ 参数：
  + `struct mg_connection *c`  --  接收事件的连接
  + `int ev`                   --  在`mongoose.h`中定义的事件编号。例如，当数据到达入站连接时，`ev`将是`MG_EV_READ`
  + `void *ev_data`            --  指向特定于事件的数据，并且对不同事件具有不同的含义。
    + 例如，对于`MG_EV_READ`事件，`ev_data`是一个`int *`指向从远程对等方接收的字节数，并保存到`c->recv` IO缓冲区中。
    + `ev_data`的确切含义是**用来描述每一个事件**。
    + 特定于协议的事件通常将`ev_data`指向具有特定协议信息的结构
  + `void *fn_data`            --  连接的用户定义指针，这是用于应用程序特定数据的占位符。
    + 这个`fn_data`指针是在`*_listen()`或者`*_connect()`调用期间设置的，并将其存储在`c->fn_data`。
    + 监听连接将`c->fn_data`的值复制到新接受的连接，因此所有接受的连接最初共享相同的`fn_data`指针。
    + 通过设置`c->fn_data = new_value`，可以随时更新或替换任何连接的`fn_data`指针

+ `struct mg_connection`具有带有连接标志的设置。标志是二进制的：它们是0或者1。一些标志是由mongoose设置的，应用代码不能修改。例如，`is_udp`标志告诉应用连接是不是UDP。
+ 一些标志是应用代码可以修改的，它们是：`is_hexdumping`, `id_draining`, `is_closing`。
  + `id_draining`标志，如果用户设置了这个标志，就是告诉mongoose向对端发送剩余数据，当都发送完毕时，关掉这个连接
  + `is_closing`标志，如果用户设置了这个标志，就是立即关闭并释放连接，而不需要发送剩余数据
  + `is_hexdumping`标志，

+ 调试日志。要增加调试的详细性，调用`mg_log_set()` ： `mg_log_set(MG_LL_DEBUG); mg_mgr_init(&mgr);`
  + `MG_INFO()`, `MG_DEBUG()`日志宏默认情况下使用`putchar()`，即它们使用标准的C stdout流。这种方式在传统的操作系统环境正常工作。在嵌入式环境中，为了查看调试日志，可以使用两种方式：IO重定位和日志重定向
    + IO重定位可以通过嵌入式SDK实现

+ 如果您需要执行连接的任何初始化，请通过捕获`MG_EV_OPEN`事件进行操作。
+ 该事件是在连接被分配并添加到事件管理之后立即发送的，并在其他任何内容之前。
  ```
    static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_OPEN) {
      ... // Do your initialisation
    }
  ``` 

+ 如果您需要保留一些特定连接的数据，则有两个选择
  + 第一，使用`c->fn_data`指针。该指针作为最后一个参数传递给事件处理程序
    ```
      static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
        if (ev == MG_EV_OPEN) {
          c->fn_data = malloc(123);       // Change our fn_data
        } else if (ev == MG_EV_CLOSE) {
          free(fn_data);  // Don't forget to free!
        }
        ...
      }

      // Every accepted connection inherit NULL pointer as c->fn_data, but we change
      // it per-connection to something else
      mg_http_listen(&mgr, "http://localhost:1234", fn, NULL);
    ``` 
  + 第二，使用`c->label`缓冲区。该缓冲区可以容纳一些特定于连接的数据，而无需额外的内存分配
    ```
      static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
        if (ev == MG_EV_WS_OPEN) {
          c->label[0] = 'W'; // Established websocket connection, store something
          ...
    ``` 

+ 如果需要关闭连接，请在自己的事件处理函数中设置`c->is_draining = 1;`。它将告诉mongoose向对端发送剩余数据，当都发送完毕时，关掉这个连接
+ 如果需要立即关闭而不需要发送剩余数据，则设置`c->is_closing = 1;`

+ 使用`mg_http_reply()`函数创建HTTP响应报文。重要的是，这个函数能够正确设置`Content-Length`头。
+ 当然，也可以手动创建HTTP响应报文。例如，使用`mg_printf()`函数，但是请确定设置了`Content-Length`头
  + `mg_printf(c, "HTTP/1.1 200 OK\r\Content-Length: %d\r\n\r\n%s", 2, "hi");` 
+ 或者，使用块的传输编码：
  ```
    mg_printf(c, "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
    mg_http_printf_chunk(c, "%s", "foo");
    mg_http_printf_chunk(c, "%s", "bar");
    mg_http_printf_chunk(c, "");  // Don't forget the last empty chunk
  ``` 
+ 需要注意的是：如果不适用`mg_http_reply()`或者`mg_http_*_chunk()`，请确保在自己的活动处理程序完成写入响应报文时，确保设置`c->is_reply = 0;`

+ 默认情况下，IO缓冲区分配的大小`MG_IO_SIZE`是2048.将其更改为512可以减少每个连接的内存消耗

+ Mongoose有三种影响构建的构建常数（预处理器定义）：目标体系结构/操作系统，目标网络堆栈，可调参数。
+ 为了在构建时间设置选项，请使用-D选项编译器标志
  ```
    $ cc app.c mongoose.c                           # Use defaults!
    $ cc app.c mongoose.c -D MG_ENABLE_IPV6=1       # Build with IPv6 enabled
    $ cc app.c mongoose.c -D MG_ARCH=MG_ARCH_RTX    # Set architecture
    $ cc app.c mongoose.c -D MG_ENABLE_SSI=0 -D MG_IO_SIZE=8192  # Multiple options
  ```
+ 支持架构的列表在`Arch.H`标题文件中定义。通常，无需明确指定体系结构。在构建过程中猜到了架构，因此通常不需要设置 
+ 网络堆栈常数在下面列出。请注意，如果未指定网络堆栈，则假定目标体系结构支持标准BSD套接字API
+ 另一类的构建常量是在`src/config.h`中定义的，以及它们的默认值。这些是包含/排除某个功能或更改相关参数的调谐物。
+ `MG_IO_SIZE`常数还设置了最大的UDP消息大小，请参见`#/907`有关详细信息。如果应用程序使用大型UDP消息，请相应地增加`MG_IO_SIZE`限制。

+ 此步骤是可选的，仅当您打算使用自定义TCP/IP堆栈时才需要。为此，您应该：
  + 禁用BSD插座API：在Mongoose_custom.h中，添加`#define MG_ENABLE_SOCKET 0`

+ 添加几个内部API函数的实现，例如`mg_send()`, `mg_mgr_poll()`等等。要参考，请查看`test/mongoose_custom.c`和实验性的`src/mip.c`

## 重要API


### 1.1 数据结构

+ `struct mg_addr`
  ```
    struct mg_addr {
      uint16_t port;    // TCP or UDP port in network byte order
      uint32_t ip;      // IP address in network byte order
      uint8_t ip6[16];  // IPv6 address
      bool is_ip6;      // True when address is IPv6 address
    };
  ``` 
+ 该结构包含网络地址。它可以被认为`sockaddr`结构在Mongoose中的等价结构体

+ `struct mg_mgr`
  ```
    struct mg_mgr {
      struct mg_connection *conns;  // List of active connections  结构体数组
      struct mg_dns dns4;           // DNS for IPv4
      struct mg_dns dns6;           // DNS for IPv6
      int dnstimeout;               // DNS resolve timeout in milliseconds
      unsigned long nextid;         // Next connection ID
      void *userdata;               // Arbitrary user data pointer
    };
  ``` 
+ 它是一个事件管理结构体，能够保存一个正在活动的连接列表，以及一些维持管理的信息

+ `struct mg_connection`
  ```
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
+ 它是一个连接：可能是一个监听连接，或者是一个已接收连接，或者是一个出站连接

### 1.2 核心API调用

+ `mg_mgr_init()`
  + `void mg_mgr_init(struct mg_mgr *mgr);`
  + 初始化事件管理器结构体变量，它所做的工作：
    + 将活动连接的列表设置为null
    + 设置IPv4和IPv6的默认DNS服务器
    + 设置默认DNS查找超时
  + 参数
    + `mgr`  --  需要初始化的`mg_mgr`结构体指针
  + 返回值：无
  + 示例
    ```
      struct mg_mgr mgr;
      mg_mgr_init(&mgr);
    ``` 
+ `mg_mgr_poll()`
  + `void mg_mgr_poll(struct mg_mgr *mgr, int ms);`
  + 在所有连接中迭代，接受新的连接，发送和接收数据，关闭连接并调用事件处理程序的功能，以适用于各自事件。
  + 执行一次池迭代(poll iteration)。对在`mgr->conns`列表中的每一个连接进行如下操作
    + 查看是否有传入数据。如果有，将数据读入到`c->recv`缓冲区，并发出一个`MG_EV_READ`事件
    + 查看`c->send`缓冲区是否有数据。如果有，写入数据，并发送`MG_EV_WRITE`事件
    + 如果一个连接处于监听状态，或已接收一个进入的连接状态，发送一个`MG_EV_ACCEPT`事件
    + 发送`MG_EV_POLL`事件
  + 参数
    + `mgr`  --  使用的事件管理结构体
    + `ms`   --  超时时间，单位为毫秒
  + 返回值：无
  + 示例
    + `while (running == true) mg_mgr_poll(&mgr, 1000 /*1 second*/);`

+ `mg_mgr_free()`
  + `void mg_mgr_free(struct mg_mgr *mgr);`
  + 关闭所有连接，释放所有资源
  + 参数：
    + `mgr`  --  需要被清除的事件管理结构体
  + 返回值：无
  + 示例
    ```
      struct mg_mgr mgr;
      mg_mgr_init(&mgr);
      while (running == true) mg_mgr_poll(&mgr, 1000);   // Event loop
      mg_mgr_free(&mgr);
    ``` 

+ `mg_listen()`
  + `struct mg_connection *mg_listen(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data);`
  + 创建一个监听连接，并将这个连接追加到`mgr->conns`连接列表中
  + 参数：
    + `mgr`  --  使用的事件管理结构体
    + `url`  --  URL。指定监听的本地IP地址和端口，例如：`tcp://127.0.0.1:1234`或`udp://0.0.0.0:9000`
    + `fn`   --  事件处理函数
    + `fn_data`  --  一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中
  + 返回值：返回创建的连接 或 NULL作为错误
  + 示例
    + `struct mg_connection *c = mg_listen(&mgr, "tcp://127.0.0.1:8080", fn, NULL);`

+ `mg_connect()`
  + `struct mg_connection *mg_connect(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data);`
  + 创建一个出站连接，并将这个连接追加到`mgr->conns`队列中
  + 参数：
    + `mgr`  --  使用的事件管理结构体
    + `url`  --  URL，指定需要连接的远程IP地址和端口。例如：`http://a.com`
    + `fn`   --  一个事件处理函数
    + `fn_data`  --  一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中
  + 返回值：返回创建的连接 或 NULL作为错误
  + 注意：
    + 这个函数不会连接对端，它只会分配需要的资源和启动连接进程。
    + 一旦对端真正连接了，会将`MG_EV_CONNECT`事件发送到连接事件处理
  + 示例
    + `struct mg_connection *c = mg_connect(&mgr, "http://example.org", fn, NULL);`

+ `mg_send()`
  + `int mg_send(struct mg_connection *c, const void *data, size_t size);`
  + 将大小为`size`的数据追加到`c->send`缓冲区。返回追加的字节数
  + 注意：
    + 这个函数不会将数据推送到网络。它仅仅是将数据追加到输出缓冲区。
    + 只有当`mg_mgr_poll()`被调用时，才会将数据发送出去。
    + 如果`mg_send()`被多次调用，则输出缓冲区会增长
  + 参数：
    + `c`  --  一个连接指针
    + `data`  --  一个指向需要增加到输出缓冲区的数据指针
    + `size`  --  数据大小
  + 返回值：如果数据成功追加，则返回true；否则返回false
  + 示例
    + `mg_send(c, "hi", 2);  // Append string "hi" to the output buffer`

+ `mg_printf(), mg_vprintf()`
  + `int mg_printf(struct mg_connection *, const char *fmt, ...);`
  + `int mg_vprintf(struct mg_connection *, const char *fmt, va_list *ap);`
  + 与`mg_send()`相同，但是使用`printf()`语义格式化数据。返回追加到输出缓冲区的字节数。有关支持格式规范列表，参见`mg_snprintf`
  + 参数：
    + `c`  --  一个连接指针
    + `fmt`  --  `printf()`语义中的格式字符串
  + 返回值：返回追加到输出缓冲区的字节数
  + 示例
    + `mg_printf(c, "Hello, %s!", "world"); // Add "Hello, world!" to output buffer`

+ `mg_wrapfd()`
  + `struct mg_connection *mg_wrapfd(struct mg_mgr *mgr, int fd, mg_event_handler_t fn, void *fn_data);`
  + 将给定的文件描述符`fd`包装到连接中，然后将该连接添加到事件管理器中。这个`fd`文件描述符必须支持`send(), recv(), select()`系统调用，而且是非阻塞的。Mongoose将把它当做TCP套接字使用。`c->rem`和`c->loc`地址将会变为空的
  + 参数：
    + `fd`  --  需要包装的文件描述符
    + `mgr` --  一个事件管理结构体
    + `fn`  --  一个指向事件处理函数的指针
    + `ud`  --  一个用户数据指针。它将被当做`fn_data`参数传递给`fn`
  + 返回值：返回创建的连接 或者 NULL作为错误

+ `mg_mkpipe()`
  + `int mg_mkpipe(struct mg_mgr *mgr, mg_event_handler_t fn, void *fn_data, bool udp);`
  + 创建两个互相连接的套接字，用于线程间通信。其中一个套接字被包装到一个Mongoose连接，并被添加到事件管理结构体中。另一个套接字将会被返回，且它应该被传递给工作线程。当一个工作线程使用`send()`发送任何数据到这个套接字，都将唤醒`mgr`和`fn`事件处理函数接收一个`MG_EV_READ`事件。另外，`fn`向工作线程发送的任何数据，都被由工作线程使用`recv()`接收。
  + 参数：
    + `mgr`  --  一个事件管理结构体
    + `fn`   --  一个指向事件处理函数的指针
    + `fn_data`  --  一个指向用户数据的指针。它将会被当做`fn_data`参数传递给`fn`
    + `udp`  --  告知创建一个UDP，还是创建一个TCP socketpair
  + 返回值：成功，返回创建的套接字；失败，返回-1
  + 使用案例参见`examples/multi-threaded`

+ `mg_hello()`
  + `void mg_hello(const char *url);`
  + 便利功能，在给定的监听URL上启动一个简单的Web服务器。这个函数只有在接收到一个`/quit`请求才会返回。服务器处理以下URI
    + `/quit`  --  退出服务，且退出函数
    + `/debug` --  设置调试级别，作为POST负载，`{"level" : 3}`是有效的
    + 对其他所有的URI，都将返回一个`hi`作为响应
  + 参数：
    + `url`  --  一个监听的URL，例如：`http://0.0.0.0:8000`

### 1.3 HTTP API

+ `struct mg_http_header`
  + 声明：
    ```
      struct mg_http_header {
        struct mg_str name;   // Header name
        struct mg_str value;  // Header value
      };
    ``` 
  + 结构代表HTTP标头，像`Content-Type: text/html`。`Content-Type` 是一个 Header name，`text/html/`是一个 Header value

+ `struct mg_http_message`
  + 声明
    ```
      struct mg_http_message {
        struct mg_str method, uri, query, proto;             // Request/response line
        struct mg_http_header headers[MG_MAX_HTTP_HEADERS];  // Headers
        struct mg_str body;                                  // Body
        struct mg_str message;                               // Request line + headers + body
      };
    ``` 
  + 结构代表HTTP消息。

+ `mg_http_listen()`
  + `struct mg_connection *mg_http_listen(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data);`
  + 创建HTTP侦听器。
  + 参数：
    + `mgr`  --  一个事件管理结构体
    + `url`  --  一个URL，指定监听的本地IP地址和端口。例如：`http://0.0.0.0:8000`
    + `fn`   --  一个事件处理函数
    + `fn_data`  --  一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中
  + 返回值：返回一个指向创建的连接指针 或者 返回NULL表示错误
  + 示例
    ```
      struct mg_connection *c = mg_http_listen(&mgr, "0.0.0.0:8000", fn, arg);
      if (c == NULL) fatal_error("Cannot create listener");
    ``` 

+ `mg_http_connect()`
  + `struct mg_connection *mg_http_connect(struct mg_mgr *, const char *url, mg_event_handler_t fn, void *fn_data);`
  + 创建HTTP客户端连接。这个函数不能连接到对端，它仅仅分配需要的资源和启动连接进程。当对端真正连接好了，会向连接事件处理函数发送一个`MG_EV_CONNECT`事件
  + 参数：
    + `mgr`  --  事件管理结构体
    + `url`  --  URL，指定远程URL。例如:`http://google.com`
    + `fn`   --  事件处理函数
    + `fn_data`  --  一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中
  + 返回值： 返回一个指向创建的连接的指针 或者 返回NULL表示错误
  + 示例
    ```
      struct mg_connection *c = mg_http_connect(&mgr, "http://google.com", fn, NULL);
      if (c == NULL) fatal_error("Cannot create connection");
    ``` 

+ `mg_http_status()`
  + `int mg_http_status(const struct mg_http_message *hm);`
  + 获取HTTP响应的状态代码。
  + 参数：
    + `hm`  --  需要解析的HTTP响应
  + 返回值：返回状态码。例如：200表示成功

+ `mg_http_get_request_len()`
  + `int mg_http_get_request_len(const unsigned char *buf, size_t buf_len);`
  + 获取请求的长度。请求的长度是直到HTTP头结束的字节数

### 1.4 WebSocket API

+ `struct mg_ws_message`
  + 声明：
    ```
      struct mg_ws_message {
        struct mg_str data; // WebSocket message data
        uint8_t flags;      // WebSocket message flags
      };
    ``` 
  + 该结构代表Websocket消息。这个`flag`元素对应于`RFC 6455`第5.2节中所述的第一个字节。(`https://www.rfc-editor.org/rfc/rfc6455#section-5.2`)

+ WebSockete message type:
  + 要从传入消息中提取消息类型，在结构体`mg_ws_message`的`flag`元素中检查四个`LSBs`
  + 可能存在的WebSocket消息类型：
    ```
      #define WEBSOCKET_OP_CONTINUE 0
      #define WEBSOCKET_OP_TEXT 1
      #define WEBSOCKET_OP_BINARY 2
      #define WEBSOCKET_OP_CLOSE 8
      #define WEBSOCKET_OP_PING 9
      #define WEBSOCKET_OP_PONG 10
    ``` 
  + 示例：
    ```
      // Mongoose events handler
      void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
        if (ev == MG_EV_WS_MSG) {
          struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
          msgtype = wm->flags & 0x0F;
          if (msgtype == WEBSOCKET_OP_BINARY) {
            // This is a binary data message
          } else if (msgtype == WEBSOCKET_OP_TEXT) {
            // This is a text data message
          }
        }
      }
    ``` 
  + 当调用`mg_ws_send()`或`ms_ws_printf()`发送消息时，请使用`RFC 6455`第5.6节中所述的正确消息类型进行数据帧(`https://www.rfc-editor.org/rfc/rfc6455#section-5.6`)

+ `mg_ws_connect()`
  + `struct mg_connection *mg_ws_connect(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data, const char *fmt, ...);`
  + 创建客户端Websocket连接。这个函数不能连接到对端，它仅仅分配需要的资源和启动连接进程。当对端真正连接好了，会向连接事件处理函数发送一个`MG_EV_CONNECT`事件
  + 参数：
    + `mgr`  --  使用的事件管理结构体
    + `url`  --  指定的远程URL。例如：`http://google.com`
    + `fn`   --  一个事件处理函数
    + `fn_data`  --  一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中
  + 返回值：返回一个指向创建的连接； 返回NULL表示错误
  + 示例
    ```
      struct mg_connection *c = mg_ws_connect(&mgr, "ws://test_ws_server.com:1000",
                                              handler, NULL, "%s", "Sec-WebSocket-Protocol: echo\r\n");
      if(c == NULL) fatal("Cannot create connection");
    ``` 

+ `mg_ws_upgrade()`
  + `void mg_ws_upgrade(struct mg_connection *c, struct mg_http_message *, const char *fmt, ...);`
  + 升级给定HTTP连接到Websocket。`fmt`是一个类似于`printf()`格式的字符串，用于额外的HTTP标头，返回给Websocket握手的客户端。如果不需要额外的标头，将`fmt`设置为空。
  + 参数：
    + `c`    --  使用的连接
    + `hm`   --  HTTP消息
    + `fmt`  --  类似于`printf`的格式字符串，用于附加`HTTP`标头或为null
  + 返回值：无
  + 示例：
    ```
      // Mongoose events handler
      void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
        if (ev == MG_EV_HTTP_MSG) {
          struct mg_http_message *hm = (struct mg_http_message *) ev_data;
          mg_ws_upgrade(c, hm, NULL);  // Upgrade HTTP to WS
        }
      }
    ``` 

+ `mg_ws_send()`
  + `size_t mg_ws_send(struct mg_connection *c, const void *buf, size_t len, int op);`
  + 向WebSocket对端发送数据
  + 参数：
    + `c`  --  使用的连接
    + `buf`  --  需要发送的数据
    + `len`  --  需要发送的数据大小
    + `op`   --  WebSocket消息类型，参见WebSocket message type
  + 返回值：返回发送的字节数
  + 示例：
    ```
      // Mongoose events handler
      void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
        if (ev == MG_EV_WS_OPEN) {
          struct mg_http_message *hm = (struct mg_http_message *) ev_data;
          mg_ws_send(c, "opened", 6, WEBSOCKET_OP_BINARY);  // Send "opened" to web socket connection
        }
      }
    ``` 

+ `mg_ws_printf(), mg_ws_vprintf()`
  + `size_t mg_ws_printf(struct mg_connection *, int op, const char *fmt, ...);`
  + `size_t mg_ws_vprintf(struct mg_connection *, int op, const char *fmt, va_list *);`
  + 和`ms_ws_send()`相同，但是使用`printf()`语义格式化数据
  + 参数：
    + `c`   --  使用的连接
    + `op`  --  WebSocket消息类型，参见WebSocket message type
    + `fmt` --  使用`printf()`语义格式化的字符串
  + 返回值：返回发送的字节数
  + 示例
    + `mg_ws_printf(c, WEBSOCKET_OP_TEXT, "Hello, %s!", "world");`

+ `mg_ws_wrap()`
  + `size_t mg_ws_wrap(struct mg_connection *c, size_t len, int op)`
  + 将输出缓冲区中的数据转换为Websocket格式。有用然后通过WebSocket实施协议。具体示例参见`examples/mqtt-over-ws-client`
  + 参数：
    + `c`  --  使用的连接
    + `len`  --  转换的字节数
    + `op`   --  WebSocket消息类型
  + 返回值：返回连接结构体中输出缓冲区新的大小
  + 示例
    ```
      size_t len = c->send.len;         // Store output buffer len
      mg_mqtt_login(c, s_url, &opts);   // Write MQTT login message
      mg_ws_wrap(c, c->send.len - len, WEBSOCKET_OP_BINARY); // Wrap it into WS
    ``` 

### 1.5 JSON API

### 1.6 Utility API

### 1.7 URL API

### 1.8 Logging API
