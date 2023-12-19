## 简介

+ <stdio.h>标准头文件

## Linux POSIX <stdio.h> 详解

`<stdio.h>` 是 C 标准库的头文件之一，在 Linux POSIX 系统中提供了对标准输入和输出的支持。

### 主要功能和常见函数：

1. **标准输入输出函数**：
   - `printf()`：用于将格式化数据打印到标准输出（终端）。
   - `scanf()`：用于从标准输入（键盘）读取格式化的数据。
   - `fprintf()`：将格式化数据打印到指定文件流中。
   - `fscanf()`：从指定文件流中读取格式化的数据。
   - `getchar()`：从标准输入中读取一个字符。
   - `putchar()`：将一个字符输出到标准输出。

2. **文件操作函数**：
   - `fopen()`：打开文件并返回文件指针。
   - `fclose()`：关闭文件。
   - `fgets()`：从文件中读取一行数据。
   - `fputs()`：将字符串写入文件。
   - `fgetc()` 和 `fputc()`：用于读取和写入单个字符到文件。
   - `feof()` 和 `ferror()`：检查文件结束和错误标志。

3. **文件定位函数**：
   - `fseek()` 和 `ftell()`：用于在文件中定位和获取当前位置。

4. **格式化输出函数**：
   - `sprintf()`：将格式化的数据写入字符串中。
   - `snprintf()`：类似于 `sprintf()`，但提供了字符数限制，避免缓冲区溢出。

5. **标准流**：
   - `stdin`：标准输入流，通常代表键盘输入。
   - `stdout`：标准输出流，通常代表终端输出。
   - `stderr`：标准错误流，通常用于输出错误消息。

6. **宏定义**：
   - `EOF`：表示文件结束。
   - `NULL`：表示空指针。

### 使用示例：
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "w");
    if (file != NULL) {
        fprintf(file, "这是一个示例文件\n");
        fclose(file);
    } else {
        printf("无法打开文件\n");
    }

    printf("读取文件内容：\n");
    FILE *fileRead = fopen("example.txt", "r");
    if (fileRead != NULL) {
        char buffer[100];
        while (fgets(buffer, sizeof(buffer), fileRead) != NULL) {
            printf("%s", buffer);
        }
        fclose(fileRead);
    } else {
        printf("无法打开文件\n");
    }

    return 0;
}
```

这个示例演示了如何使用 `<stdio.h>` 中的函数进行文件的写入和读取操作。其中，`fopen()` 用于打开文件，`fprintf()` 用于将内容写入文件，`fgets()` 用于从文件中读取内容并打印到控制台上。

## Linux POSIX <stdio.h> printf() 详解

`<stdio.h>` 是 C 语言中的一个头文件，用于提供标准输入输出功能。其中的 `printf()` 函数是用于格式化输出的一个重要函数。

### `printf()` 函数

`printf()` 用于将格式化的数据输出到标准输出（通常是控制台），其功能是“打印格式化的内容”，可以按指定格式在屏幕上显示信息。

#### 语法：
```c
int printf(const char *format, ...);
```

- **`format`**：一个字符串，用于指定输出的格式，可以包含普通字符（按原样输出）和格式说明符。
- **`...`**：额外的参数（可选），对应于 `format` 字符串中的格式说明符。

#### 格式说明符：

`format` 字符串中的格式说明符以百分号 `%` 开始，后跟一个表示要打印数据类型的字符。

常见的格式说明符包括：
- `%d`：整数
- `%f`：浮点数
- `%c`：字符
- `%s`：字符串
- `%p`：指针地址
- `%x`、`%X`：十六进制整数
- `%o`：八进制整数
- `%u`：无符号整数

#### 示例用法：

```c
#include <stdio.h>

int main() {
    int num = 10;
    float pi = 3.14159;
    char ch = 'A';
    char str[] = "Hello, World!";

    printf("整数：%d\n", num);
    printf("浮点数：%f\n", pi);
    printf("字符：%c\n", ch);
    printf("字符串：%s\n", str);

    return 0;
}
```

#### 解释：

- `%d`、`%f`、`%c`、`%s` 是用于打印不同数据类型变量的格式说明符。
- 每个 `printf()` 调用中，格式说明符会被对应的变量值替换，作为额外的参数提供给 `printf()` 函数。
  
#### 返回值：
- `printf()` 返回打印的字符数（不包括用于结束字符串输出的空字节）。如果发生错误，它将返回负值。

### 注意：
- `printf()` 函数在格式化输出方面非常强大和灵活，允许精确控制数据的显示方式。
- 如果格式说明符使用不正确，可能会导致未定义的行为或错误，如打印错误的值或使程序崩溃。

## Linux POSIX <stdio.h> scanf() 详解

`<stdio.h>` 是 C 语言中的一个头文件，提供了输入输出操作的函数和宏。`scanf()` 是其中用于输入的函数之一。

### `scanf()` 函数

`scanf()` 函数用于从标准输入（通常是键盘）获取输入，并根据指定的格式将数据存储到指定的变量中。

#### 语法：
```c
int scanf(const char *format, ...);
```

- **`format`**：包含格式说明符的字符串，用于指定输入的格式。
- **`...`**：用于接收输入数据的变量列表，按照 `format` 字符串中的格式进行匹配。

#### 格式说明符：

格式说明符在 `format` 字符串中，用于指定输入的数据类型。

常见的格式说明符与 `printf()` 相似，包括：
- `%d`：整数
- `%f`：浮点数
- `%c`：字符
- `%s`：字符串
- `%p`：指针地址
- `%x`、`%X`：十六进制整数
- `%o`：八进制整数
- `%u`：无符号整数

#### 示例用法：

```c
#include <stdio.h>

int main() {
    int num;
    float pi;
    char ch;
    char str[50];

    printf("请输入一个整数：");
    scanf("%d", &num);

    printf("请输入一个浮点数：");
    scanf("%f", &pi);

    printf("请输入一个字符：");
    scanf(" %c", &ch);  // 注意空格，避免读取上一个输入后的回车符

    printf("请输入一个字符串：");
    scanf("%s", str);

    printf("您输入的整数是：%d\n", num);
    printf("您输入的浮点数是：%f\n", pi);
    printf("您输入的字符是：%c\n", ch);
    printf("您输入的字符串是：%s\n", str);

    return 0;
}
```

#### 解释：

- `scanf()` 函数按照指定的格式说明符从标准输入中读取输入，并将输入的数据存储到相应的变量中。
- 格式说明符 `%d`、`%f`、`%c`、`%s` 分别用于读取不同类型的数据。
- `&` 运算符用于传递变量的地址，使得 `scanf()` 函数可以将输入的值存储到相应变量的内存位置中。

#### 返回值：
- `scanf()` 返回成功读取的参数数目。如果发生读取失败或到达文件结束，则返回值可能会少于指定的参数数目。

### 注意：
- 使用 `scanf()` 时要确保提供正确的格式说明符，否则可能导致输入解析错误或意外行为。
- 对于字符串 `%s`，它会在空白字符（如空格、制表符、换行符等）处停止读取，可以使用其他函数（如 `fgets()`）更安全地读取一行字符串。

使用 `scanf()` 需要谨慎，确保输入与格式匹配，以避免潜在的问题。

## Linux POSIX <stdio.h> fprintf() 详解

`<stdio.h>` 中的 `fprintf()` 函数与 `printf()` 函数类似，但不是将输出发送到标准输出（通常是屏幕），而是将格式化的输出发送到指定的文件流中。这允许将格式化的数据写入文件而不是控制台。

### `fprintf()` 函数

#### 语法：
```c
int fprintf(FILE *stream, const char *format, ...);
```

- **`stream`**：指向文件的指针，表示要写入的文件流。
- **`format`**：一个字符串，用于指定输出的格式，可以包含普通字符和格式说明符。
- **`...`**：额外的参数（可选），对应于 `format` 字符串中的格式说明符。

#### 格式说明符和用法与 `printf()` 相同。

#### 示例用法：

```c
#include <stdio.h>

int main() {
    FILE *filePointer;
    char data[] = "Hello, File I/O!";

    filePointer = fopen("output.txt", "w"); // 打开文件以写入模式

    if (filePointer == NULL) {
        printf("无法打开文件\n");
        return -1;
    }

    fprintf(filePointer, "这是 fprintf() 写入的内容：\n");
    fprintf(filePointer, "字符串：%s\n", data);
    fprintf(filePointer, "整数：%d\n", 12345);
    fprintf(filePointer, "浮点数：%f\n", 3.14159);

    fclose(filePointer); // 关闭文件流

    printf("数据已写入文件\n");
    return 0;
}
```

#### 解释：

- `fprintf()` 将格式化的输出写入指定的文件流（在此示例中是名为 "output.txt" 的文件）。
- 使用 `fopen()` 函数打开文件，指定 "w"（写入）模式。
- 检查文件指针是否为 `NULL`，以确保文件成功打开。
- 然后，`fprintf()` 将数据写入文件，格式与 `printf()` 相同。
- 使用 `fclose()` 关闭文件流。

#### 返回值：
- `fprintf()` 返回写入文件的字符数。如果发生错误，则返回负值。

### 注意：
- 使用 `fprintf()` 时要确保提供正确的文件指针以及正确的格式说明符，否则可能导致写入文件错误或意外结果。
- 在完成对文件的操作后，务必关闭文件流以释放资源。

`fprintf()` 提供了一种将格式化数据写入文件的方法，可以根据需要指定不同的文件流，并将数据写入文件而不是标准输出。

## Linux POSIX <stdio.h> fscanf() 详解

`<stdio.h>` 中的 `fscanf()` 函数与 `scanf()` 函数类似，但它从指定的文件流中读取格式化的输入，而不是从标准输入（键盘）中读取输入。

### `fscanf()` 函数

#### 语法：
```c
int fscanf(FILE *stream, const char *format, ...);
```

- **`stream`**：指向文件的指针，表示要从中读取数据的文件流。
- **`format`**：包含格式说明符的字符串，用于指定输入的格式。
- **`...`**：用于接收读取数据的变量列表，按照 `format` 字符串中的格式进行匹配。

#### 格式说明符和用法与 `scanf()` 相同。

#### 示例用法：

```c
#include <stdio.h>

int main() {
    FILE *filePointer;
    int num;
    float pi;
    char ch;
    char str[50];

    filePointer = fopen("input.txt", "r"); // 以读取模式打开文件

    if (filePointer == NULL) {
        printf("无法打开文件\n");
        return -1;
    }

    fscanf(filePointer, "%d", &num);
    fscanf(filePointer, "%f", &pi);
    fscanf(filePointer, " %c", &ch); // 注意空格，避免读取上一个输入后的回车符
    fscanf(filePointer, "%s", str);

    printf("从文件中读取的整数是：%d\n", num);
    printf("从文件中读取的浮点数是：%f\n", pi);
    printf("从文件中读取的字符是：%c\n", ch);
    printf("从文件中读取的字符串是：%s\n", str);

    fclose(filePointer); // 关闭文件流

    return 0;
}
```

#### 解释：

- `fscanf()` 函数按照指定的格式说明符从指定文件流中读取输入，并将数据存储到相应的变量中。
- 使用 `fopen()` 函数以 "r"（读取）模式打开文件流。
- 检查文件指针是否为 `NULL`，以确保文件成功打开。
- 然后，`fscanf()` 从文件中读取数据，格式与 `scanf()` 相同。
- 最后，使用 `fclose()` 关闭文件流。

#### 返回值：
- `fscanf()` 返回成功读取的参数数目。如果发生读取失败或到达文件结束，则返回值可能会少于指定的参数数目。

### 注意：
- 使用 `fscanf()` 时要确保提供正确的文件指针以及正确的格式说明符，否则可能导致读取文件错误或意外结果。
- 在完成对文件的操作后，务必关闭文件流以释放资源。

`fscanf()` 提供了一种从文件流中读取格式化数据的方法，可以根据需要从不同的文件流读取数据而不是标准输入。

## Linux POSIX <stdio.h> getchar() 详解

`getchar()` 是 `<stdio.h>` 头文件中的函数，用于从标准输入（通常是键盘）获取一个字符。

### `getchar()` 函数

#### 语法：
```c
int getchar(void);
```

- **无参数**：`getchar()` 不接受任何参数。
- **返回值**：返回一个整数值，表示获取的字符的 ASCII 值（或者在遇到文件结束或错误时返回特殊值 `EOF`）。

#### 示例用法：

```c
#include <stdio.h>

int main() {
    int ch;

    printf("请输入一个字符：\n");
    ch = getchar();

    printf("您输入的字符是：%c\n", ch);

    return 0;
}
```

#### 解释：

- `getchar()` 函数用于从标准输入中获取一个字符，并将其作为整数返回。
- `getchar()` 在用户输入一个字符后，程序会等待用户按下回车键以表示输入完成，然后才会返回该字符的 ASCII 值。

#### 返回值：
- 如果成功获取字符，则返回该字符的 ASCII 值（0 到 255 之间的整数）。
- 如果在获取字符时出现错误或者达到文件结束（End of File，EOF），则返回特殊值 `EOF`（一般为 `-1`）。

### 注意：
- `getchar()` 函数每次只能获取一个字符，即使用户输入多个字符也只返回第一个字符的 ASCII 值。
- 在需要连续获取多个字符的情况下，通常需要循环调用 `getchar()`。

`getchar()` 是一个简单且常用的函数，适用于获取单个字符的输入。如果需要读取整行文本或者处理大量输入，可能需要考虑其他输入函数或循环来获取和处理数据。

## Linux POSIX <stdio.h> putchar() 详解

`putchar()` 是 C 标准库 `<stdio.h>` 中的函数，用于将一个字符输出到标准输出设备（通常是屏幕）。

### `putchar()` 函数

#### 语法：
```c
int putchar(int character);
```

- **`character`**：要输出的字符，以整数形式传递（ASCII 值）。
- **返回值**：如果成功输出字符，则返回输出的字符（`character` 参数的值）。如果发生错误，返回特殊值 `EOF`。

#### 示例用法：

```c
#include <stdio.h>

int main() {
    char ch = 'A';

    printf("输出一个字符：\n");
    putchar(ch);

    return 0;
}
```

#### 解释：

- `putchar()` 函数用于将指定的字符输出到标准输出设备（通常是屏幕）上。
- 在示例中，`putchar(ch)` 将字符 `'A'`（ASCII 值为 65）输出到屏幕上。

#### 返回值：
- 如果成功输出字符，则返回输出的字符的 ASCII 值（即 `character` 参数的值）。
- 如果发生错误，返回特殊值 `EOF`（一般为 `-1`）。

### 注意：
- `putchar()` 函数每次只能输出一个字符。
- 如果需要输出多个字符，通常需要循环调用 `putchar()` 或者结合使用其他输出函数进行输出。

`putchar()` 是一个简单且常用的函数，用于将单个字符输出到标准输出设备。如果需要输出整个字符串或进行大量输出，可能需要考虑其他输出函数或循环来实现。