## 简介

+ cmake 语法基础 理论基础

## cmake 构建选项 打开开关

在 CMake 中，你可以使用 `option` 命令创建构建选项开关，以便在构建时根据用户的选择来开启或关闭某些功能。这些选项通常用于控制编译和构建过程中的一些特定配置。以下是如何在 CMake 中创建和使用构建选项开关的示例：

```cmake
# 在 CMakeLists.txt 中添加以下代码
option(BUILD_FEATURE_X "Build feature X" ON)
option(BUILD_FEATURE_Y "Build feature Y" OFF)

# 在合适的位置，根据选项的状态来设置相关内容
if(BUILD_FEATURE_X)
    message("Building feature X")
    add_subdirectory(feature_x)
endif()

if(BUILD_FEATURE_Y)
    message("Building feature Y")
    add_subdirectory(feature_y)
endif()
```

在这个示例中，我们定义了两个构建选项：`BUILD_FEATURE_X` 和 `BUILD_FEATURE_Y`。选项的初始状态分别设置为 `ON` 和 `OFF`。如果用户希望构建时开启 "Feature X"，可以在构建命令中使用 `-DBUILD_FEATURE_X=ON`，而如果希望关闭 "Feature Y"，可以使用 `-DBUILD_FEATURE_Y=OFF`。

根据选项的状态，我们在适当的位置添加了相关的配置。在这个例子中，如果选项 `BUILD_FEATURE_X` 被设置为 `ON`，就会构建名为 `feature_x` 的子目录中的内容。类似地，如果选项 `BUILD_FEATURE_Y` 被设置为 `ON`，就会构建 `feature_y` 子目录中的内容。

在实际项目中，你可以根据需要添加更多的选项和配置。这样的构建选项使得用户能够根据项目需求自定义构建过程，只构建他们需要的功能。

## cmake 变量

在CMake中，变量用于存储和操作数据，可以在CMake脚本中定义、设置和使用。下面是对CMake变量的详细解释：

1. CMake缓存变量（CMake Cache Variables）：这些变量存储在CMake缓存中，并可以通过CMake GUI或命令行进行设置。它们在多次运行CMake时保持持久，并且可以影响项目的配置。常见的CMake缓存变量包括`CMAKE_INSTALL_PREFIX`（安装路径）、`CMAKE_BUILD_TYPE`（构建类型）等。

2. CMake内部变量（CMake Internal Variables）：这些变量由CMake自身设置和使用，用于控制CMake的行为和功能。它们具有特殊的前缀或名称，例如`CMAKE_SOURCE_DIR`（项目根目录路径）、`CMAKE_BINARY_DIR`（构建目录路径）等。

3. 用户定义变量：这些变量由用户在CMake脚本中定义和设置。使用`set()`函数可以创建用户定义变量，并使用`${}`语法引用它们。例如：

   ```cmake
   set(MY_VARIABLE "Hello, world!")
   ```

4. 环境变量：CMake可以读取和使用系统环境变量。可以使用`$ENV{VAR_NAME}`语法引用环境变量。例如：

   ```cmake
   message("Home directory: $ENV{HOME}")
   ```

5. Cache Entry变量：CMake提供了`set()`函数的高级形式，用于创建带有用户友好描述和其他属性的缓存变量。例如：

   ```cmake
   set(MY_VARIABLE "Hello, world!" CACHE STRING "A user-friendly description")
   ```

   这将创建一个名为`MY_VARIABLE`的缓存变量，它具有用户友好的描述和其他属性，可以在CMake GUI中显示和设置。

6. List变量：List变量是一种特殊类型的变量，可以包含多个值。你可以使用`set()`函数将多个值存储到List变量中，并使用`${}`语法访问和操作它们。例如：

   ```cmake
   set(LIST_VARIABLE "value1" "value2" "value3")
   message("List variable: ${LIST_VARIABLE}")
   ```

   输出结果将是`value1;value2;value3`。

这些是CMake中常见的变量类型和用法。在CMake脚本中，你可以根据需要使用这些变量来控制和配置项目。

---

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