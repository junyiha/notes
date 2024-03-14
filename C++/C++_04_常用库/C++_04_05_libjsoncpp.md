## 简介

+ libjsoncpp库

## C++ libjsoncpp库 详解

libjsoncpp 是一个用于处理 JSON 数据的 C++ 库。它提供了一组功能强大的 API，使得在 C++ 应用程序中解析、生成和操作 JSON 数据变得简单而高效。

以下是关于 libjsoncpp 的详解：

1. **JSON 数据处理**：libjsoncpp 提供了一套 API，使得在 C++ 应用程序中处理 JSON 数据变得简单。它可以解析 JSON 字符串，将 JSON 对象转换为 C++ 对象，以及将 C++ 对象转换为 JSON 字符串。

2. **易于使用**：libjsoncpp 的 API 设计简单直观，易于理解和使用。它提供了类似于标准容器的接口，使得对 JSON 对象进行操作就像操作标准容器一样方便。

3. **跨平台性**：libjsoncpp 可以在各种平台上运行，包括 Windows、Linux、macOS 等。这使得它适用于各种不同的开发环境和应用场景。

4. **开源**：libjsoncpp 是开源的，采用 MIT 许可证。这意味着您可以自由地使用、修改和分发该库，而无需担心版权问题。

5. **高性能**：libjsoncpp 在设计上注重了性能，并且采用了一些优化策略来提高解析和生成 JSON 数据的速度。这使得它在处理大量 JSON 数据时表现出色。

6. **灵活性**：libjsoncpp 提供了丰富的功能，可以满足不同应用场景的需求。您可以使用它来处理各种类型的 JSON 数据，包括简单的键值对、嵌套对象、数组等等。

7. **与标准库兼容**：libjsoncpp 的设计与 C++ 标准库兼容，并且尽量遵循 C++ 的最佳实践和惯例。这使得它可以与其他 C++ 库和框架无缝集成。

8. **持续维护**：libjsoncpp 是一个活跃维护的项目，开发团队不断更新和改进库的功能，并及时修复可能存在的 bug 和问题。

总的来说，libjsoncpp 是一个功能强大、易于使用、高性能的 C++ JSON 库，适用于各种类型的 C++ 应用程序，包括网络服务、移动应用、游戏开发等。

## jsoncpp

### json 概述

+ JSON(`JavaScript Object Notation`, JavaScript 对象表示法) 是一种轻量级的数据交换格式。 
+ JSON是存储和交换文本信息的语法，类似于XML。但它比XML更小，更快，更易解析，易于人阅读和编写。同时也易于机器解析和生成。 
+ 它基于`JavaScript Programming Language, Standard ECMA-262 3rd Edition - December 1999`的一个子集。 
+ JSON采用完全独立于语言的文本格式，但是也使用了类似于C语言家族的习惯（包括`C, C++, C#, Java, JavaScript, Perl, Python`等）。 
+ 这些特性使JSON成为理想的数据交换语言

+ 要明白，JSON 是一种轻量级的文本数据交换格式而非编程语言，其语法只支持字符串，数值，布尔值及null以及在此基础上的对象和数组，

+ JSON建构于两种结构：
  + “名称/值”对的集合（`A collection of name/value pairs`）,不同的语言中，它被理解为对象（`object`），纪录（`record`），结构（`struct`），字典（`dictionary`），哈希表（`hash table`），有键列表（`keyed list`），或者关联数组 （`associative array`）。
  + 值的有序列表（An ordered list of values）,在大部分语言中，它被理解为数组（`array`）

+ JSON具有以下这些形式：
  + 对象是一个无序的“‘名称/值’对”集合。一个对象以“{”（左括号）开始，“}”（右括号）结束。每个“名称”后跟一个“:”（冒号）；“‘名称/值’ 对”之间使用“,”（逗号）分隔

#### JSON语法规则

+ 数据在 名称/值对 里面
+ 数据由逗号分隔
+ 大括号保存对象
+ 中括号保存数组

+ JSON名称/值对
  + JSON 数据的书写格式是：名称/值对
  + 名称/值对 包括字段名称（在双引号中），后面写一个冒号，然后是值： `"name":"hello world"`
+ JSON名称（键）必须是字符串
+ JSON值可以是：
  + 数字（整数或浮点数）
  + 字符串（在双引号中）
  + 逻辑值（true 或 false）
  + 数组（在中括号中）
  + 对象（在大括号中）
  + null

+ JSON对象
  + JSON 对象在大括号（{}）中书写
  + 对象可以包含多个名称/值对：   `{"name":"hello world", "url":"www"}`

+ JSON数组
  + JSON 数组在中括号中书写
  + 数组可包含多个对象：`"sites":[{"name":"hello", "url":"www"}, {"name":"world", "url":"www"}]`
    + 对象sites是包含两个对象的数组，每个对象代表一条关于网站(name, url)的记录

+ 访问对象值
  + 可以使用点号来访问对象的值`var myobj,x; myobj = {"name":"json", "alex":1111, "site":"www"}; x = myobj.name;`
  + 可以使用中括号来访问对象的值`var myobj,x; myobj = {"name":"json", "alex":1111, "site":"www"}; x = myobj["name"];`

#### JSON.parse()

+ JSON通常用于与服务端交换数据
+ 在接收服务器数据时，一般是字符串，可以使用JSON.parse()方法将数据交换为JavaScript对象

+ 语法：`JSON.parse(text, reviver);`
+ 参数说明：
  + `text`  -- 一个有效的JSON字符串
  + `reviver` -- 一个转换结果的函数，将为对象的每个成员调用此函数

#### JSON.stringify()

+ JSON 通常用于与服务端交换数据。
+ 在向服务器发送数据时一般是字符串。
+ 我们可以使用 JSON.stringify() 方法将 JavaScript 对象转换为字符串。

+ 语法：`JSON.stringify(value[, replacer[, space]])`
+ 参数说明：
  + `value`  --  要转换的 JavaScript 值（通常为对象或数组）。
  + `replacer` -- 用于转换结果的函数或数组
  + `space`  --  文本添加缩进、空格和换行符

### jsoncpp 详解

+ 开源程序：`libjsoncpp`
+ 地址：`https://github.com/open-source-parsers/jsoncpp`

+ 将仓库克隆到本地，cmake编译完成之后，当做第三方库的方式为：
  + 头文件：jsoncpp/include/json
  + 静态库和动态库文件：build/lib/

### jsoncpp 基本用法

+ jsonCpp主要包含三种类型的`class`：`value`、`reader`、`write`。
+ jsonCpp总所有对象、类名都在namespace json中

+ `Json::Value`
  + Json::Value时jsonCpp中最基本、最重要的类，用于表示各种类型的对象，jsoncpp 支持的对象类型可见 `Json::ValueType` 枚举值。
  + 在把value插入值后再输出来，输出的值是按字母表的顺序排列。
    + `Json::Value root;`
    + `root["status"] = 1;			//新建一个key为status，赋予数值1`
    + `root["message"] = "OK";		//新建一个key为message，赋予字符串OK`
    + `root["array"].append("arr"); //新建一个key为array，类型为数组，对第一个元素赋值为字符串“arr”`
    + `root["array"].append(1234);  // 为数组 key_array 赋值，对第二个元素赋值为：1234。`
    + `Json::ValueType type = root.type();	//获得root的类型`

+ `Json::Writer`
  + `Json::Writer`负责将内存中的`Value`对象转换成`JSON`文档，输出到文件或者是字符串中
  + Json::Writer是一个纯虚类，不能直接使用，一般使用`Json::Writer`的子类：`Json::FasterWriter`, `Json::StyledWriter`、`Json::StyledStreamWriter`
  + 注：在新版中`Json::FasterWriter`, `Json::StyledWriter`、`Json::Reader`都被弃用，替代的是`Json::StreamWriterBuilder`、`Json::CharReaderBuilder`
    + `Json::FasterWriter`：速度最快
    + `Json::StyledWriter`：格式化后的json

+ `Json::Reader`
  + 用于读取，准确说是用于将字符串或者文件输入流转换为Json::Value对象的
  + `parse()`
  + 使用`Json::Reader`对`json`文件进行解析
    + 声明：`bool parse(const std::string& document, Value& root, bool collectComments = true);`
    + 参数：
      + `root`:（输出）Json::Value的对象
  + 使用Json::Reader对json输入流（文件）进行解析
    + 声明：`bool parse(std:stream& is, Value& root, bool collectComment = true);`
  + 使用Json::Reader对字符串进行解析
    + 声明：`bool parse(const char* beginDoc, const char* ednDoc, Value& root, bool collectComment = true);`

### JsonCpp其他操作

+ 判断key是否存在
  + 声明：`bool Json::Value::isMember ( const char * key) const；`
  + 存在返回1，否则返回0

+ 判断是否为null成员函数
+ 注：Json::Value和C++中的map有一个共同的特点，就是当你尝试访问一个不存在的 key 时，会自动生成这样一个key-value默认为null的值对。

+ 得到所有成员
  + `typedef std::vectorstd::string Json::Value::Members;`
  + `Value::Members Json::Value::getMemberNames ( ) const;`
  + 该函数的类型为一个string的vector。

+ 删除成员
  + `Value Json::Value::removeMember( const char* key)`
  + 返回删除的值，或者null
