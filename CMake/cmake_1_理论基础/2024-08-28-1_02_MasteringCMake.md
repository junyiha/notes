---
category: CMake
date: 2024-08-28 09:00:00 +0800
layout: post
title: MasteringCMake
tag: CMake
---
## 简介

+ cmake官方文档: MasteringCMake 阅读笔记

## 目录结构

+ CMake在构建项目时有两个主要的目录: 源代码目录和二进制目录
  + 源代码目录是存放项目源代码的位置
  + 二进制目录，有时候也成为build目录，是CMake存放最终对象文件，库和可执行文件的位置。
+ CMake不会向源代码目录写任何文件，只会向二进制目录写文件。

## 基础用法

+ CMake用各种各样的本地开发工具，将一个或多个CMakeLists 文件作为输入，并生成项目文件或者Makefile使用
+ 下面是典型的CMake处理流程
  + 项目定义一个或多个CMakeLists文件
  + CMake配置并生成项目文件
  + 用户按需使用本地开发工具构建项目

## CMakeLists文件

+ CMakeLists文件是包含使用CMake语言描述项目的文本文件。
+ CMake语言表示为一系列的注释，命令和变量。
+ CMake为什么要有自己的语言？
  + 因为CMake如果依赖于其他语言，例如Python，就需要在使用CMake时安装其他语言。
  + 有CMake语言能够更高效，更方便。

## CMake中的Hello World

+ 示例
```cmake
cmake_minimum_required(VERSION 3.20)
project(Hello)
add_executable(Hello Hello.c)
```

+ CMakeLists文件第一行总会是 cmake_minimum_requried.这使得CMake可以使用指定的版本。