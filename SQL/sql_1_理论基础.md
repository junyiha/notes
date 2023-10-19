## 简介

+ sql的相关理论知识

## ODB 详解

ODB（Object-Relational Mapping Database）是一个开源的 C++ 对象关系映射（ORM）工具，用于将 C++ 对象和数据库之间进行映射。它提供了一个简洁的接口和代码生成工具，用于自动生成和维护数据库访问代码。以下是关于 ODB 的一些详解：

1. **定义数据模型**：使用 ODB，你可以使用 C++ 类来定义数据模型。通过在类声明中添加 ODB 注解，你可以指定类和成员变量与数据库表格和字段的映射关系。

   ```cpp
   class Person {
       public:
           // ODB 表格声明
           #pragma db table("people")
           class DbTable {
               public:
                   // ODB 字段声明
                   #pragma db id
                   int id;
                   std::string name;
                   int age;
           };

           // 成员变量与表格字段的映射
           int id;
           std::string name;
           int age;

           // ...
   };
   ```

2. **代码生成工具**：ODB 提供了一个代码生成工具，用于根据定义的数据模型自动生成数据库访问代码。你可以使用 ODB 编译器来处理类定义文件，并生成与数据库交互的代码。

   ```bash
   odb --std c++14 --database sqlite --generate-query --generate-schema Person.hpp
   ```

3. **查询和持久化**：使用 ODB，你可以通过简单的 C++ 语法进行数据库查询和持久化操作。ODB 提供了类型安全的查询接口，支持复杂的查询条件和结果集的处理。

   ```cpp
   odb::query<Person> q(odb::query<Person>::name == "John" && odb::query<Person>::age > 18);
   odb::result<Person> result(db.query<Person>(q));

   for (const auto& person : result) {
       // 处理查询结果
   }

   Person person;
   person.name = "Jane";
   person.age = 25;
   db.persist(person);
   ```

4. **事务处理**：ODB 支持事务操作，你可以使用 `odb::transaction` 对象来管理一系列数据库操作的原子性。

   ```cpp
   {
       odb::transaction txn(db);
       // 执行一系列的数据库操作
       txn.commit(); // 提交事务
   }
   ```

5. **错误处理**：ODB 使用异常来处理错误情况。当出现错误时，它会抛出异常，你可以使用 try-catch 块来捕获并处理这些异常。

   ```cpp
   try {
       // 执行数据库操作
   } catch (const odb::exception& e) {
       // 处理异常
   }
   ```

ODB 提供了详细的文档和示例代码，以帮助你更深入地了解和使用它。你可以在 ODB 的官方网站上找到更多信息：https://www.codesynthesis.com/products/odb/

需要注意的是，ODB 是一个功能强大且全面的 C++ ORM 工具，它提供了许多高级特性和灵活性。使用 ODB 需要一些学习和配置的成本，但它能够显著简化和加速与数据库的交互。

希望这些详解能够帮助你更好地理解和使用 ODB！如果你有更多问题，请随时提问。

## ORMpp 详解

ORMpp 是一个轻量级的 C++ ORM（对象关系映射）库，专为 SQLite3 数据库设计。它提供了简单的接口和注解，用于定义数据模型和数据库关系。以下是关于 ORMpp 的一些详解：

1. **定义数据模型**：使用 ORMpp，你可以使用 C++ 结构体或类来定义数据模型。你可以使用注解来标记成员变量，指定表格名称、字段名称、字段类型和约束等。

   ```cpp
   struct Person {
       ORMPP_ENTITY(Person) // 声明实体

       ORMPP_ID(int, id) // 主键字段
       ORMPP_FIELD(std::string, name) // 字符串字段
       ORMPP_FIELD(int, age) // 整数字段
   };
   ```

2. **数据库迁移**：ORMpp 支持数据库迁移，可以自动创建和更新数据库表格结构。你可以使用 `ormpp::data_migration` 对象来定义表格的创建、修改和删除操作。

   ```cpp
   ormpp::data_migration dm;
   dm.create_table<Person>(); // 创建表格
   dm.add_column<Person>("address", "TEXT"); // 添加字段
   dm.drop_table<Person>(); // 删除表格
   ```

3. **查询构建器**：ORMpp 提供了查询构建器，使得构建 SQL 查询变得更加简单。你可以使用链式方法来构建查询条件、排序和限制。

   ```cpp
   ormpp::sql_query query;
   query.select("*").from<Person>().where(ormpp::c(&Person::age) > 18).order_by("name").limit(10);

   auto results = db.query(query);
   ```

4. **事务处理**：ORMpp 支持事务操作，你可以使用 `ormpp::transaction` 对象来管理一系列数据库操作的原子性。

   ```cpp
   {
       ormpp::transaction txn(db);
       // 执行一系列的数据库操作
       txn.commit(); // 提交事务
   }
   ```

5. **错误处理**：ORMpp 使用异常来处理错误情况。当出现错误时，它会抛出异常，你可以使用 try-catch 块来捕获并处理这些异常。

   ```cpp
   try {
       // 执行数据库操作
   } catch (const std::exception& e) {
       // 处理异常
   }
   ```

ORMpp 提供了清晰的文档和示例代码，以帮助你更详细地了解和使用它。你可以在 ORMpp 的 GitHub 页面上找到更多信息：https://github.com/qicosmos/ormpp

需要注意的是，ORMpp 是一个轻量级的 C++ ORM 库，它在简化 SQLite3 数据库的使用过程中提供了便捷的接口和功能。但在使用之前，你仍然需要熟悉 SQL 查询语句和 SQLite3 数据库的概念。

希望这些详解能够帮助你更好地理解和使用 ORMpp！如果你有更多问题，请随时提问。

## SQLite Modern C++ 详解

SQLite Modern C++ 是一个基于 C++11 的轻量级 SQLite3 封装库，提供了简单而直观的接口，使在 C++ 项目中使用 SQLite3 数据库更加便捷。以下是关于 SQLite Modern C++ 的一些详解：

1. **面向对象接口**：SQLite Modern C++ 提供了面向对象的接口，使用类和方法来操作数据库。你可以创建表格类来表示数据库表格，使用成员变量和方法来操作表格中的数据。

   ```cpp
   // 定义表格类
   struct Person {
       int id;
       std::string name;
       int age;
   };

   // 插入数据
   Person person{1, "John Doe", 25};
   db.insert(person);

   // 查询数据
   auto results = db.select<Person>("SELECT * FROM people");
   for (const auto& person : results) {
       // 处理查询结果
   }
   ```

2. **类型安全**：SQLite Modern C++ 在运行时执行类型检查，确保查询和绑定的类型正确。这可以避免在 SQL 查询中出现类型不匹配的错误。

3. **查询构建器**：SQLite Modern C++ 提供了查询构建器，允许你以链式方式构建 SQL 查询，而不需要手动拼接 SQL 语句。

   ```cpp
   auto query = db
       .select("id", "name")
       .from("people")
       .where("age > ?", 18)
       .order_by("name")
       .limit(10);

   auto results = query.execute();
   ```

4. **事务处理**：SQLite Modern C++ 支持事务操作，你可以使用 `transaction` 对象来管理一系列数据库操作的原子性。

   ```cpp
   {
       transaction txn(db);
       // 执行一系列的数据库操作
       txn.commit(); // 提交事务
   }
   ```

5. **错误处理**：SQLite Modern C++ 使用异常来处理错误情况。当出现错误时，它会抛出异常，你可以使用 try-catch 块来捕获并处理这些异常。

   ```cpp
   try {
       // 执行数据库操作
   } catch (const std::exception& e) {
       // 处理异常
   }
   ```

SQLite Modern C++ 提供了清晰的文档和示例代码，以帮助你更详细地了解和使用它。你可以在 SQLite Modern C++ 的 GitHub 页面上找到更多信息：https://github.com/SqliteModernCpp/sqlite_modern_cpp

需要注意的是，SQLite Modern C++ 是一个轻量级的封装库，它在简化 SQLite3 数据库的使用过程中提供了便捷的接口，但在使用之前，你仍然需要熟悉 SQL 查询语句和 SQLite3 数据库的概念。

希望这些详解能够帮助你更好地理解和使用 SQLite Modern C++！如果你有更多问题，请随时提问。

## SQLite3 ORM 常用第三方库

在 C++ 中，有几个常用的第三方库可用于提供 SQLite3 ORM（对象关系映射）功能。以下是一些常用的 C++ SQLite3 ORM 第三方库：

1. **SQLite Modern C++**：SQLite Modern C++ 是一个轻量级的 C++ 封装库，提供了简单而直观的接口，使得在 C++ 项目中使用 SQLite3 数据库更加便捷。它支持对象关系映射和查询构建器，并提供了对数据库的增删改查操作的封装。

   GitHub 地址：https://github.com/SqliteModernCpp/sqlite_modern_cpp

2. **SQLiteCpp**：SQLiteCpp 是一个基于 C++11 的 SQLite3 封装库，提供了面向对象的接口，使得在 C++ 项目中使用 SQLite3 更加简单和方便。它支持对象关系映射和事务处理，并提供了简洁的 API 来进行数据库操作。

   GitHub 地址：https://github.com/SRombauts/SQLiteCpp

3. **ORMpp**：ORMpp 是一个轻量级的 C++ ORM 库，专为 SQLite3 数据库设计。它提供了简单的接口和注解，用于定义数据模型和数据库关系。ORMpp 支持数据库迁移、查询构建器和事务处理等功能。

   GitHub 地址：https://github.com/iansimon/ormpp

4. **Qt SQL**：Qt 是一个功能强大的 C++ 框架，其中的 Qt SQL 模块提供了对各种数据库的访问功能，包括 SQLite3。使用 Qt SQL，你可以通过对象关系映射和查询构建器来操作 SQLite3 数据库。

   官方网站：https://www.qt.io/

这些库都可以帮助你在 C++ 中使用 SQLite3 数据库，并提供了不同程度的 ORM 功能。你可以根据项目需求、库的易用性和适配性来选择最适合的库。

需要注意的是，这些库都是第三方工具，你需要根据你的项目要求和预期的功能选择适合的库，并仔细阅读它们的文档和示例代码以了解如何使用它们。

希望这些信息对你有帮助！如有更多问题，请随时提问。

## C++ REST SDK 详解

C++ REST SDK（又称为 Casablanca）是一个功能强大的 C++ 库，用于构建基于 HTTP 的客户端和服务器应用程序。它提供了一组丰富的功能和工具，用于处理网络请求、JSON 解析、异步任务等。以下是关于 C++ REST SDK 的一些详解：

1. **HTTP 客户端**：C++ REST SDK 提供了一个强大的 HTTP 客户端库，用于发送和接收 HTTP 请求和响应。你可以通过创建 `http_client` 对象，指定请求的 URI、方法、头部、消息正文等来发起 HTTP 请求。

   ```cpp
   web::http::client::http_client client(U("http://example.com"));
   web::http::http_response response = client.request(web::http::methods::GET).get();
   ```

2. **HTTP 服务器**：C++ REST SDK 允许你创建基于 HTTP 的服务器应用程序。你可以创建一个 `http_listener` 对象，并为特定的 URI 和方法注册处理程序来处理传入的请求。

   ```cpp
   web::http::experimental::listener::http_listener listener(U("http://localhost:8080"));
   listener.support(web::http::methods::GET, [](web::http::http_request request) {
       // 处理 GET 请求
   });
   listener.open().wait();
   ```

3. **异步任务和并发**：C++ REST SDK 使用异步任务模型来处理并发操作。它提供了 `pplx::task` 类，用于处理异步操作和等待任务完成。

   ```cpp
   pplx::task<std::string> task = client.request(web::http::methods::GET).then([](web::http::http_response response) {
       return response.extract_string();
   });

   task.then([](const std::string& content) {
       // 处理异步任务结果
   }).wait();
   ```

4. **JSON 解析和序列化**：C++ REST SDK 提供了用于解析和序列化 JSON 数据的工具。你可以使用 `web::json::value` 类来表示和操作 JSON 对象和数组。

   ```cpp
   web::json::value json;
   json[U("name")] = web::json::value::string(U("John"));
   json[U("age")] = web::json::value::number(25);

   web::json::value::string_t name = json[U("name")].as_string();
   int age = json[U("age")].as_integer();
   ```

5. **其他功能**：C++ REST SDK 还提供了许多其他功能，如支持 HTTPS、网络代理、cookie 管理、身份验证等。

C++ REST SDK 的 GitHub 页面提供了详细的文档和示例代码，以帮助你更深入地了解和使用它：https://github.com/microsoft/cpprestsdk

C++ REST SDK 是一个强大而全面的库，适用于构建基于 HTTP 的客户端和服务器应用程序。它可以帮助你轻松处理网络请求、JSON 数据和异步操作。

希望这些详解能够帮助你更好地理解和使用 C++ REST SDK！如果你有更多问题，请随时提问。

## OTL 详解

OTL（OCCI Template Library）是一个用于 C++ 的通用数据库访问库，它提供了高性能和灵活的接口，用于访问多种数据库。以下是关于 OTL 的一些详解：

1. **支持多种数据库**：OTL 支持多种常见的数据库系统，包括 Oracle、Microsoft SQL Server、IBM DB2、MySQL、PostgreSQL 等。你可以使用相同的接口和代码来访问不同类型的数据库，而不需要学习和使用特定数据库的 API。

2. **面向对象接口**：OTL 提供了面向对象的接口，通过类和方法来操作数据库。它使用了现代 C++ 特性，如模板和 RAII（资源获取即初始化），使得代码更加清晰和易于维护。

3. **连接管理**：使用 OTL，你可以通过提供连接字符串来建立和管理与数据库的连接。连接字符串包括数据库类型、主机名、端口号、用户名、密码等信息。

   ```cpp
   otl_connect db;
   db.rlogon("username/password@tnsname");
   ```

4. **查询执行**：使用 OTL，你可以通过编写 SQL 查询语句来与数据库进行交互。你可以直接执行原始的 SQL 语句，也可以使用绑定变量和查询构建器来构建和执行查询。

   ```cpp
   otl_stream stream;
   stream.open(1, "SELECT name, age FROM users WHERE age > :age", db);
   stream << 18;
   
   while (!stream.eof()) {
       std::string name;
       int age;
       stream >> name >> age;
       
       // 处理查询结果
   }
   ```

5. **事务处理**：OTL 支持事务操作，你可以使用事务对象来管理一系列数据库操作的原子性。

   ```cpp
   otl_trans transaction(db);

   // 执行一系列的数据库操作

   transaction.commit();
   ```

6. **错误处理**：OTL 使用异常来处理错误情况。当出现错误时，它会抛出相应的异常，你可以使用 try-catch 块来捕获并处理这些异常。

   ```cpp
   try {
       // 执行数据库操作
   } catch (otl_exception& ex) {
       // 处理异常
   }
   ```

7. **灵活性和可扩展性**：OTL 具有灵活和可扩展的架构，你可以通过编写自定义的 OTL 数据库后端适配器来支持其他数据库系统。

OTL 提供了详细的文档和示例代码，以帮助你更深入地了解和使用它。你可以在 OTL 的官方网站上找到更多信息：http://otl.sourceforge.net/

需要注意的是，OTL 是一个相对底层的库，使用它需要对 SQL 查询语句和数据库概念有一定的了解。

希望这些详解能够帮助你更好地理解和使用 OTL！如果你有更多问题，请随时提问。

## SOCI 详解

SOCI（The C++ Database Access Library）是一个通用的数据库访问库，它提供了简单和一致的接口，用于在 C++ 中访问多种不同类型的数据库。下面是关于 SOCI 的一些详解：

1. **支持多种数据库**：SOCI 支持多种常见的数据库系统，包括 SQLite、MySQL、PostgreSQL、Oracle、ODBC 等。你可以使用相同的接口和代码来访问不同类型的数据库，而不需要学习和使用特定数据库的 API。

2. **面向对象接口**：SOCI 提供了面向对象的接口，通过类和方法来操作数据库。它使用了现代 C++ 特性，如模板和 RAII（资源获取即初始化），使得代码更加清晰和易于维护。

3. **连接管理**：使用 SOCI，你可以通过提供连接字符串来建立和管理与数据库的连接。连接字符串包括数据库类型、主机名、端口号、用户名、密码等信息。

   ```cpp
   soci::session sql("mysql://user:password@localhost/mydatabase");
   ```

4. **查询执行**：使用 SOCI，你可以通过编写 SQL 查询语句来与数据库进行交互。你可以直接执行原始的 SQL 语句，也可以使用绑定变量和查询构建器来构建和执行查询。

   ```cpp
   soci::rowset<row> rs = (sql.prepare << "SELECT name, age FROM users WHERE age > :age", soci::use(18));
   
   for (const auto& r : rs) {
       std::string name;
       int age;
       r.get<0>(name);
       r.get<1>(age);
       
       // 处理查询结果
   }
   ```

5. **事务处理**：SOCI 支持事务操作，你可以使用事务对象来管理一系列数据库操作的原子性。

   ```cpp
   soci::transaction tr(sql);

   // 执行一系列的数据库操作

   tr.commit(); // 提交事务
   ```

6. **错误处理**：SOCI 使用异常来处理错误情况。当出现错误时，它会抛出相应的异常，你可以使用 try-catch 块来捕获并处理这些异常。

   ```cpp
   try {
       // 执行数据库操作
   } catch (const soci::soci_error& e) {
       // 处理异常
   }
   ```

7. **灵活性和可扩展性**：SOCI 具有灵活和可扩展的架构，你可以通过编写自定义后端适配器来支持其他数据库系统。

SOCI 提供了丰富的文档和示例代码，以帮助你更详细地了解和使用它。你可以在 SOCI 的官方网站上找到更多信息：http://soci.sourceforge.net/

需要注意的是，SOCI 是一个相对底层的库，使用它需要对 SQL 查询语句和数据库概念有一定的了解。

希望这些详解能够帮助你更好地理解和使用 SOCI！如果你有更多问题，请随时提问。

## sqlitecpp 详解

SQLiteCpp 是一个在 C++ 中使用 SQLite 数据库的轻量级封装库。它提供了简单且直观的面向对象的接口，使得在 C++ 项目中使用 SQLite 数据库更加便捷。

以下是 SQLiteCpp 的一些主要特点和用法的详解：

1. **面向对象接口**：SQLiteCpp 提供了一个面向对象的接口，通过类和方法来操作数据库。它使用了现代 C++ 特性，如 RAII（资源获取即初始化）和异常处理，使得代码更加清晰和易于维护。

2. **数据库连接**：使用 SQLite::Database 类可以创建和管理与 SQLite 数据库的连接。你可以通过指定数据库文件的路径来打开数据库连接，也可以使用内存数据库。

   ```cpp
   SQLite::Database db("example.db"); // 打开名为 "example.db" 的数据库文件连接
   ```

3. **查询执行**：你可以使用 SQLite::Statement 类执行 SQL 查询语句，并通过绑定参数和读取结果集来与数据库交互。

   ```cpp
   SQLite::Statement query(db, "SELECT * FROM users WHERE age > ?");
   query.bind(1, 18);

   while (query.executeStep()) {
       std::string name = query.getColumn(1);
       int age = query.getColumn(2);

       // 处理查询结果
   }
   ```

4. **事务处理**：SQLiteCpp 支持事务操作，通过 SQLite::Transaction 类可以实现简单的事务控制，保证一系列的数据库操作的原子性。

   ```cpp
   SQLite::Transaction transaction(db);

   // 执行一系列的数据库操作

   transaction.commit(); // 提交事务
   ```

5. **数据库操作**：SQLiteCpp 提供了许多便捷的方法来执行数据库操作，包括插入、更新、删除等。

   ```cpp
   SQLite::Statement insert(db, "INSERT INTO users (name, age) VALUES (?, ?)");
   insert.bind(1, "John Doe");
   insert.bind(2, 25);
   insert.exec(); // 执行插入操作
   ```

6. **错误处理**：SQLiteCpp 在出现错误时会抛出异常，你可以使用 try-catch 块来捕获并处理这些异常。

   ```cpp
   try {
       // 执行数据库操作
   } catch (std::exception& e) {
       // 处理异常
   }
   ```

SQLiteCpp 提供了丰富的文档和示例代码，以帮助你更详细地了解和使用它。你可以在它的 GitHub 页面上找到更多信息：https://github.com/SRombauts/SQLiteCpp

需要注意的是，尽管 SQLiteCpp 简化了在 C++ 中使用 SQLite 数据库的过程，你仍然需要熟悉 SQL 查询语句和 SQLite 数据库的概念。

希望这些详解能够帮助你更好地理解和使用 SQLiteCpp！如果你有更多问题，请随时提问。

## sqlite3 orm 第三方工具 推荐

在 C++ 中，有几个流行的第三方工具可用于提供 SQLite3 ORM（对象关系映射）功能。以下是一些常用的 C++ SQLite3 ORM 第三方库：

1. SQLiteCpp：SQLiteCpp 是一个轻量级的 C++ 封装库，提供了对 SQLite 数据库的面向对象访问接口。它使用现代 C++ 特性，简化了与 SQLite 数据库的交互，支持查询构建、事务处理等功能。

   GitHub 地址：https://github.com/SRombauts/SQLiteCpp

2. SOCI：SOCI 是一个通用的数据库访问库，支持多种数据库，包括 SQLite。它提供了面向对象的接口，可以简化数据库操作，包括查询、插入、更新等。

   GitHub 地址：https://github.com/SOCI/soci

3. OTL：OTL（OCCI Template Library）是一个通用的数据库访问库，也支持 SQLite 数据库。它提供了面向对象的接口，支持事务处理、预编译语句等功能。

   官方网站：http://otl.sourceforge.net/

4. C++ REST SDK：C++ REST SDK 是一个功能强大的 C++ 库，提供了丰富的功能，包括 HTTP 客户端/服务器、JSON 解析、异步任务等。它也提供了对 SQLite 数据库的支持，可以用作 ORM。

   GitHub 地址：https://github.com/microsoft/cpprestsdk

这些库都可以帮助你在 C++ 中使用 SQLite3 数据库，并提供了不同程度的 ORM 功能。你可以根据项目的需求、库的易用性和适配性来选择最适合的库。

需要注意的是，这些库都是第三方工具，你需要根据你的项目要求和预期的功能选择适合的库，并仔细阅读它们的文档和示例代码以了解如何使用它们。

希望这些推荐对你有所帮助！如有更多问题，请随时提问。

## sql语法和mysql 关系

SQL（Structured Query Language）是一种用于管理关系型数据库系统的编程语言。它提供了一套标准化的语法和操作，用于查询、操作和管理数据库中的数据。MySQL是一个开源的关系型数据库管理系统（RDBMS），它支持使用SQL语言进行数据库操作。

SQL语法定义了一组规则和约定，用于编写查询和操作数据库的语句。它包括以下几个主要方面：

1. 数据定义语言（DDL）：DDL用于定义数据库的结构和模式。它包括创建数据库、创建表、定义表的列和约束等操作。例如，使用DDL语句可以创建一个名为"employees"的表，定义其列和数据类型：

   ```sql
   CREATE TABLE employees (
       id INT PRIMARY KEY,
       name VARCHAR(50),
       age INT,
       salary DECIMAL(10, 2)
   );
   ```

2. 数据操作语言（DML）：DML用于插入、更新和删除数据库中的数据。它包括INSERT、UPDATE和DELETE语句，用于执行相应的操作。例如，使用DML语句可以向"employees"表中插入一条新记录：

   ```sql
   INSERT INTO employees (id, name, age, salary)
   VALUES (1, 'John Doe', 30, 50000);
   ```

3. 数据查询语言（DQL）：DQL用于从数据库中检索数据。它包括SELECT语句，用于查询和过滤数据。例如，使用DQL语句可以查询"employees"表中年龄大于等于25岁的员工：

   ```sql
   SELECT * FROM employees WHERE age >= 25;
   ```

4. 数据控制语言（DCL）：DCL用于控制数据库用户的访问权限和安全性。它包括GRANT和REVOKE语句，用于授予和撤销用户的权限。例如，使用DCL语句可以授予用户"john"对"employees"表的SELECT权限：

   ```sql
   GRANT SELECT ON employees TO john;
   ```

MySQL是一个流行的关系型数据库管理系统，它实现了SQL语言标准，并提供了额外的功能和扩展。MySQL支持大多数SQL语法的标准化操作，如DDL、DML、DQL和DCL。通过MySQL，你可以创建和管理数据库，创建表和索引，执行查询和数据操作，以及控制用户的权限。

总而言之，SQL是一种用于管理关系型数据库的标准化语言，而MySQL是一个实现了SQL标准的关系型数据库管理系统。通过使用SQL语法，你可以在MySQL数据库中执行各种操作，包括创建和定义数据库结构、插入、更新和删除数据，以及查询和检索数据。

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