## 电动吸盘接口

+ 注：
  + data ： 先占位

### 打开

+ 方法：GET
+ 路径：/api/tools/sucker/open

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
    "message":"错误信息"
}
```

### 关闭

+ 方法：GET 
+ 路径：/api/tools/sucker/close

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
    "message":"错误信息"
}
```

### 启动

+ 方法：GET
+ 路径：/api/tools/sucker/start

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
    "message":"错误信息"
}
```

### 停止

+ 方法：GET
+ 路径：/api/tools/sucker/stop

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
    "message":"错误信息"
}
```

### 检测是否抓取到工件

+ 方法:GET 
+ 路径:/api/tools/sucker/isCaptured

+ 抓取到工件
```json
{
    "code":0,
    "data":null,
    "message":"抓取到工件"
}
```

+ 未抓取到工件
```json
{
    "code":6007,
    "data":null,
    "message":"未抓取到工件"
}
```

+ 访问设备失败
```json
{
    "code":6006,
    "data":null,
    "message":"failed to get information of electric sucker device"
}
```

