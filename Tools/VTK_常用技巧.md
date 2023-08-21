## 简介

+ VTK(Visualization Toolkit) 常用的编程技巧

## vtkDebugLeaksManager 类 链接哪一个动态库

在 VTK 7.1 版本中，`vtkDebugLeaksManager` 类属于 `vtkCommonCore` 模块，因此你需要链接到 `vtkCommonCore` 动态库。以下是可能的库名称，可以在链接命令中使用：

```bash
-lvtkCommonCore-7.1
```

请注意，库名称可能因操作系统和安装配置而有所不同。在使用 CMake 构建项目时，CMake 通常会自动处理库的链接。如果你手动编写链接命令，确保链接到 `vtkCommonCore` 动态库以使用 `vtkDebugLeaksManager` 类。

如果你使用的是 CMake，可以在你的 CMakeLists.txt 文件中添加类似以下内容来链接 VTK 动态库：

```cmake
find_package(VTK 7.1 REQUIRED)
target_link_libraries(YourTargetName PRIVATE ${VTK_LIBRARIES})
```

其中 `YourTargetName` 是你要构建的目标名称。上述代码将会自动链接所需的 VTK 动态库，包括 `vtkCommonCore`。

请确保你的 VTK 安装是正确的，包含了 `vtkCommonCore` 动态库，以及你想要使用的其他模块和类。

## pcl::VoxelGrid 链接哪一个动态库

在 Point Cloud Library (PCL) 中，`pcl::VoxelGrid` 类属于点云处理的模块，因此你需要链接到与点云处理相关的动态库。通常情况下，你需要链接到以下两个主要的动态库：

1. `pcl_common`: 这个库包含了 PCL 中一些常用的数据结构、算法和函数，包括点云的表示和操作等。

2. `pcl_filters`: 这个库包含了各种点云滤波器，包括 `pcl::VoxelGrid` 网格滤波器。

如果你使用的是 CMake 来构建项目，你可以在你的 `CMakeLists.txt` 文件中添加类似以下的内容来链接 PCL 相关的动态库：

```cmake
find_package(PCL REQUIRED COMPONENTS common filters)
target_link_libraries(YourTargetName PRIVATE ${PCL_COMMON_LIBRARIES} ${PCL_FILTERS_LIBRARIES})
```

其中 `YourTargetName` 是你要构建的目标名称。上述代码会自动链接所需的 PCL 动态库，包括 `pcl_common` 和 `pcl_filters`。

请注意，PCL 的库名称可能因为操作系统和 PCL 版本而有所不同。上述示例中的库名称是基于通用的命名约定，具体情况可能会有所变化。你可以查阅你所使用的 PCL 版本的文档以获取更准确的库名称和链接信息。