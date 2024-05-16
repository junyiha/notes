## 简介

+ github 平台使用

## 使用https

+ 清除所有的git配置
  + sudo aptitude purge git

+ 在github生成token，它具有访问项目的权限

+ 安装gh工具
  + sudo apt install gh

+ 配置个人信息
  + gh auth login
  + username: 
  + token

+ git使用https

## git clone 出错

+ 今天克隆GitHub仓库中的项目时，执行git clone git://github.com/alibaba/Tangram-Android.git却失败报错：
  ```
    Cloning into 'Tangram-Android'...
    fatal: unable to access 'http://github.com/alibaba/Tangram-Android.git/': OpenSSL SSL_read: Connection was reset, errno 10054
  ``` 
+ 解决方法，需要执行以下两个步骤：
  + 输入git config --global http.sslVerify "false"，解除SSL验证；
  + 将地址https://改为git://，避开SSL验证。

## git连接到github远程仓库，并提交代码至远程仓库

+ 设置用户名和邮箱
  + `git config --global user.name "elliot53"`
  + `git config --global user.email "1604244855@qq.com"`

+ 查看配置的用户名和邮箱
  + `git config user.name`
  + `git config user.email`

+ 生成SSH Key密钥
  + `ssh-keygen -t rsa -C "1604244855@qq.com"`
  + 连续按下三次回车，密钥会在第一次回车的时候，输出密钥文件将要保存的位置

+ 获取SSH Key密钥
  + `cat /root/.ssh/rsa.pub`
  + 选中并复制全部密钥（ssh-rsa开始，一直到.com结束）

+ 配置github密钥
  + 打开github-settings
  + 选择SSH and GPG keys
  + 点击New SSH key 
  + 填入title和key

+ 在本地仓库配置远程仓库地址，本地仓库链接远程仓库
  + 复制远程仓库的ssh地址
  + `git remote add origin_ssh ssh@github.com/elliot53/notes.git`

+ 测试链接是否成功
  + `ssh -T git@github.com`

+ 脚本
```bash
git config --global user.name "elliot53"
git config --global user.email "1604244855@qq.com"
git config user.name
git config user.email
ssh-keygen -t rsa -C "1604244855@qq.com"
cat ~/.ssh/id_rsa.pub
git remote add origin_ssh ssh@github.com/elliot53/notes.git
ssh -T git@github.com
```

## 什么是GitHub Actions

+ 一个简单的需求，是在仓库出现更改时自动更新构建与部署博客。其实，监视仓库并在由改动时自动执行一系列动作是非常广泛的需求。软件开发工作中，经常需要对新添加的代码随时进行测试，或者进行部署，都是通过这样的自动化流程实现的。
+ 实际上，这类服务还有个专业名词: 持续集成(Continuous Intergration)/持续部署(Continuous Deploy)，简称CI/CD

+ 此前，最广泛使用的CI服务当属于Travis CI;现在GitHub也推出了自家的CI服务GitHub Actions。
+ 当仓库收到新的更新(push)时,GitHub会根据仓库中.github/workflows文件夹下的YAML配置文件启动CI流程