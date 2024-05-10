## 简介

+ 工作平台设备控制接口
+ 传送带设备控制接口

## 打开设备

+ 方法：GET 
+ 路径：/api/platforms/relays/open

+ 成功响应:
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应:
```json
{
    "code":-1,
    "data":null,
    "message":"失败"
}
```

## 关闭设备

+ 方法：GET 
+ 路径：/api/platforms/relays/close

+ 成功响应:
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应:
```json
{
    "code":-1,
    "data":null,
    "message":"失败"
}
```

## 启动设备

+ 方法：GET 
+ 路径：/api/platforms/relays/start

+ 成功响应:
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应:
```json
{
    "code":-1,
    "data":null,
    "message":"失败"
}
```

## 停止设备

+ 方法：GET 
+ 路径：/api/platforms/relays/stop

+ 成功响应:
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应:
```json
{
    "code":-1,
    "data":null,
    "message":"失败"
}
```