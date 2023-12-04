## 简介

+ vim相关的笔记

## vim 详解

Vim 是一个文本编辑器，是在 Vi 编辑器基础上发展而来的。它可以在终端中运行，并且具有很多强大的编辑功能。Vim 的强大功能主要体现在以下几个方面：

1. **模式**：Vim 有多种模式，其中最常见的是命令模式和编辑模式。在命令模式下，可以执行各种命令，比如移动光标、复制粘贴等；在编辑模式下可以编辑文本。

2. **多窗口编辑**：Vim 支持在一个屏幕内同时编辑多个文件，通过分割窗口（`:sp`、`:vsp`）或分割标签页（`:tabnew`）来实现。

3. **自定义**：可以通过配置文件（`.vimrc`）来自定义 Vim 的行为，如自定义快捷键、设置颜色主题、安装插件等。

4. **插件支持**：Vim 支持各种插件，可以增强编辑功能，如代码高亮、自动补全、文件树等。

5. **强大的编辑功能**：Vim 支持各种快捷键操作，可以高效地进行文本编辑、搜索、替换等操作。

Vim 的基本使用方法包括以下几点：

- **命令模式**：按下 `Esc` 键进入命令模式。
  - `h`、`j`、`k`、`l`：左、下、上、右移动光标。
  - `i`、`a`、`o`：在当前光标位置插入文本。
  - `x`：删除光标所在处的字符。
  - `dd`：删除当前行。
  - `yy`：复制当前行。
  - `p`：粘贴复制或删除的文本。
  - `/`：进行文本搜索。
  - `:w`：保存文件。
  - `:q`：退出 Vim。

- **编辑模式**：在命令模式下按下 `i`、`a` 或 `o` 键切换到编辑模式，进行文本编辑。

- **插件管理**：使用插件管理器（如 Vim-Plug）来安装和管理 Vim 插件。

- **配置文件**：修改 `~/.vimrc` 文件来定制化 Vim 编辑器的行为。

以上只是 Vim 的基础用法，Vim 有非常丰富的功能和命令，可以根据个人需求和习惯进行更多的定制和配置。如果您想要深入学习 Vim，可以参考 Vim 的官方文档或者在线教程。

## ubuntu vim-plug 安装C++插件

当您想要在 Ubuntu 上使用 Vim-Plug 安装 C++ 开发相关的插件时，您可以遵循以下步骤：

### 步骤 1：安装 Vim-Plug

1. 打开终端（Ctrl + Alt + T）。
2. 使用 curl 命令下载 Vim-Plug：
   ```bash
   curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
   ```
3. 确保插件目录存在。如果不存在，执行以下命令创建目录：
   ```bash
   mkdir -p ~/.vim/plugged
   ```

### 步骤 2：编辑 .vimrc 文件

1. 使用 Vim 打开 `.vimrc` 配置文件，如果该文件不存在则创建它：
   ```bash
   vim ~/.vimrc
   ```
2. 在 `.vimrc` 文件中添加以下内容，这会告诉 Vim 使用 Vim-Plug 管理插件：
   ```vim
   " Vim-Plug 设置
   call plug#begin('~/.vim/plugged')

   " 安装 C++ 相关插件
   Plug 'octol/vim-cpp-enhanced-highlight'
   " 其他插件...

   call plug#end()
   ```
   在 `call plug#begin()` 和 `call plug#end()` 之间的区域是用于列出要安装的插件的地方。

### 步骤 3：安装插件

1. 保存并关闭 `.vimrc` 文件（在 Vim 中执行 `:wq`）。
2. 重新打开 Vim。
3. 在 Vim 中输入以下命令安装列出的插件：
   ```vim
   :PlugInstall
   ```
4. 按下 Enter 键开始安装所列的插件。

### 步骤 4：配置插件

安装完成后，根据您安装的插件类型和需求，可能需要进行一些额外的配置步骤。这些步骤通常可以在每个插件的 GitHub 页面或文档中找到。

这些步骤将帮助您在 Ubuntu 上使用 Vim-Plug 安装 C++ 相关的插件，以便在 Vim 编辑器中更轻松地开发和编辑 C++ 代码。

## Ubuntu vim-plug C++代码补全插件

在 Ubuntu 上，有几个流行的 Vim 插件可以用于 C++ 代码补全，其中最知名的是 **YouCompleteMe** 和 **coc.nvim**。

#### YouCompleteMe

YouCompleteMe 是一个功能强大的 Vim 插件，提供了高效的代码补全功能，并支持多种编程语言，包括 C++。要安装 YouCompleteMe 插件，请按照以下步骤操作：

1. 首先，确保您已经按照上面提供的步骤安装了 Vim-Plug 插件管理器。
2. 在您的 `.vimrc` 配置文件中添加 YouCompleteMe 插件：
   ```vim
   " Vim-Plug 设置
   call plug#begin('~/.vim/plugged')

   " 安装 YouCompleteMe 插件
   Plug 'ycm-core/YouCompleteMe', { 'do': './install.py' }
   " 其他插件...

   call plug#end()
   ```
3. 保存并关闭 `.vimrc` 文件（在 Vim 中执行 `:wq`）。
4. 重新打开 Vim。
5. 在 Vim 中输入以下命令来安装 YouCompleteMe 插件：
   ```vim
   :PlugInstall
   ```
6. 安装完成后，进入 `~/.vim/plugged/YouCompleteMe` 目录，并执行以下命令进行 YCM 插件的编译安装：
   ```bash
   python3 install.py --clangd-completer
   ```

#### coc.nvim

另一个流行的 Vim 插件是 coc.nvim，它是一个具有高级特性的插件，可提供 C++ 代码补全和 IntelliSense 功能。安装步骤如下：

1. 确保您已经按照上述步骤安装了 Vim-Plug 插件管理器。
2. 在您的 `.vimrc` 配置文件中添加 coc.nvim 插件：
   ```vim
   " Vim-Plug 设置
   call plug#begin('~/.vim/plugged')

   " 安装 coc.nvim 插件
   Plug 'neoclide/coc.nvim', {'branch': 'release'}
   " 其他插件...

   call plug#end()
   ```
3. 保存并关闭 `.vimrc` 文件（在 Vim 中执行 `:wq`）。
4. 重新打开 Vim。
5. 在 Vim 中输入以下命令安装 coc.nvim 插件：
   ```vim
   :PlugInstall
   ```
6. 安装完成后，在 Vim 中使用 `:CocInstall coc-clangd` 安装 C++ 相关的语言服务器。

安装完成后，您可以根据需要配置这些插件以满足您的需求，并享受更加便捷的 C++ 开发体验。

## vim 删除指定插件

要从 Vim 中删除插件，你需要编辑你的 `.vimrc` 文件，找到包含你想删除插件的行，并将其删除。然后保存文件并退出 Vim。

假设你正在使用 Vim-Plug 来管理你的插件，你可以按照以下步骤来删除一个插件：

1. 打开终端并输入以下命令以编辑你的 `.vimrc` 文件：
   ```bash
   vim ~/.vimrc
   ```

2. 找到你想要删除的插件的配置行。它们通常具有 `Plug` 字样。比如：
   ```vim
   Plug 'some-plugin'
   ```

3. 将你想要删除的插件的配置行从 `.vimrc` 文件中删除。

4. 保存并关闭文件。你可以按下 `Esc` 键，然后输入 `:wq` 并按回车键保存并退出。

5. 重新打开 Vim，然后执行 `:PlugClean` 命令，它会删除未在 `.vimrc` 文件中列出的任何插件。

这样就完成了删除插件的操作。请记住，这些步骤可能因你的插件管理器或特定的插件而有所不同，因此你需要根据你自己的情况进行调整。