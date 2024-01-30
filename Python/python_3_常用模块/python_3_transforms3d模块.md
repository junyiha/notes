## 简介

+ transforms3d模块相关笔记

## python3 transform3d模块 详解

`transforms3d`是一个Python库，用于处理3D转换、旋转、平移等操作。这个库主要用于处理三维空间中的坐标变换，包括欧拉角、四元数、轴-角等不同表示方式之间的转换。以下是对`transforms3d`库的一些主要功能和模块的详细解释：

### 安装transforms3d库

你可以使用以下命令安装`transforms3d`库：

```bash
pip install transforms3d
```

### 主要模块和功能

#### 1. `transforms3d.euler`

该模块提供了欧拉角的转换函数。主要函数有：

- `euler2mat`：将欧拉角转换为旋转矩阵。
- `mat2euler`：将旋转矩阵转换为欧拉角。

```python
import transforms3d.euler as tf_euler

# 示例
euler_angles = (0.1, 0.2, 0.3)  # (roll, pitch, yaw)
rotation_matrix = tf_euler.euler2mat(euler_angles)
euler_angles_recovered = tf_euler.mat2euler(rotation_matrix)
```

#### 2. `transforms3d.quaternions`

该模块提供了处理四元数的函数。主要函数有：

- `quaternion_from_euler`：将欧拉角转换为四元数。
- `euler_from_quaternion`：将四元数转换为欧拉角。

```python
import transforms3d.quaternions as tf_quaternions

# 示例
euler_angles = (0.1, 0.2, 0.3)  # (roll, pitch, yaw)
quaternion = tf_quaternions.quaternion_from_euler(*euler_angles)
euler_angles_recovered = tf_quaternions.euler_from_quaternion(quaternion)
```

#### 3. `transforms3d.axangles`

该模块提供了处理轴-角表示的函数。主要函数有：

- `axangle2mat`：将轴-角表示转换为旋转矩阵。
- `mat2axangle`：将旋转矩阵转换为轴-角表示。

```python
import transforms3d.axangles as tf_axangles

# 示例
axis_angle = (1, 0, 0, 0.1)  # (x, y, z, angle)
rotation_matrix = tf_axangles.axangle2mat(axis_angle)
axis_angle_recovered = tf_axangles.mat2axangle(rotation_matrix)
```

#### 4. `transforms3d.zooms`

该模块提供了处理缩放变换的函数。主要函数有：

- `zooms_from_params`：将缩放参数转换为缩放矩阵。

```python
import transforms3d.zooms as tf_zooms

# 示例
zoom_params = (2, 3, 4)  # (scale_x, scale_y, scale_z)
zoom_matrix = tf_zooms.zooms_from_params(*zoom_params)
```

这些模块提供了在3D空间中进行不同类型的变换的工具函数。你可以根据需要选择合适的表示方式，并使用相应的函数进行转换。库的文档提供了更详细的信息和示例，可以帮助你更好地了解如何使用这些功能。