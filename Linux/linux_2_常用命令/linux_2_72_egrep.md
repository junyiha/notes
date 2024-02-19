## 简介

+ egrep命令

## linux egrep命令 详解

`egrep` 命令在 Linux 系统中用于执行扩展正则表达式的匹配操作。它在功能上与 `grep -E` 相同。正则表达式是一种用于模式匹配的强大工具，`egrep` 允许你使用更复杂的正则表达式语法。以下是一些 `egrep` 命令的常用选项和用法：

### 1. **基本用法：**
```bash
egrep "pattern" file
```
这将在指定的文件中搜索匹配指定模式的行。

### 2. **使用多个模式：**
```bash
egrep "pattern1|pattern2" file
```
使用 `|`（管道符）可以指定多个模式，表示匹配任意一个模式的行。

### 3. **忽略大小写：**
```bash
egrep -i "pattern" file
```
使用 `-i` 选项可以忽略大小写进行匹配。

### 4. **显示匹配的行号：**
```bash
egrep -n "pattern" file
```
使用 `-n` 选项可以显示匹配行的行号。

### 5. **显示不匹配的行：**
```bash
egrep -v "pattern" file
```
使用 `-v` 选项可以显示不匹配指定模式的行。

### 6. **只显示匹配的文本：**
```bash
egrep -o "pattern" file
```
使用 `-o` 选项可以只显示匹配的文本，而不显示整行。

### 7. **显示匹配的行及其前后若干行：**
```bash
egrep -A num "pattern" file
egrep -B num "pattern" file
egrep -C num "pattern" file
```
使用 `-A`、`-B` 和 `-C` 选项可以分别显示匹配行及其后 num 行、前 num 行、前后各 num 行。

### 8. **递归搜索目录下的文件：**
```bash
egrep -r "pattern" directory
```
使用 `-r` 选项可以递归搜索指定目录及其子目录下的文件。

### 9. **显示匹配的行数：**
```bash
egrep -c "pattern" file
```
使用 `-c` 选项可以只显示匹配行的数量。

### 10. **使用反向引用（Backreference）：**
```bash
egrep '(pattern)\1' file
```
使用圆括号和 `\1` 可以引用之前的模式，实现反向引用。

### 11. **匹配行首或行尾：**
```bash
egrep "^pattern" file
egrep "pattern$" file
```
`^` 表示匹配行首，`$` 表示匹配行尾。

### 12. **显示匹配模式的位置：**
```bash
egrep -b -o "pattern" file
```
使用 `-b` 选项可以显示匹配模式的字节偏移位置。

### 13. **显示匹配模式的数量：**
```bash
egrep -o "pattern" file | wc -l
```
使用管道结合 `wc -l` 命令可以显示匹配模式的数量。

这些是一些 `egrep` 命令的常用选项和用法，可以帮助你在文本文件中执行强大的正则表达式匹配操作。

## linux egrep命令 常用技巧

`egrep` 命令是 `grep` 命令的扩展版本，支持使用扩展正则表达式进行文本搜索。在许多系统中，`egrep` 和 `grep -E` 是等效的。以下是一些常用的 `egrep` 命令技巧和选项：

### 1. **基本用法：**
```bash
egrep "pattern" filename
```
`egrep` 命令用于在文件中搜索指定的正则表达式模式，并显示匹配的行。可以使用单引号或双引号括起正则表达式。

### 2. **显示匹配行及行号：**
```bash
egrep -n "pattern" filename
```
使用 `-n` 选项可以显示匹配行的行号。

### 3. **显示不匹配的行：**
```bash
egrep -v "pattern" filename
```
使用 `-v` 选项可以显示不匹配指定模式的行。

### 4. **显示匹配行前/后的内容：**
```bash
egrep -A 2 "pattern" filename  # 显示匹配行及后两行的内容
egrep -B 2 "pattern" filename  # 显示匹配行及前两行的内容
egrep -C 2 "pattern" filename  # 显示匹配行及前后各两行的内容
```
使用 `-A`、`-B`、`-C` 选项可以显示匹配行前后的指定行数的内容。

### 5. **忽略大小写进行匹配：**
```bash
egrep -i "pattern" filename
```
使用 `-i` 选项可以忽略大小写进行匹配。

### 6. **显示匹配的行数：**
```bash
egrep -c "pattern" filename
```
使用 `-c` 选项可以显示匹配的行数而不是匹配的行内容。

### 7. **显示匹配的内容及模式：**
```bash
egrep -o "pattern" filename
```
使用 `-o` 选项可以只显示匹配的内容而不是整行，并且仅显示匹配的模式。

### 8. **显示匹配模式的行数：**
```bash
egrep -o -n "pattern" filename | wc -l
```
结合 `wc -l` 命令可以显示匹配模式的行数。

### 9. **显示行尾包含匹配模式的行：**
```bash
egrep "pattern$" filename
```
在模式的末尾使用 `$` 可以显示行尾包含匹配模式的行。

### 10. **使用多个模式进行匹配：**
```bash
egrep "pattern1|pattern2" filename
```
使用 `|` 可以匹配多个模式之一的行。

### 11. **显示匹配模式的上下文：**
```bash
egrep -C 2 "pattern" filename
```
使用 `-C` 选项可以显示匹配模式的上下文内容。

### 12. **递归搜索目录中的文件：**
```bash
egrep -r "pattern" directory
```
使用 `-r` 选项可以递归搜索指定目录中的文件。

这些技巧和选项可以帮助你更灵活地使用 `egrep` 命令进行文本搜索，根据具体的需求选择合适的选项和正则表达式模式。

## egrep 详解

`egrep` 命令是 Linux 系统中用于进行正则表达式搜索的工具之一。它是 `grep` 命令的一个变种，支持扩展的正则表达式语法。下面是关于 `egrep` 命令的详细解释：

### 基本语法

`egrep` 命令的基本语法如下：

```
egrep [选项] 模式 [文件...]
```

- `选项`：可以是一系列的命令行选项，用于控制 `egrep` 的行为。
- `模式`：是一个正则表达式，用于搜索匹配的文本。
- `文件`：可选参数，表示要在其中搜索模式的一个或多个文件。如果省略文件参数，则 `egrep` 将从标准输入中读取数据。

### 常用选项

以下是一些常用的 `egrep` 选项：

- `-i`：忽略大小写，使搜索不区分大小写。
- `-v`：反向匹配，只输出不匹配模式的行。
- `-r` 或 `-R`：递归搜索，用于在目录中搜索文件，而不仅仅是单个文件。
- `-n`：显示匹配行的行号。
- `-c`：仅显示匹配行的计数而不是行本身。
- `-l`：只显示包含匹配的文件名，而不显示匹配的行。
- `-o`：只输出匹配的部分，而不是整行。
- `-A`、`-B`、`-C`：显示匹配行的上下文。

### 正则表达式语法

`egrep` 支持扩展的正则表达式语法，其中包括一些特殊字符和元字符，如 `.`（匹配任意字符）、`*`（匹配前一个字符的零个或多个实例）、`+`（匹配前一个字符的一个或多个实例）等。你可以使用这些元字符来构建强大的正则表达式模式，以匹配特定的文本模式。

### 示例

以下是一些 `egrep` 命令的示例：

1. 在文件中查找包含 "error" 或 "warning" 的行，并显示行号：
   ```
   egrep -n 'error|warning' filename.txt
   ```

2. 在目录及其子目录中递归搜索包含 "pattern" 的文件：
   ```
   egrep -r 'pattern' /path/to/directory
   ```

3. 显示包含匹配的文件名：
   ```
   egrep -l 'pattern' *.txt
   ```

4. 使用反向匹配查找不包含 "success" 的行：
   ```
   egrep -v 'success' filename.txt
   ```

这些示例只是 `egrep` 命令的一些用法，你可以根据需要构建更复杂的正则表达式模式和命令行选项来满足特定的搜索需求。要了解更多信息，可以使用 `man egrep` 命令查看 `egrep` 的手册页。