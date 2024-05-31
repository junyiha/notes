---
category: Tools
date: 2024-05-22 09:00:00 +0800
layout: post
title: PlatformIO
tag: Tools
---
## 简介

+ 嵌入式开发板编程IDE笔记
+ 官方文档
  + https://docs.platformio.org/en/latest/integration/ide/vscode.html#quick-start

## platformIO 详解

PlatformIO 是一个开源的跨平台的物联网（IoT）开发生态系统，它用于嵌入式系统和嵌入式应用程序的开发。PlatformIO 提供了一个强大的集成开发环境（IDE），支持多种硬件平台，包括Arduino、ESP8266、ESP32、Raspberry Pi等，以及多种开发框架，如Arduino、Mbed、FreeRTOS等。以下是 PlatformIO 的主要特点和功能的详细解释：

1. **多平台支持**：PlatformIO 可以在不同的操作系统上运行，包括 Windows、macOS 和 Linux，因此可以轻松迁移到不同的开发环境。

2. **多硬件平台支持**：PlatformIO 支持多种硬件平台，使开发人员能够在不同的嵌入式设备上进行开发，而无需为每个平台使用不同的开发工具。

3. **多框架支持**：PlatformIO 支持多种开发框架和库，包括 Arduino、Mbed、ESP-IDF、STM32Cube等，使开发人员能够选择适合其项目的最佳框架。

4. **集成开发环境 (IDE)**：PlatformIO 提供了一个集成开发环境，使开发人员能够方便地编写、构建、上传和调试嵌入式应用程序。PlatformIO 支持 Visual Studio Code（VSCode）等流行的文本编辑器和IDE。

5. **自动依赖管理**：PlatformIO 自动处理项目依赖关系，包括库、框架和工具链，以确保项目能够顺利构建和运行。

6. **自动固件升级**：PlatformIO 具有内置的固件升级工具，使嵌入式设备的固件更新变得更加容易。

7. **强大的命令行工具**：PlatformIO 还提供了命令行工具，使开发人员能够自动化和自定义开发流程，以满足其特定需求。

8. **丰富的插件生态系统**：PlatformIO 的插件系统使开发人员能够扩展其功能，添加新硬件平台、框架、工具等。

9. **跨平台固件开发**：PlatformIO 使开发人员能够开发跨不同平台的嵌入式固件，从单片机到嵌入式Linux系统。

总的来说，PlatformIO 是一个强大且灵活的工具，适用于嵌入式系统开发人员，它简化了开发流程，提供了一体化的开发环境，支持多种硬件平台和开发框架，以及自动化依赖管理，从而大大提高了嵌入式开发的效率。如果您是嵌入式开发人员或对嵌入式系统感兴趣，PlatformIO 是一个值得考虑的工具。

## platformIO VSCode插件 使用 详解

PlatformIO 在 Visual Studio Code（VSCode）中提供了一个功能强大的插件，使嵌入式系统开发变得更加便捷。以下是详细的 PlatformIO VSCode 插件的使用说明：

**1. 安装 PlatformIO 插件：**
   - 打开 Visual Studio Code (VSCode)。
   - 在左侧的 Extensions (扩展) 面板中，搜索 "PlatformIO IDE" 并安装该插件。

**2. 创建或打开 PlatformIO 项目：**
   - 如果您已有一个 PlatformIO 项目，可以直接在 VSCode 中打开它，或者您可以使用 `File` -> `New Project` 创建一个新项目。
   
**3. 配置项目：**
   - 在项目文件夹中，打开 `platformio.ini` 文件。这个文件用于配置项目的硬件平台、框架、依赖库等。
   - 在 `platformio.ini` 文件中，您可以指定目标硬件板（`[env]` 部分）、选择框架、添加依赖库等。

**4. 编写代码：**
   - 在 VSCode 中创建或打开源代码文件（通常是 `.cpp` 或 `.ino` 文件），然后开始编写嵌入式代码。

**5. 构建项目：**
   - 使用 PlatformIO 插件，您可以构建项目。在 VSCode 中，点击底部工具栏的构建按钮（绿色的勾号），或者使用快捷键（通常是 Ctrl + Alt + B）来构建项目。

**6. 上传固件：**
   - 构建成功后，您可以将固件上传到目标硬件板。在 VSCode 中，点击底部工具栏的上传按钮（右边的右箭头），或使用快捷键（通常是 Ctrl + Alt + U）来上传固件。

**7. 调试项目（可选）：**
   - 如果您需要调试嵌入式应用程序，PlatformIO 插件支持硬件调试器。您可以配置调试器，设置断点，以及使用 VSCode 的调试功能进行嵌入式代码的调试。

**8. 库管理：**
   - PlatformIO 插件支持库管理。您可以搜索、安装、升级和删除依赖库，以简化项目的依赖管理。这可以在 VSCode 中的 PlatformIO Sidebar（侧边栏）中完成。

**9. 终端和监控：**
   - PlatformIO 插件集成了终端和监控功能。您可以在 VSCode 中的 PlatformIO Sidebar 中打开终端，以运行特定的命令。监控功能可用于查看串口输出。

**10. 插件设置：**
   - 您可以通过点击 VSCode 左下角的齿轮图标（设置按钮）来访问 PlatformIO 插件的设置。这里您可以进行各种自定义设置，包括构建选项、上传速度、调试器配置等。

PlatformIO 插件在 VSCode 中提供了一个完整的嵌入式开发环境，支持多种硬件平台和开发框架。通过 VSCode 的集成性和 PlatformIO 的功能，您可以在一个集成的环境中完成项目配置、编码、构建、上传和调试，提高了嵌入式开发的效率。如果您是嵌入式开发人员或对嵌入式系统感兴趣，PlatformIO 插件是一个强大的工具，使您能够更轻松地进行开发和调试。

## platformio.ini文件 常见的配置参数

`platformio.ini` 文件是PlatformIO项目的配置文件，用于指定项目的构建、上传、目标设备以及其他参数。以下是一些常见的`platformio.ini`配置参数：

1. **平台和框架选择**:
   - `platform`：指定目标平台，如Arduino、Espressif、Raspberry Pi等。
   - `framework`：指定项目使用的框架，如Arduino、Mbed、ESP-IDF等。

```ini
[env:my_target]
platform = espressif8266
framework = arduino
```

2. **目标环境配置**:
   - `board`：选择目标开发板型号。
   - `board_build.mcu`：指定目标微控制器型号。
   - `board_build.f_cpu`：指定目标CPU的时钟频率。

```ini
[env:my_target]
board = nodemcu
board_build.mcu = esp8266
board_build.f_cpu = 80000000L
```

3. **串口配置**:
   - `upload_port`：指定上传固件时的串口端口。
   - `monitor_port`：指定监控串口端口。

```ini
[env:my_target]
upload_port = COM3
monitor_port = COM3
```

4. **编译参数**:
   - `build_flags`：添加编译选项，如宏定义、编译标志等。
   - `extra_scripts`：引用自定义脚本以进行更高级的构建操作。

```ini
[env:my_target]
build_flags = -D DEBUG_MODE
extra_scripts = custom_script.py
```

5. **库依赖**:
   - `lib_deps`：指定项目所需的库依赖。

```ini
[env:my_target]
lib_deps =
    Wire
    Adafruit Unified Sensor
```

6. **上传和调试工具配置**:
   - `upload_protocol`：指定上传协议，如`stlink`、`espota`、`avr109`等。
   - `debug_tool`：指定调试工具，如`stlink`, `esp-prog`, `jlink`等。

```ini
[env:my_target]
upload_protocol = espota
debug_tool = esp-prog
```

7. **上传速度和端口配置**:
   - `upload_speed`：指定上传速度，如`115200`。
   - `monitor_speed`：指定监控串口的波特率。

```ini
[env:my_target]
upload_speed = 921600
monitor_speed = 115200
```

8. **其他项目设置**:
   - `platform_packages`：指定特定平台的软件包。
   - `extra_configs`：引用其他配置文件。

```ini
[env:my_target]
platform_packages = framework-arduinoespressif8266
extra_configs = additional_config.ini
```

这些是一些常见的`platformio.ini`配置参数，您可以根据您的项目需求进行自定义。`platformio.ini`文件使您能够轻松配置PlatformIO项目的各个方面，以适应特定的硬件和软件需求。