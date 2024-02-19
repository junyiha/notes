## 简介

+ mkdir命令

## linux mkdir命令 详解

`mkdir` 是 Linux 系统中用于创建目录（文件夹）的命令。它允许用户在文件系统中创建一个或多个新的目录。以下是关于 `mkdir` 命令的详细说明：

### 基本用法：

```bash
mkdir [OPTION] DIRECTORY...
```

### 参数说明：

- **DIRECTORY：** 要创建的目录的名称，可以同时指定多个目录。

### 常用选项：

- **-m, --mode=MODE：** 设置新创建目录的权限模式（权限掩码）。
- **-p, --parents：** 递归创建目录，如果上级目录不存在也一并创建。
- **-v, --verbose：** 显示创建过程中的详细信息。

### 示例：

1. **创建单个目录：**
   ```bash
   mkdir my_directory
   ```
   创建一个名为 `my_directory` 的新目录。

2. **递归创建目录：**
   ```bash
   mkdir -p /path/to/parent/directory/new_directory
   ```
   使用 `-p` 选项可以递归创建目录，即使上级目录不存在也会创建。

3. **设置目录权限：**
   ```bash
   mkdir -m 755 my_directory
   ```
   使用 `-m` 选项可以设置新创建目录的权限模式，此示例将 `my_directory` 目录的权限设置为 `755`。

4. **同时创建多个目录：**
   ```bash
   mkdir dir1 dir2 dir3
   ```
   同时创建多个目录，即 `dir1`、`dir2` 和 `dir3`。

5. **显示详细信息：**
   ```bash
   mkdir -v dir1 dir2 dir3
   ```
   使用 `-v` 选项显示创建过程中的详细信息。

### 注意事项：

- 默认情况下，新创建的目录权限是 `777`，但这可能会受到系统 umask 的影响。
- 如果没有指定 `-m` 选项，`mkdir` 将使用系统默认的 umask 值来确定新目录的权限。
- 使用 `-p` 选项时，要小心，以免意外地在错误的位置创建目录。

`mkdir` 是一个基本而常用的命令，用于在 Linux 系统中创建目录。通过结合不同的选项，可以根据具体需求方便地创建目录并设置相应的权限。

## mkdir 

在Linux系统中，`mkdir`（make directory）命令用于创建目录。下面是`mkdir`命令的详细解释：

命令语法：
```
mkdir [选项] 目录名
```

常用选项：
- `-p`：递归创建目录，如果父目录不存在则创建。例如，`mkdir -p dir1/dir2/dir3` 将会创建`dir1`、`dir2`和`dir3`三级目录。
- `-m`：指定目录的权限模式（权限标志）。例如，`mkdir -m 755 new_dir` 将会创建一个权限为 `755` 的 `new_dir` 目录。
- `-v`：显示创建的每个目录的详细信息。
- `-p` 和 `-v` 选项可以同时使用。

示例：
1. 创建一个名为 `my_directory` 的目录：
```
mkdir my_directory
```

2. 递归地创建多级目录 `dir1/dir2/dir3`：
```
mkdir -p dir1/dir2/dir3
```

3. 创建目录并指定权限模式为 `755`：
```
mkdir -m 755 my_directory
```

4. 创建目录并显示详细信息：
```
mkdir -v my_directory
```

以上是一些常见的用法示例。`mkdir`命令还支持其他选项和参数，你可以通过运行 `man mkdir` 命令来查看更多详细的帮助文档。