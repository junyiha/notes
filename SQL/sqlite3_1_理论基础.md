## 简介

+ sqlite3 理论知识相关笔记

## SQLite 简介

+ SQLite是一个软件库，实现了自给自足的、无服务器的、零配置的、事务性的 SQL 数据库引擎。SQLite是一个增长最快的数据库引擎，这是在普及方面的增长，与它的尺寸大小无关。SQLite 源代码不受版权限制
  
+ 什么是SQLite
  + SQLite是一个进程内的库，实现了自给自足的、无服务器的、零配置的、事务性的 SQL 数据库引擎。它是一个零配置的数据库，这意味着与其他数据库不一样，您不需要在系统中配置。
  + 就像其他数据库，SQLite 引擎不是一个独立的进程，可以按应用程序需求进行静态或动态连接。SQLite 直接访问其存储文件

+ 为什么要用SQLite
  + 不需要一个单独的服务器进程或操作的系统（无服务器的）。
  + SQLite 不需要配置，这意味着不需要安装或管理。
  + 一个完整的 SQLite 数据库是存储在一个单一的跨平台的磁盘文件。
  + SQLite 是非常小的，是轻量级的，完全配置时小于 400KiB，省略可选功能配置时小于250KiB。
  + SQLite 是自给自足的，这意味着不需要任何外部的依赖。
  + SQLite 事务是完全兼容 ACID 的，允许从多个进程或线程安全访问。
  + SQLite 支持 SQL92（SQL2）标准的大多数查询语言的功能。
  + SQLite 使用 ANSI-C 编写的，并提供了简单和易于使用的 API。
  + SQLite 可在 UNIX（Linux, Mac OS-X, Android, iOS）和 Windows（Win32, WinCE, WinRT）中运行。

+ SQLite 命令
  + 与关系数据库进行交互的标准 SQLite 命令类似于 SQL。命令包括 CREATE、SELECT、INSERT、UPDATE、DELETE 和 DROP。这些命令基于它们的操作性质可分为以下几种：
  + DDL - 数据定义语言
    + CREATE : 创建一个新的表，一个表的视图，或者数据库中的其他对象。
    + ALERT  : 修改数据库中的某个已有的数据库对象，比如一个表。
    + DROP   : 删除整个表，或者表的视图，或者数据库中的其他对象。
  + DML - 数据操作语言
    + INSERT : 创建一条记录
    + UPDATE : 修改记录
    + DELETE : 删除记录
  + DQL - 数据查询语言
    + SELECT : 从一个或多个表中检索某些记录

## SQLite 命令

+ 本章将向您讲解 SQLite 编程人员所使用的简单却有用的命令。这些命令被称为 SQLite 的点命令，这些命令的不同之处在于它们不以分号 ; 结束。
+ 如需获取可用的点命令的清单，可以在任何时候输入 ".help"。例如：
  + sqlite>.help
+ .backup ?DB? FILE	
  + 备份 DB 数据库（默认是 "main"）到 FILE 文件。
+ .bail ON|
  + OFF	
  + 发生错误后停止。默认为 OFF。
+ .databases	
  + 列出数据库的名称及其所依附的文件。
+ .dump ?TABLE?	
  + 以 SQL 文本格式转储数据库。如果指定了 TABLE 表，则只转储匹配 LIKE 模式的 TABLE 表。
+ .echo ON|OFF	
  + 开启或关闭 echo 命令。
+ .exit	
  + 退出 SQLite 提示符。
+ .explain ON|OFF	
  + 开启或关闭适合于 EXPLAIN 的输出模式。如果没有带参数，则为 EXPLAIN on，即开启 EXPLAIN。
+ .header(s) ON|OFF	
  + 开启或关闭头部显示。
+ .help	
  + 显示消息。
+ .import FILE TABLE	
  + 导入来自 FILE 文件的数据到 TABLE 表中。
+ .indices ?TABLE?	
  + 显示所有索引的名称。如果指定了 TABLE 表，则只显示匹配 LIKE 模式的 TABLE 表的索引。
+ .load FILE ?ENTRY?	
  + 加载一个扩展库。
+ .log FILE|off	
  + 开启或关闭日志。FILE 文件可以是 stderr（标准错误）/stdout（标准输出）。
+ .mode MODE	
  + 设置输出模式，MODE 可以是下列之一：
    + csv 逗号分隔的值
    + column 左对齐的列
    + html HTML 的 <table> 代码
    + insert TABLE 表的 SQL 插入（insert）语句
    + line 每行一个值
    + list 由 .separator 字符串分隔的值
    + tabs 由 Tab 分隔的值
    + tcl TCL 列表元素
+ .nullvalue STRING	
  + 在 NULL 值的地方输出 STRING 字符串。
+ .output FILENAME	
  + 发送输出到 FILENAME 文件。
+ .output stdout	
  + 发送输出到屏幕。
+ .print STRING...	
  + 逐字地输出 STRING 字符串。
+ .prompt MAIN CONTINUE	
  + 替换标准提示符。
+ .quit	
  + 退出 SQLite 提示符。
+ .read FILENAME	
  + 执行 FILENAME 文件中的 SQL。
+ .schema ?TABLE?	
  + 显示 CREATE 语句。如果指定了 TABLE 表，则只显示匹配 LIKE 模式的 TABLE 表。
+ .separator STRING	
  + 改变输出模式和 .import 所使用的分隔符。
+ .show	
  + 显示各种设置的当前值。
+ .stats ON|OFF	
  + 开启或关闭统计。
+ .tables ?PATTERN?	
  + 列出匹配 LIKE 模式的表的名称。
+ .timeout MS	
  + 尝试打开锁定的表 MS 毫秒。
+ .width NUM NUM	
  + 为 "column" 模式设置列宽度。
+ .timer ON|OFF	
  + 开启或关闭 CPU 定时器。

## SQLite 语法

+ SQLite 是遵循一套独特的称为语法的规则和准则。

+ 大小写敏感性
  + 有个重要的点值得注意，SQLite 是不区分大小写的，但也有一些命令是大小写敏感的，比如 GLOB 和 glob 在 SQLite 的语句中有不同的含义。

+ 注释
  + SQLite 注释是附加的注释，可以在 SQLite 代码中添加注释以增加其可读性，他们可以出现在任何空白处，包括在表达式内和其他 SQL 语句的中间，但它们不能嵌套。
  + SQL 注释以两个连续的 "-" 字符（ASCII 0x2d）开始，并扩展至下一个换行符（ASCII 0x0a）或直到输入结束，以先到者为准。
  + 您也可以使用 C 风格的注释，以 "/*" 开始，并扩展至下一个 "*/" 字符对或直到输入结束，以先到者为准。SQLite的注释可以跨越多行。
  + sqlite>.help -- 这是一个简单的注释

+ SQLite 语句
  + 所有的 SQLite 语句可以以任何关键字开始，如 SELECT、INSERT、UPDATE、DELETE、ALTER、DROP 等，所有的语句以分号 ; 结束。

## SQLite 数据类型

+ SQLite 数据类型是一个用来指定任何对象的数据类型的属性。SQLite 中的每一列，每个变量和表达式都有相关的数据类型。
+ 您可以在创建表的同时使用这些数据类型。SQLite 使用一个更普遍的动态类型系统。在 SQLite 中，值的数据类型与值本身是相关的，而不是与它的容器相关。

+ SQLite存储类
  + 每个存储在 SQLite 数据库中的值都具有以下存储类之一：
  + NULL	: 值是一个 NULL 值。
  + INTEGER	: 值是一个带符号的整数，根据值的大小存储在 1、2、3、4、6 或 8 字节中。
  + REAL	: 值是一个浮点值，存储为 8 字节的 IEEE 浮点数字。
  + TEXT	: 值是一个文本字符串，使用数据库编码（UTF-8、UTF-16BE 或 UTF-16LE）存储。
  + BLOB	: 值是一个 blob 数据，完全根据它的输入存储。

+ Date与Time数据类型
  + SQLite 没有一个单独的用于存储日期和/或时间的存储类，但 SQLite 能够把日期和时间存储为 TEXT、REAL 或 INTEGER 值。
  + TEXT	: 格式为 "YYYY-MM-DD HH:MM:SS.SSS" 的日期。
  + REAL	: 从公元前 4714 年 11 月 24 日格林尼治时间的正午开始算起的天数。
  + INTEGER	: 从 1970-01-01 00:00:00 UTC 算起的秒数。
  + 您可以以任何上述格式来存储日期和时间，并且可以使用内置的日期和时间函数来自由转换不同格式。

## SQLite 创建数据库

+ SQLite 的 sqlite3 命令被用来创建新的 SQLite 数据库。您不需要任何特殊的权限即可创建一个数据。

+ 语法
  + sqlite3 命令的基本语法如下：
    + `$ sqlite3 DatabaseName.db`
  + 通常情况下，数据库名称在 RDBMS 内应该是唯一的。
  + 另外我们也可以使用 .open 来建立新的数据库文件：
    + `sqlite>.open test.db`
  + 上面的命令创建了数据库文件 test.db，位于 sqlite3 命令同一目录下。
  + 打开已存在数据库也是用 .open 命令，以上命令如果 test.db 存在则直接会打开，不存在就创建它。

+ .dump 命令
  + 您可以在命令提示符中使用 SQLite .dump 点命令来导出完整的数据库在一个文本文件中，如下所示：
    + `$sqlite3 testDB.db .dump > testDB.sql`
  + 上面的命令将转换整个 testDB.db 数据库的内容到 SQLite 的语句中，并将其转储到 ASCII 文本文件 testDB.sql 中。您可以通过简单的方式从生成的 testDB.sql 恢复，如下所示：
    + `$sqlite3 testDB.db < testDB.sql`
  + 此时的数据库是空的，一旦数据库中有表和数据，您可以尝试上述两个程序。

## SQLite 附加数据库

+ 假设这样一种情况，当在同一时间有多个数据库可用，您想使用其中的任何一个。SQLite 的 ATTACH DATABASE 语句是用来选择一个特定的数据库，使用该命令后，所有的 SQLite 语句将在附加的数据库下执行。

+ 语法
  + SQLite 的 ATTACH DATABASE 语句的基本语法如下：
    + `ATTACH DATABASE file_name AS database_name;`
  + 如果数据库尚未被创建，上面的命令将创建一个数据库，如果数据库已存在，则把数据库文件名称与逻辑数据库 'Alias-Name' 绑定在一起。
  + 打开的数据库和使用 ATTACH附加进来的数据库的必须位于同一文件夹下。

+ 实例
  + 如果想附加一个现有的数据库 testDB.db，则 ATTACH DATABASE 语句将如下所示：
    + `sqlite> ATTACH DATABASE 'testDB.db' as 'TEST';`
  + 使用 SQLite .database 命令来显示附加的数据库。
```sql
sqlite> .database
seq  name             file
---  ---------------  ----------------------
0    main             /home/sqlite/testDB.db
2    test             /home/sqlite/testDB.db
```
+ 数据库名称 main 和 temp 被保留用于主数据库和存储临时表及其他临时数据对象的数据库。这两个数据库名称可用于每个数据库连接，且不应该被用于附加，否则将得到一个警告消息，如下所示
```sql
sqlite>  ATTACH DATABASE 'testDB.db' as 'TEMP';
Error: database TEMP is already in use
sqlite>  ATTACH DATABASE 'testDB.db' as 'main';
Error: database main is already in use；
```

## SQLite 分离数据库

+ SQLite 的 DETACH DATABASE 语句是用来把命名数据库从一个数据库连接分离和游离出来，连接是之前使用 ATTACH 语句附加的。如果同一个数据库文件已经被附加上多个别名，DETACH 命令将只断开给定名称的连接，而其余的仍然有效。您无法分离 main 或 temp 数据库。
+ 如果数据库是在内存中或者是临时数据库，则该数据库将被摧毁，且内容将会丢失。

+ 语法
  + SQLite 的 DETACH DATABASE 'Alias-Name' 语句的基本语法如下：
    + `DETACH DATABASE 'Alias-Name';`
  + 在这里，'Alias-Name' 与您之前使用 ATTACH 语句附加数据库时所用到的别名相同。

## SQLite 创建表

+ SQLite 的 CREATE TABLE 语句用于在任何给定的数据库创建一个新表。创建基本表，涉及到命名表、定义列及每一列的数据类型。

+ 语法
  + CREATE TABLE 语句的基本语法如下：
```sql
CREATE TABLE database_name.table_name(
   column1 datatype  PRIMARY KEY(one or more columns),
   column2 datatype,
   column3 datatype,
   .....
   columnN datatype,
);
```
  + CREATE TABLE 是告诉数据库系统创建一个新表的关键字。CREATE TABLE 语句后跟着表的唯一的名称或标识。您也可以选择指定带有 table_name 的 database_name。

+ 实例
  + 下面是一个实例，它创建了一个 COMPANY 表，ID 作为主键，NOT NULL 的约束表示在表中创建纪录时这些字段不能为 NULL：
```sql
sqlite> CREATE TABLE COMPANY(
   ID INT PRIMARY KEY     NOT NULL,
   NAME           TEXT    NOT NULL,
   AGE            INT     NOT NULL,
   ADDRESS        CHAR(50),
   SALARY         REAL
);
```
  + 让我们再创建一个表，我们将在随后章节的练习中使用：
```sql
sqlite> CREATE TABLE DEPARTMENT(
   ID INT PRIMARY KEY      NOT NULL,
   DEPT           CHAR(50) NOT NULL,
   EMP_ID         INT      NOT NULL
);
```
  + 您可以使用 SQLIte 命令中的 .tables 命令来验证表是否已成功创建，该命令用于列出附加数据库中的所有表。
```
sqlite>.tables
COMPANY     DEPARTMENT
```
  + 您可以使用 SQLite .schema 命令得到表的完整信息，如下所示：
```sql
sqlite>.schema COMPANY
CREATE TABLE COMPANY(
   ID INT PRIMARY KEY     NOT NULL,
   NAME           TEXT    NOT NULL,
   AGE            INT     NOT NULL,
   ADDRESS        CHAR(50),
   SALARY         REAL
);
```

## SQLite 删除表

+ SQLite 的 DROP TABLE 语句用来删除表定义及其所有相关数据、索引、触发器、约束和该表的权限规范。
+ 使用此命令时要特别注意，因为一旦一个表被删除，表中所有信息也将永远丢失。

+ 语法
  + DROP TABLE 语句的基本语法如下。您可以选择指定带有表名的数据库名称，如下所示
    + `DROP TABLE database_name.table_name;`
    + 

## SQLite Insert 语句

+ SQLite 的 INSERT INTO 语句用于向数据库的某个表中添加新的数据行。

+ 语法
  + INSERT INTO 语句有两种基本语法，如下所示：
```sql
INSERT INTO TABLE_NAME [(column1, column2, column3,...columnN)]  
VALUES (value1, value2, value3,...valueN);
```
  + 在这里，column1, column2,...columnN 是要插入数据的表中的列的名称。
  + 如果要为表中的所有列添加值，您也可以不需要在 SQLite 查询中指定列名称。但要确保值的顺序与列在表中的顺序一致。SQLite 的 INSERT INTO 语法如下：
```sql
INSERT INTO TABLE_NAME VALUES (value1,value2,value3,...valueN);
```

+ 使用一个表来填充另一个表
  + 您可以通过在一个有一组字段的表上使用 select 语句，填充数据到另一个表中。下面是语法：
```sql
INSERT INTO first_table_name [(column1, column2, ... columnN)] 
   SELECT column1, column2, ...columnN 
   FROM second_table_name
   [WHERE condition];
```

## SQLite Select 语句

+ SQLite 的 SELECT 语句用于从 SQLite 数据库表中获取数据，以结果表的形式返回数据。这些结果表也被称为结果集。

+ 语法
  + SQLite 的 SELECT 语句的基本语法如下：
    + `SELECT column1, column2, columnN FROM table_name;`
  + 在这里，column1, column2...是表的字段，他们的值即是您要获取的。如果您想获取所有可用的字段，那么可以使用下面的语法：
    + `SELECT * FROM table_name;`

## SQLite 运算符

+ SQLite 运算符是什么？
  + 运算符是一个保留字或字符，主要用于 SQLite 语句的 WHERE 子句中执行操作，如比较和算术运算。
  + 运算符用于指定 SQLite 语句中的条件，并在语句中连接多个条件。
    + 算术运算符
    + 比较运算符
    + 逻辑运算符
    + 位运算符

+ SQLite 算术运算符
  + 假设变量 a=10，变量 b=20，则：
  + `+`	 : 加法 :  把运算符两边的值相加	a + b 将得到 30
  + `-`	 : 减法 :  左操作数减去右操作数	a - b 将得到 -10
  + `*`	 : 乘法 :  把运算符两边的值相乘	a * b 将得到 200
  + `/`	 : 除法 :  左操作数除以右操作数	b / a 将得到 2
  + `%`	 : 取模 :  左操作数除以右操作数后得到的余数	b % a 将得到 0

+ SQLite 比较运算符
  + 假设变量 a=10，变量 b=20，则：
  + `==`	检查两个操作数的值是否相等，如果相等则条件为真。	(a == b) 不为真。
  + `=` 	检查两个操作数的值是否相等，如果相等则条件为真。	(a = b) 不为真。
  + `!=`	检查两个操作数的值是否相等，如果不相等则条件为真。	(a != b) 为真。
  + `<>`	检查两个操作数的值是否相等，如果不相等则条件为真。	(a <> b) 为真。
  + `>`	    检查左操作数的值是否大于右操作数的值，如果是则条件为真。	(a > b) 不为真。
  + `<`	    检查左操作数的值是否小于右操作数的值，如果是则条件为真。	(a < b) 为真。
  + `>=`	检查左操作数的值是否大于等于右操作数的值，如果是则条件为真。	(a >= b) 不为真。
  + `<=`	检查左操作数的值是否小于等于右操作数的值，如果是则条件为真。	(a <= b) 为真。
  + `!<`	检查左操作数的值是否不小于右操作数的值，如果是则条件为真。	(a !< b) 为假。
  + `!>`	检查左操作数的值是否不大于右操作数的值，如果是则条件为真。	(a !> b) 为真。

+ SQLite 逻辑运算符
  + 下面是 SQLite 中所有的逻辑运算符列表。
  + AND	AND  : 运算符允许在一个 SQL 语句的 WHERE 子句中的多个条件的存在。
  + BETWEEN	 : BETWEEN 运算符用于在给定最小值和最大值范围内的一系列值中搜索值。
  + EXISTS	 : EXISTS 运算符用于在满足一定条件的指定表中搜索行的存在。
  + IN	     : IN 运算符用于把某个值与一系列指定列表的值进行比较。
  + NOT IN	 : IN 运算符的对立面，用于把某个值与不在一系列指定列表的值进行比较。
  + LIKE	 : LIKE 运算符用于把某个值与使用通配符运算符的相似值进行比较。
  + GLOB	 : GLOB 运算符用于把某个值与使用通配符运算符的相似值进行比较。GLOB 与 LIKE 不同之处在于，它是大小写敏感的。
  + NOT	     : NOT 运算符是所用的逻辑运算符的对立面。比如 NOT EXISTS、NOT BETWEEN、NOT IN，等等。它是否定运算符。
  + OR	     : OR 运算符用于结合一个 SQL 语句的 WHERE 子句中的多个条件。
  + IS NULL	 : NULL 运算符用于把某个值与 NULL 值进行比较。
  + IS	     : IS 运算符与 = 相似。
  + IS NOT	 : IS NOT 运算符与 != 相似。
  + ||	     : 连接两个不同的字符串，得到一个新的字符串。
  + UNIQUE	 : UNIQUE 运算符搜索指定表中的每一行，确保唯一性（无重复）。

+ SQLite 位运算符
  + 下表中列出了 SQLite 语言支持的位运算符。假设变量 A=60，变量 B=13，则：
  + `&`	    : 如果同时存在于两个操作数中，二进制 AND 运算符复制一位到结果中。	     (A & B) 将得到 12，即为 0000 1100
  + `|`	    : 如果存在于任一操作数中，二进制 OR 运算符复制一位到结果中。	        (A | B) 将得到 61，即为 0011 1101
  + `~`	    : 二进制补码运算符是一元运算符，具有"翻转"位效应，即0变成1，1变成0。	 (~A ) 将得到 -61，即为 1100 0011，一个有符号二进制数的补码形式。
  + `<<`	: 二进制左移运算符。左操作数的值向左移动右操作数指定的位数。	         A << 2 将得到 240，即为 1111 0000
  + `>>`	: 二进制右移运算符。左操作数的值向右移动右操作数指定的位数。	         A >> 2 将得到 15，即为 0000 1111

## SQLite 表达式

+ 表达式是一个或多个值、运算符和计算值的SQL函数的组合。
+ SQL 表达式与公式类似，都写在查询语言中。您还可以使用特定的数据集来查询数据库。

+ 语法
  + 假设 SELECT 语句的基本语法如下：
```sql
SELECT column1, column2, columnN 
FROM table_name 
WHERE [CONDITION | EXPRESSION];
```

+ SQLite - 布尔表达式
  + SQLite 的布尔表达式在匹配单个值的基础上获取数据。语法如下：
```sql
SELECT column1, column2, columnN 
FROM table_name 
WHERE SINGLE VALUE MATCHING EXPRESSION;
```

+ SQLite - 数值表达式
  + 这些表达式用来执行查询中的任何数学运算。语法如下：
```sql
SELECT numerical_expression as  OPERATION_NAME
[FROM table_name WHERE CONDITION] ;
```
  + 在这里，numerical_expression 用于数学表达式或任何公式。下面的实例演示了 SQLite 数值表达式的用法：
```sql
sqlite> SELECT (15 + 6) AS ADDITION
ADDITION = 21
```
  + 有几个内置的函数，比如 avg()、sum()、count()，等等，执行被称为对一个表或一个特定的表列的汇总数据计算。
```sql
sqlite> SELECT COUNT(*) AS "RECORDS" FROM COMPANY; 
RECORDS = 7
```

+ SQLite - 日期表达式
  + 日期表达式返回当前系统日期和时间值，这些表达式将被用于各种数据操作。
```sql
sqlite>  SELECT CURRENT_TIMESTAMP;
CURRENT_TIMESTAMP = 2013-03-17 10:43:35
```

## SQLite Where 子句

+ SQLite的 WHERE 子句用于指定从一个表或多个表中获取数据的条件。
+ 如果满足给定的条件，即为真（true）时，则从表中返回特定的值。您可以使用 WHERE 子句来过滤记录，只获取需要的记录。
+ WHERE 子句不仅可用在 SELECT 语句中，它也可用在 UPDATE、DELETE 语句中，等等，这些我们将在随后的章节中学习到。

+ 语法：
  + SQLite 的带有 WHERE 子句的 SELECT 语句的基本语法如下：
```sql
SELECT column1, column2, columnN 
FROM table_name
WHERE [condition]
```
  + 您还可以使用比较或逻辑运算符指定条件，比如 >、<、=、LIKE、NOT，等等

+ 下面的 SELECT 语句列出了 NAME 以 'Ki' 开始的所有记录，'Ki' 之后的字符不做限制
```sql
sqlite> SELECT * FROM COMPANY WHERE NAME LIKE 'Ki%';
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
6           Kim         22          South-Hall  45000.0
```

+ 下面的 SELECT 语句列出了 NAME 以 'Ki' 开始的所有记录，'Ki' 之后的字符不做限制：
```sql
sqlite> SELECT * FROM COMPANY WHERE NAME GLOB 'Ki*';
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
6           Kim         22          South-Hall  45000.0
```

+ 下面的 SELECT 语句列出了 AGE 的值为 25 或 27 的所有记录：
```sql
sqlite> SELECT * FROM COMPANY WHERE AGE IN ( 25, 27 );
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
2           Allen       25          Texas       15000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
```

+ 下面的 SELECT 语句列出了 AGE 的值既不是 25 也不是 27 的所有记录：
```sql
sqlite> SELECT * FROM COMPANY WHERE AGE NOT IN ( 25, 27 );
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
3           Teddy       23          Norway      20000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
```

+ 下面的 SELECT 语句列出了 AGE 的值在 25 与 27 之间的所有记录：
```sql
sqlite> SELECT * FROM COMPANY WHERE AGE BETWEEN 25 AND 27;
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
2           Allen       25          Texas       15000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
```

+ 下面的 SELECT 语句使用 SQL 子查询，子查询查找 SALARY > 65000 的带有 AGE 字段的所有记录，后边的 WHERE 子句与 EXISTS 运算符一起使用，列出了外查询中的 AGE 存在于子查询返回的结果中的所有记录：
```sql
sqlite> SELECT AGE FROM COMPANY 
        WHERE EXISTS (SELECT AGE FROM COMPANY WHERE SALARY > 65000);
AGE
----------
32
25
23
25
27
22
24
```

+ 下面的 SELECT 语句使用 SQL 子查询，子查询查找 SALARY > 65000 的带有 AGE 字段的所有记录，后边的 WHERE 子句与 > 运算符一起使用，列出了外查询中的 AGE 大于子查询返回的结果中的年龄的所有记录：
```sql
sqlite> SELECT * FROM COMPANY 
        WHERE AGE > (SELECT AGE FROM COMPANY WHERE SALARY > 65000);
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
```

## SQLite AND/OR 运算符

+ SQLite 的 AND 和 OR 运算符用于编译多个条件来缩小在 SQLite 语句中所选的数据。这两个运算符被称为连接运算符。
+ 这些运算符为同一个 SQLite 语句中不同的运算符之间的多个比较提供了可能。

+ AND 运算符
  + AND 运算符允许在一个 SQL 语句的 WHERE 子句中的多个条件的存在。使用 AND 运算符时，只有当所有条件都为真（true）时，整个条件为真（true）。
  + 例如，只有当 condition1 和 condition2 都为真（true）时，[condition1] AND [condition2] 为真（true）。

+ 语法
  + 带有 WHERE 子句的 AND 运算符的基本语法如下：
```sql
SELECT column1, column2, columnN 
FROM table_name
WHERE [condition1] AND [condition2]...AND [conditionN];
```
  + 您可以使用 AND 运算符来结合 N 个数量的条件。SQLite 语句需要执行的动作是，无论是事务或查询，所有由 AND 分隔的条件都必须为真（TRUE）。

+ OR 运算符
  + OR 运算符也用于结合一个 SQL 语句的 WHERE 子句中的多个条件。使用 OR 运算符时，只要当条件中任何一个为真（true）时，整个条件为真（true）。
  + 例如，只要当 condition1 或 condition2 有一个为真（true）时，[condition1] OR [condition2] 为真（true）。

+ 语法
  + 带有 WHERE 子句的 OR 运算符的基本语法如下：
```sql
SELECT column1, column2, columnN 
FROM table_name
WHERE [condition1] OR [condition2]...OR [conditionN]
```
  + 您可以使用 OR 运算符来结合 N 个数量的条件。SQLite 语句需要执行的动作是，无论是事务或查询，只要任何一个由 OR 分隔的条件为真（TRUE）即可。

## SQLite Update 语句

+ SQLite 的 UPDATE 查询用于修改表中已有的记录。可以使用带有 WHERE 子句的 UPDATE 查询来更新选定行，否则所有的行都会被更新。

+ 语法
  + 带有 WHERE 子句的 UPDATE 查询的基本语法如下：
```sql
UPDATE table_name
SET column1 = value1, column2 = value2...., columnN = valueN
WHERE [condition];
```
  + 您可以使用 AND 或 OR 运算符来结合 N 个数量的条件。

+ 如果您想修改 COMPANY 表中 ADDRESS 和 SALARY 列的所有值，则不需要使用 WHERE 子句，UPDATE 查询如下：
  + `sqlite> UPDATE COMPANY SET ADDRESS = 'Texas', SALARY = 20000.00;`

## SQLite Delete 语句

+ SQLite 的 DELETE 查询用于删除表中已有的记录。可以使用带有 WHERE 子句的 DELETE 查询来删除选定行，否则所有的记录都会被删除。

+ 语法
  + 带有 WHERE 子句的 DELETE 查询的基本语法如下：
```sql
DELETE FROM table_name
WHERE [condition];
```
  + 您可以使用 AND 或 OR 运算符来结合 N 个数量的条件。

## SQLite Like 子句

+ SQLite 的 LIKE 运算符是用来匹配通配符指定模式的文本值。如果搜索表达式与模式表达式匹配，LIKE 运算符将返回真（true），也就是 1。这里有两个通配符与 LIKE 运算符一起使用：
  + 百分号 （%）
  + 下划线 （_）
+ 百分号（%）代表零个、一个或多个数字或字符。下划线（_）代表一个单一的数字或字符。这些符号可以被组合使用。

+ 语法
  + % 和 _ 的基本语法如下：
```sql
SELECT column_list 
FROM table_name
WHERE column LIKE 'XXXX%'

or 

SELECT column_list 
FROM table_name
WHERE column LIKE '%XXXX%'

or

SELECT column_list 
FROM table_name
WHERE column LIKE 'XXXX_'

or

SELECT column_list 
FROM table_name
WHERE column LIKE '_XXXX'

or

SELECT column_list 
FROM table_name
WHERE column LIKE '_XXXX_'
```
+ 您可以使用 AND 或 OR 运算符来结合 N 个数量的条件。在这里，XXXX 可以是任何数字或字符串值。

+ 实例
  + 下面一些实例演示了 带有 '%' 和 '_' 运算符的 LIKE 子句不同的地方：
  + `WHERE SALARY LIKE '200%'`	查找以 200 开头的任意值
  + `WHERE SALARY LIKE '%200%'`	查找任意位置包含 200 的任意值
  + `WHERE SALARY LIKE '_00%'`	查找第二位和第三位为 00 的任意值
  + `WHERE SALARY LIKE '2_%_%'`	查找以 2 开头，且长度至少为 3 个字符的任意值
  + `WHERE SALARY LIKE '%2'`	查找以 2 结尾的任意值
  + `WHERE SALARY LIKE '_2%3'`	查找第二位为 2，且以 3 结尾的任意值
  + `WHERE SALARY LIKE '2___3'`	查找长度为 5 位数，且以 2 开头以 3 结尾的任意值

+ 下面是一个实例，它显示 COMPANY 表中 AGE 以 2 开头的所有记录：
  + `sqlite> SELECT * FROM COMPANY WHERE AGE  LIKE '2%';`

+ 下面是一个实例，它显示 COMPANY 表中 ADDRESS 文本里包含一个连字符（-）的所有记录：
  + `sqlite> SELECT * FROM COMPANY WHERE ADDRESS  LIKE '%-%';`

## SQLite Glob 子句

+ SQLite 的 GLOB 运算符是用来匹配通配符指定模式的文本值。如果搜索表达式与模式表达式匹配，GLOB 运算符将返回真（true），也就是 1。与 LIKE 运算符不同的是，GLOB 是大小写敏感的，对于下面的通配符，它遵循 UNIX 的语法。
  + `*`      ：匹配零个、一个或多个数字或字符。
  + `?`      ：代表一个单一的数字或字符。
  + `[...]`  ：匹配方括号内指定的字符之一。例如，[abc] 匹配 "a"、"b" 或 "c" 中的任何一个字符。
  + `[^...]` ：匹配不在方括号内指定的字符之一。例如，[^abc] 匹配不是 "a"、"b" 或 "c" 中的任何一个字符的字符。
+ 以上这些符号可以被组合使用

+ 语法
  + * 和 ? 的基本语法如下：
```sql
SELECT FROM table_name
WHERE column GLOB 'XXXX*'

or 

SELECT FROM table_name
WHERE column GLOB '*XXXX*'

or

SELECT FROM table_name
WHERE column GLOB 'XXXX?'

or

SELECT FROM table_name
WHERE column GLOB '?XXXX'

or

SELECT FROM table_name
WHERE column GLOB '?XXXX?'

or

SELECT FROM table_name
WHERE column GLOB '????'

```
+ 您可以使用 AND 或 OR 运算符来结合 N 个数量的条件。在这里，XXXX 可以是任何数字或字符串值。

+ 实例
  + 下面一些实例演示了 带有 '*' 和 '?' 运算符的 GLOB 子句不同的地方：
    + `WHERE SALARY GLOB '200*'`	查找以 200 开头的任意值
    + `WHERE SALARY GLOB '*200*'`	查找任意位置包含 200 的任意值
    + `WHERE SALARY GLOB '?00*'`	查找第二位和第三位为 00 的任意值
    + `WHERE SALARY GLOB '2??'`	    查找以 2 开头，且长度为 3 个字符的任意值，例如，它可能匹配 "200"、"2A1"、"2B2" 等值。
    + `WHERE SALARY GLOB '*2'`	    查找以 2 结尾的任意值
    + `WHERE SALARY GLOB '?2*3'`	查找第二位为 2，且以 3 结尾的任意值
    + `WHERE SALARY GLOB '2???3'`	查找长度为 5 位数，且以 2 开头以 3 结尾的任意值

+ `[...]` 通配符
  + `[...]` 表达式用于匹配方括号内指定的字符集中的任何一个字符。

+ 实例 1：匹配以 "A" 或 "B" 开头的产品名称。
  + `SELECT * FROM products WHERE product_name LIKE '[AB]%';`
+ 这将匹配以 "A" 或 "B" 开头的产品名称。

+ 实例 2：匹配以 "1"、"2" 或 "3" 开头的电话号码。
  + `SELECT * FROM customers WHERE phone_number LIKE '[123]%';`
+ 这将匹配以 "1"、"2" 或 "3" 开头的电话号码。

+ `[^...]` 通配符
  + `[^...]` 表达式用于匹配不在方括号内指定的字符集中的任何字符。

+ 实例 1：匹配不以 "X" 或 "Y" 开头的产品代码。
  + `SELECT * FROM products WHERE product_code LIKE '[^XY]%';`
+ 这将匹配不以 "X" 或 "Y" 开头的产品

+ 实例 2：匹配不包含数字字符的用户名。
  + `SELECT * FROM users WHERE username LIKE '[^0-9]%';`
+ 这将匹配不以数字字符开头的用户名。

## SQLite Limit 子句

+ SQLite 的 LIMIT 子句用于限制由 SELECT 语句返回的数据数量。

+ 语法
  + 带有 LIMIT 子句的 SELECT 语句的基本语法如下：
```sql
SELECT column1, column2, columnN 
FROM table_name
LIMIT [no of rows]
```
  + 下面是 LIMIT 子句与 OFFSET 子句一起使用时的语法：
```sql
SELECT column1, column2, columnN 
FROM table_name
LIMIT [no of rows] OFFSET [row num]
```
  + SQLite 引擎将返回从下一行开始直到给定的 OFFSET 为止的所有行，如下面的最后一个实例所示

+ 但是，在某些情况下，可能需要从一个特定的偏移开始提取记录。下面是一个实例，从第三位开始提取 3 个记录：
  + `sqlite> SELECT * FROM COMPANY LIMIT 3 OFFSET 2;`

## SQLite Order By

+ SQLite 的 ORDER BY 子句是用来基于一个或多个列按升序或降序顺序排列数据。

+ 语法
  + ORDER BY 子句的基本语法如下：
```sql
SELECT column-list 
FROM table_name 
[WHERE condition] 
[ORDER BY column1, column2, .. columnN] [ASC | DESC];
```
  + ASC 默认值，从小到大，升序排列
  + DESC 从大到小，降序排列

+ 您可以在 ORDER BY 子句中使用多个列，确保您使用的排序列在列清单中：
```sql
SELECT
   select_list
FROM
   table
ORDER BY
    column_1 ASC,
    column_2 DESC;
```
+ column_1 与 column_2 如果后面不指定排序规则，默认为 ASC 升序，以上语句按 column_1 升序，column_2 降序读取，等价如下语句：
```sql
SELECT
   select_list
FROM
   table
ORDER BY
    column_1,
    column_2 DESC;
```

+ 下面是一个实例，它会将结果按 NAME 和 SALARY 升序排序：
  + `sqlite> SELECT * FROM COMPANY ORDER BY NAME, SALARY ASC;`

## SQLite Group By

+ SQLite 的 GROUP BY 子句用于与 SELECT 语句一起使用，来对相同的数据进行分组。
+ 在 SELECT 语句中，GROUP BY 子句放在 WHERE 子句之后，放在 ORDER BY 子句之前。

+ 语法
  + 下面给出了 GROUP BY 子句的基本语法。GROUP BY 子句必须放在 WHERE 子句中的条件之后，必须放在 ORDER BY 子句之前。
```sql
SELECT column-list
FROM table_name
WHERE [ conditions ]
GROUP BY column1, column2....columnN
ORDER BY column1, column2....columnN
```
  + 您可以在 GROUP BY 子句中使用多个列。确保您使用的分组列在列清单中。

## SQLite Having 子句

+ HAVING 子句允许指定条件来过滤将出现在最终结果中的分组结果。
+ WHERE 子句在所选列上设置条件，而 HAVING 子句则在由 GROUP BY 子句创建的分组上设置条件。

+ 语法
  + 下面是 HAVING 子句在 SELECT 查询中的位置：
```sql
SELECT
FROM
WHERE
GROUP BY
HAVING
ORDER BY
```
  + 在一个查询中，HAVING 子句必须放在 GROUP BY 子句之后，必须放在 ORDER BY 子句之前。下面是包含 HAVING 子句的 SELECT 语句的语法：
```sql
SELECT column1, column2
FROM table1, table2
WHERE [ conditions ]
GROUP BY column1, column2
HAVING [ conditions ]
ORDER BY column1, column2
```

+ 下面是一个实例，它将显示名称计数大于 2 的所有记录：
  + `sqlite > SELECT * FROM COMPANY GROUP BY name HAVING count(name) > 2;`

## SQLite Distinct 关键字

+ SQLite 的 DISTINCT 关键字与 SELECT 语句一起使用，来消除所有重复的记录，并只获取唯一一次记录。
+ 有可能出现一种情况，在一个表中有多个重复的记录。当提取这样的记录时，DISTINCT 关键字就显得特别有意义，它只获取唯一一次记录，而不是获取重复记录。

+ 语法
  + 用于消除重复记录的 DISTINCT 关键字的基本语法如下：
```sql
SELECT DISTINCT column1, column2,.....columnN 
FROM table_name
WHERE [condition]
```

+ 现在，让我们在上述的 SELECT 查询中使用 DISTINCT 关键字：
  + `sqlite> SELECT DISTINCT name FROM COMPANY;`