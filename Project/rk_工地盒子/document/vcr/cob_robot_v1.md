## Cob 机械臂接口

+ 登录设备即连接设备
+ 注
  + 响应数据中 data 键对应的值为机械臂服务返回的数据

### 打开

+ 方法：POST
+ 路径：/api/robots/cob/open
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

### move to

+ 方法：POST
+ 路径：/api/robots/cob/moveTo
+ 请求数据：

+ move joint
```json
{
    "space": "joint",
    "speedPercent": 80,
    "target": [
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
  + 此接口COB机械臂项目支持，其他不支持

+ move line
```json
{
    "space":"cartBase",
    "cartVel":1,
    "rotVel":1,
    "target":[
        1,
        2,
        3,
        4,
        5,
        6
    ]
}

## cartVel与rotVel : 当space为cartBase时，可以用cartVel(m/s)与rotVel(rad/s)控制运动速度。
## 使用cartVel与/或rotVel时，不能使用speedPercent。
## 单独设置cartVel时，rotVel会依据cartVel与用户设置的最大速度按比例进行换算，反之亦然。
## 若不确定运动的主分量是平移还是旋转，可同时设置cartVel和rotVel，以确保这两个速度限制均不被超过。
```

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

### 拖动示教模式

+ 方法：POST
+ 路径：/api/robots/cob/dragMode
+ 请求数据：
  + drag为 true  进入拖动示教模式
  + drag为 false 退出拖动示教模式
```json
{
    "drag": true
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
+ 路径：/api/robots/cob/getPoint

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
  + 获取的笛卡尔坐标 xyz位置 单位为米， rx, ry, rz

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

### 正解 (joint to cart)

+ 方法：POST
+ 路径：/api/robots/cob/jointToCart
+ 请求数据：
```json
{
    "cart": [
        10,
        0,
        0,
        0,
        0,
        0
    ]
}
```

+ 输出
```json
{
        "cart": [1,2,3,4,5,6]
}
## cart: 与输入对应的笛卡尔工具中心点位置
```

### 逆解 (cart to joint)

+ 方法：POST
+ 路径：/api/robots/cob/cartToJoint
+ 请求数据：
```json
{
    "cart": [
        0.070059925,
        -0.35693141,
        0.230572741,
        -1.53232142,
        -2.73160644,
        0.056278602
    ],
    "jointRef": [
        0,
        0,
        1.3,
        0,
        1.3,
        0
    ]
}
```

+ 输出
```json
{
        "joint": [1,2,3,4,5,6]
}
## joint: 与输入对应的关节角
```