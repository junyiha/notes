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

+ `mg_mgr_poll()`
  + 在所有连接中迭代，接受新的连接，发送和接收数据，关闭连接并调用事件处理程序的功能，以适用于各自事件。