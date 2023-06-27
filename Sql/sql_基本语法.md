## 简介

+ sql编程语言的基本语法

## sql 常用语句

SQL（Structured Query Language）是一种用于管理关系型数据库的编程语言。下面是一些SQL编程语言中常用的语句：

1. 数据库操作语句：
   - 创建数据库：`CREATE DATABASE database_name;`
   - 删除数据库：`DROP DATABASE database_name;`
   - 切换数据库：`USE database_name;`

2. 表操作语句：
   - 创建表：`CREATE TABLE table_name (column1 datatype, column2 datatype, ...);`
   - 删除表：`DROP TABLE table_name;`
   - 修改表结构：`ALTER TABLE table_name ADD column_name datatype;`

3. 数据操作语句：
   - 插入数据：`INSERT INTO table_name (column1, column2, ...) VALUES (value1, value2, ...);`
   - 更新数据：`UPDATE table_name SET column1 = value1, column2 = value2 WHERE condition;`
   - 删除数据：`DELETE FROM table_name WHERE condition;`
   - 查询数据：`SELECT column1, column2, ... FROM table_name WHERE condition;`

4. 数据过滤语句：
   - 条件过滤：使用WHERE子句进行条件筛选，例如：`WHERE column_name = value`。
   - 范围过滤：使用BETWEEN和IN进行范围筛选，例如：`WHERE column_name BETWEEN value1 AND value2`。
   - 模糊搜索：使用LIKE进行模糊匹配，例如：`WHERE column_name LIKE '%value%'`。

5. 数据排序和限制语句：
   - 排序数据：使用ORDER BY子句对结果进行排序，例如：`ORDER BY column_name ASC/DESC`。
   - 限制结果：使用LIMIT子句限制结果集的数量，例如：`LIMIT n`。

6. 数据聚合和统计语句：
   - 聚合函数：使用聚合函数对数据进行计算，如COUNT、SUM、AVG、MIN、MAX等，例如：`SELECT COUNT(*) FROM table_name`。
   - 分组数据：使用GROUP BY子句对结果进行分组，例如：`GROUP BY column_name`。
   - 过滤分组：使用HAVING子句对分组结果进行过滤，例如：`HAVING condition`。

这些是SQL编程语言中常用的一些语句，可以用于创建和管理数据库、操作数据、查询数据和进行数据分析。具体的语法和用法可能会根据数据库管理系统的不同而有所差异，因此在实际使用时需要参考相应的数据库文档和语法规范。

---

## ORDER 详解

在SQL中，ORDER BY子句用于对查询结果进行排序。它可以按照一个或多个列的值进行升序（ASC）或降序（DESC）排序。以下是ORDER BY子句的详细解释：

基本语法：
```sql
SELECT column1, column2, ...
FROM table_name
ORDER BY column1 [ASC|DESC], column2 [ASC|DESC], ...;
```

- SELECT：用于指定要查询的列。
- FROM：用于指定要查询的表名。
- ORDER BY：用于指定排序规则。
- column1, column2, ...：要按照其值进行排序的列名。
- ASC：升序排列（默认值）。
- DESC：降序排列。

示例：
假设有一个名为"employees"的表，包含以下列：id、name和salary。我们将使用该表作为示例来说明ORDER BY的使用：

```sql
SELECT id, name, salary
FROM employees
ORDER BY salary DESC;
```

上述示例将返回按照salary列的值降序排列的结果集。结果集中的记录将按照salary的值从高到低排序。

```sql
SELECT id, name, salary
FROM employees
ORDER BY name ASC, salary DESC;
```

上述示例将返回首先按照name列的值升序排列，如果name相同，则按照salary列的值降序排列的结果集。

需要注意的是，ORDER BY子句的位置应该位于查询语句的最后，以便在执行排序之前获取查询结果。

ORDER BY子句在SQL中非常有用，它使我们能够按照特定的列或多个列对查询结果进行排序，以满足特定的排序需求。