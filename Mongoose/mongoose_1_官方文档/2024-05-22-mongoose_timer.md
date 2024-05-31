---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_timer
tag: Mongoose
---
## 简介

+ mongoose工具的计时器相关笔记

## struct mg_timer

+ 简介：
  + 计时器结构体。描述一个软件计时器。计时器粒度与主事件循环中的`mg_mgr_poll()`的超时参数相同

+ 原型：
```c
struct mg_timer {
  uint64_t period_ms;       // Timer period in milliseconds
  uint64_t expire;          // Expiration timestamp in milliseconds
  unsigned flags;           // Possible flags values below
#define MG_TIMER_ONCE 0     // Call function once
#define MG_TIMER_REPEAT 1   // Call function periodically
#define MG_TIMER_RUN_NOW 2  // Call immediately when timer is set
  void (*fn)(void *);       // Function to call
  void *arg;                // Function argument
  struct mg_timer *next;    // Linkage
};
```

## mg_timer_add

+ 简介：
  + 设置一个计时器。这是一个高级计时器API，允许将软件计时器添加到活动管理器。
  + 这个函数使用`calloc()`一个新的计时器，并将它添加到`mgr->timers`列表中。
  + 当调用`mg_mgr_poll()`时，所有添加的计时器均进行轮询，并在计时器到期时调用计时器设定的函数

+ 原型：
```c
struct mg_timer *mg_timer_add(struct mg_mgr *mgr, uint64_t period_ms, unsigned flags, void (*fn)(void *), void *fn_data);
```

+ 参数：
  + `mgr`   --  指向事件管理器的结构体指针
  + `ms`    --  一个时间间隔，以毫秒为单位
  + `flags` --  计时器标志掩码：`MG_TIMER_REPEAT`和`MG_TIMER_RUN_NOW`
  + `fn`    --  函数调用
  + `fn_data`  --  调用的函数参数

+ 返回值：
  + 返回一个指向创建的计时器的指针

+ 详解：
  + 确保计时器的间隔等于或大于`mg_mgr_poll()`的超时时间

+ 示例：
```c
void timer_fn(void *data) {
  // ...
}

mg_timer_add(mgr, 1000, MG_TIMER_REPEAT, timer_fn, NULL);
```

## mg_timer_init

+ 简介：
  + 设置一个计时器

+ 原型：
```c
void mg_timer_init(struct mg_timer **head, struct mg_timer *t, uint64_t period_ms, unsigned flags, void (*fn)(void *), void *fn_data);
```

+ 参数：
  + `head`    --  指向`mg_timer`队列头部的指针
  + `t`       --  指向一个需要被初始化的`mg_timer`
  + `ms`      --  时间间隔，以毫秒为单位
  + `flags`   --  计时器标志掩码：`MG_TIMER_REPEAT`和`MG_TIMER_RUN_NOW`
  + `fn`    --  函数调用
  + `fn_data`  --  调用的函数参数

+ 返回值：
  + 无

+ 示例
```c
void timer_fn(void *data) {
  // ...
}

struct mg_timer timer, *head = NULL;
mg_timer_init(&head, &timer, 1000, MG_TIMER_REPEAT, timer_fn, NULL);
```

## mg_timer_free

+ 简介：
  + 释放计时器，将其从内部计时器列表中删除。

+ 原型：
```c
void mg_timer_free(struct mg_timer **head, struct mg_timer *t);
```

+ 参数：
  + `head`  --  指向`mg_timer`队列头部的指针
  + `t`     --  需要释放的计时器

+ 返回值：
  + 无

+ 示例：
```c
struct mg_timer timer;
// ...
mg_timer_free(&timer);
```

## mg_timer_poll

+ 简介：
  + 如果当前的时间戳`uptime_ms`超过了计时器的到期时间，则计时器遍历列表，并调用它们

+ 原型：
```c
void mg_timer_poll(struct mg_timer **head, uint64_t uptime_ms);
```

+ 参数：
  + `head`   --  指向`mg_timer`列表头部的指针
  + `uptime_ms`  --  当前时间戳

+ 返回值：
  + 无

+ 示例：
```c
mg_timer_poll(mg_millis());
```

## mg_millis 

+ 简介：
  + 以毫秒为单位返回当前运行时间。

+ 原型：
```cpp
int64_t mg_millis(void);
```

+ 参数：
  + 无

+ 返回值：
  + 当前时间

+ 示例：
```cpp
int64_t uptime = mg_millis();
```