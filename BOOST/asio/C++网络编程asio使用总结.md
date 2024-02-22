## 简介

+ asio库使用总结 原文参考链接 : https://zhuanlan.zhihu.com/p/583533338

## 概述

+ Asio 是一个用于网络和低级 I/O 编程的跨平台 C++ 库，它使用现代 C++ 方法为开发人员提供一致的异步模型.

## io_context

+ io_context 类为异步I/O对象的用户提供了核心I/O功能，包含:
  + asio::ip::tcp::socket
  + asio::ip::tcp::acceptor
  + asio::ip::udp::socket
  + asio::deadline_timer 

### 线程安全

+ Boost.Asio 的线程安全模型。对于大多数 Boost.Asio 对象，在一个对象上挂起多个异步操作是安全的；只是指定对该对象的并发调用是不安全的。在下图中，每一列代表一个线程，每一行代表一个线程在某个时刻正在做什么。
+ 单个线程进行顺序调用而其他线程不进行调用是安全的：
```
thread_1 | thread_2
--------------------------------------+------------ ----------------------------
socket.async_receive(...); | ...
socket.async_write_some(...); | ...
```

+ 多个线程进行调用是安全的，但不能同时进行：
```
thread_1 | thread_2
--------------------------------------+------------ ----------------------------
socket.async_receive(...); | ...
... | socket.async_write_some(...);
```

+ 但是，多个线程并发调用是不安全的
```
thread_1 | thread_2
--------------------------------------+------------ ----------------------------
socket.async_receive(...); | socket.async_write_some(...);
... | ...
```

### 向io_context 提交任意任务

+ 要向 io_context 提交函数，请使用 asio::dispatch、asio::post 或 asio::defer 自由函数。
```cpp
void my_task()
{
    //...
}

int main()
{
    asio::io_context io_context;
    //提交一个函数
    asio::post(io_context, my_task);
    
    //提交一个lambda 表达式
    asio::post(io_context, [](){
        //...
    });

    //运行 io_context 直到它用完为止。
    io_context.run();
    return 0;
}
```

### 阻止 io_context 耗尽工作

+ 某些应用程序可能需要阻止 io_context 对象的 run() 调用在没有更多工作要做时返回。 例如，io_context 可能在应用程序的异步操作之前启动的后台线程中运行。 run() 调用可以通过创建一个针对 io_context 跟踪工作的执行器来保持运行：
```cpp
int main()
{
    asio::io_context io_context;
    auto work = asio::require(io_context.get_executor(), 
        asio::execution::outstanding_work.tracked);
    return 0;
}
```

+ 为了实现关闭，应用程序需要调用 io_context 对象的 stop() 成员函数。 这将导致 io_context run() 调用尽快返回，放弃未完成的操作并且不允许分派准备好的处理程序。
或者，如果应用程序要求允许所有操作和处理程序正常完成，请将工作跟踪执行程序存储在 any_io_executor 对象中，以便可以显式重置它。
```cpp
int main()
{
    asio::io_context io_context;
    asio::any_io_executor work = asio::require(io_context.get_executor(),
        asio::execution::outstanding_work.tracked);
    //...
    work = asio::any_io_executor();//允许 run() 退出
    return 0;
}
```

### io_context.run()

+ 当线程调用 io_context.run() 时，工作和处理程序将从该线程内调用。
```cpp
asio::io_context io_context;
asio::ip::tcp::socket socket(io_context);

io_context.post(&print);                             // 1
socket.connect(endpoint);                            // 2
socket.async_receive(buffer, &handle_async_receive); // 3
io_context.post(&print);                             // 4
io_context.run();                                    // 5
```
+ 在上面的示例中，io_context .run()(5) 将阻塞直到：
  + 它已从两个print处理程序调用并返回，接收操作成功或失败完成，并且其handle_async_receive处理程序已被调用并返回。
  + 通过 io_context 明确停止 io_context.stop()。
  + 从处理程序中抛出异常。
+ 请注意，当 io_context 工作用完时，应用程序必须 reset(), 在 io_context 再次运行之前。
+ run() 函数会阻塞，直到所有工作完成并且没有更多的处理程序要分派，或者直到 io_context 停止。
+ 示例：
```cpp
#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io_context;
    io_context.run();
    std::cout << "Do you reckon this line displays?" << std::endl;
    return 0;
}
//output: Do you reckon this line displays?
```

+ 如果我们的程序用完了怎么办？工作类是一个“在有工作要做时通知 io_context 的类"。换句话说，只要 io_context 有一个与之关联的工作对象，它就永远不会无事可做。
+ 示例：
```cpp
#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io_context;
    asio::io_context::work work(io_context);
    io_context.run();
    std::cout << "Do you reckon this line displays?" << std::endl;
    return 0;
}
//output: 
```

+ 如果我们不喜欢这种必须阻塞线程来工作的想法怎么办？我们将简单地模拟一个循环，调用io_context 的poll函数。poll 函数“运行 io_context 对象的事件处理循环来执行就绪的处理程序”
+ 示例：
```cpp
#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io_context;
    for(int x = 0; x < 42; ++x)
    {
        io_context.poll();
        std::cout << "Counter: " << x << std::endl;
    }
    return 0;
}
//output: 我们将看到 42 行文本输出到控制台，然后程序退出
```

+ 当我们运行这个程序时，我们得到与之前完全相同的输出和结果。这是因为当有更多工作要做时，轮询函数不会阻塞。它只是执行当前的一组工作然后返回。在一个真实的程序中，循环将基于一些其他事件，但为了简单起见，我们只使用一个固定的事件。
+ 示例：
```cpp
#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io_context;
    asio::io_context::work work(io_context);
    
    for(int x = 0; x < 42; ++x)
    {
        io_context.poll();
        std::cout << "Counter: " << x << std::endl;
    }
    return 0;
}
```

+ 如果我们想要从 io_context 中删除一个工作对象怎么办？为了实现此功能，我们必须改用指向工作对象的指针。与 boost 库保持一致，我们将使用shared_ptr，一个智能指针类。
```cpp
#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io_context;
    std::shared_ptr<asio::io_context::work> work(new asio::io_context::work(io_context));

    work.reset();

    io_context.run();

    std::cout << "Do you reckon this line displays?" << std::endl;
    return 0;
}
//如果我们运行该程序，我们将看到显示的文本行。这有效地向我们展示了如何从 io_service 中删除工作对象。
```

+ 现在我们知道如何用一个线程驱动 io_context ，我们需要弄清楚更多线程需要什么。io_context 文档页面告诉我们“多个线程可以调用 run() 函数来设置一个线程池，io_context 可以从中执行处理程序。池中等待的所有线程都是等效的，io_context 可以选择其中的任何一个他们调用处理程序。”

## Asio 多线程

+ 在多线程的场景下，每个线程都持有一个 io_context ，并且每个线程都调用各自的 io_context 的run()方法。
+ 全局只分配一个io_context ，并且让这个 io_context 在多个线程之间共享，每个线程都调用全局的 io_context 的run()方法

### 每个线程一个I/O Context

+ 特点：
  + 在多核的机器上，这种方案可以充分利用多个 CPU 核心。
  + 某个 socket 描述符并不会在多个线程之间共享，所以不需要引入同步机制
  + 在 event handler 中不能执行阻塞的操作，否则将会阻塞掉 io_context 所在的线程
+ 示例：
```cpp
#include <iostream>
#include <asio.hpp>
#include <vector>

class AsioIOContextPool
{
public:
    using IOContext = asio::io_context;
    using Work = asio::io_context::work;
    using WorkPtr = std::unique_ptr<Work>;

    //返回当前系统支持的并发线程数
    AsioIOContextPool(std::size_t size = std::thread::hardware_concurrency()) : 
        ioContexts_(size), 
        works_(size),
        nextIOContext_(0)
    {
        for(std::size_t i = 0; i < size; ++i)
        {
            works_[i] = std::unique_ptr<Work>(new Work(ioContexts_[i]));
        }

        for(std::size_t i = 0; i < ioContexts_.size(); ++i)
        {
            threads_.emplace_back([this, i](){
                ioContexts_[i].run();
            });
        }
    }

    AsioIOContextPool(const AsioIOContextPool&) = delete;
    AsioIOContextPool &operator=(const AsioIOContextPool&) = delete;

    asio::io_context& getIOContext()
    {
        auto &context = ioContexts_[nextIOContext_++];
        if(nextIOContext_ == ioContexts_.size())
        {
            nextIOContext_ = 0;
        }
        return context;
    }

    void stop()
    {
        for(auto &work : works_)
        {
            work.reset();
        }

        for(auto &t : threads_)
        {
            t.join();
        }
    }

private:
    std::vector<IOContext> ioContexts_;
    std::vector<WorkPtr> works_;
    std::vector<std::thread> threads_;
    std::size_t nextIOContext_;
};

int main()
{
    std::mutex mtx;
    AsioIOContextPool pool;
    asio::steady_timer timer{pool.getIOContext(), std::chrono::seconds{2}};
    timer.async_wait([&mtx](const asio::error_code &ec){
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Hello, World!" << std::endl;
    });

    pool.stop();
    return 0;
}
```

### 一个I/O Service与多个线程

+ 先分配一个全局 io_context，然后开启多个线程，每个线程都调用这个 io_context的run()方法。这样，当某个异步事件完成时，io_context 就会将相应的 event handler 交给任意一个线程去执行
+ 然而这种方案在实际使用中，需要注意一些问题：
  + 在 event handler 中允许执行阻塞的操作 (例如数据库查询操作)。
  + 线程数可以大于 CPU 核心数，譬如说，如果需要在 event handler 中执行阻塞的操作，为了提高程序的响应速度，这时就需要提高线程的数目
  + 由于多个线程同时运行事件循环(event loop)，所以会导致一个问题：即一个 socket 描述符可能会在多个线程之间共享，容易出现竞态条件 (race condition)。譬如说，如果某个 socket 的可读事件很快发生了两次，那么就会出现两个线程同时读同一个 socket 的问题 (可以使用strand解决这个问题)。

+ 无锁的同步方式：
  + Asio 提供了 io_context::strand：如果多个 event handler 通过同一个 strand 对象分发 (dispatch)，那么这些 event handler 就会保证顺序地执行。
+ 示例
```cpp
#include <iostream>
#include <asio.hpp>
#include <vector>

class AsioThreadPool
{
public:
    //返回当前系统支持的并发线程数
    AsioThreadPool(std::size_t size = std::thread::hardware_concurrency()) : 
        work_(new asio::io_context::work(io_context_))
    {
        for(std::size_t i = 0; i < size; ++i)
        {
            threads_.emplace_back([this](){
                io_context_.run();
            });
        }
    }

    AsioThreadPool(const AsioThreadPool&) = delete;
    AsioThreadPool &operator=(const AsioThreadPool&) = delete;

    asio::io_context& getIOContext()
    {
        return io_context_;
    }

    void stop()
    {
        work_.reset();

        for(auto &t : threads_)
        {
            t.join();
        }
    }

private:
    asio::io_context io_context_;
    std::unique_ptr<asio::io_context::work> work_;
    std::vector<std::thread> threads_;
};

int main()
{
    AsioThreadPool pool(4);    // 开启 4 个线程
    asio::steady_timer timer1{pool.getIOContext(), std::chrono::seconds{1}};
    asio::steady_timer timer2{pool.getIOContext(), std::chrono::seconds{1}};
    int value = 0;
    asio::io_context::strand strand{pool.getIOContext()};

    timer1.async_wait(strand.wrap([&value] (const asio::error_code &ec)
                              {
                                  std::cout << "Hello, World! " << value++ << std::endl;
                              }));
    timer2.async_wait(strand.wrap([&value] (const asio::error_code &ec)
                              {
                                  std::cout << "Hello, World! " << value++ << std::endl;
                              }));
    pool.stop();
    return 0;
}
```

## socket连接相关的函数

### socket 初始化

+ context 提供 I/O 执行程序的执行上下文，默认情况下，套接字将使用该执行程序为在套接字上执行的任何异步操作分派处理程序
```cpp
asio::io_context io_context;
asio::ip::tcp::socket socket(io_context);
```

### socket.open

+ open 此函数打开套接字，以便它将使用指定的协议。
```cpp
asio::io_context io_context;
asio::ip::tcp::socket socket(io_context);
socket.open(asio::ip::tcp::v4());
```

### socket.bind

+ 将套接字绑定到给定的本地端点
```cpp
asio::error_code ec;
socket.bind(asio::ip::tcp::endpoint(
        asio::ip::tcp::v4(), 12345), ec);
```

### socket.close

+ 该函数用于关闭套接字。任何异步发送、接收或连接操作都将立即取消，并以 asio::error::operation_aborted 错误完成
+ asio::system_error 失败时抛出。 请注意，即使函数指示错误，底层描述符也会关闭。
+ 对于与正常关闭已连接套接字相关的可移植行为，请在关闭套接字之前调用 shutdown()。
+ ec 设置以指示发生了什么错误（如果有）。请注意，即使函数指示错误，底层描述符也会关闭。
```cpp
asio::error_code ec;
socket.close(ec);
```

### socket.connect

+ 此函数用于将套接字连接到指定的远程端点。 函数调用将阻塞，直到连接成功或发生错误
+ 如果套接字尚未打开，它会自动打开。 如果连接失败，套接字自动打开，则套接字不会返回到关闭状态。
```cpp
asio::io_context io_context;
asio::ip::tcp::socket socket(io_context);
asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"), 12345);
socket.connect(endpoint, ec);
if(!ec){
    std::cout << "socket connect" << std::endl;
}
```

### socket.async_connect

+ 此函数用于将套接字异步连接到指定的远程端点。 函数调用总是立即返回
+ 如果套接字尚未打开，它会自动打开。 如果连接失败，套接字自动打开，则套接字不会返回到关闭状态
+ 无论异步操作是否立即完成，都不会从此函数中调用处理程序。 立即完成后，处理程序的调用将以等同于使用 asio::post() 的方式执行
```cpp
#include <iostream>
#include <asio.hpp>
#include <functional>

void connect_handler(const asio::error_code& ec)
{
    if(!ec)
    {
        std::cout << "Connect success" << std::endl;
    }
}

int main()
{
    asio::io_context io_context;
    asio::ip::tcp::socket socket(io_context);
    asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("180.222.102.202"), 80);
    socket.async_connect(endpoint, connect_handler);
    
    io_context.run();
    return 0;
}
```

### asio::connect

+ connect 函数是一个组合操作，它通过按顺序尝试每个端点来建立套接字连接
+ 此函数尝试将套接字连接到一系列端点之一。 它通过重复调用套接字的 connect 成员函数来完成此操作，对序列中的每个端点调用一次，直到成功建立连接
```cpp
int main()
{
    asio::io_context io_context;
    asio::ip::tcp::resolver r(io_context);
    asio::ip::tcp::resolver::query q("www.yahoo.com", "http");

    asio::ip::tcp::socket socket(io_context);
    asio::error_code ec;
    asio::connect(socket, r.resolve(q), ec);
    return 0;
}
```

+ 以下连接条件函数对象可用于输出有关各个连接尝试的信息：
```cpp
#include <iostream>
#include <asio.hpp>

struct my_connect_condition
{
    bool operator()(const asio::error_code& ec, const asio::ip::tcp::endpoint& next)
    {
        if(ec) std::cout << "Error: " << ec.message() << std::endl;
        std::cout << "Trying: " << next << std::endl;
        return true;
    }
};

int main()
{
    asio::io_context io_context;
    asio::ip::tcp::resolver r(io_context);
    asio::ip::tcp::resolver::query q("www.yahoo.com", "http");

    asio::ip::tcp::socket socket(io_context);
    asio::ip::tcp::endpoint e = asio::connect(socket, r.resolve(q), my_connect_condition());
    std::cout << "Connected to: " << e << std::endl;
    return 0;
}
//output:
//Trying: 180.222.102.201:80
//Connected to: 180.222.102.201:80
```

+ 或者:
```cpp
#include <iostream>
#include <asio.hpp>

//在每次连接尝试之前调用的函数对象。 函数对象的签名必须是：
struct my_connect_condition
{
    //ec 参数包含最近连接操作的结果。 在第一次连接尝试之前，ec 总是设置为指示成功。 
    //next 参数是要尝试的下一个端点。 如果应尝试下一个端点，则函数对象应返回 true，如果应跳过，则返回 false。
    bool operator()(const asio::error_code& ec, const asio::ip::tcp::endpoint& next)
    {
        if(ec) std::cout << "Error: " << ec.message() << std::endl;
        std::cout << "Trying: " << next << std::endl;
        return true;
    }
};  

int main()
{
    asio::io_context io_context;
    asio::ip::tcp::resolver r(io_context);
    asio::ip::tcp::resolver::query q("www.yahoo.com", "http");

    asio::ip::tcp::resolver::results_type e = r.resolve(q);
    asio::ip::tcp::socket socket(io_context);
    asio::error_code ec;
    asio::ip::tcp::resolver::results_type::iterator i = 
        asio::connect(socket, e.begin(), e.end(), my_connect_condition(), ec);
    if(ec)
    {
        //发生错误
    }
    else
    {
        std::cout << "Connected to: " << i->endpoint() << std::endl;
    }
    return 0;
}
```

### asio::async_connect

+ async_connect 函数是一个组合的异步操作，它通过按顺序尝试每个端点来建立套接字连接。
+ 此函数尝试将套接字连接到一系列端点之一。 它通过重复调用套接字的 async_connect 成员函数来完成此操作，对序列中的每个端点调用一次，直到成功建立连接
```cpp
//socket: 要连接的套接字。 如果套接字已经打开，它将被关闭。
//endpoints: 一系列端点。
//connect_handler: 连接操作完成时要调用的处理程序。
asio::async_connect(socket, results, connect_handler);
```
+ 示例:
```cpp
#include <iostream>
#include <asio.hpp>
#include <functional>

class client
{
public:
    client(asio::io_context& io_context) : resolver_(io_context), socket_(io_context)
    {

    }

    void Connect();
    void handle_read_header(const asio::error_code& ec, asio::ip::tcp::resolver::results_type results);
    void connect_handler(const asio::error_code& ec, const asio::ip::tcp::endpoint& endpoint);
private:
    asio::ip::tcp::resolver resolver_;
    asio::ip::tcp::socket socket_;
};

void client::Connect()
{
    // resolver_.async_resolve("www.yahoo.com", "http", std::bind(&client::handle_read_header, this,
    //                               std::placeholders::_1,
    //                               std::placeholders::_2));

    //如果不传入this Error: error C4573: “client::socket_”的用法要求编译器捕获“this”，但当前默认捕获模式不允许使用“this”
    resolver_.async_resolve("www.yahoo.com", "http", [this](const asio::error_code& ec, asio::ip::tcp::resolver::results_type results){
        if(!ec)
        {
            asio::async_connect(socket_, results, [](const asio::error_code& ec, const asio::ip::tcp::endpoint& endpoint){
                if(!ec)
                {
                    std::cout << "ok" << std::endl;
                }
            });
        }
    });
}

void client::handle_read_header(const asio::error_code& ec, asio::ip::tcp::resolver::results_type results)
{
    if(!ec)
    {
        asio::async_connect(socket_, results, std::bind(&client::connect_handler, this,
                                  std::placeholders::_1,
                                  std::placeholders::_2));
    }
}

void client::connect_handler(const asio::error_code& ec, const asio::ip::tcp::endpoint& endpoint)
{
    if(!ec)
    {
        std::cout << "ok" << std::endl;
    }
}

int main()
{
    asio::io_context io_context;
    client c(io_context);
    c.Connect();
    io_context.run();
    return 0;
}
```

### asio::ip::tcp::endpoint

+ 端点是使用某个端口连接到一个地址
+ 创建方法
```cpp
//(1) Default constructor
basic_endpoint() ASIO_NOEXCEPT : impl_() {}

//(2) 使用按主机字节顺序指定的端口号构造端点。IP地址将是任意地址（即INADDR_any或in6addr_any）。
//    此构造函数通常用于接受新连接。
basic_endpoint(const InternetProtocol& internet_protocol, unsigned short port_num) ASIO_NOEXCEPT
: impl_(internet_protocol.family(), port_num) {}

//(3) 使用端口号和IP地址构造端点。此构造函数可用于接受特定接口上的连接或建立到远程端点的连接。
basic_endpoint(const asio::ip::address& addr, unsigned short port_num) ASIO_NOEXCEPT : impl_(addr, port_num)
{}
```

+ 例如:
```cpp
asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 1234);
```

+ 如果想连接一台主机,例如 "http://www.yahoo.com"
```cpp
#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io_context;
    asio::ip::tcp::resolver resolver(io_context);
    asio::ip::tcp::resolver::query query("www.yahoo.com", "80");
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    asio::ip::tcp::endpoint ep = *iter;
    std::cout << ep.address().to_string() << std::endl;
    return 0;
}
//output: 180.222.102.202
```

### asio::ip::tcp::acceptor

+ 如果底层操作系统调用也是线程安全的，则同步接受操作是线程安全的。 这意味着允许对单个套接字对象执行同步接受操作的并发调用。 其他同步操作，如打开或关闭，不是线程安全的
+ 打开一个启用了 SO_REUSEADDR 选项的套接字接收器：
```cpp
#include <iostream>
#include <asio.hpp>
#include <functional>

int main()
{
    asio::io_context io_context;
    asio::ip::tcp::acceptor acceptor(io_context);
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 8888);
    //此函数打开套接字接受器，以便它使用指定的协议。
    acceptor.open(endpoint.protocol());
    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    //将接受器绑定到给定的本地端点。
    acceptor.bind(endpoint);
    asio::error_code ec;
    //max_listen_connections: 待处理连接队列的最大长度。
    //此函数将套接字接受器置于可以接受新连接的状态。
    acceptor.listen(asio::socket_base::max_listen_connections, ec);
    if(!ec)
    {
        std::cout << "listen success" << std::endl;
    }
    io_context.run();
   
    return 0;
}
```

+ asio::ip::tcp::acceptor::open()
  + 此函数打开套接字接受器，以便它使用指定的协议

+ asio::ip::tcp::acceptor::set_option()
  + 此函数用于在接受器上设置选项。
```cpp
acceptor.open(endpoint.protocol());
acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
```

+ asio::ip::tcp::acceptor::get_option()
  + 此函数用于获取接受器上选项的当前值。
```cpp
asio::ip::tcp::acceptor::reuse_address option;
acceptor.get_option(option);
bool is_set = option.get();
```

+ asio::ip::tcp::acceptor::bind()
  + 将接受器绑定到给定的本地端点。

+ asio::ip::tcp::acceptor::listen()
  + max_listen_connections: 待处理连接队列的最大长度
  + 此函数将套接字接受器置于可以接受新连接的状态

+ asio::ip::tcp::acceptor::close()
  + 此函数用于关闭接受器。 任何异步接受操作将立即取消
```cpp
asio::error_code ec;
acceptor.close(ec);
```

+ asio::ip::tcp::acceptor::cacel()
  + 此函数会导致所有未完成的异步连接、发送和接收操作立即完成，并且取消操作的处理程序将传递 asio::error::operation_aborted 错误

+ asio::ip::tcp::socket::io_control()
  + 该函数用于在接收器上执行 IO 控制命令。
  + 例如：获取准备读取的字节数：
```cpp
asio::ip::tcp::acceptor::non_blocking_io command(true);
socket.io_control(command);
```

+ asio::ip::tcp::acceptor::local_endpoint()
  + 此函数用于获取接受器的本地绑定端点
```cpp
asio::ip::tcp::endpoint endpoint = acceptor.local_endpoint();
```

+ asio::ip::tcp::acceptor::wait()
  + 此函数用于执行阻塞等待，以等待接受器进入准备好读、写或错误条件状态。
```cpp
acceptor.wait(asio::ip::tcp::acceptor::wait_read);
```

+ asio::ip::tcp::acceptor::async_wait()
  + 此函数用于执行异步等待接受器进入准备好读取、写入或错误条件状态。
```cpp
acceptor.async_wait(
    asio::ip::tcp::acceptor::wait_read,
    wait_handler);
```

+ asio::ip::tcp::acceptor::accept()
  + 此函数用于接受从对等点到给定套接字的新连接。 函数调用将阻塞，直到成功接受新连接或发生错误。
```cpp
asio::io_context io_context;
asio::ip::tcp::acceptor acceptor(io_context);
//...
asio::ip::tcp::socket socket(io_context);
acceptor.accept(socket);
```

+ asio::ip::tcp::acceptor::async_accept()
  + 此函数用于异步接受到套接字的新连接。 函数调用总是立即返回。
  + 接受新连接的套接字。 对等对象的所有权由调用者保留，调用者必须保证在调用处理程序之前它是有效的。
```cpp
asio::io_context io_context;
asio::ip::tcp::acceptor acceptor(io_context);
//...
asio::ip::tcp::socket socket(io_context);
acceptor.async_accept(socket, accept_handle);
```

+ asio::ip::tcp::socket::async_read_some()
  + 开始异步读取。
  + 此函数用于从流套接字中异步读取数据。
  + 函数调用总是立即返回。
  + buffers： 一个或多个缓冲区，数据将被读入其中。
  + 尽管可以根据需要复制缓冲区对象，但底层内存块的所有权由调用者保留，调用者必须保证它们在调用处理程序之前保持有效。
  + handler： 读取操作完成时要调用的处理程序。将根据需要制作处理程序的副本。的函数签名
  + 无论异步操作是否立即完成，都不会从此函数中调用处理程序。立即完成后，处理程序的调用将以等同于使用 asio::post() 的方式执行。
  + 读取操作可能无法读取所有请求的字节数。如果需要确保在异步操作完成之前读取请求的数据量，请考虑使用 async_read 函数。
  + 要读入单个数据缓冲区，请使用缓冲区函数，如下所示：
```cpp
socket.async_read_some(asio::buffer(data, size), handler);
```

+ asio::ip::tcp::socket::async_read()
  + async_read 函数是一个组合的异步操作，它在完成之前从流中读取一定数量的数据。
  + 启动异步操作以从流中读取一定数量的数据。
  + 此函数用于从流中异步读取一定数量字节的数据。函数调用总是立即返回。异步操作将继续，直到以下条件之一为真：
  + 此操作是根据对流的 async_read_some 函数的零次或多次调用来实现的，称为组合操作。程序必须确保流不执行其他读取操作（例如 async_read、流的 async_read_some 函数或任何其他执行读取的组合操作），直到此操作完成。
  + s： 要从中读取数据的流。该类型必须支持 AsyncReadStream 概念。
  + buffers： 一个或多个缓冲区，数据将被读入其中。缓冲区大小的总和表示要从流中读取的最大字节数。尽管可以根据需要复制缓冲区对象，但底层内存块的所有权由调用者保留，调用者必须保证它们在调用处理程序之前保持有效。
  + handler： 读取操作完成时要调用的处理程序。将根据需要制作处理程序的副本。的函数签名
  + 无论异步操作是否立即完成，都不会从此函数中调用处理程序。立即完成后，处理程序的调用将以等同于使用 asio::post() 的方式执行。
```cpp
asio::async_read(s, asio::buffer(data, size), handler);
```

+ async_read_some 和 async_read 的区别
  + asio::async_read 通常用户读取指定长度的数据，读完或出错才返回
  + socket.async_read_some读取到数据或出错就返回，不一定读完了整个包

+ asio::ip::tcp::socket::async_write_some()
  + 此函数用于将数据异步写入流套接字。函数调用总是立即返回。
  + buffers 一个或多个要写入套接字的数据缓冲区。
  + 尽管可以根据需要复制缓冲区对象，但底层内存块的所有权由调用者保留，调用者必须保证它们在调用处理程序之前保持有效。
  + handler 写入操作完成时要调用的处理程序。 将根据需要制作处理程序的副本。
  + 无论异步操作是否立即完成，都不会从此函数中调用处理程序。 立即完成后，处理程序的调用将以等同于使用 asio::post() 的方式执行。
  + 写操作可能不会将所有数据传输到对等方。
  + 如果需要确保在异步操作完成之前写入所有数据，请考虑使用 async_write 函数
```cpp
socket.async_write_some(asio::buffer(data, size), handler);
```

+ asio::async_write()
  + 此函数用于将一定数量的字节数据异步写入流。函数调用总是立即返回。异步操作将继续，直到以下条件之一为真：
  + 提供的缓冲区中的所有数据都已写入。也就是说，传输的字节数等于缓冲区大小的总和。
  + 此操作是根据对流的 async_write_some 函数的零次或多次调用来实现的，称为组合操作。程序必须确保流不执行其他写入操作（例如 async_write、流的 async_write_some 函数或任何其他执行写入的组合操作），直到此操作完成。
  + s 要写入数据的流。该类型必须支持 AsyncWriteStream 概念。
  + buffers 一个或多个包含要写入的数据的缓冲区。
  + 尽管可以根据需要复制缓冲区对象，但底层内存块的所有权由调用者保留，调用者必须保证它们在调用处理程序之前保持有效。
  + param handler 写入操作完成时要调用的处理程序。
  + 将根据需要制作处理程序的副本。
  + 无论异步操作是否立即完成，都不会从此函数中调用处理程序。立即完成后，处理程序的调用将以等同于使用 asio::post() 的方式执行
```cpp
asio::async_write(s, asio::buffer(data, size), handler);
```

## Buffer

+ asio在处理I/O操作时支持两种类型的buffer
  + asio::buffer
  + asio::streambuffer

### asio::buffer

+ asio::buffer 函数用于创建一个缓冲区对象来表示原始内存、POD 元素数组、POD 元素向量或 std::string
+ 缓冲区对象将连续的内存区域表示为由指针和字节大小组成的二元组。{void*, size_t} 形式的元组指定内存的可变（可修改）区域。 类似地，{const void*, size_t} 形式的元组指定一个常量（不可修改的）内存区域。 这两种形式分别对应类mutable_buffer和const_buffer。 为了反映 C++ 的转换规则，mutable_buffer 可以隐式转换为 const_buffer，并且不允许进行相反的转换
```cpp
sock.send(asio::buffer(data, size));
```
+ 在上面的例子中，asio::buffer 的返回值满足了ConstBufferSequence 概念的要求，可以直接传递给socket 的write 函数。 为可修改内存创建的缓冲区也符合 MutableBufferSequence 概念的要求
+ 可以从 POD 元素的内置数组、std::vector、std::array 或 boost::array 创建一个单独的缓冲区。 这有助于通过自动确定缓冲区的大小来防止缓冲区溢出
```cpp
char d1[128];
size_t bytes_transferred = sock.receive(asio::buffer(d1));

std::vector<char> d2(128);
bytes_transferred = sock.receive(asio::buffer(d2));

std::array<char, 128> d3;
bytes_transferred = sock.receive(asio::buffer(d3));
```
+ 在上述所有三种情况下，创建的缓冲区恰好为 128 字节长。 请注意，在创建或使用缓冲区时，向量永远不会自动调整大小。 缓冲区大小是使用向量的 size() 成员函数确定的，而不是其容量
+ 可以使用 data() 和 size() 成员函数访问缓冲区的内容：
```cpp
int main()
{
    //通过 std::string 构造 asio::buffer
    std::string str = "test";
    asio::const_buffer const_buffer = asio::buffer(str.data(), str.size());

    std::size_t s1 = const_buffer.size();
    const void* p1 = const_buffer.data();
    std::cout << "s1: " << s1 << " p1: " << p1 << std::endl;
    //output: s1: 4 p1: 000000D5A6B0F510
    
    //通过std::array构造asio::buffer
    std::array<char, 5> arrData = {'t', 'e', 's', 't', '\0'};
    asio::mutable_buffer mutable_buffer = asio::buffer(arrData.data(), arrData.size());
    std::size_t s2 = mutable_buffer.size();
    unsigned char* p2 = static_cast<unsigned char*>(mutable_buffer.data());
    std::cout << "s2: " << s2 << " p2: " << p2 << std::endl;
    //output: s2: 5 p2: test

    //通过std::vector构造asio::buffer
    std::vector<char> vecData = {'g', 'o', 'o', 'd', '\0'};
    asio::mutable_buffer v_buffer = asio::buffer(vecData.data(), vecData.size());

    std::size_t s3 = asio::buffer_size(v_buffer);
    const void* p3 = asio::buffer_cast<const void*>(v_buffer);
    std::cout << "s3: " << s3 << " p3: " << p3 << std::endl;
    //output: s3: 5 p3: 000001F890A53410

    return 0;
}
```

### asio::streambuf

+ 基于 std::streambuf 的可自动调整大小的缓冲区类
+ basic_streambuf 类派生自 std::streambuf 以将 streambuf 的输入和输出序列与一个或多个字符数组相关联。 这些字符数组在 basic_streambuf 对象内部，但提供了对数组元素的直接访问，以允许它们在 I/O 操作中有效使用。 写入 basic_streambuf 对象的输出序列的字符将附加到同一对象的输入序列

### asio::buffer 获取缓冲区大小并防止缓冲区溢出

+ Asio 使用 Buffer 类来表示缓冲区。这些类提供抽象并保护 Asio 操作免受缓冲区溢出。尽管将结果asio::buffer()传递给操作，但不会传输原数据，例如缓冲区的大小或其基础类型。此外，这些缓冲区不拥有内存，因此应用程序有责任确保底层内存在缓冲区抽象的整个生命周期内保持有效
+ 该 asio::buffer() 函数提供了一种创建缓冲区类的便捷方法，其中缓冲区的大小是从可能的类型中推导出来的。当 Asio 能够推导出缓冲区长度时，Asio 操作在使用结果缓冲区类型时不会引发缓冲区溢出。但是，如果应用程序代码将缓冲区的大小指定为 asio::buffer()，则应用程序有责任确保该大小不大于底层内存

+ 读取数据时，需要缓冲区。如果 Asio 不传输大小，那么根本问题就变成了如何知道要分配多少内存。这个问题有几个解决方案
  + 通过查询套接字有多少数据可用 socket::available()，然后相应地分配缓冲区
```cpp
std::vector<char> data(socket_.available());
asio::read(socket_, asio::buffer(data));
```
  + 使用Asio可用内存中增长的类，如 asio::streambuf。一些操作，比如asio::read()接受streambuf对象作为它们的缓冲区，并将根据操作的需要分配内存。但是应提供完成条件；否则操作将继续，直到缓冲区已满
```cpp
asio::streambuf data; 
asio::read(socket_, data, asio::transfer_at_least(socket_.avaliable()));
```

+ 在固定大小的协议中，数据生产者和消费者都使用相同大小的消息。由于读者知道消息的大小，读者可以预先分配一个缓冲区
+ 在可变长度协议中，消息通常分为两部分：头部和主体。标头通常是固定大小的，并且可以包含各种元信息，例如正文的长度。这允许读取器将标头读入固定大小的缓冲区，提取正文长度，为正文分配缓冲区，然后读取正文。
```cpp
// Read fixed header.
std::vector<char> data(fixed_header_size);
boost::asio::read(socket_, boost::asio::buffer(data));

protocol::header header(data);
network_to_local(header); // Handle endianess.

// Read body.
data.resize(header.body_length());
boost::asio::read(socket_, boost::asio::buffer(data));  

protocol::body body(data);
network_to_local(body); // Handle endianess.
```

### mutable_buffer

+ mutable_buffer 类提供了可以修改的缓冲区的安全表示。 它不拥有底层数据，因此复制或分配的成本很低
+ 示例:
```cpp
#include <array> // std::array
#include <functional> // std::bind
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <asio.hpp>

void noop(const std::string& str) {}

namespace protocol {
enum
{
  header_size = sizeof(std::size_t)
};
} // namespace protocol

std::vector<char> build_header(const std::string& body)
{
  std::vector<char> buffer(protocol::header_size);
  auto body_size = body.size();
  std::memcpy(&buffer[0], &body_size, sizeof body_size);
  return buffer;
}

std::size_t parse_header(const std::vector<char>& buffer)
{
  return *reinterpret_cast<const std::size_t*>(&buffer[0]);
}

int main()
{
  using asio::ip::tcp;

  // Create all I/O objects.
  asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 1234));
  tcp::socket socket1(io_context);
  tcp::socket socket2(io_context);
  
  // Connect the sockets.
  acceptor.async_accept(socket1, std::bind(&noop, "accept"));
  socket2.async_connect(acceptor.local_endpoint(), std::bind(&noop, "connect"));
  
  io_context.run();
  io_context.reset();

  //  Write a message from socket1 to socket2.
  std::string test_message = "this is a test message";
  {
    auto header = build_header(test_message);

    // Gather header and body into a single buffer.
    std::array<asio::const_buffer, 2> buffers = {{
      asio::buffer(header),
      asio::buffer(test_message)
    }};

    // Write header and body to socket.
    std::cout << socket1.is_open() << std::endl;
    asio::write(socket1, buffers);
  }

  // Read from socket2.
  {  
    std::vector<char> buffer;

    // Read header.
    buffer.resize(protocol::header_size);
    asio::read(socket2, asio::buffer(buffer));

    // Extract body size from header, resize buffer, then read body.
    auto body_size = parse_header(buffer);
    buffer.resize(body_size);
    asio::read(socket2, asio::buffer(buffer));

    // Verify body was read.
    assert(std::equal(begin(buffer), end(buffer), 
                      begin(test_message)));
    std::cout << "received: \n"
                 "  header: " << body_size << "\n"
                 "  body: ";
    std::cout.write(&buffer[0], buffer.size());
    std::cout << std::endl;

    return 0;
  }
}
```