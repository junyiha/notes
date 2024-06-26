---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_86_automake
tag: LinuxCommand
---
## 简介

+ automake命令

## linux automake命令 详解

`automake` 是 GNU Build System 工具链的一部分，用于自动生成 Makefile.in 文件，这些文件后续可以通过 `configure` 脚本生成 Makefile 文件。它主要用于简化软件包的构建过程，特别是在跨平台开发中。以下是关于 `automake` 命令的详细解释：

1. **概述**：
   `automake` 的作用是根据开发者提供的 Makefile.am 文件生成 Makefile.in 文件。这些 Makefile.in 文件包含了构建软件包所需的规则和命令。然后，通过运行 `configure` 脚本，可以根据系统环境和用户配置生成最终的 Makefile 文件。

2. **工作原理**：
   开发者编写 `Makefile.am` 文件，其中包含了构建软件包所需的规则、依赖和命令。然后通过 `automake` 命令生成对应的 `Makefile.in` 文件。`Makefile.in` 文件是一个模板，其中的变量会在运行 `configure` 脚本时替换为具体的值，生成最终的 `Makefile`。

3. **用法**：
   `automake` 命令的基本用法如下：
   ```
   automake [OPTION] [FILE]
   ```
   其中，`FILE` 是 `Makefile.am` 文件的路径。如果不指定 `FILE`，则 `automake` 将会在当前目录中寻找默认的 `Makefile.am` 文件。

4. **选项**：
   - `-a` 或 `--add-missing`：添加缺失的文件到软件包中，例如缺失的 `install-sh` 和 `missing` 脚本等。
   - `-c` 或 `--copy`：复制生成的文件到当前目录，而不是链接。
   - `-f` 或 `--force-missing`：即使存在缺失的文件，也继续生成 Makefile.in 文件。
   - `-W` 或 `--warnings=category`：设置警告级别，可选的 `category` 包括 `none`、`error`、`no-`*`warning-category`、`error-`*`warning-category` 等。
   - `-h` 或 `--help`：显示帮助信息。
   - `-V` 或 `--version`：显示版本信息。

5. **示例**：
   ```
   automake          # 生成默认的 Makefile.in 文件（从 Makefile.am）
   automake myproject/Makefile.am   # 从指定的 Makefile.am 文件生成 Makefile.in 文件
   ```

6. **注意事项**：
   - `automake` 需要和 `autoconf` 配合使用，通常在 `configure.ac` 中使用 `AM_INIT_AUTOMAKE` 宏来配置 `automake`。
   - `Makefile.am` 文件使用了一种简化的 Makefile 语法，定义了各种规则、依赖和命令，但并不直接包含目标文件或最终的构建规则。这些信息会在运行 `configure` 脚本时根据系统环境和用户配置生成最终的 `Makefile` 文件。
   - `automake` 自动生成的 `Makefile.in` 文件是跨平台的，通常不需要修改即可在不同的系统上使用。

`automake` 在 GNU Build System 中扮演着重要的角色，它简化了软件包的构建过程，使得软件包能够更容易地在不同的系统上进行构建和安装。