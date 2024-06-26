---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_37_whereis
tag: LinuxCommand
---
## 简介

+ whereis命令

## linux whereis命令 详解

`whereis` 是 Linux 中的一个用于查找二进制、源代码和帮助文档文件的命令。它提供了一种简便的方式来查找系统中特定文件或程序的位置。以下是`whereis`命令的详解：

### 基本语法：

```bash
whereis [选项] 文件或程序名
```

### 常用选项：

- **-b：** 限制搜索二进制文件。
- **-m：** 限制搜索帮助手册文件。
- **-s：** 限制搜索源代码文件。
- **-u：** 显示不包括指定文件类型的位置。

### 示例：

1. **查找二进制文件：**
   ```bash
   whereis ls
   ```
   这将返回 `ls` 命令的二进制文件、帮助文件和源代码文件的路径。

2. **限制搜索类型：**
   ```bash
   whereis -b ls
   ```
   仅显示 `ls` 命令的二进制文件路径。

3. **查找帮助文档：**
   ```bash
   whereis -m ls
   ```
   仅显示 `ls` 命令的帮助文档路径。

4. **查找源代码：**
   ```bash
   whereis -s ls
   ```
   仅显示 `ls` 命令的源代码路径。

5. **显示多个文件的位置：**
   ```bash
   whereis ls grep
   ```
   查找多个文件或程序的位置。

6. **显示不同类型的位置：**
   ```bash
   whereis -b -m ls
   ```
   仅显示 `ls` 命令的二进制文件和帮助文档路径。

7. **不同文件类型的路径：**
   ```bash
   whereis -u ls
   ```
   显示不包括 `ls` 命令的源代码文件的路径。

### 注意事项：

- `whereis` 主要用于查找系统命令或文件，不适用于用户自定义的脚本或其他非系统提供的文件。
- `whereis` 会搜索默认的系统路径，如 `/bin`、`/usr/bin` 等，因此，如果某个程序或文件不在这些路径下，`whereis` 将无法找到它。

总的来说，`whereis` 是一个方便的工具，用于快速查找系统中二进制、源代码和帮助文档文件的位置。如果需要查找更广泛范围的文件，或者需要自定义搜索路径，可能需要使用其他工具如 `find` 或 `locate`。

## linux whereis命令 常用技巧

虽然 `whereis` 命令相对简单，但你可以通过一些技巧来更灵活地使用它：

1. **结合通配符进行模糊搜索：**
   ```bash
   whereis -b -u "*keyword*"
   ```
   使用通配符 `*` 可以进行模糊搜索，查找包含指定关键字的二进制文件。

2. **使用管道和其他命令：**
   ```bash
   whereis -b command | xargs ls -l
   ```
   结合 `xargs` 可以将 `whereis` 的输出作为参数传递给其他命令，这里是 `ls -l`。

3. **输出详细信息：**
   ```bash
   whereis -l ls
   ```
   使用 `-l` 选项可以输出详细的信息，包括文件类型和路径。

4. **查找共享库文件：**
   ```bash
   whereis -M /lib /usr/lib -f libc.so
   ```
   使用 `-M` 选项指定额外的搜索路径，查找共享库文件。

5. **在路径中搜索指定文件类型：**
   ```bash
   whereis -b -B /path/to/search -f filename
   ```
   使用 `-B` 选项指定自定义搜索路径，查找指定文件类型。

6. **使用别名简化命令：**
   ```bash
   alias ws='whereis -b -m -s'
   ws command
   ```
   创建一个别名（这里是 `ws`），以简化 `whereis` 的命令行输入。

7. **结合 `find` 进行更复杂的搜索：**
   ```bash
   find $(whereis -b command | cut -d' ' -f2) -name "*.txt"
   ```
   使用 `find` 命令可以基于 `whereis` 的结果执行更复杂的搜索操作。

8. **将 `whereis` 结果导入数组：**
   ```bash
   paths=($(whereis -b command | cut -d' ' -f2))
   echo "${paths[0]}"
   ```
   将 `whereis` 的输出导入到 Bash 数组中，以便进一步处理。

9. **显示文件权限和所有者：**
   ```bash
   whereis -l ls | xargs ls -l
   ```
   结合 `-l` 选项和 `xargs` 来显示文件的权限和所有者信息。

10. **过滤结果：**
    ```bash
    whereis -b command | grep "/bin/"
    ```
    使用 `grep` 命令过滤 `whereis` 的输出，只显示包含 "/bin/" 的路径。

这些技巧可以帮助你更好地利用 `whereis` 命令，使其更适应你的需求。根据具体情况，你可能会结合其他命令和选项以达到更复杂的搜索和操作。

## whereis  

+ 检查二进制文件和库文件的位置
  + `whereis systemctl`

在Linux中，`whereis`命令用于定位可执行程序、源代码文件和帮助文档的位置。它提供了一个简单的方法来查找特定命令或文件在系统中的位置。

以下是`whereis`命令的一般语法：

```
whereis [options] command
```

其中，`options`是可选的一些选项，`command`是要查找的命令或文件。

以下是一些常见的`whereis`命令选项和用法：

1. 查找可执行程序：
   ```
   whereis ls
   ```

   此命令将显示`ls`命令的可执行程序位置。

2. 查找源代码文件：
   ```
   whereis grep
   ```

   此命令将显示`grep`命令的源代码文件位置。

3. 查找帮助文档：
   ```
   whereis man
   ```

   此命令将显示`man`命令的帮助文档位置。

`whereis`命令会搜索特定文件类型的位置，并显示相关信息，包括可执行程序、源代码和帮助文档的路径。它会搜索系统默认的搜索路径，如`/bin`、`/usr/bin`等。

请注意，`whereis`命令仅搜索已经建立索引的文件和路径，因此可能无法找到某些文件。另外，它不会搜索用户自定义的路径或目录。