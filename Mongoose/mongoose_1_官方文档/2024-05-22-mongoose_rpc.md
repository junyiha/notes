---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_rpc
tag: Mongoose
---
## 简介

+ RPC(Remote Procedure Call, 远程过程调用),是一种通信协议和编程模型，用于实现分布式系统中不同节点之间的远程调用。它允许在不同计算机或进程之间像调用本地函数一样调用远程函数，隐藏了底层网络通信的细节
+ Mongoose包含一组函数，通过RPC方法简化服务器端处理。

## struct mg_rpc 

+ 简介：
  + RPC方法处理程序结构。每个方法在一个链表中都有一个入口，每个入口指向一个字符串，该字符串描述了将调用该方法的模式，以及为满足该方法调用而调用的函数，并带有一个适当的函数参数。

+ 原型：
```cpp
struct mg_rpc {
  struct mg_rpc *next;              // Next in list
  struct mg_str method;             // Method pattern
  void (*fn)(struct mg_rpc_req *);  // Handler function
  void *fn_data;                    // Handler function argument
};
```

## struct mg_rpc_req 

+ 简介：
  + RPC请求描述符。被调用的方法会收到一个包含请求的描述符，以及一个指向函数的指针，该函数将被调用来打印输出响应，并带有一个适当的函数参数；例如：mg_pfn_realloc() 或 mg_pfn_iobuf()

+ 原型：
```cpp
struct mg_rpc_req {
  struct mg_rpc **head;  // RPC handlers list head
  struct mg_rpc *rpc;    // RPC handler being called
  mg_pfn_t pfn;          // Response printing function
  void *pfn_data;        // Response printing function data
  void *req_data;        // Arbitrary request data
  struct mg_str frame;   // Request, e.g. {"id":1,"method":"add","params":[1,2]}
};
```

## mg_rpc_add 

+ 简介：
  + 将方法method_pattern添加到RPC方法列表的头部。调用该方法将调用handler，并将handler_data与请求一起传递给它(如下使用示例中的r->fn_data)。

+ 原型：
```cpp
void mg_rpc_add(struct mg_rpc **head, struct mg_str method_pattern,
                void (*handler)(struct mg_rpc_req *), void *handler_data);
```

+ 参数：
  + head -- 链表指针
  + method_pattern -- 方法的名称
  + handler -- 执行该方法操作的RPC函数
  + handler_data -- 任意函数数据

+ 注：
  + 如果method_pattern为空字符串，该处理程序将被调用来处理JSON-RPC响应。如果JSON请求是由双方发起的，那么处理响应可能是必要的。

+ 示例：
```cpp
struct mg_rpc *s_rpc_head = NULL;

static void rpc_sum(struct mg_rpc_req *r) {
  double a = 0.0, b = 0.0;
  mg_json_get_num(r->frame, "$.params[0]", &a);
  mg_json_get_num(r->frame, "$.params[1]", &b);
  mg_rpc_ok(r, "%g", a + b);
}

static void rpc_mul(struct mg_rpc_req *r) {//...}
}

  mg_rpc_add(&s_rpc_head, mg_str("sum"), rpc_sum, NULL);
  mg_rpc_add(&s_rpc_head, mg_str("mul"), rpc_mul, NULL);
```

## mg_rpc_del 

+ 简介：
  + 从RPC方法列表中删除带有RPC函数处理程序的方法

+ 原型：
```cpp
void mg_rpc_del(struct mg_rpc **head, void (*handler)(struct mg_rpc_req *));
```

+ 参数：
  + head -- 链表指针
  + handler -- RPC函数处理程序的方法，使用NULL删除全部

+ 示例：
```cpp
struct mg_rpc *s_rpc_head = NULL;
// add methods
// ...

// Time to cleanup
mg_rpc_del(&s_rpc_head, rpc_mul);    // Deallocate specific handler
mg_rpc_del(&s_rpc_head, NULL);       // Deallocate all RPC handlers
```

## mg_rpc_process 

+ 简介：
  + 为这个请求调用合适的方法。如果请求的方法不存在，将调用mg_rpc_err()并打印错误提示。

+ 原型：
```cpp
void mg_rpc_process(struct mg_rpc_req *req);
```

+ 参数：
  + req -- 一个请求

+ 示例：
```cpp
struct mg_rpc *s_rpcs = NULL;                               // Empty RPC list head
mg_rpc_add(&s_rpcs, mg_str("rpc.list"), mg_rpc_list, NULL); // Add rpc.list
// ... add more RPC methods

// On request, process the incoming frame
struct mg_str req = mg_str("{\"id\":1,\"method\":\"sum\",\"params\":[1,2]}");
struct mg_iobuf io = {0, 0, 0, 512};  // Empty IO buf, with 512 realloc granularity
struct mg_rpc_req r = {
  .head = &s_rpcs,        // RPC list head
  .rpc = NULL,            // This will be set by mg_rpc_process()
  .pfn = mg_pfn_iobuf,    // Printing function: print into the io buffer
  .pfn_data = &io,        // Pass our io buffer as a parameter
  .req_data = NULL,       // No specific request data
  .frame = req,           // Specify incoming frame
};

mg_rpc_process(&r);
if (io.buf != NULL) printf("Response: %s\n", (char *) io.buf);
mg_iobuf_free(&io);
```

## mg_rpc_ok, mg_rpc_vok

+ 简介：
  + 打印结果帧的辅助函数

+ 原型：
```cpp
void mg_rpc_ok(struct mg_rpc_req *, const char *fmt, ...);
void mg_rpc_vok(struct mg_rpc_req *, const char *fmt, va_list *ap);
```

+ 参数：
  + req -- 一个请求
  + fmt -- 使用printf语义格式化的字符串

+ 示例：
```cpp
static void rpc_sum(struct mg_rpc_req *r) {
  double a = 0.0, b = 0.0;
  mg_json_get_num(r->frame, "$.params[0]", &a);
  mg_json_get_num(r->frame, "$.params[1]", &b);
  mg_rpc_ok(r, "%g", a + b);
}
```

## mg_rpc_err, mg_rpc_verr

+ 简介：
  + 打印错误帧的辅助函数

+ 原型：
```cpp
void mg_rpc_err(struct mg_rpc_req *, int code, const char *fmt, ...);
void mg_rpc_verr(struct mg_rpc_req *, int code, const char *fmt, va_list *);
```

+ 参数：
  + req -- 一个请求
  + fmt -- 使用printf语义格式化的字符串

+ 示例：
```cpp
static void rpc_dosome(struct mg_rpc_req *r) {
  ...
  mg_rpc_err(r, -32109, "\"%.*s not found\"", len, &r->frame.ptr[offset]);
}
```

## mg_rpc_list 

+ 简介：
  + 内置RPC方法，用于列出所有已注册的RPC方法。该函数通常不直接调用，而是作为方法注册。

+ 原型：
```cpp
void mg_rpc_list(struct mg_rpc_req *r);
```

+ 参数：
  + req -- 一个请求

+ 示例：
```cpp
mg_rpc_add(&s_rpc_head, mg_str("rpc.list"), mg_rpc_list, &s_rpc_head);
```