## 简介

+ C++ 惯用写法

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