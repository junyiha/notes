---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_83_update-alternatives
tag: LinuxCommand
---
## 简介

+ update-alternatives命令

## linux g++ 多版本管理

在 Linux 系统上，你可以使用 `update-alternatives` 来进行多版本管理，特别是对于编译器如 `g++` 的管理。这允许你在系统上安装多个版本的 `g++`，并通过 `update-alternatives` 选择默认版本。

以下是一个简单的步骤来实现 `g++` 多版本管理：

1. **安装多个版本的 g++：**

   首先，确保你已经安装了要管理的多个版本的 `g++`。你可以使用包管理工具如 `apt`、`yum` 或者 `dnf` 进行安装。

   ```bash
   sudo apt-get install g++-version1 g++-version2
   ```

   例如：

   ```bash
   sudo apt-get install g++-7 g++-8
   ```

2. **使用 `update-alternatives` 配置 g++：**

   使用 `update-alternatives` 添加和配置 `g++` 的备选项。以下是一个示例：

   ```bash
   sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 100
   sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 90
   ```

   这里，我们给 `g++-7` 和 `g++-8` 分别分配了优先级 100 和 90。较高优先级的版本将成为默认版本。

3. **选择默认版本：**

   使用 `update-alternatives --config g++` 来选择默认的 `g++` 版本：

   ```bash
   sudo update-alternatives --config g++
   ```

   这将显示一个菜单，让你选择要设置为默认的 `g++` 版本。

4. **验证版本：**

   使用以下命令验证 `g++` 的当前版本：

   ```bash
   g++ --version
   ```

   确保显示的版本号是你选择的默认版本。

通过这种方式，你可以方便地在系统上安装和管理多个版本的 `g++`。这对于处理不同项目或依赖不同 `C++` 标准的情况非常有用。

## linux update-alternatives命令 是什么

`update-alternatives` 是一个用于管理 Linux 系统上多个软件版本或者实现的工具的命令。它允许你在系统中选择默认的软件版本或者实现，而不必手动修改符号链接或者其他相关的配置文件。

通过 `update-alternatives`，你可以为系统中的特定命令或者服务设置不同的备选项，然后选择默认的备选项。这对于系统管理员来说是一个方便的工具，因为它可以在不同版本之间切换而不会导致配置混乱。

例如，假设你有多个版本的 Java 安装在系统上，你可以使用 `update-alternatives` 来选择默认使用的 Java 版本，而无需手动更改符号链接或者其他相关配置。

命令的基本语法如下：

```bash
sudo update-alternatives --config <name-of-alternative>
```

其中 `<name-of-alternative>` 是你要配置的备选项的名称。这个命令会显示一个菜单，列出可用的备选项，你可以选择其中一个作为默认。

要添加新的备选项，你可以使用 `--install` 选项。具体的用法可以通过 `man update-alternatives` 查看命令的手册页面来获取更多信息。

## linux update-alternatives命令 详解

`update-alternatives` 命令用于管理系统上的备选项，例如不同版本的软件、命令或服务。通过该命令，用户可以方便地在备选项之间切换，而无需手动编辑配置文件。以下是该命令的详细解释：

### 基本语法：

```bash
update-alternatives [options] --config <name-of-alternative>
```

- `<name-of-alternative>`: 要管理的备选项的名称。

### 常用选项：

- `--install <link> <name> <path> <priority>`: 添加一个备选项。这个选项用于将一个备选项加入到系统中。例如：

  ```bash
  sudo update-alternatives --install /usr/bin/java java /usr/java/jdk1.8.0_171/bin/java 1
  ```

  这个命令将 JDK 1.8.0_171 的 Java 可执行文件添加为备选项。

- `--config <name-of-alternative>`: 配置默认的备选项。这个选项用于在多个备选项中选择一个作为默认值。

  ```bash
  sudo update-alternatives --config java
  ```

  用户将会看到一个菜单，可以选择要使用的 Java 版本。

- `--display <name-of-alternative>`: 显示指定备选项的信息。

  ```bash
  update-alternatives --display java
  ```

- `--remove <name-of-alternative> <path>`: 从备选项列表中删除一个备选项。

  ```bash
  sudo update-alternatives --remove java /usr/java/jdk1.8.0_171/bin/java
  ```

### 工作流程：

1. **安装备选项：** 使用 `--install` 选项将备选项添加到系统。

2. **配置默认备选项：** 使用 `--config` 选项选择默认的备选项。

3. **显示备选项信息：** 使用 `--display` 可以查看备选项的信息，包括路径、符号链接等。

4. **删除备选项：** 使用 `--remove` 选项可以从备选项列表中删除不再需要的备选项。

### 示例：

#### 1. 安装备选项：

```bash
sudo update-alternatives --install /usr/bin/editor editor /usr/bin/nano 50
sudo update-alternatives --install /usr/bin/editor editor /usr/bin/vim.basic 30
```

#### 2. 配置默认备选项：

```bash
sudo update-alternatives --config editor
```

用户可以选择默认的编辑器。

#### 3. 显示备选项信息：

```bash
update-alternatives --display editor
```

显示与编辑器相关的备选项信息。

#### 4. 删除备选项：

```bash
sudo update-alternatives --remove editor /usr/bin/nano
```

从备选项列表中删除 Nano 编辑器。

### 注意事项：

- 使用 `sudo` 或者在具有足够权限的用户下运行命令，因为修改备选项可能需要超级用户权限。
- 在某些系统上，`update-alternatives` 可能不适用于所有软件。它通常用于系统软件和一些常见的命令。
- 具体备选项的名称、路径和优先级等参数可能因软件而异，具体使用时需要参考软件的文档或手册。

这是 `update-alternatives` 命令的基本概述，具体的使用方法和备选项名称会根据不同的软件而有所不同。可以通过 `man update-alternatives` 命令查看完整的命令手册。

## linux update-alternatives命令 常用技巧

`update-alternatives` 命令是一个强大的工具，以下是一些在使用该命令时的常用技巧：

1. **查看当前备选项配置：**
   
   使用 `--display` 选项可以查看当前备选项的配置信息，包括备选项的名称、路径、优先级等。

   ```bash
   sudo update-alternatives --display <name-of-alternative>
   ```

   例如，查看 Java 的备选项配置：

   ```bash
   sudo update-alternatives --display java
   ```

2. **安装新备选项：**

   使用 `--install` 选项可以添加新的备选项。例如，安装一个新版本的 Java：

   ```bash
   sudo update-alternatives --install /usr/bin/java java /usr/java/jdk1.11.0/bin/java 2
   ```

3. **配置默认备选项：**

   使用 `--config` 选项可以选择默认的备选项。例如，选择默认的 Java 版本：

   ```bash
   sudo update-alternatives --config java
   ```

   用户将会看到一个菜单，可以选择要使用的 Java 版本。

4. **手动更改备选项路径：**

   在某些情况下，你可能需要手动更改备选项的路径。可以直接编辑 `/etc/alternatives/` 目录下对应备选项的符号链接，或者使用 `--set` 选项：

   ```bash
   sudo update-alternatives --set <name-of-alternative> <alternative-path>
   ```

   例如，手动设置 Java 的路径：

   ```bash
   sudo update-alternatives --set java /usr/java/jdk1.11.0/bin/java
   ```

5. **删除不需要的备选项：**

   使用 `--remove` 选项可以从备选项列表中删除不再需要的备选项：

   ```bash
   sudo update-alternatives --remove <name-of-alternative> <alternative-path>
   ```

   例如，删除不再需要的 Java 版本：

   ```bash
   sudo update-alternatives --remove java /usr/java/jdk1.8.0_171/bin/java
   ```

6. **查看已安装备选项的列表：**

   使用 `--list` 选项可以列出某个备选项的所有可选项：

   ```bash
   sudo update-alternatives --list <name-of-alternative>
   ```

   例如，列出所有安装的 Java 版本：

   ```bash
   sudo update-alternatives --list java
   ```

7. **通过脚本自动配置备选项：**

   如果你需要在脚本中自动配置备选项，可以使用 `--auto` 选项：

   ```bash
   sudo update-alternatives --auto <name-of-alternative>
   ```

   这样可以根据预设规则自动选择默认备选项。

这些技巧可以帮助你更灵活地管理系统上的备选项，特别是当你需要安装、配置或更新多个版本的软件时。在使用 `update-alternatives` 时，请确保谨慎操作，以免影响系统稳定性。