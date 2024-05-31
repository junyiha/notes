---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_logging
tag: Mongoose
---
## 简介

+ mongoose 日志相关函数
+ Mongoose为日志记录提供了一系列函数和宏。应用程序可以为自己的目的使用这些函数，也可以使用Mongoose API的其他部分。

## LOG

+ 简介：
  + 日志宏

+ 原型：
```cpp
#define LOG(level, args)
#define MG_ERROR(args) MG_LOG(MG_LL_ERROR, args)
#define MG_INFO(args) MG_LOG(MG_LL_INFO, args)
#define MG_DEBUG(args) MG_LOG(MG_LL_DEBUG, args)
#define MG_VERBOSE(args) MG_LOG(MG_LL_VERBOSE, args)
```

+ 示例：
```cpp
MG_INFO(("Hello %s!", "world"));  // Output "Hello, world"
```

---

## mg_log_set 

+ 简介：
  + 设置Mongoose日志级别

+ 原型：
```cpp
void mg_log_set(const char *spec);
```

+ 参数：
  + spec -- 字符串，包含日志级别，可以是以下值之一
    + 0 -- 关闭日志
    + 1 -- 仅输出错误
    + 2 -- 输出错误和消息
    + 3 -- 输出错误，消息和调试消息
    + 4 -- 输出所有日志信息

+ 返回值：
  + 无

+ 详解：
  + 可以根据源文件覆盖日志级别。例如，如果有一个名为foo.c的文件，您希望将全局级别设置为2（info），但将foo.c文件的日志级别提高到debug，那么规格应该是 "2,foo.c=3"。可以有多个以逗号分隔的重写。

+ 示例：
```cpp
mg_log_set("2");                  // Set log level to info
mg_log_set("2,foo.c=3,bar.c=0");  // Set log level to info, with overrides
```

---

## mg_hexdump 

+ 简介：
  + 记录二进制数据buf, len的十六进制转储。

+ 原型：
```cpp
void mg_hexdump(const void *buf, int len);
```

+ 参数：
  + buf -- 数据指针
  + len -- 数据大小

+ 返回值：
  + 无

+ 示例：
```cpp
mg_hexdump(c->recv.buf, c->recv.len);  // Hex dump incoming data
```

---

## mg_log_set_fn 

+ 简介：
  + 将日志重定向到自定义函数。

+ 原型：
```cpp
void mg_log_set_fn(mg_pfn_t logfunc, void *param);
```

+ 参数：
  + logfunc -- 记录单个字符的函数指针
  + param -- 日志函数参数

+ 示例：
```cpp
static void mylog(char ch, void *param) {
  static char buf[256];
  static size_t len;
  buf[len++] = ch;
  if (ch == '\n' || len >= sizeof(buf)) {
    syslog(LOG_INFO, "%.*s", (int) len, buf); // Send logs
    len = 0;
  }
}
...
mg_log_set_fn(mylog, NULL);
```