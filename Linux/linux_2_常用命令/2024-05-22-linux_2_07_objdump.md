---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_07_objdump
tag: LinuxCommand
---
## 简介

+ objdump命令相关笔记

## linux objdump命令 详解

`objdump` 是一个用于显示目标文件（object file）信息的强大工具，它通常随着 GNU binutils 工具集一起提供。`objdump` 可以用于分析二进制文件、共享库、可执行文件等，提供了很多有用的信息，包括汇编代码、符号表、段信息等。以下是一些常见的用法和选项：

### 基本用法:

1. **查看文件信息:**
   ```bash
   objdump -f your_file
   ```
   显示文件头的基本信息，包括目标架构、文件大小、入口点等。

2. **查看节（section）信息:**
   ```bash
   objdump -h your_file
   ```
   显示目标文件的各个节的详细信息，包括名称、大小、VMA（虚拟内存地址）、LMA（加载内存地址）、对齐等。

### 汇编代码:

1. **显示全部汇编代码:**
   ```bash
   objdump -d your_file
   ```
   显示目标文件中的所有汇编代码。

2. **指定节进行汇编代码显示:**
   ```bash
   objdump -d -j .text your_file
   ```
   只显示指定节（这里是 `.text` 节）的汇编代码。

3. **以反汇编形式显示:**
   ```bash
   objdump -D your_file
   ```
   以反汇编形式显示目标文件的所有代码。

### 符号表:

1. **显示符号表:**
   ```bash
   objdump -t your_file
   ```
   显示目标文件的符号表，包括函数、变量等。

2. **显示动态符号表:**
   ```bash
   objdump -T your_file
   ```
   显示目标文件的动态符号表。

### 其他选项:

1. **显示重定位信息:**
   ```bash
   objdump -r your_file
   ```
   显示目标文件的重定位信息。

2. **输出到文件:**
   ```bash
   objdump -d your_file > output.asm
   ```
   将汇编代码输出到文件。

这只是 `objdump` 的一些基本用法，该工具提供了更多选项，可以根据需要进行定制。可以通过 `man objdump` 命令查看 `objdump` 的手册页，获取更详细的信息。