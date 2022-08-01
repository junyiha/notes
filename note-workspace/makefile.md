书写规则：
    依赖关系：生成目标的方法

规则语法：
    targets:prerequisites
        command
    targets：文件名，以空格分开，可以使用通配符
    command：命令行，如果不与prerequisites在一行，必须在下一行以Tab键开头，如果在一行，用分号做分割
    prerequisites：目标所依赖的文件

反斜杠（\）：换行符

变量：
    变量在声明时，需要给予初值，而在使用时，需要给变量名前加上$符号，并且用小括号括起来