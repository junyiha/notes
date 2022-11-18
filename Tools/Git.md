# Git 笔记

## git常见错误

### `fatal:refusing to merge unrelated histories`

+ 在使用`git pull`命令拉取代码时出现这个错误
+ 原因：本地仓库和远程仓库实际上时独立的两个仓库
+ 解决方法：添加选项`--allow-unrelated-histories`解决问题
  + `git pull zhuoer dev --allow-unrelated-histories`

## git 常用命令

### 创建版本库

+ `git clone <url>` : 克隆远程版本库
+ `git init` : 初始化本地版本库

### 修改和提交

+ `git status` : 查看状态
+ `git diff` : 查看变更内容
+ `git add .` : 跟踪所有改动过的文件
+ `git add <file>` : 跟踪指定的文件
+ `git mv <old> <new>` : 文件改名
+ `git rm <file>` : 删除文件
+ `git commit -m "commit message"` : 提交所有更新过的文件
+ `git commit --amend` : 修改最后一次提交

### 查看提交历史

+ `git log` : 查看提交历史
+ `git log -p <file>` : 查看指定文件的提交历史
+ `git blame <file>` : 以列表方式查看指定文件的提交历史

### 撤销

+ `git reset --     0  1.9G   0% /sys/fs/cgroup
/dev/mmcblk0p7   16G   12G  3.1G  79% /data
 HEAD` : 撤销工作目录中所有未提交文件的修改内容
+ `git checkout HEAD <file>` : 撤销指定的未提交的修改内容
+ `git revert <commit>` : 取消指定的提交

### 分支与标签

+ `git branch` : 显示所有本地分支
+ `git checkout <branch/tag>` : 切换到指定分支或标签
+ `git branch <new-branch>` : 创建新分支
+ `git branch -d <branch>` : 删除本地分支
+ `git tag` : 列出所有本地标签
+ `git tag <tagname>` : 基于最新提交的创建标签
+ `git tag -d <tagname>` : 删除标签
+ `git branch -b dev notes/dev` : 切换指定远程分支

### 合并和衍合

+ `git merge <branch>` : 合并指定分支到当前分支
+ `git rebase <branch>` : 衍合指定分支到当前分支

### 远程操作

+ `git remote -v` : 查看远程版本库信息
+ `git remote show <remote>` : 查看指定远程版本库信息
+ `git remote add <remote> <url>` : 添加远程版本库
+ `git fetch <remote>` : 从远程库获取代码
+ `git pull <remote> <branch>` : 下载代码及快速合并
+ `git push <remote> <branch>` : 上传代码及快速合并
+ `git push <remote> :<branch/tag-name>` : 删除远程分支或标签
+ `git push --tags` : 上传所有标签

## 拉取

+ `git pull origin master`
  + `push` : 将本地仓库与远程仓库合并
  + `-u` : 将本地仓库分支与远程仓库分支一起合并，就是说将master的分支也提交上去，这样就可以在远程仓库上看到在本地仓库的master中创建了多少分支。不加这个参数，只将当前的master与远程的合并，没有分支的历史纪录，也不能切换分支
  + `origin` : 远程仓库的意思，如果这个仓库是远程的，那么必须使用这个选项
  + `master` : 提交本地master分支仓库

## 递归克隆

+ `git clone --recursive http://192.167.10.28/dagger/manager_node.git`
+ `recursive`选项会递归克隆项目下的所有git项目

## 撤销 `git add` 并保留修改的方法

+ **`git reset --mixed` -- 撤销所有的已经`add`的文件**
+ `git reset HEAD .` -- 复制撤销某个文件或文件夹
+ `git reset HEAD -filename` -- 另外，可以使用`git status` ，git会告诉可以通过哪一个命令来执行操作

---------------------------------------------------------------------

## 工作流

1. working directory:持有实际文件
2. Index:类似于一个缓冲区与,临时保存文件的改动
3. HEAD:指向最后一次提交的结果

## 添加与提交

1. 把文件添加到暂存区: `git add <filename>`
2. 提交改动信息: `git commit -m "代码提交信息"`. (至此,改动已经提交到了HEAD,但是还没有到远端仓库)
3. 推送改动: `git push origin master(master 换成想要推送的分支)`

## Git工作流程

1. 克隆Git资源作为工作目录
2. 在克隆的资源上添加或者修改文件
3. 如果其他人修改了,你可以更新资源
4. 在提交前查看修改
5. 提交修改
6. 在修改完成后,如果发现错误,可以撤回提交并再次修改并提交

## 基本概念:工作区,暂存区和版本库

+ 工作区:就是在电脑里能够看到的目录
+ 暂存区:英文叫stage或index,一般放在.git目录下的index文件中,所以把暂存区有时也叫做索引(index)
+ 版本库:工作区有一个隐藏目录.git,这个不算工作区,而是git的版本库

1. 当对工作区修改(或新增)的文件执行 `git add` 命令时,暂存区的目录树被更新,同时工作区修改(或新增)的文件内容被写入到对象库中的一个新的对象中,而该对象的ID被记录在暂存区的文件索引中
2. 当执行提交操作时 `git commit` 时,暂存区的目录树写到版本库(对象库)中,master分支会做相应的更新,即**master只想的目录树就是提交时暂存区的目录树.**

## Git官方手册

### Git的三种状态:已提交(committed), 已修改(modified)和已暂存(staged)

+ 已修改:表示修改了文件,但还没有保存到数据库中
+ 已暂存:表示对一个已修改文件的当前版本做了标记,使之包含在下次提交的快照中
+ 已提交:表示数据已经安全地保存在本地数据库中

### 这会让Git项目拥有三个三阶段:工作区, 暂存区和Git目录

+ 工作区:是对项目的某个版本独立提取出来的内容,这些从Git仓库的压缩数据中提取出来的文件,放在磁盘上进行使用或修改
+ 暂存区:是一个文件,保存了下次将要提交的文件列表信息,一般在Git仓库目录中.按照Git的术语叫做"索引",不过一般说法还是叫"暂存区"
+ Git仓库目录:是Git用来保存项目的元数据和对象数据库的地方.这是Git中最重要的部分,**从其他计算机克隆仓库时,复制的就是这里的数据.**

### 基本的Git工作流程

1. 在工作区中修改文件
2. 将想要下次提交的更改 选择性地暂存,这样只会将更改的部分添加到暂存区
3. 提交更新,找到暂存区的文件,将快照永久性存储到Git目录

## `.gitignore` 文件

+ In the project, it does not need to save all of the files. And the `.gitignore` file is used to save the folders which do not need to save.
+ 在工程中，并不是所有文件都需要保存到版本库中。在Git工作区的根目录下创建一个特殊的`.gitignore`文件，把要忽略的文件名填进去，Git就会自动忽略这些文件或目录
+ 匹配规则
  + 空格不匹配任意文件，可作为分隔符，可用反斜杠转义
  + 开头的文件标识注释，可以使用反斜杠进行转义
  + `/` 结束的模式只匹配文件夹以及在该文件夹路径下的内容，但是不匹配该文件
  + `/` 开始的模式匹配项目和目录
  + `?` 通用匹配单个字符
  + `*` 通用匹配零个或多个字符
  + `[]` 通用匹配单个字符列表

## git remote

+ `git remote`：用于管理远程仓库
+ `git remote`：不带参数时可以查看远程仓库名称
+ `git remote -v` : 可以查看远程仓库名称和网址
+ `git remote add 仓库名 仓库地址` : 添加远程仓库，同时设置远程仓库的名字
+ `git remote rm origin` : 删除名字为`origin`的远程仓库

## git branch

+ `git branch` : 可以查看本地仓库的分支情况
+ `git branch 分支名` : 创建分支
+ `git checkout 分支名` : 切换到指定分支
  + 两个命令可以合成一个命令：`git checkout -b 分支名` ，相当于创建分支后切换到新建分支

+ `git branch -d 分支名` : 删除某个分支
+ `git merge 分支名` : 合并某个分支到现在所处的分支

+ `git branch -r` : 查看远程仓库的分支情况
+ `git branch -a` : 查看所有分支的情况，即本地分支和远程分支（上面的部分是本地分支，下面红色的部分是远程的分支）

+ 远程分支的创建不能通过`git branch`进行，而是在`git push`的时候默认执行

+ 分支重命名：`git branch -m oldname newname`

## git push

+ `git push <远程主机名> <本地分支名> : <远程分支名>`
  + 分支的推送顺序写法是：`<来源地>:<目的地>`

+ 远程分支的删除也不能使用`git branch` , 同样采用`git push`
  + `git push <远程主机名> --delete <删除的分支名>`
  + 或者：`git push <远程主机名> : <远程分支名>` ，省略了本地分支名相当于推送了一个空的本地分支到远程分支上，就相当于删除了远程分支

## git fetch

+ `git fetch`这个命令用于取回远程仓库上的更新到本地仓库，默认是取回远程仓库上的所有更新，
+ 如果要取回执行分支上的内容，可以使用`git fetch <远程仓库> <分支名>`。这样取回的分支是不会影响本地仓库中的代码，通常用于查看他人进程，取回远程分支之后，可以在远程分支的基础上创建新的分支，也可以将远程分支和本地分支合并:`git merge origin/dev` or `git rebase origin/dev` ： 表示将当前分支与远程分支合并

---------------------------------------------------------------

## git从历史上的某一次提交处建立分支

+ `git log --oneline --all --graph --decorate`
+ `git branch dev 3be5879`

## 远程仓库

+ `git remote add <shortname> <url>` ： 添加一个新的远程Git仓库，同时指定一个方便使用的简写.
  + `git remote add zhuoer http://192.167.10.28/dagger/zhuoer` ： 现在可以在命令行中使用字符串`zhuoer`来代替整个URL

+ `git fetch <remote>` : 从远程仓库中获得数据。这个命令会访问远程仓库，从中拉取所有还没有的数据。执行完成后，将会拥有那个远程仓库中所有分支的引用，可以随时合并或者查看。
+ **如果使用`clone`命令克隆了一个仓库，命令会自动将其添加为远程仓库并且默认以`origin`为简写**。所以，`git fetch origin`会抓取克隆（或上一次抓取）后新推送的所有工作。
  + 注意：`git fetch`命令只会将数据下在到本地仓库，它并不会自动合并或者修改当前的工作，当准备好时，必须要手动将其合并入你的工作。
+ 如果当前分支设置了跟踪远程分支，那么可以使用`git pull`命令自动抓取后合并该远程分支到当前分支。
+ 默认情况下，`git clone`命令会自动设置本地`master`分支跟踪克隆的远程仓库的`master`分支（或其他名字的默认分支）。运行`git pull`通常会从最初克隆的服务器上抓取数据并自动尝试合并到当前所在的分支。）

## 推送到远程仓库

+ `git push <remote> <branch>`
  + 当你想要将`master`分支推送到`origin`服务器时（再次说明，克隆时通常会自动帮你设置好那两个名字），那么运行这个命令就可以将你所做的备份到服务器。

## 查看某个远程仓库

+ `git remote show <remote>`
  + 查看某一个远程仓库的更多信息
  + 它同样会列出远程仓库的URL与跟踪分支的信息。它告诉你正在处于`master`分支，并且如果运行`git pull`，就会抓取所有的远程引用，然后将远程`master`分支合并到本地`master`分支，
  + 它也会列出拉取到的所有远程引用。

### 远程仓库的重命名与移除

+ `git remote rename`
  + 修改一个远程仓库的简写名
  + 这个操作也会修改所有远程跟踪的分支名字

+ `git remote remove`或者`git remote rm`
  + 移除一个远程仓库
  + 一旦使用这种方式删除了一个远程仓库，那么所有和这个远程仓库相关的远程跟踪分支以及配置信息也会一起被删除。

## 打标签

+ `git tag`
  + 在Git中列出已有的标签
  + 按照通配符列出标签需要`-l`或者`--list`选项
  + 如果只想要完整的标签列表，那么运行`git tag`就会默认假定你想要一个列表，它会直接列出来

+ 创建标签，Git支持两种标签：轻量标签(`lightweight`)与附注标签(`annotated`)
  + 轻量标签很像一个不会改变的分支--它只是某个特定提交的引用
  + 附注标签是存储在Git数据库中的一个完整对象，它们是可以被校验的，其中包括打标签者的名字，电子邮件，地址，日期时间，此外还有一个标签信息，并且可以使用GNU Privacy Guard（GTG）签名并验证。
+ 通常会建议创建附注标签，这样可以拥有以上所有信息，但是如果只是想用一个临时的标签，或者因为某些原因不想要保存信息，那么也可以用轻量标签

+ 附注标签的创建: `git tag -a v1.4 -m "my version 1.4"`
  + `-m` : 指定了一条将会存储在标签中的信息。如果没有为附注标签指定一条信息，Git会启动编辑其要求你输入信息

+ 轻量标签，本质上是将提交校验和存储到一个文件中--没有保存任何其他信息。
+ 创建轻量标签，不需要使用`-a`, `-s`, `-m`选项，只需要提供标签名字：`git tag v1.4-lw`

+ 后期打标签
  + 要在提交上打标签，需要在命令的末尾指定提交的校验和（或部分校验和）
  + `git tag -a v1.2 9fcaw1`

+ 删除标签
  + 删除本地仓库上的标签，可以使用命令`git tag -d <tagname>`
    + 注意：该命令并不会从任何远程仓库中移除这个标签，必须使用`git push <remote>:refs/tags/<tagname>`来更新远程仓库
    + 第一种变体是：`git push <remote> :refs/tags/<tagname>`，这种操作的含义是：将冒号前面的空值推送到远程标签名，从而高效地删除它
    + 第二种更加直观的删除远程标签的方式是：`git push <remote> --delete <tagname>`

+ 通过使用`git show`可以看到标签信息和与之对应的提交信息

## Git别名

+ Git并不会在输入部分命令时自动推断出想要的命令。如果不想每次都输入完整的Git命令，可以通过`git config`文件来轻松地为每一个命令设置一个别名。
+ 例如：
  + `git config --global alias.co checkout`
  + `git config --global alias.br branch`
  + `git config --global alias.ci commit`
  + `git config --global alias.st status`
  + 这意味着，当要输入`git commit`时，只需要输入`git ci`
+ 在创建认为应该存在的命令时，这个技术会很有用。
  + 例如：为了解决取消暂存文件的易用性问题，可以向Git中添加取消暂存别名,`git config --global alias.unstage 'reset HEAD --`
  + 通常也会添加一个`last`命令：`git config --global alias.last 'log -l HEAD`。这样，可以很轻松地看到最后一次提交
+ Git只是简单地将别名替换为对应的命令。

## Git分支

+ 几乎所有的版本控制系统都以某种形式支持分支。使用分支意味着可以把工作从开发主线上分离开来，以免影响开发主线。

+ **Git保存的不是文件的变化或者差异，而是一系列不同时刻的快照。**
+ Git的分支，其实质上仅仅是指向提交对象的可变指针。Git的默认分支名字是`master`，在多次提交操作之后，其实已经有一个指向最后哪个提交对象的`master`分支。`master`分支会在每次提交时自动向前移动。
  + Git的`master`分支并不是一个特殊分支。它跟其他分支完全没有区别。之所以几乎每一个仓库都有`master`分支，是因为`git init`命令默认创建它，并且大多数人都懒得去改动它

+ `git branch testing` : 创建分支`testing`，这会在当前所在的提交对象上创建一个指针。那么，Git又是怎么知道当前在哪一个分支上呢？
  + 也很简单，它有一个名为`HEAD`的特殊指针。它是一个指针，指向当前所在的本地分支（可以把`HEAD`想象为当前分支的别名）
  + 在本示例中，仍然在`master`分支上，因为`git branch`命令仅仅创建一个新分支，并不会自动切换到新分支中去
+ `git log --decorate` ： 查看各个分支当前所指的对象

+ 分支切换:`git checkout testing`。如此以来，`HEAD`就指向`testing`分支了。

+ 由于Git的分支实质上仅是包含所指对象校验和（长度为40的SHA-1值字符串）的文件，所以它的创建和销毁都异常高效

### 远程分支

+ 远程引用是对远程仓库的引用（指针），包括分支，标签等。
+ 可以通过 `git ls-remote <remote>`来显示地获得远程引用的完整列表
+ 或者通过`git remote show <remote>`获得远程分支的更多信息
+ 更常见的做法是利用**远程跟踪分支**，远程跟踪分支是远程分支状态的引用，它们以`<remote>/<branch>`的形式命名
  + 例如：假设网络里由一个在`git.ourcompany.com`的Git服务器。如果从这里克隆，Git的`clone`命令会自动将其命名为`origin`，拉取它的所有数据，创建一个指向它的`master`分支的指针，并且在本地将其命名为`origin/master`。Git也会给你一个与`origin`的`master`分支在指向同一个地方的本地`master`分支，这样你就有工作的基础。
  + `origin`并无特殊含义。远程仓库名字`origin`与分支名字`master`一样，在Git中并没有任何特别的含义一样。同时,`master`是当你运行`git init`时默认的起始分支名字。如果你运行`git clone -o booyah`，那么默认的远程分支名字将会是`booyah/master`

+ `git push <remote> <branch>` ： 推送到某个分支

+ 与给定的远程仓库同步数据，运行`git fetch <remote>`命令。
  + 示例：`git fetch a311d`
  + 这个命令查找`a311d`是哪一个服务器，从中抓取本地没有的数据，并且更新本地数据库，移动`a311d/master`指针到更新之后的位置。

+ `git pull` : 拉取
  + 当`git fetch`命令从服务器上抓取本地没有的数据时，它并不会修改工作目录中的内容，它只会获取数据然后让你自己合并
  + `git pull`命令在大多数情况下它的含义是一个`git fetch`紧接着一个`git merge`命令

## 如何避免每次输入密码

+ 如果正在使用`HTTPS URL`来推送，Git服务器会询问用户名与密码。默认情况下它会在终端中提示服务器是否允许你进行推送
+ 如果不想在每一个推送时都输入用户名与密码，可以设置一个`credential cache`。最简单的方式就是将其保存在内存中几分钟，可以简单地运行`git config --global credential.helper cache`来设置

## 跟踪分支

+ 从一个远程跟踪分支检出一个本地分支会自动创建所谓的“跟踪分支”（它跟踪的分支叫做“上游分支”）。
+ 跟踪分支是与远程分支有直接关系的本地分支。如果在一个跟踪分支上输入`git pull`，Git能够自动地识别去那个服务器上抓取，合并到哪个分支。
+ 当克隆一个仓库时，它通常会自动地创建一个跟踪`origin/master`的`master`分支。
+ 如果想设置其他的跟踪分支，或者是一个在其他远程仓库上的跟踪分支，简单的示例：`git checkout -b <branch> <remote>/<branch>`。这是一个十分常用的操作，所以Git提供了`--track`快捷方式
+ 如果想要将本地分支与远程分支设置为不同的名字，可以使用命令`git checkout -b sf origin/serverfix`

## 删除远程分支

+ 运行带有`--delete`选项的`git push`命令，用来删除一个远程分支，例如:`git push zhuoer --delete docker-mqtt`
+ 基本上这个命令做的只是从服务器上移除这个指针。Git服务器通常会保留数据一段时间直到垃圾回收运行，所以如果不小心删除掉了，通常是很容易恢复的。

## Git 子模块

+ 使用场景：某个工作中的项目需要包含并使用另一个项目。也许是第三方库，或者独立开发的，用于多个父项目的库。现在问题是：把它们当作两个独立的项目，同时又想在一个项目中使用另一个
+ Git通过**子模块**来解决这个问题：子模块允许将一个Git仓库作为另一个Git仓库的子目录。它能够将另一个仓库克隆到自己的项目中，同时还可以保持提交的独立。

+ 将一个已存在的Git仓库添加为正在工作的仓库的自模块：`git submodule add`命令后加上想要跟踪的项目的相对或者绝对URL来添加新的子模块。
  + 默认情况下，子模块会将子项目放到一个与仓库同名的目录中，如果想放到其他地方，可以在命令结尾添加一个不同的路径。
+ `.gitmodules`配置文件，保存了项目URL与已经拉取的本地目录之间的映射