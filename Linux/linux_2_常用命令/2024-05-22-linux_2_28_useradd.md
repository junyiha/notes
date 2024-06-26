---
category: Linux
date: 2024-05-22 09:00:00 +0800
layout: post
title: linux_2_28_useradd
tag: LinuxCommand
---
## 简介

+ userdata命令

## linux useradd命令 详解

`useradd`命令用于在Linux系统中创建新用户。它可以通过命令行提供一系列选项和参数来配置新用户的属性。以下是`useradd`命令的基本语法和一些常见选项：

### 基本语法：

```bash
useradd [选项] 用户名
```

### 常见选项：

1. **指定用户家目录：**
   ```bash
   useradd -m -d /home/newuser newuser
   ```
   - `-m`: 创建用户的家目录。
   - `-d`: 指定用户的家目录路径。

2. **指定用户ID（UID）：**
   ```bash
   useradd -u 1001 newuser
   ```
   - `-u`: 指定用户ID。

3. **指定初始登录Shell：**
   ```bash
   useradd -s /bin/bash newuser
   ```
   - `-s`: 指定初始登录Shell。

4. **指定用户组：**
   ```bash
   useradd -g users newuser
   ```
   - `-g`: 指定用户的主组。

5. **指定附加组：**
   ```bash
   useradd -G wheel,ftp newuser
   ```
   - `-G`: 指定用户的附加组。

6. **设置用户密码：**
   ```bash
   passwd newuser
   ```
   使用`passwd`命令为新用户设置密码。

7. **强制用户在首次登录时修改密码：**
   ```bash
   useradd -e 2023-01-31 newuser
   ```
   - `-e`: 指定过期日期。

8. **创建系统用户：**
   ```bash
   useradd -r sysuser
   ```
   - `-r`: 创建系统用户。

### 示例：

- 创建一个新用户并设置密码：
  ```bash
  useradd newuser
  passwd newuser
  ```

- 创建用户时指定用户ID、初始Shell和主组：
  ```bash
  useradd -u 1001 -s /bin/bash -g users newuser
  ```

- 创建系统用户：
  ```bash
  useradd -r sysuser
  ```

请注意，使用`useradd`仅会创建用户，如果你需要为新用户分配文件访问权限，可能还需要使用`chown`和`chmod`等命令。要了解更多选项和详细信息，可以查看`man useradd`。

## linux useradd命令 常用技巧

在使用`useradd`命令时，有一些常用的技巧和选项，可以帮助你更灵活地创建和管理用户。以下是一些常见的`useradd`命令技巧：

1. **一次性设置多个用户：**
   ```bash
   sudo useradd user1 user2 user3
   ```
   可以在一条命令中一次性创建多个用户。

2. **使用`-m`选项创建用户的家目录：**
   ```bash
   sudo useradd -m newuser
   ```
   `-m`选项将会为新用户创建一个家目录。

3. **指定用户ID（UID）：**
   ```bash
   sudo useradd -u 1001 newuser
   ```
   使用`-u`选项可以为用户指定特定的用户ID。

4. **指定用户组：**
   ```bash
   sudo useradd -g users newuser
   ```
   使用`-g`选项可以指定新用户的主组。

5. **添加用户到多个附加组：**
   ```bash
   sudo useradd -G wheel,ftp newuser
   ```
   使用`-G`选项可以为用户指定多个附加组。

6. **指定用户的登录Shell：**
   ```bash
   sudo useradd -s /bin/bash newuser
   ```
   使用`-s`选项可以为用户指定初始登录Shell。

7. **创建系统用户：**
   ```bash
   sudo useradd -r sysuser
   ```
   使用`-r`选项可以创建系统用户，这样系统用户将没有家目录，通常用于运行服务的用户。

8. **创建用户并设置过期日期：**
   ```bash
   sudo useradd -e 2023-01-31 newuser
   ```
   使用`-e`选项可以设置用户的过期日期，用户在首次登录时需要修改密码。

9. **创建用户时强制指定密码：**
   ```bash
   sudo useradd -p $(openssl passwd -crypt mypassword) newuser
   ```
   使用`-p`选项可以指定经过加密的密码。上例中使用`openssl passwd -crypt`生成加密的密码。

10. **禁用新用户的登录权限：**
    ```bash
    sudo useradd -M newuser
    ```
    使用`-M`选项可以创建用户，但不会为其创建家目录，也不会设置登录Shell，从而禁用其登录权限。

这些技巧可以帮助你更好地使用`useradd`命令，根据具体需求创建和管理用户。确保仔细查看`man useradd`以了解更多详细信息。

## useradd 

+ useradd, 用于建立用户账号
+ useradd可用来建立用户账号,账号建好之后,再用passwd设定账号的密码,用userdel删除账号,
+ 示例:
  + `useradd tt # 添加一般用户`
  + `useradd -g root tt  # 为添加的用户指定相应的用户组`
  + `useradd -r tt  # 创建一个系统用户`
  + `useradd -d /home/myd tt  # 为新添加的用户指定home目录`
  + `useradd caojh -u 544  # 建立用户并制定id`

在Linux中，`useradd`命令用于创建新用户账号。它是用于管理用户的基本命令之一。

以下是`useradd`命令的一般语法：

```
useradd [options] username
```

其中，`options`是可选的一些选项，`username`是要创建的新用户的用户名。

以下是一些常见的`useradd`命令选项和用法：

1. 创建新用户：
   ```
   useradd username
   ```

   此命令将创建一个新用户账号，并使用指定的用户名。

2. 指定用户ID（UID）：
   ```
   useradd -u uid username
   ```

   此命令将为新用户指定一个特定的用户ID（UID）。如果未指定，系统会自动分配一个唯一的UID。

3. 指定用户所属的初始组：
   ```
   useradd -g groupname username
   ```

   此命令将指定新用户所属的初始组。如果未指定，将使用与用户名相同的组。

4. 指定用户的主目录：
   ```
   useradd -d homedir username
   ```

   此命令将为新用户指定一个特定的主目录。如果未指定，系统将创建一个与用户名相同的目录。

5. 创建用户并指定登录Shell：
   ```
   useradd -s shell username
   ```

   此命令将为新用户指定一个特定的登录Shell。如果未指定，将使用系统默认的Shell。

`useradd`命令还支持其他一些选项，如设置用户的密码、指定用户的备注信息等。您可以使用`man useradd`命令查看完整的选项和用法说明。

请注意，使用`useradd`命令仅创建用户账号，不会自动创建密码或设置用户的权限和访问控制。您可能需要使用其他命令，如`passwd`和`usermod`，来设置密码和修改用户的属性。
