## 简介

+ apt相关命令笔记

## linux apt-file命令 详解

`apt-file` 是一个用于查询 APT 软件包中包含的文件的命令行工具。它不仅可以帮助你查找已安装软件包中的文件，还可以查找尚未安装但包含在软件包中的文件。使用 `apt-file` 可以帮助你找到特定文件属于哪个软件包。

以下是一些常见的 `apt-file` 命令及其说明：

1. **安装 apt-file：**
   ```bash
   sudo apt install apt-file
   ```
   在使用 `apt-file` 之前，你需要安装它。

2. **更新文件数据库：**
   ```bash
   sudo apt-file update
   ```
   在查询之前，你需要先更新文件数据库，以确保它包含最新的信息。

3. **搜索已安装软件包中的文件：**
   ```bash
   apt-file list 软件包名称
   ```
   该命令列出指定已安装软件包中包含的文件。

4. **搜索未安装软件包中的文件：**
   ```bash
   apt-file search 文件名
   ```
   该命令搜索未安装软件包中包含指定文件名的软件包。

5. **显示与正则表达式匹配的所有软件包：**
   ```bash
   apt-file search --regexp '正则表达式'
   ```
   该命令显示与指定正则表达式匹配的所有软件包。

6. **查找包含某个目录的软件包：**
   ```bash
   apt-file search /path/to/directory
   ```
   该命令搜索包含指定目录的软件包。

7. **显示文件属于哪个软件包：**
   ```bash
   apt-file search --package-only 文件名
   ```
   该命令仅显示包含指定文件名的软件包。

8. **在所有已知软件包中搜索文件：**
   ```bash
   apt-file search --all 文件名
   ```
   该命令在所有已知的软件包中搜索指定文件名，包括未安装的软件包。

使用 `apt-file` 可以方便地查找软件包中的文件，这对于理解系统中的文件属于哪个软件包、找出软件包提供的特定文件等非常有用。

## linux apt-cache命令 详解

`apt-cache` 是 Linux 中用于查询 APT (Advanced Package Tool) 缓存的命令行工具。它允许用户从本地软件包数据库中检索有关软件包的信息，包括依赖关系、版本、描述等。

以下是一些常见的 `apt-cache` 命令及其说明：

1. **查看软件包信息：**
   ```bash
   apt-cache show 软件包名称
   ```
   该命令显示有关指定软件包的详细信息，包括版本、大小、依赖关系、描述等。

2. **搜索软件包：**
   ```bash
   apt-cache search 关键词
   ```
   通过该命令可以搜索软件包。它会列出所有与指定关键词相关的软件包。

3. **显示软件包提供的文件：**
   ```bash
   apt-cache showpkg 软件包名称
   ```
   该命令用于显示软件包提供的文件列表，以及该软件包所依赖的其他软件包。

4. **显示软件包的依赖关系：**
   ```bash
   apt-cache depends 软件包名称
   ```
   该命令用于显示指定软件包的依赖关系。

5. **显示软件包的反向依赖关系（被哪些软件包依赖）：**
   ```bash
   apt-cache rdepends 软件包名称
   ```
   该命令用于显示指定软件包的反向依赖关系，即依赖于该软件包的其他软件包。

6. **显示 APT 缓存统计信息：**
   ```bash
   apt-cache stats
   ```
   该命令用于显示有关 APT 缓存的统计信息，包括软件包的数量、大小等。

7. **显示软件包的提供者信息：**
   ```bash
   apt-cache showpkg -a 软件包名称
   ```
   该命令显示软件包在不同体系结构上的提供者信息。

8. **显示软件包的正则表达式匹配信息：**
   ```bash
   apt-cache showpkg --names-only '正则表达式'
   ```
   该命令显示与指定正则表达式匹配的软件包名称。

以上是一些常见的 `apt-cache` 命令。这些命令可以帮助你更好地了解软件包的信息和相互关系。

## linux apt apt-get

`apt` 和 `apt-get` 是 Linux 系统中用于管理软件包的两个命令，它们都属于 Advanced Package Tool（APT）工具集。

1. **apt-get:**
   - `apt-get` 是较早的软件包管理命令，用于安装、卸载、更新和管理软件包。它使用比较直接的命令语法，如 `apt-get install`、`apt-get remove` 等。
   - 示例：安装一个软件包
     ```bash
     sudo apt-get install 软件包名称
     ```
   - `apt-get` 在操作时需要使用 `sudo` 以管理员权限执行。

2. **apt:**
   - `apt` 是 `apt-get` 的新一代包装，提供了更简洁、友好的命令行接口，并且支持逐步更新。它整合了一些常用的 `apt-get` 子命令，使得用户在使用时更为方便。
   - 示例：安装一个软件包
     ```bash
     sudo apt install 软件包名称
     ```
   - `apt` 使用时同样需要 `sudo` 权限。

一些使用 `apt` 相对于 `apt-get` 的优点包括：
- 更友好的输出和进度条。
- 能够显示可用的自动修复指令。
- 与 `apt` 命令一起使用的时候，不需要再运行 `apt-get update` 命令。

两者的基本功能是相似的，但 `apt` 提供了更为现代和用户友好的界面。在新的 Ubuntu 版本中，推荐使用 `apt` 命令。在老的系统或某些特殊情况下，你可能会看到人们仍然使用 `apt-get`。

## linux apt命令 详解

`apt`（Advanced Package Tool）是用于在Debian及其衍生发行版（如Ubuntu）中进行软件包管理的工具。它提供了一组命令，用于搜索、安装、卸载、更新和管理软件包。以下是一些常用的`apt`命令及其说明：

1. **更新软件包列表：**
   ```bash
   sudo apt update
   ```
   该命令用于从软件源服务器更新本地软件包列表，以获取最新的软件包信息。在执行其他`apt`命令之前，通常应该首先运行此命令。

2. **升级已安装的软件包：**
   ```bash
   sudo apt upgrade
   ```
   该命令用于升级已安装的所有软件包到最新可用的版本。在执行升级操作之前，建议先运行`apt update`以确保软件包列表是最新的。

3. **升级系统：**
   ```bash
   sudo apt dist-upgrade
   ```
   该命令用于执行更大规模的系统升级，包括新内核的安装等。它会比`apt upgrade`更积极地解决依赖关系。

4. **安装软件包：**
   ```bash
   sudo apt install 软件包名称
   ```
   该命令用于安装指定软件包。你可以同时安装多个软件包，例如：
   ```bash
   sudo apt install 软件包1 软件包2
   ```

5. **卸载软件包：**
   ```bash
   sudo apt remove 软件包名称
   ```
   该命令用于卸载指定软件包，但保留其配置文件。如果你希望同时删除配置文件，可以使用`purge`：
   ```bash
   sudo apt purge 软件包名称
   ```

6. **搜索软件包：**
   ```bash
   apt search 关键词
   ```
   该命令用于搜索与指定关键词相关的软件包。

7. **显示软件包信息：**
   ```bash
   apt show 软件包名称
   ```
   该命令用于显示有关指定软件包的详细信息，包括版本、大小、依赖关系等。

8. **清理无用的软件包：**
   ```bash
   sudo apt autoremove
   ```
   该命令用于删除已安装但不再需要的软件包。

这些是一些`apt`命令的常见用法。你可以使用`man apt`查看`apt`的手册以获取更详细的信息。

## linux apt命令 常用技巧

在使用`apt`命令时，有一些常用的技巧和实用的选项，可以提高软件包管理的效率。以下是一些常见的技巧：

1. **查看软件包信息：**
   ```bash
   apt show 软件包名称
   ```
   可以使用该命令查看软件包的详细信息，包括版本、大小、依赖关系等。

2. **查找软件包：**
   ```bash
   apt search 关键词
   ```
   通过该命令可以搜索软件包。可以根据关键词查找与之相关的软件包。

3. **模糊搜索：**
   ```bash
   apt list | grep 关键词
   ```
   使用`apt list`列出所有可用软件包，然后通过`grep`进行模糊搜索。

4. **列出已安装的软件包：**
   ```bash
   apt list --installed
   ```
   该命令列出所有已经安装的软件包。

5. **列出可升级的软件包：**
   ```bash
   apt list --upgradeable
   ```
   该命令列出可以升级的所有软件包。

6. **查看软件包依赖关系：**
   ```bash
   apt depends 软件包名称
   ```
   该命令用于查看指定软件包的依赖关系。

7. **查看软件包提供的文件：**
   ```bash
   dpkg -L 软件包名称
   ```
   使用`dpkg`命令查看指定软件包提供的文件列表。

8. **使用代理服务器：**
   如果你在使用代理服务器，可以在`/etc/apt/apt.conf`中设置代理配置，或者在命令行中使用`-o`选项：
   ```bash
   sudo apt -o Acquire::http::Proxy="http://代理地址" update
   ```

9. **使用多线程下载：**
   在更新软件包时，可以使用多线程进行下载以提高速度。在`/etc/apt/apt.conf`中添加以下配置：
   ```
   Acquire::http::Pipeline-Depth "0";
   Acquire::http::No-Cache "true";
   Acquire::http::Dl-Limit "256";
   ```

10. **使用国内镜像：**
    将系统的软件源替换为国内镜像源可以加快下载速度。在`/etc/apt/sources.list`中修改软件源，将其替换为适合你的国内源。

这些技巧可以让你更方便、更高效地使用`apt`命令进行软件包管理。根据个人需要，你可以结合这些技巧执行不同的操作。

## apt 家族

### apt

+ update
  - 从所有配置的源中下载包信息。其他的命令对这些数据进行操作

+ upgrade
  - upgrade 用于安装当前安装在系统上的所有软件包的可用升级，这些软件包来自于 sources.list(5) 配置的源的升级
  - 如果有需要满足的依赖关系，新的安装包将会被安装。但是现有的安装包永远都不会被删除。如果一个软件包的升级需要删除一个已安装的软件包，那么这个软件包的升级将不会被执行

+ full-upgrade
  - full-upgrade执行升级的功能，但如果需要升级系统，它将删除当前安装的软件包，如果需要这样做来升级整个系统的话。 

+ install, remove, purge
  - install, 安装软件包
  - remove, 仅删除软件包数据，会留下用户配置信息
  - purge, 会既删除软件包数据，也会删除用户配置信息 

+ autoremove
  - autoremove是用来删除那些自动安装的软件包，以满足依赖的软件包，但现在不再需要了，因为依赖关系改变了或需要它们的软件包在这期间被删除，因此不再需要。 

+ search
  - 搜索可以用来在可用的软件包列表中搜索给定包的列表中搜索，并显示匹配结果。 

+ show
  - 显示有关给定软件包的信息，包括它的依赖性、安装和下载大小、软件包的可用来源以及对它的描述和下载大小，软件包的可用来源，软件包内容的描述等等。包的内容描述等等。 

+ list
  - list与dpkg-query --list有点类似，它可以显示满足特定条件的满足特定条件的软件包列表。 

+ edit-sources
  - edit-sources 可以让你在你喜欢的文本编辑器中编辑 sources.list(5) 文件。同时也提供基本的智能检查。 

### apt-get 

+ update
+ upgrade

+ dist-upgrade
  - dist-upgrade除了执行升级的功能外，还能智能地处理新版本软件包的依赖关系变化；apt-get有一个 "智能 "的冲突解决系统，它将尝试升级最重要的软件包如果有必要的话，它会尝试升级最重要的软件包，而牺牲掉不那么重要的软件包。 

+ dselect-upgrade
  - dselect-upgrade与传统的Debian packaging前端，即 dselect(1)。 

+ install
+ remove
+ purge

+ source 
  - 获取源码包

+ build-dep
  - build-dep 导致 apt-get 安装/移除软件包，以满足一个源代码软件包的构建的依赖性。 

+ check
  - 检查是一个诊断工具；它更新软件包缓存并检查损坏的依赖关系。 

+ download
  - download将下载给定的二进制包到当前目录。

+ clean
  - 清理本地存储库中检索到的软件包文件。它删除了除锁文件外的所有文件都从 /var/cache/apt/archives/ 和/var/cache/apt/archives/partial/。 

+ autoclean
  - 和clean一样，autoclean也会清除本地仓库中检索到的软件包文件。不同的是不同的是，它只删除那些不能再被下载的软件包文件，并且基本上是无用的。 

+ changelog
  - changelog试图下载一个软件包的更新日志并通过sensible-pager。

+ indextargets
  - 默认情况下，显示一个deb822格式的所有数据文件的信息列表(又称索引目标) apt-get update 会下载。 

### apt-cache 

在Linux中，`apt-cache`是一个用于查询APT（Advanced Package Tool）软件包管理器缓存的命令行工具。它允许您查看已安装软件包和可用软件包的详细信息，以及搜索软件包的相关信息。

下面是一些常见的`apt-cache`命令选项和用法：

1. 查询软件包信息：
   - `apt-cache show <package>`：显示指定软件包的详细信息，包括版本、描述、作者、依赖关系等。
   - `apt-cache showpkg <package>`：显示软件包的包信息以及其相关的依赖关系和依赖它的软件包信息。

2. 搜索软件包：
   - `apt-cache search <pattern>`：根据模式搜索可用的软件包。模式可以是软件包名称、关键字或描述的一部分。
   - `apt-cache search <keyword1> <keyword2>`：根据多个关键字搜索软件包。这将返回同时包含这些关键字的软件包。
   - `apt-cache search --names-only <pattern>`：只搜索软件包的名称而不搜索描述或关键字。

3. 显示依赖关系：
   - `apt-cache depends <package>`：显示指定软件包的依赖关系，包括它所依赖的软件包和被它所依赖的软件包。
   - `apt-cache rdepends <package>`：显示依赖于指定软件包的其他软件包。

4. 清除软件包缓存：
   - `apt-cache clean`：清除APT软件包管理器的本地软件包缓存。这将删除已下载的软件包文件，但不会删除已安装的软件包。

这些是`apt-cache`命令的一些常见选项和用法。您可以使用`apt-cache`命令来获取关于软件包的信息、搜索软件包以及查看软件包的依赖关系。在使用这些命令时，请确保以管理员权限运行，例如使用`sudo`命令。

### apt-file

+ 查找包文件
  + `apt-file find libopenssh.so`

在Linux中，`apt-file`是一个用于查询软件包文件的命令行工具。它可以帮助您查找特定文件属于哪个软件包，并可以搜索软件包中的文件。

以下是一些常见的`apt-file`命令选项和用法：

1. 初始化数据库：
   在第一次使用`apt-file`之前，需要初始化文件数据库。使用以下命令进行初始化：
   ```bash
   sudo apt-file update
   ```

2. 查询文件所属的软件包：
   - `apt-file search <filename>`：查询指定文件所属的软件包。文件名可以是绝对路径或相对路径。
   - 例如：`apt-file search /bin/ls`将返回包含`/bin/ls`的软件包。

3. 列出软件包中的文件：
   - `apt-file list <package>`：列出指定软件包中的所有文件。
   - 例如：`apt-file list coreutils`将列出`coreutils`软件包中的所有文件。

4. 搜索文件名：
   - `apt-file search <pattern>`：根据模式搜索文件名。模式可以是文件名的一部分或关键字。
   - 例如：`apt-file search libstdc++.so`将返回包含`libstdc++.so`的软件包。

请注意，`apt-file`命令需要根据您的系统安装软件包文件的索引数据库。因此，在使用`apt-file`之前，需要确保数据库已经初始化并更新。您可以使用`sudo apt-file update`命令来更新数据库。

使用`apt-file`命令可以帮助您轻松地查找软件包文件和软件包中的文件。这对于解决缺少文件或查找特定文件所属的软件包非常有用。

### apt-mark

在Linux中，`apt-mark`是一个用于标记和操作APT软件包状态的命令行工具。它可以用于设置、清除和查询软件包的各种标记，以及管理软件包的状态。

以下是一些常见的`apt-mark`命令选项和用法：

1. 标记软件包状态：
   - `apt-mark hold <package>`：将指定软件包标记为"hold"状态，阻止其被升级或删除。
   - `apt-mark unhold <package>`：取消指定软件包的"hold"标记。

2. 设置软件包自动安装状态：
   - `apt-mark auto <package>`：将指定软件包标记为"auto"状态，允许APT自动安装和升级。
   - `apt-mark manual <package>`：将指定软件包标记为"manual"状态，阻止APT自动安装和升级。

3. 查询软件包状态：
   - `apt-mark showhold`：显示所有被标记为"hold"状态的软件包。
   - `apt-mark showauto`：显示所有被标记为"auto"状态的软件包。

4. 清除软件包状态：
   - `apt-mark unmarkauto <package>`：取消指定软件包的"auto"标记。
   - `apt-mark unmarkhold <package>`：取消指定软件包的"hold"标记。
   - `apt-mark unmarkall`：清除所有软件包的标记。

这些是`apt-mark`命令的一些常见选项和用法。您可以使用`apt-mark`命令来设置软件包的状态标记，以控制APT软件包管理器的行为。这对于防止软件包被升级或删除、手动管理软件包状态以及自定义软件包安装行为非常有用。请注意，在使用这些命令时，需要以管理员权限运行，例如使用`sudo`命令。

## aptitude 

`aptitude`是Linux系统中的一个交互式软件包管理器，用于安装、升级、删除和管理软件包。它提供了一个用户友好的命令行界面，可以方便地浏览、搜索和操作软件包。

下面是一些常见的`aptitude`命令选项和用法：

1. 浏览软件包列表：
   - `aptitude`：启动`aptitude`界面，显示可用软件包列表。
   - 使用箭头键或快捷键浏览软件包列表。
   - 输入软件包名或关键字进行搜索。

2. 安装和卸载软件包：
   - 使用`+`号标记软件包以进行安装。
   - 使用`-`号标记软件包以进行卸载。
   - 按下`g`键执行所有标记的操作。

3. 查看软件包详细信息：
   - 在软件包列表中选中一个软件包，按下`Enter`键以查看详细信息。
   - 显示软件包的描述、版本、依赖关系和其他相关信息。

4. 搜索软件包：
   - 按下`/`键进行搜索，然后输入要搜索的软件包名称或关键字。
   - 使用箭头键浏览搜索结果。

5. 进阶命令：
   - `aptitude update`：更新软件包列表。
   - `aptitude upgrade`：升级可用的软件包。
   - `aptitude dist-upgrade`：执行发行版升级，包括软件包和系统组件的升级。
   - `aptitude clean`：清理软件包缓存。
   - `aptitude autoclean`：清理旧版本的软件包。

请注意，`aptitude`命令提供了更多功能和选项，可以根据您的需求进行更高级的软件包管理操作。在使用`aptitude`时，请仔细阅读相关文档和手册，以了解更多命令和选项的详细信息。

总体而言，`aptitude`是一个功能强大且易于使用的软件包管理器，提供了交互式的方式来管理和控制Linux系统上的软件包。