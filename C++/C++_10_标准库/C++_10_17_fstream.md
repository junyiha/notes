## 简介

+ C++ <fstream>标准库

## C++ <fstream>标准库

在 C++ 中，`<fstream>` 是标准库中用于文件输入和输出的头文件。它提供了用于操作文件的类和函数，允许你以输入和输出的方式处理文件数据。

这个头文件定义了三个主要的类：

1. `std::ifstream`: 用于从文件中读取数据（输入文件流）。
2. `std::ofstream`: 用于向文件写入数据（输出文件流）。
3. `std::fstream`: 用于读写文件（输入输出文件流）。

这些类都继承自 `std::istream`（用于输入）或 `std::ostream`（用于输出），因此它们具有类似于 `std::cin` 和 `std::cout` 的功能。

以下是一个简单的示例，展示了如何使用 `<fstream>` 头文件中的 `std::ifstream` 和 `std::ofstream` 类来读取和写入文件：

```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ofstream outputFile("output.txt"); // 创建一个输出文件流对象

    if (outputFile.is_open()) {
        outputFile << "Writing this to a file.\n";
        outputFile.close(); // 关闭文件流
    } else {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return 1;
    }

    std::ifstream inputFile("output.txt"); // 创建一个输入文件流对象

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) { // 逐行读取文件内容
            std::cout << line << std::endl; // 输出到控制台
        }
        inputFile.close(); // 关闭文件流
    } else {
        std::cerr << "Unable to open file for reading!" << std::endl;
        return 1;
    }

    return 0;
}
```

在这个示例中，首先使用 `std::ofstream` 打开一个文件输出流，并向文件 "output.txt" 写入一行数据。接着使用 `std::ifstream` 打开相同的文件作为输入流，并使用 `std::getline` 逐行读取文件内容，并输出到控制台。

这些文件流类提供了许多其他的功能，比如定位到文件特定位置、判断文件是否打开、错误处理等，可以根据需要在程序中使用。

## C++ <fstream>标准库 常用类和函数

在 C++ 的 `<fstream>` 标准库中，常用的类和函数用于文件的输入和输出操作。以下是一些常用的类和函数：

### 常用类：

1. **`std::ifstream`**：
   - 用于从文件中读取数据的输入文件流类。
   - 示例：
     ```cpp
     std::ifstream inputFile("filename.txt");
     ```

2. **`std::ofstream`**：
   - 用于向文件写入数据的输出文件流类。
   - 示例：
     ```cpp
     std::ofstream outputFile("filename.txt");
     ```

3. **`std::fstream`**：
   - 用于同时进行文件读写操作的输入输出文件流类。
   - 示例：
     ```cpp
     std::fstream file("filename.txt");
     ```

### 常用函数：

1. **`open()`**：
   - 打开文件，可以指定文件名和打开模式。
   - 示例：
     ```cpp
     std::ifstream inputFile;
     inputFile.open("filename.txt");
     ```

2. **`close()`**：
   - 关闭文件。
   - 示例：
     ```cpp
     inputFile.close();
     ```

3. **`is_open()`**：
   - 检查文件是否打开。
   - 示例：
     ```cpp
     if (inputFile.is_open()) {
         // 文件已打开
     }
     ```

4. **`operator<<` 和 `operator>>`**：
   - 用于向文件写入数据和从文件读取数据。
   - 示例：
     ```cpp
     outputFile << "Writing to file\n";
     inputFile >> data;
     ```

5. **`getline()`**：
   - 从文件中逐行读取数据。
   - 示例：
     ```cpp
     std::string line;
     while (std::getline(inputFile, line)) {
         // 处理每一行数据
     }
     ```

6. **`tellg()` 和 `seekg()`**（对于 `std::fstream`）：
   - `tellg()` 返回当前文件指针的位置。
   - `seekg()` 设置文件指针到指定位置。
   - 示例：
     ```cpp
     inputFile.seekg(0, std::ios::beg); // 将文件指针移至文件开头
     std::streampos position = inputFile.tellg(); // 获取当前文件指针位置
     ```

这些是 `<fstream>` 头文件中最常用的类和函数。它们提供了强大的功能，允许你对文件进行读写操作，并且具有一些用于定位、判断文件状态、格式化输入输出等额外的功能。

## std::ifstream

`std::ifstream` 是 C++ 标准库中的类，用于从文件中读取数据。它是 `std::istream` 的派生类，提供了用于从文件读取数据的功能。

### 创建 `std::ifstream` 对象：

```cpp
#include <fstream>

int main() {
    std::ifstream inputFile("filename.txt");
    
    if (inputFile.is_open()) {
        // 文件已成功打开
        // 可以使用 inputFile 对象进行读取操作
    } else {
        // 文件打开失败
    }
    
    inputFile.close(); // 关闭文件
    return 0;
}
```

### 主要方法和功能：

1. **`open()`**：用于打开文件，可以指定文件名和打开模式。

    ```cpp
    std::ifstream inputFile;
    inputFile.open("filename.txt");
    ```

2. **`is_open()`**：检查文件是否成功打开。

    ```cpp
    if (inputFile.is_open()) {
        // 文件已打开
    }
    ```

3. **`close()`**：关闭文件。

    ```cpp
    inputFile.close();
    ```

4. **`operator>>`**：从文件中读取数据。

    ```cpp
    int data;
    inputFile >> data;
    ```

5. **`getline()`**：从文件中逐行读取数据。

    ```cpp
    std::string line;
    while (std::getline(inputFile, line)) {
        // 处理每一行数据
    }
    ```

6. **`tellg()` 和 `seekg()`**：用于获取和设置文件指针位置（对于 `std::ifstream` ）。

    ```cpp
    inputFile.seekg(0, std::ios::beg); // 将文件指针移至文件开头
    std::streampos position = inputFile.tellg(); // 获取当前文件指针位置
    ```

`std::ifstream` 允许你打开一个文件以供读取数据，并提供了许多方法来从文件中读取数据，包括按字节、按行等不同方式，使得文件读取操作非常灵活。

## std::ofstream

`std::ofstream` 是 C++ 标准库中的类，用于向文件中写入数据。它是 `std::ostream` 的派生类，提供了向文件写入数据的功能。

### 创建 `std::ofstream` 对象：

```cpp
#include <fstream>

int main() {
    std::ofstream outputFile("filename.txt");
    
    if (outputFile.is_open()) {
        // 文件已成功打开
        // 可以使用 outputFile 对象进行写入操作
    } else {
        // 文件打开失败
    }
    
    outputFile.close(); // 关闭文件
    return 0;
}
```

### 主要方法和功能：

1. **`open()`**：用于打开文件，可以指定文件名和打开模式。

    ```cpp
    std::ofstream outputFile;
    outputFile.open("filename.txt");
    ```

2. **`is_open()`**：检查文件是否成功打开。

    ```cpp
    if (outputFile.is_open()) {
        // 文件已打开
    }
    ```

3. **`close()`**：关闭文件。

    ```cpp
    outputFile.close();
    ```

4. **`operator<<`**：向文件中写入数据。

    ```cpp
    outputFile << "Writing this to the file.\n";
    ```

`std::ofstream` 允许你打开一个文件以供写入数据，并提供了 `operator<<` 等方法来向文件中写入数据。你可以使用这些方法将数据以文本或二进制形式写入文件中，完成各种文件写入操作。

## std::fstream

`std::fstream` 是 C++ 标准库中的类，用于对文件进行读写操作。它是 `std::iostream` 的派生类，同时具有读取和写入文件的能力。

### 创建 `std::fstream` 对象：

```cpp
#include <fstream>

int main() {
    std::fstream file("filename.txt", std::ios::in | std::ios::out);
    
    if (file.is_open()) {
        // 文件已成功打开
        // 可以使用 file 对象进行读写操作
    } else {
        // 文件打开失败
    }
    
    file.close(); // 关闭文件
    return 0;
}
```

### 主要方法和功能：

1. **`open()`**：用于打开文件，可以指定文件名和打开模式。

    ```cpp
    std::fstream file;
    file.open("filename.txt", std::ios::in | std::ios::out);
    ```

    - `std::ios::in`：以读取模式打开文件。
    - `std::ios::out`：以写入模式打开文件。
    - `std::ios::app`：在文件末尾追加数据。

2. **`is_open()`**：检查文件是否成功打开。

    ```cpp
    if (file.is_open()) {
        // 文件已打开
    }
    ```

3. **`close()`**：关闭文件。

    ```cpp
    file.close();
    ```

4. **`operator<<` 和 `operator>>`**：用于向文件写入数据和从文件读取数据。

    ```cpp
    file << "Writing to file\n";
    int data;
    file >> data;
    ```

5. **`seekg()` 和 `tellg()`** 和 **`seekp()` 和 `tellp()`**：用于获取和设置文件指针位置。

    - 对于输入位置（`get`）：
        ```cpp
        file.seekg(0, std::ios::beg); // 将文件指针移至文件开头
        std::streampos position = file.tellg(); // 获取当前文件指针位置
        ```

    - 对于输出位置（`put`）：
        ```cpp
        file.seekp(0, std::ios::beg); // 将文件指针移至文件开头
        std::streampos position = file.tellp(); // 获取当前文件指针位置
        ```

`std::fstream` 可以用于同时进行文件读取和写入操作，提供了一些类似 `std::ifstream` 和 `std::ofstream` 的方法和功能，可以更灵活地对文件进行操作。

## std::fstream::open() 

`std::fstream::open()` 是 C++ 标准库 `<fstream>` 头文件中 `std::fstream` 类的成员函数之一。它用于打开文件并将其与 `std::fstream` 对象关联，从而允许对文件进行读取或写入操作。

这是 `std::fstream::open()` 的基本语法：

```cpp
#include <fstream>

int main() {
    std::fstream fileStream;

    // 打开一个文件进行输入/输出操作
    fileStream.open("filename.txt", std::ios::in | std::ios::out);

    if (fileStream.is_open()) {
        // 文件成功打开，执行操作
        // ...

        // 完成操作后关闭文件
        fileStream.close();
    } else {
        // 未能打开文件，处理错误
        // ...
    }

    return 0;
}
```

`open()` 中使用的参数解释：

- `"filename.txt"` 是要打开的文件名。
- `std::ios::in` 指定文件将用于输入操作。
- `std::ios::out` 指定文件将用于输出操作。
- `std::ios::in | std::ios::out` 是一个示例，使用按位 OR 运算符结合这些标志，允许在文件上进行输入和输出操作。根据所需的文件访问模式，可以使用其他标志（例如 `std::ios::app`、`std::ios::binary` 等）。

在执行任何读取或写入操作之前，请确保使用 `is_open()` 检查文件是否成功打开。另外，在对文件执行操作后，最好使用 `close()` 成员函数关闭文件，以释放与文件关联的资源。

此外，应实现错误处理来处理无法打开文件的情况，例如文件不存在或程序没有足够的权限访问文件等情况。

## std::ios

`std::ios` 是 C++ 标准库中定义的一个位掩码枚举类型，用于指定流的状态和控制流的行为。它提供了一系列常量，用于在文件流或内存流中指定不同的行为和状态。

这些常量通常与流类（比如 `std::ifstream`、`std::ofstream`、`std::fstream` 等）的成员函数一起使用，例如 `open()`、`close()` 等。

以下是一些 `std::ios` 类型的常量：

- `std::ios::in`：用于输入操作，允许从流中读取数据。
- `std::ios::out`：用于输出操作，允许向流中写入数据。
- `std::ios::binary`：指定以二进制模式打开文件，用于处理二进制数据。
- `std::ios::ate`：在打开文件时将文件指针移到文件末尾。
- `std::ios::app`：在打开文件时将文件指针移到文件末尾，并在写入时将数据追加到文件末尾。
- `std::ios::trunc`：如果文件已经存在，打开时将文件截断为零长度。

这些常量可以通过按位 OR 运算符结合使用，以同时指定多个流状态。例如：

```cpp
#include <fstream>

int main() {
    std::ofstream fileStream;

    // 打开文件进行输出操作，并在文件末尾追加数据
    fileStream.open("filename.txt", std::ios::out | std::ios::app);

    if (fileStream.is_open()) {
        // 文件成功打开，执行操作
        // ...

        // 完成操作后关闭文件
        fileStream.close();
    } else {
        // 未能打开文件，处理错误
        // ...
    }

    return 0;
}
```

这里，`std::ios::out | std::ios::app` 将打开文件以允许输出操作，并在文件末尾追加数据。

`std::ios` 类型提供了灵活的控制和配置流的能力，可以根据需要组合使用这些常量，以满足特定的文件读写需求。

## std::fstream::close()

`std::fstream::close()` 是 C++ 标准库中 `std::fstream` 类的成员函数之一。它用于关闭先前由 `std::fstream::open()` 打开的文件。

在对文件执行读取或写入操作后，通常应使用 `std::fstream::close()` 函数来关闭文件，以释放与该文件关联的资源并确保对文件所做的更改被保存。关闭文件可以防止数据丢失或文件损坏，并允许其他程序或进程访问该文件。

以下是 `std::fstream::close()` 的使用示例：

```cpp
#include <fstream>
#include <iostream>

int main() {
    std::fstream fileStream;

    // 打开文件进行读取/写入操作
    fileStream.open("filename.txt", std::ios::in | std::ios::out);

    if (fileStream.is_open()) {
        // 文件成功打开，执行读取/写入操作
        fileStream << "Hello, File!"; // 写入数据到文件
        // ...

        // 关闭文件
        fileStream.close();
        std::cout << "File closed." << std::endl;
    } else {
        // 未能打开文件，处理错误
        std::cout << "Failed to open the file." << std::endl;
    }

    return 0;
}
```

在上述示例中，`std::fstream::close()` 在操作文件后调用，以关闭先前打开的文件。在关闭文件之前，任何对文件的操作都应该完成，以确保数据正确地写入文件。当文件不再需要时，最好及时关闭文件。

关闭文件的操作是一个良好的编程实践，有助于避免资源泄漏并确保文件的正确处理。

## std::fstream::is_open()

`std::fstream::is_open()` 是 `std::fstream` 类的成员函数之一，用于检查与 `std::fstream` 对象关联的文件是否成功打开。该函数返回一个 `bool` 类型的值，指示文件是否已打开。

以下是 `std::fstream::is_open()` 的基本用法示例：

```cpp
#include <fstream>
#include <iostream>

int main() {
    std::fstream fileStream;

    // 尝试打开文件进行读取/写入操作
    fileStream.open("filename.txt", std::ios::in | std::ios::out);

    if (fileStream.is_open()) {
        // 文件成功打开，执行读取/写入操作
        std::cout << "File is open." << std::endl;

        // ...

        // 关闭文件
        fileStream.close();
    } else {
        // 未能打开文件，处理错误
        std::cout << "Failed to open the file." << std::endl;
    }

    return 0;
}
```

在这个示例中，`std::fstream::is_open()` 用于检查文件是否成功打开。如果文件成功打开，则输出 `"File is open."`，否则输出 `"Failed to open the file."`。这可以帮助您在执行读取或写入操作之前检查文件是否已正确打开，以避免在无法访问文件的情况下执行文件操作。

使用 `std::fstream::is_open()` 是一种良好的实践，可用于确保文件已正确打开并准备接受读取或写入操作。

## std::fstream::operator<<

`std::fstream::operator<<` 是用于向文件流 (`std::fstream`) 写入数据的操作符重载。它允许像使用 `<<` 操作符一样向文件中写入数据，类似于向 `std::cout` 输出流中写入数据一样。

这个操作符重载通常与文件流对象一起使用，允许将各种类型的数据写入到已打开的文件中。

以下是一个简单的示例，演示了如何使用 `std::fstream::operator<<` 将数据写入文件：

```cpp
#include <fstream>
#include <iostream>

int main() {
    std::ofstream fileStream; // 使用 ofstream，但也可以使用 fstream

    fileStream.open("output.txt"); // 打开文件进行写入操作

    if (fileStream.is_open()) {
        int number = 42;
        double pi = 3.14159;
        std::string message = "Hello, File!";

        // 向文件写入数据
        fileStream << "An integer: " << number << std::endl;
        fileStream << "A double: " << pi << std::endl;
        fileStream << "A message: " << message << std::endl;

        std::cout << "Data written to file." << std::endl;

        // 关闭文件
        fileStream.close();
    } else {
        std::cout << "Failed to open the file." << std::endl;
    }

    return 0;
}
```

在这个示例中，`fileStream << "An integer: " << number << std::endl;` 将整数、浮点数和字符串写入了文件中。`<<` 操作符被用于串联不同类型的数据，并将它们写入到打开的文件流中。`std::endl` 用于在文件中插入换行符。

请注意，在使用 `std::fstream::operator<<` 之前，确保文件已经成功打开，并且操作完毕后，记得关闭文件流以释放资源。

## std::fstream::operator>>

`std::fstream::operator>>` 是 C++ 标准库中 `std::fstream` 类的成员函数之一，用于文件流的输入操作。它允许从文件流中读取数据，类似于从标准输入流 `std::cin` 中读取数据。

这个操作符重载通常用于从已打开的文件中读取数据，并根据不同的数据类型进行提取。它可以和 `std::ifstream` 或 `std::fstream` 对象一起使用，允许从文件中读取各种类型的数据。

以下是一个示例，演示了如何使用 `std::fstream::operator>>` 从文件中读取数据：

```cpp
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream fileStream; // 使用 ifstream 进行输入操作

    fileStream.open("input.txt"); // 打开文件进行读取

    if (fileStream.is_open()) {
        int number;
        double pi;
        std::string message;

        // 从文件中读取数据
        fileStream >> number >> pi >> message;

        // 显示从文件中读取的数据
        std::cout << "Number: " << number << std::endl;
        std::cout << "Pi: " << pi << std::endl;
        std::cout << "Message: " << message << std::endl;

        // 读取完成后关闭文件
        fileStream.close();
    } else {
        std::cout << "无法打开文件。" << std::endl;
    }

    return 0;
}
```

在这个示例中，`operator>>` 用于从文件流 (`fileStream`) 中提取整数、浮点数和字符串，并将它们存储到相应的变量中（`number`、`pi`、`message`）。然后，它将从文件中提取的数据显示在控制台上。

请确保在尝试从文件中读取数据之前，文件已经成功打开，并在读取完成后关闭文件流，释放相关资源。

## std::fstream::getline()

`std::fstream::getline()` 是 `std::fstream` 类的成员函数之一，用于从文件中逐行读取数据并将其存储到字符串中。

这个函数通常与 `std::ifstream` 或 `std::fstream` 对象一起使用，用于从文件中读取文本数据，并将每行数据存储到字符串中。

以下是一个示例，演示了如何使用 `std::fstream::getline()` 从文件中逐行读取数据：

```cpp
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream fileStream; // 使用 ifstream 进行输入操作

    fileStream.open("input.txt"); // 打开文件进行读取

    if (fileStream.is_open()) {
        std::string line;

        // 逐行读取文件中的数据
        while (std::getline(fileStream, line)) {
            // 处理每行读取的数据
            std::cout << "Line read: " << line << std::endl;
        }

        // 读取完成后关闭文件
        fileStream.close();
    } else {
        std::cout << "无法打开文件。" << std::endl;
    }

    return 0;
}
```

在这个示例中，`std::fstream::getline()` 用于从文件流 (`fileStream`) 中逐行读取数据，并将每行数据存储在名为 `line` 的字符串中。然后，每次读取一行后，它将该行数据显示在控制台上。

这是一个非常常用的方法，特别是当需要按行读取文本文件中的内容时。每次调用 `getline()` 函数时，它会读取文件的下一行，并将其存储到字符串中，直到文件结束或发生读取错误为止。

请确保文件已成功打开，并在读取完成后关闭文件流，以便释放相关资源。

## std::fstream::tellg()

`std::fstream::tellg()` 是 `std::fstream` 类的成员函数之一，用于返回当前文件读取位置的位置指针（stream position pointer）。

在 C++ 中，文件流有一个位置指针，用于标识当前读取或写入操作在文件中的位置。`tellg()` 用于获取当前位置指针的位置（以字节为单位），它返回一个 `std::streampos` 类型的值，表示文件流中当前的位置。

以下是一个示例，演示了如何使用 `std::fstream::tellg()` 来获取当前文件读取位置：

```cpp
#include <fstream>
#include <iostream>

int main() {
    std::ifstream fileStream; // 使用 ifstream 进行输入操作

    fileStream.open("input.txt", std::ios::ate); // 打开文件并将文件指针移到文件末尾

    if (fileStream.is_open()) {
        // 获取当前文件指针位置
        std::streampos position = fileStream.tellg();

        std::cout << "Current position in the file: " << position << " bytes." << std::endl;

        // 关闭文件
        fileStream.close();
    } else {
        std::cout << "无法打开文件。" << std::endl;
    }

    return 0;
}
```

在这个示例中，`std::fstream::tellg()` 被调用以获取当前文件读取位置。`std::ios::ate` 标志用于在打开文件时将文件指针移到文件末尾。获取位置指针后，它以字节为单位输出当前的文件指针位置。

请注意，在使用 `tellg()` 之前，通常会使用适当的打开模式打开文件，以便能够获取有效的位置。这个函数通常与其他文件定位和操作函数一起使用，用于了解当前的文件读取位置。

## std::fstream::seekg()

`std::fstream::seekg()` 是 `std::fstream` 类的成员函数之一，用于在文件流中定位读取位置。这个函数用于设置文件读取位置指针（stream position pointer）的位置，允许在文件中移动到特定的位置进行读取操作。

它有多种重载形式，允许您以不同的方式定位文件流的读取位置。一般情况下，它使用相对于某个位置的偏移量来移动文件读取位置指针。

以下是一个示例，演示了如何使用 `std::fstream::seekg()` 在文件中定位读取位置：

```cpp
#include <fstream>
#include <iostream>

int main() {
    std::ifstream fileStream; // 使用 ifstream 进行输入操作

    fileStream.open("input.txt"); // 打开文件进行读取

    if (fileStream.is_open()) {
        // 移动文件读取位置指针到文件的第 10 个字节处（偏移量为 10）
        fileStream.seekg(10);

        // 读取并显示从当前位置开始的文件内容
        char ch;
        while (fileStream.get(ch)) {
            std::cout << ch;
        }

        // 关闭文件
        fileStream.close();
    } else {
        std::cout << "无法打开文件。" << std::endl;
    }

    return 0;
}
```

在这个示例中，`std::fstream::seekg(10)` 将文件读取位置指针移动到文件的第 10 个字节处。然后使用 `fileStream.get(ch)` 从当前位置开始读取文件内容，并将其显示在控制台上。

`seekg()` 函数的参数可以是一个偏移量（例如 `seekg(10)`），也可以使用其他形式的重载函数，例如 `seekg(10, std::ios::beg)` 来指定相对于文件开头的偏移量，或者 `seekg(-10, std::ios::end)` 来指定相对于文件末尾的偏移量。

这个函数对于需要定位并从文件中的特定位置开始读取数据的情况非常有用。