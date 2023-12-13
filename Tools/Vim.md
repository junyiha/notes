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

## Vim-plug

### 安装

+ 运行命令:
  + curl -fLo ~/.vim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

### 用法

+ 安装插件
  + 要安装插件，你必须如下所示首先在 Vim 配置文件中声明它们。一般 Vim 的配置文件是  ~/.vimrc
  + 请记住，当你在配置文件中声明插件时，列表应该以 call plug#begin(PLUGIN_DIRECTORY) 开始，并以 plug#end() 结束。
  + 例如，我们安装 “lightline.vim” 插件。为此，请在 ~/.vimrc 的顶部添加以下行。
```bash
call plug#begin('~/.vim/plugged')
Plug 'itchyny/lightline.vim'
call plug#end()
```

### 检查状态

+ 使用以下命令检查状态：
  + :PlugStatus

### 安装插件

+ 使用以下命令安装：
  + :PlugInstall

### 更新插件

+ 要更新插件，请运行：
  + :PlugUpdate
+ 更新插件后，按下 d 查看更改。或者，你可以之后输入 :PlugDiff。

### 审查插件

+ 有时，更新的插件可能有新的 bug 或无法正常工作。要解决这个问题，你可以简单地回滚有问题的插件。输入 :PlugDiff 命令，然后按回车键查看上次 :PlugUpdate的更改，并在每个段落上按 X 将每个插件回滚到更新前的前一个状态。

### 删除插件

+ 删除一个插件删除或注释掉你以前在你的 vim 配置文件中添加的 plug 命令。然后，运行 :source ~/.vimrc 或重启 Vim 编辑器。最后，运行以下命令卸载插件：
  + :PlugClean
+ 该命令将删除 vim 配置文件中所有未声明的插件。

## 升级 Vim-plug

+ 要升级vim-plug本身，请输入：
  + :PlugUpgrade

## NERDTree

+ 这个插件是几乎所有研发人员都会安装的一个插件——目录树，可以支持在不退出vim的编辑器的前提下，在文件中快速切换，同时能让开发人员快速掌握项目目录结构，是提升开发效率必不可少的工具

+ 安装
```bash
call plug#begin()
Plug 'preservim/nerdtree'
call plug#end()
```

+ 配置
  + NERDTree默认无须配置即可直接使用，当然更改部分映射后，可以使得目录树试用起来更加得心应手。最常见的配置在~/.vimrc添加如下命令，即可使用Ctrl+n快速开启目录树。
```bash
map <C-n> :NERDTreeToggle<CR>
```

+ 使用
  + 目录树的使用主要通过在vim的command模式下键入如下命令，即可达到相应的效果。
  + ?: 快速帮助文档
  + o: 打开一个目录或者打开文件，创建的是 buffer，也可以用来打开书签
  + go: 打开一个文件，但是光标仍然留在 NERDTree，创建的是 buffer
  + t: 打开一个文件，创建的是Tab，对书签同样生效
  + T: 打开一个文件，但是光标仍然留在 NERDTree，创建的是 Tab，对书签同样生效
  + i: 水平分割创建文件的窗口，创建的是 buffer
  + gi: 水平分割创建文件的窗口，但是光标仍然留在 NERDTree
  + s: 垂直分割创建文件的窗口，创建的是 buffer
  + gs: 和 gi，go 类似
  + x: 收起当前打开的目录
  + X: 收起所有打开的目录
  + e: 以文件管理的方式打开选中的目录
  + D: 删除书签