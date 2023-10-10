## 第一章 预备知识

### C++简介

+ C++融合了三种不同的编程方式：
  - C语言代表的过程性语言
  - C++在C语言基础上添加的类代表的面向对象语言
  - C++模板支持的泛型编程

### C++简史

+ 汇编语言，依赖于计算机的内部机器语言。
+ 它是低级语言(low-level)，即直接操作硬件，例如直接访问CPU寄存器和内存单元。因此，汇编语言针对于特定的计算机处理器，要将汇编程序移植到另一种计算机上，必须使用不同的汇编语言重新编写程序

+ 高级语言(high-level)，致力于解决问题，而不针对特定的硬件。
+ 一种被称为**编译器**的特殊程序将高级语言翻译成特定计算机的内部语言。这样，就可以通过对每个平台使用不同的编译器来在不同的平台上使用同一个高级语言程序了

+ 一般来说，计算机语言要处理两个概念--数据和算法
  - 数据，是程序使用和处理的信息
  - 算法，是程序使用的方法

+ 结构化编程，将分支（决定接下来应执行哪个指令）限制为一小组行为良好的结构。
+ C语言的词汇表中就包含了这些结构：for循环，while循环，do while循环，if else语句
+ **结构化编程技术反映了过程性编程的思想，根据执行的操作来构思一个程序**

+ 面向对象编程(OOP)，与强调算法的过程性编程不同的是，OOP强调的是数据。它不像过程性编程那样，试图使问题满足语言的过程性方法，而是试图**让语言来满足问题的要求**。其理念是设计与问题的本质特性相对应的数据格式。

+ **在C++中，类是一种规范，它描述了这种新型数据格式，对象是根据这种规范构造的特定数据结构。**
+ OOP程序设计方法首先设计类，它们准确地表示了程序要处理的东西。类定义描述了对每个类可执行的操作，然后便可以设计一个使用这些类的对象的程序。
+ 从低级组织（如类）到高级组织（如程序）的处理过程，叫做自下向上(bottom-up)的编程
+ OOP编程并不仅仅是将数据和方法合并为类定义。
  - 它还有助于创建可重用的代码，这将减少大量的工作。
  - 信息隐藏可以保护数据
  - 多态能够为运算符和函数创建多个定义，通过编程上下文来确定使用哪个定义
  - 继承能够使用旧类派生出新类
+ OOP引入了很多新的理念，使用的编程方法不同于过程性编程。它不是将重点放在任务上，而是放在表示概念上。

+ 泛型编程(generic programming)是C++支持的另一种编程模式。它与OOP的目标相同，即使重用代码和抽象通用概念的技术更简单。
+ 不过OOP强调的是编程的数据方便，而泛型编程强调的是独立于特定数据类型。它们的侧重点不同。
+ OOP是一个管理大型项目的工具，而泛型编程提供了执行常见任务（例如对数据排序或合并链表）的工具。
+ 术语泛型(generic)指的是，创建独立于类型的代码。
  - C++的数据表示有多种类型--整数，小数，字符，字符串，用户定义的，由多种类型组成的符合结构。
  - 例如，要对不同类型的数据进行排序，通常必需为每种类型创建一个排序函数。
  - 泛型编程需要对语言进行扩展，以便可以只编写一个泛型（即不是特定类型的）函数，并将其用于各种实际类型。
  - C++模板提供了完成这种任务的机制。

## 第二章 开始学习C++

+ 语句，是要执行的操作。
+ 为理解源代码，编译器需要直到一条语句何时结束，另一条语句何时开始。有些语句使用语句分隔符。
+ C++与C一样，使用终止符(terminator)，而不是分隔符。
+ 终止符是一个分号，它是语句的结束标记，是语句的组成部分，而不是语句之间的标记
+ 结论：在C++中，不能省略分号

+ 通常，C++函数可被其他函数激活或调用
+ 函数头描述了函数与调用它的函数之间的接口。
+ 位于函数名前面的部分叫做函数返回类型，**它描述的是从函数返回给调用它的函数的信息**。
+ 函数名后括号中的部分叫做形参列表(argument list)或参数列表(parameter list)。它描述的是从调用函数传递给被调用的函数的信息。

+ C++注释以双斜杠(`//`)打头，到行尾结束。注释可以位于单独的一行上，也可以和代码位于同一行
+ C-风格注释，包括在符号`/*`和`*/`之间。由于C-风格注释以`*/`结束，而不是到行尾结束，因此可以跨越多行。事实上，C99标准也在C语言中添加了`//`注释

+ 源代码中的标记和空白
  - 一行代码中不可分隔的元素叫做标记(token)。
  - 通常，必需用空格，制表符或回车将两个标记分开。空格，制表符和回车统称为空白(white space)。
+ C++源代码风格
  - 每条语句占一行
  - 每个函数都有一个开始花括号和一个结束花括号，这两个花括号各占一行
  - 函数中的语句都相对于花括号进行缩进
  - 与函数名称相关的圆括号周围没有空白。

+ C++程序是一组函数，而每个函数又是一组语句

+ 计算机是一种精确的，有条理的机器。要将信息项存储在计算机中，必须指出信息的存储位置和所需的内存空间。
+ 在C++中，完成这种任务的一种相对简便的方法，是使用声明语句来指出存储类型并提供位置标签。
+ 程序中的声明语句叫做定义声明(defining declaration)语句，简称为定义(definition)。这意味着它将导致编译器为变量分配内存空间。在较为复杂的情况下，还可能有引用声明(reference declaration)

+ 总结
  1. C++程序由一个或多个被称为函数的模块组成。程序从main()函数开始执行，因此该函数必不可少。函数由函数头和函数体组成。函数头指出函数的返回值的类型和函数期望通过参数传递给它的信息的类型。函数体由一系列位于花括号`{}`中的C++语句组成
  2. 有多种类型的C++语句，包括：
       - 声明语句，定义函数中使用的变量的名称和类型
       - 赋值语句，使用赋值运算符`=`给变量赋值
       - 消息语句，将消息发送给对象，激发某种行为
       - 函数调用，执行函数。被调用的函数执行完毕后，程序返回到函数调用语句后面的语句
       - 函数原型，声明函数的返回类型，函数接受的参数数量和类型
       - 返回语句，将一个值从被调用的函数那里返回到调用函数中。

## 第三章 处理数据

+ 计算机内存的基本单元是位(bit)。
+ 可以将位看作电子开关，可以开，也可以关。关表示值0，开表示值1。
+ 8为的内存块可以设置出256中不同的组合，因为每一位都可以有两种设置，所以8位的总组合数为256。
+ 字节(byte)，**通常指的是8位的内存单元**。从这个意义上来说，**字节指的就是描述计算机内存量的度量单位**，1KB等于1024字节，1MB等于1024KB。


## 第四章 复合类型

### 指针与C++基本原理

+ 面向对象编程与传统的过程性编程的区别在于，OOP强调的是在**运行阶段（而不是编译阶段）进行决策**。
  - 运行阶段，指的是程序正在运行时
  - 编译阶段，指的是编译器将程序组合起来时。
+ 运行阶段决策，就好比度假时，选择参观那些景点取决于天气和当时的心情；而编译阶段决策更像不管在什么条件下，都坚持预先设定的日程安排。
+ 运行阶段决策提供了灵活性，可以根据当时的情况进行调整

### 指针小结

+ 声明指针
+ 给指针赋值。应将内存地址赋给指针。**可以对变量名应用`&`运算符，来获得被命名的内存的地址，new运算符返回未命名的内存的地址**。
+ 对指针解除引用。
  - 对指针解除引用意味着获得指针指向的值。对指针应用解除引用或间接值运算符(`*`)来解除引用。
  - 另一种对指针解除引用的方法是**使用数组表示法**。例如，`pn[0]`与`*pn`是一样的。一定不要对未被初始化为适当地址的指针解除引用。
+ 区分指针和指针所指向的值
+ 数组名。在多数情况下，C++将数组名视为数组的第一个元素的地址。一种例外情况是，将sizeof运算符用于数组名时，此时将返回整个数组的长度（单位为字节）
+ 指针算术
+ 数组的动态联编和静态联编
  - 使用数组声明来创建数组时，将采用静态联编，即数组的长度在编译时设置
  - 使用`new[]`运算符创建数组时，将采用动态联编(动态数组),即将在运行时为数组分配空间，其长度也将在运行时设置。使用完这种数组后，应该使用`delete[]`释放其占用的内存
+ 数组表示法和指针表示法
  - 使用方括号数组表示法等同于对指针解除引用
  - 数组名和指针变量都是如此，因此对于指针和数组名，即可以使用指针表示法，也可以使用数组表示法

### 自动存储，静态存储和动态存储

+ 自动存储
  - 在函数内部定义的常规变量使用自动存储空间，被称为自动变量(automatic variable)，这意味着它们在所属的函数被调用时自动产生，在该函数结束时小王
  - 实际上，自动变量是一个局部变量，其作用域为包含它的代码块。代码块是被包含在花括号中的一段代码。
  - 自动变量通常存储在栈中。这意味着执行代码块时，其中的变量将依次加入到栈中，而在离开代码块时，将按相反的顺序释放这些变量，这被称为后进先出(LIFO)。因此，在程序执行过程中，栈将不断地增大和缩小。

+ 静态存储
  - 静态存储是整个程序执行期间都存在的存储方式。
  - 使变量成为静态的方式有两种：一种是在函数外面定义它，另一种是在声明变量时使用关键字`static`

+ 动态存储
  - new和delete运算符提供了一种比自动变量和静态变量更灵活的方法。
  - 它们管理了一个内存池，这在C++中被称为自由存储空间(free store)或堆(heap)。
  - 该内存池同用于静态变量和自动变量的内存是分开的。new和delete能够在一个函数中分配内存，而在另一个函数中释放它。因此数据的生命周期不完全受程序或函数的生存时间控制。

+ 栈，堆和内存泄漏
  - 如果使用new运算符在自由存储空间（或堆）上创建变量后，没有调用delete，则即使包含指针的内存由于作用域规则和对象生命周期的原因而被释放，在自由存储空间上动态分配的变量或结构也将继续存在。
  - 实际上，将会无法访问自由存储空间中的结构，因为指向这些内存的指针无效。这将导致内存泄漏。被泄漏的内存将在程序的整个生命周期内都不可使用；这些内存被分配出去，但无法收回。
  - 极端情况（不过不常见）是，内存泄漏可能会非常严重，以致于应用程序可用的内存被耗尽，出现内存耗尽错误，导致程序崩溃。另外，这种泄漏还会给一些操作系统或在相同的内存空间中运行的应用程序带来负面影响，导致它们崩溃。

## 第八章

+ 内联函数是C++为提供程序运行速度所做的一项改进。常规函数和内联函数之间的主要区别不在于编写方式，而在于C++编译器如何将它们组合到程序中。
+ 编译过程的最终产品是可执行程序--由一组机器语言指令组成。运行程序时，操作系统将这些指令载入到计算机内存中，因此每条指令都有特定的内存地址。计算机随后将逐步执行这些指令。

+ 引用变量
  - 引用是已定义的变量的别名（另一个名称）
  - 引用变量的主要用途是用作函数的形参。通过将引用变量用作参数，函数将使用原始数据，而不是其副本。这样除指针之外，引用也为函数处理大型结构提供了一种非常方便的途径，同时对于设计类来说，引用也是必不可少的
  - `int rats; int & rodents = rats;  // make rodents an alias for rate`
  - 其中，`&`不是地址运算符，而是类型标识符的一部分。就像声明中的`char*`指的是指向`char`的指针一样，`int&`指的是指向int的引用。
  + 引用经常被用作函数参数，使得函数中的变量名称为调用程序中的变量的别名，这种传递参数的方法称为按引用传递。按引用传递允许被调用的函数能够访问调用函数中的变量

### 实例化和具体化

+ 为进一步了解模板，必需理解术语：实例化和具体化
+ 谨记：在代码中包含函数模板本身并不会生成函数定义，它只是一个用于生成函数定义的方案。编译器使用模板为特定类型生成函数定义时，得到的是模板实例(instantiation)
  - 例如，函数调用`Swap(i, j)`导致编译器生成`Swap()`的一个实例，该实例使用int类型。模板并非函数定义，但是使用int的模板实例是函数定义。**这种实例化方式被称为隐式实例化(implicit instantiation),因为编译器之所以知道需要进行定义，是由于程序调用`Swap()`函数时提供了int参数。
  - 最初，编译器只能通过隐式实例化，来使用模板生成函数定义，但是现在C++还允许显式实例化(explicit instantiation)。这意味着可以直接命令编译器创建特定的实例，例如`Swap<int>()`。其语法是，声明所需要的种类--使用`<>`符号指示类型，并在声明前加上关键字`template` -- `template void Swap<int>(int, int);  // explicit instantiation`

### 小结

+ 引用变量是一种伪装指针，它允许为变量创建别名（另一个名称）。引用变量主要被用作处理结构和类对象的函数的参数。
+ 通常，被声明为特定类型引用的标识符只能指向这种类型的数据；然而，如果一个类是从另一个类派生出来的，则基类引用可以指向派生类对象

+ 函数的特征标是它的参数列表。程序员可以定义两个同名函数，只要其特征标不同。这被称为函数多态或函数重载。
+ **通常，通过重载函数来为不同的数据类型提供相同的服务**。

+ 函数模板自动完成重载函数的过程。只需使用泛型和具体算法来定义函数，编译器将为程序中使用的特定参数类型生成正确的函数定义 

## 第九章 内存模型和名称空间

### 头文件管理

+ 在同一个文件中只能将同一个头文件包含一次。记住这个规则很容易，但很可能在不知情的情况下将头文件包含多次。
  - 例如，可能使用包含了另一个头文件的头文件。有一种标准的C/C++技术可以避免多次包含同一个文件。
+ 它是基于预处理编译指令`#ifndef`（即if not defined)

### 自动变量和栈

+ 了解典型的C++编译器如何实现自动变量，有助于更深入地了解自动变量
+ 由于自动变量的数目随函数的开始和结束而增减，因此程序必须在运行时对自动变量进行管理。

+ 常用的方法是留出一段内存，并将其视为栈，以管理变量的增减。之所以被称为栈，是由于新数据被象征性地放在原有数据的上面（也就是说，在相邻的内存单元中，而不是在同一个内存单元中），当程序使用完后，将其从栈中删除。栈的默认长度取决于实现，但编译器通常提供改变栈长度的选项。
+ 程序使用两个指针来跟踪栈，一个指针指向栈底--栈的开始位置，另一个指针指向栈顶--下一个可用内存单元。当函数被调用时，其自动变量将被加入到栈中，栈顶指针指向变量后面的下一个可用的内存单元。函数结束时，栈顶指针被重置为函数被调用前的值，从而释放新变量使用的内存。

+ 栈是LIFO（后进先出）的，即最后加入到栈中的变量首先被弹出。这种设计简化了参数传递。函数调用将其参数的值放在栈顶，然后重新设置栈顶指针。被调用的函数根据其形参描述来确定每个参数的地址。

### 寄存器变量

+ 关键字`register`最初是由C语言引入的，它建议编译器使用CPU寄存器来存储自动变量，这样的目的是--提高访问变量的速度。

### 说明符和限定符

+ 有些被称为存储说明符(storage class specifier)或cv-限定符(cv-qualifier)的C++关键字提供了其他有关存储的信息

+ 存储说明符
  1. `auto`（在C++11中不再是说明符）
       - 在C++11之前，可以在声明中使用关键字`auto`指出变量为自动变量
       - 在C++11中，`auto`用于自动类型推断。
  2. `register`
       - 用于在声明中指示寄存器存储，
       - 在C++11中，它只是显式地指出变量是自动的
  3. `static`
       - 它被用在作用域为整个文件的声明中时，表示内部链接性
       - 被用于局部声明中，表示局部变量的存储持续性为静态的
  4. `extern`
       - 它表明是引用声明，即声明引用在其他地方定义的变量
  5. `thread_local`（C++11新增加的，可与`static`或`extern`结合使用）
       - 它指出变量的持续性与其所属线程的持续性相同
       - `thread_local`变量之于线程，犹如常规静态变量之于整个程序
  6. `mutable`
       - 它的含义将根据const来解释
       - 可以用它来指出，即时结构（或类）变量为const，其某个成员也可以被修改

+ cv-限定符(cv表示const volatile)
  1. `const` 
       - 它是最常用的cv-限定符，它表明--内存被初始化后，程序便不能再对它进行修改
  2. `volatile`
       - 它表明，即时程序代码没有对内存单元进行修改，其值也可能发生变化；该关键字的作用是为了改善编译器的优化能力
       - 例如，假设编译器发现，程序在几条语句中两次使用了某个变量的值，则编译器可能不是让程序查找这个值两次，而是将这个值缓存到寄存器中。这种优化假设变量的值在这两次使用之间不会变化。如果不将变量声明为`volatile`，则编译器将进行这种优化；将变量声明为`volatile`，相当于告诉编译器，不要进行这种优化。

### 小结

+ C++鼓励程序员在开发程序时使用多个文件。一种有效的组织策略是，使用头文件来定义用户类型，为操纵给用户类型的函数提供函数原型；并将函数定义放在一个独立的源代码文件中。头文件和源代码文件一起定义和实现了用户定义的类型及其使用方式。最后，将`main()`和其他使用这些函数的函数放在第三个文件中


## 第十章 对象和类

+ 过程性编程方法 -- 首先考虑要遵循的步骤，然后考虑如何表示这些数据（并不需要程序一直运行，用户可能希望能够将数据存储在一个文件中，然后从这个文件中读取数据）

+ OOP方法 -- 首先从用户的角度考虑对象，描述对象所需的数据以及描述用户与数据交互所需的操作。完成对接口的描述后，需要确定如何实现接口和数据存储。最后，使用新的设计方案创建出程序。

+ 指定基本类型完成了三项工作
  - 决定数据对象需要的内存数量
  - 决定如何解释内存中的位（long和float在内存中占用的位数相同，但将它们转换为数值的方法不同）
  - 决定可使用数据对象执行的操作或方法

+ 类，是一种将抽象转换为用户定义类型的C++工具，它将数据表示和操纵数据的方法组合成一个整洁的包
+ 类规范由两个部分组成
  - 类声明：以数据成员的方式描述数据部分，以成员函数（被称为方法）的方式描述公有接口
  - 类方法定义：描述如何实现类成员函数
  - 简单地说，类声明提供了类的蓝图，而方法定义则提供了细节

### 什么是接口？

+ 接口，是一个共享框架，供两个系统（例如在计算机和打印机之间或者用户和计算机程序之间）交互时使用

+ 对于类，我们说公共接口。在这里，公共(public)是使用类的程序，交互系统由类对象组成，而接口由编写类的人提供的方法组成。
+ 接口，让程序员能够编写与类对象交互的代码，从而让程序能够使用类对象。

+ 为开发一个类并编写一个使用它的程序，需要完成多个步骤。这里将开发过程分成多个阶段，而不是一次性完成。
+ 通常，C++程序员将接口（类定义）放在头文件中，并将实现（类方法的代码）放在源代码文件中。

### 访问控制

+ 使用类对象的程序都可以直接访问公有部分，但只能通过公有成员函数来访问对象的私有成员。
+ 因此，公有成员函数是程序和对象的私有成员之间的桥梁，提供了对象和程序之间的接口。防止程序直接访问数据被称为数据隐藏

+ 类设计尽可能将公有接口与实现细节分开。
  - 公有接口表示设计的抽象组件。将实现细节放在一起并将它们与抽象分开被称为封装。
  - 数据隐藏（将数据放在类的私有部分中）是一种封装，将实现的细节隐藏在私有部分中，也是一种封装
  - 封装的另一个例子是，将类函数定义和类声明放在不同的文件中

+ 类和结构
  - 类描述看上去很像是包含成员函数以及public和private可见性标签的结构声明。
  - 实际上，C++对结构进行了扩展，使之具有与类相同的特性。它们之间唯一的区别是，结构的默认访问类型是public，而类为private。C++程序员通常使用类来实现类描述，而把结构限制为只表示纯粹的数据对象（常被称为普通老式数据结构）

### 实现类成员函数

+ 创建类描述的第二个部分：为那些由类声明中的原型表示的成员函数提供代码。
+ 成员函数定义与常规函数定义非常相似，它们有函数头和函数体，也可以有返回类型和参数。但是它们还有两个特殊的特征：
  - **定义成员函数时，使用作用域解析运算符(`::`)来表示函数所属的类**
  - **类方法可以访问类的`private`组件**

+ 成员函数的函数头使用作用域运算符解析(`::`)来指出函数所属的类。因此，作用域解析运算符确定了方法定义对应的类的身份。

### 内联方法

+ 定义位于类声明中的函数都将自动成为内联函数

+ 内联函数的特殊规则要求在每个使用它们的文件中都对其进行定义。确保内联定义对多文件程序中的所有文件都可用的，最简便的方法是：将内联定义放在定义类的头文件中（有些开发系统包含智能链接程序，允许将内联定义放在一个独立的实现文件）

### 方法使用哪个对象

+ 所创建的每个新对象都有自己的存储空间，用于存储其内部变量和类成员；但同一个类的所有对象共享同一组类方法，即每种方法只有一个副本。
  - 例如，假设kate和joe都是Stock对象，则`kate.shares`将占据一个内存块，而`joe.shares`占用另一个内存块，但`kate.show()`和`joe.show()`都调用同一个方法，也就是说，它们将执行同一个代码块，只是将这些代码用于不同的数据。

+ 在OOP中，调用成员函数被成为发送消息，因此将同样的消息发送给两个不同的对象将调用同一个方法，但是该方法被用于两个不同的对象。

### 类作用域

+ 在类中定义的名称（如类数据成员名和类成员函数名）的作用域都为整个类，作用域为整个类的名称只在该类中是已知的，在类外是不可知的。
+ 另外，类作用域意味着不能从外部直接访问类的成员，公有成员函数也是如此。也就是说，要调用公有成员函数，必需通过对象
+ 同样，在定义成员函数时，必需使用作用域解析运算符
  
+ 总之，在类声明或成员函数定义中，可以使用未修饰的成员名称。
+ 构造函数名称在被调用时，才能被识别，因为它的名称与类名相同
+ 其他情况下，使用类成员名时，必需根据上下文使用直接成员运算符(`.`)，间接成员运算符(`->`)或作用域解析运算符(`::`)

### 小结

+ 面向对象编程强调的是程序如何表示数据。使用OOP方法解决编程问题的第一步是根据它与程序之间的接口来描述数据，从而指定如何使用数据。然后，设计一个类来实现该接口。一般来说，私有数据成员存储信息，公有成员函数（又称方法）提供访问数据的唯一途径。类将数据和方法组合成一个单元，其私有性实现数据隐藏

+ 类是用户定义的类型，对象是类的实例。这意味着对象是这种类型的变量。例如由new按类描述分配的内存


## 第十一章 使用类

+ 学习C++的难点之一是需要记住大量的东西，但在拥有丰富的实践经验之前，根本不可能全部记住这些东西。
+ 掌握知识的好的方法是，在自己开发的C++程序中使用其中的新特性。对这些新特性有了充分的认知后就可以添加其他C++特性

+ 正如C++创始人`Bjarne Stroustrup`在一次C++专业程序员大会上所建议的：**轻松地使用这种语言。不要觉得必须使用所有的特性，不要在第一次学习时就试图使用所有的特性**


## 第十二章 类和动态内存分配

### 指针和对象小结

+ 使用常规表示法来声明指向对象的指针 -- `String* gla;`

+ 可以将指针初始化为指向已有的对象 -- `String* first = &saying[0];`

+ 可以使用new来初始化指针，这将创建一个新的对象 -- `String* favorite = new String(sayings[choice])`

+ 对类使用new将调用相应的类构造函数来初始化新创建的对象

+ 可以使用`->`运算符通过指针访问类方法 -- `shortest->length()`

+ 可以对对象指针应用解除引用运算符(`*`)来获得对象 -- `first = &saying[i];`


## 第十三章 类继承

+ 希望同一个方法在派生类和基类中的行为是不同的。换句话来说，方法的行为应该取决于调用方法的对象。这种较复杂的行为称为多态--具有多种形态，即同一个方法的行为随上下文而异。

+ 有两种重要的机制可用于实现多态公有继承：
  - 在派生类中重新定义基类的方法
  - 使用虚方法

+ **注意** 
  - 如果要在派生类中重新定义基类的方法，通常**应将基类方法声明为虚的**。这样，程序将根据对象类型而不是引用或指针的类型来选择方法版本。
  - 为基类声明一个虚析构函数也是一种惯例

### 静态联编和动态联编

+ 程序调用函数时，将使用哪一个可执行代码块？  编译器负责回答这个问题
+ 将源代码中的函数调用解释为执行特定的函数代码块被称为**函数名联编(binding)**

+ 在C语言中，这非常简单，因为每个函数名都对应一个不同的函数

+ 在C++中，由于函数重载的远古，这项任务更复杂。编译器必须查看函数参数及函数名才能确定使用哪一个函数。
  
+ C/++编译器可以在编译过程完成这种联编。在编译过程中进行联编被称为**静态联编(static binding)，又称为早期联编(early binding)**
+ 然而，虚函数使这项工作变得更困难。因为虚函数使得 -- 使用哪一个函数是不能在编译时确定的。因为编译器不知道用户将选择那种类型的对象，所以，编译器必须生成能够在程序运行时选择正确的虚函数的代码，这被称为**动态联编(dynamic binding)，又称为晚期联编(late binding)**

+ 将派生类引用或指针转转为基类引用或指针 被称为**向上强制转换(upcasting)**,这使公有继承不需要进行显式类型转换。

+ 相反的过程 -- 将基类指针或引用转换为派生类指针或引用 被称为**向下强制转换(downcasting)**

+ 编译器对非虚方法使用静态联编

+ 为什么有两种类型的联编以及为什么默认为静态联编？ -- 效率和概念模型

+ 效率
  - 为了使程序能够在运行阶段进行决策，必须采取一些方法来跟踪基类指针或引用指向的对象类型，这增加了额外的处理开销
  - C++的指导原则之一是 -- 不要为不使用的特性付出代价（内存或处理时间）。仅当程序设计确实需要虚函数时，才适用它们

+ 虚函数的工作原理
  1. 通常，编译器处理虚函数的方法是：给每个对象添加一个隐藏成员。隐藏成员中保存了一个指向函数地址数组的指针。这种数组称为虚函数表(virtual function table, vtbl)。
  2. 虚函数表中存储了为类对象进行声明的虚函数的地址。
    - 例如，基类对象包含了一个指针，该指针指向基类中所有虚函数的地址表。派生类对象将包含一个指向独立地址的指针。如果派生类提供了虚函数的新定义，该虚函数表将保存新函数的地址；如果派生类没有重新定义虚函数，该vtbl将保存函数原始版本的地址。如果派生类定义了新的虚函数，则该函数的地址也将被添加到vtbl中
    - 调用虚函数时，程序将查看存储在对象中的vtbl地址，然后转向相应的函数地址表。如果使用类声明中定义的第一个虚函数，则程序将使用数组中的第一个函数地址，并执行具有该地址的函数。如果使用类声明中的第三个虚函数，程序将使用地址为数组中第三个元素的函数。
+ 总之，使用虚函数时，在内存和执行速度方面有一定的成本，包括
  - 每个对象都将增大，增大量为存储地址的空间
  - 对于每个类，编译器都要创建一个虚函数地址表（数组)
  - 对于每个函数调用，都需要执行一项额外的操作，即在表中查找地址

+ **有关虚函数注意事项**
  - 在基类方法的声明中使用关键字`virtual`可以使该方法在基类以及所有的派生类（包括从派生类派生出来的类）中是虚的
  - 如果使用指向对象的引用或指针来调用虚方法，程序将使用为对象类型定义的方法，而不使用为引用或指针类型定义的方法。这称为动态联编或晚期联编。这种行为非常重要。因为这样基类指针或引用可以指向派生类对象
  - 如果定义的类将被用作基类，则应将那些要在派生类中重新定义的类方法声明为虚的。

+ 当基类和派生类都采用动态内存分配时，派生类的析构函数，复制构造函数，赋值运算符都必须使用相应的基类方法来处理基类元素。
+ 这种要求是要通过三种不同的方式来满足的。对于析构函数，这是自动完成的；对于构造函数，这是通过在初始化成员列表中调用基类的复制构造函数来完成的；如果不这样做，将自动调用基类的默认构造函数。对于赋值运算符，这是通过使用作用域解析运算符显式地调用基类的赋值运算符来完成的。

### 小结

+ 继承，通过使用已有的类（基类）定义新的类（派生类），使得能够根据需要修改编程代码。


## C++中的代码重用

+ C++的一个主要目标是促进代码重用。公有继承是实现这种目标的机制之一，但并不是唯一的机制。
+ 方法之一是使用这样的类成员--本身是另一个类的对象。这种方法称为包含(containment), 组合(composition)或层次化(layering)
+ 另一种方法是使用私有或保护继承。通常，包含，私有继承和保护继承用于实现`has-a`关系，即新的类将包含另一个类的对象。

+ C++和约束
  - C++包含让程序员能够限制程序结构的特性--使用`explicit`防止单参数构造函数的隐式转换，使用const限制方法修改数据，等等。
  - 这样做的根本原因是：**在编译阶段出现错误优于在运行阶段出现错误

+ 使用包含还是私有继承？
  - 由于即可以使用包含，也可以使用私有继承来建立`has-a`关系，那么应该使用那种方式？
  - 通常，应该使用包含来建立`has-a`关系；
  - 如果新类需要访问原有类的保护成员，或者需要重新定义虚函数，则应该使用私有继承

### 类模板

+ `template <class Type>`
+ 关键字`template`告诉编译器，将要定义一个模板。尖括号中的内容相当于函数的参数列表。可以把关键字class看作是变量的类型名，该变量接受类型作为其值，把`Type`看作是该变量的名称。
+ 这里使用class并不意味着`Type`必须是一个类；而只是表明`Type`是一个通用的类型说明符，在使用模板时，将使用实际的类型替换它。较新的C++实现**允许在这种情况下使用不太容易混淆的关键字`typename`代替class**
  - `template <typename Type>  // newer choice`
+ 可以使用自己的泛型名代替`Type`，其命名规则与其他标识符相同。**当前流行的选项包括`T`和`Type`。
+ 当模板被调用时，`Type`将被具体的类型值（例如int， string）取代。在模板定义中，可以使用泛型名来表示要存储在栈中的类型。

### 小结

+ C++提供了几种重用代码的手段

+ 公有继承能够建立`is-a`关系，这样派生类可以重用基类的代码
+ 私有继承和保护继承也使得能够重用基类的代码，但是建立的是`has-a`关系
  - 使用私有继承时，基类的公有成员和保护成员将称为派生类的私有成员
  - 使用保护继承时，基类的公有成员和保护成员将成为派生类的保护成员
+ **无论使用哪一种继承，基类的公有接口都将成为派生类的内部接口，这有时候被称为继承实现，但并不继承接口，因为派生类对象不能显式地使用基类的接口。因此，不能将派生对象看作是一种基类对象。由于这个原因，在不进行显式类型转换的情况下，基类指针或引用将不能指向派生类对象。**

+ 还可以通过开发包含对象成员的类来重用类代码，这种方法被称为包含，层次化或组合。
+ 它建立的是`has-a`关系。与私有继承和保护继承相比，包含更容易实现和使用，所以通常优先采用这种方式。
+ 然而，私有继承和保护继承比包含有一些不同的功能。例如，继承允许派生类访问基类的保护成员；还允许派生类重新定义从基类那里继承的徐函数。因为包含不是继承，所以通过包含来重用类代码时，不能使用这些功能
+ 另一个方面，如果需要使用某个类的几个对象，则用包含更加合适。

+ 所有这些机制的目的都是为了让程序员能够重用经过测试的代码，而不用手工复制它们，这样可以简化编程工作，提供程序的可靠性。


## 第十五章 友元，异常和其他

+ 在C++中，可以将类声明放在另一个类中。在另一个类中声明的类称为嵌套类(nested class)，它通过提供新的类型类作用域来避免名称混乱。
+ 包含的类的成员函数可以创建和使用被嵌套类的对象；而仅当声明位于公有部分，才能在包含类的外面使用嵌套类，而且必须使用作用域解析运算符。

### 异常

+ 如果其中一个参数是另一个参数的负值，则调用abort（）函数。Abort（）的函数原型位于头文件`cstdlib`中，其典型实现是向标准错误流(即`cerr`使用的错误流)发送消息`abnormal program termination（程序异常终止）`，然后终止程序。它还返回一个随实现而异的值，告诉操作系统（如果程序是由另一个程序调用的，则告诉父进程）处理失败。
+ `abort()`是否刷新文件缓冲区（用于存储读写到文件中的数据的内存区域）取决于实现。

### 返回错误码

+ 一种比异常终止更灵活的方法是，使用函数的返回值来指出问题

### 异常机制

+ C++异常是对程序运行过程中发生的异常情况的一种响应。
+ 异常提供了将控制权从程序的一个部分传递到另一个部分的途径。
+ 对异常的处理有3个组成部分：
    - 引发异常；
    - 使用处理程序捕获异常
    - 使用try块

+ 程序在出现问题时将引发异常。**`throw`语句实际上是跳转，即命令程序跳到另一条语句**。
+ `throw`关键字表示引发异常，紧随其后的值（例如字符串或对象）指出了异常的特征。

+ 程序使用异常处理程序(`exception handler`)来捕获异常，异常处理程序位于要处理问题的程序中。
+ `catch`关键字表示捕获异常。处理程序以关键字`catch`开头，随后是位于括号中的类型声明，它指出了异常处理程序要响应的异常类型；然后是一个用花括号括起来的代码块，指出要采取的措施。
+ `catch`关键字和异常类型用作标签，指出当异常被引发时，程序应该跳到这个位置执行。异常处理程序也被称为`catch`块

+ `try`块标识其中特定的异常可能被激活的代码块，它后面跟一个或多个`catch`块。`try`块是由关键字`try`指示的，关键字`try`的后面是一个由花括号括起来的代码块，表明需要注意这些代码引发的异常。

+ 通常，引发异常的函数将传递一个对象。这样做的重要优点之一是，可以使用不同的异常类型来区分不同的函数在不同的情况下引发的异常。
+ 另外，对象可以携带信息，程序员可以根据这些信息来确定引发异常的原因。同时，`catch`块可以根据这些信息来决定采取什么样的措施

### 栈解退

+ C++通常是如何处理函数调用和返回的。
+ C++通常通过将信息放在栈中来处理函数调用。具体地说，程序将调用函数的指令的地址（返回地址）放到栈中。当被调用的函数执行完毕后，程序将使用该地址来确定从哪里开始继续执行。另外，函数调用将函数参数放到栈中。在栈中，这些函数参数都被视为自动变量。如果被调用的函数创建了新的自动变量，则这些变量也将被添加到栈中。如果被调用的函数调用了另一个函数，则后者的信息将被添加到栈中，依次类推。
+ 当函数结束时，程序流程将跳到该函数被调用时存储的地址处，同时栈顶的元素被释放。因此，函数通常都返回到调用它的函数，依次类推，同时每个函数都在结束时释放其自动变量。如果自动变量是类对象，则类的析构函数将被调用。

+ 现在假设函数由于出现异常（而不是由于返回）而终止，则程序也将释放栈中的内存，但不会在释放栈的第一个返回地址后停止，而是继续释放栈，直到找到一个位于`try`块中的返回地址。随后，控制权将转到块尾的异常处理程序，而不是函数调用后面的第一条语句。这个过程被称为**栈解退**

## 第十六章 string类和标准模板库

+ `STL`提供了一组表示容器，迭代器，函数对象和算法的模板。

+ 容器是一个与数组类似的单元，可以存储若干个值。 STL容器是同质的，即存储的值的类型相同
+ 算法是完成特定任务（如对数组进行排序或在链表中查找特定值）的处方
+ 迭代器能够用来遍历容器的对象，与能够遍历数组的指针类似，是广义指针；
+ 函数对象是类似于函数的对象，可以是类对象或函数指针（包含函数名，因为函数名被用作指针）。
+ STL使得能够构造各种容器（包括数组，队列和链表）和执行各种操作（包括搜索，排序和随机排列）

### 泛型编程

+ `STL`是一种泛型编程(`generic programming`)。面向对象编程关注的编程的数据方面，而泛型编程关注的是算法。它们之间的共同点是抽象和创建可重用代码，但它们的理念绝然不同。
+ 泛型编程旨在编写独立于数据类型的代码。在C++中，完成通用程序的工具是模板。当然，模板使得能够按泛型定义函数或类，而STL通过通用算法更进了一步。模板让这一切成为可能，但必须对元素进行仔细地设计。为了解模板和设计是如何协同工作的，来看一看需要迭代器的原因。

+ **理解迭代器是理解`STL`的关键所在**。模板使得算法独立于存储的数据类型，而迭代器使得算法独立于使用的容器类型。因此，它们都是STL通用方法的重要组成部分。

+ 泛型编程旨在使用同一个find函数来处理数组，链表或任何其他容器类型。即函数不仅独立于容器中存储的数据类型，而且独立于容器本身的俄数据结构。模板提供了存储在容器中的数据类型的通用表示，因此还需要遍历容器中的值的通用表示，迭代器正是这样的通用表示。

+ 每个容器类(`vector list deque等`)定义了相应的迭代器类型。对于其中的某个类，迭代器可能是指针；而对于另一个类，则可能是对象。不管实现方式如何，迭代器都将提供所需的操作。
+ 其次，每个容器类都有一个超尾标记，当迭代器递增到超越容器的最后一个值后，这个值将被赋给迭代器。每个容器类都有`begin()`和`end()`方法，它们分别返回一个指向容器的第一个元素和超尾位置的迭代器。每个容器都有++操作，让迭代器从指向第一个元素逐步指向超尾位置，从而遍历容器中的每一个元素。

+ 使用容器类时，无需知道其迭代器是如何实现的，也无需知道超尾是如何实现的，而只需要知道它有迭代器，其`begin()`返回一个指向第一个元素的迭代器，`end()`返回一个指向超尾位置的迭代器即可。

+ 总结一下`STL`方法。首先是处理容器的算法，应尽可能通用的术语来表达算法，使之独立于数据类型和容器类型。为使通用算法能够适用于具体情况，应定义能够满足算法需求的迭代器，并把要求加到容器设计上。即基于算法的要求，设计基本迭代器的特征和容器特征。

#### 如何理解迭代？？

+ 迭代，是一个重复的过程，每次重复都是基于上一次的结果而继续的，**单纯的重复并不是迭代**，例如，A + B =》 E ，生成的过程就是迭代，克隆就不是迭代

+ 迭代器，指的是迭代取值的工具。而涉及到把多个值循环取出来的类型有：列表，字符串，元组，字典，集合，打开的文件对象

+ 实现一个简单的迭代取值（基于索引）的方式，只适用于有索引的数据类型：列表，字符串，字典
+ **为了解决基于索引迭代取值的局限性，就必须提供一种能够不依赖索引的取值方式，这就是迭代**

+ 在一个迭代器取值干净的情况下，再对其取值，取不到，必须再调用一次迭代器才能取值

---

+ `STL`定义了五种迭代器，并根据所需要的迭代器类型对算法进行了描述。这五种迭代器分别是输入迭代器，输出迭代器，正向迭代器，双向迭代器和随机访问迭代器。
  - 输入迭代器 -- 被程序用来读取容器中的信息，是单向迭代器，可以递增，但不能倒退
  - 输出迭代器 -- 用于将信息从程序传输到容器的迭代器，因此程序的输出就是容器的输入。
  - 正向迭代器 -- 每次沿容器向前移动一个元素，并总是按照相同的顺序遍历一系列值
  - 双向迭代器 -- 具有正向迭代器的所有特性，同时支持两种（前缀和后缀）递减运算符
  - 随机访问迭代器 -- 具有双向迭代器的所有特性，同时添加了支持随机访问的操作和用于对元素进行排序的关系运算符

---

### 概念，改进和模型

+ STL有若干个用C++语言无法表达的特性，例如迭代器种类。因此，虽然可以设计具有正向迭代器特征的类，但不能让编译器将算法限制为只使用这个类。
+ 原因在于，正向迭代器是一系列要求，而不是类型。所设计的迭代器类可以满足这种要求，常规指针也能满足这种要求。
+ STL算法可以使用任何满足其要求的迭代器实现。STL文献使用术语概念(concept)来描述一系列的要求。因此，存在输入迭代器概念，正向迭代器概念等。

+ **概念，可以具有类似继承的关系**。例如，双向迭代器继承了正向迭代器的功能。然而，不能将C++继承机制用于迭代器。例如，可以将正向迭代器实现为一个类，而将双向迭代器实现为一个常规指针。
+ 因此，对C++而言，这种双向迭代器是一种内置类型，不能从类派生而来。然而，从概念上看，它确实能够继承。有些`STL`文献使用术语**改进(refinement)**来表示这种概念上的继承，因此，双向迭代器是对正向迭代器概念的一种改进。
  
+ **概念的具体实现被称为模型(model)**。因此，指向int的常规指针是一个随机访问迭代器模型，也是一个正向迭代器模型，因为它满足该概念的所有要求。

---

### 关联容器

+ 关联容器(associative container)是对容器概念的另一个改进。关联容器将值与键关联在一起，并使用键来查找值。

+ 关联容器的优点在于，它提供了对元素的快速访问。与序列相似，关联容器也允许插入新元素，但不能指定元素的插入位置。原因是关联容器通常有用于确定数据放置位置的算法，以便能够快速检索信息。

+ 关联容器通常是使用某种树实现的。

+ STL提供了四种关联容器：`set, multiset, map, multimap`。前两种是在头文件`set`中定义的，后两种是在头文件`map`中定义的

---

### 函数对象

+ 很多`STL`算法都是用函数对象 -- 也叫函数符(functor)。函数符是可以以函数方式与`()`结合使用的任意对象。这包括函数名，指向函数的指针和重载了`()`运算符的类对象(即定义了函数`operator()`的类)

### 总结

+ C++提供了一组功能强大的库，这些库提供了很多常见编程问题的解决方案以及简化其他问题的工具。`string`类为将字符串作为对象来处理提供了一种方便的方法。`string`类提供了自动内存管理功能以及众多处理字符串的方法和函数

+ STL是一个容器类模板，迭代器类模板，函数对象模板和算法函数模板的集合，它们的设计是一致的，都是基于泛型编程原则的。算法通过使用模板，从而独立于所存储的对象的类型：通过使用迭代器接口，从而独立于容器的类型。迭代器是广义指针

+ **STL使用术语概念来描述一组要求**

+ 有些算法被表示为容器类方法，但大量算法都被表示为通用的，非成员函数，这是通过将迭代器作为容器和算法之间的接口得以实现的

+ 容器和算法都是由其提供或需要的迭代器类型表征的。


## 第十七章 输入， 输出和文件

+ 多数计算机语言的输入和输出是以语言本身为基础实现的。但是C和C++都没有将输入和输出建立在语言中。这两种语言的关键字包括for和if，但不包括与I/O有关的内容。C语言最初把I/O留给了编译器实现人员。这样做的一个原因是为了让实现人员能够自由的设计I/O函数，使之最适合于目标计算机的硬件要求。实际上，多数实现人员都把I/O建立在最初为UNIX环境开发的库函数的基础之上。ANSI C 正式承认这个I/O软件包时，将其称为标准输入/输出包，并将其作为标准C库不可或缺的组成部分。C++也认可这个软件包，因此如果熟悉`stdio.h`文件中声明的C函数系列，则可以在C++程序中使用它们，较新的实现使用头文件`cstdio`来支持这些函数。

+ C++依赖于C++的I/O解决方案，而不是C语言的I/O解决方案，前者是在头文件`iostream`中定义一组类

### 流和缓冲区

+ C++程序把输入和输出看作字节流。输入时，程序从输入流中抽取字节；输出时，程序将字节插入到输出流中。对于面向文本的程序，每个字节代表一个字符，更通俗地说，字节可以构成字符或数值数据的二进制表示。

+ 输入流中的字节可能来自键盘，也可能来自存储设备（例如硬盘）或其他程序。同样，输出流中的字节可以流向屏幕，打印机，存储设备或者其他程序。**流充当了程序和流源或流目标之间的桥梁**。
+ 这使得C++程序可以以相同的方式对待来自键盘的输入和来自文件的输入。C++程序只是检查字节流，而不需要知道字节来自何方。同理，通过使用流，C++程序处理输出的方式将独立于其去向。因此管理输入包含两部：
    - 将流和输入去向的程序关联起来
    - 将流和文件连接起来

+ 换句话说，输入流需要两个连接，每端各一个。文件端部连接提供了流的来源，程序端连接将流的流出部分转储到程序中（文件端连接可以是文件，也可以是设备）。同样，对输出的管理包括将输出流连接到程序以及将输出目标与流关联起来。

+ 通常，通过使用缓冲区可以更高效地处理输入和输出。
+ 缓冲区，**是用作中介的内存块，它是将信息从设备传输到程序或从程序传输给设备的临时存储工具**。
+ 缓冲区帮忙匹配两种不同的信息传输速率。
+ 输出时，程序首先填满缓冲区，然后把整块数据传输给硬盘，并清空缓冲区，以备下一批输出使用，这被称为刷新缓冲区(flushing the buffer)

### 文件输入和输出

+ 大多数计算机程序都使用了文件。字处理程序创建文档文件；数据库程序创建和搜索信息文件；编译器读取源代码文件并生成可执行文件。
+ 文件本身是存储在某种设备（磁盘，光盘，软盘或硬盘）上的一系列字节。通常，操作系统管理文件，跟踪它们的位置，大小，创建时间等。

### 小结

+ 流，是进出程序的字节流。
+ 缓冲区是内存中的临时存储区域，是程序与文件或其他I/O设备之间的桥梁。
+ 信息在缓冲区和文件之间传输时，将使用设备（例如磁盘驱动器）处理效率最高的尺寸以大块数据的方式进行传输。
+ 信息在缓冲区和程序之间传输时，是逐字节传输的。这种方式对于程序中的处理操作更为方便。
+ C++通过将一个被缓冲流同程序及其输入源相连接来处理输入。同样，C++也通过将一个被缓冲流和程序及其输出目标相连来处理输出。
+ `iostream`和`fstream`文件构成了I/O类库，该类库定义了大量用于管理流的类。

## 探讨C++新标准

+ 如果仔细阅读了本书，则应很好地掌握了C++的规则，然而，这仅仅是学习这种语言的开始，接下来需要学习如何高效地使用该语言，这样的路更长。更好的情况是，工作或学习环境能够接触到优秀的C++代码和程序员。
+ 另外，了解C++后，便可以阅读一些介绍高级主体和面向对象编程的书记，附录H列出了一些这样的资源。

+ OOP有助于开发大型项目，并提高其可靠性。OOP方法的基本活动之一是发明能够表示正在模拟的情况（被称为问题域(problem domain)）的类。
+ 由于实际问题通常很复杂，因此找到适当的类富有挑战性。创建复杂的系统时，从空白开始通常不可行，最好采用**逐步迭代**的方式。为此，该领域的实践者开发了多种技术和策略。**具体地说，重要的是在分析和设计阶段完成尽可能多的迭代工作，而不要不断地修改实际代码**。

+ 除了加深对C++的总体理解外，还可能需要学习特定的类库

## 附录H

+ C++常见问题解答，第二版 -- Cline, Marshall, Greg Lomow and Mike Girou. C++FAQ, Second Edition

+ C++标准库教程和参考手册 -- Josuttis, Nicolai M. The C++ Standard Library:A Tutorial and Reference

+ Meyers, Scott. Effective C++:55 Specific Ways to Improve Your Programs and Designs, Third Edition.
    - 本书针对的是了解C++的程序员，提供了55条规定和指南。其中一些是技术性的，例如解释何时应该定义复制构造函数和赋值运算符；其他一些更为通用，例如对`is-a` `has-a`关系的讨论

+ Stroustrup,Bjarne. The C++ Programming Language. Third Edition. 

+ `http://webstore.ansi.org`
+ `www.iso.org`
+ `http://www.parashift.com/C++-faq-lite`