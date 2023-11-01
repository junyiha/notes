## 简介

+ cmake 语法基础 理论基础

## CMakeLists add_definitions() 详解

`add_definitions()` 是 CMake 中用于添加编译器宏定义的命令。它允许您在整个项目中为源代码文件添加全局宏定义，以实现条件编译或其他编译时配置。以下是有关 `add_definitions()` 的详解：

**语法：**

```cmake
add_definitions(-D<DEFINE_1> -D<DEFINE_2> ... -D<DEFINE_N>)
```

- `-D<DEFINE>`: 指定一个宏定义，`-D` 后跟宏的名称。您可以使用多个 `-D` 来指定多个宏定义。

**示例：**

假设您希望在整个项目中定义一个宏，例如 `ENABLE_FEATURE_X`，以便在源代码文件中进行条件编译。您可以在项目的 CMakeLists.txt 文件中使用 `add_definitions()` 来定义宏：

```cmake
add_definitions(-DENABLE_FEATURE_X)
```

这将使 `-DENABLE_FEATURE_X` 添加到编译器命令行，以便在编译源文件时启用该宏。您可以在源代码文件中使用 `#ifdef` 或 `#ifndef` 指令来检查该宏的存在，然后根据需要执行不同的代码。

```cpp
#ifdef ENABLE_FEATURE_X
// 这部分代码只在 ENABLE_FEATURE_X 定义时编译
// 执行 Feature X 相关的操作
#else
// 这部分代码在 ENABLE_FEATURE_X 未定义时编译
// 执行其他操作
#endif
```

**注意事项：**

- `add_definitions()` 命令将全局宏定义应用于整个项目，因此请确保不会意外地影响其他目标或源文件。如果需要更精确的控制，可以考虑使用 `target_compile_definitions()` 命令来为特定目标添加宏定义。
- 如果您需要定义带有值的宏，例如 `-DVERSION_NUMBER=42`，只需在 `-D` 后添加宏的名称和值即可。
- 使用 `add_definitions()` 命令会为所有目标和源文件添加宏定义，这可能会导致不必要的宏定义冲突。因此，在 CMake 3.12 及更高版本中，推荐使用 `target_compile_definitions()` 来更精确地控制宏定义的作用范围。

总之，`add_definitions()` 是用于添加全局宏定义的 CMake 命令，它可以帮助您在整个项目中进行条件编译和其他编译时配置。

## cmake CMakeLists.txt include_directories()函数 详解

`include_directories()`函数是CMake中的一个用于指定头文件包含路径的函数。它用于告诉CMake编译器在哪里查找头文件。在CMakeLists.txt文件中使用`include_directories()`函数非常有用，因为它允许您配置项目以便正确找到所有所需的头文件。

下面是关于`include_directories()`函数的详细解释：

```cmake
include_directories(directory1 [directory2 ...])
```

- `directory1`, `directory2`, ...：这些参数是包含头文件的目录路径。您可以指定一个或多个目录，用于告诉CMake查找头文件的位置。通常，这些目录路径是相对于`CMakeLists.txt`文件的。

`include_directories()`函数的作用是将指定的目录路径添加到CMake项目的头文件包含路径中，以使编译器能够找到所需的头文件。当您使用`#include`指令包含头文件时，编译器将在这些目录中查找头文件。

示例用法：

```cmake
include_directories(include)  # 添加一个名为"include"的头文件目录

# 或者指定多个头文件目录
include_directories(
    include
    common
)
```

在上面的示例中，`include_directories()`函数用于指定项目的头文件搜索路径，通常这些路径包括项目中的`include`目录和`common`目录。这使得您可以在CMake项目中使用相对路径来包含头文件，而无需手动指定完整的文件路径。

请注意，从CMake 3.15开始，更推荐使用`target_include_directories()`函数，它允许更好的目标级别控制，以及更容易实现接口库的目录传递。这是一个更现代和更具有可维护性的做法。

```cmake
target_include_directories(target_name
    PUBLIC
        include
    PRIVATE
        private_include
)
```

上述示例中，`target_include_directories()`函数将头文件目录添加到名为`target_name`的目标（可执行文件或库）中，可以使用`PUBLIC`和`PRIVATE`修饰符来指定头文件目录的可见性。这提供了更灵活的控制选项。

## cmake CMakeLists.txt 内置变量

CMake提供了一些内置变量，用于获取有关项目和构建环境的信息，您可以在CMakeLists.txt文件中使用这些变量来进行配置和生成目标。以下是一些常用的内置变量：

1. `CMAKE_SOURCE_DIR`：指向CMakeLists.txt文件所在的源代码根目录的路径。

2. `CMAKE_BINARY_DIR`：指向CMake生成构建文件的根目录的路径。这通常是项目构建的目录，与源代码分开。

3. `CMAKE_CURRENT_SOURCE_DIR`：指向当前处理的CMakeLists.txt文件所在的目录。

4. `CMAKE_CURRENT_BINARY_DIR`：指向与当前处理的CMakeLists.txt文件关联的构建目录。

5. `CMAKE_PROJECT_NAME`：包含当前项目的名称，通常由`project()`命令指定。

6. `CMAKE_VERSION`：CMake的版本信息。

7. `CMAKE_CXX_COMPILER`：指向C++编译器的可执行文件路径。

8. `CMAKE_C_COMPILER`：指向C编译器的可执行文件路径。

9. `CMAKE_SYSTEM`：指定操作系统的名称。

10. `CMAKE_SYSTEM_NAME`：指定操作系统的名称，通常是与`CMAKE_SYSTEM`相同。

11. `CMAKE_SYSTEM_VERSION`：指定操作系统的版本号。

12. `CMAKE_SYSTEM_PROCESSOR`：指定操作系统的处理器架构。

13. `CMAKE_BUILD_TYPE`：用于指定构建类型（例如，Debug、Release、RelWithDebInfo等）。可以使用此变量来控制编译器标志和优化级别。

14. `CMAKE_INSTALL_PREFIX`：指定安装目标的根目录。默认情况下，它通常是`/usr/local`（Linux）或`C:\Program Files`（Windows）。

15. `CMAKE_MODULE_PATH`：用于指定查找CMake模块的路径。模块通常用于共享一些通用的CMake配置。

这些内置变量可用于配置项目的不同方面，包括源文件路径、构建文件路径、编译器信息、操作系统信息和其他构建选项。您可以在CMakeLists.txt文件中使用这些变量，以根据项目的需求自定义构建过程。

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