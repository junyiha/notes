## mysql 5.7

### 不用密码也能登录的问题

+ 在ubuntu下载mysql后，用mysql命令就可以直接登录数据库了，这是因为在mysql.user表里有个plugin的字段，root这个用户的值是auth_socket, 需要把它改成mysql_native_password。
+ 具体步骤如下：
  + `use mysql;`
  + `update user set authentication_string=PASSWORD("密码") where user=‘root‘;`
  + `update user set plugin="mysql_native_password"; `
  + `flush privileges;`
  + `quit;`

## SQL 

+ SQL 是用于访问和处理数据库的标准的计算机语言。
+ 在本教程中，您将学到如何使用 SQL 访问和处理数据系统中的数据，这类数据库包括：MySQL、SQL Server、Access、Oracle、Sybase、DB2 等等。

## 1.1 SQL 简介

+ SQL (Structured Query Language:结构化查询语言) 是用于管理关系数据库管理系统（RDBMS）。 
+ SQL 的范围包括数据插入、查询、更新和删除，数据库模式创建和修改，以及数据访问控制。

### 1.1.1 SQL 是什么

+ SQL 指结构化查询语言，全称是 Structured Query Language。
+ SQL 让您可以访问和处理数据库，包括数据插入、查询、更新和删除。
+ SQL 在1986年成为 ANSI（American National Standards Institute 美国国家标准化组织）的一项标准，在 1987 年成为国际标准化组织（ISO）标准。

### 1.1.2 SQL 能做什么

+ SQL 面向数据库执行查询
+ SQL 可从数据库取回数据
+ SQL 可在数据库中插入新的记录
+ SQL 可更新数据库中的数据
+ SQL 可从数据库删除记录
+ SQL 可创建新数据库
+ SQL 可在数据库中创建新表
+ SQL 可在数据库中创建存储过程
+ SQL 可在数据库中创建视图
+ SQL 可以设置表、存储过程和视图的权限

### 1.1.3 SQL 是一种标准 - 但是...

+ 虽然 SQL 是一门 ANSI（American National Standards Institute 美国国家标准化组织）标准的计算机语言，但是仍然存在着多种不同版本的 SQL 语言。
+ 然而，为了与 ANSI 标准相兼容，它们必须以相似的方式共同地来支持一些主要的命令（比如 SELECT、UPDATE、DELETE、INSERT、WHERE 等等）。

+ 注释：除了 SQL 标准之外，大部分 SQL 数据库程序都拥有它们自己的专有扩展！

### 1.1.4 RDBMS

+ RDBMS 指关系型数据库管理系统，全称 Relational Database Management System。
+ RDBMS 是 SQL 的基础，同样也是所有现代数据库系统的基础，比如 MS SQL Server、IBM DB2、Oracle、MySQL 以及 Microsoft Access。
+ RDBMS 中的数据存储在被称为表的数据库对象中。
+ 表是相关的数据项的集合，它由列和行组成。

## 1.2 SQL 语法

### 1.2.1 数据库表

+ 一个数据库通常包含一个或多个表。每个表有一个名字标识（例如:"Websites"）,表包含带有数据的记录（行）。

### 1.2.2 SQL 语句

+ SQL 对大小写不敏感：SELECT 与 select 是相同的。

+ 某些数据库系统要求在每条 SQL 语句的末端使用分号。
+ 分号是在数据库系统中分隔每条 SQL 语句的标准方法，这样就可以在对服务器的相同请求中执行一条以上的 SQL 语句。

### 1.2.3 一些最重要的 SQL 命令

+ SELECT - 从数据库中提取数据
+ UPDATE - 更新数据库中的数据
+ DELETE - 从数据库中删除数据
+ INSERT INTO - 向数据库中插入新数据
+ CREATE DATABASE - 创建新数据库
+ ALTER DATABASE - 修改数据库
+ CREATE TABLE - 创建新表
+ ALTER TABLE - 变更（改变）数据库表
+ DROP TABLE - 删除表
+ CREATE INDEX - 创建索引（搜索键）
+ DROP INDEX - 删除索引

## 1.3 SQL SELECT语句

+ SELECT 语句用于从数据库中选取数据。结果被存储在一个结果表中，称为结果集。

+ SQL SELECT 语法
  ```
    SELECT column1, column2, ...
    FROM table_name;
  ```
  + `SELECT * FROM table_name;`
+ 参数说明：
  + column1, column2, ...：要选择的字段名称，可以为多个字段。如果不指定字段名称，则会选择所有字段。
  + table_name：要查询的表名称。

+ 大多数数据库软件系统都允许使用编程函数在结果集中进行导航，比如：Move-To-First-Record、Get-Record-Content、Move-To-Next-Record 等等。
+ 类似这些编程函数不在本教程讲解之列。如需学习通过函数调用访问数据的知识，请访问我们的 ADO 教程 或者 PHP 教程。

## 1.3 SQL SELECT DISTINCT 语句

+ SELECT DISTINCT 语句用于返回唯一不同的值。
+ 在表中，一个列可能会包含多个重复值，有时您也许希望仅仅列出不同（distinct）的值。DISTINCT 关键词用于返回唯一不同的值。

+ SQL SELECT DISTINCT 语法
  ```
    SELECT DISTINCT column1, column2, ...
    FROM table_name;
  ``` 
+ 参数说明：
  + column1, column2, ...：要选择的字段名称，可以为多个字段。如果不指定字段名称，则会选择所有字段。
  + table_name：要查询的表名称。

+ SELECT DISTINCT 实例
  + 下面的 SQL 语句仅从 "Websites" 表的 "country" 列中选取唯一不同的值，也就是去掉 "country" 列重复值：
  + `SELECT DISTINCT country FROM Websites;`

## 1.3 SQL WHERE 子句

+ WHERE 子句用于过滤记录。
+ WHERE 子句用于提取那些满足指定条件的记录。

+ SQL WHERE 语法
  ```
    SELECT column1, column2, ...
    FROM table_name
    WHERE condition;
  ``` 
+ 参数说明：
  + column1, column2, ...：要选择的字段名称，可以为多个字段。如果不指定字段名称，则会选择所有字段。
  + table_name：要查询的表名称。

+ WHERE 子句实例
  + 下面的 SQL 语句从 "Websites" 表中选取国家为 "CN" 的所有网站：
  + `SELECT * FROM Websites WHERE country='CN';`

## 1.4 SQL AND & OR 运算符

+ AND & OR 运算符用于基于一个以上的条件对记录进行过滤。
+ 如果第一个条件和第二个条件都成立，则 AND 运算符显示一条记录。
+ 如果第一个条件和第二个条件中只要有一个成立，则 OR 运算符显示一条记录。

+ AND 运算符实例
  + 下面的 SQL 语句从 "Websites" 表中选取国家为 "CN" 且alexa排名大于 "50" 的所有网站：
    ```
      SELECT * FROM Websites
      WHERE country='CN'
      AND alexa > 50;
    ``` 
+ OR 运算符实例
  + 下面的 SQL 语句从 "Websites" 表中选取国家为 "USA" 或者 "CN" 的所有客户：
    ```
      SELECT * FROM Websites
      WHERE country='USA'
      OR country='CN';
    ``` 
+ 结合 AND & OR
  + 您也可以把 AND 和 OR 结合起来（使用圆括号来组成复杂的表达式）。
  + 下面的 SQL 语句从 "Websites" 表中选取 alexa 排名大于 "15" 且国家为 "CN" 或 "USA" 的所有网站：
    ```
      SELECT * FROM Websites
      WHERE alexa > 15
      AND (country='CN' OR country='USA');
    ``` 

## 1.5 SQL ORDER BY 关键字

+ ORDER BY 关键字用于对结果集进行排序。
+ ORDER BY 关键字用于对结果集按照一个列或者多个列进行排序。
+ ORDER BY 关键字默认按照升序对记录进行排序。如果需要按照降序对记录进行排序，您可以使用 DESC 关键字。

+ SQL ORDER BY 语法
  ```
    SELECT column1, column2, ...
    FROM table_name
    ORDER BY column1, column2, ... ASC|DESC;
  ``` 
+ 参数解析：
  + column1, column2, ...：要排序的字段名称，可以为多个字段。
  + ASC：表示按升序排序。
  + DESC：表示按降序排序。

+ ORDER BY 实例
  + 下面的 SQL 语句从 "Websites" 表中选取所有网站，并按照 "alexa" 列排序：
    ```
      SELECT * FROM Websites
      ORDER BY alexa;
    ``` 
+ ORDER BY DESC 实例
  + 下面的 SQL 语句从 "Websites" 表中选取所有网站，并按照 "alexa" 列降序排序：
    ```
      SELECT * FROM Websites
      ORDER BY alexa DESC;
    ``` 
+ ORDER BY 多列
  + 下面的 SQL 语句从 "Websites" 表中选取所有网站，并按照 "country" 和 "alexa" 列排序：
    ```
      SELECT * FROM Websites
      ORDER BY country,alexa;
    ``` 

## 1.5 SQL INSERT INTO 语句

+ INSERT INTO 语句用于向表中插入新记录。
+ INSERT INTO 语句可以有两种编写形式。
  + 第一种形式无需指定要插入数据的列名，只需提供被插入的值即可：
    ```
      INSERT INTO table_name
      VALUES (value1,value2,value3,...);
    ```
  + 第二种形式需要指定列名及被插入的值：
    ```
      INSERT INTO table_name (column1,column2,column3,...)
      VALUES (value1,value2,value3,...);
    ``` 
+ 参数说明：
  + table_name：需要插入新记录的表名。
  + column1, column2, ...：需要插入的字段名。
  + value1, value2, ...：需要插入的字段值。

+ INSERT INTO 实例
  + 假设我们要向 "Websites" 表中插入一个新行。
    ```
      INSERT INTO Websites (name, url, alexa, country)
      VALUES ('百度','https://www.baidu.com/','4','CN');
    ```
  + 在指定的列插入数据
  + 下面的 SQL 语句将插入一个新行，但是只在 "name"、"url" 和 "country" 列插入数据（id 字段会自动更新）：
    ```
      INSERT INTO Websites (name, url, country)
      VALUES ('stackoverflow', 'http://stackoverflow.com/', 'IND');
    ``` 

## 1.6 SQL UPDATE 语句

+ UPDATE 语句用于更新表中的记录。
+ UPDATE 语句用于更新表中已存在的记录。

+ SQL UPDATE 语法
  ```
    UPDATE table_name
    SET column1 = value1, column2 = value2, ...
    WHERE condition;
  ``` 
+ 参数说明：
  + table_name：要修改的表名称。
  + column1, column2, ...：要修改的字段名称，可以为多个字段。
  + value1, value2, ...：要修改的值，可以为多个值。
  + condition：修改条件，用于指定哪些数据要修改

+ 请注意 SQL UPDATE 语句中的 WHERE 子句！
+ WHERE 子句规定哪条记录或者哪些记录需要更新。如果您省略了 WHERE 子句，所有的记录都将被更新！

+ SQL UPDATE 实例
  + 假设我们要把 "菜鸟教程" 的 alexa 排名更新为 5000，country 改为 USA。
    ```
      UPDATE Websites 
      SET alexa='5000', country='USA' 
      WHERE name='菜鸟教程';
    ``` 

## 1.7 SQL DELETE 语句

+ DELETE 语句用于删除表中的记录。
+ DELETE 语句用于删除表中的行。

+ SQL DELETE 语法
  ```
    DELETE FROM table_name
    WHERE condition;
  ``` 
+ 参数说明：
  + table_name：要删除的表名称。
  + condition：删除条件，用于指定哪些数据要删除

+ SQL DELETE 实例
  + 假设我们要从 "Websites" 表中删除网站名为 "Facebook" 且国家为 USA 的网站。
    ```
      DELETE FROM Websites
      WHERE name='Facebook' AND country='USA';
    ``` 

+ 删除所有数据
  + 您可以在不删除表的情况下，删除表中所有的行。这意味着表结构、属性、索引将保持不变：
  + `DELETE FROM table_name;`

## SQL 脚本

+ 像编写shell脚本一样，只不过语句换成了SQL语句
+ 编写完成之后，通过mysql -u root -p password 进入到sql命令窗口，执行指令`source /sql.sh`执行sql脚本