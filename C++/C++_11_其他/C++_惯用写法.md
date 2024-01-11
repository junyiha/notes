## 简介

+ C++ 惯用写法

## RAII

+ RAII可能是C++中最常用的编程技法.他的思想是把资源映射到对象,根据这些对象的作用域自动管理它们的生命周期
+ 例如，如果在堆上打开一个文件句柄，那么一旦我们从函数返回（或循环，或任何它在内部声明的作用域）时，它都应该被隐式关闭。
+ 如果类的成员中有动态内存分配，那么当该类实例被销毁时，相关内存应该被隐式释放。

+ 每一种资源-内存分配,文件句柄,数据库连接,套接字和任何其他需要获取和释放的资源  都应该包装在这样一个RAII类中,其声明周期由它的对象所在的作用域决定,和RAII类对象绑定.
+ C++语言会保证,当对象超出作用域时,析构函数被调用,不管对象如何离开该作用域.即使抛出异常,所有相关对象也将超出作用域,所以他们的相关资源都会被释放.

+ C++很多地方都用到了RAII特性,例如lock_guard, 智能指针等.

## 使用enum class 而非 enum

+ enum class 最重要的好处是: 防止隐式转换

## Copy-and-swap

+ copy-and-swap 技法保证了强异常安全的保证,它可以非常方便的实现operator=
```cpp
class String
{
    char * str;
public:
    String & operator = (String s) // the pass-by-value parameter serves as a temporary
    {
       s.swap (*this); // Non-throwing swap
       return *this;
    }// Old resources released when destructor of s is called.

    void swap(String & s) noexcept // Also see non-throwing swap idiom
{
        std::swap(this->str, s.str);
    }
};
```

+ 补充知识点,异常安全的四种保证
  + Nothrow(或者nofail)异常保证: 该函数永远不会抛出异常.对于可能在堆栈展开期间被调用的析构函数和其他函数,期望它们不会抛出异常(错误通过其他方式报告或隐藏).析构函数默认情况下是noexcept的(自C++11起).Nofail(函数总是成功执行)的要求适用于交换(swaps),移动构造函数和其他被那些提供强异常保证的函数所使用的函数.
  + 强异常保证: 如果该函数抛出异常,程序的状态将回滚到函数调用之前的状态(例如 std::vector::push_back).即使抛出异常,程序仍然处于有效状态.
  + 基本异常保证: 如果该函数抛出异常,程序仍然处于有效状态,没有资源泄漏,所有对象的不变性仍然保持完整.
  + 无异常保证: 如果该函数抛出异常,程序可能处于无效状态,可能会发生资源泄漏,内存损坏或其他破坏不变性的错误.

## CRTP: Curiously Recurring Template Pattern

+ CRTP 是指将一个类作为模板参数传递给其基类的情况
```cpp

template<class Derived>
struct BaseCRTP {};

struct Example : BaseCRTP<Example> {};
```

+ 在基类中,通过进行类型转换(可以使用static_cast或dynamic_cast)可以获取派生类实例,包括派生类型
```cpp

template<class Derived>
struct BaseCRTP {
  void call_foo() {
    Derived& self = *static_cast<Derived*>(this);
    self.foo();
  }
};

struct Example : BaseCRTP<Example> {
  void foo() { cout << "foo()\\n"; }
};
```

## PIMPL 模式

+ 简介
  + 很实用的一种基础模式

+ PIMPL 解释：
  + PIMPL（Private Implementation 或 Pointer to Implementation）是通过一个私有的成员指针，将指针所指向的类的内部实现数据进行隐藏。

+ 示例：
```cpp
//x.h
class X
{
public:
    void Fun();
private:
    int i; //add int i;
};

//c.h
#include <x.h>
class C
{
public:
    void Fun();
private:
    X x; //与X的强耦合
};

PIMPL做法：
//c.h
class X; //代替#include <x.h>
class C
{
public:
    void Fun();
private:
    X *pImpl; //pimpl
};
```
+ 降低模块的耦合。因为隐藏了类的实现，被隐藏的类相当于原类不可见，对隐藏的类进行修改，不需要重新编译原类。
+ 降低编译依赖，提高编译速度。指针的大小为（32位）或8（64位），X发生变化，指针大小却不会改变，文件c.h也不需要重编+ 
+ 接口与实现分离，提高接口的稳定性。
  + 通过指针封装，当定义“new C”或"C c1"时 ,编译器生成的代码中不会掺杂X的任何信息。
  + 当使用C时，使用的是C的接口（C接口里面操作的类其实是pImpl成员指向的X对象），与X无关，X被通过指针封装彻底的与实现分离。
```cpp
//c.cpp
C::C()pImpl(new X())
{
}

C::~C()
{
     delete pImpl;
     pImpl = NULL;
}

void C::Fun()
{
    pImpl->Fun();
}

//main
#include <c.h>
int main()
{
    C c1;
    c1.Fun();
    return 0;
}
```