---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_websocket
tag: Mongoose
---
## 简介

+ websocket相关函数

## struct mg_ws_message

+ 简介：
  + 该结构代表Websocket消息。这个`flag`元素对应于`RFC 6455`第5.2节中所述的第一个字节。(`https://www.rfc-editor.org/rfc/rfc6455#section-5.2`)

+ 原型：
```cpp
struct mg_ws_message {
  struct mg_str data; // WebSocket message data
  uint8_t flags;      // WebSocket message flags
};
```

## websocket message type

+ 简介：
  + 要从传入消息中提取消息类型，在结构体`mg_ws_message`的`flag`元素中检查四个`LSBs`

+ 可能存在的WebSocket消息类型：
```cpp
#define WEBSOCKET_OP_CONTINUE 0
#define WEBSOCKET_OP_TEXT 1
#define WEBSOCKET_OP_BINARY 2
#define WEBSOCKET_OP_CLOSE 8
#define WEBSOCKET_OP_PING 9
#define WEBSOCKET_OP_PONG 10
```

+ 示例：
```cpp
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_WS_MSG) {
    struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
    msgtype = wm->flags & 0x0F;
    if (msgtype == WEBSOCKET_OP_BINARY) {
      // This is a binary data message
    } else if (msgtype == WEBSOCKET_OP_TEXT) {
      // This is a text data message
    }
  }
}
```

+ 注：
  + 当调用`mg_ws_send()`或`ms_ws_printf()`发送消息时，请使用`RFC 6455`第5.6节中所述的正确消息类型进行数据帧(`https://www.rfc-editor.org/rfc/rfc6455#section-5.6`)

---

## mg_ws_connect 

+ 简介：
  + 创建客户端Websocket连接。这个函数不能连接到对端，它仅仅分配需要的资源和启动连接进程。当对端真正连接好了，会向连接事件处理函数发送一个`MG_EV_CONNECT`事件

+ 原型：
```cpp
struct mg_connection *mg_ws_connect(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn, void *fn_data, const char *fmt, ...);
```

+ 参数：
  + `mgr`  --  使用的事件管理结构体
  + `url`  --  指定的远程URL。例如：`http://google.com`
  + `fn`   --  一个事件处理函数
  + `fn_data`  --  一个任意指针，当事件处理函数被调用时，它会被作为`fn_data`传递。这个指针作为`c->fn_data`存储在连接结构体中

+ 返回值：
  + 返回一个指向创建的连接
  + 返回NULL表示错误

+ 示例
```cpp
struct mg_connection *c = mg_ws_connect(&mgr, "ws://test_ws_server.com:1000",
                                        handler, NULL, "%s", "Sec-WebSocket-Protocol: echo\r\n");
if(c == NULL) fatal("Cannot create connection");
``` 

---

## mg_ws_upgrade

+ 简介：
  + 升级给定HTTP连接到Websocket。`fmt`是一个类似于`printf()`格式的字符串，用于额外的HTTP标头，返回给Websocket握手的客户端。如果不需要额外的标头，将`fmt`设置为空

+ 原型：
```cpp
void mg_ws_upgrade(struct mg_connection *c, struct mg_http_message *, const char *fmt, ...);
```

+ 参数：
  + `c`    --  使用的连接
  + `hm`   --  HTTP消息
  + `fmt`  --  类似于`printf`的格式字符串，用于附加`HTTP`标头或为null

+ 返回值：
  + 无

+ 示例：
```cpp
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    mg_ws_upgrade(c, hm, NULL);  // Upgrade HTTP to WS
  }
}
``` 

---

## mg_ws_send

+ 简介：
  + 向WebSocket对端发送数据

+ 原型：
```cpp
size_t mg_ws_send(struct mg_connection *c, const void *buf, size_t len, int op);
```

+ 参数：
  + `c`  --  使用的连接
  + `buf`  --  需要发送的数据
  + `len`  --  需要发送的数据大小
  + `op`   --  WebSocket消息类型，参见WebSocket message type

+ 返回值：
  + 返回发送的字节数

+ 示例：
```cpp
// Mongoose events handler
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_WS_OPEN) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    mg_ws_send(c, "opened", 6, WEBSOCKET_OP_BINARY);  // Send "opened" to web socket connection
  }
}
``` 
---

## mg_ws_printf, mg_ws_vprintf

+ 简介：
  + 和`ms_ws_send()`相同，但是使用`printf()`语义格式化数据

+ 原型：
```cpp
size_t mg_ws_printf(struct mg_connection *, int op, const char *fmt, ...);
size_t mg_ws_vprintf(struct mg_connection *, int op, const char *fmt, va_list *);
```

+ 参数：
  + `c`   --  使用的连接
  + `op`  --  WebSocket消息类型，参见WebSocket message type
  + `fmt` --  使用`printf()`语义格式化的字符串

+ 返回值：
  + 返回发送的字节数

+ 示例:
```cpp
mg_ws_printf(c, WEBSOCKET_OP_TEXT, "Hello, %s!", "world");
```

---

## mg_ws_wrap 

+ 简介：
  + 将输出缓冲区中的数据转换为Websocket格式。有用然后通过WebSocket实施协议。具体示例参见`examples/mqtt-over-ws-client`

+ 原型：
```cpp
size_t mg_ws_wrap(struct mg_connection *c, size_t len, int op)
```

+ 参数：
  + `c`  --  使用的连接
  + `len`  --  转换的字节数
  + `op`   --  WebSocket消息类型

+ 返回值：
  + 返回连接结构体中输出缓冲区新的大小

+ 示例:
```cpp
size_t len = c->send.len;         // Store output buffer len
mg_mqtt_login(c, s_url, &opts);   // Write MQTT login message
mg_ws_wrap(c, c->send.len - len, WEBSOCKET_OP_BINARY); // Wrap it into WS
``` 