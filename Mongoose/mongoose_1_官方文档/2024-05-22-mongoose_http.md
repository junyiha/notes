---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_http
tag: Mongoose
---
## 简介

+ mongoose 中http相关api笔记


## struct mg_http_header

+ 简介：
  + 结构代表HTTP标头，像`Content-Type: text/html`。`Content-Type` 是一个 Header name，`text/html/`是一个 Header value

+ 原型
```c
struct mg_http_header {
  struct mg_str name;   // Header name
  struct mg_str value;  // Header value
};
```

---

## struct mg_http_message

+ 简介：
  + 结构代表HTTP消息。

+ 原型
```c
struct mg_http_message {
  struct mg_str method, uri, query, proto;             // Request/response line
  struct mg_http_header headers[MG_MAX_HTTP_HEADERS];  // Headers
  struct mg_str body;                                  // Body
  struct mg_str message;                               // Request line + headers + body
};
```

---

## mg_http_listen 

+ 简介：
  + 创建HTTP侦听器。

+ 原型
```c
struct mg_connection *mg_http_listen(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data);
```

+ 参数：
  + mgr : 一个事件管理结构体
  + url : 一个URL，指定监听的本地IP地址和端口。例如：`http://0.0.0.0:8000`
  + fn : 一个事件处理函数
  + fn_data : 一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中

+ 返回值：
  + 成功，返回一个指向创建的连接指针
  + 失败，返回NULL

+ 示例
```c
struct mg_connection *c = mg_http_listen(&mgr, "0.0.0.0:8000", fn, arg);
if (c == NULL) fatal_error("Cannot create listener");
```

---

## mg_http_connect

+ 简介
  + 创建HTTP客户端连接。这个函数不能连接到对端，它仅仅分配需要的资源和启动连接进程。当对端真正连接好了，会向连接事件处理函数发送一个`MG_EV_CONNECT`事件

+ 原型：
```c
struct mg_connection *mg_http_connect(struct mg_mgr *, const char *url, mg_event_handler_t fn, void *fn_data);
```

+ 参数：
  + mgr : 一个事件管理结构体
  + url : 一个URL，指定监听的本地IP地址和端口。例如：`http://0.0.0.0:8000`
  + fn : 一个事件处理函数
  + fn_data : 一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中

+ 返回值：
  + 成功，返回一个指向创建的连接指针
  + 失败，返回NULL

+ 示例
```c
struct mg_connection *c = mg_http_connect(&mgr, "http://google.com", fn, NULL);
if (c == NULL) fatal_error("Cannot create connection");
```

---

## mg_http_status 

+ 简介：
  + 获取HTTP响应的状态代码。

+ 原型
```c
int mg_http_status(const struct mg_http_message *hm);
```

+ 参数：
  + hm : 需要解析的HTTP响应

+ 返回值：
  + 返回状态码，例如：200表示成功

---

## mg_http_get_request_len 

+ 简介：
  + 获取请求的长度。请求的长度是直到HTTP头结束的字节数。它不包括HTTP请求体的长度

+ 原型
```c
int mg_http_get_request_len(const unsigned char *buf, size_t buf_len);
```

+ 参数：
  + buf : 指向存放请求数据的缓冲区的指针
  + buf_len : 缓冲区大小

+ 返回值：
  + 成功，返回请求的长度
  + 0, 消息不完整
  + -1， 错误

+ 示例：
```c
const char *buf = "GET /test \n\nGET /foo\n\n";
int req_len = mg_http_get_request_len(buf, strlen(buf));  // req_len == 12
```

---

## mg_http_parse

+ 简介：
  + 解析请求报文字符串，并存入到`mg_http_message`结构体中

+ 原型：
```c
int mg_http_parse(const char *s, size_t len, struct mg_http_message *hm);
```

+ 参数：
  + s : 一个请求字符串
  + len : 请求字符串的长度
  + hm : 存储解析请求报文结果的结构体指针

+ 返回值：
  + 返回请求报文的长度

+ 示例
```c
struct mg_http_message hm;
const char *buf = "GET / HTTP/1.0\n\n";
if (mg_http_parse(buf, strlen(buf), &hm) > 0) { /* success */ }
```

---

## mg_http_printf_chunk

+ 简介：
  + 使用`printf()`语义，写一个块编码的块数据。(Write a chunk of data in chunked encoding format, using printf() semantic)

+ 原型：
```c
void mg_http_printf_chunk(struct mg_connection *c, const char *fmt, ...);
```

+ 参数：
  + c : 一个连接指针
  + fmt : 以`printf()`语义的字符串

+ 返回值：
  + 无

+ 示例
```c
mg_http_printf_chunk(c, "Hello, %s!", "world");
```

---

## mg_http_write_chunk 

+ 简介：
  + 写入一个块编码格式的块数据(Write a chunk of data in chunked encoding format.)

+ 原型
```c
void mg_http_write_chunk(struct mg_connection *c, const char *buf, size_t len);
```

+ 参数：
  + c : 一个连接指针
  + buf : 需要写入的数据
  + len : 写入数据的长度

+ 返回值：
  + 无

+ 示例：
```c
mg_http_write_chunk(c, "hi", 2);
```

---

## mg_http_delete_chunk 

+ 简介：
  + 从输入缓冲区中删除指定的块(chunk)

+ 原型：
```c
void mg_http_delete_chunk(struct mg_connection *c, struct mg_http_message *hm);
```

+ 参数：
  + c : 连接指针
  + hm : 需要删除的块(chunk)

+ 返回值：
  + 无

+ 示例
```c
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_CHUNK) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    mg_http_delete_chunk(c, hm); // Remove received chunk
  }
}
```

---

## struct mg_http_serve_opts

+ 简介：
  + 传递给`mg_http_serve_dir()`和`mg_http_serve_file()`的结构，该结构驱动了这两个函数的行为

+ 原型
```c
struct mg_http_serve_opts {
  const char *root_dir;       // Web root directory, must be non-NULL
  const char *ssi_pattern;    // SSI file name pattern, e.g. #.shtml
  const char *extra_headers;  // Extra HTTP headers to add in responses
  const char *mime_types;     // Extra mime types, ext1=type1,ext2=type2,..
  const char *page404;        // Path to the 404 page, or NULL by default
  struct mg_fs *fs;           // Filesystem implementation. Use NULL for POSIX
};
```

---

## mg_http_serve_dir 

+ 简介：
  + 根据给定选项服务多个静态文件。文件也可以被压缩,包括目录索引。所有压缩文件都必须以.gz结尾，并且不得在没有扩展名的情况下存在具有相同名称的文件，否则将优先考虑

+ 原型：
```c
void mg_http_serve_dir(struct mg_connection *c, struct mg_http_message *hm, const struct mg_http_serve_opts *opts);
```

+ 参数：
  + c : 使用的连接
  + hm : 应该被服务的HTTP消息
  + opts : 服务选项。请注意，`opts.root_dir`可以选择接受额外的逗号分隔`uri=path`

+ 返回值：
  + 无

+ 示例：
```c
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    struct mg_http_serve_opts opts;
    memset(&opts, 0, sizeof(opts));
    opts.root_dir = "/var/www,/conf=/etc";  // Serve /var/www. URIs starting with /conf are served from /etc
    mg_http_serve_dir(c, hm, &opts);
  }
}
```

---

## mg_http_serve_file 

+ 简介：
  + 服务一个静态文件。如果不存在带有路径中指定的文件名的文件，则Mongoose尝试附加`.gz`；如果存在这样的文件，它将使用`Content-Encoding: gzip` header 去服务

+ 原型:
```c
void mg_http_serve_file(struct mg_connection *c, struct mg_http_message *hm, const char *path, struct mg_http_serve_opts *opts);
```

+ 参数：
  + c : 使用连接
  + hm : 需要服务的HTTP消息
  + path : 需要服务的文件路径
  + opts : 服务选项

+ 返回值：
  + 无

+ 示例：
```c
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    struct mg_http_serve_opts opts = {
      .mime_types = "png=image/png",
      .extra_headers = "AA: bb\r\nCC: dd\r\n"
    };
    mg_http_serve_file(c, hm, "a.png", &opts);
  }
}
```

---

## mg_http_reply

+ 简介：
  + 通过使用`printf()`语义发送简单的HTTP响应。这个函数根据`body_fmt`格式化响应体(response body)，然后自动追加到一个正确的`Content-Length`头(header)。额外的`headers`需要通过`headers`参数传递

+ 原型：
```c
void mg_http_reply(struct mg_connection *c, int status_code, const char *headers, const char *body_fmt, ...);
```

+ 参数：
  + c : 一个连接
  + status_code : 一个HTTP响应状态码
  + headers : 额外的headers，默认为NULL，如果不是空，则必须以`\r\n`结尾
  + fmt : 使用`printf`语义，需要格式化成HTTP body的字符串

+ 返回值：
  + 无

+ 示例：
```c
// 发送一个简单的JSON响应：
mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"result\": %d}", 123);
// 发送一个302重定向：
mg_http_reply(c, 302, "Location: /\r\n", "");
// 发送一个错误
mg_http_reply(c, 403, "", "%s", "Not Authorized\n");
```

---

## mg_http_get_header

+ 简介：
  + 获取HTTP header值

+ 原型：
```c
struct mg_str *mg_http_get_header(struct mg_http_message *hm, const char *name);
```

+ 参数：
  + hm : 需要寻找 header 的HTTP消息
  + name : Header name

+ 返回值：
  + 成功，HTTP header
  + 失败，NULL

+ 示例：
```c
// Mongoose event handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    struct mg_str *s = mg_http_get_header(hm, "X-Extra-Header");
    if (s != NULL) {
      mg_http_reply(c, 200, "", "Holly molly! Header value: %.*s", (int) s->len, s->ptr);
    } else {
      mg_http_reply(c, 200, "", "Oh no, header is not set...");
    }
  }
}
```

---

## mg_http_get_header_var 

+ 简介：
  + 解析具有表格`name1=value1; name=value2;...`的HTTP header，并获取一个给定的变量

+ 原型：
```c
struct mg_str mg_http_get_header_var(struct mg_str s, struct mg_str v);
```

+ 参数：
  + s : HTTP header
  + name : 变量名字

+ 返回值：
  + 成功，一个请求的变量
  + 失败，一个空的字符串

+ 示例：
```c
struct mg_str *cookie = mg_http_get_header(hm, "Cookie");
struct mg_str token = mg_str("");

if (cookie != NULL) {
  token = mg_http_get_header_var(*cookie, mg_str("access_token"));
}
```

---

## mg_http_var 

+ 简介：
  + 获取未编码的HTTP变量

+ 原型：
```c
struct mg_str mg_http_var(struct mg_str buf, struct mg_str name);
```

+ 参数：
  + buf : 一个url编码的字符串：HTTP请求体或查询字符串(HTTP request body or query string)
  + name : 获取的变量名字

+ 返回值：
  + 成功，返回变量的值
  + 失败，返回一个空字符串

+ 示例：
```c
// We have received a request to /my/uri?a=b&c=d%20
// The hm->query points to "a=b&c=d%20"
struct mg_str v = mg_http_var(hm->query, mg_str("c"));  // v = "d%20"
```

---

## mg_http_get_var

+ 简介：
  + 获取并解码HTTP 变量

+ 原型：
```c
int mg_http_get_var(const struct mg_str *var, const char *name, char *buf, int len);
```

+ 参数：
  + var : HTTP请求体(HTTP request body)
  + name : 变量名
  + buf : 写入解码变量的缓冲区(Buffer to write decoded variable)
  + len : 缓冲区大小

+ 返回值：
  + 成功，解码变量的长度， 0
  + 失败，返回负数

+ 示例：
```c
char buf[100] = "";
mg_http_get_var(&hm->body, "key1", buf, sizeof(buf)) {
  ...
}
```

---

## mg_http_creds 

+ 简介：
  + 从请求获取身份验证证书，然后将它存储到`user`, `userlen`, `pass`, `passlen`缓冲区中。

+ 原型：
```c
void mg_http_creds(struct mg_http_message *hm, char *user, size_t userlen, char *pass, size_t passlen);
```

+ 参数：
  + hm : 需要查找证书的HTTP 消息
  + user : 接收用户名字的缓冲区
  + userlen : user缓冲区的大小
  + pass : 接收密码的缓冲区
  + passlen : pass缓冲区的大小

+ 返回值：
  + 无

+ 示例：
```c
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    char user[100], pass[100];
    mg_http_creds(hm, user, sizeof(user), pass, sizeof(pass)); // "user" is now user name and "pass" is now password from request
  }
}
```

---

## mg_http_match_uri 

+ 简介：
  + 检查在HTTP请求报文中，是否有和给定的`glob`字符串相匹配的字符串

+ 原型：
```c
bool mg_http_match_uri(const struct mg_http_message *hm, const char *glob);
```

+ 参数：
  + hm : 需要匹配检索的HTTP消息
  + glob : 匹配的字符串

+ 返回值：
  + 成功，true 
  + 失败，false

+ 示例：
```c
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_http_match_uri(hm, "/secret")) {
      mg_http_reply(c, 200, NULL, "Very big secret!");
    } else {
      mg_http_reply(c, 200, NULL, "hello world..");
    }
  }
}
```

---

## mg_http_bauth 

+ 简介：
  + 将一个基本的`Authorization` header写入到输出缓冲区

+ 原型：
```c
void mg_http_bauth(struct mg_connection *c, const char *user, const char *pass);
```

+ 参数：
  + c : 使用的连接
  + user : 用户名
  + pass : 密码

+ 返回值：
  + 无

+ 示例：
```c
mg_printf(c, "POST /v1/subscriptions HTTP/1.1\r\n"
             "Host: api.stripe.com\r\n"
             "Transfer-Encoding: chunked\r\n");
mg_http_bauth(c, stripe_private_key, NULL);     // Add Basic auth header
mg_printf(c, "%s", "\r\n");                     // End HTTP headers

mg_http_printf_chunk(c, "&customer=%s", customer_id);   // Set customer
mg_http_printf_chunk(c, "&items[0][price]=%s", price);  // And price
mg_http_printf_chunk(c, "");                            // End request
```

---

## struct mg_http_part 

+ 简介：
  + 描述HTTP 多个消息(multipart message)中单个部分的结构体

+ 原型：
```c
// Parameter for mg_http_next_multipart
struct mg_http_part {
  struct mg_str name;      // Form field name
  struct mg_str filename;  // Filename for file uploads
  struct mg_str body;      // Part contents
};
```

---

## mg_http_next_multipart 

+ 简介：
  + 根据给定的`offset`，在`body`中解析multipart chunk。一个初始的`offset`应该为0.在提供的`part`中填充参数，可能为空。返回下一块的offsete，或者返回0表示没有其他块(chunks)

+ 原型：
```c
size_t mg_http_next_multipart(struct mg_str body, size_t offset, struct mg_http_part *part);
```

+ 参数：
  + body : 消息体
  + offset : 开始偏移量
  + part : 指向需要填充的`struct mg_http_part`结构体

+ 返回值：
  + 成功，返回下一块的offset
  + 失败，返回0，或者表示没有其他块

+ 示例：
```c
struct mg_http_part part;
size_t pos = 0;

while ((pos = mg_http_next_multipart(body, pos, &part)) != 0) {
  // Use part
}
```

---

## mg_http_upload 

+ 简介：
  + 这是一个助手实用程序功能，用于通过小块上传大型文件。将HTTP POST 数据追加到指定目录的文件中。文件名和文件偏移由查询字符串参数指定:`POST /upload?name=firmware.bin&offset=2048 HTTP/1.1`。如果偏移量为0，则将文件截断。客户的责任是将文件分为较小的块，并发送一系列由此功能处理的POST请求

+ 原型：
```c
int mg_http_upload(struct mg_connection *c, struct mg_http_message *hm, struct mg_fs *fs, const char *path, size_t max_size);
```

+ 参数：
  + c : 一个连接
  + hm : 一个需要被解析的HTTP message
  + fs : 需要写文件的文件系统，例如：`&mg_fs_posix`
  + path : 一个文件名
  + max_size : 允许的文件大小的最大值

+ 返回值：
  + 成功，返回文件的大小
  + 失败，返回一个负数

+ 示例：
```c
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_http_match_uri(hm, "/upload")) {
      mg_http_upload(c, hm, &mg_fs_posix, "/tmp/myfile.bin", 99999);
    } else {
      struct mg_http_serve_opts opts = {.root_dir = "."};   // Serve
      mg_http_serve_dir(c, ev_data, &opts);                 // static content
    }
  }
}
```