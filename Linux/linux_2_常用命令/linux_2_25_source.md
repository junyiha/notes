## 简介

+ source命令

## source  

+ source命令（从 C Shell而来）是`bash shell`的内置命令； `.` 点命令，就是一个点符号，是source的另一名称。这两个命令都以一个脚本为参数，该脚本将在当前shell的环境执行，即** 不会启动一个新的子shell** 。所有在脚本中设置的变量都将成为当前shell的一部分
+ source命令的妙用：
  + 在编译核心时，常常要反复输入一长串命令。这些命令即长又繁琐，而且有时候容易输错。
  + 如果把命令做成一个文件，让它自动执行，对于需要多次反复编译核心的用户来说，会很方便
  + 用source命令可以做到这一点。** 它的作用就是把一个文件的内容当成是shell来执行** 
+ `source filename, sh filename, ./filename`
  + 当shell脚本具有可执行权限时，用`sh filename`与`./filename`执行脚本没有区别。 `./filename`是因为当前目录没有在`PATH`, 所有`.` 都是用来表示当前目录的

在Linux中，`source`命令用于在当前Shell环境中执行指定的脚本文件，并将其内容加载到当前Shell会话中。它通常用于加载和执行Shell脚本，以便在当前Shell会话中设置环境变量、函数和其他Shell配置。

以下是`source`命令的一般语法：

```
source filename
```

或者可以使用点号(`.`)来代替`source`命令：

```
. filename
```

其中，`filename`是要执行的脚本文件的名称，可以是相对路径或绝对路径。

`source`命令的作用是将指定的脚本文件的内容作为当前Shell会话的一部分来执行，而不是在一个单独的子Shell中执行。这意味着在执行完脚本后，其中定义的变量、函数和别名将在当前Shell环境中保持可用。

使用`source`命令的一些常见用例包括：

1. 加载Shell配置文件：
   ```
   source ~/.bashrc
   ```

   此命令将加载用户主目录下的`.bashrc`文件中定义的配置，使得配置的环境变量、别名等在当前Shell会话中生效。

2. 执行Shell脚本：
   ```
   source script.sh
   ```

   此命令将执行`script.sh`脚本文件，并将脚本中的内容加载到当前Shell环境中。

需要注意的是，`source`命令是在当前Shell环境中执行脚本，因此需要确保脚本文件具有可执行权限。

使用`source`命令可以方便地在当前Shell会话中加载和执行脚本文件，将脚本中定义的变量、函数和其他配置设置直接应用于当前环境。

## linux source命令 详解

`source` 命令是在 Bash（Bourne Again SHell）中使用的一个内置命令，它用于在当前 Shell 环境中执行指定脚本文件，通常是用来加载配置文件或者在当前 Shell 环境中应用一些设置。以下是关于 `source` 命令的详细解释：

### 1. 基本用法

`source` 命令的基本语法如下：

```bash
source filename
```

或者使用缩写形式：

```bash
. filename
```

其中 `filename` 是要执行的脚本文件的路径。

### 2. 作用

`source` 的主要作用是在当前 Shell 环境中运行指定的脚本，而不是创建一个新的子 Shell 来执行脚本。这与直接运行脚本的区别在于，直接运行脚本会在一个新的子 Shell 中执行，而 `source` 会在当前 Shell 环境中执行，因此它可以影响当前 Shell 的环境变量和状态。

### 3. 使用场景

- **加载配置文件：** 常见的用法是在登录时加载用户的配置文件，比如 `~/.bashrc` 或 `~/.bash_profile` 文件。这样，用户定义的环境变量、别名和函数将在登录后的每个 Shell 会话中生效。

```bash
source ~/.bashrc
```

- **应用设置和变更：** 当你修改了一个 Shell 脚本或配置文件，并希望立即应用这些变更而不用关闭当前的 Shell 会话时，可以使用 `source` 命令。

```bash
source myscript.sh
```

### 4. 注意事项

- **点号 `.` 与 `source` 的等价性：** 在 Bash 中，`.`（点号）和 `source` 是等价的，它们都用于执行脚本文件。例如：

  ```bash
  . myscript.sh
  ```

- **文件路径：** 如果文件路径中包含空格，最好将路径用引号括起来：

  ```bash
  source "path with spaces/myscript.sh"
  ```

- **退出状态：** 如果脚本执行成功，`source` 命令将返回 0；如果出现错误，返回非零值。

### 5. 示例

假设有一个脚本文件 `myscript.sh` 包含以下内容：

```bash
# myscript.sh
export MY_VARIABLE="Hello, World!"
```

使用 `source` 命令应用该脚本：

```bash
source myscript.sh
echo $MY_VARIABLE
```

上述代码执行后，`$MY_VARIABLE` 将在当前 Shell 中生效，并输出 "Hello, World!"。

总的来说，`source` 命令是一个方便的工具，用于在当前 Shell 环境中执行脚本，使得对环境变量和设置的修改能够立即生效。

## linux source命令 详解

`source` 命令用于在当前 Shell 环境中执行指定的脚本文件，通常用于加载配置文件或在当前 Shell 中应用一些设置。在 Bash 中，`.`（点号）也可以用于执行脚本文件，它与 `source` 是等价的。以下是关于 `source` 命令的详细解释：

### 1. 基本语法

```bash
source filename [arguments]
```

或者使用点号的缩写形式：

```bash
. filename [arguments]
```

其中，`filename` 是脚本文件的路径，而 `arguments` 是传递给脚本的参数。

### 2. 作用

`source` 命令的主要作用是在当前 Shell 环境中运行指定的脚本，而不是创建一个新的子 Shell。这意味着脚本中的变量、函数和其他环境设置将直接影响当前 Shell。

### 3. 使用场景

- **加载配置文件：** 常见的用法是在登录时加载用户的配置文件，例如 `~/.bashrc` 或 `~/.bash_profile` 文件。通过 `source` 命令，用户定义的环境变量、别名和函数将在每个新的 Shell 会话中生效。

    ```bash
    source ~/.bashrc
    ```

- **应用设置和变更：** 当修改了一个 Shell 脚本或配置文件，并希望立即应用这些变更而不用重新启动 Shell 时，可以使用 `source` 命令。

    ```bash
    source myscript.sh
    ```

### 4. 注意事项

- **点号 `.` 与 `source` 的等价性：** 在 Bash 中，`.`（点号）和 `source` 是等价的，它们都用于执行脚本文件。例如：

    ```bash
    . myscript.sh
    ```

- **文件路径中的空格：** 如果文件路径中包含空格，最好将路径用引号括起来。

    ```bash
    source "path with spaces/myscript.sh"
    ```

- **退出状态：** 如果脚本执行成功，`source` 命令将返回 0；如果出现错误，返回非零值。

### 5. 示例

假设有一个脚本文件 `myscript.sh` 包含以下内容：

```bash
# myscript.sh
export MY_VARIABLE="Hello, World!"
```

使用 `source` 命令应用该脚本：

```bash
source myscript.sh
echo $MY_VARIABLE
```

上述代码执行后，`$MY_VARIABLE` 将在当前 Shell 中生效，并输出 "Hello, World!"。

总的来说，`source` 命令是一个有用的工具，特别是在需要在当前 Shell 中应用配置或设置时，可以确保变量和环境的改变在当前 Shell 中生效。