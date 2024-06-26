---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_77_valgrind
tag: LinuxCommand
---
## 简介

+ valgrind命令

## linux valgrind命令 详解

`Valgrind` 是一个用于内存调试、内存泄漏检测、性能分析等的开源工具。它可以用于 Linux 操作系统，并支持多种不同的编程语言，如C、C++。

以下是一些 `Valgrind` 命令的基本用法和解释：

### 1. **安装 Valgrind：**
在大多数 Linux 发行版中，可以使用包管理器安装 Valgrind。例如，在 Ubuntu 中可以使用以下命令：
```bash
sudo apt-get install valgrind
```

### 2. **检测内存泄漏：**
```bash
valgrind --leak-check=full ./your_program
```
这个命令运行你的程序，并对内存泄漏进行全面检查。`--leak-check=full` 选项会输出详细的泄漏信息。

### 3. **检测内存错误：**
```bash
valgrind ./your_program
```
这个命令运行你的程序，并检查是否有内存错误。Valgrind 将会输出错误的详细信息。

### 4. **检测特定函数的内存泄漏：**
```bash
valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./your_program arg1 arg2
```
这个命令在检测内存泄漏时，会显示详细的泄漏信息，包括泄漏的函数。

### 5. **生成调用图：**
```bash
valgrind --tool=callgrind ./your_program
```
这个命令使用 Callgrind 工具，生成程序执行期间的函数调用图，用于性能分析。

### 6. **检测缓存问题：**
```bash
valgrind --tool=cachegrind ./your_program
```
这个命令使用 Cachegrind 工具，用于检测程序中的缓存问题。

### 7. **检测线程问题：**
```bash
valgrind --tool=helgrind ./your_program
```
这个命令使用 Helgrind 工具，检测多线程程序中的竞争条件和死锁等问题。

### 8. **检测指令错误：**
```bash
valgrind --tool=exp-sgcheck ./your_program
```
这个命令使用 Exp-Sgcheck 工具，用于检测程序中的指令错误。

### 9. **检测系统调用错误：**
```bash
valgrind --tool=memcheck --vgdb-error=0 ./your_program
```
这个命令使用 Memcheck 工具，并禁止 Valgrind 报告系统调用的错误。

### 10. **显示版本信息：**
```bash
valgrind --version
```
这个命令显示 Valgrind 工具的版本信息。

这些命令只是 Valgrind 工具链的一部分，Valgrind 提供了多个工具用于不同类型的分析和调试任务。在使用 Valgrind 之前，确保你的程序已经编译为可调试版本，以便 Valgrind 能够提供更详细的信息。

## linux valgrind命令 常用技巧

在使用 Valgrind 进行内存调试和性能分析时，以下是一些常用的技巧和选项：

### 1. **检测内存泄漏：**
```bash
valgrind --leak-check=full ./your_program
```
使用 `--leak-check=full` 选项启用详细的内存泄漏检查。这将显示泄漏的详细信息，包括泄漏的位置和大小。

### 2. **检测特定函数的内存泄漏：**
```bash
valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./your_program arg1 arg2
```
通过结合 `--show-leak-kinds=all` 和 `--trace-children=yes` 选项，可以检测子进程中的内存泄漏，并显示泄漏的函数。

### 3. **生成调用图：**
```bash
valgrind --tool=callgrind ./your_program
```
使用 Callgrind 工具生成程序执行期间的函数调用图。生成的数据文件可以使用 `kcachegrind` 查看。

### 4. **检测缓存问题：**
```bash
valgrind --tool=cachegrind ./your_program
```
使用 Cachegrind 工具检测程序中的缓存问题。生成的数据文件可以使用 `cg_annotate` 或 `kcachegrind` 进行分析。

### 5. **检测线程问题：**
```bash
valgrind --tool=helgrind ./your_program
```
使用 Helgrind 工具检测多线程程序中的竞争条件和死锁等问题。

### 6. **检测指令错误：**
```bash
valgrind --tool=exp-sgcheck ./your_program
```
使用 Exp-Sgcheck 工具检测程序中的指令错误。

### 7. **禁止报告系统调用错误：**
```bash
valgrind --tool=memcheck --vgdb-error=0 ./your_program
```
通过添加 `--vgdb-error=0` 选项，禁止 Valgrind 报告系统调用的错误。

### 8. **自定义内存分析选项：**
```bash
valgrind --tool=memcheck --track-origins=yes ./your_program
```
通过添加 `--track-origins=yes` 选项，可以追踪未初始化内存的来源，帮助找到相关问题。

### 9. **执行内存分析并生成日志文件：**
```bash
valgrind --log-file=valgrind.log ./your_program
```
通过添加 `--log-file` 选项，将 Valgrind 的输出保存到指定的日志文件中。

### 10. **排除指定的文件或函数：**
```bash
valgrind --exclude-file=exclude_file.txt ./your_program
```
通过添加 `--exclude-file` 选项，可以排除特定的文件或函数不进行内存分析。

### 11. **指定检查的范围：**
```bash
valgrind --track-origins=yes --read-var-info=yes ./your_program
```
通过添加 `--read-var-info=yes` 选项，可以指定检查的范围，以帮助找到内存问题。

### 12. **显示 Valgrind 版本信息：**
```bash
valgrind --version
```
使用 `--version` 选项可以显示 Valgrind 工具的版本信息。

这些技巧和选项可以帮助你更有效地使用 Valgrind 工具进行内存调试和性能分析。请根据具体需求选择合适的选项，并查看 Valgrind 的文档以获取更多详细信息。

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