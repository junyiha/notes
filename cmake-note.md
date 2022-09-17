## 简介

+ CMake可以编译源代码,制作程序库,产生适配器(wrapper),可以用任意的顺序构建执行档
+ CMake支持in-place建构(二进档和源代码在同一个目录树中)和out-of-place构建(二进档在别的目录里),因此可以很容易从一个源代码目录树中建构出多个二进档.
+ CMake也支持静态与动态程式库的建构
+ CMake是一种工具,它读入用于描述软件如何构建的脚本,CMake将评估这些脚本并构建出表达软件项目的内部结构,如果它处理完这些脚本并没有发现错误,CMake将生成用于实际构建项目的构建文件(可能是脚本或者IDE工程文件)
+ CMake支持多种构建工具,包括一系列命令行构建工具和主流IDE,运行cmake --help可以看到在当前平台下CMake所支持的构建工具.
+ CMake中将这些构建系统称作generator.**因此,CMake不是构建系统,而是构建系统生成器,具体的构建工作还是要交给Make, Ninja等构建系统去做**
+ 运行CMake时,它会运行多项检查,在检查和评估构建脚本期间,它会将一些值缓存到CMakeCache.txt当中,这让我们在增量式开发中,可以跳过长时间的检查过程,但是CMake的缓存也会带来一些问题,比如:修改了某些配置没有办法及时的反映在下次构建中,所以有时构建出问题可以尝试删除CMake缓存文件后重新构建

什么是CMakeList.txt文件?
+ 放置所有CMake命令的文件,当cmake在某个文件夹下运行时,会寻找该文件,如果找不到则报错

为什么要使用cmake?
+ 跨平台
+ 可配置
+ 众多开源项目都只支持(或仅支持)CMake构建

## 构建CMake项目

CMake构建的两种形式:就地构建(in-source)和源码外构建(out-of-source)
+ 就地构建:在源文件目录下构建,产生的二进制文件将于源文件生成在一个文件夹里
+ 源码外构建:单独创建一个build文件夹,在该文件夹下构建二进制文件,与源代码文件分开

源码树和构建树
+ 源码树是源代码目录,里面放着源代码文件和CMakeLists.txt文件
+ 构建树就是存放构建系统文件和输出文件的目录
+ 通过变量`CMAKE_BINARY_DIR`访问到构建树的顶层文件夹(执行cmake命令的目录)
+ 通过变量`CMAKE_SOURCE_DIR`访问到源码树的顶层文件夹(根CMakeLists.txt文件所在的目录).
+ 注:对于就地构建,源码树和构建树是等价的

CMake的执行过程分为三个阶段:
英文:
1. **Configure**:  
   + Parse top level CMakeLists.txt, 
   + Generates cache variables, 
   + Only relevant in GUI builds
2. **Generate**:
   + Generate native build tool files, 
   + Can do cross compilation passing toolchain files
3. **Build**:
   + Uses native build tools to compile the sources, 
   + All it takes is cmake --build
中文:
1. 配置阶段:
   + CMake将解析源码树顶层的`CMakeLists.txt`,并生成一个`CMakeCache.txt`以存储cache变量
   + 对于CMake-GUI,该阶段由点击Configure出发,
   + 对于命令版本的CMake,该阶段与生成阶段结合在一起
   + CMake打印消息:`Configuring done`以表示配置阶段结束
2. 生成阶段:
   + CMake将根据`CMakeLists.txt`和`CMakeCache.txt`生成构建系统文件
   + 在CMake-GUI中,该阶段由点击Generate出发
   + CMake打印消息`Generating done`以表示生成阶段结束
3. 构建阶段:
   + 这一阶段由构建系统负责,在这个阶段中将生成项目的目标