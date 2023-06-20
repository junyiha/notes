## 简介

+ CMake常用的方法和CMakeLists编程技巧

## cmake 3.10.2 退出 终止 命令

在CMake 3.10.2版本中，可以使用`return()`命令来退出当前的CMake脚本的执行。这个命令会立即终止当前脚本的执行，并返回到调用方。

以下是`return()`命令的用法：

```cmake
return()
```

当调用`return()`命令时，CMake会立即停止执行当前的CMake脚本，并返回到调用方。

以下是一个简单的示例，演示如何使用`return()`命令退出CMake脚本的执行：

```cmake
# 检查条件，如果不满足则退出脚本
if(NOT SOME_CONDITION)
    message("Condition not met, exiting...")
    return()
endif()

# 执行其他操作
message("Continuing execution...")
```

在上述示例中，如果`SOME_CONDITION`条件不满足，那么在执行到`return()`命令时，脚本将立即退出并返回到调用方。否则，将继续执行后续的操作。

请注意，`return()`命令只能用于退出当前的CMake脚本，并返回到调用方。它不会终止整个CMake过程。如果您需要终止整个CMake过程，可以使用`message(FATAL_ERROR "Error message")`命令，该命令会显示一个致命错误消息并终止整个CMake过程的执行。

---

## cmake 3.10.2 switch 选择实现

在CMake 3.10.2版本中，由于没有直接支持的`switch`语句，您可以使用多个`if`和`elseif`语句来实现类似的功能。

以下是一个示例，展示如何使用多个`if`和`elseif`语句实现类似`switch`的功能：

```cmake
set(SWITCH_VAR "value2")

if(SWITCH_VAR STREQUAL "value1")
    # 执行value1对应的操作
    message("Switch case: value1")
elseif(SWITCH_VAR STREQUAL "value2")
    # 执行value2对应的操作
    message("Switch case: value2")
elseif(SWITCH_VAR STREQUAL "value3")
    # 执行value3对应的操作
    message("Switch case: value3")
else()
    # 执行默认的操作
    message("Switch default case")
endif()
```

在上述示例中，我们使用了多个`if`和`elseif`语句来检查变量`SWITCH_VAR`的值，并根据不同的条件执行相应的操作。如果`SWITCH_VAR`的值等于`value1`，则执行与`value1`对应的操作；如果`SWITCH_VAR`的值等于`value2`，则执行与`value2`对应的操作，依此类推。如果没有匹配的条件，将执行`else`语句中定义的默认操作。

虽然这种方式在CMake 3.10.2中没有直接的`switch`语句，但通过使用多个`if`和`elseif`语句，您可以根据不同的条件选择不同的操作，实现类似`switch`的功能。请根据实际需求编写适当的条件判断，并执行相应的操作。

---

## cmake 3.10.2 通过宏选择不同目标编译

在CMake 3.10.2版本中，可以使用`option`命令来定义宏，并通过`if`语句来选择不同的目标编译。以下是一个示例：

```cmake
cmake_minimum_required(VERSION 3.10.2)
project(MyProject)

# 定义宏，用于选择编译选项
option(BUILD_TARGET_A "Build target A" ON)
option(BUILD_TARGET_B "Build target B" OFF)

# 添加源文件
set(SOURCES src/main.cpp)

# 根据宏的值，选择要构建的目标
if(BUILD_TARGET_A)
    add_executable(targetA ${SOURCES})
    # 其他针对目标A的配置
endif()

if(BUILD_TARGET_B)
    add_executable(targetB ${SOURCES})
    # 其他针对目标B的配置
endif()
```

在这个示例中，我们使用`option`命令定义了两个宏：`BUILD_TARGET_A`和`BUILD_TARGET_B`。这两个宏的默认值分别为ON和OFF。根据这些宏的值，我们使用`if`语句选择要构建的目标。

要使用CMake 3.10.2版本运行上述CMakeLists.txt文件，可以使用以下命令：

```shell
cmake -H. -Bbuild
cmake --build build
```

这将在`build`目录中生成构建文件，并使用生成的构建文件来构建目标。

请注意，如果您的CMake版本较旧，某些语法可能不受支持。确保在运行CMake命令之前，检查您所使用的CMake版本是否支持所需的功能。

---

## cmake 3.10.2 打印 语法

在CMake 3.10.2版本中，您可以使用`message`命令来打印消息、变量值和其他调试信息。`message`命令的语法如下：

```cmake
message([<mode>] "<message string>")
```

其中，`mode`是可选参数，用于指定消息的类型。常用的`mode`参数有以下几种：

- `STATUS`：打印带有前缀`--`的消息。
- `WARNING`：打印带有前缀`-- Warning:`的警告消息。
- `AUTHOR_WARNING`：打印带有前缀`-- Author Warning:`的作者警告消息。
- `SEND_ERROR`：打印带有前缀`-- Send Error:`的错误消息，并停止配置过程。
- `FATAL_ERROR`：打印带有前缀`-- FATAL_ERROR:`的严重错误消息，并停止配置过程。
- `DEPRECATION`：打印带有前缀`-- DEPRECATION:`的过时警告消息。

以下是一些示例：

```cmake
# 打印普通消息
message("This is a message")

# 打印带有前缀的消息
message(STATUS "This is a status message")
message(WARNING "This is a warning message")
message(AUTHOR_WARNING "This is an author warning message")

# 打印错误消息并停止配置过程
message(SEND_ERROR "This is an error message")

# 打印严重错误消息并停止配置过程
message(FATAL_ERROR "This is a fatal error message")

# 打印过时警告消息
message(DEPRECATION "This is a deprecation warning message")
```

当运行CMake时，这些消息将显示在终端上，以便您查看配置过程中的相关信息、警告和错误。

请注意，`message`命令在CMake 3.10.2版本中的语法与较新版本（如CMake 3.21）中的语法略有不同。如果您的CMake版本是3.10.2，可以使用上述示例来打印消息。如果使用的是较新版本的CMake，请参考官方文档以获取更准确的语法信息。