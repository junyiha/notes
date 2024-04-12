## 简介

+ shell编程常用技巧

## linux 写一个定时刷新的24h运行脚本

你可以使用`crontab`来创建一个定时刷新的脚本。`crontab`是一个用于在Linux系统上定期执行任务的工具。下面是一个示例，假设你有一个名为`refresh.sh`的脚本，你想每天定时运行：

首先，创建一个`refresh.sh`脚本：

```bash
#!/bin/bash

# 这是你的刷新任务脚本内容
# 例如，你可以在这里写下你想要执行的任务
# 比如，刷新某个文件夹下的内容

echo "Running refresh script at $(date)"
# 在这里执行你的刷新任务
```

保存并退出。

接下来，编辑你的`crontab`：

```bash
crontab -e
```

在编辑器中添加以下行，表示每天的0点执行`refresh.sh`脚本：

```
0 0 * * * /path/to/refresh.sh
```

确保将`/path/to/refresh.sh`替换为你实际的`refresh.sh`脚本的路径。

保存并退出编辑器。

这将使你的`refresh.sh`脚本每天的午夜被执行，从而实现了24小时定时刷新的需求。

## linux stat 获取指定目录的空闲空间

你可以使用 `stat` 命令获取文件系统的信息，但是 `stat` 命令不能直接获取指定目录的空闲空间。要获取指定目录的空闲空间，你可以使用 `df` 命令。

以下是一个示例 Bash 脚本，用于获取指定目录的空闲空间：

```bash
#!/bin/bash

# 指定要获取空间信息的目录
directory="/path/to/your/directory"

# 获取目录所在的文件系统
filesystem=$(df -P "$directory" | awk 'NR==2 {print $1}')

# 获取文件系统的空闲空间
free_space=$(df -P "$filesystem" | awk 'NR==2 {print $4}')

echo "Free space in $directory : $free_space"
```

在这个脚本中，你需要将 `/path/to/your/directory` 替换为你要查询空间信息的目录路径。脚本将首先使用 `df` 命令获取该目录所在的文件系统，然后再次使用 `df` 命令获取该文件系统的空闲空间。最后，脚本会输出空闲空间的信息。

请注意，这个脚本只是一个简单的示例，适用于大多数情况。在实际使用中，你可能需要更复杂的逻辑来确保脚本的稳健性和安全性。

## linux bash 字符串删除

如果你要删除字符串中的特定字符或子字符串，你可以使用 Bash 的内置功能 `sed`、`awk` 或字符串操作函数来实现。下面是一些方法示例：

### 使用 `sed` 删除字符串中的字符：

```bash
#!/bin/bash

# 原始字符串
original_string="Hello World"

# 删除字符串中的空格
modified_string=$(echo "$original_string" | sed 's/ //g')

echo "Original string: $original_string"
echo "Modified string: $modified_string"
```

### 使用 `awk` 删除字符串中的字符：

```bash
#!/bin/bash

# 原始字符串
original_string="Hello World"

# 删除字符串中的空格
modified_string=$(echo "$original_string" | awk '{gsub(" ", "")}1')

echo "Original string: $original_string"
echo "Modified string: $modified_string"
```

### 使用字符串操作函数删除字符串中的子字符串：

```bash
#!/bin/bash

# 原始字符串
original_string="Hello World"

# 删除字符串中的 "llo" 子字符串
substring_to_remove="llo"
modified_string="${original_string//$substring_to_remove}"

echo "Original string: $original_string"
echo "Modified string: $modified_string"
```

这些示例中，原始字符串是 "Hello World"，然后使用不同的方法删除了其中的空格或子字符串。你可以根据自己的需求选择其中一种方法。

## linux bash 获取docker容器的id

要获取正在运行的 Docker 容器的 ID，你可以使用 Docker 命令行工具。以下是使用 `docker ps` 命令来获取正在运行容器的 ID 的示例：

```bash
#!/bin/bash

# 获取正在运行的容器的 ID
container_id=$(docker ps -q)

echo "Running Docker container ID: $container_id"
```

在这个脚本中，`docker ps -q` 命令用于列出正在运行的容器，并使用 `-q` 参数只显示容器的 ID。然后将结果存储在 `container_id` 变量中，并输出该变量的值。 

这只会获取第一个正在运行的容器的 ID。如果你想获取特定容器的 ID，你可以使用 `docker ps -qf` 命令并提供过滤条件，如容器的名称、标签等。例如，要获取名称为 `my_container` 的容器的 ID，你可以使用以下命令：

```bash
container_id=$(docker ps -qf "name=my_container")
```

你可以根据自己的需要调整这些命令。

## linux find命令找到指定文件并保存到数组中

在Linux中，`find`命令用于查找文件和目录。如果你想使用`find`命令找到指定文件并将结果保存到一个数组中，你可以使用以下方法：

```bash
# 1. 使用 find 命令查找指定文件，并将结果保存到数组
files_array=($(find /path/to/search -name "your_pattern"))

# 2. 输出数组内容（可选）
echo "Files found:"
for file in "${files_array[@]}"; do
    echo "$file"
done

cmd="libtool -static -o libabsl.a "

for file in "${files_array[@]}"; do 
    cmd="${cmd} ${file}"
done

echo "cmd:"
echo ${cmd}
```

在这个例子中：
- `/path/to/search` 是你要搜索的目录的路径。
- `"your_pattern"` 是你要匹配的文件名模式。你可以使用通配符来匹配文件名的一部分，比如 `*.txt` 表示所有以 `.txt` 结尾的文件。
- `files_array` 是保存文件列表的数组。

请注意，上述代码假设文件和目录名不包含空格。如果你的文件名中可能包含空格，建议使用更复杂的方法来处理，比如使用 `find` 命令的 `-print0` 选项以及 `readarray` 命令：

```bash
# 使用 find 命令查找指定文件，将结果以空字符分隔保存到数组
readarray -d '' files_array < <(find /path/to/search -name "your_pattern" -print0)

# 输出数组内容
echo "Files found:"
for file in "${files_array[@]}"; do
    echo "$file"
done
```

这种方法通过 `-print0` 选项和 `readarray -d ''` 的配合，确保了对文件名中可能包含的空格进行正确处理。