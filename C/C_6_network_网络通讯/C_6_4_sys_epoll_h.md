## 简介

+ <sys/epoll.h>笔记

## linux <sys/epoll.h>是什么

`<sys/epoll.h>` 是 Linux 系统中用于使用 `epoll()` 系统调用的头文件。`epoll` 是一种高效的 I/O 多路复用机制，用于监视大量文件描述符上的事件。该头文件中包含了 `epoll()` 系统调用所需的函数原型和相关宏定义。

`<sys/epoll.h>` 提供了以下重要的函数和数据结构：

### 1. `epoll_create()`

```c
int epoll_create(int size);
```

- 创建一个 epoll 实例，返回一个文件描述符用于操作 epoll 实例。`size` 参数已经不再起到作用，只是一个提示值。

### 2. `epoll_ctl()`

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

- 用于在 epoll 实例中注册、修改或删除文件描述符和事件。
- `epfd` 是 epoll 实例的文件描述符。
- `op` 是操作类型，可以是 `EPOLL_CTL_ADD`、`EPOLL_CTL_MOD` 或 `EPOLL_CTL_DEL`，分别用于添加、修改或删除文件描述符和事件。
- `fd` 是要监视的文件描述符。
- `event` 是 `struct epoll_event` 结构体，用于描述要监视的事件类型。

### 3. `epoll_wait()`

```c
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

- 等待文件描述符上的事件发生。
- `epfd` 是 epoll 实例的文件描述符。
- `events` 是一个用于存储事件的数组。
- `maxevents` 是 `events` 数组的大小，表示最多可以存储多少个事件。
- `timeout` 是等待的超时时间（以毫秒为单位），如果设置为 -1 则表示一直等待直到有事件发生。

### 4. `struct epoll_event`

该头文件中还定义了 `struct epoll_event` 结构体，用于描述要监视的事件。该结构体包含了两个成员：

```c
struct epoll_event {
    uint32_t events;       // 事件类型
    epoll_data_t data;    // 用户数据
};
```

- `events` 是要监视的事件类型，可以是 `EPOLLIN`、`EPOLLOUT`、`EPOLLERR`、`EPOLLHUP` 等。
- `data` 是一个 union 类型，可以存储文件描述符或者用户自定义的指针等信息。

总的来说，`<sys/epoll.h>` 头文件提供了使用 `epoll()` 系统调用所需的函数原型和相关数据结构。它是在 Linux 中实现高效的 I/O 多路复用机制的关键头文件之一。

## linux <sys/epoll.h>详解

`<sys/epoll.h>` 是 Linux 系统中用于使用 `epoll()` 系统调用的头文件。`epoll` 是一种高效的 I/O 多路复用机制，允许程序有效地管理大量文件描述符上的事件，特别适用于高并发的网络编程场景。

### 数据结构

`<sys/epoll.h>` 头文件中包含了 `epoll_event` 结构体，用于描述要监视的事件：

```c
struct epoll_event {
    uint32_t events;     // 表示要监视的事件类型
    epoll_data_t data;   // 与事件相关的用户数据
};
```

- `events` 是一个位掩码，表示要监视的事件类型，例如 `EPOLLIN`、`EPOLLOUT`、`EPOLLERR`、`EPOLLHUP` 等。
- `data` 是一个 union 类型，可以存储文件描述符或者用户定义的指针等数据。

### 函数原型

`<sys/epoll.h>` 包含了以下关键的函数原型：

#### 1. `int epoll_create(int size);`

- 创建一个 epoll 实例，返回一个文件描述符以供操作 epoll 实例。`size` 参数已经不再起到作用，只是一个提示值。

#### 2. `int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);`

- 用于在 epoll 实例中注册、修改或删除文件描述符和事件。
- `epfd` 是 epoll 实例的文件描述符。
- `op` 是操作类型，可以是 `EPOLL_CTL_ADD`、`EPOLL_CTL_MOD` 或 `EPOLL_CTL_DEL`，分别用于添加、修改或删除文件描述符和事件。
- `fd` 是要监视的文件描述符。
- `event` 是 `struct epoll_event` 结构体，用于描述要监视的事件类型。

#### 3. `int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);`

- 等待文件描述符上的事件发生。
- `epfd` 是 epoll 实例的文件描述符。
- `events` 是一个用于存储事件的数组。
- `maxevents` 是 `events` 数组的大小，表示最多可以存储多少个事件。
- `timeout` 是等待的超时时间（以毫秒为单位），如果设置为 -1 则表示一直等待直到有事件发生。

### 使用方法

1. 创建一个 epoll 实例：`int epfd = epoll_create(size);`
2. 通过 `epoll_ctl()` 将文件描述符添加到 epoll 实例中：`epoll_ctl(epfd, op, fd, &event);`
3. 使用 `epoll_wait()` 等待文件描述符上的事件：`int nfds = epoll_wait(epfd, events, maxevents, timeout);`

`<sys/epoll.h>` 提供了使用 `epoll()` 系统调用所需的函数原型和相关数据结构，允许程序更有效地管理和监视大量文件描述符上的事件。这是一种适用于高性能网络编程和并发处理的重要机制。

## linux <sys/epoll.h> struct epoll_event详解

`struct epoll_event` 是 `<sys/epoll.h>` 中定义的数据结构，用于描述 `epoll` 实例中的事件，它包含了要监视的事件类型以及与事件相关的数据。

以下是 `struct epoll_event` 结构体的定义：

```c
struct epoll_event {
    uint32_t events;     // 表示要监视的事件类型
    epoll_data_t data;   // 与事件相关的用户数据
};
```

- `events` 是一个 32 位的无符号整数，表示要监视的事件类型。它是一个位掩码，可以是以下事件类型的组合：
  - `EPOLLIN`：表示对应的文件描述符上有数据可读。
  - `EPOLLOUT`：表示对应的文件描述符可以写入。
  - `EPOLLERR`：表示对应的文件描述符发生错误。
  - `EPOLLHUP`：表示对应的文件描述符挂起，可能是连接断开或者被关闭。
  - 等等，还有其他类型的事件。

- `data` 是一个 `epoll_data_t` 类型的 union。它可以存储文件描述符或者用户定义的指针等数据。具体定义如下：

```c
typedef union epoll_data {
    void *ptr;           // 用户定义的数据指针
    int fd;              // 文件描述符
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;
```

这个 union 可以存储不同类型的数据，具体存储什么样的数据取决于应用程序中的使用方式。

`struct epoll_event` 结构体用于向 `epoll` 实例中注册文件描述符并指定要监视的事件类型，以及关联额外的数据。在调用 `epoll_ctl()` 向 `epoll` 实例中添加、修改或删除文件描述符时，会用到这个结构体。

这个结构体是在使用 `epoll` 实现高效的 I/O 多路复用时必不可少的一部分，它描述了应用程序感兴趣的事件类型以及与之关联的数据。

## linux <sys/epoll.h> epoll_create()详解

`epoll_create()` 是 Linux 中用于创建 epoll 实例的系统调用之一，它返回一个文件描述符，用于对 epoll 实例进行操作。

### 函数原型

```c
#include <sys/epoll.h>

int epoll_create(int size);
```

- `size` 是一个已被废弃的参数，代表要监视的文件描述符数量的一个提示。该参数在现代内核中已经不再起作用，仅作为一个历史遗留而保留。

### 返回值

- 如果成功，`epoll_create()` 返回一个新的文件描述符，用于对 epoll 实例进行操作。
- 如果失败，返回值为 -1，并且设置 `errno` 表示错误的原因。

### 使用方法

```c
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int epoll_fd = epoll_create(10); // 创建 epoll 实例

    if (epoll_fd == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }

    // 对 epoll 实例进行操作，例如使用 epoll_ctl() 注册文件描述符等

    close(epoll_fd); // 关闭 epoll 实例

    return 0;
}
```

### 作用

- `epoll_create()` 用于创建一个 epoll 实例，该实例允许程序监视文件描述符上的事件。
- 它返回一个文件描述符，后续可以使用 `epoll_ctl()` 向这个 epoll 实例中添加、修改或删除文件描述符和事件，并使用 `epoll_wait()` 等待文件描述符上的事件发生。

总的来说，`epoll_create()` 创建一个 epoll 实例，并返回一个文件描述符，该文件描述符用于对 epoll 实例进行操作。这是使用 epoll 实现高效 I/O 多路复用的第一步。

## linux <sys/epoll.h> epoll_ctl()详解

`epoll_ctl()` 是 Linux 中 `<sys/epoll.h>` 头文件中定义的函数，用于控制（管理） epoll 实例中的文件描述符和事件，可以实现添加、修改或删除文件描述符和事件的操作。

### 函数原型

```c
#include <sys/epoll.h>

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

- `epfd` 是 epoll 实例的文件描述符，由 `epoll_create()` 创建。
- `op` 是控制操作的类型，可以是以下之一：
  - `EPOLL_CTL_ADD`：将文件描述符添加到 epoll 实例中。
  - `EPOLL_CTL_MOD`：修改已经注册的文件描述符的事件。
  - `EPOLL_CTL_DEL`：从 epoll 实例中删除文件描述符。
- `fd` 是要操作的文件描述符。
- `event` 是一个指向 `struct epoll_event` 结构体的指针，用于指定要监视的事件类型。

### 返回值

- 如果操作成功，`epoll_ctl()` 返回 0。
- 如果出现错误，返回值为 -1，并设置 `errno` 表示错误的原因。

### 使用方法

```c
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int epoll_fd = epoll_create(10); // 创建 epoll 实例

    if (epoll_fd == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }

    struct epoll_event event;
    event.events = EPOLLIN; // 监视可读事件
    event.data.fd = /* Your file descriptor */; // 设置要监视的文件描述符

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, /*fd*/, &event) == -1) {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }

    // 进行其他的 epoll_ctl() 操作，如修改事件、删除文件描述符等

    close(epoll_fd); // 关闭 epoll 实例

    return 0;
}
```

### 作用

- `epoll_ctl()` 用于向 epoll 实例中注册、修改或删除文件描述符和事件。
- 通过 `EPOLL_CTL_ADD`，可以将文件描述符添加到 epoll 实例中，并指定要监视的事件类型。
- `EPOLL_CTL_MOD` 可用于修改已经注册的文件描述符的事件。
- `EPOLL_CTL_DEL` 可以从 epoll 实例中删除文件描述符。

总之，`epoll_ctl()` 允许程序员控制 epoll 实例，对文件描述符进行添加、修改或删除操作，并定义要监视的事件类型，以便在调用 `epoll_wait()` 等待事件发生时得到相应的通知。

## linux <sys/epoll.h> epoll_wait()详解

`epoll_wait()` 是 Linux 中 `<sys/epoll.h>` 头文件中定义的函数，用于等待文件描述符上的事件发生，是使用 epoll 实现 I/O 多路复用的核心之一。

### 函数原型

```c
#include <sys/epoll.h>

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

- `epfd` 是 epoll 实例的文件描述符，由 `epoll_create()` 创建。
- `events` 是一个用于存储事件的数组。
- `maxevents` 是 `events` 数组的大小，表示最多可以存储多少个事件。
- `timeout` 是等待的超时时间（以毫秒为单位）：
  - 如果设置为 -1，表示一直等待直到有事件发生。
  - 如果设置为 0，表示立即返回。
  - 如果设置为一个正整数，表示等待指定的毫秒数。

### 返回值

- 如果有事件发生，`epoll_wait()` 返回发生事件的文件描述符数量（大于 0）。
- 如果超时时间到达或者没有事件发生，返回值为 0。
- 如果出现错误，返回值为 -1，并设置 `errno` 表示错误的原因。

### 使用方法

```c
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_EVENTS 10

int main() {
    int epoll_fd = epoll_create(10); // 创建 epoll 实例

    if (epoll_fd == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }

    struct epoll_event events[MAX_EVENTS]; // 存放事件的数组

    // 等待事件发生
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    if (num_events == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }

    // 处理发生的事件
    for (int i = 0; i < num_events; ++i) {
        // 根据 events[i] 中的信息处理事件
    }

    close(epoll_fd); // 关闭 epoll 实例

    return 0;
}
```

### 作用

- `epoll_wait()` 用于等待文件描述符上的事件发生。
- 它会阻塞程序，直到指定文件描述符上有事件发生，或者超时时间到达。
- 当有事件发生时，将会填充 `events` 数组，程序可以遍历数组处理发生的事件。

`epoll_wait()` 是使用 epoll 实现高效 I/O 多路复用的重要部分，它允许程序等待多个文件描述符上的事件发生，并有效地处理这些事件。