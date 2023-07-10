## 简介

+ Git常见的语法知识

## git tag 标签的使用

### 标签(tag)相关的常用命令

+ `git tag` 查看标签
+ `git tag <tag-name>` 创建命名标签
+ `git tag -a <tag-name> -m <message>` 添加一个注解标签
+ `git tag <tag-name> <commit-id> -a -m <message>` 给过去提交记录创建标签
+ `git push origin <tag-name>` 推送标签到远程仓库
+ `git push origin --tags` 推送全部标签
+ `git pull origin --tags` 远程拉取标签
+ `git tag -d <tag-name>` 删除本地标签
+ `git push origin :refs/tags/<tag-name>` 删除远程标签

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
