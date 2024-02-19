## 简介

+ split命令

## split

+ 功能：将单个tar文件切割成多个tar文件
+ 命令：`split -b 4000M -a 1 -d nvidia.tar nvidia.tar`
+ 参数：
  + `-b`  --  指定生成的分割包大小
  + `-a`  --  设定序列的长度，默认为2，这里设置为1，生成的文件就为nvidia.tar1，
  + `-d`  --  指定生成的分割包后缀为数字的形式

在Linux中，`split`命令用于将一个大文件拆分成多个较小的文件。它可以按照文件大小、行数或指定的分割标准将文件分割成多个部分，方便处理和传输大型文件。

以下是`split`命令的一般语法：

```
split [options] input_file [output_file_prefix]
```

其中，`options`是可选的一些选项，`input_file`是要拆分的输入文件，`output_file_prefix`是输出文件的前缀。输出文件的名称将以前缀开头，后跟一个字母或数字来表示各个部分。

以下是一些常见的`split`命令选项和用法：

1. 按照文件大小拆分：
   ```
   split -b size input_file output_file_prefix
   ```

   此命令将根据指定的文件大小（`size`）将输入文件拆分成多个部分。`size`可以使用以下后缀表示：K（千字节）、M（兆字节）、G（千兆字节）等。

2. 按照行数拆分：
   ```
   split -l lines input_file output_file_prefix
   ```

   此命令将根据指定的行数（`lines`）将输入文件拆分成多个部分。

3. 自定义输出文件名格式：
   ```
   split --additional-suffix=suffix input_file output_file_prefix
   ```

   此命令将在输出文件的名称中添加指定的后缀（`suffix`），以自定义输出文件名的格式。

4. 拆分二进制文件：
   ```
   split -b size --binary input_file output_file_prefix
   ```

   如果要拆分二进制文件，可以使用`--binary`选项。

`split`命令还支持其他一些选项，如指定拆分文件的数量、保留原始文件等。您可以使用`man split`命令查看完整的选项和用法说明。

`split`命令对于处理大型文件或需要分割成较小部分的文件非常有用。它可以帮助您在处理和传输文件时更加高效地操作数据。

## 将`split`分割的压缩包合并

+ `cat nvidia.tar* > nvidia.tar | cat nvidia.tar01 nvidia.tar02 > nvidia.tar`

## `.7z` 文件

+ 使用`p7zip`软件解压
+ 参数：
  + `-d , --decompress --uncompress` : decompress file
  + `-c --stdout --to-stdout` : output data to stdout
  + `` 

## linux split命令 详解

`split` 命令用于将一个大文件拆分成多个小文件，可以指定拆分的大小或拆分的行数。这个命令在处理大型日志文件或备份文件时非常有用。

**基本语法：**
```bash
split [选项] 输入文件 [输出文件前缀]
```

**常见选项：**
- `-b, --bytes=SIZE`：按字节大小拆分。
- `-l, --lines=NUMBER`：按行数拆分。
- `-a, --suffix-length=N`：设置输出文件后缀的长度。
- `--numeric-suffixes`：使用数字后缀替代字母后缀。
- `--additional-suffix=SUFFIX`：添加额外的后缀到输出文件。

**示例：**
1. **按字节大小拆分：**
   ```bash
   split -b 1M largefile.txt smallfile
   ```
   这将把 `largefile.txt` 拆分成以 `smallfile` 为前缀的多个小文件，每个文件大小为 1MB。

2. **按行数拆分：**
   ```bash
   split -l 1000 largefile.txt smallfile
   ```
   这将把 `largefile.txt` 拆分成以 `smallfile` 为前缀的多个小文件，每个文件包含 1000 行。

3. **设置输出文件后缀长度：**
   ```bash
   split -b 1M -a 3 largefile.txt smallfile
   ```
   在这个例子中，输出文件的后缀长度为 3。

4. **使用数字后缀：**
   ```bash
   split -l 500 --numeric-suffixes largefile.txt smallfile
   ```
   这将使用数字后缀而不是默认的字母后缀。

5. **添加额外的后缀：**
   ```bash
   split -l 500 --numeric-suffixes --additional-suffix=.txt largefile.txt smallfile
   ```
   这将使用数字后缀，并且每个输出文件都会以 `.txt` 结尾。

**注意：** 如果没有指定输出文件前缀，`split` 默认使用 `x` 作为前缀。

`split` 命令非常适用于需要将大文件拆分成小块以便于处理或传输的情况。

## linux split命令 常用技巧

以下是在使用 `split` 命令时的一些常用技巧：

1. **按大小拆分文件：**
   ```bash
   split -b 1G largefile.txt smallfile
   ```
   这将把 `largefile.txt` 拆分成以 `smallfile` 为前缀的多个小文件，每个文件大小为 1GB。

2. **按行数拆分文件并指定文件前缀：**
   ```bash
   split -l 1000 -d -a 3 -t " " largefile.txt data_
   ```
   这将把 `largefile.txt` 按照每行 1000 行进行拆分，使用三位数字后缀，并以 `data_` 为前缀。

3. **自定义文件名后缀：**
   ```bash
   split -l 500 --numeric-suffixes --additional-suffix=.part largefile.txt smallfile
   ```
   这将使用数字后缀，并且每个输出文件都会以 `.part` 结尾。

4. **跳过前几行：**
   ```bash
   tail -n +100 largefile.txt | split -l 500 --numeric-suffixes - smallfile
   ```
   这将跳过文件的前 100 行，然后将其余的内容按行拆分。

5. **使用 `cat` 连接文件：**
   ```bash
   cat smallfile* > combinedfile.txt
   ```
   这将使用 `cat` 命令将以 `smallfile` 为前缀的所有小文件连接成一个大文件。

6. **使用 `find` 来拆分多个文件：**
   ```bash
   find . -name "*.log" -exec split -l 1000 --numeric-suffixes {} {}.part \;
   ```
   这将在当前目录及其子目录中找到所有以 `.log` 结尾的文件，并将每个文件按行数拆分成小文件。

这些技巧可以根据具体需求帮助你更灵活地使用 `split` 命令来处理大文件。