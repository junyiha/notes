1. gcc和g++分别是GNU的c&c++编译器。gcc和g++在执行编译工作的时候，总共四步：
    1. 预处理，生成.i文件{预处理器cpp}
    2. 将预处理后的文件转换成汇编语言，生成文件.s{编译器egcs}
    3. 由汇编变为目标代码（机器代码）生成.o的文件{汇编器as}
    4. 链接目标代码，生成可执行程序{连接器ld}
2. 命令：
   - `-c`：只激活预处理、编译和汇编，生成obj文件.o
   - `-S`：只激活预处理和编译，生成汇编代码
   - `-I`：指定头文件所在路径
   - `-L`：指定库文件所在路径
   - `-l`：指定库的名字
3. 今日头条 
   1. GCC是一个驱动式的程序，它调用其他程序来依次进行编译、汇编和链接。
   2. GCC分析命令行参数，然后决定该调用哪一个子程序，哪些参数应该传递给子程序。所有这些行为都是由SPEC字符串（spec strings）来控制的。通常情况下，每一个GCC可以调用的子程序都对应着一个SPEC字符串，不过有少数的子程序需要多个SPEC字符串来控制他们的行为。

+ 试图最大化一段关键代码性能的程序员,通常会尝试源代码的各种形式,每次编译并检查产生的汇编代码,从而了解程序将要运行的效率如何,此外,有些时候,高级语言提供的抽象层会隐藏我们想要了解的程序的运行时行为(深入理解计算机操作系统 P109)

### 编译器的工作过程
1. 配置(configure)
   - 编译器在开始工作之前,需要知道当前的系统环境,比如标准库在哪里,软件的安装位置在哪里,需要安装那些组件等等.
   - 这是因为不同计算机的系统环境不一样,通过指定编译参数,编译器就可以灵活适应环境,编译出各种环境都能运行的机器码,**这个确定编译参数的步骤,就叫做"配置(configure)"**
   - 这些配置信息保存在一个配置文件中,约定俗成是一个叫做`configure`的脚本文件.通常它是由`autoconf`工具生成的.编译器通过运行这个脚本,获得编译参数
2. 确定标准库和头文件的位置
   - 源码肯定会用到标准库函数(standard library)和头文件(header).它们可以放在系统的任意目录中,编译器实际上没有办法自动检测它们的位置,只有通过配置文件才能知道
   - 编译的第二步,就是从配置文件中知道标准库和头文件的位置.一般来说,配置文件会给出一个清单,列出几个具体的目录.等到编译时,编译器就按顺序到这几个目录中,寻找目标
3. 确定依赖关系
   - 对于大型项目来说,源码之间往往存在依赖关系,编译器需要确定编译的先后顺序.假设A文件依赖于B文件,编译器应该保证做到:**只有在B文件编译完成后,才开始编译A文件;当B文件发生变化时,A文件会被重新编译**
   - 编译顺序保存在一个叫做`makefile`的文件中,里面列出哪个文件先编译,哪个文件后编译.而`makefile`文件由`configure`脚本运行生成,这就是**为什么编译时configure必须首先运行的原因**
4. 头文件的预编译(precompilation)
   - 不同的源码文件,可能引用同一个头文件,编译的时候,头文件也必须一起编译
   - 为了节省时间,编译器会在编译源码之前,先编译头文件.这保证了头文件只需编译一次,不必每次用到的时候都需要重新编译
   - 不过,并不是头文件的所有内容都会被预编译,用来声明宏的`#define`命令,就不会被预编译
5. 预处理(preprocessing)
   - 预编译完成后,编译器就开始替换掉源码中bash的头文件和宏,编译器在这一步还会移除注释
6. 编译(Compilation)
   - 预处理之后,编译器就开始生成机器码.
   - 对于某些编译器来说,还存在一个中间步骤,会先把源码转为汇编码(`assembly`),然后再把汇编码转为机器码
   - 这种转码后的文件称为对象文件(`object file`)
7. 连接(Linking)
   - 把外部函数的代码(通常是后缀名为`.lib`和`.a`的文件),添加到可执行文件中,这就叫做连接(linking).
   - 这种通过拷贝,将外部函数库添加到可执行文件的方式,叫做静态连接(static linking)
   - `make`命令的作用,就是**从第四步头文件预编译开始,一直到做完这一步.**
8. 安装(Installation)
   - 上一步的连接是在**内存**中进行的,即编译器在内存中生成了可执行文件.下一步,必须将可执行文件保存到用户事先指定的安装目录
   - 表面上,这一步就是将可执行文件(连带相关的数据文件)拷贝过去,但是实际上,这一步还必须完成创建目录,保存文件,设置权限等步骤,这整个的过程就称为"安装(Installation)"
9. 操作系统连接
   - 可执行文件安装后,必须以某种方式通知操作系统,让其知道可以使用这个程序了
   - 这就要求在操作系统中,登记这个程序的元数据:文件名,文件描述,关联后缀名等等.linux系统中,这些信息通常保存在`/usr/share/applications/`目录下的`.desktop`文件中.另外在windows操作系统中,还需要在start启动菜单中,建立一个快捷方式
   - 这些事情就叫做"操作系统连接".`make install`命令,就用来完成"安装"和"操作系统连接"这两步
10. 生成安装包
   - 到这一步,源码编译的整个过程就基本完成了,但是事实上,如果只有源码可以交给用户,是不可行的,大部分用户要的是一个二进制的可执行程序,立刻就能运行.这就要求开发者,将上一步生成的可执行文件,做成可以分发的安装包
   - 所以,编译器还必须有生成安装包的功能,通常是将可执行文件(连带相关的数据文件),以某种目录结构,保存成压缩文件包,交给用户
11. 动态连接(Dynamic linking)
   - 静态连接就是把外部函数库,拷贝到可执行文件中,这样做的好处是:适用范围较广,不用担心用户机器缺少某个库文件;缺点是:安装包会比较大,而且多个应用程序之间,无法共享文件.
   - 动态连接的做法正好相反,外部函数库不进入安装包,只在运行时动态引用.这样做的好处是:安装包比较小,多个应用程序可以共享文件;缺点是:用户必须事先安装好库文件,而且版本和安装位置都必须符合要求,否则就不能正常运行