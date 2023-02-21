## URDF 是什么

+ 参考
  + `https://baike.baidu.com/item/urdf/23744717`

### 百度百科

+ URDF，全称为Unified Robot Description Format，中文可以翻译为“统一机器人描述格式”。
+ 与计算机文件中的.txt文本格式、.jpg图像格式等类似，URDF是一种基于XML规范、用于描述机器人结构的格式。
+ 根据该格式的设计者所言，设计这一格式的目的在于提供一种尽可能通用（as general as possible）的机器人描述规范

+ 从机构学角度讲，机器人通常被建模为由连杆和关节组成的结构。
+ 连杆是带有质量属性的刚体，而关节是连接、限制两个刚体相对运动的结构。关节也被称为运动副。通过关节将连杆依次连接起来，就构成了一个个运动链（也就是这里所定义的机器人模型）。
+ 一个URDF文档即描述了这样的一系列关节与连杆的相对关系、惯性属性、几何特点和碰撞模型。具体来说，包括 
  + 机器人模型的运动学与动力学描述
  + 机器人的几何表示
  + 机器人的碰撞模型

---

+ 根据关节与连杆相关元素的定义，列举如下基于URDF的机器人描述示例：

+ 单连杆机器人，一个仅由一根连杆构成的机器人模型可用URDF描述如下：
  ```
    <?xml version="1.0"?>
    <robot name="mybot">  
        <link name="base_link">    
            <visual>      
                <geometry>        
                    <cylinder length="0.6" radius="0.2"/>      
                </geometry>    
            </visual>  
        </link>
    </robot>
  ``` 
  + 以上定义描述了一个名称为`mybot`的机器人，该机器人具有一根名为`base_link`的连杆，该连杆是一个长为`0.6`、横截面半径为`0.2`的圆柱体。根据机器人操作系统（ROS）的官方文档，URDF格式采用`“米-千克-秒”`制，因此上述数值单位为米。

+ 二连杆机器人
  ```
    <?xml version="1.0"?>
    <robot name="two_link_bot">
        <link name="link_0">
            <visual>
                <geometry>
                    <cylinder length="0.6" radius="0.2"/>
                </geometry>
            </visual>
        </link>
        
        <link name="link_1">
            <visual>
                <geometry>
                    <cylinder length="0.6" radius="0.2"/>
                </geometry>
            </visual>
        </link>
        
        <joint name="joint_0" type="revolute">
            <axis xyz="0 0 1"/>
            <limit effort="100.0" lower="0.0" upper="0.5" velocity="0.5"/>
            <origin rpy="0 0 0" xyz="0.0 0.0 0.3"/>
            <parent link="link_0"/>
            <child link="link_1"/>
        </joint>
    </robot>
  ``` 
  + 以上定义描述了一个名称为`two_link_bot`的机器人，该机器人具有两根连杆，两根连杆由一个旋转关节`joint_0`连接。