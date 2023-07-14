## 简介

+ shell脚本编程的常用方法

## 判断变量是否为空

在 Linux Shell 脚本中，可以使用不同的方式来判断一个变量是否为空。以下是几种常用的方法：

1. **使用 if-else 语句**：
   ```bash
   if [ -z "$var" ]; then
     echo "变量为空"
   else
     echo "变量不为空"
   fi
   ```

   在上述示例中，使用 `-z` 表达式来判断变量 `$var` 是否为空。如果为空，则执行 if 语句块中的命令；如果不为空，则执行 else 语句块中的命令。

2. **使用双引号和等号比较**：
   ```bash
   if [ "$var" = "" ]; then
     echo "变量为空"
   else
     echo "变量不为空"
   fi
   ```

   这种方式使用双引号将变量引起来，并与空字符串进行等号比较，判断变量是否为空。

3. **使用双括号和双引号**：
   ```bash
   if [[ -z "$var" ]]; then
     echo "变量为空"
   else
     echo "变量不为空"
   fi
   ```

   在这种方式中，使用双括号 `[[ ... ]]` 来进行条件判断，并使用双引号将变量引起来。

需要注意的是，变量前面的 `$` 符号需要加上双引号，这样可以避免在变量为空时引发语法错误。

这些是常用的方式来判断一个变量是否为空。根据具体的需求和脚本环境，您可以选择适合您的方式来进行变量的判空操作。

希望这些解释对您有所帮助！如果您有更多问题，请随时提问。

## 获取时间

在 Shell 脚本中，可以使用 `date` 命令来获取当前的时间和日期。

要获取当前的完整时间，可以使用以下命令：

```bash
current_time=$(date +%T)
echo "当前时间：$current_time"
```

该命令使用 `%T` 格式化选项来获取当前时间，并将结果保存在 `current_time` 变量中。

如果你只需要获取当前的日期，可以使用以下命令：

```bash
current_date=$(date +%F)
echo "当前日期：$current_date"
```

这里使用 `%F` 格式化选项来获取当前日期，并将结果保存在 `current_date` 变量中。

`date` 命令还有很多其他的格式化选项，你可以根据需求选择适合你的日期和时间格式。使用 `man date` 命令可以查看 `date` 命令的完整文档，其中包含了所有的格式化选项和用法示例。

除了 `date` 命令，还可以使用其他 Shell 内建的变量来获取当前时间和日期。例如：

- 获取当前时间戳：

  ```bash
  current_timestamp=$(date +%s)
  echo "当前时间戳：$current_timestamp"
  ```

- 获取当前年份：

  ```bash
  current_year=$(date +%Y)
  echo "当前年份：$current_year"
  ```

- 获取当前月份：

  ```bash
  current_month=$(date +%m)
  echo "当前月份：$current_month"
  ```

等等，根据具体需求选择适合的日期和时间信息。

---

## gsettings 常用示例

以下是一些常见的 `gsettings` 命令示例，涵盖了不同的设置类别：

1. 修改桌面背景图片：
   ```bash
   gsettings set org.gnome.desktop.background picture-uri 'file:///path/to/image.jpg'
   ```

2. 修改桌面壁纸平铺方式：
   ```bash
   gsettings set org.gnome.desktop.background picture-options 'scaled'
   ```

3. 修改桌面图标显示/隐藏：
   ```bash
   gsettings set org.gnome.desktop.background show-desktop-icons false
   ```

4. 修改窗口主题：
   ```bash
   gsettings set org.gnome.desktop.wm.preferences theme 'Adwaita'
   ```

5. 修改默认浏览器：
   ```bash
   gsettings set org.gnome.desktop.default-applications.web-browser 'firefox.desktop'
   ```

6. 修改鼠标双击行为：
   ```bash
   gsettings set org.gnome.desktop.peripherals.mouse double-click true
   ```

7. 修改键盘重复延迟和速度：
   ```bash
   gsettings set org.gnome.desktop.peripherals.keyboard delay 200
   gsettings set org.gnome.desktop.peripherals.keyboard repeat-interval 20
   ```

8. 修改屏幕亮度调节方式：
   ```bash
   gsettings set org.gnome.settings-daemon.plugins.power idle-dim false
   ```

这些示例只是 `gsettings` 命令的一小部分。你可以通过查阅相关的文档或使用 `gsettings list-schemas`、`gsettings list-keys SCHEMA` 等命令来探索更多可用的设置和键。

请注意，命令中的 `SCHEMA` 和 `KEY` 根据要修改的设置不同而有所变化。确保替换命令中的占位符为适当的值。

---

## gsettings 打开 关闭 代理

在Ubuntu中，你可以使用`gsettings`命令来打开和关闭代理设置。以下是相关的命令示例：

打开代理：
```
gsettings set org.gnome.system.proxy mode 'manual'
gsettings set org.gnome.system.proxy.http host 'proxy.example.com'
gsettings set org.gnome.system.proxy.http port 8080
```
将 `'proxy.example.com'` 替换为你的代理服务器地址，`8080` 替换为代理服务器端口号。

关闭代理：
```
gsettings set org.gnome.system.proxy mode 'none'
```

这些命令将设置系统代理模式为手动（manual）并指定代理服务器的地址和端口。关闭代理时，将把系统代理模式设置为无（none）。

请注意，这些命令基于 GNOME 桌面环境的代理设置。如果你使用的是其他桌面环境，可能会有不同的命令或配置文件用于管理代理设置。

另外，使用`gsettings`命令修改的代理设置将在整个系统范围内生效，包括各个应用程序和网络连接。你可能需要重新启动一些应用程序或系统才能使代理设置生效。

---

## linux Ctrl 快捷命令

在Linux中，Ctrl键（Control键）结合其他键组合可以触发各种快捷命令。下面是一些常用的Ctrl快捷键及其功能的详细解释：

1. Ctrl+C：发送中断信号（SIGINT）给当前正在前台运行的进程，用于中断（终止）进程的执行。

2. Ctrl+Z：发送暂停信号（SIGTSTP）给当前正在前台运行的进程，将其挂起并放入后台。可以使用`fg`命令将其重新放到前台运行，或使用`bg`命令将其转换为后台运行。

3. Ctrl+D：表示输入流结束，用于退出交互式shell。当你在终端中输入Ctrl+D时，它会告诉shell当前输入结束，然后触发相应的行为，如关闭当前终端会话或退出交互式程序。

4. Ctrl+L：清除终端屏幕，等效于使用`clear`命令。它将当前终端窗口的内容滚动到顶部，使终端屏幕变为空白。

5. Ctrl+A：将光标移到命令行的开头。

6. Ctrl+E：将光标移到命令行的末尾。

7. Ctrl+K：删除光标位置到命令行末尾的文本。

8. Ctrl+U：删除光标位置到命令行开头的文本。

9. Ctrl+W：删除光标之前的一个单词。

10. Ctrl+R：在命令历史中进行反向搜索。

11. Ctrl+G：取消当前的编辑或操作，放弃正在进行的命令。

这些是一些常见的Ctrl快捷键，在Linux终端中使用频率很高。它们可以帮助你更高效地控制终端会话、编辑命令行以及与进程进行交互。请注意，某些快捷键在特定的应用程序或环境中可能会有不同的功能或效果。

---

## linux alt 快捷命令

在Linux中，Alt键（也称为Meta键或Option键）结合其他键组合可以触发各种快捷命令。下面是一些常用的Alt快捷键及其功能的简要说明：

1. Alt+Tab：在打开的窗口之间切换。按下Alt键并保持按住，然后连续按下Tab键可以切换到下一个窗口。松开Alt键时，所选的窗口将被激活。

2. Alt+F4：关闭当前活动的窗口。按下Alt键并保持按住，然后按下F4键可以关闭当前窗口。

3. Alt+Space：打开窗口菜单。按下Alt键并保持按住，然后按下Space键可以打开当前窗口的菜单选项，例如最大化、最小化、移动等。

4. Alt+Enter：在终端中切换全屏模式。按下Alt键并保持按住，然后按下Enter键可以在终端窗口之间切换全屏模式。

5. Alt+Up/Down：在终端中上下滚动。按下Alt键并保持按住，然后按下上箭头或下箭头键可以在终端中上下滚动输出。

6. Alt+Left/Right：在终端中左右切换。按下Alt键并保持按住，然后按下左箭头或右箭头键可以在终端中左右切换命令。

这些是一些常见的Alt快捷键，在Linux中使用频率较高。请注意，某些快捷键可能因特定的桌面环境、窗口管理器或应用程序而有所不同。此外，Alt键也常用于与其他键组合以实现特定功能，具体取决于应用程序的键绑定设置。

## clear 清除屏幕信息  ctrl+L

在Linux中，`clear`命令用于清除当前终端窗口上的内容，使其变为空白屏幕，以提供一个干净的工作环境。

使用`clear`命令非常简单，只需在终端中键入以下命令即可：

```shell
clear
```

执行该命令后，当前终端窗口中的所有文本和输出将被清除，终端将变为空白屏幕，光标回到终端的起始位置。

`clear`命令常用于清除终端中的大量输出或命令的执行结果，以便获得更好的可读性和清晰度。当终端窗口中显示的内容过多或杂乱时，使用`clear`命令可以快速清除屏幕并重新开始。

需要注意的是，`clear`命令只会清除当前终端窗口的内容，并不会影响其他终端或窗口的显示。当你切换到其他终端或打开新的终端窗口时，之前的内容仍然可见。

除了`clear`命令，你也可以使用快捷键`Ctrl + L`来达到相同的效果，它可以清除当前终端窗口的内容。

总结起来，`clear`命令用于清除当前终端窗口的内容，使其变为空白屏幕。这是一个简单但实用的命令，可以提供一个干净的工作环境。

---

## 查看目录下所有文件的行数

要查看Linux中一个目录下所有文件的行数，可以使用`find`命令与`wc`命令的组合。以下是一个示例命令：

```shell
find /path/to/directory -type f -exec cat {} + | wc -l
```

请替换`/path/to/directory`为你想要查看的目录的实际路径。

该命令的解释如下：

- `find /path/to/directory`：查找指定目录下的所有文件。
- `-type f`：限定只查找普通文件，排除目录和其他特殊文件。
- `-exec cat {} +`：对找到的每个文件执行`cat`命令，将文件内容输出到标准输出。
- `|`：将`cat`命令的输出通过管道传递给下一个命令。
- `wc -l`：对输入进行行数统计，输出总行数。

执行该命令后，会输出指定目录下所有文件的总行数。

请注意，如果目录下的文件较多或文件较大，这个命令可能需要一些时间来完成执行。另外，该命令只统计文件中的行数，不包括空行和文件夹的行数。

---

## 根据进程名 获取进程id

在Shell脚本中，可以使用`pgrep`命令来根据进程名获取进程ID（PID）。`pgrep`命令可以根据进程名模式匹配正在运行的进程，并返回符合条件的进程ID。

以下是一个示例Shell脚本，演示如何使用`pgrep`命令获取进程ID：

```bash
#!/bin/bash

process_name="example_process"  # 设置进程名

# 使用pgrep命令获取进程ID
pid=$(pgrep "$process_name")

if [ -n "$pid" ]; then
    echo "进程 $process_name 的PID为: $pid"
else
    echo "未找到进程 $process_name"
fi
```

在上述示例中，首先定义了要查找的进程名为`example_process`。然后，使用`pgrep`命令和进程名作为参数来获取进程ID。如果找到了符合条件的进程，`$pid`变量将保存进程ID，并打印出来。如果未找到进程，则打印相应的提示信息。

可以将上述脚本保存为`.sh`文件，并在Shell环境中运行，即可根据进程名获取进程ID。

需要注意的是，`pgrep`命令还支持其他选项，如根据用户、进程所属终端等条件进行进程查找。您可以通过`man pgrep`命令查看`pgrep`命令的详细用法和选项。