---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_url
tag: Mongoose
---
## 简介

+ mongoose关于URL的函数

## mg_url_port 

+ 简介：
  + 根据给定的URL返回端口

+ 原型：
```cpp
unsigned short mg_url_port(const char *url);
```

+ 参数：
  + url -- 需要提取端口号的URL

+ 返回值：
  + 成功，返回给定URL的端口号
  + 失败，如果URL不包含端口并且URL协议没有默认端口，则为0

+ 示例：
```cpp
unsigned short port1 = mg_url_port("https://myhost.com") // port1 is now 443 (default https port)
unsigned short port2 = mg_url_port("127.0.0.1:567") // port2 is now 567
```

## mg_url_is_ssl 

+ 简介：
  + 检查给定的URL是否使用加密方案

+ 原型：
```cpp
int mg_url_is_ssl(const char *url);
```

+ 参数：
  + url -- 需要检查的URL

+ 返回值：
  + 如果URL使用了加密方案，返回0
  + 如果没有，则返回非0

+ 示例：
```cpp
if (mg_url_is_ssl("https://example.org") == 0) {
  // scheme is encrypted
}
```

## mg_url_host 

+ 简介：
  + 从给定的URL中提取主机名。

+ 原型：
```cpp
struct mg_str mg_url_host(const char *url);
```

+ 参数：
  + url -- 一个URL字符串

+ 返回值：
  + 主机名

+ 示例：
```cpp
struct mg_str a = mg_url_host("https://my.example.org:1234"); // a == "my.example.org"
struct mg_str b = mg_url_host("tcp://[::1]"); // b == "[::1]"
```

## mg_url_user 

+ 简介：
  + 从给定的URL中提取用户名。

+ 原型：
```cpp
struct mg_str mg_url_user(const char *url);
```

+ 参数：
  + url -- 需要提取用户名的URL

+ 返回值：
  + 成功，返回用户名
  + 失败，返回空的字符串

+ 示例：
```cpp
struct mg_str user_name = mg_url_user("https://user@password@my.example.org"); // user_name is now "user"
```

## mg_url_pass 

+ 简介：
  + 从给定的URL中提取密码

+ 原型：
```cpp
struct mg_str mg_url_pass(const char *url);
```

+ 参数：
  + url -- 需要提取密码的URL

+ 返回值：
  + 成功，返回密码
  + 失败，返回空的字符串

+ 示例：
```cpp
struct mg_str pwd = mg_url_user("https://user@password@my.example.org"); // pwd is now "password"
```

## mg_url_uri 

+ 简介：
  + 从给定的URL中提取URI。注意，函数返回url内的指针；不需要明确地free()它。

+ 原型：
```cpp
const char *mg_url_uri(const char *url);
```

+ 参数：
  + url -- 需要提取URI的URL

+ 返回值：
  + 成功，返回URI字符串
  + 失败，返回 `\`

+ 示例：
```cpp
const char *uri = mg_url_uri("https://example.org/subdir/subsubdir"); // `uri` is now pointer to "subdir/subsubdir"
```