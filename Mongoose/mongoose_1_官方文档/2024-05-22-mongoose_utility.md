---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_utility
tag: Mongoose
---
## 简介

+ mongoose 工具

## mg_call 

+ 简介：
  + 发送ev事件到c事件处理程序。该函数在实现您自己的协议时非常有用。

+ 原型：
```cpp
void mg_call(struct mg_connection *c, int ev, void *ev_data);
```

+ 参数：
  + c -- 发送事件的连接
  + ev -- 发送的事件
  + ev_data -- 附加事件参数

+ 返回值：
  + 无

+ 示例：
```cpp
// In a timer callback, send MG_EV_USER event to all connections
static void timer_fn(void *arg) {
  struct mg_mgr *mgr = (struct mg_mgr *) arg;
  for (struct mg_connection *c = mgr->conns; c != NULL; c = c->next) {
    mg_call(c, MG_EV_USER, "hi!");
  }
}
```

---

## mg_error 

+ 简介：
  + 向连接事件处理程序发送MG_EV_ERROR，并使用printf语义格式化错误信息。

+ 原型：
```cpp
void mg_error(struct mg_connection *c, const char *fmt, ...);
```

+ 参数：
  + c -- 发送事件的连接
  + fmt -- 使用printf语义格式化的字符串

+ 返回值：
  + 无

+ 示例：
```cpp
mg_error(c, "Operation failed, error code: %d", errno);
```