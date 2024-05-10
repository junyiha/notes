
## 检测器

### 初始化检测器

+ 方法：GET
+ 路径：/api/detectors/detector/init

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

### 检测一帧图片

+ 方法：GET
+ 路径：/api/detectors/detector/detect

+ 成功响应
```json
{
    "code":0,
    "data":{
        "point_array":[
            {
                "rx":-0.01703958989179134,
                "ry":2.861906422352928,
                "rz":-0.19738513912341824,
                "x":0.012879030038020094,
                "y":-0.43891458463458,
                "z":0.0841377863535
            }
        ]
    },
    "message":"成功"
}
```
+ 注
  + x,y,z 为目标的中心点坐标
  + rx,ry,rz 为目标的姿态信息

+ 失败响应
```json
{
    "code":-1,
    "data":null,
    "message":"(错误信息)"
}
```

+ 没有检测到目标
```json
{
    "code":0,
    "data":{
        "message":"没有检测框",
        "point_array":[]
    },
    "message":"成功"
}
```

### 关闭检测器

+ 方法：GET
+ 路径：/api/detectors/detector/close

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

