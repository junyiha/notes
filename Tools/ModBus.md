## 简介

+ ModBus 相关理论知识

## CRC 详解

CRC (Cyclic Redundancy Check) 是一种错误检测码，用于验证数据的完整性。它是一种快速且广泛应用的校验算法，常用于通信协议、存储设备、网络传输等领域。

CRC 的基本原理是通过对数据进行多项式计算来生成校验值，这个校验值称为 CRC 值。发送方在传输数据前，会计算数据的 CRC 值，并将该值附加到数据后面一并传输。接收方在接收到数据后，也会计算接收到的数据的 CRC 值，并与接收到的 CRC 值进行比较。如果两个 CRC 值匹配，表示数据没有出现错误；如果 CRC 值不匹配，表示数据可能在传输过程中发生了错误或被篡改。

CRC 的特点包括：

1. 快速：CRC 是一种非常快速的校验算法，适用于实时数据传输和处理。

2. 简单：CRC 的实现相对简单，通常用位操作来处理数据和多项式计算。

3. 检测能力：CRC 能够检测不少常见的错误，但并不是绝对可靠，无法检测所有错误。

4. 冗余：CRC 增加了一定的冗余数据，用于检测错误。

在使用 CRC 时，需要事先定义一个生成多项式。不同的 CRC 标准使用不同的多项式，常见的标准有 CRC-16、CRC-32 等。选择合适的 CRC 标准取决于具体应用的要求。

总体而言，CRC 是一种简单、高效且广泛应用的错误检测码。它在数据传输和存储中起着重要的作用，帮助保障数据的完整性和可靠性。

## linux libmodbus 库 详解

`libmodbus` 是一个用于通信协议 Modbus 的开源C库，用于实现 Modbus 协议的通信。Modbus 是一种通信协议，用于连接工业自动化设备，使它们能够在不同设备之间进行数据传输。以下是关于 `libmodbus` 库的详细信息：

**安装 libmodbus 库**：

你可以使用你的 Linux 发行版的包管理器来安装 `libmodbus` 库。例如，如果你使用的是 Ubuntu，可以使用以下命令安装：

```sh
sudo apt-get install libmodbus-dev
```

**使用 libmodbus 库**：

以下是一些关于 `libmodbus` 库的基本使用方法和功能：

1. **创建 modbus 上下文**：

   ```c
   modbus_t* ctx = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1);
   ```

   在这个示例中，我们创建了一个用于串口通信的 Modbus 上下文。

2. **连接到 Modbus 设备**：

   ```c
   if (modbus_connect(ctx) == -1) {
       perror("Connection failed");
       modbus_free(ctx);
       return -1;
   }
   ```

   使用 `modbus_connect` 函数连接到 Modbus 设备。

3. **读取和写入 Modbus 寄存器**：

   ```c
   uint16_t data[5];
   int num = modbus_read_registers(ctx, 0, 5, data);
   
   uint16_t value = 1234;
   modbus_write_register(ctx, 10, value);
   ```

   使用 `modbus_read_registers` 函数读取寄存器数据，使用 `modbus_write_register` 函数写入寄存器数据。

4. **关闭连接并释放资源**：

   ```c
   modbus_close(ctx);
   modbus_free(ctx);
   ```

   在完成通信后，使用 `modbus_close` 函数关闭连接，并使用 `modbus_free` 函数释放资源。

5. **其他功能**：

   `libmodbus` 还提供了其他一些功能，如 Modbus TCP/IP 支持、异常处理、不同寄存器类型的读写等。

`libmodbus` 库使得在 Linux 下实现 Modbus 协议通信变得更加容易。你可以查阅官方文档或在线教程，深入了解 `libmodbus` 库的更多功能和用法。在编程中，你可以根据需要使用合适的函数来实现 Modbus 通信，并根据通信需求进行相应的设置和处理。

## linux libmodbus 库 使用 详解 示例

下面是一个使用 `libmodbus` 库进行 Modbus 通信的简单示例。在这个示例中，我们将使用 Modbus RTU 通信协议通过串口与 Modbus 设备通信，并读取一些寄存器的值。

```c
#include <stdio.h>
#include <modbus.h>

int main() {
    modbus_t *ctx;
    uint16_t data[5];

    // 创建 Modbus 上下文，串口路径为 "/dev/ttyUSB0"，波特率为 9600
    ctx = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1);
    if (ctx == NULL) {
        fprintf(stderr, "Unable to create Modbus context\n");
        return 1;
    }

    // 连接到 Modbus 设备
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    }

    // 读取寄存器数据，起始地址为 0，读取 5 个寄存器
    int num = modbus_read_registers(ctx, 0, 5, data);
    if (num == -1) {
        fprintf(stderr, "Read error: %s\n", modbus_strerror(errno));
        modbus_close(ctx);
        modbus_free(ctx);
        return 1;
    }

    // 打印读取的寄存器值
    for (int i = 0; i < num; i++) {
        printf("Register %d: %d\n", i, data[i]);
    }

    // 关闭连接并释放资源
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
```

在这个示例中，我们首先创建了一个 Modbus 上下文 `ctx`，然后使用 `modbus_connect` 函数连接到 Modbus 设备。接着，使用 `modbus_read_registers` 函数读取起始地址为 0 的连续 5 个寄存器的值。最后，我们打印出读取的寄存器值，并在完成通信后关闭连接和释放资源。

请注意，此示例是一个基本的用法演示。在实际应用中，你可能需要根据 Modbus 设备的配置和通信需求进行适当的设置和处理。