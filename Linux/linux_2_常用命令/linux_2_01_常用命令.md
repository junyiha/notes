## stty 查询中断按键

+ 不同的终端类型、Shell版本其中断的按键是不同的，甚至还可以自定义，这可通过stty命令查询：`sitty -a`
+ 注意：`^`是Ctrl的缩写

## 终端初始化脚本

+ 参考：
  + `https://www.cnblogs.com/yoyo-sincerely/p/5931245.html`

## 显示路径问题

+ `\w`  --  当前工作目录，例如`/home/user`
+ `\W`  --  当前工作目录的基名(basename)，例如`user`

+ 解决问题：终端显示路径太长，不易于阅读
+ 解决方法：将`.bashrc`中的`\w`更换为`\W`

## MD5校验

+ Windows下生成md5校验码: `certutil -hashfile filename MD5`
+ Linux下生成md5校验码:   `md5sum filename`


## 文件名通配符

+ `×`：与0个或多个任意的字符相匹配
+ `？`：只与单个任意的字符匹配，可以使用多个问号
+ `[]`：与`？`相似，只与一个字符匹配。区别在于：问号与任意一个字符匹配，而方括号只与方括号中列出的字符之一匹配。短横线（`-`）代表一个范围内的字符。注：只能是升序

## sudo  

+ sudo, superuser do

在Linux中，`sudo`是一种命令行工具，用于以超级用户（也称为root用户）的权限执行其他命令。它允许普通用户在需要执行特权操作时临时获得root权限，从而执行需要管理员权限的任务，而无需切换到root用户。

以下是`sudo`命令的一般语法：

```
sudo [options] command [arguments]
```

其中，`options`是可选的一些选项，`command`是要以root权限执行的命令，`arguments`是传递给命令的参数。

以下是一些常见的`sudo`命令选项和用法：

1. 以root权限执行命令：
   ```
   sudo command
   ```

   此命令将以root权限执行`command`命令。

2. 切换到root用户：
   ```
   sudo -i
   ```

   此命令将打开一个新的shell会话，并切换到root用户身份。

3. 以其他用户身份执行命令：
   ```
   sudo -u username command
   ```

   此命令将以指定用户（`username`）的权限执行`command`命令。

4. 查看sudo命令的使用情况：
   ```
   sudo -h
   ```

   此命令将显示`sudo`命令的帮助信息，包括选项和用法。

5. 列出当前用户的sudo权限：
   ```
   sudo -l
   ```

   此命令将列出当前用户可以使用`sudo`执行的命令列表。

通过使用`sudo`命令，系统管理员可以授予特定的权限给普通用户，使其能够执行有限的特权操作，同时避免了在整个会话中使用root权限的风险。这提供了更好的系统安全性和管理员对系统的更细粒度控制。

需要注意的是，只有在`/etc/sudoers`文件中明确配置了用户的sudo权限，用户才能使用`sudo`命令。只有具备sudo权限的用户才能成功执行以root权限执行的命令。

## supervisor  

+ supervisor, 是一个客户端/服务器系统,它允许用户监视和控制类UNIX操作系统上的许多进程,是linux下一个便利的启动和监控服务的命令
+ Supervisor, 是用Python开发的一个client/server服务,是Linux/Unix系统下的一个进程管理工具,不支持Windows系统.它可以很方便的监听,启动,停止,重启一个或多个进程
+ 用Supervisor管理的进程,当一个进程意外被杀死,supervisor监听到进程死后,会自动将它重新拉起,很方便的做到进程自动恢复的功能,不再需要自己写shell脚本来控制.
+ 因为Supervisor是Python开发的,安装前先检查一下系统是否安装了Python2.4以上的版本
+ supervisor包括两个命令:supervisord, supervisorctl,分别是后台的守护进程以及命令行管理命令.
+ supervisor安装完成后会生成是三个执行程序:`supervisortd`, `supervisorctl`, `echo_supervisord_conf`
  + `supervisortd`, 用于管理supervisor本身服务
  + `supervisorctl`, 用于管理需要委托给supervisor工具的服务
  + `echo_supervisord_conf`, 用于生成supervisor的配置文件
  + supervisor的守护进程服务(用于接受进程管理命令),客户端(用于和守护进程通信,发送管理进程的指令)
+ 两个命令共用一个配置文件,默认是:`/etc/supervisor/supervisor.conf`,而`supervisor.conf`通过include来引入其他配置文件,一般放在`/etc/supervisor/conf.d`目录下

## redshift  

在Linux中，`redshift`是一种用于调整屏幕颜色温度的命令行工具。它可以通过减少屏幕的蓝光成分来减轻视觉疲劳，并在晚上或低光环境下提供更舒适的视觉体验。

下面是`redshift`命令的一些常见选项和用法：

1. 基本用法：
   - 启动`redshift`：`redshift`
   - 停止`redshift`：`redshift -x`

2. 调整颜色温度：
   - 使用`-t`选项指定颜色温度（单位为开尔文）：`redshift -t 4000`
   - 使用`-b`选项指定颜色温度并降低亮度：`redshift -b 0.8 -t 4000`

3. 调整定位信息：
   - 使用`-l`选项指定纬度和经度以计算日出和日落时间：`redshift -l LAT:LON`
   - 例如：`redshift -l 37.8:-122.4`（设定位置为旧金山）

4. 调整亮度：
   - 使用`-m`选项启用亮度调整模式：`redshift -m METHOD`
   - 方法包括`randr`（默认值）和`vidmode`

5. 调整亮度变化速度：
   - 使用`-r`选项指定亮度变化速度（单位为小时）：`redshift -r SPEED`

6. 自定义配置文件：
   - 使用`-c`选项指定自定义配置文件的路径：`redshift -c /path/to/config`

7. 显示调试信息：
   - 使用`-v`选项显示详细的调试信息：`redshift -v`

以上是一些常见的`redshift`命令选项和用法示例。请注意，`redshift`命令需要正确配置和运行，以便根据位置和时间自动调整屏幕颜色温度。您可以根据自己的需求和喜好来调整命令的参数，以达到最佳的视觉效果。

## curl  

+ 在Linux中curl是一个利用URL规则在命令行下工作的文件传输工具。支持文件的上传和下载，是综合传输工具，但是按照传统，习惯称curl为下载工具
+ 参数
  + `-f / --fail` : 连接失败时不显示http错误
  + `-s / --silent` : 静音模式，不输出任何东西
  + `-S / --show-error` : 当与`-s`一起使用时，如果`curl`失败，`curl`将显示一条错误消息
  + `-L / --location` : （HTTP/HTTPS）跟踪重定向。如果服务器报告请求页面已移动到另一个位置，此选项将使curl在新位置上重做请求

在Linux中，`curl`命令是一个功能强大的网络工具，用于与服务器进行数据交互。它支持多种协议，包括HTTP、HTTPS、FTP、SMTP等，并可以执行各种操作，如下载文件、发送请求、上传文件等。

以下是`curl`命令的一般语法：

```
curl [options] [URL]
```

其中，`options`是可选的一些选项，用于配置`curl`的行为，`URL`是要访问的目标地址。

以下是一些常见的`curl`命令选项和用法：

1. 发送HTTP GET请求并输出响应内容：
   ```
   curl http://example.com
   ```

   此命令将向`http://example.com`发送HTTP GET请求，并将响应内容输出到终端。

2. 下载文件到本地：
   ```
   curl -O http://example.com/file.txt
   ```

   此命令将从`http://example.com/file.txt`下载文件，并保存到当前目录下的`file.txt`文件。

3. 发送POST请求并传递参数：
   ```
   curl -d "param1=value1&param2=value2" -X POST http://example.com/api
   ```

   此命令将向`http://example.com/api`发送HTTP POST请求，并将参数`param1=value1&param2=value2`作为请求体发送。

`curl`命令还支持其他许多选项，如设置请求头、设置超时时间、处理重定向等。

使用`curl`命令可以方便地进行各种网络操作，如获取API数据、下载文件、测试网络连接等。它是一种非常强大和灵活的工具，广泛应用于开发、调试和自动化脚本等场景。

---

## curl --data-binary

`curl` 是一个命令行工具，用于进行 HTTP 请求。`--data-binary` 选项用于在 HTTP POST 请求中发送二进制数据作为请求体。以下是对该选项的详细解释：

当你在 `curl` 中使用 `--data-binary` 选项时，你需要提供要发送的数据作为请求体。这些数据可以是二进制数据，即可以包含非文本字符或不适合解释为纯文本的格式。例如，它可以是图像文件、视频文件或任何其他类型的二进制数据。

`--data-binary` 选项期望你在命令行上直接指定数据，通常需要使用引号将其括起来，以保留任何特殊字符或格式。以下是一个示例：

```shell
curl --data-binary "@文件名" URL
```

在上面的示例中，`@文件名` 表示包含要发送的二进制数据的文件路径。`@` 符号告诉 `curl` 读取文件的内容并将其用作请求体。

另外，你也可以直接在命令行上内联指定二进制数据，而无需使用文件：

```shell
curl --data-binary "二进制数据" URL
```

在上面的示例中，`"二进制数据"` 表示你要发送的实际二进制数据。如果需要，确保正确编码数据，特别是如果数据包含可能被命令行解释器解释为特殊字符的字符。

当 `curl` 使用 `--data-binary` 选项发送 HTTP 请求时，默认情况下会将 `Content-Type` 头设置为 `application/octet-stream`。这向服务器表明请求体包含未知或未指定类型的二进制数据。如果需要指定其他内容类型，可以使用 `--header` 选项设置适当的头部。

值得注意的是，`--data-binary` 与 `curl` 中的 `--data` 选项是不同的。`--data` 选项用于将数据作为请求体发送，但它将数据视为纯文本，进行字符编码和特殊字符解释。相比之下，`--data-binary` 保留了数据的二进制特性，没有进行任何修改。

请记得将 "文件名" 替换为实际的文件路径，或将 "二进制数据" 替换为要发送的二进制数据，并将 "URL" 替换为要发送请求的服务器的 URL。

## xdg-user-dirs-upate  

+ 该命令会读取配置文件`/etc/xdg/user-dirs.defaults`,并在`$HOME`下创建一整套默认的经本地化的用户目录

`xdg-user-dirs-update`命令是一个用于更新用户目录的工具，它在Linux系统中用于管理用户的标准目录，例如桌面、下载、文档、音乐、图片等目录。

在Linux系统中，用户目录的路径通常存储在`~/.config/user-dirs.dirs`文件中。`xdg-user-dirs-update`命令用于根据配置文件中定义的规则，更新用户目录的路径和名称。

以下是`xdg-user-dirs-update`命令的一般语法：

```
xdg-user-dirs-update
```

运行`xdg-user-dirs-update`命令将读取`~/.config/user-dirs.dirs`文件中的配置信息，并根据配置更新用户目录的路径和名称。

`~/.config/user-dirs.dirs`文件的示例内容如下：

```
XDG_DESKTOP_DIR="$HOME/Desktop"
XDG_DOWNLOAD_DIR="$HOME/Downloads"
XDG_DOCUMENTS_DIR="$HOME/Documents"
XDG_MUSIC_DIR="$HOME/Music"
XDG_PICTURES_DIR="$HOME/Pictures"
XDG_VIDEOS_DIR="$HOME/Videos"
```

上述配置定义了标准的用户目录路径，如桌面、下载、文档、音乐、图片和视频目录。

运行`xdg-user-dirs-update`命令后，它将根据配置文件的内容，自动创建相应的目录，并将用户的默认目录路径设置为配置文件中定义的路径。

`xdg-user-dirs-update`命令通常在用户登录时自动执行，确保用户的标准目录存在且正确设置。