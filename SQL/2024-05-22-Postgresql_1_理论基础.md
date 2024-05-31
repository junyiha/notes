---
category: SQL
date: 2024-05-22 09:00:00 +0800
layout: post
title: Postgresql_1_理论基础
tag: SQL
---
## 简介

+ PostgresQL 关系型数据库

## 什么是数据库？

+ 数据库（Database）是按照数据结构来组织、存储和管理数据的仓库。
+ 每个数据库都有一个或多个不同的 API 用于创建，访问，管理，搜索和复制所保存的数据。
+ 我们也可以将数据存储在文件中，但是在文件中读写数据速度相对较慢。
+ 所以，现在我们使用关系型数据库管理系统（RDBMS）来存储和管理的大数据量。所谓的关系型数据库，是建立在关系模型基础上的数+ 据库，借助于集合代数等数学概念和方法来处理数据库中的数据。
+ ORDBMS（对象关系数据库系统）是面向对象技术与传统的关系数据库相结合的产物，查询处理是 ORDBMS 的重要组成部分，它的性能+ 优劣将直接影响到DBMS 的性能。
+ ORDBMS在原来关系数据库的基础上，增加了一些新的特性。
+ RDBMS 是关系数据库管理系统，是建立实体之间的联系，最后得到的是关系表。
+ OODBMS 面向对象数据库管理系统，将所有实体都看成对象，并将这些对象类进行封装，对象之间的通信通过消息 OODBMS 对象关系数据库在实质上还是关系数据库

## ORDBMS 术语

+ 在我们开始学习 PostgreSQL 数据库前，让我们先了解下 ORDBMS 的一些术语：
  + 数据库: 数据库是一些关联表的集合。
  + 数据表: 表是数据的矩阵。在一个数据库中的表看起来像一个简单的电子表格。
  + 列: 一列(数据元素) 包含了相同的数据, 例如邮政编码的数据。
  + 行：一行（=元组，或记录）是一组相关的数据，例如一条用户订阅的数据。
  + 冗余：存储两倍数据，冗余降低了性能，但提高了数据的安全性。
  + 主键：主键是唯一的。一个数据表中只能包含一个主键。你可以使用主键来查询数据。
  + 外键：外键用于关联两个表。
  + 复合键：复合键（组合键）将多个列作为一个索引键，一般用于复合索引。
  + 索引：使用索引可快速访问数据库表中的特定信息。索引是对数据库表中一列或多列的值进行排序的一种结构。类似于书籍的目录。
  + 参照完整性: 参照的完整性要求关系中不允许引用不存在的实体。与实体完整性是关系模型必须满足的完整性约束条件，目的是保证数+ 据的一致性。

## PostgreSQL 特征

+ 函数：通过函数，可以在数据库服务器端执行指令程序。
+ 索引：用户可以自定义索引方法，或使用内置的 B 树，哈希表与 GiST 索引。
+ 触发器：触发器是由SQL语句查询所触发的事件。如：一个INSERT语句可能触发一个检查数据完整性的触发器。触发器通常由INSERT或UPDATE语句触发。 多版本并发控制：PostgreSQL使用多版本并发控制（MVCC，Multiversion concurrency control）系统进行并发控制，该系统向每个用户提供了一个数据库的"快照"，用户在事务内所作的每个修改，对于其他的用户都不可见，直到该事务成功提交。
+ 规则：规则（RULE）允许一个查询能被重写，通常用来实现对视图（VIEW）的操作，如插入（INSERT）、更新（UPDATE）、删除（DELETE）。
+ 数据类型：包括文本、任意精度的数值数组、JSON 数据、枚举类型、XML 数据等。
+ 全文检索：通过 Tsearch2 或 OpenFTS，8.3版本中内嵌 Tsearch2。
+ NoSQL：JSON，JSONB，XML，HStore 原生支持，至 NoSQL 数据库的外部数据包装器。
+ 数据仓库：能平滑迁移至同属 PostgreSQL 生态的 GreenPlum，DeepGreen，HAWK 等，使用 FDW 进行 ETL。

## Linux 上安装 PostgreSQL (Ubuntu 安装 PostgreSQL)

+ Ubuntu 可以使用 apt-get 安装 PostgreSQL：
```bash
sudo apt-get update
sudo apt-get install postgresql postgresql-client
```

+ 安装完毕后，系统会创建一个数据库超级用户 postgres，密码为空。
  + #  sudo -i -u postgres

+ 这时使用以下命令进入 postgres，输出以下信息，说明安装成功：
```bash
~$ psql
psql (9.5.17)
Type "help" for help.

postgres=# 
```
+ 输入以下命令退出 PostgreSQL 提示符：
  + \q

+ PostgreSQL 安装完成后默认是已经启动的，但是也可以通过下面的方式来手动启动服务。
```bash
sudo /etc/init.d/postgresql start   # 开启
sudo /etc/init.d/postgresql stop    # 关闭
sudo /etc/init.d/postgresql restart # 重启
```