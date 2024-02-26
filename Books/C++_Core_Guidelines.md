## 简介

+ C++ Core Guidelines笔记

## 第二章 理念

### 在代码中直接表达思想

+ 程序员应该直接用代码直接表达他们的思想，因为代码可以被编译器和工具检查
+ 一个专业的C++开发者应该了解STL算法

### 用ISO标准C++写代码

+ 使用当前的C++标准，不要使用编译器扩展
+ 此外，要注意未定义行为和实现定义行为
  + 未定义行为： 
  + 实现定义行为：程序的行为可能因编译器实现而异。实现必须在文档里描述实现的行为

在C++编程中，有两个重要的概念：未定义行为（Undefined Behavior）和实现定义行为（Implementation Defined Behavior）。

1. **未定义行为 (Undefined Behavior)**:
   - 当程序包含未定义行为时，C++标准没有规定程序的行为，允许编译器和运行时环境采用任何行为。这可能导致程序崩溃、产生意外结果、或者在不同的编译器、平台或编译选项下表现不同。
   - 未定义行为可能是由于程序中的错误、溢出、指针操纵等原因引起的，也可能是标准规定没有定义的操作。

2. **实现定义行为 (Implementation Defined Behavior)**:
   - 当某个方面的行为是由C++标准定义的，但是标准允许不同的实现在这方面做出不同的选择，这被称为实现定义行为。
   - 例如，标准规定某个操作的结果可以有多种可能，但实现需要选择其中一种并在文档中明确说明。

示例：

```cpp
#include <iostream>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << arr[5] << std::endl; // 未定义行为，越界访问数组

    int x = -5;
    unsigned int y = 10;
    std::cout << x * y << std::endl; // 实现定义行为，结果取决于具体的实现
    return 0;
}
```

在这个例子中，访问数组`arr`的第六个元素是未定义行为，因为数组索引越界。而对于`x * y`的乘法，结果是实现定义的，因为标准并没有规定对于负数和无符号数相乘的具体行为。

在编写C++代码时，尽量避免未定义行为，因为它可能导致代码在不同环境下的行为不可预测。实现定义行为可能会因不同的编译器或平台而异，但至少有一个可预测的结果。

+ 当你必须使用没有写在ISO标准里的扩展时，可以用一个稳定的接口将它们封装起来

### 表达意图

+ 表达意图是良好的代码文档的一个重要准则。文档应该说明代码会做什么，而不是代码会怎么做

### 不要泄漏任何资源

+ 资源可以是内存，也可以是文件句柄或者套接字。
+ 处理资源的惯用法是RAII。RAII是 Resource Acquisition Is Initialization(资源获取即初始化)的缩写，本质上意味着你在用户定义类型的构造函数中获取资源，在析构函数中释放资源。通过使对象成为一个有作用于的对象，C++的运行时会自动照顾到资源的生存期
+ C++大量使用RAII：锁负责处理互斥量，智能指针负责处理原始内存，STL的容器负责处理底层元素，等等

### 不可变数据优先于可变数据

+ 使用不可变数据的理由有很多。
+ 首先，当你使用常量时，你的代码更加容易验证
+ 最重要的是常量在并发程序中具有很大的优势
+ 不可变数据在设计上是没有数据竞争的，因为数据竞争的必要条件就是对数据进行修改

### 封装杂乱的构件，不要让他在代码中散布开

+ 混乱的代码往往是低级代码易于隐藏错误，容易出现问题。
+ 如果可能的话，用STL中的高级构件(例如容器和算法)来取代你的杂乱代码。
+ 如果这不可能，就把那些杂乱的代码封装带一个用户自定义的类型或者函数中

### 适当使用辅助工具

+ 计算机比人类更擅长做枯燥和重复性的工作。也就是说，应该使用静态分析工具，并发工具和测试工具来自动完成这些验证。
+ 用一个以上的C++编译器来编译代码，往往是验证代码的最简单方式。一个编译器可能检测不到某种未定义行为，而另一个编译器可能会在同样的情况下发出警告或者产生错误

### 适当使用支持库

+ 你应该去找设计良好，文档齐全，支持良好的库。
+ 突出的例子包括：
  + C++标准库
  + Guidelines支持的库
  + Boost库

## 第三章 接口

+ 接口是服务的提供者和使用者之间的契约

### 避免非const的全局变量

+ 全局变量会在函数中注入隐藏的依赖，而该依赖并不是接口的一部分
+ 非const的全局变量有许多弊端。首先，非const的全局变量破坏了封装。这种对封装的破坏让你无法对函数/类(实体)进行孤立思考。

### 避免单例

+ 单例就是全局变量，因此你应当尽可能避免单例。单例简单，直接地保证该类最多只有一个实例存在。
+ C++ 单例模式 详解
单例模式是一种设计模式，其目的是确保一个类只有一个实例，并提供全局访问点。这有助于确保在整个应用程序中共享相同的资源或状态，以及提供一种方便的方法来访问该实例。下面详细解释C++中的单例模式。

### 实现单例模式的步骤：

1. **私有构造函数：** 将类的构造函数声明为私有，以防止外部直接实例化类。

    ```cpp
    class Singleton {
    private:
        Singleton() {}  // 私有构造函数
    };
    ```

2. **静态成员变量：** 在类中声明一个静态私有指针，用于保存唯一的实例。

    ```cpp
    class Singleton {
    private:
        static Singleton* instance;  // 静态私有指针
        Singleton() {}  // 私有构造函数
    };
    ```

3. **静态方法：** 提供一个公共的静态方法，用于获取类的实例。在这个方法中，检查实例是否已经存在，如果不存在，则创建一个新实例并返回。

    ```cpp
    class Singleton {
    private:
        static Singleton* instance;  // 静态私有指针
        Singleton() {}  // 私有构造函数

    public:
        static Singleton* getInstance() {
            if (instance == nullptr) {
                instance = new Singleton();
            }
            return instance;
        }
    };
    ```

4. **删除复制构造函数和赋值运算符：** 为了防止通过复制构造函数或赋值运算符创建新实例，将它们声明为私有并不实现。

    ```cpp
    class Singleton {
    private:
        static Singleton* instance;  // 静态私有指针
        Singleton() {}  // 私有构造函数

    public:
        static Singleton* getInstance() {
            if (instance == nullptr) {
                instance = new Singleton();
            }
            return instance;
        }

    private:
        Singleton(const Singleton&);  // 禁止复制构造函数
        Singleton& operator=(const Singleton&);  // 禁止赋值运算符
    };
    ```

### 线程安全性：

上述实现在单线程环境下是有效的，但在多线程环境中可能会有问题。为了确保线程安全，可以使用加锁机制，例如互斥锁。

```cpp
#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;  // 静态私有指针
    static std::mutex mutex;     // 互斥锁
    Singleton() {}               // 私有构造函数

public:
    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);  // 加锁
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

private:
    Singleton(const Singleton&);             // 禁止复制构造函数
    Singleton& operator=(const Singleton&);  // 禁止赋值运算符
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

int main() {
    // 获取单例实例
    Singleton* singletonInstance1 = Singleton::getInstance();
    Singleton* singletonInstance2 = Singleton::getInstance();

    std::cout << "Address of instance 1: " << singletonInstance1 << std::endl;
    std::cout << "Address of instance 2: " << singletonInstance2 << std::endl;

    return 0;
}
```

这个例子中，通过 `std::mutex` 实现了简单的互斥锁，确保在多线程环境中仍然能够正确地创建单例实例。

### 运用依赖注入化解

+ 当某个对象使用单例的时候，隐藏的依赖就被注入对象中。而借助依赖注入技术，这个依赖可以变成接口的一部分，并且服务是从外界注入的。这样，客户代码和注入的服务之间就没有了依赖。
+ 依赖注入的典型方式是构造函数，设置函数(setter)成员或者模板参数

### 构建良好的接口

+ 函数应该通过接口(而不是全局变量)进行沟通。
+ 接口应当遵循以下规则：
  + 接口明确
  + 接口精确并且具有强类型
  + 保持较低的参数数目
  + 避免相同类型却不相关的参数相邻

+ 术语"可调用"(callable)。可调用实体是在行为上像函数的东西。它可以是函数，也可以是函数对象，或者是lambda表达时。
+ 如果可调用实体接受一个参数，它就是一元可调用实体；如果它接受两个参数，则称为二元可调用实体
+ std::transform_reduce先将一元可调用实体应用到一个范围或者将二元可调用实体应用到两个范围，然后将二元可调用实体应用到前一步的结果的范围上。

### 不要用单个指针来传递数组

+ 这条规则的出现是为了解决一些未定义行为
+ 补救的方法也简单，使用STL中的容器，例如std::vector，并在函数体中检查容器的大小

### 为了库ABI的稳定，考虑使用PImpI惯用法

+ 应用程序二进制接口(ABI)是两个二进制程序模块间的接口
+ 借助PImpI惯用法，可以隔离类的用户和实现，从而避免重复编译。
+ PImpI是 pointer to implementation(指向实现的指针)的缩写，它指的是C++中的一种编程技巧：
  + 将实现细节放在另一个类中，从而将其从类中移除。而这个包含实现的细节的类是通过一个指针来访问的。
  + 这么做是因为私有数据成员会参与类的内存布局，而私有函数成员会参与重载决策。这些依赖意味着对成员实现细节的修改会导致所有类的用户都需要重新编译。
  + 持有指向实现的指针(PImpI)的类可将用户隔离在类实现的变化之外，而代价则是多了一次间接。

+ C++ PImpI编程技巧  详解
PImpl（Pointer to Implementation）是一种编程技巧，也称为“编译期实现”或“内部实现”，它的目的是将类的实现细节封装在一个单独的实现类中，从而减少头文件的依赖关系，提高代码的模块化性和可维护性。

### PImpl模式的实现步骤：

1. **声明外部接口：** 在类的头文件中声明类的公共接口，但将实际的成员变量和实现细节的声明放到一个内部类中。

    ```cpp
    // MyClass.h
    class MyClass {
    public:
        MyClass();
        ~MyClass();

        void publicMethod1();
        void publicMethod2();

    private:
        class Impl;  // 内部实现类的前向声明
        Impl* pImpl;  // 内部实现类的指针
    };
    ```

2. **定义实现类：** 在实现文件中定义内部实现类，并将实际的成员变量和函数实现放在这里。

    ```cpp
    // MyClass.cpp
    #include "MyClass.h"

    // 实现内部实现类
    class MyClass::Impl {
    public:
        void privateMethod1() {
            // 实现细节
        }

        void privateMethod2() {
            // 实现细节
        }

        // 成员变量
        int data;
    };

    // MyClass 构造函数
    MyClass::MyClass() : pImpl(new Impl()) {}

    // MyClass 析构函数
    MyClass::~MyClass() {
        delete pImpl;
    }

    // 公共方法的实现调用内部实现类的方法
    void MyClass::publicMethod1() {
        pImpl->privateMethod1();
    }

    void MyClass::publicMethod2() {
        pImpl->privateMethod2();
    }
    ```

### PImpl的优势：

1. **降低编译依赖：** 将实现细节从头文件中移除，降低了头文件的依赖关系。这样，当实现发生变化时，只有实现文件需要重新编译，而不会影响到调用方。

2. **隐藏实现细节：** 将实现细节放在内部实现类中，可以隐藏对类的具体实现的细节，只需要暴露公共接口给用户。

3. **减小编译时间：** 当头文件发生变化时，只有依赖头文件的文件需要重新编译，而不会触发整个项目的重新编译。

4. **改善二进制兼容性：** 通过将实现细节放在内部实现类中，可以减少对外部接口的更改，提高二进制兼容性。

5. **模块化设计：** 可以更容易地设计模块化的系统，每个模块只关注自己的接口和实现细节。

### 注意事项：

1. **内存管理：** 要确保在类的析构函数中正确释放内部实现类的内存，以防止内存泄漏。

2. **拷贝和赋值：** PImpl模式可能导致默认的拷贝构造函数和赋值运算符不再适用，需要自定义这些函数并确保正确处理内部实现类的拷贝和赋值。

3. **性能开销：** PImpl模式引入了指针和额外的间接层，可能会带来一些微小的性能开销，但通常在维护性和可读性上的优势远远超过了这些开销。

PImpl是一种强大的C++编程技巧，特别适用于大型项目和库的开发，有助于提高代码的模块化性和可维护性。

### 本章精华

+ 不要使用全局变量，它们会引入隐藏的依赖
+ 单例就是变相的全局变量
+ 接口，尤其是函数，应该表达出意图
+ 接口应当是强类型的，而且应该只有几个不容易弄混的参数
+ 不要按指针接收C数组，而应该使用std::span
+ 如果你想要将类的使用和实现分开，请使用PImpI惯用法

## 第四章 函数

+ 软件开发人员通过将复杂的任务划分为较小的单元来掌控复杂性。在处理完小单元后，他们把小单元放在一起来掌控复杂的任务。
+ 函数是一种典型的单元，也是程序的基本构件。

### 函数定义

+ 好软件的最重要原则是好名字。
+ 将有意义的操作打包成精心命名的函数
+ 一个函数应该执行单一的逻辑操作
+ 使函数保持简短

+ 当你无法为函数找到一个有意义的名称时，这充分说明你的函数执行不止一项逻辑操作，而且你的函数并不简短

### 如果函数有可能需要在编译期求值，就把它声明为 constexpr

+ constexpr函数是可能在编译期运行的函数。当你在常量表达式中调用constexpr函数时，或者当你要用一个constexpr变量来获取constexpr函数的结果时，它会在编译期运行。也可以用只能在运行其求值的参数来调用constexpr函。
+ constexpr函数是隐含內联的
+ 编译期求值的constexpr的结果通常会被系统标记为只读
+ 性能是constexpr函数的第一大好处；它的第二大好处是，编译期求值的constexpr函数是纯函数，因此constexpr函数是线程安全的
+ 最后，计算结果会在运行期作为只读存储区域中的常量来提供

### 如果你的函数必定不抛异常，就把它声明为noexcept

+ 通过将函数声明为noexcept，你减少了备选控制路径的数量；因此，noexcept对优化器来说是一个有价值的提示
+ 即使你的函数可以抛出异常，noexcept往往也合理。noexcept在这种情况下意味着：我不在乎异常。其原因可能是：你无法对异常作出反应。在这种情况下，系统处理异常的唯一办法是调用std::terminate()
+ 以下类型的函数永远不应该抛出异常：
  + 析构函数
  + swap函数
  + 移动操作和默认构造函数

### 优先使用纯函数

+ 纯函数是指在给定相同参数时总是返回相同结果的函数。这个属性也被称为引用透明性。纯函数的行为就像无限大的查找表
+ 非纯函数是指random()或者time()这样的函数，它们会在不同的调用中返回不同的结果。换句话说，与函数体之外的状态交互的函数是不纯的
+ 纯函数有一些非常有趣的属性
  + 孤立的测试
  + 孤立的验证或重构
  + 还存其结果
  + 被自动重排或者在其他线程上执行

+ 纯函数也常被称为数学函数。
+ constexpr函数在编译期求值时是纯的。模板元编程是一种嵌在命令式语言C++中的纯函数式语言

### 优先采用简单而约定俗成的信息传递方式

+ 数据的类型：
  + 拷贝开销低或者不可能拷贝构造： func(X)
  + 移动开销低：std::vector<T>, std::string
  + 移动开销中: std::array<std::vector>或者BigPOD(POD代表 Plain Old Data，简旧数据，意为一般的传统数据--没有析构函数，构造函数以及虚成员函数的类)
  + 移动开销未知: 模板
  + 移动开销高：BigPOD[]或者std::array<BigPOD>

+ 参数传递的方向
  + 入：输入参数
  + 入并保留拷贝：被调用者保留一份数据
  + 入并移入：参数处在所谓的被移动状态。被移动状态意味着它处于合法但未指定的状态。基本上，你在重新使用被移动的对象前必须对他进行初始化
  + 入/出：参数会被修改
  + 出：输出参数

### 对于入参，拷贝开销低的类型按值传递，其他类型则以const引用来传递

+ 默认情况下，输入值可以拷贝就拷贝。如果拷贝开销不低，就通过const引用来传入。
+ 经验法则：
  + 如果 sizeof(par) <= 2 * sizeof(void*)，则按值传递参数par
  + 如果 sizeof(par) > 2 * sizeof(void*)，则按const引用传递par

### 对于转发参数，要用TP&&来传递，并且只std::forward该参数

+ 有时你想转发参数par。这意味着你希望保持左值的左值性，以及右值的右值性，这样才能完美地转发参数，使它的语义不发生变化
+ 转发参数的典型用例是工厂函数，工厂函数通过调用某个用户指定对象的构造函数创建出该对象。你不知道参数是不是右值，也不知道构造函数需要多少个参数

在C++中，工厂函数是一种设计模式，它提供了一种创建对象的方式，使得在不暴露对象的具体实现细节的情况下能够创建对象。工厂函数通常用于创建类的实例，而不是直接调用类的构造函数。这有助于实现抽象和封装，同时提供了灵活性和可维护性。

以下是关于C++工厂函数的一些详解：

1. **定义**：
   工厂函数是一个函数，负责创建和返回类的实例。它通常是类的静态成员函数，或者是一个独立于类的函数。

   ```cpp
   class Product {
   public:
       virtual ~Product() {}
       virtual void doSomething() = 0;
   };

   class ConcreteProduct : public Product {
   public:
       void doSomething() override {
           // 具体产品的实现
       }
   };

   class Factory {
   public:
       static Product* createProduct() {
           return new ConcreteProduct();
       }
   };
   ```

2. **返回类型**：
   工厂函数通常返回一个指向基类（抽象类）的指针或引用，这样可以隐藏具体实现的细节，同时允许客户端代码通过基类接口使用对象。

3. **抽象类**：
   工厂函数通常用于创建抽象类的实例，这样可以根据需要选择合适的具体实现。在上面的例子中，`Product` 是抽象类，而 `ConcreteProduct` 是它的具体实现。

4. **灵活性**：
   工厂函数提供了一种动态创建对象的方式，允许在运行时根据条件或配置选择要创建的具体类型，从而提供更大的灵活性。

   ```cpp
   int main() {
       Product* product = Factory::createProduct();
       product->doSomething();
       delete product;

       return 0;
   }
   ```

5. **多态性**：
   通过返回基类指针，工厂函数支持多态性，允许通过基类接口调用具体类的方法。

6. **单例工厂**：
   工厂函数可以实现为单例，确保在应用程序中只存在一个工厂实例，从而确保对对象创建的全局控制。

   ```cpp
   class SingletonFactory {
   public:
       static SingletonFactory& getInstance() {
           static SingletonFactory instance;
           return instance;
       }

       Product* createProduct() {
           return new ConcreteProduct();
       }

   private:
       SingletonFactory() {}  // 私有构造函数，确保只能通过 getInstance() 访问
   };
   ```

总的来说，工厂函数是一种有用的设计模式，它提供了一种灵活、可扩展且易于维护的方式来创建对象，特别是在需要隐藏具体实现的情况下。

+ 三个点(省略号)表示形参包。我们将使用形参包的模板称为变参模板
+ 形参包的打包和解包
  + 当省略号在类型参数T1的左边时，参数包被打包；当省略号在右边时，参数包被解包
  + 返回语句 T(std::forward<T1>(t1)...)中的这种解包实质上意味着表达式std::forward<T1>(t1)被不断重复，直到形参表的所有参数都被消耗掉，并且会在每个子表达式之间加一个逗号
+ C++ 形参包 详解

在C++中，形参包（parameter pack）是C++11引入的一个特性，它允许你定义一个可以包含任意数量参数的函数或类模板。形参包的主要优势之一是在不知道参数数量的情况下，仍然能够编写通用的代码。

以下是有关C++形参包的详解：

1. **定义形参包**：
   形参包使用省略号 `...` 表示。它可以用在函数模板或类模板的参数列表中。

   ```cpp
   // 函数模板形参包的例子
   template <typename... Args>
   void myFunction(Args... args) {
       // 使用args...
   }
   ```

   在上面的例子中，`Args` 是一个模板参数包，而 `args` 是函数参数包。

2. **展开形参包**：
   通过使用展开操作符 `...`，可以在函数体内展开形参包，以便对每个参数执行相同的操作。

   ```cpp
   template <typename... Args>
   void printValues(Args... args) {
       (std::cout << ... << args) << '\n';  // 展开形参包，逐个输出参数
   }
   ```

   在上面的例子中，`(std::cout << ... << args)` 部分展开了形参包，逐个将参数传递给 `std::cout`。

3. **递归展开**：
   形参包可以用于递归展开，实现对每个参数的逐一处理。

   ```cpp
   template <typename T>
   void printSingleValue(const T& value) {
       std::cout << value << '\n';
   }

   template <typename T, typename... Args>
   void printValues(T first, Args... rest) {
       printSingleValue(first);    // 处理第一个参数
       printValues(rest...);       // 递归展开处理剩余参数
   }
   ```

   在上面的例子中，`printValues` 函数递归展开形参包，对每个参数调用 `printSingleValue` 函数。

4. **折叠表达式**：
   C++17 引入了折叠表达式，使得展开形参包更加简洁。

   ```cpp
   template <typename... Args>
   void printValues(Args... args) {
       (std::cout << ... << args) << '\n';  // 折叠表达式
   }
   ```

   折叠表达式使得对形参包的处理更加紧凑和易读。

5. **使用形参包的场景**：
   形参包通常在需要处理可变数量参数的通用函数或模板中使用，例如元组的操作、可变参数模板、泛型代码等。

形参包是C++中强大的工具，它为编写通用和灵活的代码提供了便利。在处理不定数量参数的场景中，形参包的使用可以显著提高代码的可读性和可维护性。

+ 转发与变参模板的结合是C++中典型的创建模式

### 对于 入-出 参数，使用非const的引用来传递

+ 这条规则把函数的设计意图传达给了调用法：该函数会修改它的参数

### 对于 出 的输出值，优先使用返回值而非输出参数

+ 用返回值就好，但是别用const，因为它不但没有附加价值，而且还会干扰移动语义

### 要返回多个 出 值，优先考虑返回结构体或者多元组

+ 当你向std::set中插入一个值时，成员函数insert的重载会返回一个std::pair，它由两部分组成：
  + 一个指向所插入元素的迭代器
  + 还有一个bool，如果插入成功，它会被设置为true

+ C++11中的std::tie和C++17中的结构化绑定是将两个值绑定到某变量的两种优雅方式
+ 结构化绑定
C++结构化绑定（Structured Bindings）是C++17引入的一项特性，它提供了一种方便的方式来将多个变量绑定到结构体、元组或其他类似的数据结构的成员上。结构化绑定的目的是简化对结构化数据的访问和处理。

在结构化绑定中，可以使用`auto`关键字和花括号来声明和初始化多个变量，这些变量会被绑定到结构体或元组的成员。这使得代码更加简洁和可读。

以下是结构化绑定的基本语法：

```cpp
#include <tuple>

int main() {
    // 示例：使用结构化绑定绑定元组的元素
    std::tuple<int, double, std::string> myTuple{42, 3.14, "Hello"};

    auto [a, b, c] = myTuple;  // 结构化绑定

    // 现在 a, b, c 分别是 myTuple 的元素
    // a = 42, b = 3.14, c = "Hello"

    return 0;
}
```

上述例子中，`auto [a, b, c]` 表示使用结构化绑定将`myTuple`中的元素绑定到变量`a`、`b`、`c`上。

另外，结构化绑定还可以用于对结构体成员的绑定，如下所示：

```cpp
struct Point {
    int x;
    int y;
};

int main() {
    Point p{10, 20};

    auto [px, py] = p;  // 结构化绑定

    // px = 10, py = 20

    return 0;
}
```

结构化绑定在循环中也非常有用，可以方便地遍历容器中的元素：

```cpp
#include <vector>

int main() {
    std::vector<std::pair<int, double>> vec{{1, 3.14}, {2, 6.28}, {3, 9.42}};

    for (const auto& [index, value] : vec) {
        // 使用结构化绑定遍历容器中的元素
        // index 和 value 分别绑定到 pair 的第一个和第二个元素
        // ...
    }

    return 0;
}
```

结构化绑定在C++中提供了一种更简洁、更灵活的方式来处理结构化数据，从而使代码更加清晰易读。这个特性的引入使得C++语言更具现代感和表达力。

### 参数传递： 所有权语义

+ func(value): 函数func自己有一份value的拷贝并且就是其所有者。func会自动释放该资源
+ func(pointer*)： func借用了资源，所以无权删除该资源。func在每次使用前都必须检查该指针是否为空指针
+ func(reference&)：func借用了资源。与指针不同，引用的值总是合法的
+ func(std::unique_ptr): func是资源的新所有者。func的调用方法显式地把资源的所有权传递给了被调用方。func会自动释放该资源
+ func(std::shared_ptr): func是资源的额外所有者。func会延长资源的生存期。在func结束时，它也会结束对资源的所有权。如果func是资源的最后一个所有者，那么它的结束会导致资源的释放

+ 在应用层面使用std::move的意图并不在于移动。在应用层面使用std::move的目的是所有权的转移

+ C++ 所有权语义 详解
C++的所有权语义指的是对于对象内存的所有权管理方式，即确定何时创建、拥有、传递和销毁对象。在C++中，主要有两种所有权语义，即值语义和引用语义。

1. **值语义（Value Semantics）**：
   - **对象拥有其值**：当使用值语义时，对象在栈上或作为成员变量直接存储其值。当对象复制时，新的对象独立拥有自己的值，不受原始对象的影响。
   - **拷贝构造函数和赋值运算符**：值类型对象通常需要定义拷贝构造函数和赋值运算符，以确保正确地复制对象的值。

   ```cpp
   class ValueSemanticsExample {
   public:
       ValueSemanticsExample(int val) : value(val) {}
       
       // 拷贝构造函数
       ValueSemanticsExample(const ValueSemanticsExample& other) : value(other.value) {}
       
       // 赋值运算符
       ValueSemanticsExample& operator=(const ValueSemanticsExample& other) {
           if (this != &other) {
               value = other.value;
           }
           return *this;
       }

   private:
       int value;
   };
   ```

2. **引用语义（Reference Semantics）**：
   - **对象拥有引用**：当使用引用语义时，对象本身并不存储值，而是存储对其他对象的引用。多个对象可以共享相同的值。
   - **拷贝构造函数和赋值运算符需小心**：引用类型对象通常需要小心处理拷贝构造函数和赋值运算符，以避免意外地共享底层资源。

   ```cpp
   class ReferenceSemanticsExample {
   public:
       ReferenceSemanticsExample(int& valRef) : valueReference(valRef) {}

   private:
       int& valueReference;
   };
   ```

在现代C++中，智能指针也提供了一种更灵活的所有权语义。智能指针允许在堆上动态分配内存，并通过引用计数等机制来管理内存的释放。`std::unique_ptr`提供了独占所有权，而`std::shared_ptr`允许多个指针共享同一块内存。

```cpp
#include <memory>

class SmartPointerExample {
public:
    SmartPointerExample(int val) : value(std::make_unique<int>(val)) {}

private:
    std::unique_ptr<int> value;
};
```

在选择值语义还是引用语义时，需要根据程序的需求和性能考虑。值语义通常更容易理解和使用，而引用语义可以更有效地共享资源，但需要小心管理共享状态，以避免潜在的问题。

### 返回 T* (仅仅)用于表示位置

+ 指针仅用于表示位置。这正是函数find的作用

+ 指针或引用永远不应该转移所有权

### 当不希望发生拷贝，也不需要表达 没有返回对象 时，应该返回 T&

+ 当不存在 没有返回对象 这种可能性的时候，就可以返回引用而非指针了
+ 有时你想进行链式操作，但是不详为不必要的临时对象进行拷贝和析构

+ 返回局部对象的引用(指针)是未定义行为。未定义行为本质上意味着，不要假想程序的行为

### 不要返回 T&&

### 不要返回 std::move(本地变量)

### main()的返回类型是 int

+ 依照C++标准,main函数有两种变体
  + int main() {...}
  + int main(int argc, char** argv[]) {...}

+ 第二个版本等效于 int main(int argc, char* argv[]) {...}
+ main函数并不需要返回语句。如果控制流到达main函数的末尾而没有碰到一条返回语句，其效果相当于执行 return 0; 这意味着程序的成功执行

### 当函数不适用时(需要捕获局部变量，或者编写一个局部函数)，请使用lambda表达式

+ 什么时候必须用lambda表达式，什么是否必须使用普通函数。这里有两条明显的理由
  + 如果可调用实体必须捕获局部变量或者它是在局部作用域内声明的，你就必须使用lambda函数
  + 如果可调用实体需要支持重载，那么应该使用普通函数

## 在局部使用(包括要传递给算法)的lambda表达式中，优先通过引用来捕获

## 在非局部使用(包括要被返回，存储在堆上或者要传递给其他线程)的lambda表达式中，避免通过引用来捕获

+ 这两条规则高度关联，它们可以归结为： lambda表达式应该只对有效数据进行操作。
  + 当lambda通过拷贝捕获数据时，根据定义，数据总是有效的
  + 当lambda通过引用捕获数据时，数据的生存期必须超过lambda的生存期

### 在有选择的情况下优先采用默认参数而非重载

+ 如果你需要用不同数量的参数来调用一个函数，尽可能优先采用默认参数而不是重载。这样你就遵循了DRY(不要重复自己)原则

### 不要使用 va_arg 参数

+ 当你的函数需要接受任意数量的参数时，要使用变参模板而不是va_arg参数

+ 变参数函数(variadic function)是像std::printf这样的函数，可以接受任意数量的参数。
+ 问题是，必须假设传递的类型是正确的。当然这种假设非常容易出错，其正确性依赖于程序员的素养

+ va_arg宏的背景信息
  + va_list : 保存下列宏的必要信息
  + va_start : 启用对变参数函数参数的访问
  + va_arg : 访问下一个变参数函数的参数
  + va_end : 结束对变参数函数参数的访问
+ C++ va_arg 变参数函数参数 详解
`va_arg` 是C语言中用于处理可变参数函数（变参函数）的宏，它允许函数接受可变数量的参数。在C++中，虽然不鼓励使用C风格的可变参数函数，但仍然支持这一特性。

以下是关于`va_arg`的详解：

1. **头文件**：
   使用 `va_arg` 需要包含 `<cstdarg>` 头文件，其中定义了一组宏和类型，用于处理可变参数函数。

   ```cpp
   #include <cstdarg>
   ```

2. **可变参数函数的声明和定义**：
   可变参数函数通常以省略号 `...` 结尾，其中包含不定数量的参数。`va_list` 类型用于存储参数列表。

   ```cpp
   #include <cstdarg>
   #include <iostream>

   void myVarArgsFunction(int num, ...) {
       va_list args;
       va_start(args, num);

       for (int i = 0; i < num; ++i) {
           int value = va_arg(args, int);
           std::cout << "Argument " << i + 1 << ": " << value << std::endl;
       }

       va_end(args);
   }
   ```

   在上面的例子中，`myVarArgsFunction` 接受一个整数参数 `num`，表示后续可变参数的数量。函数通过 `va_arg` 从参数列表中获取具体的参数值。

3. **`va_start` 和 `va_end`**：
   在使用 `va_arg` 之前，需要使用 `va_start` 宏初始化 `va_list` 对象，以及在函数结束时使用 `va_end` 宏清理资源。

   ```cpp
   void myVarArgsFunction(int num, ...) {
       va_list args;
       va_start(args, num);

       // ...

       va_end(args);
   }
   ```

4. **注意事项**：
   - 参数传递的方式对使用 `va_arg` 很重要。对于整数、指针等基本类型，`va_arg` 可以很好地工作。但对于复杂的用户自定义类型，需要谨慎处理。
   - 没有可变参数的方式获取参数数量，需要依赖固定参数来传递数量信息。
   - 使用 `va_arg` 时，需要清楚每个参数的类型，以避免类型不匹配的问题。

5. **C++ 中的替代方案**：
   在现代C++中，推荐使用模板和标准库中的可变参数模板（variadic templates）来代替传统的可变参数函数。这种方式更类型安全，更灵活。

   ```cpp
   #include <iostream>

   template <typename... Args>
   void myVarArgsFunction(Args... args) {
       (std::cout << ... << args) << std::endl;
   }

   int main() {
       myVarArgsFunction(1, "Hello", 3.14);
       return 0;
   }
   ```

   在上面的例子中，使用可变参数模板实现了类似的功能，同时获得了更好的类型安全性。

+ 这些问题可以通过C++17的折叠表达式轻松解决。跟va_arg相比，折叠表达式会自动推导出其参数的数量和类型
+ 变参模板可以接受任意数量的参数。这些任意数量的参数由所谓的参数包持有，用省略号表示。
+ 此外，在C++17中，可以用二元运算符直接对参数包进行归约。这一针对变参模板的增强被称为折叠表达式

### 本章精华

+ 一个函数应该执行一个操作，要简短，并有一个精心选择的名字
+ 要把可以在编译期运行的函数实现为constexpr
+ 如果可能的话，将你的函数实现为纯函数
+ 区分一个函数的入，入/出和出参。对入参使用按值传递或者按const引用传递，对入/出参数使用按引用传递，对出参使用按值传递
+ 向函数传递参数涉及所有权语义的问题。按值传递使函数成为资源的独立所有者。按指针或引用传递意味着函数值是借用了该资源。std::unique_ptr将所有权转移给函数,std::shared_ptr则使函数称为共享的所有者
+ 当你的函数需要接受任意数量的参数时，要使用变参模板而不是va_arg参数

## 第五章 类和类层次结构

+ 类是一种用户定义类型，程序员可以为其指定表示方法，操作和接口。
+ 类的层次结构被用来组织相关的结构

+ Guidelines先给出了一些概要规则：
  + 具体类型
  + 构造函数，赋值和析构函数
  + 类的层次结构
  + 重载和运算符重载
  + 联合体

### class(类)和struct(结构体)之间的语法差异

+ 在结构体中，所有成员默认为 public(公开)。在类中，所有成员默认 private(私有)
+ 继承的情况也是如此。结构体的基类默认为 public，类的基类默认为 private

### 把相关的数据组织到结构(struct或class)中

+ 通过将相关元素放在结构体中，函数签名变得可以自我描述。

### 当类具有不变式时使用class；如果数据成员可以独立变化，则使用struct

+ 类的不变式是用于约束类的实例的不变式。成员函数必须使这个不变式保持成立。不变式约束了类的实例的可能取值。
+ C++ 类中的不变式是什么意思
  + 在C++中，类的不变式（invariant）指的是在类的对象上始终保持成立的条件或属性。这是一种约定或规则，用于确保对象的有效性和一致性。在面向对象编程中，不变式是类设计的一部分，用于描述对象应该具有的状态。
  + 不变式通常与类的公共接口和方法一起工作，确保在对象上执行操作时，类的内部状态不会违反这些不变式。不变式可以看作是类内部约定的一部分，旨在维护对象的有效性。
  + 例如，考虑一个表示时间的类，该类有小时和分钟两个成员变量。一个可能的不变式是，小时应该在0到23之间，分钟应该在0到59之间。在类的方法中，如果有任何操作可能破坏这个不变式，需要在方法执行前或执行后重新确保不变式的成立。

+ 类的不变式在构造函数中被初始化和检查

### 在类中体现出接口和实现之间的区别

+ 类的公开成员函数是类的接口，私有部分则是实现

### 仅当函数需要直接访问类的内部表示时，才把它变成成员

+ 如果一个函数不需要访问类的内部结构，它就不应该是成员。这样的话，你会得到松耦合，而类的内部结构的改变不会影响辅助函数

+ 运算符 =, (), [] 和 -> 必须是类的成员

### 将辅助函数与它们支持的类放在同一个命名空间中

+ 辅助函数应该在类的命名空间中，因为它是类的接口的一部分。与成员函数相反，辅助函数不需要直接访问类的内部表示。

### 不要在一条语句里定义类或者枚举的同时声明该类型的变量

+ 如果在一条语句里定义类或者枚举同时声明其类型的变量，会引起混淆，因此应该避免

### 如有任何非公开成员，就使用class，而不是struct

### 尽量减少成员的暴露

+ 数据隐藏和封装是面向对象类设计的基石之一:你将类中的成员封装起来，只允许通过公共成员函数进行访问。
+ 你的类可能有两种接口
  + 一种是用于外部的 public 接口
  + 一种是用于派生类的 protected接口。
+ 其余成员都应该属于 private

### 具体类型

+ 具体类型是 最简单的一种类。它常常被称作为值类型，不属于某个类型层次结构的一部分
+ 规范类型是一种 行为类似于int 的类型，因此，它必须支持拷贝和赋值，相等比较，以及可交换。更正式的说法是，一个规范类型X行为上像int，支持下列操作
  + 默认构造: X()
  + 拷贝构造: X(const X&)
  + 拷贝赋值: operator = (const X&)
  + 移动构造: X(X&&)
  + 移动赋值: operator = (X&&)
  + 析构: ~X()
  + 交换操作: swap(X&, X&)
  + 相等运算符: operator == (const X&, const X&)

### 优先使用具体类型而不是类层次结构

+ 如果没有需要类层次结构的用例，就使用具体类型。具体的类型更容易实现，更小且更快。
+ 不必担心继承，虚性，引用或指针，包括内存分配和释放。不会有虚派发，因此也没有运行期的开销

### 让具体类型规范化

+ 如果你有一个具体类型，可以考虑将它升级为规范类型
+ 内置类型(例如int或者double)是规范类型，而用户定义类型(例如std::string)或容器(std::vector, std::unordered_map)也是如此

### 构造函数 ，赋值函数和析构函数

+ 六个特殊的成员函数，它们控制着对象的生命周期
  + 默认构造函数: X()
  + 拷贝构造函数: X(const X&)
  + 拷贝赋值函数: operator = (const X&)
  + 移动构造函数: X(X&&)
  + 移动赋值函数: operator = (X&&)
  + 析构函数: ~X()

+ 编译期可以为这 六大 生成默认实现，但是也可以明确用 =default(预置) 来要求编译提供它们，或者使用 =delete(预置) 来删除它们
+ 默认构造函数可以在没有参数的情况下被调用，但是它可能每个参数都有默认值

### 如果能避免定义默认操作，那就这么做

+ 这一规则也被称为 零法则。这意味着你可以通过使用有合适的拷贝/移动语义类型，来避免自行编写构造函数，拷贝/移动构造函数，赋值运算符或者析构函数。
+ 有合适的拷贝/移动语义的类型包括规范类型，例如内置类型bool或者double，也包括标准模板库(STL)的容器，例如std::vector或者std::string

+ 当编译器为一个类自动生成拷贝构造函数时，它调用该类的所有成员和所有基类的拷贝构造函数

### 如果定义或 =delete 了任何默认操作，就对所有默认操作都进行定义或 =delete

+ 六大 是紧密相关的。由于这种关系，你应该对所有特殊成员函数进行定义或者 =delete