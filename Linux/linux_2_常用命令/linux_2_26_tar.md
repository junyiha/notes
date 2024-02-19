## 简介

+ tar命令

## tar

+ 解压文件:`tar -zxf filename -C destination-path`
+ 压缩文件:`tar -zcf filename`

## linux tar命令 详解

`tar`是Linux系统中一个用于归档和压缩文件的命令行工具。它的名称来源于"tape archive"，最初设计是为了在磁带上创建备份。下面是`tar`命令的一些常见用法和参数：

### 基本语法：

```bash
tar [选项] [文件或目录]
```

### 常见选项：

1. **创建归档文件：**
   ```bash
   tar -cvf archive.tar file1 file2 directory
   ```
   - `-c`: 创建归档文件。
   - `-v`: 显示详细信息。
   - `-f`: 指定归档文件的名称。

2. **解压缩归档文件：**
   ```bash
   tar -xvf archive.tar
   ```
   - `-x`: 解压缩归档文件。

3. **查看归档文件内容：**
   ```bash
   tar -tvf archive.tar
   ```
   - `-t`: 列出归档文件中的内容。

4. **添加文件到已有归档文件：**
   ```bash
   tar -rvf archive.tar newfile
   ```
   - `-r`: 向已有归档文件中添加文件。

5. **从归档中删除文件：**
   ```bash
   tar --delete -f archive.tar file1
   ```
   - `--delete`: 从归档文件中删除文件。

6. **指定工作目录：**
   ```bash
   tar -C /path/to/directory -xvf archive.tar
   ```
   - `-C`: 指定解压缩时的工作目录。

7. **压缩归档文件（使用gzip）：**
   ```bash
   tar -czvf archive.tar.gz directory
   ```
   - `-z`: 使用gzip进行压缩。

8. **压缩归档文件（使用bzip2）：**
   ```bash
   tar -cjvf archive.tar.bz2 directory
   ```
   - `-j`: 使用bzip2进行压缩。

### 示例：

- 创建归档文件并压缩：
  ```bash
  tar -czvf archive.tar.gz directory
  ```

- 解压缩压缩过的归档文件：
  ```bash
  tar -xzvf archive.tar.gz
  ```

- 查看归档文件内容：
  ```bash
  tar -tvf archive.tar
  ```

请注意，`tar`命令的选项可能有所不同，具体取决于系统和`tar`版本。你可以使用`man tar`命令查看`tar`的手册页以获
取更详细的信息。

## linux tar命令 常用技巧

在使用`tar`命令时，有一些常用的技巧和实用的选项，可以帮助你更有效地处理文件和目录。以下是一些常用的`tar`命令技巧：

1. **压缩和解压缩：**
   - 压缩文件：
     ```bash
     tar -czvf archive.tar.gz file1 file2 directory
     ```
   - 解压缩文件：
     ```bash
     tar -xzvf archive.tar.gz
     ```

2. **使用不同的压缩算法：**
   - 使用bzip2进行压缩：
     ```bash
     tar -cjvf archive.tar.bz2 directory
     ```
   - 使用xz进行压缩：
     ```bash
     tar -cJvf archive.tar.xz directory
     ```

3. **仅显示归档文件的内容而不解压缩：**
   ```bash
   tar -tvf archive.tar
   ```

4. **向归档文件添加新文件：**
   ```bash
   tar -rvf archive.tar newfile
   ```

5. **从归档文件中删除文件：**
   ```bash
   tar --delete -f archive.tar file1
   ```

6. **创建归档时排除特定文件或目录：**
   ```bash
   tar --exclude=pattern -cvf archive.tar directory
   ```

7. **压缩归档文件时显示进度信息：**
   ```bash
   tar -czvf - directory | pv > archive.tar.gz
   ```
   - `pv`是一个用于显示数据流进度的命令。

8. **在指定目录解压缩文件：**
   ```bash
   tar -C /path/to/destination -xvzf archive.tar.gz
   ```

9. **将归档文件从远程服务器传输到本地：**
   ```bash
   ssh user@remote 'tar -czvf - directory' | tar -xzvf -
   ```

10. **仅解压缩归档文件的部分内容：**
    ```bash
    tar -xzvf archive.tar.gz --wildcards '*.txt'
    ```
    - 仅解压缩归档文件中扩展名为`.txt`的文件。

这些技巧可以帮助你更灵活地使用`tar`命令，提高在文件和目录处理方面的效率。记得查看`man tar`以获取更多详细信息。

## tar 

+ tar(tape archive),命令用于备份文件
+ tar是用来建立,还原备份文件的工具程序,它可以加入,解开备份文件内的文件

+ tar命令 可以为linux的文件和目录创建档案。利用tar，可以为某一特定文件创建档案（备份文件），也可以在档案中改变文件，或者向档案中加入新的文件。tar最初被用来在磁带上创建档案，现在，用户可以在任何设备上创建档案。利用tar命令，可以把一大堆的文件和目录全部打包成一个文件，这对于备份文件或将几个文件组合成为一个文件以便于网络传输是非常有用的。

+ 首先要弄清两个概念：打包和压缩。打包是指将一大堆文件或目录变成一个总的文件；压缩则是将一个大的文件通过一些压缩算法变成一个小文件。
+ 为什么要区分这两个概念呢？
  + 这源于Linux中很多压缩程序只能针对一个文件进行压缩，这样当你想要压缩一大堆文件时，你得先将这一大堆文件先打成一个包（tar命令），然后再用压缩程序进行压缩（gzip bzip2命令）。

+ 语法：
  ```
    tar [-ABcdgGhiklmMoOpPrRsStuUvwWxzZ][-b <区块数目>][-C <目的目录>]
        [-f <备份文件>][-F <Script文件>][-K <文件>][-L <媒体容量>][-N <日期时间>]
        [-T <范本文件>][-V <卷册名称>][-X <范本文件>][-<设备编号><存储密度>]
        [--after-date=<日期时间>][--atime-preserve][--backuup=<备份方式>]
        [--checkpoint][--concatenate][--confirmation][--delete]
        [--exclude=<范本样式>][--force-local][--group=<群组名称>][--help]
        [--ignore-failed-read][--new-volume-script=<Script文件>][--newer-mtime]
        [--no-recursion][--null][--numeric-owner][--owner=<用户名称>][--posix]
        [--erve][--preserve-order][--preserve-permissions]
        [--record-size=<区块数目>][--recursive-unlink][--remove-files]
        [--rsh-command=<执行指令>][--same-owner][--suffix=<备份字尾字符串>]
        [--totals][--use-compress-program=<执行指令>][--version]
        [--volno-file=<编号文件>][文件或目录...]
  ``` 

+ 选项：
  + -A或--catenate：新增文件到以存在的备份文件；
  + -b<区块数目>或–blocking-factor=<区块数目>；
  + -B：设置区块大小；
  + -c或--create：建立新的备份文件；
  + -C <目录>：切换工作目录，先进入指定目录再执行压缩/解压缩操作，可用于仅压缩特定目录里的内容或解压缩到特定目录
  + -d或–diff或–compare 对比备份文件内和文件系统上的文件的差异。
  + -f<备份文件>或–file=<备份文件> 指定备份文件。
  + -F<Script文件>或–info-script=<Script文件> 每次更换磁带时，就执行指定的Script文件
  + -g或–listed-incremental 处理GNU格式的大量备份。
  + -G或–incremental 处理旧的GNU格式的大量备份。
  + -h或–dereference 不建立符号连接，直接复制该连接所指向的原始文件。
  + -i或–ignore-zeros 忽略备份文件中的0 Byte区块，也就是EOF。
  + -k或–keep-old-files 解开备份文件时，不覆盖已有的文件。
  + -K<文件>或–starting-file=<文件> 从指定的文件开始还原。
  + -l或–one-file-system 复制的文件或目录存放的文件系统，必须与tar指令执行时所处的文件系统相同，否则不予复制
  + -L<媒体容量>或-tape-length=<媒体容量> 设置存放每体的容量，单位以1024 Bytes计算。
  + -m或–modification-time 还原文件时，不变更文件的更改时间。
  + -M或–multi-volume 在建立，还原备份文件或列出其中的内容时，采用多卷册模式。
  + -N<日期格式>或–newer=<日期时间> 只将较指定日期更新的文件保存到备份文件里。
  + -o或–old-archive或–portability 将资料写入备份文件时使用V7格式。
  + -O或–stdout 把从备份文件里还原的文件输出到标准输出设备。
  + -p或–same-permissions 用原来的文件权限还原文件。
  + -P或–absolute-names 文件名使用绝对名称，不移除文件名称前的”/”号。
  + -r或–append 新增文件到已存在的备份文件的结尾部分。
  + -R或–block-number 列出每个信息在备份文件中的区块编号。
  + -s或–same-order 还原文件的顺序和备份文件内的存放顺序相同。
  + -S或–sparse 倘若一个文件内含大量的连续0字节，则将此文件存成稀疏文件。
  + -t或–list 列出备份文件的内容。
  + -T<范本文件>或–files-from=<范本文件> 指定范本文件，其内含有一个或多个范本样式，让tar解开或建立符合设置条件的文件。
  + -u或–update 仅置换较备份文件内的文件更新的文件。
  + -U或–unlink-first 解开压缩文件还原文件之前，先解除文件的连接。
  + -v或–verbose 显示指令执行过程。
  + -V<卷册名称>或–label=<卷册名称> 建立使用指定的卷册名称的备份文件。
  + -w或–interactive 遭遇问题时先询问用户。
  + -W或–verify 写入备份文件后，确认文件正确无误。
  + -x或--extract或--get：从备份文件中还原文件；
  + -t或--list：列出备份文件的内容；
  + -z或--gzip或--ungzip：通过gzip指令处理备份文件；
  + -Z或--compress或--uncompress：通过compress指令处理备份文件；
  + -<设备编号><存储密度>  设置备份用的外围设备编号及存放数据的密度。
  + --after-date=<日期时间> 此参数的效果和指定”-N”参数相同。
  + --atime-preserve 不变更文件的存取时间。
  + --backup=<备份方式>或–backup 移除文件前先进行备份。
  + --checkpoint 读取备份文件时列出目录名称。
  + --concatenate 此参数的效果和指定”-A”参数相同。
  + --confirmation 此参数的效果和指定”-w”参数相同。
  + --delete 从备份文件中删除指定的文件。
  + --exclude=<范本样式> 排除符合范本样式的问家。
  + --group=<群组名称>  把加入设备文件中的文件的所属群组设成指定的群组。
  + --help 在线帮助。
  + --ignore-failed-read 忽略数据读取错误，不中断程序的执行。
  + --new-volume-script=<Script文件>  此参数的效果和指定”-F”参数相同。
  + --newer-mtime 只保存更改过的文件。
  + --no-recursion  不做递归处理，也就是指定目录下的所有文件及子目录不予处理。
  + --null 从null设备读取文件名称。
  + --numeric-owner 以用户识别码及群组识别码取代用户名称和群组名称。
  + --owner=<用户名称> 把加入备份文件中的文件的拥有者设成指定的用户。
  + --posix 将数据写入备份文件时使用POSIX格式。
  + --preserve 此参数的效果和指定”-ps”参数相同。
  + --preserve-order 此参数的效果和指定”-A”参数相同。
  + --preserve-permissions 此参数的效果和指定”-p”参数相同。
  + --record-size=<区块数目> 此参数的效果和指定”-b”参数相同。
  + --recursive-unlink 解开压缩文件还原目录之前，先解除整个目录下所有文件的连接。
  + --remove-files 文件加入备份文件后，就将其删除。
  + --rsh-command=<执行指令> 设置要在远端主机上执行的指令，以取代rsh指令。
  + --same-owner 尝试以相同的文件拥有者还原问家你。
  + --suffix=<备份字尾字符串> 移除文件前先行备份。
  + --totals 备份文件建立后，列出文件大小。
  + --use-compress-program=<执行指令> 通过指定的指令处理备份文件。
  + --version 显示版本信息。
  + --volno-file=<编号文件> 使用指定文件内的编号取代预设的卷册编号。

+ 参数：文件或目录：指定要打包的文件或目录列表。
+ 实例：
  + `-z`：有gzip属性的
  + `-j`：有bz2属性的
  + `-Z`：有compress属性的
  + `-v`：显示所有过程
  + `-O`：将文件解开到标准输出


+ 下面的参数-f是必须的
  + -f: 使用档案名字，切记，这个参数是最后一个参数，后面只能接档案名。
  ```
    tar -cf all.tar *.jpg
    # 这条命令是将所有.jpg的文件打成一个名为all.tar的包。-c是表示产生新的包，-f指定包的文件名。

    tar -rf all.tar *.gif
    # 这条命令是将所有.gif的文件增加到all.tar的包里面去。-r是表示增加文件的意思。

    tar -uf all.tar logo.gif
    # 这条命令是更新原来tar包all.tar中logo.gif文件，-u是表示更新文件的意思。

    tar -tf all.tar
    # 这条命令是列出all.tar包中所有文件，-t是列出文件的意思

    tar -cfv archive.tar foo bar  # 从文件foo和bar创建archive.tar。
    tar -tvf archive.tar         # 详细列出archive.tar中的所有文件。
    tar -xf archive.tar          # 从archive.tar提取所有文件。
  ``` 

+ zip格式
  + 压缩： zip -r [目标文件名].zip [原文件/目录名]
  + 解压： unzip [原文件名].zip
  + 注：-r参数代表递归

+ tar格式（该格式仅仅打包，不压缩）
  + 打包：tar -cvf [目标文件名].tar [原文件名/目录名]
  + 解包：tar -xvf [原文件名].tar
  + 注：c参数代表create（创建），x参数代表extract（解包），v参数代表verbose（详细信息），f参数代表filename（文件名），所以f后必须接文件名。

+ tar.gz格式
  + 方式一：利用前面已经打包好的tar文件，直接用压缩命令。
    + 压缩：gzip [原文件名].tar
    + 解压：gunzip [原文件名].tar.gz
  + 方式二：一次性打包并压缩、解压并解包
    + 打包并压缩： tar -zcvf [目标文件名].tar.gz [原文件名/目录名]
    + 解压并解包： tar -zxvf [原文件名].tar.gz
    + 注：z代表用gzip算法来压缩/解压。

+ tar.bz2格式
  + 方式一：利用已经打包好的tar文件，直接执行压缩命令：
    + 压缩：bzip2 [原文件名].tar
    + 解压：bunzip2 [原文件名].tar.bz2
  + 方式二：一次性打包并压缩、解压并解包
    + 打包并压缩： tar -jcvf [目标文件名].tar.bz2 [原文件名/目录名]
    + 解压并解包： tar -jxvf [原文件名].tar.bz2
    + 注：小写j代表用bzip2算法来压缩/解压。

+ tar.xz格式
  + 方式一：利用已经打包好的tar文件，直接用压缩命令：
    + 压缩：xz [原文件名].tar
    + 解压：unxz [原文件名].tar.xz
  + 方式二：一次性打包并压缩、解压并解包
    + 打包并压缩： tar -Jcvf [目标文件名].tar.xz [原文件名/目录名]
    + 解压并解包： tar -Jxvf [原文件名].tar.xz
    + 注：大写J代表用xz算法来压缩/解压。

+ jar格式
  + 压缩：jar -cvf [目标文件名].jar [原文件名/目录名]
  + 解压：jar -xvf [原文件名].jar

+ 7z格式
  + 压缩：7z a [目标文件名].7z [原文件名/目录名]
  + 解压：7z x [原文件名].7z
  + 注：这个7z解压命令支持rar格式