---
category: Tools
date: 2024-05-22 09:00:00 +0800
layout: post
title: PostgreSQL
tag: Tools
---
## 简介

+ PostgreSQL数据库

## postgreSQL 数据库是什么

PostgreSQL是一个免费的开源关系型数据库管理系统（RDBMS），它采用了PostgreSQL许可证，允许用户免费使用、修改和分发它。PostgreSQL经常被简称为"Postgres"。它具有强大的功能和可扩展性，被广泛用于开发各种类型的应用程序。

一些 PostgreSQL 的关键特性包括：

1. **关系型数据库管理系统（RDBMS）**：PostgreSQL是一种基于关系模型的数据库系统，允许用户以表格的形式存储和管理数据。

2. **免费且开源**：PostgreSQL是免费的，用户可以自由使用、修改和分发它。

3. **支持多种数据类型**：除了常见的数据类型如整数、字符和日期等，PostgreSQL还支持JSON、数组、几何数据类型等多种复杂数据类型。

4. **支持SQL语言**：它支持标准的结构化查询语言（SQL），允许用户进行数据查询、操作和管理。

5. **扩展性**：PostgreSQL具有良好的扩展性，支持插件和扩展模块，允许用户添加额外的功能和特性。

6. **事务支持**：它支持ACID（原子性、一致性、隔离性和持久性）属性，确保数据操作的完整性和一致性。

7. **触发器和存储过程**：PostgreSQL支持触发器和存储过程，使得用户能够在特定事件发生时自动执行操作。

8. **复制和高可用性**：提供复制功能，可以创建备份以及实现高可用性和故障容错。

PostgreSQL是一个功能强大、稳定可靠且高度可定制的数据库管理系统，被广泛应用于各种类型的应用程序，从个人项目到大型企业级应用都可以使用它来存储和管理数据。

## PostgreSQL 详解

PostgreSQL是一个功能强大的开源关系型数据库管理系统（RDBMS），具有许多特性和优势，适用于各种规模和类型的应用。以下是对PostgreSQL的一些详细解释：

### 特性和功能：

1. **数据类型支持**：除了标准的数据类型（整数、字符、日期等），PostgreSQL支持复杂数据类型如数组、JSON、几何数据等。

2. **多种编程语言扩展**：允许使用多种编程语言编写存储过程、函数和触发器，如PL/pgSQL、PL/Python、PL/Perl、PL/Java等。

3. **ACID兼容**：支持事务的ACID属性（原子性、一致性、隔离性、持久性），确保数据的完整性和一致性。

4. **扩展性**：具有良好的扩展性，支持插件和扩展模块，可添加额外功能以满足特定需求。

5. **复杂查询优化**：支持复杂的查询语句和联合查询，提供了强大的优化功能以提高查询性能。

6. **完整性约束**：支持各种完整性约束，如主键约束、外键约束、唯一约束等，确保数据的完整性。

7. **触发器和存储过程**：允许开发者定义触发器和存储过程，以实现在特定事件发生时自动执行的操作。

8. **并发控制**：提供有效的并发控制机制，支持多个用户同时对数据库进行访问和操作。

9. **复制和高可用性**：支持数据复制功能，可创建备份以及实现高可用性和故障容错。

10. **安全性**：提供多种安全功能，包括访问控制、SSL支持、数据加密等，保护数据库免受未经授权的访问和攻击。

### 应用领域：

1. **Web应用程序**：用于存储和管理Web应用程序的数据，如电子商务平台、社交媒体网站等。

2. **企业级应用**：被广泛用于企业级应用，用于数据分析、报告生成、客户关系管理等。

3. **地理信息系统（GIS）**：由于其对地理空间数据的支持，常用于开发GIS应用。

4. **科学研究**：用于处理大量数据和进行复杂查询，满足科学研究领域的需求。

5. **物联网（IoT）**：适用于存储和管理大量物联网设备生成的数据。

### 社区和生态系统：

1. **活跃的社区支持**：拥有一个活跃的开发社区，提供广泛的文档、教程和支持。

2. **丰富的第三方工具和扩展**：有许多第三方工具和扩展可用于简化开发、监控和管理PostgreSQL数据库。

总的来说，PostgreSQL是一个功能强大、稳定可靠且高度可定制的数据库管理系统，它的特性和灵活性使其成为许多应用程序开发者和企业的首选数据库之一。

## PostgreSQL 可以用哪些编程语言开发

PostgreSQL本身是用C语言开发的，但它提供了许多支持扩展的方式，允许使用多种编程语言来开发扩展功能。这些扩展可以作为存储过程、函数、触发器等与数据库交互的组件，其中一些常用的开发语言包括：

1. **PL/pgSQL**：这是PostgreSQL的内置过程式语言，类似于Oracle的PL/SQL。它与SQL语句紧密集成，允许开发者编写存储过程和触发器等。

2. **PL/Python**：允许使用Python语言编写存储过程、函数和触发器。它使得开发者可以利用Python的强大功能来扩展数据库功能。

3. **PL/Perl**：允许使用Perl语言编写存储过程、函数和触发器。对于熟悉Perl的开发者来说，这是一个很好的选择。

4. **PL/Java**：允许使用Java语言编写存储过程、函数和触发器。这个扩展允许开发者利用Java的强大功能来扩展数据库。

5. **PL/SQL**：通过第三方扩展，允许在PostgreSQL中使用Oracle的PL/SQL语言，从而方便那些熟悉Oracle数据库的开发者。

6. **其他语言扩展**：除了上述常用的语言外，PostgreSQL还支持其他一些语言的扩展，如PL/R（R语言）、PL/V8（JavaScript）等。这些扩展使得开发者可以根据自己的需求选择适合的编程语言来开发数据库功能。

通过这些扩展，开发者可以选择自己熟悉的编程语言来扩展PostgreSQL的功能，使其适应各种需求和场景。

## PostgreSQL 语法

+ 默认情况下 PostgreSQL 安装完成后，自带了一个命令行工具 SQL Shell(psql)。
+ Linux 系统可以直接切换到 postgres 用户来开启命令行工具：
  + #  sudo -i -u postgres

+ 进入命令行工具，我们可以使用 \help 来查看各个命令的语法 ：
  + postgres-# \help <command_name>

+ SQL 语句
  + 一个 SQL 语句通常包含了关键字、标识符（字段）、常量、特殊符号等，下面是一个简单的 SQL 语句：
  + SELECT id, name FROM runoob

+ PostgreSQL 命令
  + ABORT
    + ABORT 用于退出当前事务。
    + ABORT [ WORK | TRANSACTION ]
  + ALTER AGGREGATE
    + 修改一个聚集函数的定义 。
```sql
ALTER AGGREGATE _name_ ( _argtype_ [ , ... ] ) RENAME TO _new_name_
ALTER AGGREGATE _name_ ( _argtype_ [ , ... ] ) OWNER TO _new_owner_
ALTER AGGREGATE _name_ ( _argtype_ [ , ... ] ) SET SCHEMA _new_schema_
```
  + ALTER COLLATION
    + 修改一个排序规则定义 。
```sql
ALTER COLLATION _name_ RENAME TO _new_name_
ALTER COLLATION _name_ OWNER TO _new_owner_
ALTER COLLATION _name_ SET SCHEMA _new_schema_
```
  + ALTER CONVERSION
```sql
ALTER CONVERSION name RENAME TO new_name
ALTER CONVERSION name OWNER TO new_owner
```
  + ALTER DATABASE
    + 修改一个数据库。
```sql
ALTER DATABASE name SET parameter { TO | = } { value | DEFAULT }
ALTER DATABASE name RESET parameter
ALTER DATABASE name RENAME TO new_name
ALTER DATABASE name OWNER TO new_owner
```
  + ALTER DEFAULT PRIVILEGES
    + 定义默认的访问权限。
```sql
ALTER DEFAULT PRIVILEGES
    [ FOR { ROLE | USER } target_role [, ...] ]
    [ IN SCHEMA schema_name [, ...] ]
    abbreviated_grant_or_revoke

where abbreviated_grant_or_revoke is one of:

GRANT { { SELECT | INSERT | UPDATE | DELETE | TRUNCATE | REFERENCES | TRIGGER }
    [, ...] | ALL [ PRIVILEGES ] }
    ON TABLES
    TO { [ GROUP ] role_name | PUBLIC } [, ...] [ WITH GRANT OPTION ]
...
```