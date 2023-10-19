## 简介

+ CMake常用的方法和CMakeLists编程技巧

## cmake CMakeLists.txt文件编译多个可执行文件 for循环 示例 详解

要在CMake中使用循环来生成多个可执行文件，通常需要使用CMake的`foreach`循环结构。下面是一个示例CMakeLists.txt文件，展示如何使用`foreach`循环来生成多个可执行文件：

```cmake
cmake_minimum_required(VERSION 3.0)

project(MyProject)

# 列出所有要编译的可执行文件
set(executables
    MyExecutable1
    MyExecutable2
    MyExecutable3
)

# 遍历可执行文件列表并生成它们
foreach(executable ${executables})
    # 每个可执行文件的源文件
    set(${executable}_sources ${executable}.cpp)

    # 添加可执行文件
    add_executable(${executable} ${${executable}_sources})

    # 如果可执行文件有依赖库文件，可以在这里链接它们
    # target_link_libraries(${executable} SomeLibrary)

endforeach()
```

这个示例CMakeLists.txt文件包含以下关键部分：

1. `set(executables ...)`：这一行定义了一个变量`executables`，其中包含了要编译的多个可执行文件的名称。在这个示例中，我们列出了三个可执行文件的名称，但您可以根据需要添加更多。

2. `foreach(executable ${executables})`：这是一个`foreach`循环，用于迭代`executables`变量中的每个可执行文件名称。

3. `set(${executable}_sources ${executable}.cpp)`：在循环内，我们为每个可执行文件设置了一个源文件变量，例如`MyExecutable1_sources`，这是根据可执行文件的名称构建的。

4. `add_executable(${executable} ${${executable}_sources})`：在循环内，我们使用`add_executable`命令为每个可执行文件生成目标。`add_executable`使用了之前定义的源文件变量。

5. （可选）`target_link_libraries(${executable} SomeLibrary)`：如果可执行文件有依赖的库文件，可以使用此命令将它们链接到可执行文件。

这种结构使您能够轻松地扩展项目，以支持多个可执行文件，而无需手动为每个文件编写`add_executable`命令。这在大型项目中特别有用，因为它可以减少配置文件的复杂性。

## cmake CMakeLists.txt文件编译多个可执行文件常见结构 示例 详解

CMake是一个用于管理C++项目的跨平台构建工具，它允许您配置项目并生成适用于不同编译器和操作系统的构建系统。在CMake中，通常将项目的构建配置信息保存在一个名为CMakeLists.txt的文件中。

如果您想要在一个CMake项目中编译多个可执行文件，通常可以按照以下结构来组织CMakeLists.txt文件：

```cmake
cmake_minimum_required(VERSION 3.0)  # 指定最低的CMake版本

project(MyProject)  # 指定项目名称

# 添加可执行文件1
add_executable(MyExecutable1
    source1.cpp
    source2.cpp
)

# 添加可执行文件2
add_executable(MyExecutable2
    source3.cpp
    source4.cpp
)

# 可选：如果项目中有共享的库文件，可以使用add_library添加库文件

# 链接库文件到可执行文件1
target_link_libraries(MyExecutable1
    SomeLibrary1
    SomeLibrary2
)

# 链接库文件到可执行文件2
target_link_libraries(MyExecutable2
    SomeLibrary3
    SomeLibrary4
)
```

上述代码是一个简单的CMakeLists.txt文件，用于编译两个可执行文件。以下是对代码的详细解释：

1. `cmake_minimum_required(VERSION 3.0)`：这一行指定了项目所需的最低CMake版本。您可以根据您的需要更改此版本号。

2. `project(MyProject)`：这一行指定了项目的名称。在这里，项目名称被设置为"MyProject"，您可以将其替换为您的项目名称。

3. `add_executable(MyExecutable1 source1.cpp source2.cpp)`：这一行添加了一个名为"MyExecutable1"的可执行文件，并指定了源代码文件(source1.cpp和source2.cpp)。您可以根据您的项目需要添加更多的源文件。

4. `add_executable(MyExecutable2 source3.cpp source4.cpp)`：同样，这一行添加了一个名为"MyExecutable2"的可执行文件，并指定了不同的源代码文件。

5. `target_link_libraries(MyExecutable1 SomeLibrary1 SomeLibrary2)`：如果您的项目依赖于一些库文件，您可以使用这行来链接这些库文件到"MyExecutable1"。类似地，您可以为"MyExecutable2"链接其他库文件。

这只是一个简单的示例，CMake支持更复杂的项目结构和配置选项，可以根据实际需求进行定制。在实际项目中，您可能需要添加更多的配置信息，如编译选项、包含路径、安装规则等。请根据您的项目需求进一步扩展和定制CMakeLists.txt文件。

## cmake CMakeLists.txt文件常见结构 示例 详解

CMakeLists.txt文件是CMake项目的核心配置文件，它定义了项目的属性、源文件、依赖关系和构建规则。以下是一个常见的CMakeLists.txt文件结构示例，带有详细的解释：

```cmake
# 指定CMake的最低版本要求
cmake_minimum_required(VERSION 3.0)

# 定义项目名称
project(MyProject)

# 添加可执行文件并指定源文件
add_executable(myapp
    main.cpp         # 主程序入口
    utils.cpp        # 自定义工具函数
)

# 添加可选的编译标志
# add_compile_options(-std=c++11)  # 设置C++标准，可选

# 查找并添加依赖的库（例如，查找并添加Boost库）
# find_package(Boost REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
# target_link_libraries(myapp ${Boost_LIBRARIES})

# 设置输出目录，将可执行文件放在bin目录中
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录，可以在子目录中定义更多的CMakeLists.txt文件
# add_subdirectory(subdirectory_name)

# 可以定义自定义的构建规则、安装规则等

# 可以包括其他CMakeLists.txt文件
# include(subdirectory_name/CMakeLists.txt)
```

上述示例演示了一个简单的CMakeLists.txt文件，以下是各个部分的详细解释：

1. `cmake_minimum_required(VERSION 3.0)`：这一行指定了最低的CMake版本要求。

2. `project(MyProject)`：这一行定义了项目的名称。项目名称将用于生成构建文件和可执行文件的前缀。

3. `add_executable(myapp ...)`：这一行定义了可执行文件（myapp）以及与之关联的源文件。列出了要包括在可执行文件中的所有源文件。

4. `add_compile_options(-std=c++11)`：这是一个可选部分，用于设置编译选项。在这里，它设置了C++标准为C++11。

5. `find_package(Boost REQUIRED)`：这是一个可选的示例，用于查找并添加依赖的库。在这里，它查找并添加了Boost库。

6. `set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)`：这一行指定了可执行文件的输出目录，通常会将可执行文件放在`bin`子目录中。

7. `set(CMAKE_CXX_STANDARD 11)`：这一行指定了项目所使用的C++标准。

8. `add_subdirectory(subdirectory_name)`：这一行用于包括子目录，如果项目需要包括其他模块或库，你可以在子目录中定义另一个CMakeLists.txt文件。

9. `include(subdirectory_name/CMakeLists.txt)`：这一行可以用于包括其他CMakeLists.txt文件，如果你希望将其他项目的构建规则包括到当前项目中。

这只是一个简单的示例，你可以根据项目的需求和复杂性来扩展和修改CMakeLists.txt文件。CMake提供了广泛的选项和命令，以支持各种不同类型的项目和构建需求。

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