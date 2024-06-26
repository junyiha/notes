---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_42_realpath
tag: LinuxCommand
---
## 简介

+ realpath命令 

## linux realpath命令 详解

`realpath` 命令用于获取指定文件或目录的真实路径。它会解析所有的符号链接并显示最终的规范化路径。以下是关于 `realpath` 命令的详细解释：

### 语法：

```bash
realpath [选项] 文件名
```

### 常用选项：

- `-e`：如果文件不存在，则不输出任何信息。
- `-m`：相当于 `--canonicalize-missing`，如果文件不存在，则不输出任何信息。

### 示例用法：

1. **显示文件的真实路径：**
   ```bash
   realpath filename
   ```
   这将显示指定文件的真实路径，解析所有符号链接。

2. **显示目录的真实路径：**
   ```bash
   realpath /path/to/directory
   ```
   类似于文件，也可以用于显示指定目录的真实路径。

3. **如果文件不存在，则不输出任何信息：**
   ```bash
   realpath -e non_existent_file
   ```
   使用 `-e` 选项，如果文件不存在，则不输出任何信息。

4. **相当于 `-e` 的另一种写法：**
   ```bash
   realpath -m non_existent_file
   ```
   使用 `-m` 选项，也可以达到如果文件不存在，则不输出任何信息的效果。

### 工作原理：

`realpath` 命令通过递归解析所有的符号链接来获取文件或目录的真实路径。它能够处理相对路径和绝对路径，并返回规范化的绝对路径。

### 注意事项：

- 在一些较旧的系统上，可能需要安装 `coreutils` 包（通常包含 `realpath`）来使用该命令。
- 对于不存在的文件，`realpath` 在默认情况下会输出错误消息，使用 `-e` 或 `-m` 选项可以避免这种输出。

### 示例输出：

```
/path/to/filename
```

`realpath` 命令是在处理文件路径时非常有用的工具，尤其是当路径中包含符号链接或相对路径时。通过返回规范化的绝对路径，它有助于确保脚本或程序可以准确地访问所需的文件或目录。

## linux realpath命令 常用技巧

`realpath` 命令在处理文件路径时非常实用，以下是一些常用的技巧：

1. **显示文件的真实路径：**
   ```bash
   realpath filename
   ```
   最简单和最基本的用法是显示指定文件的真实路径。

2. **显示目录的真实路径：**
   ```bash
   realpath /path/to/directory
   ```
   类似于文件，也可以用于显示指定目录的真实路径。

3. **将相对路径转换为绝对路径：**
   ```bash
   realpath relative/path/to/file
   ```
   `realpath` 可以将相对路径转换为绝对路径，方便在脚本中使用。

4. **显示目录中的所有文件的真实路径：**
   ```bash
   realpath /path/to/directory/*
   ```
   使用通配符，可以一次性显示目录中所有文件的真实路径。

5. **将路径保存到变量中：**
   ```bash
   filepath=$(realpath filename)
   echo $filepath
   ```
   将文件的真实路径保存到变量中，以便在脚本中进一步使用。

6. **判断文件是否存在并获取真实路径：**
   ```bash
   if [ -e filename ]; then
       realpath filename
   else
       echo "File not found."
   fi
   ```
   使用 `-e` 选项，可以判断文件是否存在，如果存在则显示真实路径。

7. **使用 `readlink` 代替 `realpath`：**
   ```bash
   readlink -f filename
   ```
   在一些系统上，`readlink` 也可以用来获取文件的真实路径，效果类似于 `realpath`。

8. **结合其他命令使用：**
   ```bash
   cd $(realpath /path/to/directory)
   ```
   可以结合其他命令使用，比如在脚本中切换到指定目录。

9. **使用 `-e` 选项检查路径的有效性：**
   ```bash
   realpath -e /path/to/possibly/invalid/path
   ```
   使用 `-e` 选项，可以检查路径是否有效，如果无效则不输出任何信息。

这些技巧可以使你更灵活地使用 `realpath` 命令，适应不同的场景和需求。

## realpath  

+ 获取指定文件或目录的绝对路径

在Linux中，`realpath`命令用于获取给定路径的绝对路径。它会解析所有符号链接，并返回路径的规范化版本，消除任何冗余或相对路径。

以下是`realpath`命令的一般语法：

```
realpath [options] file(s)
```

其中，`options`是可选的一些选项，`file(s)`是要获取绝对路径的文件或目录列表。

以下是一些常见的`realpath`命令选项和用法：

1. 获取文件的绝对路径：
   ```
   realpath file.txt
   ```

   此命令将返回`file.txt`文件的绝对路径。

2. 获取目录的绝对路径：
   ```
   realpath /usr/local/bin
   ```

   此命令将返回`/usr/local/bin`目录的绝对路径。

`realpath`命令可以用于解析路径中的符号链接并返回规范化的绝对路径。它对于需要获取路径的确切位置和处理文件路径的任务非常有用。

请注意，`realpath`命令需要指定的路径存在才能返回绝对路径。如果路径不存在或无法访问，它会产生错误。
