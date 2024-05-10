## Cob 机械臂接口

+ 登录设备即连接设备
+ 注
  + 响应数据中 data 键对应的值为机械臂服务返回的数据

+ 拖动示教放置点:
```json
{
    "space": "cartBase",
    "cartVel": 0.3,
    "rotVel": 0.3,
    "cart_flag":1,
    "rot_flag":1,
    "cart":[
        -0.3107980,
        0.00547460,
        0.26607365
    ],
    "?rot":"欧拉角",
    "rot":[
        0.0905825,
        -3.10053,
        0.0453788
    ]
}
```

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
    "?space":"运动空间类型: joint, 关节空间; cartBase, 笛卡尔空间",
    "space": "joint",
    "?speedPercent": "关节空间下运动的速度,范围 0 - 100",
    "speedPercent": 80,
    "?joint_flag":"位置标志: 1, 绝对目标关节角; 2, 相对目标关节角",
    "joint_flag":1,
    "?target":"目标关节角 输入格式为 角度",
    "target": {
        "joint_01":0,
        "joint_02":0,
        "joint_03":0,
        "joint_04":0,
        "joint_05":0,
        "joint_06":0
    }
}
```
+ 注
  + 请求的数据目前单位为 角度
  + 此接口COB机械臂项目支持，其他不支持

+ move line
```json
{
    "?space":"运动空间类型: joint, 关节空间; cartBase, 笛卡尔空间",
    "space":"cartBase",
    "?cartVel":"笛卡尔空间下位置移动速度,单位为 m/s",
    "cartVel":1.0,
    "?rotVel":"笛卡尔空间下旋转速度,单位为 rad/s",
    "rotVel":1.0,
    "?cart_flag":"位置标志: 1, 绝对位置; 2, 相对位置",
    "cart_flag":1,
    "?rot_flag":"姿态标志: 1, 绝对姿态; 2, 相对姿态",
    "rot_flag":1,
    "?cart":"位置数据, 输入格式为 米",
    "cart": {
        "x":1,
        "y":2,
        "z":3
    },
    "?rot":"姿态数据, 输入格式为 绝对姿态 则输入轴角,由机械臂本身获取的姿态或者相机检测到的目标姿态 ; 相对姿态 则输入欧拉角 弧度 分别是 绕 x 旋转的弧度 绕 y 轴旋转的弧度 绕 z 轴旋转的弧度",
    "rot": {
        "rx":4,
        "ry":5,
        "rz":6
    }
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
      "CartInfo":{
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
        },
        "?JointInfo":"关节角数据,输出格式为 角度",
        "JointInfo":{
          "joint_01":0,
          "joint_02":0,
          "joint_03":0,
          "joint_04":0,
          "joint_05":0,
          "joint_06":0
        }
      }
    },
    "message":"成功"
}
```
+ 注
  + 获取的关节角单位为 弧度
  + 获取的笛卡尔坐标 xyz位置 单位为米， rx, ry, rz,单位为弧度

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

### 设置末端工具 (set tool)

+ 方法:POST
+ 路径:/api/robots/cob/setTool
+ 请求数据:
```json
{
    "?index": "正整数，区分不同tool的唯一标识",
    "index": 1,
    "?name": "名字",
    "name": "sucker",
    "?position": "0-5 x, y, z, Rx, Ry, Rz",
    "position": [
        0,
        0,
        0,
        0,
        0
    ],
    "?mass": "质量",
    "mass": 2.042,
    "?centerOfMass": "质心",
    "centerOfMass": [
        -0.035310,
        -0.000020,
        0.001640
    ],
    "?inertia": "inertia  : 0-8 转动惯量 Ixx Ixy Ixz Iyx Iyy Iyz Izx Izy Izz",
    "inertia": [
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    ]
}
```

+ 成功响应:
```json
{
    "code":0,
    "data":{
        "STATUS":"SUCCESS"
    },
    "message":"成功"
}
```

+ 失败响应:
```json
{
    "code":8008,
    "data":{
        "STATUS":"FAIL"
    },
    "message":"失败"
}
```

## 设置默认工具 (set default tool)

+ 方法:POST
+ 路径:/api/robots/cob/setDefaultTool
+ 请求数据:
```json
{
    "index":1
}
```

+ 成功响应:
```json
{
    "code":0,
    "data":{
        "STATUS":"SUCCESS"
    },
    "message":"成功"
}
```

+ 失败响应:
```json
{
    "code":8009,
    "data":{
        "STATUS":"FAIL"
    },
    "message":"失败"
}
```

## 删除工具 (delete tool)

+ 方法:POST
+ 路径:/api/robots/cob/DeleteTool
+ 请求数据:
```json
{
    "index":1
}
```

+ 成功响应:
```json
{
    "code":0,
    "data":{
        "STATUS":"SUCCESS"
    },
    "message":"成功"
}
```

+ 失败响应:
```json
{
    "code":8010,
    "data":{
        "STATUS":"FAIL"
    },
    "message":"失败"
}
```