## 简介

+ Linux系统下常用命令笔记

## e2fsck

`e2fsck`是用于检查和修复ext2、ext3和ext4文件系统中的错误的命令。下面是对`e2fsck`命令的详细解释：

```
e2fsck [选项] 设备
```

其中，`选项`是一些可用的标志和参数，`设备`是要检查和修复的文件系统所在的设备或分区。

常用的选项包括：

- `-p`：自动修复不需要人工干预的错误。
- `-y`：自动回答"yes"以所有问题，用于无人值守操作。
- `-f`：强制运行`e2fsck`，即使文件系统被标记为已经干净。
- `-c`：检查设备上的坏扇区，并将其添加到坏块列表中。
- `-n`：仅显示要执行的操作，而不实际执行它们。
- `-v`：显示更详细的输出，包括修复过程中的详细信息。
- `-b  备份文件`：将修复前的元数据备份到指定的文件中。

除了选项之外，您还需要指定要检查和修复的文件系统所在的设备。例如，如果您要检查/dev/sda1上的文件系统，可以运行以下命令：

```
e2fsck /dev/sda1
```

`e2fsck`命令将会扫描文件系统并显示任何检测到的错误。如果它发现任何错误，它会提示您是否修复它们。您可以根据提示进行选择，或者使用前面提到的选项自动修复错误。

请注意，在运行`e2fsck`之前，建议您确保文件系统是以只读模式挂载的，以避免进一步损坏。如果您不能以只读模式挂载文件系统，最好使用其他工具或在紧急情况下考虑使用专业的数据恢复服务。

## nano 

Nano 是一个文本编辑器，常用于 Linux 和其他 Unix-like 系统。它是一个简单、易于使用的命令行编辑器，适合初学者和那些寻找基本编辑功能的用户。下面是 Nano 的一些详解：

1. 启动 Nano：
   要启动 Nano 编辑器，请在终端中输入以下命令：
   ```
   nano
   ```
   如果要打开特定文件进行编辑，请在命令后加上文件名：
   ```
   nano filename
   ```

2. Nano 的界面：
   Nano 编辑器的界面相对简洁。在编辑器的底部显示了一些常用的命令说明，如保存文件、退出编辑器等。使用箭头键导航光标在文本中移动。

3. 基本操作：
   - 输入文本：在编辑器中直接键入文本即可。
   - 保存文件：按下 `Ctrl + O`，然后按下 `Enter`，将文件保存到当前文件名。
   - 退出编辑器：按下 `Ctrl + X`，如果文件有未保存的更改，Nano 会提示您保存或放弃更改。

4. 快捷键：
   Nano 提供了一些常用的快捷键来进行各种操作：
   - `Ctrl + G`：显示帮助菜单，其中包含可用的命令列表。
   - `Ctrl + K`：剪切当前行或选定的文本。
   - `Ctrl + U`：粘贴剪切的文本。
   - `Ctrl + W`：搜索文本。
   - `Ctrl + \`：替换文本。
   - `Ctrl + C`：显示当前光标位置的行号。

5. 配置文件：
   Nano 的行为可以通过编辑配置文件 `~/.nanorc` 进行自定义。您可以在配置文件中定义颜色方案、键绑定和其他首选项。

6. 其他功能：
   Nano 提供了其他一些功能，如自动缩进、语法高亮、多文档编辑等。您可以通过命令行参数或配置文件来启用或禁用这些功能。

Nano 是一个简单而实用的文本编辑器，尤其适合新手和需要基本编辑功能的用户。它的命令行界面和快捷键使得编辑文本文件变得方便快捷。

---

## uname 详解

`uname` 命令用于显示关于当前操作系统的信息。它通常用于获取有关系统的基本信息，如内核版本、操作系统类型、处理器架构等。

以下是 `uname` 命令的常用选项及其解释：

- `-a`：显示所有可用信息，包括内核名称、主机名、操作系统类型、内核版本、处理器类型等。
- `-s`：显示操作系统名称。
- `-n`：显示主机名。
- `-r`：显示内核版本。
- `-v`：显示操作系统版本。
- `-m`：显示处理器架构。
- `-p`：显示处理器类型。
- `-i`：显示硬件平台。
- `-o`：显示操作系统类型。

您可以通过在终端中运行 `uname` 命令，后跟所需的选项，来获取相应的信息。例如，要显示操作系统名称和内核版本，可以运行以下命令：

```
uname -s -r
```

示例输出可能如下所示：

```
Linux 5.4.0-73-generic
```

在上述示例中，`Linux` 是操作系统名称，`5.4.0-73-generic` 是内核版本。

请注意，`uname` 命令是跨平台的，可以在不同的操作系统上运行。但是，具体的选项和输出可能因操作系统而异。因此，在特定的操作系统上，`uname` 命令可能提供更多或不同的信息。

通过查阅 `uname` 命令的手册页（`man uname`），您可以获取更多关于该命令的详细信息和其他可用选项。

---

## asan 工具 详解

AddressSanitizer（ASan）是一种用于检测内存错误的工具，它是 LLVM 编译器工具链的一部分。ASan 主要用于检测内存越界访问、使用未初始化的内存、内存泄漏等常见的内存错误。

下面是 ASan 的一些主要特点和工作原理的详细解释：

1. 内存错误检测：ASan 在程序执行期间动态地分配和管理内存，并在每个内存块的边界添加额外的元数据。当程序访问超出分配的内存范围或使用未初始化的内存时，ASan 会检测到这些错误并生成相应的报告。

2. 内存泄漏检测：ASan 跟踪程序中动态分配的内存，并在程序结束时检查是否有未释放的内存。如果存在内存泄漏，ASan 会生成相应的报告指示泄漏的内存块的位置。

3. 元数据重映射：ASan 使用位图技术来存储内存元数据，以减少对内存的额外开销。这种位图会与程序的内存布局进行映射，以便快速定位错误和泄漏。

4. 堆栈跟踪：当发生内存错误时，ASan 会捕获当前的函数调用堆栈信息，以便定位错误发生的位置。这对于调试和定位问题非常有帮助。

5. 崩溃报告：当程序发生内存错误导致崩溃时，ASan 会生成详细的崩溃报告，其中包含了堆栈跟踪、错误类型和发生位置等信息。

使用 ASan 进行内存错误检测时，需要使用支持 ASan 的编译器进行编译，并在链接时启用 ASan 的运行时库。编译和链接选项可以根据具体的编译器和工具链有所差异。

ASan 是一个强大的工具，可以帮助开发者在早期阶段捕获和调试内存错误，提高代码的质量和可靠性。然而，由于 ASan 需要额外的运行时开销和内存使用，对于大型项目或性能敏感的代码，可能需要在测试和生产环境中进行谨慎使用和评估。

---

## asan 工具 使用 示例

以下是一个简单的示例，演示如何使用 AddressSanitizer（ASan）来检测和调试内存错误：

1. 编写代码文件（示例文件名为 `example.c`）：

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* buffer = (int*)malloc(sizeof(int) * 10);
    buffer[10] = 42; // 内存越界访问

    free(buffer);
    return 0;
}
```

2. 使用编译器进行编译和链接，启用 ASan：

```shell
$ clang -fsanitize=address -g example.c -o example
```

或者使用 gcc 编译器：

```shell
$ gcc -fsanitize=address -g example.c -o example
```

在编译过程中，我们通过添加 `-fsanitize=address` 选项来启用 ASan。

3. 运行程序：

```shell
$ ./example
```

4. ASan 检测到内存错误后，会生成相应的报告并打印在终端上，类似于以下内容：

```
=================================================================
==12345==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60200000eff0 at pc 0x0000004009b9
READ of size 4 at 0x60200000eff0 thread T0
    #0 0x4009b8 in main example.c:6
    #1 0x7ffff6b4ab96 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21b96)
    #2 0x4008c9 in _start (/path/to/example+0x4008c9)

Address 0x60200000eff0 is a wild pointer.
SUMMARY: AddressSanitizer: heap-buffer-overflow example.c:6 in main
Shadow bytes around the buggy address:
  0x0c047fffbe70: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbe80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbe90: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbea0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbeb0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0c047fffbec0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa[04]fa
  0x0c047fffbed0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbee0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbef0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbf00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fffbf10: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8

 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==12345==ABORTING
```

报告中会提供详细的错误信息，包括错误类型、错误地址、堆栈跟踪等。在这个示例中，ASan 检测到了堆缓冲区溢出错误。

通过这种方式，ASan 可以帮助开发者捕获和调试内存错误，提供有用的诊断信息，以帮助修复问题和提高代码质量。

---

## valgrind

Valgrind 是一个开源的内存调试和性能分析工具，常用于 C 和 C++ 程序的调试和性能优化。它提供了一套强大的工具集，可以帮助开发者发现内存泄漏、内存错误、线程问题和性能瓶颈等问题。

Valgrind 主要包含以下几个工具：

1. Memcheck：用于检测程序的内存错误，如使用未初始化的变量、访问已释放内存、内存越界等问题。它可以跟踪每个分配和释放的内存块，并检查是否存在问题。

2. Cachegrind：用于分析程序的缓存使用情况和缓存命中率。它可以模拟处理器的缓存行行为，并提供详细的缓存访问统计信息，帮助开发者优化程序的缓存性能。

3. Callgrind：用于分析程序的函数调用关系和性能。它会记录程序的函数调用栈，并统计每个函数的执行次数、执行时间和调用关系，以便开发者识别热点函数和性能瓶颈。

4. Massif：用于分析程序的堆内存使用情况。它会跟踪程序的堆内存分配和释放，并生成堆内存使用的详细报告，帮助开发者识别内存泄漏和内存使用情况。

使用 Valgrind 的基本步骤如下：

1. 安装 Valgrind：根据你的操作系统，使用适当的方式安装 Valgrind。

2. 编译程序：在编译程序时，使用 `-g` 选项开启调试符号，以便 Valgrind 能够提供更详细的调试信息。

3. 运行程序：使用 `valgrind` 命令来运行程序，例如：`valgrind --tool=memcheck ./my_program`。

4. 分析结果：Valgrind 会输出详细的调试信息和分析结果，包括内存错误、内存泄漏、性能统计等。开发者可以根据输出信息来识别和修复问题。

请注意，Valgrind 在运行时会对程序的性能产生一定的影响，并且在分析大型程序时可能会导致较长的运行时间。因此，建议在开发和测试阶段使用 Valgrind 进行调试和性能分析，而在发布版本时禁用 Valgrind。

Valgrind 是一个功能强大且广泛使用的工具，但对于复杂的程序或多线程程序，可能需要更深入的了解和配置才能得到准确的分析结果。建议阅读 Valgrind 的官方文档和用户指南，以获得更详细

的使用说明和技巧。

---

## valgrind 常用选项 

Valgrind 是一个功能强大的工具，提供了许多选项和参数来进行不同类型的代码分析。以下是一些 Valgrind 常用的选项：

1. `--tool=<toolname>`: 指定要使用的 Valgrind 工具。例如，`--tool=memcheck` 表示使用 Memcheck 工具进行内存错误检查。

2. `--leak-check=<yes|no>`: 设置是否进行内存泄漏检查。`--leak-check=yes` 表示启用内存泄漏检查，`--leak-check=no` 表示禁用。

3. `--show-leak-kinds=<kinds>`: 设置要显示的内存泄漏类型。例如，`--show-leak-kinds=definite` 表示只显示确定的内存泄漏。

4. `--track-origins=<yes|no>`: 设置是否跟踪未初始化的值的来源。`--track-origins=yes` 表示启用跟踪，`--track-origins=no` 表示禁用。

5. `--vgdb=<yes|no>`: 设置是否启用 Valgrind GDB 调试服务器。`--vgdb=yes` 表示启用，`--vgdb=no` 表示禁用。

6. `--xml-file=<filename>`: 将分析结果以 XML 格式输出到指定文件。

7. `--log-file=<filename>`: 将 Valgrind 的日志输出到指定文件。

8. `--num-callers=<num>`: 设置要显示的函数调用堆栈的层数。

9. `--suppressions=<filename>`: 指定要使用的抑制文件，用于屏蔽某些特定的错误报告。

这些只是 Valgrind 的一些常用选项，实际上 Valgrind 提供了更多的选项和参数，用于不同类型的分析和优化需求。你可以通过运行 `valgrind --help` 命令来查看完整的选项列表和说明。

请注意，使用 Valgrind 进行代码分析时，要根据具体的需求选择合适的选项，并进行适当的调试和优化。不同的选项可能会对程序的性能和运行时间产生影响，因此需要综合考虑使用。

---

## valgrind memcheck 详解

Valgrind Memcheck 是 Valgrind 工具集中的一个工具，用于检测程序中的内存错误和泄漏。它可以帮助开发者发现未初始化变量、内存越界访问、重复释放内存等问题。下面是一个简单的示例，展示如何使用 Valgrind Memcheck 进行内存错误检测。

1. 编译程序：
   首先，使用编译器在调试模式下编译你的程序，并添加 `-g` 选项以生成调试符号。例如：

   ```bash
   gcc -g -o my_program my_program.c
   ```

2. 运行程序：
   使用 Valgrind Memcheck 工具运行你的程序。命令格式如下：

   ```bash
   valgrind --tool=memcheck ./my_program
   ```

   运行以上命令后，Valgrind Memcheck 将会对 `my_program` 进行内存错误检测，并输出结果。

3. 分析结果：
   Valgrind Memcheck 将输出详细的检测结果，包括内存错误的类型、错误位置、堆栈跟踪等信息。例如：

   ```
   ==12345== Invalid read of size 4
   ==12345==    at 0x12345678: some_function (my_program.c:10)
   ==12345==    by 0x123456AB: main (my_program.c:20)
   ==12345==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
   ```

   这个示例输出表示在 `my_program.c` 文件的第 10 行发生了一个无效的读取操作，导致程序访问了一个未分配的内存地址。

通过分析 Valgrind Memcheck 的输出结果，你可以定位和修复程序中的内存错误，并确保程序在运行时没有内存泄漏等问题。

请注意，Valgrind Memcheck 可能会对程序的性能产生一定的影响，并且在分析大型程序时可能会导致较长的运行时间。因此，建议在开发和测试阶段使用 Valgrind Memcheck 进行内存错误检测，而在发布版本时禁用 Valgrind。

---

## valgrind cachegrind 详解

Valgrind Cachegrind 是 Valgrind 工具集中的一个工具，用于分析程序的缓存使用情况和缓存命中率。它可以帮助开发者了解程序的缓存访问模式，并优化程序的缓存性能。以下是一个简单的示例，展示如何使用 Valgrind Cachegrind 进行缓存分析。

1. 编译程序：
   首先，使用编译器在调试模式下编译你的程序，并添加 `-g` 选项以生成调试符号。例如：

   ```bash
   gcc -g -o my_program my_program.c
   ```

2. 运行程序：
   使用 Valgrind Cachegrind 工具运行你的程序。命令格式如下：

   ```bash
   valgrind --tool=cachegrind ./my_program
   ```

   运行以上命令后，Valgrind Cachegrind 将会运行你的程序，并收集缓存访问的统计信息。

3. 分析结果：
   Valgrind Cachegrind 将输出详细的缓存访问统计信息，包括缓存命中率、缓存行使用情况、缓存分支预测等。例如：

   ```
   ==12345== D   refs: 1,234,567
   ==12345== I1  misses: 1,234
   ==12345== L1  misses: 567
   ==12345== LLi misses: 89
   ==12345== LLd misses: 12
   ```

   这个示例输出表示在运行程序期间，发生了一定数量的缓存访问和缓存未命中。根据这些统计信息，你可以了解程序的缓存访问情况，并针对性地进行性能优化。

通过分析 Valgrind Cachegrind 的输出结果，你可以发现程序的缓存使用模式，识别缓存未命中的原因，并采取相应的优化措施，以提高程序的缓存性能。

请注意，Valgrind Cachegrind 对程序的性能有一定的影响，并且在分析大型程序时可能会导致较长的运行时间。因此，建议在开发和测试阶段使用 Valgrind Cachegrind 进行缓存分析，而在发布版本时禁用 Valgrind。

---

## valgrind callgrind 详解

Valgrind Callgrind 是 Valgrind 工具集中的一个工具，用于分析程序的函数调用关系和性能。它可以帮助开发者了解程序的函数调用栈、函数执行次数、执行时间等信息，以便进行性能优化。以下是一个简单的示例，展示如何使用 Valgrind Callgrind 进行函数调用和性能分析。

1. 编译程序：
   首先，使用编译器在调试模式下编译你的程序，并添加 `-g` 选项以生成调试符号。例如：

   ```bash
   gcc -g -o my_program my_program.c
   ```

2. 运行程序：
   使用 Valgrind Callgrind 工具运行你的程序。命令格式如下：

   ```bash
   valgrind --tool=callgrind ./my_program
   ```

   运行以上命令后，Valgrind Callgrind 将会运行你的程序，并收集函数调用和性能信息。

3. 分析结果：
   Valgrind Callgrind 将输出详细的函数调用和性能信息，包括函数执行次数、执行时间、调用关系等。例如：

   ```
   ==12345== Profiling timer expired
   ==12345==    Ir          I1mr          Dr          D1mr          Dw         D1mw       ILmr       DLmr      ILmw     DLmw       Ir_op
   ==12345== 1,234,567    1,234,567  1,234,567    1,234,567  1,234,567    1,234,567  1,234,567  1,234,567  1,234,567  1,234,567  1,234,567
   ```

   这个示例输出表示程序的函数执行次数、内存读写次数等信息。根据这些统计信息，你可以了解函数的执行频率和性能状况，找出热点函数和性能瓶颈。

通过分析 Valgrind Callgrind 的输出结果，你可以了解程序的函数调用关系和性能状况，进而进行性能优化。你可以根据函数的执行次数和执行时间，针对性地优化热点函数，减少函数调用次数，改进算法等。

请注意，Valgrind Callgrind 对程序的性能有一定的影响，并且在分析大型程序时可能会导致较长的运行时间。因此，建议在开发和测试阶段使用 Valgrind Callgrind 进行函数调用和性能分析，而在发布版本时禁用 Valgrind。

---

## valgrind massif 详解

Valgrind Massif 是 Valgrind 工具集中的一个工具，用于分析程序的堆内存分配情况和堆内存使用情况。它可以帮助开发者了解程序在不同时间点的内存分配情况，识别内存泄漏和高内存消耗的地方。以下是一个简单的示例，展示如何使用 Valgrind Massif 进行堆内存分析。

1. 编译程序：
   首先，使用编译器在调试模式下编译你的程序，并添加 `-g` 选项以生成调试符号。例如：

   ```bash
   gcc -g -o my_program my_program.c
   ```

2. 运行程序：
   使用 Valgrind Massif 工具运行你的程序。命令格式如下：

   ```bash
   valgrind --tool=massif ./my_program
   ```

   运行以上命令后，Valgrind Massif 将会运行你的程序，并收集堆内存分配和使用的信息。

3. 分析结果：
   Valgrind Massif 将输出详细的堆内存分配和使用信息，包括内存堆栈、内存分配和释放时间等。例如：

   ```
   ==12345== Command: ./my_program
   ==12345==
   ==12345==   bytes          calls         time
   ==12345==  1,234,567     1,234,567     1.234s
   ```

   这个示例输出表示程序在运行过程中进行了一定数量的内存分配，总共分配了 1,234,567 字节的内存，并在 1.234 秒的时间内完成。

通过分析 Valgrind Massif 的输出结果，你可以了解程序的堆内存分配情况，发现内存泄漏和高内存消耗的地方。Valgrind Massif 还提供了可视化工具 `ms_print`，可以将 Massif 的输出结果以图形的形式展示，帮助你更直观地分析和优化程序的内存使用。

请注意，Valgrind Massif 对程序的性能有一定的影响，并且在分析大型程序时可能会导致较长的运行时间和较大的内存开销。因此，建议在开发和测试阶段使用 Valgrind Massif 进行堆内存分析，而在发布版本时禁用 Valgrind。