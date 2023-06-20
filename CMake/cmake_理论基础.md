## 简介

+ cmake 语法基础 理论基础

## cmake 3.10.2 option

在CMake 3.10.2版本中，`option`命令用于定义和处理用户选项。它允许您在CMake配置过程中提供一些可配置的选项，以便用户可以根据需要进行选择。

以下是`option`命令的语法：

```cmake
option(<option_variable> "<option_description>" [initial_value])
```

- `<option_variable>`：要定义的选项的变量名。
- `<option_description>`：选项的描述文本，将在配置过程中显示给用户。
- `[initial_value]`：选项的初始值，默认情况下为`OFF`。如果用户选择了该选项，则变量的值为`ON`。

使用`option`命令定义选项后，可以通过`${<option_variable>}`来引用选项的值。

以下是一个示例，展示了CMake 3.10.2中`option`命令的使用：

```cmake
option(BUILD_TESTS "Build test targets" ON)
option(DEBUG_LOGGING "Enable debug logging" OFF)

if(BUILD_TESTS)
    message("Building test targets")
else()
    message("Not building test targets")
endif()

if(DEBUG_LOGGING)
    message("Debug logging is enabled")
else()
    message("Debug logging is disabled")
endif()
```

在上述示例中，定义了两个选项：`BUILD_TESTS`和`DEBUG_LOGGING`。`BUILD_TESTS`的初始值为`ON`，而`DEBUG_LOGGING`的初始值为`OFF`。

根据选项的值，使用`if`语句来执行相应的操作。如果`BUILD_TESTS`为`ON`，则输出"Building test targets"；否则输出"Not building test targets"。如果`DEBUG_LOGGING`为`ON`，则输出"Debug logging is enabled"；否则输出"Debug logging is disabled"。

在CMake的配置过程中，用户可以通过设置这些选项来控制构建的行为。

请注意，选项的值是通过CMake**缓存系统**进行保存的，可以通过命令行选项或图形界面工具来修改选项的值。