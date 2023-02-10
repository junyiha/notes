# VSCode 基础

## 下载

+ 首先，在官网找到需要下载的文件，点击下载，并将下载连接复制下来，例如：
  + `https://az764295.vo.msecnd.net/stable/97dec172d3256f8ca4bfb2143f3f76b503ca0534/code_1.74.3-1673284829_amd64.deb`

+ 然后，将`az764295.vo.msecnd.net`替换为`vscode.cdn.azure.cn`，例如：
  + `https://vscode.cdn.azure.cn/stable/97dec172d3256f8ca4bfb2143f3f76b503ca0534/code_1.74.3-1673284829_amd64.deb`

+ 这就是国内的镜像

## 使用root用户打开vscode

+ 背景：
  + 在远程调试机械臂的时候，需要使用到root权限来运行程序，所以在调试的时候需要使用到root权限

+ 方法：
  + 在`.bashrc`中加入一行代码：
    + `alias code='/usr/share/code/code . --no-sandbox --unity-lanuch'`
  + 然后，直接在终端使用vscode命令打开vscode : `code`


# VSCode C++ 配置

## 三个文件:`task.json` `launch.json` `c_cpp_properties.json`

1. IntelliSense：Intelligence Sense，代码自动补全
2. Task.json:
    告诉VScode如何编译.cpp文件，配置后将调用g++编译器基于源代码创建可执行文件。
    参数：
        command：设置要运行的指定程序
        args：参数数组指明要传送给g++的命令行参数，这些参数必须按照编译器要求的顺序来说明
        ${file}：g++执行的活动文件
        ${fileDirname}：当前目录
        label：任务列表中显示的值
3. launch.json：使用F5启动GDB调试器来调试程序
4. c_cpp_properties.json：对c/c++扩展实现更多控制，可以改变编译器的路径，C++标准以及更多

## 变量替换

+ VScode在`launch.json`调试文件和`task.json`任务文件中是支持变量替换的，这就意味着可以很方便的使用VScode一些预定以的变量。
+ 变量的使用方式：`${variableName}`
+ 常用的变量：
  - `${workspaceFolder}` : 项目文件夹在`VScode`中打开的路径
  - `${file}` : 当前打开的文件
  - `${relativeFile}` : 相对于`${workspaceFolder}`的文件路径
  - `${fileBasename}` : 当前打开文件的名称
  - `${fileBasenameNoExtension}` : 当前打开文件的名称，不带扩展名
  - `${fileExtname}` : 当前打开文件的扩展名
  - `${fileDirname}` : 当前打开文件的文件夹名称

## 调试 断点

### 日志点，`Logpoints`

+ 日志点是断点的变体，它不会“中断”到调试器中，而是将消息记录到控制台。日志点对于再调试无法暂停或停止的生产服务器时注入日志记录特别有用。(A Logpoint is a variant of a breakpoint that does not "break" into the debugger but instead logs a message to the console. Logpoints are especially useful for injecting logging while debugging production servers that cannot be paused or stopped)
+ 日志消息是纯文本，但可以包含表达式，需要使用花括号

### 表达式条件断点

+ 条件断点是表达式结果为`true`时才会进行断点

### 命中计数断点

+ 只有该行代码命中了指定次数，才会进行断点

### 内联断点

+ 仅当执行到达与内联断点关联的列时，才会命中内联断点。
+ 这在调试一行中包含多个语句的缩小代码时特别有用。比如for循环，短路运算符等一行代码包含多个表达式时
+ 在指定位置按`shift + F9`

## 快捷键

+ `ctrl + p` ： 快速搜索文件并跳转，添加`:`可以跳转到指定行
+ `alt + 鼠标左键` : 选中多行同时编辑