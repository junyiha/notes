## spdlog 开源库分析

### 1.1 概述

+ 使用方法一：
  + 下载好项目源代码，使用cmake编译，命令:`cmake -S . -B build`，然后进入build进行make，会获取到一个静态库 `libspdlog.a`
  + 之后通过包含include下的头文件和链接生成的静态库，使用spdlog

+ 使用方法二：
  + 将头文件和源文件分别添加到相应工程中的头文件和源文件
  + 然后再CMakeLists.txt中添加头文件目录和源文件目录，并且添加一条命令用来编译指定文件：`target_compile_definitions(${PROJECT_NAME} PUBLIC SPDLOG_COMPILED_LIB)`

### 1.2 基本用法

+ 输出日志信息到标准输出
  + `spdlog::info("This is a log message.{0} {1}", "hello", "world")`
  + `spdlog::warn("This is a warn message");`
  + `spdlog::debug("This message should not be displayed");`
  + `spdlog::set_level(spdlog::level::trace);  // set specifice logger's log level`
  + `spdlog::debug("This message should be displayed, because the level is setted trace");`

+ 日志信息输出到文件
  + 创建基础日志文件：
    + `#include "spdlog/sinks/basic_file_sink.h"`
    + `auto my_logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt", true);`
    + 创建一个文件为`logs/basic-log.txt`，并设置输出的消息标识为`file_logger`的日志文件，通过使用`my_logger`来操作该日志文件
  + 将日志输出到日志文件中：
    + `my_logger->info("Helo Info");`

+ 输出行号：
  + `SPDLOG_DEBUG("some debug message about program: {}", "robot");`