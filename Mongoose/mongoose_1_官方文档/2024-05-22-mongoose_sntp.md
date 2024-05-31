---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_sntp
tag: Mongoose
---
## 简介

+ SNTP server(simple network time protocol), 是一种用于提供时间同步服务的网络服务器。它基于网络通信协议，允许计算机和其他网络设备通过网络获取准确的时间信息

## mg_sntp_connect

+ 简介：
  + 连接SNTP服务器。

+ 原型：
```cpp
struct mg_connection *mg_sntp_connect(struct mg_mgr *mgr, const char *url,
                                      mg_event_handler_t fn, void *fn_data)
```

+ 参数：
  + mgr -- 使用的事件管理器
  + url -- 指定远程URL，如果为空，则为time.google.com。
  + fn  -- 事件处理函数
  + fn_data -- 一个任意指针，在调用事件处理程序时作为fn_data传递。该指针也将作为c->fn_data存储在连接结构中。

+ 返回值：
  + 成功，返回指向创建的连接的指针
  + 失败，返回NULL

+ 示例：
```cpp
static void sntp_cb(struct mg_connection *c, int ev, void *evd, void *fnd) {
  if (ev == MG_EV_SNTP_TIME) {
    // Time received
    struct timeval *tv = (struct timeval *tv)evd;
  }
}
...
mg_sntp_connect(mgr&, NULL /* connect to time.google.com */, sntp_cb, NULL);
```

## mg_sntp_request 

+ 简介：
  + 向SNTP服务器发送时间请求

+ 原型：
```cpp
void mg_sntp_request(struct mg_connection *c)
```

+ 参数：
  + c -- 使用的连接

+ 返回值：
  + 无

+ 示例：
```cpp
mg_sntp_request(c);
```