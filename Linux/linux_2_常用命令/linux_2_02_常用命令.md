## 简介

+ linux环境下常用命令 第二部分

## gnome-screensaver-command 

`gnome-screensaver-command` 是用于与 GNOME 屏幕保护程序交互的命令行工具。它允许你控制屏幕保护程序的状态、设置和操作。

以下是一些常用的 `gnome-screensaver-command` 命令及其功能：

- `gnome-screensaver-command -a`：激活屏幕保护程序。这会立即启动屏幕保护程序并锁定屏幕，要解锁屏幕，你需要提供用户密码。
- `gnome-screensaver-command -d`：禁用屏幕保护程序。这会关闭屏幕保护程序的自动启动和锁定屏幕的功能。
- `gnome-screensaver-command -q`：查询屏幕保护程序的状态。它会返回屏幕保护程序是否激活和屏幕是否锁定的信息。
- `gnome-screensaver-command -l`：锁定屏幕。这会立即锁定屏幕，要解锁屏幕，你需要提供用户密码。

这些是 `gnome-screensaver-command` 命令的一些示例。通过使用不同的选项，你可以进行更多的配置和操作，如设置屏幕保护程序的超时时间、配置锁定屏幕的效果等。

需要注意的是，`gnome-screensaver-command` 命令仅在使用 GNOME 桌面环境的 Linux 系统中可用。对于其他桌面环境或窗口管理器，可能有不同的命令或工具来控制屏幕保护程序。

希望这个解释对你有帮助！如有需要，请随时提问。

---

## pulseaudio

PulseAudio 是 Linux 上广泛使用的音频服务器和音频子系统。它提供了许多命令行工具来管理和控制音频设备、音频流和音量等。下面是一些常用的 PulseAudio 命令及其详解：

1. `pacmd`：`pacmd` 是 PulseAudio 的命令行控制界面，可以用于交互式地管理和监视 PulseAudio。通过输入 `pacmd` 进入交互模式，然后可以使用以下命令：

   - `list-sinks`：列出所有可用的音频输出设备（音频输出设备称为 "sink"）。

   - `list-sources`：列出所有可用的音频输入设备（音频输入设备称为 "source"）。

   - `list-clients`：列出所有当前连接到 PulseAudio 的客户端应用程序。

   - `set-default-sink`：设置默认的音频输出设备。

   - `set-default-source`：设置默认的音频输入设备。

   - `set-sink-volume`：设置音频输出设备的音量。

   - `set-source-volume`：设置音频输入设备的音量。

   - `exit`：退出 `pacmd` 交互模式。

2. `pactl`：`pactl` 是 PulseAudio 的控制命令行工具，用于控制 PulseAudio 的运行状态和配置。下面是一些常用的 `pactl` 命令：

   - `pactl list`：列出当前 PulseAudio 状态的概览，包括音频设备、音频流和音量等信息。

   - `pactl set-sink-volume`：设置音频输出设备的音量。

   - `pactl set-source-volume`：设置音频输入设备的音量。

   - `pactl set-default-sink`：设置默认的音频输出设备。

   - `pactl set-default-source`：设置默认的音频输入设备。

   - `pactl suspend`：暂停或恢复 PulseAudio 服务器。

   - `pactl exit`：停止 PulseAudio 服务器。

3. `pavucontrol`：`pavucontrol` 是 PulseAudio 的图形用户界面控制面板，用于图形化地管理和控制 PulseAudio。可以通过命令行运行 `pavucontrol` 启动它。

   `pavucontrol` 提供了一个用户友好的界面，可以查看和调整每个应用程序的音频流、音量和音频设备等设置。

这些命令只是 PulseAudio 提供的一部分工具和功能。你可以根据需要查阅相关文档和手册，或者使用命令的 `--help` 选项获取更详细的命令说明和选项信息。

---
## alsamixer

`alsamixer` 是 Linux 上用于调整 ALSA（Advanced Linux Sound Architecture）音频驱动的命令行工具。它提供了一个终端界面，允许你调整音频设备的音量、通道设置和其他音频参数。下面是一些常用的 `alsamixer` 命令及其详解：

1. `alsamixer`：直接运行 `alsamixer` 命令将打开一个终端窗口，显示当前音频设备的音量控制界面。

   - 使用左右箭头键切换不同的音频通道（如果有多个通道可用）。
   - 使用上下箭头键调整当前通道的音量。
   - 使用空格键切换静音状态。
   - 使用 Esc 键退出 `alsamixer`。

2. `alsamixer -c <card>`：使用 `-c` 选项指定要控制的音频设备（声卡）。可以通过 `<card>` 参数指定声卡的编号或标识符。例如，`alsamixer -c 0` 或 `alsamixer -c hw:0`。

3. `alsamixer -V <view>`：使用 `-V` 选项指定要显示的视图。视图可以是 `Playback`（播放），`Capture`（捕获）或 `All`（全部）。例如，`alsamixer -V Capture` 将只显示捕获设备的音量控制界面。

4. `alsamixer -D <device>`：使用 `-D` 选项指定要控制的特定音频设备。可以通过 `<device>` 参数指定设备的名称或标识符。例如，`alsamixer -D hw:0,0`。

5. `alsamixer -h` 或 `alsamixer --help`：显示 `alsamixer` 命令的帮助信息，包括可用选项和用法示例。

通过 `alsamixer`，你可以调整音频设备的音量、平衡、增益和其他音频控制参数。请注意，使用 `alsamixer` 进行的更改是实时的，不会永久保存。如果你希望在系统启动时应用特定的音频设置，可能需要考虑其他方法，例如 ALSA 的配置文件或其他工具。

在使用 `alsamixer` 时，如果遇到问题或需要进一步了解每个选项的详细说明，可以参考 ALSA 的官方文档或手册。

---

---

## aplay 

`aplay` 是 Linux 系统上的命令行音频播放工具，它使用 ALSA（Advanced Linux Sound Architecture）来播放音频文件。下面是对 `aplay` 命令的详细解释：

1. `aplay <file>`：直接运行 `aplay` 命令并指定音频文件作为参数，将会播放该音频文件。例如，`aplay audio.wav` 将会播放名为 "audio.wav" 的音频文件。

2. `aplay -l`：使用 `-l` 选项可以列出系统上可用的音频设备（声卡）列表。它会显示设备的编号、名称和硬件信息等。

3. `aplay -D <device>`：使用 `-D` 选项可以指定要使用的音频设备。可以通过 `<device>` 参数指定设备的名称或标识符。例如，`aplay -D hw:0,0 audio.wav` 将会使用 `hw:0,0` 设备播放 "audio.wav" 文件。

4. `aplay -f <format>`：使用 `-f` 选项可以指定音频文件的格式。可以通过 `<format>` 参数指定格式，如 `S16_LE`、`S24_LE`、`float_le` 等。

5. `aplay -r <rate>`：使用 `-r` 选项可以指定音频文件的采样率。可以通过 `<rate>` 参数指定采样率的数值。

6. `aplay -c <channels>`：使用 `-c` 选项可以指定音频文件的通道数。可以通过 `<channels>` 参数指定通道数的数值。

7. `aplay -t <duration>`：使用 `-t` 选项可以指定音频文件的播放时长。可以通过 `<duration>` 参数指定播放时长的数值和单位，如 `10s`、`2m` 等。

8. `aplay -q`：使用 `-q` 选项可以启用静默模式，即不显示播放进度和其他信息。

9. `aplay --help`：使用 `--help` 选项可以显示 `aplay` 命令的帮助信息，包括可用选项和用法示例。

这些选项只是 `aplay` 命令的一部分，你可以根据需要查阅 `aplay` 的手册页或使用命令的 `--help` 选项获取更详细的命令说明和选项信息。

通过 `aplay`，你可以在 Linux 系统上播放音频文件。它对于测试音频设备、验证音频配置和简单的音频播放任务非常有用。

---

## modprobe

`modprobe` 是 Linux 系统上的一个命令行工具，用于动态加载和卸载内核模块（驱动程序）。它可以根据模块的名称自动加载相应的内核模块，并处理模块之间的依赖关系。下面是对 `modprobe` 命令的详细解释：

1. `modprobe <module>`：直接运行 `modprobe` 命令并指定模块名称作为参数，将会尝试加载该模块。例如，`modprobe snd_usb_audio` 将会加载名为 "snd_usb_audio" 的内核模块。

2. `modprobe -r <module>`：使用 `-r` 选项可以卸载指定的内核模块。例如，`modprobe -r snd_usb_audio` 将会卸载名为 "snd_usb_audio" 的内核模块。

3. `modprobe -l`：使用 `-l` 选项可以列出所有可用的内核模块。它会显示模块的路径和名称。

4. `modprobe -a <module>`：使用 `-a` 选项可以加载指定模块及其所有依赖的模块。它会自动处理模块之间的依赖关系。

5. `modprobe -c`：使用 `-c` 选项可以显示当前加载的内核模块的配置信息。它会列出每个模块的配置参数。

6. `modprobe -n <module>`：使用 `-n` 选项可以检查指定模块是否可加载，但不实际加载它。它会输出一个表示模块是否可加载的消息。

7. `modprobe -v <module>`：使用 `-v` 选项可以显示详细的加载信息，包括加载的模块及其依赖关系。

8. `modprobe -d <directory>`：使用 `-d` 选项可以指定要搜索模块的目录。默认情况下，`modprobe` 将搜索默认的模块目录。

9. `modprobe -h` 或 `modprobe --help`：显示 `modprobe` 命令的帮助信息，包括可用选项和用法示例。

通过 `modprobe` 命令，你可以在 Linux 系统上动态加载和卸载内核模块。这对于根据需要加载所需的驱动程序或模块、解决硬件兼容性问题以及进行模块调试和配置非常有用。请注意，你可能需要以超级用户权限（root 或使用 `sudo` 命令）运行 `modprobe` 命令，以便加载或卸载内核模块。

希望这些信息能帮助你理解和使用 `modprobe` 命令。如有需要，你可以参考相关文档或手册以获取更多详细信息。

---

## insmod 

`insmod` 是 Linux 系统上的一个命令行工具，用于手动加载内核模块（驱动程序）到内核中。它可以加载指定的内核模块并将其插入当前运行的内核中。下面是对 `insmod` 命令的详细解释：

1. `insmod <module>`：直接运行 `insmod` 命令并指定模块名称作为参数，将会尝试加载该模块。例如，`insmod mymodule.ko` 将会加载名为 "mymodule.ko" 的内核模块。

2. `insmod -f <module>`：使用 `-f` 选项可以强制加载指定的内核模块，即使模块已经加载过。注意，这可能导致冲突或意外行为，因此谨慎使用该选项。

3. `insmod -r <module>`：使用 `-r` 选项可以卸载指定的内核模块。注意，使用 `insmod -r` 只会从内核中卸载模块，而不会处理模块的依赖关系。因此，如果有其他模块依赖于该模块，则可能导致系统不稳定。

4. `insmod -l <module>`：使用 `-l` 选项可以指定模块文件的路径，而不是使用当前目录。例如，`insmod -l /path/to/modules/mymodule.ko` 将加载指定路径下的内核模块。

5. `insmod -s <symbol>`：使用 `-s` 选项可以指定要加载的模块中的符号（函数或变量）。这在需要仅加载模块中的特定符号时很有用。

6. `insmod -h` 或 `insmod --help`：显示 `insmod` 命令的帮助信息，包括可用选项和用法示例。

需要注意的是，使用 `insmod` 命令手动加载内核模块需要具有超级用户权限（root 或使用 `sudo` 命令）。加载模块前，你需要确保该模块的二进制文件（`.ko` 文件）存在，并且与当前运行的内核版本兼容。

希望这些信息能帮助你理解和使用 `insmod` 命令。如有需要，你可以参考相关文档或手册以获取更多详细信息。

---

## ubuntu-drivers devices

`ubuntu-drivers devices` 是一个 Ubuntu 系统上的命令，用于列出可用的硬件驱动程序。它会扫描系统上的硬件设备，并显示适用于这些设备的推荐和可选驱动程序。下面是对 `ubuntu-drivers devices` 命令的详细解释：

1. `ubuntu-drivers devices`：直接运行 `ubuntu-drivers devices` 命令将列出系统中的硬件设备以及可用的驱动程序信息。

2. 输出格式：命令的输出结果包含了设备的厂商、型号和设备标识符等信息，以及推荐和可选驱动程序的名称。

3. 推荐驱动程序：在输出结果中，推荐的驱动程序被标记为 "recommended"，表示它们是最适合该设备的驱动程序。这些驱动程序通常由 Ubuntu 官方维护，并且在兼容性和稳定性方面经过测试。

4. 可选驱动程序：在输出结果中，可选的驱动程序被标记为 "proprietary"，表示它们是由硬件厂商提供的专有驱动程序。这些驱动程序可能提供更好的性能或功能，但可能不像推荐驱动程序那样经过广泛测试。

通过运行 `ubuntu-drivers devices` 命令，你可以获取有关系统硬件设备和适用驱动程序的信息。这对于了解系统硬件配置、选择适当的驱动程序以及解决硬件兼容性问题非常有用。

希望这些信息能帮助你理解和使用 `ubuntu-drivers devices` 命令。如有需要，你可以参考相关文档或手册以获取更多详细信息。


---

## gsettings

`gsettings` 是一个命令行工具，用于在 Ubuntu 中访问和修改 GNOME 桌面环境的设置。它允许你通过命令行方式读取和更改各种系统设置、应用程序设置以及桌面外观和行为等。

下面是一些 `gsettings` 命令的常见用法和解释：

1. `gsettings list-schemas`：列出可用的模式（schemas）。这将显示所有可用的模式名称，你可以使用这些模式名称来查询和修改相关设置。

2. `gsettings list-keys SCHEMA`：列出给定模式（SCHEMA）下的所有键（keys）。使用具体的模式名称替换 `SCHEMA` 部分来查看该模式下的所有可用键。

3. `gsettings get SCHEMA KEY`：获取给定模式（SCHEMA）下给定键（KEY）的值。这可用于查看当前设置的值。

4. `gsettings set SCHEMA KEY VALUE`：将给定模式（SCHEMA）下给定键（KEY）的值设置为指定的值（VALUE）。使用这个命令可以修改设置的值。

5. `gsettings reset SCHEMA KEY`：重置给定模式（SCHEMA）下给定键（KEY）的值为默认值。

6. `gsettings range SCHEMA KEY`：显示给定模式（SCHEMA）下给定键（KEY）的值的允许范围。

需要注意的是，`SCHEMA` 是模式的名称，而 `KEY` 是模式中的键的名称。你可以使用 `list-schemas` 和 `list-keys` 命令来获取可用的模式和键的列表。

举例来说，`org.gnome.desktop.background` 是一个常用的模式，用于控制桌面背景相关的设置。你可以使用类似以下的命令来修改桌面背景图片：
```
gsettings set org.gnome.desktop.background picture-uri 'file:///path/to/image.jpg'
```
这会将桌面背景设置为指定路径下的图像文件。

`gsettings` 提供了一种方便的方式来从命令行管理和调整 GNOME 桌面环境的各种设置。你可以查阅相关的文档和手册来获取更多关于 `gsettings` 命令的详细信息和示例用法。

## nautilus 

`nautilus` 是 Linux 系统中一个常用的文件管理器，它提供了图形化界面来浏览和管理文件和文件夹。下面是对 `nautilus` 命令的详细解释：

1. **启动 Nautilus：** 可以在终端中输入 `nautilus` 命令来启动 Nautilus 文件管理器。它会打开一个新的窗口显示当前用户的主目录。

2. **打开指定目录：** 可以使用 `nautilus` 命令并指定目录路径来打开特定的目录。例如，`nautilus /path/to/directory` 会打开指定路径的目录。

3. **图形化界面操作：** Nautilus 提供了一系列图形化界面操作，包括文件和文件夹的复制、剪切、粘贴、重命名、删除等。可以使用鼠标右键单击文件或文件夹，或使用菜单栏的选项来执行这些操作。

4. **查看和排序文件列表：** Nautilus 允许你以不同的方式查看和排序文件列表。你可以切换到图标视图、列表视图或压缩视图，并可以根据名称、大小、类型等进行排序。

5. **搜索文件：** Nautilus 提供了搜索功能，可以通过菜单栏中的搜索栏输入关键字来搜索文件和文件夹。

6. **自定义文件管理器：** Nautilus 允许你自定义文件管理器的外观和行为。你可以通过菜单栏中的“偏好设置”选项访问各种设置选项，如外观、行为、文件预览等。

请注意，`nautilus` 命令通常用于在桌面环境中打开 Nautilus 文件管理器。如果你使用的是不带桌面环境的服务器版本的 Linux，可能无法直接运行 `nautilus` 命令。在服务器上，你可能需要使用其他基于终端的文件管理工具。

---

## xxd

+ 简介：
  + xxd 是一个在 Linux 系统中用于十六进制和ASCII码转换的命令行工具。它可以将文件或输入的数据转换为十六进制和ASCII码的表示形式，或者将十六进制和ASCII码的数据还原为二进制格式

+ 语法
```bash
xxd [选项] [文件名]
```

+ 选项：
  + -b：以二进制格式显示数据。
  + -c <列数>：指定每行显示的列数。
  + -e：以大端字节序（big-endian）格式显示数据。
  + -g <字节数>：指定每个显示的数据块的字节数。
  + -l <长度>：指定要显示的字节数。
  + -s <偏移量>：指定要从输入中开始显示的偏移量。
  + -u：以大写字母表示十六进制数值。
  + -v：以完整的输出格式显示，不省略重复的行。

## hexdump

+ 简介：
  + hexdump 命令在 Linux 中用于以十六进制和ASCII码形式显示文件或输入的内容。它可以将二进制文件或数据转换为人可读的格式

+ 语法：
```bash
hexdump [选项] [文件名]
```

+ 选项：
  + -C：以十六进制和ASCII码形式显示内容，并在每行末尾显示对应的ASCII字符。
  + -b：以八进制格式显示内容。
  + -c：以字符形式显示内容。
  + -d：以十进制格式显示内容。
  + -e：指定自定义的格式字符串来显示内容。
  + -n <长度>：指定要显示的字节数。
  + -s <偏移量>：指定要从输入中开始显示的偏移量。
  + -v：以完整的输出格式显示，不省略重复的行。
  + -x：以十六进制格式显示内容。

## exiftool

+ 简介：
  + 在 Linux 上可以使用 exiftool 命令来查看图片的元数据。你可以在终端中运行以下命令来获取图片的详细元数据：
  + `exiftool image.jpg`

+ 注：
  + 安装依赖包libimage-exiftool-perl: `sudo apt install libimage-exiftool-perl`

## linux下，常用的查看动态库的符号链接工具

1. nm：nm 命令用于列出目标文件或共享库中的符号信息。可以使用 nm 命令来查看动态库中的符号链接。例如，要查看一个动态库文件（如libexample.so）中的符号链接，可以运行以下命令：
   ```
   nm -D libexample.so
   ```
   这将显示动态库中的所有符号及其链接信息。

2. objdump：objdump 命令用于显示目标文件或可执行文件的信息，包括符号表。可以使用 objdump 命令来查看动态库中的符号链接。例如，要查看一个动态库文件中的符号链接，可以运行以下命令：
   ```
   objdump -T libexample.so
   ```
   这将显示动态库中的符号链接表。

3. readelf：readelf 命令用于显示 ELF（Executable and Linkable Format）格式文件的信息，包括符号表。可以使用 readelf 命令来查看动态库中的符号链接。例如，要查看一个动态库文件中的符号链接，可以运行以下命令：
   ```
   readelf -s libexample.so
   ```
   这将显示动态库中的符号表，其中包含符号链接信息。


## Linux 常用命令全拼

+ 参考网站：`https://www.runoob.com/w3cnote/linux-command-full-fight.html`


## eog

<!-- + 简介：
  + 使用命令行查看图片

+ 示例：
  + `eog picturepath` -->

+ 简介：
  + eog 是 Linux 系统中的一个命令行工具，用于打开和显示图像文件。它是 Eye of GNOME (EOG) 图像查看器的命令行接口

+ 语法：
```bash 
eog [选项] [图像文件]
```

+ 选项：
  + -f 或 --fullscreen：以全屏模式打开图像。
  + -g 或 --geometry=宽度x高度：指定窗口的初始大小。
  + -n 或 --new-instance：在新的 EOG 实例中打开图像。
  + -w 或 --disable-gallery：禁用图库模式

+ 示例：
```bash 
eog image.jpg
```

+ 注：
  + 当你在终端中运行 eog 命令并指定一个图像文件作为参数时，它会打开 Eye of GNOME (EOG) 图像查看器，并在窗口中显示指定的图像。你可以使用鼠标滚轮来缩放图像，使用工具栏进行放大、缩小、旋转等操作。还可以通过菜单栏中的选项进行图像的保存、打印和设置
  + eog 命令提供了一个快速和方便的方式来查看图像文件，尤其适用于图像的预览和简单的编辑操作。它支持多种常见的图像格式，如 JPEG、PNG、GIF 等
  + 需要注意的是，eog 命令通常用于在图形化环境下打开图像文件。如果你在没有图形界面的终端环境中运行 eog 命令，可能会出现错误或无法正常工作


## 查看linux服务器开机自启动服务

+ 命令：
  + `systemctl list-unit-files`

+ 参数：
  + 其中STATE显示为enable字样的服务，即可开机自启动的服务 

+ 查处的内容过多，可通过grep 命令进行筛选
  + `systemctl list-unit-files | grep firewalld`

## 开启或关闭开机自启动

+ 关闭开机自启动：
  + `systemctl disable  服务name`

+ 开启开机自启动：
  + `systemctl enable  服务name`



## getconf

+ 简介：
  - 查询保存系统配置的变量
+ 参数
  - `-a` : 显示所有当前系统的配置变量和变量的值
  - `-v` : 
  - `system_var` : 查询指定配置变量的值
  - `path_var` : 参数是一个通过pathconf命令定义的系统配置变量

## 清空文件内容

+ 通过重定向到 Null 来清空文件内容
  + `> access.log`

+ 使用 ‘true’ 命令重定向来清空文件
  + 下面我们将使用 : 符号，它是 shell 的一个内置命令，等同于 true 命令，它可被用来作为一个 no-op（即不进行任何操作）
  + `: > access.log`
  + `true > access.log`

+ 使用 cat/cp/dd 实用工具及 /dev/null 设备来清空文件
  + 在 Linux 中， null 设备基本上被用来丢弃某个进程不再需要的输出流，或者作为某个输入流的空白文件，这些通常可以利用重定向机制来达到。
  + 所以 /dev/null 设备文件是一个特殊的文件，它将清空送到它这里来的所有输入，而它的输出则可被视为一个空文件。
  + 另外，你可以通过使用 cat 命令 显示 /dev/null 的内容然后重定向输出到某个文件，以此来达到清空该文件的目的。
  + `cat /dev/null > access.log`
+ 下面，我们将使用 cp 命令 复制 /dev/null 的内容到某个文件来达到清空该文件的目的，具体如下所示：
  + `cp /dev/null access.log`
+ 而下面的命令中， if 代表输入文件，of 代表输出文件。
  + `dd if=/dev/null of=access.log`

+ 使用 echo 命令清空文件
  + `echo "" > access.log`
  + `echo > access.log`
+ 注意：你应该记住空字符串并不等同于 null 。字符串表明它是一个具体的事物，只不过它的内容可能是空的，但 null 则意味着某个事物并不存在
+ 基于这个原因，当你将 echo 命令 的输出作为输入重定向到文件后，使用 cat 命令 来查看该文件的内容时，你将看到一个空白行（即一个空字符串）
+ 要将 null 做为输出输入到文件中，你应该使用 -n 选项，这个选项将告诉 echo 不再像上面的那个命令那样输出结尾的那个新行。

+ 使用 truncate 命令来清空文件内容
  + truncate 可被用来将一个文件缩小或者扩展到某个给定的大小
  + 你可以利用它和 -s 参数来特别指定文件的大小。要清空文件的内容，则在下面的命令中将文件的大小设定为 0:
    + `truncate -s 0 access.log`

## fstab

`fstab`（文件系统表）是一个Linux系统配置文件，用于定义系统在启动时挂载文件系统的方式和规则。它通常位于`/etc/fstab`路径下，由系统管理员进行编辑和管理。

`fstab`文件中的每一行表示一个要挂载的文件系统，每个字段之间用空格或制表符分隔。以下是`fstab`文件的常用字段和说明：

```plaintext
<文件系统>  <挂载点>  <文件系统类型>  <挂载选项>  <dump>  <pass>
```

- `<文件系统>`：要挂载的设备或网络位置。可以是设备名称（如`/dev/sda1`）、UUID（Universally Unique Identifier）、标签（Label）或网络位置（如`//server/share`）。
- `<挂载点>`：设备将被挂载到的目录路径。
- `<文件系统类型>`：设备的文件系统类型，如`ext4`、`ntfs`、`nfs`等。
- `<挂载选项>`：指定挂载设备时的选项，如`ro`（只读）、`rw`（读写）、`noauto`（不自动挂载）、`user`（允许普通用户挂载）等。
- `<dump>`：备份标志。如果设置为`0`，表示不会被备份；如果设置为`1`，表示会被备份。
- `<pass>`：检查顺序。用于`fsck`命令检查文件系统的顺序。如果设置为`0`，表示不会被检查。

示例`fstab`文件条目：

```plaintext
/dev/sda1   /mnt/data   ext4   defaults   0   2
//server/share   /mnt/nfs   nfs   defaults   0   0
```

上述示例中，第一行表示将`/dev/sda1`设备挂载到`/mnt/data`目录，使用`ext4`文件系统和默认挂载选项。`dump`设置为`0`，`pass`设置为`2`。第二行表示将网络位置`//server/share`挂载到`/mnt/nfs`目录，使用NFS文件系统和默认挂载选项，不进行备份和检查。

要编辑`fstab`文件，请使用具有管理员权限的文本编辑器，例如`vi`或`nano`。请谨慎编辑`fstab`文件，确保提供正确的设备和挂载选项，以免影响系统的正常启动和文件系统的挂载。

---

## mffs.ext4

`mkfs.ext4`是一个Linux命令，用于创建ext4文件系统（第四个扩展文件系统）在指定的设备上。

以下是`mkfs.ext4`命令的常用选项和用法：

```bash
mkfs.ext4 [options] <device>
```

常用选项：

- `-b block-size`：指定文件系统的块大小，默认为4096字节。
- `-L volume-label`：为文件系统设置卷标。
- `-m reserved-blocks-percentage`：指定保留块的百分比，用于系统管理员。
- `-T usage-type`：设置文件系统的用途类型，如`news`, `backup`, `web`, 等。
- `-O feature`：启用指定的文件系统特性，如`^has_journal`表示不使用日志功能。
- `-E extended-option`：设置扩展选项，如`stride`, `stripe-width`, `nodiscard`, 等。

示例用法：

1. 创建ext4文件系统：

```bash
mkfs.ext4 /dev/sdb1
```

上述命令将在设备`/dev/sdb1`上创建一个ext4文件系统，默认使用4096字节的块大小。

2. 创建具有指定块大小的ext4文件系统：

```bash
mkfs.ext4 -b 8192 /dev/sdb1
```

上述命令将在设备`/dev/sdb1`上创建一个ext4文件系统，并指定块大小为8192字节。

3. 为ext4文件系统设置卷标：

```bash
mkfs.ext4 -L MyVolume /dev/sdb1
```

上述命令将在设备`/dev/sdb1`上创建一个ext4文件系统，并设置卷标为"MyVolume"。

4. 启用特定的文件系统特性：

```bash
mkfs.ext4 -O ^has_journal /dev/sdb1
```

上述命令将在设备`/dev/sdb1`上创建一个ext4文件系统，并禁用日志功能。

`mkfs.ext4`命令用于创建ext4文件系统之前，请确保已经正确地指定了要创建文件系统的设备。创建文件系统将格式化该设备并擦除其上的所有数据，请谨慎操作。

---

## Linux下视频剪辑，录制工具

+ kazam 
  - 录制屏幕：`apt-get install -y kazam`
  - 缺点：保存的视频，在vlc打开看不到视频，传到手机剪影也不能剪辑

+ openshot
  - `apt-get install -y openshot-qt`
  - 和pr相似

+ **simplescreenrecorder**
  - 录制屏幕：`apt-get install -y simplescreenrecorder`
  - 优点：相比于kazam，其录制的视频，容量小，vlc支持播放

---

## 屏保命令和锁屏命令

+ `gnome-screensaver-command -a`  --  显示屏保但是不锁定，移动鼠标或敲击键盘后自动消失

+ `gnome-screensaver-command -l`  --  显示屏保并锁定，移动鼠标或敲击键盘弹出密码框

+ `sudo loginctl list-sessions`   -- 列出当前所有的会话（默认命令）

+ `sudo loginctl lock-session [ID]`   -- 锁定指定会话（如果会话支持屏幕锁）或者当前调用者的会话

+ `sudo loginctl unlock-session [ID]` -- 解锁指定会话（如果会话支持屏幕锁）或者当前调用者的会话

+ `sudo loginctl lock-sessions`  --  锁定全部会话

+ `sudo loginctl unlock-sessions` -- 解锁全部会话

+ ubuntu18 锁屏快捷键  --  `Super + L`

---

## fdisk

`fdisk`是一个Linux命令行工具，用于对磁盘分区进行管理和操作。它可以创建、删除、调整磁盘分区以及显示磁盘分区信息。

以下是`fdisk`命令的常用选项和用法：

```bash
fdisk [options] <device>
```

常用选项：

- `-l`：列出指定设备或所有设备的分区表信息。
- `-s`：显示指定设备或所有设备的分区大小。
- `-u`：以扇区而不是柱面为单位显示分区信息。
- `-c`：与`-l`选项一起使用时，使用紧凑的格式显示分区表信息。
- `-p`：与`-l`选项一起使用时，使用可打印的格式显示分区表信息。
- `-n`：创建一个新的分区。
- `-d`：删除一个分区。
- `-t`：更改分区的类型。

示例用法：

1. 列出所有设备的分区表信息：

```bash
fdisk -l
```

上述命令将列出所有设备的分区表信息，包括设备名称、分区大小、分区类型等。

2. 列出指定设备的分区表信息：

```bash
fdisk -l /dev/sda
```

上述命令将列出设备`/dev/sda`的分区表信息。

3. 创建新的分区：

```bash
fdisk /dev/sdb
```

上述命令将打开设备`/dev/sdb`的分区表，并引导您通过一系列的交互式步骤来创建新的分区。

4. 删除分区：

```bash
fdisk /dev/sdc
Command (m for help): d
Partition number (1-4): 1
```

上述命令将打开设备`/dev/sdc`的分区表，并提示您输入要删除的分区号。

5. 更改分区类型：

```bash
fdisk /dev/sdd
Command (m for help): t
Partition number (1-4): 1
Hex code (type L to list codes): 83
```

上述命令将打开设备`/dev/sdd`的分区表，并提示您输入要更改的分区号和新的分区类型。

`fdisk`命令涉及对磁盘分区进行操作，因此需要以root权限运行。请谨慎操作，以免对系统造成损害。

---

## iostat

`iostat`是一个Linux命令，用于报告和存档系统磁盘IO活动的统计信息。它可以提供有关磁盘读写速度、IO等待时间、IO请求队列长度以及CPU利用率的信息。

以下是`iostat`命令的常用选项和用法：

```bash
iostat [options] [interval] [count]
```

常用选项：

- `-c`：仅显示CPU利用率统计。
- `-d`：仅显示磁盘IO统计。
- `-k`：以KB为单位显示统计信息。
- `-m`：以MB为单位显示统计信息。
- `-x`：显示详细的磁盘IO统计，包括每个设备的读写速度、IO等待时间、IO请求队列长度等。
- `-t`：在每一行的输出中显示时间戳。
- `-y`：在每一行的输出中显示日期和时间。
- `-h`：显示帮助信息。

示例用法：

1. 显示磁盘IO统计信息：

```bash
iostat
```

上述命令将显示所有磁盘设备的读写速度、IO等待时间和IO请求队列长度。

2. 以1秒的间隔连续显示磁盘IO统计信息，共显示5次：

```bash
iostat 1 5
```

上述命令将每秒显示一次磁盘IO统计信息，连续显示5次。

3. 仅显示CPU利用率统计信息：

```bash
iostat -c
```

上述命令将仅显示CPU的利用率统计信息。

4. 显示详细的磁盘IO统计信息：

```bash
iostat -x
```

上述命令将显示详细的磁盘IO统计信息，包括每个设备的读写速度、IO等待时间、IO请求队列长度等。

`iostat`命令还支持其他选项和用法，您可以通过`man iostat`命令查看完整的帮助文档和更多示例。

---

## sysstat

`sysstat`是一个性能监控工具集，它提供了一系列的命令行工具，用于收集和分析系统的性能数据。这些工具可以帮助您监视系统的资源利用率、性能瓶颈和运行状况。

`sysstat`包括以下常用命令：

1. `sar`：用于收集、报告和存档系统活动信息，包括CPU利用率、内存使用、磁盘IO、网络流量等。示例用法：`sar -u`显示CPU利用率，`sar -r`显示内存使用情况，`sar -d`显示磁盘IO统计。

2. `iostat`：用于报告和存档系统磁盘IO活动的统计信息，包括每个磁盘的读写速度、IO等待时间、IO请求队列长度等。示例用法：`iostat -x`显示详细的磁盘IO统计。

3. `mpstat`：用于报告和存档每个CPU的利用率和其他统计信息，包括用户时间、系统时间、空闲时间等。示例用法：`mpstat -P ALL`显示每个CPU的利用率。

4. `pidstat`：用于报告和存档进程的CPU利用率、内存使用和IO统计。示例用法：`pidstat -p <pid>`显示特定进程的统计信息。

5. `ifstat`：用于报告和存档网络接口的流量统计，包括接收和发送的数据量。示例用法：`ifstat -a`显示所有网络接口的流量统计。

这些命令都是通过收集系统性能数据并以可读的格式进行报告。您可以根据具体需求选择适合的命令，并结合不同的选项来获取所需的性能信息。

`sysstat`工具集在大多数Linux发行版中都可用，但需要先安装。您可以使用包管理器（如apt、yum等）来安装`sysstat`软件包。

---

## dmesg

`dmesg`是一个Linux命令，用于显示内核环缓冲区的内容。它可以提供有关系统启动期间发生的事件、硬件故障、驱动程序加载和其他内核消息的详细信息。

以下是`dmesg`命令的常用选项和用法：

```bash
dmesg [options]
```

常用选项：

- `-c, --clear`：清除内核环缓冲区的内容。
- `-s, --buffer-size=size`：设置内核环缓冲区的大小。
- `-n, --console-level=level`：设置在控制台上显示的内核消息的级别。
- `-r, --raw`：以原始格式显示内核消息，不进行解析。
- `-T, --ctime`：以人类可读的日期和时间格式显示内核消息的时间戳。
- `--color[=when]`：设置输出中的颜色。
- `-h, --help`：显示帮助信息。

示例用法：

1. 显示内核环缓冲区的内容：

```bash
dmesg
```

上述命令将显示内核环缓冲区中的所有消息。

2. 清除内核环缓冲区的内容：

```bash
dmesg -c
```

上述命令将清除内核环缓冲区的内容。

3. 以人类可读的日期和时间格式显示内核消息：

```bash
dmesg -T
```

上述命令将以人类可读的日期和时间格式显示内核消息的时间戳。

4. 设置内核消息的显示级别：

```bash
dmesg -n 4
```

上述命令将仅显示级别为4（警告级别）及以上的内核消息。

`dmesg`命令还支持其他选项和用法，您可以通过`man dmesg`命令查看完整的帮助文档和更多示例。

---

## date

`date`是Linux系统中用于显示和设置系统日期和时间的命令。它还可以格式化日期和时间以满足特定的需求。

以下是`date`命令的常用选项和用法：

```bash
date [options] [+format]
```

常用选项：

- `-d, --date=STRING`：使用指定的日期和时间字符串进行操作，而不是当前日期和时间。
- `-u, --utc, --universal`：使用协调世界时（UTC）进行操作，而不是本地时间。
- `--rfc-3339=TIMESPEC`：使用RFC 3339格式显示日期和时间。
- `--iso-8601[=TIMESPEC]`：使用ISO 8601格式显示日期和时间。
- `-R, --rfc-2822`：使用RFC 2822格式显示日期和时间。
- `--help`：显示帮助信息。

格式化选项（常用的格式化选项）：

- `%Y`：四位数的年份（例如：2023）。
- `%y`：两位数的年份（例如：23）。
- `%m`：两位数的月份（例如：06）。
- `%d`：两位数的日期（例如：09）。
- `%H`：两位数的小时（24小时制）（例如：15）。
- `%M`：两位数的分钟（例如：30）。
- `%S`：两位数的秒钟（例如：45）。
- `%A`：完整的星期几名称（例如：Sunday）。
- `%a`：缩写的星期几名称（例如：Sun）。
- `%B`：完整的月份名称（例如：June）。
- `%b`：缩写的月份名称（例如：Jun）。
- `%Z`：时区名称（例如：PST）。
- `%z`：时区偏移量（例如：-0800）。

示例用法：

1. 显示当前日期和时间：

```bash
date
```

2. 显示当前日期（年、月、日）：

```bash
date +%Y-%m-%d
```

3. 显示当前时间（小时、分钟、秒）：

```bash
date +%H:%M:%S
```

4. 根据指定格式显示日期和时间：

```bash
date +"%Y-%m-%d %H:%M:%S"
```

5. 显示当前时间的UNIX时间戳：

```bash
date +%s
```

`date`命令还支持其他选项和格式化标记，可以根据具体的需求进行调整。您可以通过`man date`命令查看`date`命令的完整帮助文档和更多用法示例。

---

## pgrep 

`pgrep`是一个在Linux系统中用于根据进程名或其他条件查找进程ID（PID）的命令。它可以根据给定的进程名、用户、进程组、终端等条件进行匹配，然后返回符合条件的进程ID。

以下是`pgrep`命令的常用选项和用法：

```bash
pgrep [options] pattern
```

常用选项：

- `-u, --euid euid`：根据有效用户ID查找进程。
- `-U, --uid uid`：根据实际用户ID查找进程。
- `-g, --gid gid`：根据进程组ID查找进程。
- `-t, --terminal terminal`：根据终端设备号查找进程。
- `-x, --exact`：精确匹配进程名，不进行模糊匹配。
- `-f, --full`：匹配进程的完整命令行。
- `-a, --list-full`：显示完整的进程信息，包括进程名和命令行。
- `-l, --list-name`：显示进程名和PID，类似于`ps`命令的输出。

示例用法：

1. 根据进程名查找进程ID：

```bash
pgrep nginx
```

上述命令将返回所有进程名包含"nginx"的进程ID。

2. 根据用户ID查找进程ID：

```bash
pgrep -u 1000
```

上述命令将返回用户ID为1000的所有进程ID。

3. 显示完整的进程信息：

```bash
pgrep -a nginx
```

上述命令将显示所有进程名包含"nginx"的进程信息，包括进程名和命令行。

`pgrep`命令还支持其他选项和用法，可以通过`man pgrep`命令查看详细的帮助文档。

## ps

+ ps命令用于报告当前系统的进程状态，可以搭配kill指令随时中断，删除不必要的程序。
+ ps明星是最基本的同时也是非常强大的进程查看命令，使用该命令可以确定有哪些进程正在运行和运行的状态，进程是否结束，进程有没有僵死，哪些进程占用了过多的资源等等
+ 参数
  + `a` : 显示当前终端下的所有进程信息，包括其他用户的进程
  + `u` : 使用以用户为主的格式输出进程信息
  + `x` : 显示当前用户在所有终端下的进程
+ 字段解释
  + `USER` : 启动该进程的用户账号名称
  + `PID`  : 该进程的ID号,在当前系统中是唯一的
  + `%CPU` : CPU占用的百分比
  + `%MEM` : 内存占用的百分比
  + `VSZ`  : 占用虚拟内存(swap空间)的大小
  + `RSS`  : 占用常驻内存(物理内存)的大小
  + `TTY`  : 该进程在哪个终端上运行. `"?"`表示未知或不需要终端
  + `STAT` : 显示了进程当前的状态
    + `S , interruptible sleep (waiting for an event to complete` : 休眠
    + `R , running or runnable (on run queue)` : 运行
    + `Z , defunct("zombie") process, terminated but not reaped by its parent` : 僵死, 对于僵死状态的进程应该手动终止
    + `< , high-priority (not nice to other users)` : 高优先级
    + `N , low-priority (nice to other users)` : 低优先级
    + `s , is a session leader` : 父进程
    + `+ , is in the foreground process group` : 前台进程
    + `l , is multi-threaded(using CLONE_THREAD, like NPTL pthreads do)`:多线程
  + `START`: 启动该进程的时间
  + `TIME` : 该进程占用CPU的时间
  + `COMMAND`: 启动该进程的命令的名称
+ 参数
  + `e` : 显示系统内的所有进程信息
  + `l` : 使用长(long)格式显示进程信息
  + `f` : 使用完整的(full)格式显示进程信息

## top

+ 简介：
  + top, 以全屏交互式的界面显示进程排名,及时跟踪包括CPU,内存等系统资源占用情况,默认情况下每三秒刷新一次,其作用基本类似于Windows系统中的任务管理器
  + top命令，是Linux下常用的性能分析工具，能够实时显示系统中各个进程的资源占用状况，常用于服务端性能分析。
  + top命令，可以实时动态地查看系统的整体运行情况，是一个综合了多方信息监测系统性能和运行信息的实用工具。通过top命令所提供的互动式界面，用热键可以管理。
  + 在top命令中按f按可以查看显示的列信息，按对应字母来开启/关闭列，大写字母表示开启，小写字母表示关闭。带*号的是默认列。

+ 语法
  + top(选项)

+ 选项
  + -b：以批处理模式操作；
  + -c：显示完整的治命令；
  + -d：屏幕刷新间隔时间；
  + -I：忽略失效过程；
  + -s：保密模式；
  + -S：累积模式；
  + -i<时间>：设置间隔时间；
  + -u<用户名>：指定用户名；
  + -p<进程号>：指定进程；
  + -n<次数>：循环显示的次数。

+ top交互命令：在top命令执行过程中可以使用的一些交互命令。这些命令都是单字母的，如果在命令行中使用了-s选项， 其中一些命令可能会被屏蔽。
  + h：显示帮助画面，给出一些简短的命令总结说明；
  + k：终止一个进程；
  + i：忽略闲置和僵死进程，这是一个开关式命令；
  + q：退出程序；
  + r：重新安排一个进程的优先级别；
  + S：切换到累计模式；
  + s：改变两次刷新之间的延迟时间（单位为s），如果有小数，就换算成ms。输入0值则系统将不断刷新，默认值是5s；
  + f或者F：从当前显示中添加或者删除项目；
  + o或者O：改变显示项目的顺序；
  + l：切换显示平均负载和启动时间信息；
  + m：切换显示内存信息；
  + t：切换显示进程和CPU状态信息；
  + c：切换显示命令名称和完整命令行；
  + M：根据驻留内存大小进行排序；
  + P：根据CPU使用百分比大小进行排序；
  + T：根据时间/累计时间进行排序；
  + w：将当前设置写入~/.toprc文件中。

+ 实例
  ```
    top - 09:44:56 up 16 days, 21:23,  1 user,  load average: 9.59, 4.75, 1.92
    Tasks: 145 total,   2 running, 143 sleeping,   0 stopped,   0 zombie
    Cpu(s): 99.8%us,  0.1%sy,  0.0%ni,  0.2%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
    Mem:   4147888k total,  2493092k used,  1654796k free,   158188k buffers
    Swap:  5144568k total,       56k used,  5144512k free,  2013180k cache
  ``` 
+ 解释
  + top - 09:44:56[当前系统时间],
  + 16 days[系统已经运行了16天],
  + 1 user[个用户当前登录],
  + load average: 9.59, 4.75, 1.92[系统负载，即任务队列的平均长度]
  + Tasks: 145 total[总进程数],
  + 2 running[正在运行的进程数],
  + 143 sleeping[睡眠的进程数],
  + 0 stopped[停止的进程数],
  + 0 zombie[冻结进程数],
  + Cpu(s): 99.8%us[用户空间占用CPU百分比],
  + 0.1%sy[内核空间占用CPU百分比],
  + 0.0%ni[用户进程空间内改变过优先级的进程占用CPU百分比],
  + 0.2%id[空闲CPU百分比], 0.0%wa[等待输入输出的CPU时间百分比],
  + 0.0%hi[],
  + 0.0%st[],
  + Mem: 4147888k total[物理内存总量],
  + 2493092k used[使用的物理内存总量],
  + 1654796k free[空闲内存总量],
  + 158188k buffers[用作内核缓存的内存量]
  + Swap:  5144568k total[交换区总量],
  + 56k used[使用的交换区总量],
  + 5144512k free[空闲交换区总量],
  + 2013180k cached[缓冲的交换区总量],

+ 字段解释:
  + `Tasks` : 系统任务信息
  + `total` : 总进程数
  + `running` : 正在运行的进程数
  + `sleeping` : 休眠的进程数
  + `stopped`  : 终止的进程数
  + `zombie`  : 僵死无响应的进程数

+ 常用命令
  + `top ` 回车之后再输入c，会显示进程详细信息
  + `top -p pid`， 查看指定进程ID的动态资源

+ 在 top 命令中，你可以使用以下快捷键来修改显示的单位：
  - 按下 "e" 键：切换内存显示单位，可以在字节（Bytes）、千字节（KBytes）、兆字节（MBytes）和吉字节（GBytes）之间进行切换。
  - 按下 "E" 键：切换内存和交换空间显示单位，与 "e" 键类似，但同时会修改交换空间的显示单位。
  - 按下 "k" 键：切换 CPU 使用率的显示单位，可以在百分比（%）、千分比（m%）和百万分比（M%）之间进行切换。
  - 按下 "K" 键：切换 CPU 时间的显示单位，可以在秒（s）、毫秒（ms）和微秒（us）之间进行切换。
+ 在 top 命令中按下相应的键后，单位会相应地进行切换，并且在顶部的标题行中会显示当前的单位。你可以根据需要选择合适的单位来查看系统资源的使用情况。

## pstree

+ pstree,以树状图的方式展现进程之间的派生关系,显示效果比较直观
+ 参数
  + `a` : 显示每个程序的完整指令,包含路径,参数或者是常驻服务的标示
  + `c` : 不使用精简表示法
  + `G` : 使用VT100终端机的列绘图字符
  + `n` : 用程序识别码排序,预设是以程序名称来排序
  + `p` : 显示程序识别码
  + `u` : 显示用户名称

## ss --  查看端口状态信息

+ 简介：
  + ss 是一个 Linux 下用于查看套接字统计信息的命令。它提供了比 netstat 更全面和高效的功能

+ 语法
```bash
ss [options]
```

+ 选项：
  + -t: 显示 TCP 套接字信息。
  + -u: 显示 UDP 套接字信息。
  + -w: 显示 RAW 套接字信息。
  + -a: 显示所有套接字信息，包括监听和非监听状态。
  + -s: 显示套接字统计信息，包括每个协议的统计数据。
  + -p: 显示与套接字关联的进程信息。
  + -n: 不进行服务名称解析，显示 IP 地址和端口号。
  + -r: 显示路由表信息。
  + -l: 仅显示监听状态的套接字。
  + -o: 显示计时器信息

+ 详解：
  + 使用 ss 命令时，可以结合不同的选项来获取特定类型的套接字信息。例如，ss -t 显示所有 TCP 套接字信息，ss -u 显示所有 UDP 套接字信息，ss -l 显示所有监听状态的套接字信息
  + ss 命令的输出包括以下列
    + State: 套接字的状态，如 ESTABLISHED（已建立）、LISTEN（监听）等。
    + Recv-Q: 接收队列的字节数。
    + Send-Q: 发送队列的字节数。
    + Local Address: 本地 IP 地址和端口号。
    + Peer Address: 对端 IP 地址和端口号。
    + Process（-p 选项时显示）: 与套接字关联的进程信息

+ 注：
  + 通过 ss 命令，可以查看网络连接状态、套接字使用情况、进程与套接字的关联信息等。它在排查网络问题、监视网络连接和调试网络应用程序时非常有用
  + 安装 iproute2 软件包：ss 命令是 iproute2 软件包的一部分，因此需要安装该软件包

<!-- + 参数：
  + `-l, --listening`  --  仅显示被监听的套接字
  + `-s, --summary`  -- 打印概括的状态信息
  + `-p, --processes`  --  显示使用套接字的进程
  + `-i, --info`     --  显示TCP内部详细的信息
  + `-t, --tcp`      --  显示TCP套接字
  + `-n, --numeric`  --  显示数值，不显示服务名字 -->

## 杀死指定进程

+ `kill -9 process_pid`