---
category: Windows
date: 2024-05-22 09:00:00 +0800
layout: post
title: windows_04_socket编程
---
## 简介

+ windows系统下socket网络编程笔记

## windows系统下socket编程

在 Windows 系统下进行 Socket 编程，你可以使用 Windows Sockets API（通常称为 Winsock）。Winsock 是用于在 Windows 上进行网络编程的 API，它提供了一套函数和数据结构，允许应用程序通过网络进行通信。

以下是一个简单的示例，展示了在 Windows 下使用 Winsock API 进行基本的套接字通信：

```c
#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int iResult;
    int clientAddrLen = sizeof(clientAddr);

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    // Create a TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        printf("Error creating socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Bind the socket to an address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Use any available IP address on the machine
    serverAddr.sin_port = htons(8080); // Use port 8080

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port 8080...\n");

    // Accept a client connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Client connected\n");

    // Communication with the client
    // ... (send/receive data)

    // Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
```

这个示例创建了一个简单的 TCP 服务器。它初始化 Winsock，创建一个 TCP 套接字（`socket()`），绑定到一个地址和端口（`bind()`），开始监听来自客户端的连接请求（`listen()`），接受一个客户端连接（`accept()`），并最终关闭套接字并清理 Winsock 资源。

请注意，这只是一个基本示例，实际的网络通信可能涉及到更多的错误处理、数据发送和接收等操作。此外，该示例仅支持单个客户端连接，实际应用可能需要支持多客户端并发连接，需要使用多线程或异步编程技术来实现。

## Winsock是什么

Winsock（Windows Sockets）是用于在 Microsoft Windows 操作系统上进行网络通信的编程接口。它是一组用于网络通信的 API，允许开发人员在 Windows 平台上创建网络应用程序，实现数据的传输、接收和处理。

Winsock 提供了一种类似于 Berkeley 套接字（BSD Sockets）接口的编程模型，它支持多种网络协议，例如 TCP（传输控制协议）和 UDP（用户数据报协议），允许应用程序通过这些协议进行网络通信。

使用 Winsock API，开发人员可以执行以下操作：

1. 创建和管理套接字（socket）：通过 `socket()` 函数创建套接字并设置其参数。
2. 绑定套接字到本地地址和端口：使用 `bind()` 函数将套接字绑定到特定的本地地址和端口。
3. 监听和接受连接：使用 `listen()` 函数开始监听传入的连接请求，并通过 `accept()` 函数接受客户端的连接。
4. 发送和接收数据：使用 `send()` 和 `recv()` 函数发送和接收数据。
5. 关闭套接字和清理资源：使用 `closesocket()` 关闭套接字，并在应用程序结束时使用 `WSACleanup()` 清理 Winsock 资源。

Winsock 在 Windows 平台上成为了标准的网络编程接口，并且提供了丰富的功能和灵活性，使得开发人员可以编写各种类型的网络应用程序，包括网络服务器、客户端、实时通信应用、网络游戏等。

需要注意的是，Winsock 并非 Windows 独有的 API，类似的套接字接口也存在于其他操作系统上，例如 BSD 系统（如 Linux 和 macOS）上的 BSD Sockets。然而，Winsock 是专门为 Windows 平台设计和优化的网络编程接口。

## Winsock详解

Winsock（Windows Sockets）是用于在 Microsoft Windows 操作系统上进行网络通信的编程接口。它提供了一系列函数、数据结构和定义，允许开发人员编写网络应用程序，实现数据的传输、接收和处理。

以下是 Winsock 的一些重要概念和功能：

1. **套接字（Socket）**：
   - 在 Winsock 中，套接字是网络通信的基本抽象，用于描述通信的端点。它允许应用程序通过网络进行数据传输。
   - 使用 `socket()` 函数创建套接字，并指定协议族（例如 AF_INET 用于 IPv4），类型（例如 SOCK_STREAM 用于流式套接字或 SOCK_DGRAM 用于数据报套接字），以及协议。
   - 套接字可以是面向连接的（如 TCP）或无连接的（如 UDP）。

2. **地址结构（Address Structures）**：
   - 在网络通信中，地址结构用于表示和存储网络地址信息，例如 IP 地址和端口号。
   - `struct sockaddr` 是 Winsock 中通用的地址结构，`struct sockaddr_in` 用于存储 IPv4 地址信息。

3. **地址解析和转换**：
   - 使用 `getaddrinfo()` 函数将主机名（例如 www.example.com）和服务/端口名（例如 HTTP 或 80）转换为可用于套接字操作的地址信息结构。

4. **绑定（Binding）**：
   - 使用 `bind()` 函数将套接字绑定到本地的 IP 地址和端口号，以便接受传入的连接或发送数据。

5. **监听和接受连接**：
   - `listen()` 函数用于开始监听传入的连接请求。
   - `accept()` 函数用于接受传入的连接，并创建新的套接字来处理该连接。

6. **发送和接收数据**：
   - 使用 `send()` 和 `recv()` 函数发送和接收数据。对于 TCP 套接字，这些函数用于在连接上进行数据传输；对于 UDP 套接字，它们用于发送和接收数据报。

7. **关闭套接字和清理资源**：
   - 使用 `closesocket()` 函数关闭套接字，并使用 `WSACleanup()` 函数在应用程序结束时释放 Winsock 资源。

8. **异步通信**：
   - Winsock 还支持异步操作，允许应用程序同时处理多个套接字的通信，通过使用事件或 I/O 完成端口（IOCP）等机制实现异步通信。

9. **错误处理和状态查询**：
   - 使用 `WSAGetLastError()` 函数获取最近一次发生的套接字相关错误。
   - `WSAStartup()` 函数用于初始化 Winsock 库，返回值表示初始化是否成功。
   - `WSAIsBlocking()` 函数用于查询套接字是否处于阻塞模式。

总的来说，Winsock 提供了强大且灵活的功能，允许开发人员构建各种网络应用程序，包括客户端和服务器，支持 TCP 和 UDP 等协议，以及实现复杂的网络通信需求。要使用 Winsock 编写网络应用程序，你需要了解套接字的基本概念和相关函数的使用方法，以便正确地建立、管理和处理网络连接。

## WSAPoll() 是什么 详细解释

`WSAPoll()` 是 Windows Sockets API （Winsock）中的一个函数，用于在 Windows 平台上进行异步套接字状态检查。它类似于类Unix系统上的`poll()`函数，在多路复用（Multiplexing）的情况下，用于轮询一组套接字以检查它们的就绪状态，例如是否可以读取、写入或出错等。

该函数的作用是检查套接字集合中指定套接字的状态，可以同时检查多个套接字。通过`WSAPoll()`函数，你可以非阻塞地等待多个套接字之一准备就绪，而不需要为每个套接字创建一个单独的线程或使用其他复杂的同步机制。

以下是 `WSAPoll()` 函数的基本信息和参数：

```c
int WSAPoll(
  LPWSAPOLLFD fdArray,
  ULONG      fds,
  INT        timeout
);
```

- `fdArray`：指向一个 `WSAPOLLFD` 结构数组的指针，每个结构描述了一个要检查状态的套接字。
- `fds`：`fdArray` 数组中元素的数量。
- `timeout`：超时时间，以毫秒为单位。如果设置为负数（如 `-1`），`WSAPoll()` 将会无限期地等待套接字状态的变化；如果设置为 `0`，则立即返回，表示对所有套接字的状态进行一次检查；如果设置为正数，则表示等待指定的毫秒数后超时返回。

`WSAPOLLFD` 结构用于描述一个套接字及其所关注的事件：

```c
typedef struct pollfd {
    SOCKET fd;
    SHORT  events;
    SHORT  revents;
} WSAPOLLFD, *LPWSAPOLLFD;
```

- `fd`：套接字描述符。
- `events`：表示应用程序感兴趣的事件，可以是 `POLLRDNORM`（可读）、`POLLWRNORM`（可写）等等。
- `revents`：表示实际发生的事件，由函数填充。函数调用后，将设置该字段以指示套接字的状态。

`WSAPoll()` 函数调用后，会检查指定的套接字集合的状态，并将就绪的套接字标记在相应的 `revents` 字段中。然后，你可以检查 `revents` 字段以确定哪些套接字处于就绪状态，以便执行相应的操作。

需要注意的是，`WSAPoll()` 函数在 Windows Vista 及更高版本的系统上可用。它可以用于编写高效的异步网络应用程序，允许程序员更有效地管理多个套接字并监视其状态，而无需阻塞线程等待单个套接字的状态变化。

## C++在windows进行socket编程

在 Windows 上进行 C++ 的 Socket 编程通常使用 Winsock 库。下面是一个简单的示例，展示了如何在 C++ 中使用 Winsock 创建一个简单的 TCP 客户端和服务器。

请注意，此示例仅展示基本的连接和通信流程，实际的应用程序可能需要更多的错误处理和完善的逻辑来处理数据发送和接收等操作。

### TCP 服务器示例：

```cpp
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Create a TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Bind the socket to an address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 8080...\n";

    // Accept a client connection
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected\n";

    // Communication with the client
    // ... (send/receive data)

    // Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
```

### TCP 客户端示例：

```cpp
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Create a TCP socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Connect to the server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    serverAddr.sin_port = htons(8080); // Server port

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server\n";

    // Communication with the server
    // ... (send/receive data)

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
```

这两个示例展示了一个简单的 TCP 客户端和服务器。你可以在其中的通信部分添加发送和接收数据的代码，以完成更复杂的通信逻辑。需要注意的是，在实际应用中，需要充分处理错误和异常情况，并且实现完整的数据收发机制。

## VSCode在windows下链接win32库

在 Visual Studio Code 中连接（link）Win32 库，你需要进行以下步骤：

### 1. 创建 C/C++ 项目或文件

- 在 Visual Studio Code 中创建或打开一个 C/C++ 项目或文件夹。

### 2. 设置编译器和构建系统

- 确保你的开发环境已配置好 C/C++ 的编译器和构建系统，比如 MinGW、MSVC 或者其他兼容的编译器。你需要安装相应的工具链和构建工具。

### 3. 编写代码并包含 Win32 头文件

- 在你的 C/C++ 代码中，引入你需要的 Win32 头文件。例如，如果你想使用 Windows 套接字 API，可以包含以下头文件：

```cpp
#include <winsock2.h>
#include <ws2tcpip.h>
```

### 4. 链接 Win32 库

- 打开项目的构建设置或者配置文件（例如 CMakeLists.txt 或 tasks.json）。
- 确保在构建配置中指定需要链接的 Win32 库文件。对于 Windows 套接字 API（例如 `Ws2_32.lib`），你需要在配置文件中指定链接的库文件。

如果你使用 CMake 来构建项目，可以在 CMakeLists.txt 文件中使用 `target_link_libraries` 来链接库文件。比如：

```cmake
target_link_libraries(your_project_name Ws2_32.lib)
```

如果你使用 Visual Studio Code 的 tasks.json 来构建项目，可以使用相应的编译命令并在其中指定需要链接的库文件。

### 5. 编译和构建项目

- 在 Visual Studio Code 中使用你所选定的构建系统来编译和构建项目。可以通过终端或者使用内置的构建工具来完成。

### 6. 运行项目

- 编译成功后，运行你的项目以验证 Win32 库是否正确链接，并且项目能够按预期运行。

这些步骤适用于在 Visual Studio Code 中连接 Win32 库。确保你的代码中包含正确的头文件，并且在项目的构建设置中指定了需要链接的库文件，这样才能成功链接并使用 Win32 API。