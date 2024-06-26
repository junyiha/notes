---
category: C
date: 2024-05-22 09:00:00 +0800
layout: post
title: C_6_2_sys_socket_h
tag: CNetwork
---
## 简介

+ <sys/socket.h>头文件 笔记

## linux <sys/socket.h>是什么

`<sys/socket.h>` 是一个 C/C++ 语言中的头文件，通常用于在 Linux 系统上进行网络编程。该头文件包含了一系列用于创建、操作网络套接字（socket）的函数、结构体和宏定义。

套接字是网络通信的基础，它允许进程通过网络进行通信。`<sys/socket.h>` 中定义了创建套接字、绑定地址、监听连接、接受连接等操作所需的函数和相关的常量、数据结构。这些函数和常量允许开发者在 Linux 系统上编写网络应用程序，实现各种网络通信，如 TCP、UDP、IPv4、IPv6 等。

一些常用的函数包括 `socket()`（创建套接字）、`bind()`（绑定套接字地址）、`listen()`（监听连接）、`accept()`（接受连接请求）、`connect()`（建立连接）、`send()` 和 `recv()`（发送和接收数据）等。

这个头文件以及相关的系统调用和函数提供了程序员在 Linux 平台上进行网络编程的基础，使得开发者能够编写网络应用程序来实现数据通信和网络服务。

## linux <sys/socket.h>详解

`<sys/socket.h>` 是 Linux 系统中用于网络编程的头文件之一，它包含了一系列用于处理套接字（socket）的系统调用、结构体和宏定义。

套接字是一种抽象的通信端点，允许不同计算机之间进行数据通信。`<sys/socket.h>` 提供了创建、配置和操作套接字的函数和常量，使得开发者能够进行网络通信。以下是该头文件中常用的一些函数、数据结构和宏定义：

### 数据结构：

- `struct sockaddr`：用于表示通用的套接字地址信息。
- `struct sockaddr_in`：用于表示 IPv4 的套接字地址信息。
- `struct sockaddr_in6`：用于表示 IPv6 的套接字地址信息。
- `struct sockaddr_storage`：用于存储任意类型套接字地址的结构体。

### 函数：

- `socket()`：创建一个新的套接字，返回一个文件描述符。
- `bind()`：将一个套接字绑定到特定的地址和端口。
- `listen()`：开始监听传入的连接请求。
- `accept()`：接受传入的连接请求并返回新的套接字。
- `connect()`：建立与远程套接字的连接。
- `send()` 和 `recv()`：发送和接收数据。
- `close()`：关闭套接字连接。

### 常量和宏定义：

- 套接字类型：`SOCK_STREAM`（流套接字，提供面向连接的、可靠的字节流服务，如 TCP）、`SOCK_DGRAM`（数据报套接字，提供无连接的数据传输，如 UDP）等。
- 地址族：`AF_INET`（IPv4 地址族）、`AF_INET6`（IPv6 地址族）等。
- 套接字选项：如 `SO_REUSEADDR`（允许地址重用）、`SO_KEEPALIVE`（启用保活机制）等。

使用 `<sys/socket.h>` 中提供的函数和常量，开发者可以实现各种网络应用，包括客户端-服务器模型、网络通信、数据传输等。这些函数和常量为 Linux 下的网络编程提供了基础设施。

## linux <sys/socket.h> struct sockaddr详解

在 Linux 的 `<sys/socket.h>` 头文件中，`struct sockaddr` 是用于表示通用的套接字地址信息的结构体。它是一个通用的地址结构，用于在网络编程中传递和存储各种类型的套接字地址信息，无论是 IPv4、IPv6 还是其他协议族的地址信息。

`struct sockaddr` 的定义如下：

```c
struct sockaddr {
    unsigned short sa_family; // 地址族，例如 AF_INET、AF_INET6
    char sa_data[14];         // 实际的地址信息，大小取决于不同的协议族
};
```

这个结构体的主要成员有：

- `sa_family`：表示地址族（address family），用于指示地址的类型，例如 `AF_INET` 表示 IPv4 地址族，`AF_INET6` 表示 IPv6 地址族。这个字段的大小为 2 个字节（`unsigned short`）。
  
- `sa_data`：这是一个包含实际地址信息的字符数组，大小为 14 字节。在实际使用中，这个字段会被强制转换为不同类型的结构体，以便于存储特定地址族的信息。例如，对于 IPv4 地址族 (`AF_INET`)，会将 `struct sockaddr` 转换为 `struct sockaddr_in`，而对于 IPv6 地址族 (`AF_INET6`)，会转换为 `struct sockaddr_in6`。

由于 `struct sockaddr` 是一个通用的结构体，它通常与类型转换结合使用，以适应不同的地址族和套接字操作。例如，在使用时，你可能会使用类型转换来将 `struct sockaddr` 转换为 `struct sockaddr_in` 或 `struct sockaddr_in6`，这样就可以操作 IPv4 或 IPv6 地址信息。

网络编程中经常使用的函数，如 `bind()`、`connect()`、`accept()` 等，通常需要 `struct sockaddr` 类型的地址作为参数，以指定套接字的地址信息。在这些函数中，`struct sockaddr` 以及其不同的转换类型用于存储和传递相关的地址信息。

## linux <sys/socket.h> struct sockaddr_in详解

在 Linux 的 `<sys/socket.h>` 头文件中，`struct sockaddr_in` 是用于表示 IPv4 套接字地址信息的结构体。它是对通用的 `struct sockaddr` 结构的扩展，专门用于存储和处理 IPv4 地址信息。

`struct sockaddr_in` 的定义如下：

```c
struct sockaddr_in {
    sa_family_t sin_family; // 地址族，一般为 AF_INET
    in_port_t sin_port;     // 16 位端口号
    struct in_addr sin_addr; // IPv4 地址
    unsigned char sin_zero[sizeof(struct sockaddr) - sizeof(sa_family_t) - sizeof(in_port_t) - sizeof(struct in_addr)]; // 用于填充使结构体大小与 sockaddr 一致
};
```

这个结构体的主要成员包括：

- `sin_family`：与通用的 `struct sockaddr` 相同，表示地址族，通常设置为 `AF_INET` 表示 IPv4 地址族。

- `sin_port`：一个 16 位的整数，表示端口号。在网络编程中，端口号用于标识进程在主机上运行的服务。

- `sin_addr`：一个 `struct in_addr` 类型的结构体成员，用于存储 IPv4 地址信息。

- `sin_zero`：用于填充，使得 `struct sockaddr_in` 的大小与 `struct sockaddr` 保持一致。这样做是为了与旧版代码兼容，新的套接字地址结构体 `struct sockaddr_in` 虽然有自己的大小，但是要与通用的 `struct sockaddr` 大小一致以便于类型转换和处理。

在实际使用中，`struct sockaddr_in` 结构体通常与其他函数和数据类型一起使用，例如 `bind()`、`connect()` 和 `accept()` 等函数需要将 `struct sockaddr_in` 类型的地址信息作为参数传递。

这个结构体和相关的函数使得开发者可以在 Linux 系统上进行 IPv4 网络编程，并能够方便地处理 IPv4 地址和端口信息。

## linux <sys/socket.h> struct sockaddr_in6详解

在 Linux 的 `<sys/socket.h>` 头文件中，`struct sockaddr_in6` 是用于表示 IPv6 套接字地址信息的结构体。与 `struct sockaddr_in` 类似，`struct sockaddr_in6` 是对通用的 `struct sockaddr` 结构的扩展，专门用于存储和处理 IPv6 地址信息。

`struct sockaddr_in6` 的定义如下：

```c
struct sockaddr_in6 {
    sa_family_t sin6_family;   // 地址族，一般为 AF_INET6
    in_port_t sin6_port;       // 16 位端口号
    uint32_t sin6_flowinfo;    // 流标识和流级别
    struct in6_addr sin6_addr; // IPv6 地址
    uint32_t sin6_scope_id;    // 用于设置接口的标识符
};
```

这个结构体的主要成员包括：

- `sin6_family`：与通用的 `struct sockaddr` 相同，表示地址族，通常设置为 `AF_INET6` 表示 IPv6 地址族。

- `sin6_port`：一个 16 位的整数，表示端口号。在网络编程中，端口号用于标识进程在主机上运行的服务。

- `sin6_flowinfo`：用于指定数据包的流信息。

- `sin6_addr`：一个 `struct in6_addr` 类型的结构体成员，用于存储 IPv6 地址信息。

- `sin6_scope_id`：用于设置接口的标识符，以标识某个特定接口。

与 `struct sockaddr_in` 类似，`struct sockaddr_in6` 结构体也会用于与各种函数和数据类型一起使用，例如 `bind()`、`connect()` 和 `accept()` 等函数需要将 `struct sockaddr_in6` 类型的地址信息作为参数传递。

这个结构体和相关的函数使得开发者可以在 Linux 系统上进行 IPv6 网络编程，并能够方便地处理 IPv6 地址和端口信息。

## linux <sys/socket.h> struct sockaddr_storage详解

在 Linux 的 `<sys/socket.h>` 头文件中，`struct sockaddr_storage` 是一个通用的、足够大以容纳任何套接字地址结构的结构体。它被设计为一个泛型的套接字地址结构，可用于存储各种不同类型的套接字地址信息，包括 IPv4、IPv6 或其他协议族的地址信息。

`struct sockaddr_storage` 的定义如下：

```c
struct sockaddr_storage {
    sa_family_t ss_family;  // 地址族，用于指示地址的类型
    char __ss_pad1[_SS_PAD1SIZE]; // 结构体填充，确保内存对齐
    int64_t __ss_align; // 结构体对齐
    char __ss_pad2[_SS_PAD2SIZE]; // 结构体填充，确保内存对齐
};
```

其中，`_SS_PAD1SIZE` 和 `_SS_PAD2SIZE` 是为了内存对齐而填充的大小。

`struct sockaddr_storage` 结构体最主要的成员是 `ss_family`，用于指示实际地址结构的类型。根据 `ss_family` 的值，可以进行类型转换，将 `struct sockaddr_storage` 转换为相应的地址结构（例如 `struct sockaddr_in` 或 `struct sockaddr_in6`），以便于处理特定类型的套接字地址。

`struct sockaddr_storage` 通常用于网络编程中，当你需要处理不同类型的套接字地址时，可以将不同的地址类型都转换为 `struct sockaddr_storage`，以便于统一地进行存储和传递。

这个结构体的设计使得它成为一个通用的容器，可以存储不同类型的套接字地址，为网络编程提供了一定的灵活性和扩展性。

## linux <sys/socket.h> setsockopt()详解

`setsockopt()` 是 Linux 中 `<sys/socket.h>` 头文件中定义的函数，用于设置 socket 的选项参数。它允许对打开的 socket 进行配置和控制，以适应特定的网络通信需求。

### 函数原型

```c
#include <sys/socket.h>

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

- `sockfd` 是要设置选项的 socket 文件描述符。
- `level` 是选项的协议级别，通常是 `SOL_SOCKET`（表示通用 socket 选项），也可以是特定协议的级别，如 `IPPROTO_TCP` 或 `IPPROTO_IP`。
- `optname` 是要设置的选项名称。
- `optval` 是一个指向存放选项值的缓冲区的指针。
- `optlen` 是选项值的长度。

### 返回值

- 如果设置选项成功，返回值为 0。
- 如果失败，返回值为 -1，并设置 `errno` 表示错误的原因。

### 使用方法

```c
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置 socket 选项，例如设置 SO_REUSEADDR 选项
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // 进行其他操作

    close(sockfd); // 关闭 socket

    return 0;
}
```

### 作用

- `setsockopt()` 函数允许在创建 socket 后，通过设置选项对 socket 进行配置，如修改 socket 的属性、调整 socket 的行为等。
- 例如，可以通过设置 `SO_REUSEADDR` 选项来允许地址重用，允许多个 socket 绑定到相同的地址和端口。
- 还可以使用其他选项来调整缓冲区大小、设置超时、启用或禁用协议特性等。

总之，`setsockopt()` 是一个用于设置 socket 选项的函数，可以根据需要配置和控制 socket 的行为，以满足特定的网络通信需求。

## linux <sys/socket.h> socket详解

在 Linux 中，`<sys/socket.h>` 头文件提供了在网络编程中使用的套接字（socket）相关的函数和宏定义。其中最重要的函数之一就是 `socket()`。

`socket()` 函数用于创建一个新的套接字，并返回一个文件描述符，该文件描述符用于后续对该套接字的操作，比如发送和接收数据、连接等。

函数原型如下：

```c
int socket(int domain, int type, int protocol);
```

参数解释：
- `domain`：指定套接字的协议族（例如 `AF_INET` 表示 IPv4，`AF_INET6` 表示 IPv6 等）。
- `type`：指定套接字的类型（例如 `SOCK_STREAM` 表示流套接字，提供可靠的、面向连接的服务，如 TCP；`SOCK_DGRAM` 表示数据报套接字，提供无连接的服务，如 UDP）。
- `protocol`：指定协议，通常设置为 0，表示使用 `domain` 和 `type` 参数默认的协议。

示例用法：
```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}
// 对新创建的套接字进行后续操作，比如绑定地址、监听连接、接受连接等
```

通过 `socket()` 函数，你可以在 Linux 系统上创建不同类型的套接字，根据指定的协议族、类型和协议进行网络编程。接下来，可以使用返回的文件描述符对套接字进行各种操作，比如绑定地址、建立连接、发送和接收数据等。

## linux <sys/socket.h> bind()详解

在 Linux 的 `<sys/socket.h>` 头文件中，`bind()` 函数用于将一个套接字（socket）与一个特定的地址（IP 地址和端口号）绑定在一起。这个函数主要用于服务器端程序，在服务器启动时指定它所在的 IP 地址和端口号，以便客户端能够连接到该地址。

函数原型如下：

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

参数解释：
- `sockfd`：套接字文件描述符，通过 `socket()` 函数创建的套接字描述符。
- `addr`：指向 `struct sockaddr` 结构体的指针，包含要绑定的地址信息。
- `addrlen`：`addr` 结构体的长度。

示例用法：

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}

struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT); // 设置端口号
server_addr.sin_addr.s_addr = INADDR_ANY; // 将套接字绑定到任何可用的地址

int bind_status = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (bind_status < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
}
```

在上述示例中，`bind()` 函数将创建的套接字 `sockfd` 与 `struct sockaddr_in` 结构体中指定的 IP 地址和端口号绑定在一起。对于服务器程序，`bind()` 通常在 `socket()` 之后立即调用，以指定服务器将要监听的地址和端口。

绑定成功后，服务器可以使用该地址接收来自客户端的连接请求。如果绑定失败，`bind()` 将返回一个负值，并且可以通过 `perror()` 函数打印错误信息。

需要注意的是，在使用 `bind()` 函数之前，确保指定的端口号没有被其他进程占用，并且有足够的权限来绑定该地址。

## linux <sys/socket.h> listen()详解

在 Linux 的 `<sys/socket.h>` 头文件中，`listen()` 函数用于将指定的套接字（socket）转换为被动监听套接字，即将套接字用于接受连接请求，并指定服务器套接字可以排队等待的最大连接请求数量。

函数原型如下：

```c
int listen(int sockfd, int backlog);
```

参数解释：
- `sockfd`：套接字文件描述符，通过 `socket()` 函数创建的套接字描述符。
- `backlog`：指定等待连接队列的最大长度，即允许排队等待的最大连接请求数量。

示例用法：

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}

struct sockaddr_in server_addr;
// 填充 server_addr 结构体...

int bind_status = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (bind_status < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
}

int listen_status = listen(sockfd, 5); // 允许最多 5 个连接请求排队等待处理
if (listen_status < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
}
```

在上述示例中，`listen()` 函数将创建的套接字 `sockfd` 转换为一个被动监听套接字，允许最多 5 个连接请求排队等待处理。这表示如果有更多的连接请求到达服务器但尚未被处理，它们将被拒绝或者等待，直到服务器处理当前排队的连接请求。

`listen()` 函数通常在调用 `bind()` 函数之后，并且在调用 `accept()` 函数之前调用。当套接字处于监听状态时，服务器可以使用 `accept()` 函数接受连接请求并创建新的套接字用于与客户端通信。

## linux <sys/socket.h> accept()详解

在 Linux 的 `<sys/socket.h>` 头文件中，`accept()` 函数用于从被动监听套接字（listening socket）接受客户端的连接请求，创建一个新的连接套接字，并返回一个新的文件描述符，通过该文件描述符可以与客户端进行通信。

函数原型如下：

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

参数解释：
- `sockfd`：被监听的套接字文件描述符，通过 `socket()` 函数创建并经过 `bind()` 和 `listen()` 的设置。
- `addr`：用于存储客户端地址信息的结构体指针，当成功建立连接时，此结构体将填充为客户端的地址信息。
- `addrlen`：`addr` 结构体的长度指针，接受的客户端地址信息的长度。

示例用法：

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}

struct sockaddr_in server_addr;
// 填充 server_addr 结构体...

int bind_status = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (bind_status < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
}

int listen_status = listen(sockfd, 5);
if (listen_status < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
}

struct sockaddr_in client_addr;
socklen_t client_addrlen = sizeof(client_addr);

int new_socket = accept(sockfd, (struct sockaddr *)&client_addr, &client_addrlen);
if (new_socket < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
}
```

在上述示例中，`accept()` 函数从被监听套接字 `sockfd` 中接受连接请求，并创建了一个新的套接字 `new_socket`，用于与客户端进行通信。同时，`accept()` 将填充 `client_addr` 结构体，包含客户端的地址信息。

`accept()` 函数在服务器端通常用于循环中，每次调用 `accept()` 都会接受一个新的连接请求，返回一个新的套接字用于与新客户端进行通信。这样服务器可以同时处理多个客户端的连接请求。

## linux <sys/socket.h> connect()详解

在 Linux 的 `<sys/socket.h>` 头文件中，`connect()` 函数用于建立与远程服务器的连接。它被用于客户端程序，用于向服务器发起连接请求。

函数原型如下：

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

参数解释：
- `sockfd`：客户端套接字文件描述符，通过 `socket()` 函数创建的套接字描述符。
- `addr`：指向 `struct sockaddr` 结构体的指针，包含要连接的目标地址信息。
- `addrlen`：`addr` 结构体的长度。

示例用法：

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}

struct sockaddr_in server_addr;
// 填充 server_addr 结构体...

int connect_status = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (connect_status < 0) {
    perror("connection failed");
    exit(EXIT_FAILURE);
}
```

在上述示例中，`connect()` 函数用于将客户端套接字 `sockfd` 连接到指定的服务器地址 `server_addr`。如果连接成功，`connect()` 函数返回 0，如果连接失败，它会返回 -1，并可以通过 `perror()` 函数输出错误信息。

`connect()` 在客户端通常用于发起连接，如果连接成功建立，客户端可以随后使用 `send()` 和 `recv()` 函数发送和接收数据。连接失败可能由多种原因引起，例如服务器不可达、连接超时等，因此在实际使用时，通常需要适当处理连接失败的情况。

## linux <sys/socket.h> send()详解

在 Linux 的 `<sys/socket.h>` 头文件中，`send()` 函数用于通过套接字发送数据到连接的另一端（对于面向连接的套接字，如 TCP 套接字）。这个函数通常用于客户端和服务器之间进行数据通信。

函数原型如下：

```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

参数解释：
- `sockfd`：套接字文件描述符，通过 `socket()` 函数创建的套接字描述符。
- `buf`：指向包含要发送数据的缓冲区的指针。
- `len`：要发送的数据的长度。
- `flags`：用于指定发送操作的附加选项，通常设置为 0。

返回值是发送的字节数。如果出现错误，返回 -1，并可以通过 `errno` 全局变量获取错误码。

示例用法：

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}

// 假设 buffer 已经包含了要发送的数据
char buffer[1024] = "Hello, server!";
int send_status = send(sockfd, buffer, strlen(buffer), 0);
if (send_status < 0) {
    perror("send failed");
    exit(EXIT_FAILURE);
}
```

在上述示例中，`send()` 函数用于将存储在 `buffer` 中的数据通过套接字 `sockfd` 发送给连接的另一端。如果发送成功，`send()` 函数返回发送的字节数，如果发送失败，它会返回 -1，并可以通过 `perror()` 函数输出错误信息。

`send()` 函数通常与 `recv()` 函数一起使用，在客户端和服务器之间进行双向数据传输。

## linux <sys/socket.h> recv()详解

在 Linux 的 `<sys/socket.h>` 头文件中，`recv()` 函数用于从套接字接收数据，即从连接的另一端（对于面向连接的套接字，如 TCP 套接字）接收数据。这个函数通常用于客户端和服务器之间进行数据通信。

函数原型如下：

```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

参数解释：
- `sockfd`：套接字文件描述符，通过 `socket()` 函数创建的套接字描述符。
- `buf`：指向存储接收数据的缓冲区的指针。
- `len`：缓冲区的长度，即要接收的数据的最大字节数。
- `flags`：用于指定接收操作的附加选项，通常设置为 0。

返回值是接收的字节数。如果出现错误，返回 -1，并可以通过 `errno` 全局变量获取错误码。

示例用法：

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}

char buffer[1024];
int recv_status = recv(sockfd, buffer, sizeof(buffer), 0);
if (recv_status < 0) {
    perror("receive failed");
    exit(EXIT_FAILURE);
} else if (recv_status == 0) {
    printf("Connection closed by peer\n");
} else {
    printf("Received data: %s\n", buffer);
}
```

在上述示例中，`recv()` 函数用于从套接字 `sockfd` 接收数据，并将接收到的数据存储在 `buffer` 缓冲区中。如果接收成功，`recv()` 函数返回接收到的字节数，如果接收失败，它会返回 -1，并可以通过 `perror()` 函数输出错误信息。

需要注意的是，`recv()` 函数在接收数据时会阻塞程序的执行，直到有数据可用或者发生错误。因此，通常在实际应用中，需要结合其他逻辑或者循环来处理接收数据的情况。

## linux <sys/socket.h> close()详解

在 Linux 的 `<sys/socket.h>` 头文件中，`close()` 函数用于关闭一个文件描述符，包括套接字描述符。在网络编程中，当不再需要使用一个套接字时，应该通过 `close()` 函数来关闭它，释放资源并结束与该套接字相关联的连接。

函数原型如下：

```c
int close(int sockfd);
```

参数 `sockfd` 是要关闭的套接字文件描述符。

示例用法：

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
}

// 其他操作，比如连接、数据传输等...

int close_status = close(sockfd);
if (close_status < 0) {
    perror("close failed");
    exit(EXIT_FAILURE);
}
```

在上述示例中，`close()` 函数被用于关闭之前通过 `socket()` 函数创建的套接字描述符 `sockfd`。如果关闭成功，`close()` 函数返回 0，如果关闭失败，它会返回 -1，并可以通过 `perror()` 函数输出错误信息。

在网络编程中，及时关闭不再使用的套接字是很重要的，这可以防止资源泄漏和不必要的资源占用。

## sys/socket.h

+ 套接字常量、类型和函数的声明。

### socket()

+ 简述：创建一个`type`类型，`domain`协议簇，`protocol`通信协议的socket，并返回一个文件描述符
+ 声明：`int socket(int domain, int type, int protocol);`
+ 参数：
  + `domain`  --  选择所用的协议族
    + `AF_INET`，代表IPv4
    + `AF_INET6`，代表IPv6
  + `type`    --  
    + `SOCK_STREAM`, 表示有序，可靠，双工，面向连接的字节流，通常由TCP实现
    + `SOCK_DGRAM`,  通过定长的，不可靠消息提供无连接通信，通常由UDP实现
  + `protocol` -- 指定特定的通信type使用的协议。
    + 在大多数实现中，每个type参数只能使用一种协议。
    + `SOCK_STREAM`,使用`IPPROTO_TCP`
    + `SOCK_DGRAM`, 使用`IPPROTO_UDP`
    + 如果参数为0，则默认设置为1
+ 返回值：
  + 成功  --  返回文件描述符
  + 失败  --  

### socketpair()

+ 简述：创建两个`type`类型，`domain`协议簇，`protocol`通信协议的，互相连接的socket，将文件描述符放在`fds[0]`和`fds[1]`
+ 声明：`int socketpair(int domain, int type, int protocol, int fds[2]);`
+ 参数：
  + `domain`  --  选择所用的协议族
    + `AF_INET`，代表IPv4
    + `AF_INET6`，代表IPv6
  + `type`    --  
    + `SOCK_STREAM`, 表示有序，可靠，双工，面向连接的字节流，通常由TCP实现
    + `SOCK_DGRAM`,  通过定长的，不可靠消息提供无连接通信，通常由UDP实现
  + `protocol` -- 指定特定的通信type使用的协议。
    + 在大多数实现中，每个type参数只能使用一种协议。
    + `SOCK_STREAM`,使用`IPPROTO_TCP`
    + `SOCK_DGRAM`, 使用`IPPROTO_UDP`
    + 如果参数为0，则默认设置为1
  + `fds[2]`  --  存放两个文件描述符的数组  --  Input/Output
+ 返回值：
  + 成功  --  返回0
  + 失败  --  返回-1

### bind()

+ 简述：将套接字通信端点的句柄(`socket FD`)与一个特定的逻辑网络连接关联起来
+ 声明：`int bind(int fd, const struct sockaddr *address, socklen_t address_len);`
+ 参数：
  + `fd`       --  通信端点的文件描述符
  + `address`  --  关联的地址
  + `len`      --  地址字节长度(the local address which is LEN bytes long)
+ 返回值：
  + 成功  --  返回0
  + 失败  --  返回-1，并设置errno

### getsockname()

+ 简述：通过本地文件描述符的地址和长度(单位:byte)，获取socket名字
+ 声明：`int getsockname(int fd, const struct sockaddr *address, socklent *len);`
+ 参数：
  + `fd`  --  文件描述符
  + `address`  --  地址
  + `len`      --  长度
+ 返回值：
  + 成功  -- 
  + 失败  --  

### connect()

+ 简述：创建一个socket文件描述符和地址的连接
+ 声明：`int connect(int fd, const struct sockaddr *addr, socklent_t len);`
+ 参数：
  + `fd`  --  文件描述符
  + `addr` --  要连接的地址
  + `len`  --  地址的长度(单位：字节)
+ 返回值：  
  + 成功  --  返回0
  + 失败  --  返回-1

### send()

+ 简述：发送N字节的BUF到socket FD。返回发送的数字或-1。
+ 声明：`ssize_t send (int fd, const void *buf, size_t n, int flags);`
+ 参数：
+ 返回值：

### recv()

+ 简述：从socket FD中读取N个字节，并输入到BUF中
+ 声明：`ssize_t recv(int fd, void *buf, size_t n, int flags);`
+ 参数：
  + `fd`  --  文件描述符
  + `buf` --  要存放的缓冲区
  + `n`   --  读取的数据大小
  + `flags` --  
+ 返回值：
  + 成功  --  返回读取的字节数
  + 失败  --  返回-1

### sendto()

+ 简述：在socket FD上向地址ADDR(长度为ADDR_LEN)发送N个字节的BUF
+ 声明：
  + `ssize_t sendto(int fd, const void *buf, size_t n, int flags, const struct *addr, socklen_t addr_len);`
+ 参数：
+ 返回值：
  + 成功  --  返回发送的字节数
  + 失败  --  返回-1

### recvfrom()

+ 简述：通过socket FD读取N个字节到BUF
+ 声明：`ssize_t recvfrom(int fd, void *buf, size_t n, int flags, const struct *addr, socklen_t addr_len);`
+ 参数：
+ 返回值：
  + 成功  --  返回读取的字节数
  + 失败  --  返回-1
+ 注意：
  + 如果ADDR不为空，将其`*ADDR_LEN`字节填充为发送方的地址，并将地址的实际大小存储在`*ADDR_LEN`中。返回读取的字节数或-1错误

### sendmsg()

+ 简述：在socket FD上发送一个由MESSAGE描述的信息
+ 声明：`ssize_t sendmsg(int fd, const struct msghdr *message, int flags);`
+ 参数：
+ 返回值：
  + 成功  --  返回发送的字节数
  + 失败  --  返回-1

### recvmsg()

+ 简述：从socket FD接收一个由MESSAGE描述的信息
+ 声明：`ssize_t recvmsg(int fd, struct msghdr *message, int flags);`
+ 参数：
+ 返回值：
  + 成功  --  返回接收到的字节数
  + 失败  --  返回-1

### getsockopt()

+ 简述：将套接字`FD`的选项`OPTNAME`在协议级别`level`上的当前值放入`OPTVAL` (`*OPTLEN`字节长)，并将`*OPTLEN`设置为该值的实际长度
+ 声明：`int getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlen);`
+ 返回值：
  + 成功  --  返回接收到的字节数
  + 失败  --  返回-1

### setsockopt()

+ 简述：设置套接字`FD`的选项`OPTNAME`在协议级别`level`为`*OPTVAL` (`OPTLEN`字节长)
+ 声明：`int setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);`
+ 返回值：
  + 成功  --  返回接收到的字节数
  + 失败  --  返回-1

### listen()

+ 简述：准备接受套接字FD上的连接。在进一步的请求被拒绝之前，将有N个连接请求排队
+ 声明：`int listen(int fd, int n);`
+ 返回值：
  + 成功  --  返回接收到的字节数
  + 失败  --  返回-1

### accept()

+ 简述：在套接字FD上等待连接.
  + 当连接到达时，打开一个新的套接字与之通信，将`*ADDR (*ADDR_LEN字节长)`设置为连接对等体的地址，将`*ADDR_LEN`设置为地址的实际长度，
  + 并返回新套接字的描述符，错误则返回-1
+ 声明：`int accept(int fd, const struct sockaddr *addr, socklen_t *addr_len);`
+ 返回值：
  + 成功  --  新套接字的描述符
  + 失败  --  返回-1

### shutdown()

+ 简述：关闭套接字FD上打开的全部或部分连接
+ 声明：`int shutdown(int fd, int how);`
+ 参数：
  + `fd`  --  套接字文件描述符
  + `how`  --
    + `SHUT_RD`  --  不再接收连接
    + `SHUT_WR`  --  不再传输数据
    + `SHUT_RDWR`  --  不再传输数据和接收连接
+ 返回值：
  + 成功  --  返回0
  + 失败  --  返回-1