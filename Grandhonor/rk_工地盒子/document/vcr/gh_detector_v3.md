
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
    "message":"成功",
    "data":{
        "point_array":[
            {
              "?cart":"位置数据, 输出格式为 米",
              "cart": {
                  "x":1,
                  "y":2,
                  "z":3
              },
              "?rot":"姿态数据, 输出格式为 轴角",
              "rot": {
                  "rx":4,
                  "ry":5,
                  "rz":6
              }
            },
            {
              "?cart":"位置数据, 输出格式为 米",
              "cart": {
                  "x":1,
                  "y":2,
                  "z":3
              },
              "?rot":"姿态数据, 输出格式为 轴角",
              "rot": {
                  "rx":4,
                  "ry":5,
                  "rz":6
              }
            }
        ]
    }
}
```
+ 注
  + cart为目标的中心点坐标
  + rot 为目标的姿态信息

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

