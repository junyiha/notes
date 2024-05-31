---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_file_system
tag: Mongoose
---
## 简介

+ 文件相关api

## struct mg_fd

+ 简介：
  + 文件系统虚拟化层
  + Mongoose允许覆盖文件IO操作，以支持不同的存储设备，如可编程的闪存，无文件系统设备等。为了实现这一点，Mongoose提供了一个结构mg_fs API来指定一个自定义的文件系统。除此之外，Mongoose还提供了几个内置的API--一个标准的POSIX，FatFS，和一个 "打包的FS "API：
```c
extern struct mg_fs mg_fs_posix;   // POSIX open/close/read/write/seek
extern struct mg_fs mg_fs_packed;  // Packed FS, see examples/device-dashboard
extern struct mg_fs mg_fs_fat;     // FAT FS
```

+ 原型：
```c
struct mg_fs {
  int (*st)(const char *path, size_t *size, time_t *mtime);  // stat file
  void (*ls)(const char *path, void (*fn)(const char *, void *), void *);
  void *(*op)(const char *path, int flags);             // Open file
  void (*cl)(void *fd);                                 // Close file
  size_t (*rd)(void *fd, void *buf, size_t len);        // Read file
  size_t (*wr)(void *fd, const void *buf, size_t len);  // Write file
  size_t (*sk)(void *fd, size_t offset);                // Set file position
  bool (*mv)(const char *from, const char *to);         // Rename file
  bool (*rm)(const char *path);                         // Delete file
  bool (*mkd)(const char *path);                        // Create directory
};

enum { MG_FS_READ = 1, MG_FS_WRITE = 2, MG_FS_DIR = 4 };
```

## struct mg_fd

+ 简介：
  + 已打开的文件抽象。

+ 原型：
```c
struct mg_fd {
  void *fd;
  struct mg_fs *fs;
};
```

## mg_fs_open

+ 简介：
  + 在一个给定的文件系统中打开一个文件

+ 原型：
```c
struct mg_fd *mg_fs_open(struct mg_fs *fs, const char *path, int flags);
```

+ 参数：
  + fs : 一个文件系统的实现
  + path : 一个文件路径
  + flags : 所需的标志，是MG_FS_READ和MG_FS_WRITE的组合。

+ 返回值：
  + 成功： 一个非NULL的已打开的描述符、
  + 失败： NULL

+ 示例
```c
struct mg_fd *fd = mg_fs_open(&mg_fs_posix, "/tmp/data.json", MG_FS_WRITE);
```

## mg_fs_close

+ 简介：
  + 关闭一个已打开的文件描述符

+ 原型：
```c
void mg_fs_close(struct mg_fd *fd);
```

+ 参数：
  + fd : 一个已打开的文件描述符

+ 返回自：
  + 无

## mg_file_read

+ 简介：
  + 在内存中读取整个文件。

+ 原型
```c
char *mg_file_read(struct mg_fs *fs, const char *path, size_t *size);
```

+ 参数
  + fs : 一个文件系统的实现
  + path : 一个文件路径
  + size : 如果不是NULL，将包含所读文件的大小。

+ 返回值：
  + 成功时，一个指向文件数据的指针，该指针保证为0端。
  + 错误时，为NULL

+ 示例：
```c
size_t size = 0;
char *data = mg_file_read(&mg_fs_packed, "/data.json", &size);
```

## mg_file_write

+ 简介：
  + 写入一段数据buf，len到一个文件路径。如果该文件不存在，它将被创建。之前的内容，如果有的话，会被删除。

+ 原型：
```c
bool mg_file_write(struct mg_fs *fs, const char *path, const void *buf, size_t len);
```

+ 参数：
  + fs : 一个文件系统的实现
  + path : 一个文件路径
  + buf : 一个指向待写数据的指针
  + len : 待写数据的大小

+ 返回值：
  + 成功, true
  + 失败, false

+ 示例：
```c
mg_file_write(&mg_fs_fat, "/test.txt", "hi\n", 3);
```

## mg_file_printf

+ 简介：
  + 写一个打印格式的数据到一个文件路径。如果该文件不存在，它将被创建。之前的内容（如果有的话）被删除

+ 原型：
```c
bool mg_file_printf(struct mg_fs *fs, const char *path, const char *fmt, ...);
```

+ 参数：
  + fs : 一个文件系统的实现
  + path : 一个文件路径
  + fmt : printf语义中的格式字符串。支持的格式指定器的列表见mg_snprintf。

+ 返回值：
  + 成功, true
  + 失败, false

+ 示例：
```c
mg_file_printf(&mg_fs_fat, "/test.txt", "%s\n", "hi");
```