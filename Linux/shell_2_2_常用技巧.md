## 简介

+ shell编程常用技巧

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