## 简介

+ Linux POSIX <sys/stat.h> 详解

## Linux POSIX <sys/stat.h> 详解

`<sys/stat.h>` 是 POSIX 操作系统中的一个头文件，用于处理文件状态信息和文件系统属性。它包含了一些在文件和文件系统方面的函数、宏和数据结构的定义。

### 一些常见的函数和宏：
- **`stat()` 和 `fstat()`**：用于获取文件的状态信息，包括文件的大小、权限、所有者信息等。
- **`S_IFMT`、`S_IFREG`、`S_IFDIR`** 等宏：用于检查文件类型（常规文件、目录等）的位掩码。
- **`chmod()`、`chown()`、`utime()`** 等函数：用于改变文件的权限、所有者或者修改文件的访问和修改时间。
- **文件访问权限掩码（例如 `S_IRUSR`、`S_IWGRP` 等）**：用于设置文件的读、写、执行权限。

### 一些常见的数据结构：
- **`struct stat`**：用于存储文件的状态信息。该结构包含了文件的各种属性，如大小、权限、时间戳等。
  
### 示例（使用 `stat()` 获取文件状态信息）：
```c
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct stat fileInfo;
    const char *filename = "example.txt"; // 假设存在的文件名

    // 获取文件状态信息并存储在 fileInfo 结构体中
    if (stat(filename, &fileInfo) == 0) {
        printf("文件大小：%lld 字节\n", (long long)fileInfo.st_size);
        printf("访问权限：%o\n", fileInfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        // 更多的文件状态信息可通过 struct stat 中的其他成员获取，如 st_mode、st_uid、st_gid、st_atime 等
    } else {
        perror("stat");
    }

    return 0;
}
```

### 注意事项：
- `<sys/stat.h>` 中包含的函数和数据结构允许程序员获取和修改文件的属性信息，如权限、所有者、文件大小等。
- 该头文件中定义了一些宏，用于检查文件类型和设置文件权限，以及一些函数，用于修改文件的属性信息。
- 使用这些函数和数据结构可以在编写文件处理相关的程序时获取文件的状态信息，并进行相应的操作。

总的来说，`<sys/stat.h>` 提供了一系列函数、宏和数据结构，用于获取和修改文件的状态信息，对文件的操作和文件系统属性进行处理。

## Linux POSIX <sys/stat.h> stat() 详解

`stat()` 是 POSIX 操作系统中 `<sys/stat.h>` 头文件中定义的一个函数，用于获取指定文件的状态信息，并将其存储在 `struct stat` 结构体中。

### 函数签名：
```c
int stat(const char *pathname, struct stat *statbuf);
```

- **返回值**：若成功，返回 0；失败则返回 -1，并设置 `errno` 表示错误类型。
- **参数**：
  - `pathname`：字符串，表示要查询状态的文件路径。
  - `statbuf`：`struct stat` 类型的指针，用于存储获取到的文件状态信息。

### `struct stat` 结构体：
```c
struct stat {
    dev_t     st_dev;         // 设备 ID
    ino_t     st_ino;         // inode 号
    mode_t    st_mode;        // 文件类型和访问权限
    nlink_t   st_nlink;       // 链接数
    uid_t     st_uid;         // 用户 ID
    gid_t     st_gid;         // 组 ID
    off_t     st_size;        // 文件大小（字节数）
    time_t    st_atime;       // 最后访问时间
    time_t    st_mtime;       // 最后修改时间
    time_t    st_ctime;       // 最后状态改变时间
    blksize_t st_blksize;     // 文件系统 I/O 缓冲区大小
    blkcnt_t  st_blocks;      // 分配的文件块数
};
```

### 示例：
```c
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct stat fileInfo;
    const char *filename = "example.txt"; // 假设存在的文件名

    // 获取文件状态信息并存储在 fileInfo 结构体中
    if (stat(filename, &fileInfo) == 0) {
        printf("文件大小：%lld 字节\n", (long long)fileInfo.st_size);
        printf("访问权限：%o\n", fileInfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        // 更多的文件状态信息可通过 struct stat 中的其他成员获取，如 st_mode、st_uid、st_gid、st_atime 等
    } else {
        perror("stat");
    }

    return 0;
}
```

### 注意事项：
- `stat()` 函数用于获取指定文件的详细状态信息，如文件大小、访问权限、所有者信息、最后访问时间等。
- 要使用 `stat()` 函数，需要包含 `<sys/stat.h>` 头文件。
- 在调用 `stat()` 函数时，需要传递文件路径和一个指向 `struct stat` 结构体的指针，该结构体将会被填充为文件的状态信息。
- 如果函数执行成功，返回值为 0；否则返回 -1，并设置 `errno` 表示错误类型。

`stat()` 函数是用于获取文件状态信息的重要函数之一，它允许程序员获取文件的详细属性和状态，以便在程序中进行相应的操作。

## Linux POSIX <sys/stat.h> fstat() 详解

`fstat()` 是 POSIX 操作系统中 `<sys/stat.h>` 头文件中定义的一个函数，用于获取一个已打开文件的状态信息，并将其存储在 `struct stat` 结构体中。

### 函数签名：
```c
int fstat(int filedes, struct stat *buf);
```

- **返回值**：若成功，返回 0；失败则返回 -1，并设置 `errno` 表示错误类型。
- **参数**：
  - `filedes`：文件描述符，表示已经打开的文件。
  - `buf`：`struct stat` 类型的指针，用于存储获取到的文件状态信息。

### `struct stat` 结构体：
```c
struct stat {
    dev_t     st_dev;         // 设备 ID
    ino_t     st_ino;         // inode 号
    mode_t    st_mode;        // 文件类型和访问权限
    nlink_t   st_nlink;       // 链接数
    uid_t     st_uid;         // 用户 ID
    gid_t     st_gid;         // 组 ID
    off_t     st_size;        // 文件大小（字节数）
    time_t    st_atime;       // 最后访问时间
    time_t    st_mtime;       // 最后修改时间
    time_t    st_ctime;       // 最后状态改变时间
    blksize_t st_blksize;     // 文件系统 I/O 缓冲区大小
    blkcnt_t  st_blocks;      // 分配的文件块数
};
```

### 示例：
```c
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    struct stat fileInfo;
    const char *filename = "example.txt"; // 假设存在的文件名
    int fileDescriptor;

    // 打开文件
    fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor < 0) {
        perror("open");
        return -1;
    }

    // 获取文件状态信息并存储在 fileInfo 结构体中
    if (fstat(fileDescriptor, &fileInfo) == 0) {
        printf("文件大小：%lld 字节\n", (long long)fileInfo.st_size);
        printf("访问权限：%o\n", fileInfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        // 更多的文件状态信息可通过 struct stat 中的其他成员获取，如 st_mode、st_uid、st_gid、st_atime 等
    } else {
        perror("fstat");
    }

    // 关闭文件
    close(fileDescriptor);

    return 0;
}
```

### 注意事项：
- `fstat()` 函数用于获取一个已经打开文件的详细状态信息，如文件大小、访问权限、所有者信息、最后访问时间等。
- 要使用 `fstat()` 函数，需要包含 `<sys/stat.h>` 和 `<fcntl.h>` 头文件。
- 在调用 `fstat()` 函数时，需要传递文件描述符和一个指向 `struct stat` 结构体的指针，该结构体将会被填充为文件的状态信息。
- 如果函数执行成功，返回值为 0；否则返回 -1，并设置 `errno` 表示错误类型。

`fstat()` 函数允许程序员在已经打开的文件上获取详细的状态信息，这对于进行文件操作和管理非常有用。

## Linux POSIX <sys/stat.h> chmod() 详解

`chmod()` 是 POSIX 操作系统中 `<sys/stat.h>` 头文件中定义的一个函数，用于改变文件的访问权限。

### 函数签名：
```c
int chmod(const char *pathname, mode_t mode);
```

- **返回值**：若成功，返回 0；失败则返回 -1，并设置 `errno` 表示错误类型。
- **参数**：
  - `pathname`：字符串，表示要修改权限的文件路径。
  - `mode`：`mode_t` 类型，表示新的访问权限，使用八进制表示。

### 示例：
```c
#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt"; // 假设存在的文件名
    mode_t newMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 新的权限，只允许所有者读写，组和其他用户只允许读

    // 修改文件权限
    if (chmod(filename, newMode) == 0) {
        printf("文件权限修改成功\n");
    } else {
        perror("chmod");
    }

    return 0;
}
```

### 注意事项：
- `chmod()` 函数用于改变指定文件的访问权限。
- `mode` 参数用 `mode_t` 类型表示，可以使用 `S_IRUSR`（所有者读权限）、`S_IWUSR`（所有者写权限）、`S_IXUSR`（所有者执行权限）等宏定义。
- 使用位掩码运算符 `|` 来组合权限选项，然后传递给 `chmod()` 函数来设置文件的新权限。
- 要使用 `chmod()` 函数，需要对指定的文件有合适的权限。

`chmod()` 函数允许程序员根据需要修改文件的访问权限，以控制文件的读、写、执行等操作，对于安全性和权限管理非常重要。

## Linux POSIX <sys/stat.h> chown() 详解

`chown()` 是 POSIX 操作系统中 `<sys/stat.h>` 头文件中定义的一个函数，用于修改文件的所有者和所属组。

### 函数签名：
```c
int chown(const char *pathname, uid_t owner, gid_t group);
```

- **返回值**：若成功，返回 0；失败则返回 -1，并设置 `errno` 表示错误类型。
- **参数**：
  - `pathname`：字符串，表示要修改所有者和所属组的文件路径。
  - `owner`：`uid_t` 类型，表示文件的新所有者 ID。
  - `group`：`gid_t` 类型，表示文件的新所属组 ID。

### 示例：
```c
#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt"; // 假设存在的文件名
    uid_t newOwner = 1000; // 新的所有者 ID
    gid_t newGroup = 1000; // 新的所属组 ID

    // 修改文件所有者和所属组
    if (chown(filename, newOwner, newGroup) == 0) {
        printf("文件所有者和所属组修改成功\n");
    } else {
        perror("chown");
    }

    return 0;
}
```

### 注意事项：
- `chown()` 函数用于修改指定文件的所有者和所属组。
- `owner` 参数表示文件的新所有者 ID，`group` 参数表示文件的新所属组 ID。
- 要使用 `chown()` 函数，需要对指定的文件有适当的权限，通常只有超级用户或文件的当前所有者可以修改文件的所有者和所属组。

`chown()` 函数允许程序员根据需要更改文件的所有者和所属组，这对于管理文件系统权限和安全性是非常重要的。

## Linux POSIX <sys/stat.h> utime() 详解

`utime()` 是 POSIX 操作系统中 `<sys/stat.h>` 头文件中定义的一个函数，用于修改文件的访问时间和修改时间。

### 函数签名：
```c
#include <utime.h>

int utime(const char *filename, const struct utimbuf *times);
```

- **返回值**：若成功，返回 0；失败则返回 -1，并设置 `errno` 表示错误类型。
- **参数**：
  - `filename`：字符串，表示要修改访问时间和修改时间的文件路径。
  - `times`：`struct utimbuf` 类型的指针，指向包含访问时间和修改时间信息的结构体。

### `struct utimbuf` 结构体：
```c
struct utimbuf {
    time_t actime;  // 访问时间
    time_t modtime; // 修改时间
};
```

### 示例：
```c
#include <stdio.h>
#include <sys/stat.h>
#include <utime.h>

int main() {
    const char *filename = "example.txt"; // 假设存在的文件名
    struct utimbuf newTimes;

    newTimes.actime = 1640260800; // 2022-12-24 00:00:00 的时间戳，作为新的访问时间
    newTimes.modtime = 1640264400; // 2022-12-24 01:00:00 的时间戳，作为新的修改时间

    // 修改文件的访问时间和修改时间
    if (utime(filename, &newTimes) == 0) {
        printf("文件访问时间和修改时间修改成功\n");
    } else {
        perror("utime");
    }

    return 0;
}
```

### 注意事项：
- `utime()` 函数用于修改指定文件的访问时间和修改时间。
- `struct utimbuf` 结构体包含了要设置的访问时间和修改时间的值，以秒为单位。
- 要使用 `utime()` 函数，需要对指定的文件有适当的权限。

`utime()` 函数允许程序员根据需要更改文件的访问时间和修改时间，这对于模拟文件访问和修改时间、文件同步等操作是非常有用的。