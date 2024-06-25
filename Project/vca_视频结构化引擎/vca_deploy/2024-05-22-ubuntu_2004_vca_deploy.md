---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: ubuntu_2004_vca_deploy
tag: ProjectOfVideoContentAnalysis
---

+ 安装openssh-server, openssh-client
+ 配置sshd-config文件
  + 修改`PermitRootLogin yes`
  + 修改`Port 20233`

## 依赖环境

+ python3.8.3
  + 因为算力节点和管理节点的代码是用python编写的

+ nginx
  + 用于浏览器访问后端

+ mysql
  + 用于永久存储告警数据和其他信息

+ supervisor
  + 用于管理算力节点和管理节点的启动和停止

+ redis
  + 用于vca和算力节点，算力节点和管理节点的实时通信

## 安装步骤

### python3.8.3

+ 源代码：
  + /mnt/remote/190-mnt/zhangjunyi/Software/python/Python-3.8.3.tgz

+ 安装依赖包
  - `apt-get install -y libssl-dev openssl libffi-dev zlib1g-dev`

+ 编译安装Python3.8.3
  + `cd Python-3.8.3`
  + `./configure --prefix=/usr/local/python38`
  + `make && make install`
  + `ln -s 

+ 安装算力节点和管理节点的python依赖组件
  + `/usr/local/python38/bin/python3.8 -m pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --upgrade pip`
  + `/usr/local/python38/bin/python3.8 -m pip install -i https://pypi.tuna.tsinghua.edu.cn/simple -r ./requirement.txt`
  + requirement.txt:
    + 管理节点
      - redis==3.2.1
      - psutil==5.7.0
      - pyzmq==20.0.0
      - django-cors-headers==3.11.0
      - configobj==5.0.6
      - pymysql==1.0.2
      - Django==3.2.5
      - djangorestframework==3.11.0
      - django_redis==5.2.0
      - django-filter==21.1
      - xlwt==1.3.0
      - pillow==9.0.1
      - APScheduler==3.8.1
      - requests==2.22.0
      - netifaces
      - #opencv-python==4.1.1.26  Could not find a version that satisfies the requirement
      - opencv-python==4.1.2.30
      - #numpy==1.17.2 opencv-python 4.1.2.30 depends on numpy>=1.17.3
      - numpy==1.17.3
      - concurrent-log-handler==0.9.20
      - uwsgi
    + 算力节点：
      - paho-mqtt==1.6.1
      - redis==3.2.1
      - psutil==5.7.0
      - pyzmq==20.0.0

## mysql

+ 安装mysql
  + `apt-get install mysql-server`

+ 修改密码(mysql 8.0.32)：
  + 添加`skip-grant-table`跳过权限验证
    + `/etc/mysql/mysql.conf.d/mysqld.conf`
  + 重启服务
    + `/etc/init.d/mysql restart`
  + 刷新权限列表
    + `flush privileges;`
  + 密码重置
    + 先把root的旧密码置空
    + `use mysql;`
    + `update user set authentication_string='' where user='root';`
    + 退出，将`skip-grant-table`注释，重启mysql服务
    + 设置新密码：
    + `alter user 'root'@'localhost' identified by '123456';`

+ 修改密码mysql(7.5)
  - use mysql;
  - update user set authentication_string='123456' where user='root';
  - update user set plugin="mysql_native_password";
  - flush privileges;

+ 导入数据库
  + source命令导入
    + `create database ManagerV3;`
    + `use ManagerV3;`
    + `set names utf8;`
    + `source /data/dagger/ManagerV3.sql;`

## redis

+ 安装redis
  - `apt-get install redis-server`

## nginx

+ 安装nginx
  + `apt-get install nginx`

+ 配置文件：
  + /mnt/remote/190-mnt/zhangjunyi/Software/nginx/

## supervisor

+ 安装supervisor
  + `apt-get install supervisor`

+ 配置文件路径
  + /mnt/remote/190-mnt/zhangjunyi/Software/supervisor/
  + 修改LD_LIBRARY_PATH环境变量