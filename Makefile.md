## 书写规则：

+ 依赖关系：生成目标的方法

## 规则语法：
```
  targets:prerequisites
      command
  targets：文件名，以空格分开，可以使用通配符
  command：命令行，如果不与prerequisites在一行，必须在下一行以Tab键开头，如果在一行，用分号做分割
  prerequisites：目标所依赖的文件
  反斜杠（\）：换行符
```

## 参数

+ `make -C dir`, `--directory=dir` : Change to directory `dir` before reading the makefiles or doing anything else.

## 变量：
+ 变量在声明时，需要给予初值，而在使用时，需要给变量名前加上$符号，并且用小括号括起来
+ makefile中变量分为环境变量，内置变量和自动变量
+ **环境变量**
  - `DESKTOP_SESSION` : ubuntu
  - `XDG_SESSION_TYPE`: x11
  - `XAUTHORITY`      : /run/user/1000/gdm/Xauthority
  - `_`               : /usr/bin/make

+ **自动变量**
  - `$@` : 表示规则的目标文件名
  - `$<` : 规则的第一个依赖文件名。如果是一个目标文件使用隐含规则来重建，则代表由隐含规则加入的第一个依赖文件
  - `$^` : 规则的所有依赖文件列表，使用空格分隔。如果目标是静态库文件，它所代表的只能是所有库成员(.0文件)名。一个文件可重复的出现在目标的依赖中，变量`$^`只记录它的一次引用情况。就是说变量`$^`会去掉重复的依赖文件。
  - `$+` : 类似于`$^`，但是它保留了依赖文件中重复出现的文件。主要用在程序链接时库的交叉引用场合
  
+ **内置变量**
  - `$(CURDIR)` : 显示当前路径
  - `$(SHELL)`  : /bin/sh
  - `$(CC)`     : cc , C语言编译器的名称
  - `$(CPP)`    : $(CC) -E ， C语言预处理器的名称
  - `$(CXX)`    : g++ , C++语言的编译器的名称
  - `$(RM)`     : rm -f , 删除文件程序的名称
  - `$(CFLAGS)` : C语言编译器的编译选项，无默认值
  - `$(CXXFLAGS)`: C++语言编译器的编译选项，无默认值

## 函数

+ `$(abspath names...)` : 获取文件的绝对地址 
+ `ifeq (condition1, condition2) ... endif` :  如果`condition1` 等于 `conditon2` , 则执行下面的操作，否则不执行
+ ` += `
    ```
    variable = main.o merge.o
    variable += delete.o
    # ALL:$(variable)
    all:
    	@echo ${variable} 
    # 输出: main.o merge.o delete.o
    ```
+ `${addprefix "前缀", filenames...}` : 为文件加前缀
    ```
    variable = main.o merge.o
    variable += delete.o
    var = ${addprefix -x/, ${variable}}
    all:
    	@echo ${var} 
    # 输出: -x/main.o -x/merge.o -x/delete.o
    ```
+ `${wildcard /home/user/workspace/shell/*.sh}` : 获取指定路径下的指定文件
    ```
      var = ${wildcard ./*.txt}
      all:
      	@echo ${var} 
      # 输出: ./foo.txt ./bar.txt

    ```
+ `${patsubst pattern, replacement, text}` : 根据相应规则替换文件名
  ```
    var = ${wildcard ./*.txt}
    pat = ${patsubst %.txt, %.md, ${var}}
    all:
    	@echo ${var} 
    	@echo ${pat}
    # 输出: ./foo.txt ./bar.txt   \  ./foo.md ./bar.md
  ```

## 技巧

### Makefile中获取当前执行的Makefile所在路径

+ Linux下我们可以用pwd命令来获取当前所执行命令的目录，在Makefile中对应可用`PWD := $(shell pwd)`来获取。
  
+ 但是如果子Makefile 文件是从别处执行的(通过`make -f .../Makefile` 执行)，那么`$(shell pwd)`得到的目录即为执行`make -f`命令的当前目录
+ 在这种情况下
  + 根据gnu make定义，`gnu make` 会自动将所有读取的`makefile`路径都会加入到`MAKEFILE_LIST`变量中，而且是按照读取的先后顺序添加
  + 所以可以通过`$(abspath $(lastword $(MAKEFILE_LIST)))`返回当前正在被执行的`Makefile`的绝对路径,然后通过`patsubst`去掉文件名得到绝对目录
  
+ 代码：
  ```
    makefile_path:=$(abspath $(lastword $(MAKEFILE_LIST)))
    cur_makefile_path:=$(patsubst %/makefile, %/, ${shell ls $(makefile_path)})

    all:
    	@echo ${makefile_path}
    	@echo ${cur_makefile_path}
  ``` 