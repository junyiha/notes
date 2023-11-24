# API 文档

Json 内容单位为 m 和 rad（弧度）， 旋转表示方式为旋转向量

## 控制

### Move

- moveTo
    - url: /api/control/moveTo
    - 运动到关节空间或笛卡尔空间中指定的目标点。运动轨迹为对应空间中的直线。改为立刻返回。
    - example_1: joint 设置指定目标
    
    ```
    {
        "space" : "joint",
        "speedPercent" : 50,
        "target" : [1,2,3,4,5,6]
    }
    ## space : joint/cartBase
    ## speedPercent : 速度百分比，50则为50%
    ## space为cart时  target 0-5 : x,y,z,Rx,Ry,Rz
    ## space为joint时 target 0-5 : J1 - J6
    
    ```
    
    - example_2: cartBase 设置指定目标
    
    ```
    {
        "space" : "cartBase",
        "cartVel" : 1.0,
        "rotVel" : 1.0,
        "target" : [1,2,3,4,5,6]
        "blend" : {
            "method" : ""
            "param" : {
                "blendRadius" : 0.01
            }
        }
    }
    
    ## cartVel与rotVel : 当space为cartBase时，可以用cartVel(m/s)与rotVel(rad/s)控制运动速度。
        * 使用cartVel与/或rotVel时，不能使用speedPercent。
        * 单独设置cartVel时，rotVel会依据cartVel与用户设置的最大速度按比例进行换算，反之亦然。
        * 若不确定运动的主分量是平移还是旋转，可同时设置cartVel和rotVel，以确保这两个速度限制均不被超过。
    ## blend
        * method 选择 blend 方式, 暂仅支持一种
        * param blend参数
            * blendRadius 交融半径 double（m）
    
    ```
    - example_3: 设置指定示教点
    
    ```
    {
        "space" : "cartBase", 
        "pointIndex" : 1,
        "cartVel" : 1.0,
        "rotVel" : 1.0,
    }
    
    ## 设置示教点为目标无需指定space
    
    ```

---

- moveRel
    - url: /api/control/moveRel
    - 在指定空间（关节/笛卡尔基座/笛卡尔工具中心点）中做指定的相对运动。运动轨迹为对应空间中的直线。
    - example:
    
    ```
    {
        "space" : "cartTcp",
        "speedPercent" : 50,
        "target" : [0.1,0,0,0,0,0]
    }
    ## space : joint/cartBase/cartTcp
    ## speedPercent : 速度百分比，50则为50%
    ## target : 目标偏移量，例如，上面的例子表示以50%的速度向工具中心点的x方向移动0.1m
    ## space为cart时  target 0-5 : x,y,z,Rx,Ry,Rz
    ## space为joint时 target 0-5 : J1 - J6
    
    ```
    
- stopAllTasks
    - url: /api/control/stop
    - 停止当前任务并清空任务队列。请求会立刻返回，请求返回后，需要调用getIsTaskRunning接口以检查队列是否已清空。

- pause
    - url: /api/control/pause
    - 暂停执行任务队列中的任务。

- continue
    - url: /api/control/continue
    - 继续执行任务队列中的任务。

- setSpeedPercent
    - url: /api/control/speedPercent
    - 设置当前运动速度百分比。
    - example:
    
    ```
    {
        "speedPercent" : 50
    }
    ## speedPercent : 速度百分比，50则为50%，范围0.1 ~ 100
    
    ```

### Jog

- jog（不建议API编程用户使用，建议使用moveRel）
    - url: /api/control/jog
    - 点动。
    - example:
    
    ```
    {
        "jog": {
                "space": "joint",
                "index": 0,
                "step": 0.1,
                "direction": -1,
                "speedPercent": 50
        }
    }
    ## space : joint/cartBase/cartTcp
    ## space为cartBase或cartTcp时  index可选 0-5 : x,y,z,Rx,Ry,Rz
    ## space为joint时 index可选 0-5 : J1 - J6
    ## step  : 步进值， m 或 rad
    ## direction    : 方向 1/-1
    ## speedPercent : 速度百分比，50则为50%
    
    ```
    

### Drag

- drag
    - url: /api/control/drag
    - 进入/退出拖动模式。
    - example:
    
    ```
    {
        "drag" : true
    }
    ## drag : true则开启拖动  false 则关闭拖动
    
    ```
    

## 写入

### 安全

- setTool
    - url: /api/safety/setTool
    - example:
    
    ```
    {
        "index": 1,
        "name": "T1",
        "position": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0],
        "mass": 100.0,
        "centerOfMass": [1.0, 2.0, 3.0],
        "inertia": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]
    }
    ## index    : 正整数，区分不同tool的唯一标识
    ## name     : 名字
    ## position : 0-5 x, y, z, Rx, Ry, Rz
    ## mass     : 质量
    ## centerOfMass : 0-2 质心
    ## inertia  : 0-8 转动惯量 Ixx Ixy Ixz Iyx Iyy Iyz Izx Izy Izz
    
    ```
    

---

- deleteTool
    - url: /api/safety/deleteTool
    - example:
    
    ```
    {
        "index" : 1
    }
    ## index : 为正整数，则删除对应编号tool
    
    {
        "index": [1, 2, 3]
    }
    ## index : 为数组，则删除数组内所有编号对应的tool
    
    ```
    

---

- setDefaultTool
    - url: /api/safety/setDefaultTool
    - example:
    
    ```
    {
        "index" : 1
    }
    ## index : 正整数，设置对应编号的tool为默认tool，之后每次启动都会进行加载
    
    ```
    

---

- setMaxCartVel
    - url: /api/safety/setMaxCartVel
    - example:
    
    ```
    {
        "transVel": 1.0,
        "transAcc": 1.0,
        "transJerk": 1.0,
        "rotVel": 1.0,
        "rotAcc": 1.0,
        "rotJerk": 1.0
    }
    ## transVel : 平移速度 m/s
    ## rotVel   : 转动速度 rad/s
    
    ```
    

---

- setMaxJointVel
    - url: /api/safety/setMaxJointVel
    - example:
    
    ```
    {
        "jointVel": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0],
        "jointAcc": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0],
        "jointJerk": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    }
    ## jointVel : 0-5  分别为 J1 - J6 的 joint_max_vel
    ## jointAcc : 0-5  分别为 J1 - J6 的 joint_max_acc
    ## jointJerk: 0-5  分别为 J1 - J6 的 joint_max_jerk
    
    ```
    

---

- resetMaxCartVel
    - url: /api/safety/resetMaxCartVel
    - 将笛卡尔速度限制重置到系统限制的50%
    - example: GET接口，无参数

---

- resetMaxJointVel
    - url: /api/safety/setMaxJointVel
    - 将关节速度限制重置到系统限制的50%
    - example: GET接口，无参数

### 示教点

- savePoint
    - url: /api/teach/savePoint
    - example:
    
    ```
    {
        "index": 1,
        "pointName": "P1",
        "joint": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0],
        "cart": [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    }
    ## index     : 正整数，示教点的唯一标识
    ## pointName : 示教点名字
    ## joint     : 0-5 表示 J1 - J6弧度
    ## cart      : 0-5 表示 x, y, z, Rx, Ry, Rz
    
    ```
    

---

- deletePoint
    - url: /api/teach/deletePoint
    - example:
    
    ```
    {
        "index" : 1
    }
    ## index : 为正整数，则删除对应编号point
    
    {
        "index": [1, 2, 3]
    }
    ## index : 为数组，则删除数组内所有编号对应的point
    
    ```
    

## 正逆解

- JntToCart
    - url: /api/common/JntToCart
    - 返回输入的关节角对应的笛卡尔工具中心点位置。需要注意，此结果是与当前工具设置相关的。
    - example:
    
    ```
    {
            "joint": [1,2,3,4,5,6]
    }
    ## joint: 输入的关节角
    
    ```
    
    - Result:
    
    ```
    {
            "cart": [1,2,3,4,5,6]
    }
    ## cart: 与输入对应的笛卡尔工具中心点位置
    
    ```
    
- CartToJnt
    - url: /api/common/CartToJnt
    - 返回输入的笛卡尔工具中心点位置对应的关节角，**需要注意，目前使用的是迭代逆解，因此建议设置一个已示教的目标点附近的关节角作为参考关节角。**
    - example:
    
    ```
    {
            "cart": [1,2,3,4,5,6]
            "jointRef": [0,0,1.5708,0,1.5708,0]
    }
    ## cart: 笛卡尔工具中心点位置
    ## jointRef: 参考关节角，将作为迭代的起点。若不设置，将使用机器人当前关节角。
    
    ```
    
    - Result:
    
    ```
    {
            "joint": [1,2,3,4,5,6]
    }
    ## joint: 与输入对应的关节角
    
    ```

## 工具校准

- 设置校准点
    - url: /api/safety/tool/calibrate/addPoint
    - 设置校准点，需要将点作为参数发送给服务，每次仅设置一个，最多设置10个，超出后需要调用clear接口清空再设置
    - example:
    
    ```
    {
            "point" : [
                [J1, J2, J3, J4, J5, J6]
            ]
    }
    ## point: 以Array形式输入点的关节角
    
    ```
    - Result:
    
    ```
    {
        "count" : 4
    }
    ## 返回当前已设置点数
    
    ```

- 获取之前设置的校准点
    - url: /api/safety/tool/calibrate/getPoints
    - 获取设置的校准点，如果未设置则返回null
    - GET方法无需参数
    - Result:
    
    ```
    {
            "points" : [
                [J1, J2, J3, J4, J5, J6],
                [J1, J2, J3, J4, J5, J6],
                [J1, J2, J3, J4, J5, J6],
                [J1, J2, J3, J4, J5, J6]
            ]
    }
    ## points: 以Array形式返回已设置点，若为空则返回null
    
    ```

- 清空校准点
    - url: /api/safety/tool/calibrate/clearPoints
    - 清空所有已保存校准点，注：清空后无缓存，请将需要的点自行保存后再清空
    - GET方法无需参数

- 开始校验
    - url: /api/safety/tool/calibrate
    - 根据已有校验点开始校验并获得结果，如果设置的点不足四个则失败
    - GET方法无需参数    
    - Result:
    
    ```
    {
            "toolCenterPoint": [x, y, z],
            "err": e
    }
    ## toolCenterPoint: 返回校准的x, y ,z
    ## err: 返回误差值（参考价值较低）
    
    ```


## 读取

此下均为get方法

### 通用

- getCurStatus
    - url: /api/common/getCurStatus
    - result:
    
    ```
    {
            "Info": {
                    "JointInfo": [0, 1, 2, 3, 4, 5],
                    "CartInfo": [0, 1, 2, 3, 4, 5]
            }
    }
    ## jointInfo : 0-5 表示J1 - J6位置
    ## cartInfo  : 0-5 表示当前工具设置下的 x, y, z, Rx, Ry, Rz
    
    ```
    

---

- getIsTaskRunning
    - url: /api/common/getIsTaskRunning
    - 检查机器人任务队列中是否有任务正在执行。注意，若当前队列中有任务且任务被暂停，此接口会返回True。
    - result:
    
    ```
    {
            "isTaskRunning" : "True"
    }
    
    ```
    

### 安全

- getTool
    - url: /api/safety/getTool
    - result:暂不显示

---

- getMaxCartVel
    - url: /api/safety/getMaxCartVel
    - result:
    
    ```
    {
        "transVel": 1.0,
        "transAcc": 1.0,
        "transJerk": 1.0,
        "rotVel": 1.0,
        "rotAcc": 1.0,
        "rotJerk": 1.0
    }
    ## transVel : 平移速度 m/s
    ## rotVel   : 转动速度 rad/s
    
    ```
    

---

- getMaxJointVel
    - url: /api/safety/getMaxJointVel
    - result:
    
    ```
    {
            "jointVel" : [1,2,3,4,5,6],
            "jointAcc" : [1,2,3,4,5,6],
            "jointJerk": [1,2,3,4,5,6],
            "jointName": ["关节一", "关节二", "关节三", "关节四", "关节五", "关节六"]
    }
    ## jointVel : 0-5 表示J1 - J6的关节速度
    ## jointAcc : 0-5 表示J1 - J6的关节加速度
    ## jointJerk: 0-5 表示J1 - J6的关节加加速度
    ## jointName: 关节名
    
    ```
    

### 示教点

- getPoints
    - url: /api/teach/getPoints
    - result:暂不显示


# 规划但未完成


- getCurrentTaskId
    - url:
    - 返回机器人任务队列中当前执行任务的编号。后续实现。


---

- getPointByName/getPointById
    - url:
    - 按名称或按序号获取示教点。现在不做，后续无锡或客户有需求时，确定具体实现。
