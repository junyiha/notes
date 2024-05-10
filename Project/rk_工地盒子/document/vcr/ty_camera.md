## 相机接口

### 初始化相机

+ 方法：GET
+ 路径：/api/cameras/tycamera/init

+ 成功响应
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应
```json
{
    "code":-1,
    "data":null,
    "message":"(错误信息)"
}
```

### 打开相机

+ 方法：GET
+ 路径：/api/cameras/tycamera/open

+ 成功响应
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应
```json
{
    "code":-1,
    "data":null,
    "message":"(错误信息)"
}
```

### 关闭相机

+ 方法：GET
+ 路径：/api/cameras/tycamera/close

+ 成功响应
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应
```json
{
    "code":-1,
    "data":null,
    "message":"(错误信息)"
}
```

### 反初始化相机

+ 方法：GET
+ 路径：/api/cameras/tycamera/uninit

+ 成功响应
```json
{
    "code":0,
    "data":null,
    "message":"成功"
}
```

+ 失败响应
```json
{
    "code":-1,
    "data":null,
    "message":"(错误信息)"
}
```