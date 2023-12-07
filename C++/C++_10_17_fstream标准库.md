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