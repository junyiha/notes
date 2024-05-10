## Beijing 机械臂接口

+ 登录设备即连接设备
+ 注
  + 响应数据中 data 键对应的值为机械臂服务返回的数据

### 打开

+ 方法：POST
+ 路径：/api/robots/beijing/open
+ 请求数据：
```json
{
    "username":"admin(字符串)",
    "passwd":"123456(字符串)"
}
```

+ 成功响应
```json
{
    "code":0,
    "data":{
        "STATUS":"SUCCESS"
    },
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

+ 注
  + 连接设备：目前想法为机械臂服务登录成功，表示连接设备成功

### move joint(关节空间运动指令)

+ 方法：POST
+ 路径：/api/robots/beijing/moveJoint
+ 请求数据：
```json
{
    "space": "jointSpace(字符串)",
    "speed": 50,
    "point": [
        0,
        0,
        0,
        0,
        0,
        0
    ]
}
```
+ 注
  + 请求的数据目前单位为 弧度

+ 成功请求响应
```json
{
    "code":0,
    "data":{
        "STATUS":"SUCCESS"
    },
    "message":"成功"
}
```

+ 失败请求响应
```json
{
    "code":-1,
    "data":null,
    "message":"错误信息"
}
```

+ 执行指令失败响应
```json
{
    "code":0,
    "data":{
        "STATUS":"FAIL"
    },
    "message":"成功"
}
```

### move line(笛卡尔空间运动指令)

+ 方法：POST
+ 路径：/api/robots/beijing/moveLine
+ 请求数据：
```json
{
    "space": "tcpSpace(字符串)",
    "point": [
		0.012879,
		-0.438915,
		0.0841378,
		-0.0170369,
		2.86191,
		-0.197385
    ]
}
```
+ 注
  + 目前单位 ： 
    + xyz 单位为 米
    + rx,ry,rz 单位为 弧度

+ 成功响应
```json
{
    "code":0,
    "data":{
        "STATUS":"SUCCESS"
    },
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

+ 执行指令失败响应
```json
{
    "code":0,
    "data":{
        "STATUS":"FAIL"
    },
    "message":"成功"
}
```

### 拖动示教模式

+ 方法：POST
+ 路径：/api/robots/beijing/dragMode
+ 请求数据：
  + drag为 true  进入拖动示教模式
  + drag为 false 退出拖动示教模式
```json
{
    "drag": true,
    "mode": [
        8,
        8,
        8,
        8,
        8,
        8
    ]
}
```

+ 成功响应
```json
{
    "code":0,
    "data":{
        "STATUS":"SUCCESS"
    },
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

+ 执行指令失败响应
```json
{
    "code":0,
    "data":{
        "STATUS":"FAIL"
    },
    "message":"成功"
}
```

### 获取当前坐标点

+ 方法：GET
+ 路径：/api/robots/beijing/getPoint

+ 成功响应
```json
{
    "code":0,
    "data":{
        "CartInfo":[
            0.06573017199841043,
            -0.18093039602297886,
            0.6714999842590678,
            1.5707963497743604,
            3.1413529690927877,
            0.34917237684522284
        ],
        "JointInfo":[
            0.34907650304322624,
            0.000335558297349984,
            0.00023968449810713143,
            0.00014381069886427886,
            0.00009587379924285257,
            0
        ],
        "STATUS":"SUCCESS"
    },
    "message":"成功"
}
```
+ 注
  + 获取的关节角单位为 弧度
  + 获取的笛卡尔坐标 xyz位置 单位为米， rpy姿态 单位为欧拉角

+ 失败响应
```json
{
    "code":-1,
    "data":null,
    "message":"错误信息"
}
```

+ 执行指令失败响应
```json
{
    "code":0,
    "data":{
        "STATUS":"FAIL"
    },
    "message":"成功"
}
```

