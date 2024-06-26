---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_05_pkg_config
tag: LinuxCommand
---
## 简介

+ pkg-config 工具的笔记

## linux pkg-config 是什么

`pkg-config` 是一个用于帮助管理软件包依赖关系的工具，特别是在 Linux 系统上。它允许开发者查询已安装的库的信息，以便在编译和链接时正确地设置相关的编译器和链接器选项。

具体而言，`pkg-config` 主要有以下功能：

1. **查询已安装库的信息：** 开发者可以使用 `pkg-config` 查询已安装的库的版本、包含路径、链接标志等信息。

2. **提供正确的编译和链接选项：** 在编译和链接程序时，`pkg-config` 可以生成正确的编译器和链接器选项，确保程序正确地链接到所需的库。

3. **简化构建过程：** 使用 `pkg-config` 可以使构建过程更加简化和可移植。开发者可以通过查询库的信息来适应不同的系统和环境。

例如，如果你想编写一个使用 GTK+ 图形库的程序，你可以使用 `pkg-config` 查询 GTK+ 库的信息，并在编译和链接时使用返回的选项，而不必手动设置这些选项。

以下是 `pkg-config` 命令的一些基本用法：

- `pkg-config --list-all`: 列出系统上所有已安装的库和它们的信息。
- `pkg-config --cflags <package>`: 返回指定库的编译选项。
- `pkg-config --libs <package>`: 返回指定库的链接选项。

例如，要获取 GTK+ 库的编译选项，可以运行：

```bash
pkg-config --cflags gtk+-3.0
```

`pkg-config` 在许多 Linux 发行版中都是默认安装的，因此大多数开发者可以直接使用它来简化软件构建过程。

## pkg-config 详解

`pkg-config` 是一个在 Linux 和类 Unix 系统中用于获取编译和链接库信息的工具。它可以帮助开发者配置和编译软件项目，以便正确地链接所需的外部库和头文件。以下是关于 `pkg-config` 的详细解释：

**基本用法：**
`pkg-config` 的基本用法是通过在命令行中调用它，并传递一些选项和参数来获取有关库的信息。

```bash
pkg-config [options] package-names
```

- `options`：一些选项，用于控制 `pkg-config` 的行为。
- `package-names`：要查询的库的名称。它通常是你希望查找的库的名称，如 `opencv`, `gtk+-3.0` 等。

**常用选项：**
- `--cflags`：获取用于编译的头文件路径和编译器选项。
- `--libs`：获取用于链接的库路径和链接器选项。
- `--modversion`：获取库的版本号。
- `--list-all`：列出系统中所有已安装的库及其版本。

**示例用法：**
以下是一个使用 `pkg-config` 的示例，假设你想编译一个使用 GTK+ 3 的简单程序：

1. 查询 GTK+ 3 的编译选项（头文件路径和编译器选项）：

```bash
pkg-config --cflags gtk+-3.0
```

2. 查询 GTK+ 3 的链接选项（库路径和链接器选项）：

```bash
pkg-config --libs gtk+-3.0
```

3. 编译程序（假设程序名为 `myapp`）：

```bash
gcc myapp.c -o myapp `pkg-config --cflags --libs gtk+-3.0`
```

**优点：**
- `pkg-config` 确保了在编译和链接软件时，所需的库路径、头文件路径以及编译和链接选项都是正确的，减少了因为路径错误或选项不匹配而导致的问题。
- 它是一个跨平台的工具，在多个 Linux 发行版和类 Unix 系统中都可使用。

**注意事项：**
- 要使用 `pkg-config`，你需要安装相关的库及其开发包（通常是以 `-dev` 或 `-devel` 结尾的包）。
- 一些库可能不支持 `pkg-config`，或者可能有不同的名称和用法，需要查阅它们的文档。

总之，`pkg-config` 是一个有助于简化库配置和编译过程的工具，它可以提供关于库的编译和链接信息，减少了配置和构建软件项目的复杂性。

## pkg-config 常用选项

`pkg-config` 工具提供了一些常用选项，用于获取有关库的信息，例如头文件路径、库路径和版本等。以下是一些常用的 `pkg-config` 选项：

1. `--cflags`：用于获取用于编译的头文件路径和编译器选项。

```bash
pkg-config --cflags package-name
```

示例：

```bash
pkg-config --cflags gtk+-3.0
```

2. `--libs`：用于获取用于链接的库路径和链接器选项。

```bash
pkg-config --libs package-name
```

示例：

```bash
pkg-config --libs gtk+-3.0
```

3. `--modversion`：获取库的版本号。

```bash
pkg-config --modversion package-name
```

示例：

```bash
pkg-config --modversion opencv
```

4. `--list-all`：列出系统中所有已安装的库及其版本。

```bash
pkg-config --list-all
```

5. `--static`：获取静态库的链接选项。

```bash
pkg-config --static package-name
```

示例：

```bash
pkg-config --static zlib
```

6. `--variable`：获取特定变量的值，如 `pkg-config --variable=prefix package-name` 可以获取库的安装路径。

```bash
pkg-config --variable=variable-name package-name
```

示例：

```bash
pkg-config --variable=prefix opencv
```

7. `--exists`：检查库是否存在。

```bash
pkg-config --exists package-name
```

示例：

```bash
pkg-config --exists libpng
```

8. `--help`：获取关于 `pkg-config` 命令的帮助信息。

```bash
pkg-config --help
```

这些选项可以根据你的需要来使用，它们可以帮助你获取关于特定库的编译和链接信息，以便在开发过程中正确地配置和编译你的项目。

## pkg-config 查看所有库

要查看系统中安装的所有库及其版本，可以使用以下命令：

```bash
pkg-config --list-all
```

运行这个命令会列出系统中已安装的所有库的名称和版本信息。输出可能会非常长，所以你可以将输出通过分页工具如 `less` 进行分页显示：

```bash
pkg-config --list-all | less
```

使用上述命令，你可以查看系统中已经安装的所有库，以便在开发软件项目时了解可用的库资源。

## linux pkg-config 查看指定目录的配置文件

要使用`pkg-config`命令查看指定目录的配置文件，你可以通过设置`PKG_CONFIG_PATH`环境变量来指定`pkg-config`应该搜索的目录。然后，你可以使用`pkg-config`命令来查询指定库的配置信息。

以下是一些步骤：

1. 设置`PKG_CONFIG_PATH`环境变量以包含你希望`pkg-config`搜索的目录。假设你希望`pkg-config`在`/path/to/your/dir`目录中搜索配置文件，你可以执行以下命令：

```bash
export PKG_CONFIG_PATH=/path/to/your/dir:$PKG_CONFIG_PATH
```

2. 使用`pkg-config`命令查询指定库的配置信息。例如，如果你想查询`libfoo`库的配置信息，你可以执行：

```bash
pkg-config --modversion libfoo
```

或者，如果你想获取更多有关该库的信息，你可以执行：

```bash
pkg-config --libs --cflags libfoo
```

这将显示用于编译和链接应用程序的选项。

请注意，设置`PKG_CONFIG_PATH`只是临时的，仅在当前终端会话中有效。如果你希望在每次登录时都设置这个环境变量，你可以将其添加到你的shell配置文件（例如`~/.bashrc`或`~/.bash_profile`）中。