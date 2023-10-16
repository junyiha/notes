
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
        "?image":"图像base64字符串",
        "image":"string",
        "?image_height": "图像高度",
        "image_height": 1920,
        "?image_width": "图像宽度",
        "image_width": 1080,
        "?camera_offset":"相机标定中的坐标系的偏移量(相机基坐标点相对于机械臂基坐标点)",
        "camera_offset":{
            "x":0.558303,
            "y":-0.0101538,
            "z":1.44008
        },
        "?image_real_height":"对应真实世界的长度",
        "image_real_height":2.12,
        "?image_real_width":"对应真实世界的宽度",
        "image_real_width":1.989,
        "point_array":[
            {
              "?index":"目标结构化数据索引",
              "index":0,
              "?box":"图像检测框结构化信息",
              "box":{
                  "x":667,
                  "y":481,
                  "w":215,
                  "h":202,
                  "rotation_z":0
              },
              "?cart":"位置数据, 输出格式为 米",
              "cart": {
                  "x":1,
                  "y":2,
                  "z":3
              },
              "?rot":"姿态数据, 输出格式为 欧拉角 单位为角度",
              "rot": {
                  "rx":4,
                  "ry":5,
                  "rz":6
              },
              "?object_attribute":"目标的物理属性，宽度，长度，高度",
              "?object_attribute":{
                    "width":1.1,
                    "height":2.2,
                    "depth":3.3
              },
              "?cloud":"点云数据",
              "cloud":[
                    {
                        "x":1,
                        "y":2,
                        "z":3
                    }
                    {
                        "x":1,
                        "y":2,
                        "z":3
                    }
              ]
            },
            {
              "?index":"目标结构化数据索引",
              "index":1,
              "?box":"图像检测框结构化信息",
              "box":{
                  "x":667,
                  "y":481,
                  "w":215,
                  "h":202,
                  "rotation_z":0
              },
              "?cart":"位置数据, 输出格式为 米",
              "cart": {
                  "x":1,
                  "y":2,
                  "z":3
              },
              "?rot":"姿态数据, 输出格式为 欧拉角  单位为角度",
              "rot": {
                  "rx":4,
                  "ry":5,
                  "rz":6
              },
              "?object_attribute":"目标的物理属性，宽度，长度，高度",
              "?object_attribute":{
                    "width":1.1,
                    "height":2.2,
                    "depth":3.3
              },
              "?cloud":"点云数据",
              "cloud":[
                    {
                        "x":1,
                        "y":2,
                        "z":3
                    }
                    {
                        "x":1,
                        "y":2,
                        "z":3
                    }
              ]
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

