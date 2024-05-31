---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_tls
tag: Mongoose
---
## 简介

+ TLS(Transport Layer Security)，是一种用于保护网络通信安全性的加密协议。它建立在传输层协议(例如TCP)之上，用于在客户端和服务器之间创建安全的通信通道

## struct mg_tls_opts

+ 简介：
  + TLS初始化结构

+ 原型：
```cpp
struct mg_tls_opts {
  const char *ca;        // CA certificate file. For both listeners and clients
  const char *crl;       // Certificate Revocation List. For clients
  const char *cert;      // Certificate
  const char *certkey;   // Certificate key
  const char *ciphers;   // Cipher list
  struct mg_str srvname; // If not empty, enables server name verification
  struct mg_fs *fs;      // FS API for reading certificate files
};
```

+ 参数：
  + ca -- 证书颁发机构。可以是文件名或字符串。用于验证另一端发送给我们的证书。如果为空，则禁用证书检查。
  + crl -- 证书吊销列表。可以是文件名或字符串。用于验证另一端发送给我们的证书。如果为空，则禁用证书吊销检查。
  + cert -- 我们自己的证书。可以是文件名或字符串。如果为NULL，则不与对方进行认证。
  + certkey -- 证书的密钥。有时，证书和它的密钥绑定在一个.pem文件中，在这种情况下，cert和certkey的值可能是相同的
  + ciphers -- 允许使用的密码列表
  + srvname -- 启用服务器名称验证

+ 注：
  + 如果ca和cert都设置了，那么所谓的双向TLS就启用了，这时双方都要互相验证。通常，服务器端连接同时设置ca和cert，而客户端只设置ca。

## mg_tls_init 

+ 简介：
  + 在给定连接上初始化TLS

+ 原型：
```cpp
void mg_tls_init(struct mg_connection *c, struct mg_tls_opts *opts);
```

+ 参数：
  + c -- 需要初始化TLS的连接
  + opts -- TLS初始化参数

+ 返回值：
  + 无

+ 示例：
```cpp
struct mg_tls_opts opts = {.cert = "ca.pem"};
mg_tls_init(c, &opts);
```

+ 注：
  + mbedTLS使用mg_random作为RNG。mg_random可以通过设置MG_ENABLE_CUSTOM_RANDOM=1并定义自己的mg_random()实现来覆盖。