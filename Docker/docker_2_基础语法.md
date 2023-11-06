## 简介

+ docker基础语法

## docker inspect 详解

`docker inspect` 命令用于查看 Docker 中的各种对象的详细信息，包括容器、镜像、网络、卷等。这个命令以 JSON 格式输出对象的配置和状态信息，可用于调试、监视和了解 Docker 对象的各个方面。下面是有关 `docker inspect` 命令的详细解释：

语法：
```bash
docker inspect [OPTIONS] OBJECT [OBJECT...]
```

- `OPTIONS`：可选，可以附加一些选项来控制输出格式和内容。
- `OBJECT`：必需，指定要检查的 Docker 对象的名称或 ID。

以下是一些常见的用法和选项：

1. 查看容器详细信息：

   ```bash
   docker inspect container_name_or_id
   ```

   这将输出指定容器的详细信息，包括容器的配置、状态、网络设置等等。

2. 查看镜像详细信息：

   ```bash
   docker inspect image_name_or_id
   ```

   这将输出指定镜像的详细信息，包括镜像的元数据、层信息等。

3. 输出格式选项：

   默认情况下，`docker inspect` 输出 JSON 格式的信息，但你可以使用 `--format` 选项来指定自定义输出格式。例如：

   ```bash
   docker inspect --format '{{.State.Status}}' container_name_or_id
   ```

   这将仅输出容器的状态（运行、停止等）。

4. 查看多个对象的信息：

   你可以一次查看多个 Docker 对象的信息。例如，要查看多个容器的详细信息，可以列出它们的名称或 ID 并用空格分隔：

   ```bash
   docker inspect container1 container2
   ```

5. 使用 `--type` 选项过滤对象类型：

   你可以使用 `--type` 选项来过滤要检查的 Docker 对象的类型。例如，要查看所有网络的详细信息，可以运行：

   ```bash
   docker inspect --type network
   ```

   这将列出所有网络的详细信息。

6. 导出信息到文件：

   如果你想将对象的详细信息保存到文件中，可以使用重定向操作符（`>`）将输出重定向到文件。例如：

   ```bash
   docker inspect container_name_or_id > container_info.json
   ```

   这将容器的详细信息保存到 `container_info.json` 文件中。

`docker inspect` 命令是一个非常有用的工具，可用于深入了解 Docker 对象的各个方面，从容器的配置到网络设置，以及镜像的元数据等等。通过查看这些信息，你可以更好地理解和管理你的 Docker 环境。

## docker --network(net) 详解

在 Docker 中，网络是容器和其他容器或宿主机之间进行通信的基础。Docker 提供了多种网络模式和选项，可以根据不同的需求选择适当的网络配置。以下是 Docker 中一些常见的网络选项：

1. `--network`：这是一个全局选项，用于指定容器所属的网络。可以通过以下几种预定义的网络进行选择：

   - `bridge`：默认网络模式，Docker 在主机上创建一个名为 `bridge` 的虚拟网络，容器将连接到该网络，容器可以通过它与宿主机和其他容器通信。

   - `host`：使用宿主机的网络命名空间，容器与宿主机共享网络栈，与宿主机拥有相同的网络接口和IP地址。适用于需要容器与宿主机共享网络的场景。

   - `none`：不使用任何网络，容器将没有网络接口，只适用于特殊情况。

   - `container:<name|id>`：使容器与指定名称或ID的另一个容器共享网络命名空间，从而实现容器之间的网络通信。

   - 自定义网络：可以使用 `docker network create` 命令创建自定义网络，并将容器连接到该网络。

2. `--publish` 或 `-p`：这个选项用于将容器内部的端口映射到宿主机上，允许外部主机通过宿主机的IP和端口访问容器内部的服务。

   例如：`docker run -p 8080:80 nginx` 将容器内部的80端口映射到宿主机的8080端口。

3. `--expose`：用于将容器内部的端口暴露给与容器连接的其他容器，但不映射到宿主机。这只是一种文档工具，实际上并不会进行端口映射。

4. `--link`：已经过时，不推荐使用。用于在容器之间创建链接，允许容器使用对方的环境变量进行通信。

5. `--hostname`：指定容器的主机名。

这些选项可以通过 `docker run` 命令进行设置，例如：

```
docker run --network=bridge -p 8080:80 --name my_container nginx
```

上述命令将创建一个名为 `my_container` 的容器，连接到默认的 `bridge` 网络，并将容器内部的80端口映射到宿主机的8080端口，让外部可以通过宿主机的IP和端口访问容器内的NGINX服务。

请注意，Docker 的网络功能在不同版本之间可能会有一些变化，建议查阅最新的 Docker 文档以获得最准确的信息。

## docker compose 

Docker Compose 是一个用于定义和管理多容器应用程序的工具，它使用一个单独的 YAML 文件来配置应用程序的服务、网络和卷等。

以下是一些常用的 Docker Compose 命令及其功能：

1. 启动和停止容器组：
   - 启动容器组：`docker-compose up` 或 `docker-compose start` 命令可以启动 Docker Compose 配置文件中定义的所有服务和容器。
   - 停止容器组：`docker-compose stop` 命令可以停止 Docker Compose 配置文件中定义的所有服务和容器。

2. 构建和重建容器：
   - 构建容器：`docker-compose build` 命令可以根据 Docker Compose 配置文件中的定义，构建容器的镜像。
   - 重建容器：`docker-compose up --build` 命令可以重建所有容器的镜像，并重新启动容器组。

3. 查看容器组状态：
   - 查看容器组状态：`docker-compose ps` 命令可以列出 Docker Compose 配置文件中定义的所有服务和容器的状态信息。

4. 执行命令：
   - 在容器内执行命令：`docker-compose exec <service> <command>` 命令可以在指定的服务容器内执行命令。

5. 清理容器和资源：
   - 删除容器：`docker-compose rm` 命令可以删除停止的容器。
   - 清理资源：`docker-compose down` 命令可以停止并删除所有容器、网络和卷。

6. 查看日志：
   - 查看容器日志：`docker-compose logs` 命令可以查看 Docker Compose 配置文件中定义的所有服务和容器的日志。

这些是一些常见的 Docker Compose 命令及其功能。你可以根据需要使用这些命令来管理和操作 Docker Compose 配置文件中定义的容器组。

请注意，在使用 Docker Compose 命令之前，确保已经安装了 Docker Compose 工具，并在当前工作目录下存在正确的 Docker Compose 配置文件。

---

## docker save

+ 简介：
  + docker save 命令用于将 Docker 镜像保存为一个 tar 归档文件。这个归档文件可以方便地传输、备份或在其他 Docker 主机上加载和使用

+ 语法：
```bash
docker save [OPTIONS] IMAGE [IMAGE...]
```

+ 参数：
  + OPTIONS：可选参数，用于指定额外的选项，如压缩级别等。
  + IMAGE：要保存为归档文件的 Docker 镜像名称或镜像 ID

+ 示例：
```bash
docker save -o myimage.tar myimage:latest
```

+ 注：
  + 上述示例将名为 myimage:latest 的 Docker 镜像保存为 myimage.tar 归档文件。
  + 要了解更多关于 docker save 命令的详细信息，你可以使用 docker save --help 查看帮助文档
  + 使用 docker save 命令保存的归档文件可以使用 docker load 命令进行加载和导入。这样可以在其他 Docker 主机上使用相同的镜像，或者进行备份和共享镜像

## docker system

`docker system` 命令用于管理和查看 Docker 系统资源的相关信息。它提供了一组子命令，可以用于获取关于 Docker 守护进程（Docker daemon）的状态、清理无用资源以及查看 Docker 系统的使用情况。下面是对 `docker system` 命令的一些常用子命令的详细解释：

1. **`docker system df`**：显示 Docker 系统的磁盘使用情况，包括镜像、容器和卷的使用情况。

2. **`docker system events`**：实时显示 Docker 系统的事件流，包括容器的创建、启动、停止、删除等事件。

3. **`docker system info`**：显示 Docker 系统的详细信息，包括容器、镜像、存储驱动、内核版本等。

4. **`docker system prune`**：清理无用的 Docker 资源，包括未使用的镜像、停止的容器、未使用的网络等。

5. **`docker system resize`**：调整 Docker 容器终端的大小。

这只是 `docker system` 命令的一些常见用法。你可以通过运行 `docker system --help` 或 `docker system <子命令> --help` 查看完整的帮助文档，以了解更多关于各个子命令的详细信息和使用方式。

请注意，`docker system` 命令需要在具有足够权限的环境中执行，例如在管理员或超级用户模式下执行。

## docker system prune

`docker system prune` 命令用于清理无用的 Docker 资源，以释放磁盘空间。它会删除未使用的镜像、停止的容器、未使用的网络和未被任何容器引用的卷。这可以帮助你清理系统中的不必要资源，以避免占用过多的磁盘空间。

用法：
```bash
docker system prune [OPTIONS]
```

参数：
- `OPTIONS`：可选参数，用于指定额外的选项。常见的选项包括：
  - `-a, --all`：清理所有未使用的资源，包括未使用的镜像、容器、网络和卷。
  - `-f, --force`：强制执行清理操作，不需要用户进行确认。
  - `--filter <FILTER>`：按照指定的条件过滤要清理的资源。
  - `-v, --volumes`：同时清理未被容器引用的卷。

示例：
```bash
docker system prune -a
```

上述示例将清理所有未使用的 Docker 资源，包括未使用的镜像、停止的容器、未使用的网络和未被任何容器引用的卷。

请注意，清理操作是不可逆的，一旦执行将无法恢复被删除的资源。在执行 `docker system prune` 命令之前，请确保你了解将要删除的资源，并确认没有重要的数据会被删除。

使用 `docker system prune` 命令可以帮助你管理 Docker 系统资源，提供更高效和规整的环境。

<!-- + 语法：`docker system prune [options]`
+ 作用：清除缓存
+ `[options]`
  - `-all, -a` : 删除所有未使用的镜像，不只是闲置的。(Remove all unused images not just dangling ones)
  - `--filter` : 提供数值过滤，例如：`label=<key>=<value>`。(Provide filter values)
  - `--force, -f` : 不提示确认。(Do not prompt for confirmation)
  - `--volumes` : 清除卷。(Prune volumes)

+ `docker system prune --volumes`
+ 该命令清除：
  - 所有停止的容器
  - 所有不被任何一个容器使用的网络
  - 所有不被任何一个容器使用的volume
  - 所有无实例的镜像 -->

## docker system df

`docker system df` 命令用于显示 Docker 系统的磁盘使用情况，包括镜像、容器和卷的使用情况。它可以帮助你了解 Docker 系统在磁盘上占用的空间，以便更好地管理和优化资源。

用法：
```bash
docker system df [OPTIONS]
```

参数：
- `OPTIONS`：可选参数，用于指定额外的选项。常见的选项包括：
  - `--no-trunc`：不截断输出的镜像和容器名称。
  - `-v, --volumes`：同时显示卷的使用情况。

示例：
```bash
docker system df
```

上述示例将显示 Docker 系统的磁盘使用情况，包括镜像、容器和卷的使用情况。

输出内容包括以下几个部分：
- `IMAGE TYPE`：镜像类型（例如，镜像、容器或卷）。
- `TOTAL`：总大小。
- `USED`：已使用的大小。
- `SHARED`：共享的大小。
- `CACHE`：缓存的大小。
- `RECLAIMABLE`：可回收的大小。
- `PARENT`：父镜像的 ID。
- `TAG`：镜像的标签或容器的名称。
- `VIRTUAL SIZE`：虚拟大小。

使用 `docker system df` 命令可以方便地查看 Docker 系统的磁盘使用情况，帮助你了解镜像和容器占用的空间。这有助于进行资源管理和优化，以确保磁盘空间得到合理利用。

<!-- + 语法：`docker system df [options]`
+ 作用：显示docker磁盘的使用情况(show docker disk usage)
+ `options` :
  - `--format` : 使用go模板打印更好的图像
  - `--verbose, -v` : 显示空间使用的详细信息 -->

## docker system info

`docker system info` 命令用于显示 Docker 系统的详细信息，包括容器、镜像、存储驱动、内核版本等。它提供了有关 Docker 守护进程（Docker daemon）和运行环境的相关信息。

用法：
```bash
docker system info
```

示例输出：
```
Client:
 Context:    default
 Debug Mode: false
 Plugins:
  app: Docker App (Docker Inc., v0.9.1-beta3)
  buildx: Build with BuildKit (Docker Inc., v0.5.1-docker)

Server:
 Containers: 3
  Running: 2
  Paused: 0
  Stopped: 1
 Images: 15
 Server Version: 20.10.6
 Storage Driver: overlay2
  Backing Filesystem: extfs
  Supports d_type: true
 ...
```

输出内容包括以下几个部分：
- `Client`：客户端相关信息，如上下文和调试模式。
- `Plugins`：安装的插件列表。
- `Server`：Docker 守护进程相关信息，如容器数量、镜像数量、服务器版本等。
- `Storage Driver`：存储驱动信息，如使用的驱动类型、底层文件系统等。
- 其他相关信息，如操作系统类型、内核版本等。

通过运行 `docker system info` 命令，你可以获得有关 Docker 系统的详细信息，帮助你了解 Docker 运行环境和配置。这对于故障排查、性能优化和了解 Docker 系统的状态非常有用。

<!-- + 语法：`docker system info [options]`
+ 作用：显示全部系统的信息
+ `[options]`:
  - `--format, -f` : 以指定的go模板格式化输出 -->

## docker stats

`docker stats` 命令用于实时监视 Docker 容器的资源使用情况，包括 CPU 使用率、内存使用量、网络 I/O 等。它提供了一个实时的流式输出，可以帮助你了解正在运行的容器的性能和资源消耗情况。

用法：
```bash
docker stats [OPTIONS] [CONTAINER...]
```

参数：
- `OPTIONS`：可选参数，用于指定额外的选项。常见的选项包括：
  - `--all, -a`：显示所有的容器（包括停止的容器）。
  - `--format`：自定义输出格式。
  - `--no-stream`：只显示一次统计结果，然后退出。
  - `--no-trunc`：不截断输出的容器名称。
- `CONTAINER`：要监视的容器名称或容器 ID。如果不指定容器，则会监视所有正在运行的容器。

示例：
```bash
docker stats container1 container2
```

上述示例将实时监视名为 `container1` 和 `container2` 的容器的资源使用情况。

输出内容包括以下几个部分：
- `CONTAINER ID`：容器的 ID。
- `NAME`：容器的名称。
- `CPU %`：CPU 使用率。
- `MEM USAGE / LIMIT`：内存使用量和限制。
- `MEM %`：内存使用率。
- `NET I/O`：网络输入/输出。
- `BLOCK I/O`：块设备输入/输出。
- `PIDS`：进程 ID 数量。

使用 `docker stats` 命令可以实时监视 Docker 容器的资源使用情况，帮助你了解容器的性能和资源消耗情况。这对于监控和优化容器的运行非常有用。请注意，`docker stats` 命令会持续输出监视结果，可以通过 Ctrl+C 终止命令的执行。

<!-- + 显示容器资源的使用情况，包括：CPU，内存，网络I/O等
+ 语法：`docker stats [options] [container...]`
+ `[options]`:
  - `-all, -a` : 显示所有的容器，包括未运行的
  - `--format` : 指定返回值的模板文件
  - `-no-stream` : 展示当前状态就直接退出了，不再实时更新
  - `--no-trunc` : 不截断输出
+ 输出详情：
  - `CONTAINER ID` ， `NAME` : 容器ID，名称
  - `CPU%, MEM%` : 容器使用的CPU和内存的百分比
  - `MEM USAGE/LIMIT` : 容器正在使用的总内存，以及允许使用的内存总量
  - `NET I/O` : 容器通过其网络接口发送和接受的数据量
  - `BLOCK I/O` : 容器从主机上的块设备读取和写入的数据量
  - `PIDs` : 容器创建的进程或线程数 -->

## docker history

`docker history` 命令用于查看 Docker 镜像的历史记录，包括每个镜像层的创建步骤和相关信息。它可以帮助你了解镜像是如何构建的，每个镜像层的来源和变更，以及各个镜像层的大小。

用法：
```bash
docker history [OPTIONS] IMAGE
```

参数：
- `OPTIONS`：可选参数，用于指定额外的选项。常见的选项包括：
  - `--no-trunc`：显示完整的命令信息，不截断输出。
  - `--quiet, -q`：仅显示镜像层的 ID。

示例：
```bash
docker history myimage:latest
```

上述示例将显示名为 `myimage:latest` 的 Docker 镜像的历史记录。

输出内容包括以下几个部分：
- `IMAGE ID`：镜像层的 ID。
- `CREATED`：镜像层的创建时间。
- `CREATED BY`：创建镜像层的命令或操作。
- `SIZE`：镜像层的大小。

`docker history` 命令按照镜像层的构建顺序列出了镜像的历史记录。每个镜像层都代表一个变更，它可以是一个 Dockerfile 中的一条指令或者基于其他镜像层的修改。通过查看镜像的历史记录，你可以了解镜像是如何构建的，每个步骤的细节和影响，以及镜像层的大小情况。

请注意，镜像历史记录中的每一行都会添加一个新的镜像层，并且每个镜像层都会占用磁盘空间。因此，构建过多的镜像层可能会增加镜像的大小和磁盘消耗。

<!-- + 语法：`docker history [options] IMAGE`
+ 作用：显示一个镜像的历史
+ `[options]`:
  - `--format` : 使用go模板输出
  - `--human, -H` : 以人习惯的阅读方式输出
  - `--no-trunc` : 不截断输出
  - `--quiet, -q` : 仅显示镜像IDs -->

## docker kill

`docker kill` 命令用于强制停止正在运行的 Docker 容器。它发送一个 SIGKILL 信号给容器的主进程，使容器立即停止运行，类似于使用 `kill -9` 命令终止进程。

用法：
```bash
docker kill [OPTIONS] CONTAINER [CONTAINER...]
```

参数：
- `OPTIONS`：可选参数，用于指定额外的选项。常见的选项包括：
  - `-s, --signal`：指定要发送的信号。默认为 SIGKILL。
- `CONTAINER`：要停止的容器名称或容器 ID。

示例：
```bash
docker kill mycontainer
```

上述示例将停止名为 `mycontainer` 的 Docker 容器。

注意事项：
- 使用 `docker kill` 命令会立即停止容器，不会触发容器的停止信号或执行容器的停止脚本。
- 如果你希望优雅地停止容器并触发容器的停止信号和脚本，可以使用 `docker stop` 命令。
- 使用 `docker kill` 命令强制停止容器可能导致数据丢失或不正常的容器状态，请谨慎使用。

`docker kill` 命令用于强制停止正在运行的容器，对于无法通过正常方式停止的容器，这是一种有效的方法。然而，它不是优雅停止容器的首选方法，因为容器没有机会进行清理操作。建议在必要时使用，并确保了解可能的副作用。

<!-- + 语法：`docker kill [options] container [container...]`
+ 作用：杀死一个或者多个正在运行的容器
+ `[options]`
  - `--signal, -s` : 发送到容器的信号。(Signal to send to the container)
  - `SIGHUB` , 信号，网络编程 -->

## docker pause

`docker pause` 命令用于暂停正在运行的 Docker 容器。它会暂停容器内所有的进程，使其停止在当前状态，直到恢复为止。暂停后的容器不会消耗 CPU 资源，但内存和磁盘资源仍然保留。

用法：
```bash
docker pause CONTAINER [CONTAINER...]
```

参数：
- `CONTAINER`：要暂停的容器名称或容器 ID。

示例：
```bash
docker pause mycontainer
```

上述示例将暂停名为 `mycontainer` 的 Docker 容器。

注意事项：
- 暂停容器会暂停容器内的所有进程，包括正在运行的和后台运行的。
- 暂停后的容器可以使用 `docker unpause` 命令来恢复运行。
- 暂停容器并不会影响容器的网络连接，因此容器仍然可以接收网络流量。
- 只有在支持容器暂停功能的操作系统上才能使用 `docker pause` 命令。

使用 `docker pause` 命令可以方便地暂停正在运行的容器，以便进行调试、维护或其他需要容器暂停的操作。请确保在使用此命令之前了解其影响，并谨慎操作以避免不必要的问题。
<!-- + 语法：`docker pause container [container...]`
+ 作用：暂停一个或多个容器中的所有进程 -->

## docker unpause

`docker unpause` 命令用于恢复被暂停的 Docker 容器。它会使之前被暂停的容器继续运行，并恢复容器内的所有进程的执行。

用法：
```bash
docker unpause CONTAINER [CONTAINER...]
```

参数：
- `CONTAINER`：要恢复的容器名称或容器 ID。

示例：
```bash
docker unpause mycontainer
```

上述示例将恢复名为 `mycontainer` 的 Docker 容器。

注意事项：
- 只有被暂停的容器才能使用 `docker unpause` 命令进行恢复。
- 恢复容器后，之前被暂停的进程会继续执行。
- 容器的网络连接不会受到 `docker unpause` 命令的影响。

使用 `docker unpause` 命令可以恢复之前被暂停的容器，使其继续运行。这对于从暂停状态中恢复容器非常有用，例如在进行调试或维护操作后重新启动容器。请注意，只能对已暂停的容器执行 `docker unpause` 命令。

<!-- + 语法：`docker unpause container [container...]`
+ 作用：不暂停一个或多个容器中的所有进程 -->

## docker rename

`docker rename` 命令用于为 Docker 容器重命名。它可以修改容器的名称标识符，使其更符合你的需求或命名约定。

用法：
```bash
docker rename CONTAINER NEW_NAME
```

参数：
- `CONTAINER`：要重命名的容器名称或容器 ID。
- `NEW_NAME`：新的容器名称。

示例：
```bash
docker rename mycontainer newname
```

上述示例将名为 `mycontainer` 的 Docker 容器重命名为 `newname`。

注意事项：
- 重命名容器只会修改容器的名称标识符，不会对容器内的运行进程或状态造成影响。
- 容器的新名称必须是唯一的，不得与现有容器名称重复。

使用 `docker rename` 命令可以轻松地为 Docker 容器重新命名，以便更好地管理容器或与命名约定保持一致。请记住，在容器被重命名后，你需要使用新的名称来执行其他容器相关的操作。

<!-- + 语法：`docker rename container new_name`
+ 作用：重命名一个容器 -->

## builder

+ manage builds

### build

+ 命令：`docker builder build [OPTIONS] PATH | URL | -`
+ 简介：从Dockerfile创建一个镜像
+ 选项：
  + `--add-host` : 添加一个自定义的主机到IP的映射（host:ip）
  + `--build-arg` : 设置构建时的变量
  + `--cache-from` : 考虑作为缓存来源的镜像
  + `--cgroup-parent` : 容器的可选父级c组
  + `--compress` : 使用gzip压缩构建环境
  + `--cpu-period`
  + `--cpu-quota`
  + `--cpu-shares,-c`
  + `--cpuset-cpus`
  + `--cpuset-mems`
  + `--disable-content-true` : 跳过镜像验证，默认为true
  + `--file,-f` : Dockerfile的名称，默认为PATH/Dockerfile
  + `--force-rm` : 始终移除中间的容器
  + `--iidfile` : 将镜像的ID写入到文件中
  + `--isolation` : 容器隔离技术
  + `--label` : 设置镜像的元数据
  + `--memory,-m` : 内存限制
  + `--memory-swap` : 交换限制等于内存加交换：-1表示启用无限制交换。
  + `--network` : 在构建过程中为RUN指令设置网络模式
  + `--no-cache` : 在构建镜像的时候不要使用缓存
  + `--platform` : 如果服务器是多平台的，则设置平台
  + `--pull` : 始终尝试拉取一个较新版本的镜像
  + `--quiet,-q` : 过滤构建镜像的输出，仅在成功时输出镜像的ID
  + `--rm` : 构建成功后删除中间容器
  + `--security-opt` : 安全选项
  + `--shm-size` : /dev/shm的大小
  + `--squash` : 将新建的层压成一个新的层
  + `--tag,-t` : 名称和可选的标签，格式为name:tag
  + `--target` : 设置目标构建阶段为构建。
  + `--ulimit` : 限定选项

## run

+ 命令：`docker run [OPTIONS] IMAGE [COMMAND] [ARG...]`
+ 简介：docker run命令首先在指定的镜像上创建一个可写的容器层，然后用指定的命令启动它。也就是说，docker run相当于API中的/containers/create然后/containers/(id)/start。一个停止的容器可以用docker start来重新启动，其之前的所有变化都是完整的。
+ 选项：
  + `--add-host` : 添加一个自定义的主机到IP的映射（host:ip）
  + `--attach,-a` : 附加到STDIN、STDOUT或STDERR上
  + `--blkio-weight` : 区块IO（相对权重），在10和1000之间，或0表示禁用（默认为0）。
  + `--blkio-weight-device` : 块状IO重量（相对设备重量）
  + `--cap-add` : 	增加Linux功能
  + `--cap-drop` : 	降低Linux的能力
  + `--cgroup-parent` : 容器的可选父级c组
  + `--cgroupns`
  + `--cidfile` : 将容器ID写到文件中
  + `--cpu-count` : CPU计数，仅支持Windows
  + `--cpu-percent` : 
  + `--cpu-period` 
  + `--cpu-quota`
  + `--cpu-rt-period`
  + `--cpu-rt-runtime`
  + `--cpu-shared,-c`
  + `--cpus` : cpu的数量
  + `--cpuset-cpus`
  + `--cpuset-mems`
  + `--detach,-d` : 在后台运行容器并打印容器ID
  + `--detach-keys` : 覆盖脱离容器的按键顺序
  + `--device` : 在容器中添加一个主机设备
  + `--device-cgroup-rule` : 在cgroup允许的设备列表中添加一条规则
  + `--device-read-bps` : 限制从一个设备上的读取速率（每秒字节数）。
  + `--device-read-iops` : 限制从一个设备的读取率（每秒的IO）。
  + `--device-write-bps`
  + `--device-write-iops`
  + `--disable-content-trust` : 跳过镜像验证，默认为true
  + `--dns` : 设置自定义的DNS服务器
  + `--dns-option` : 设置DNS选项
  + `--dns-search` : 设置自定义DNS搜索域
  + `--domainname` : 容器NIS域名
  + `--entrypoint` : 覆盖镜像的默认ENTRYPOINT
  + `--env,-e` : 设置环境变量
  + `--env-file` : 读取环境变量的文件
  + `--expose` : 暴露一个端口或一系列的端口
  + `--gpus` : 要添加到容器中的GPU设备（'全部'用于传递所有GPU）。
  + `--group-add`
  + `--health-cmd` : 运行命令以检查健康状况
  + `--health-interval` : 运行检查的间隔时间（ms|s|m|h）（默认为0s）。
  + `--health-retries`
  + `--health-start-period`
  + `--health-timeout`
  + `--help` : 输出帮助信息
  + `--hostname,-h` : 容器主机名称
  + `--init` : 在容器内运行一个init，转发信号并收割进程
  + `--interactive,-i` : 保持STDIN开放，即使没有连接
  + `--io-maxbandwidth` : 系统驱动器的最大IO带宽限制（仅Windows）。
  + `--io-maxiops` : 系统驱动器的最大IOps限制（仅Windows）。

## 常用命令

## `docker images, docker image ls`

+ 列出本地主机上的镜像
  - `repository` : 表示镜像的仓库源
  - `tag` : 镜像的标签
  - `image id` : 镜像id
  - `created` : 镜像创建时间
  - `size` : 镜像大小
  
## `docker rmi helloworld`

+ 删除镜像
  
## `docker run -it ubuntu /bin/bash`

+ 使用ubuntu镜像启动一个容器,参数为以命令模式进入该容器
  - `-i` : 交互操作
  - `-t` : 终端
  - `ubuntu` : ubuntu镜像
  - `/bin/bash` : 放在镜像名后的是命令,这里是希望有个交互式shell
  
## `docker run -itd --name ubuntu-test ubuntu /bin/bash`

+ 后台运行容器
  - `-d` : 默认不会进入容器,想要进入容器需要使用指令`docker exec`

## `docker ps`

+ 语法：`docker ps [options]`
+ 作用：列出容器
+ `[options]`
  - `--all, -a` : 显示所有容器(默认仅显示正在运行的)。(Show all containers(default shows just running))
  - `--filter, -f` : 基于指定的条件过滤输出信息。(Filter output based on conditions provided)
  - `--format` : 使用go模板输出
  - `--last, -n` : 显示n个最后创建的容器。(Show n last created containers(includes all states))
  - `--no-trunc` : 不截断输出。(Don't truncate output)
  - `--quiet, -q` : 仅显示容器ID。(Only display container IDs)
  - `--size, -s` : 显示总文件大小。(Display total file sizes)
  
## `docker start id`

+ 启动一个已停止的容器
  
## `docker stop`

+ 语法：`docker stop [options] container [container...]`
+ 作用：停止一个容器
+ `[options]`:
  - `--time, -t` : 在杀死容器之前等待停止的时间，默认为10秒
  
## `docker restart id`

+ 重启一个容器

## docker attach, docker exec

+ 进入容器:在使用`-d`参数时,容器启动后会进入后台,此时想要进入容器,通过以下指令:
  - docker attach: `docker attach id`
  - docker exec:推荐使用此命令,因为使用它退出容器终端,但是不会导致容器的停止,`docker exec -it id /bin/bash`

## docker export, docker import, docker commit

## docker export

+ `docker export`命令不会导出与容器关联的卷的内容。如果卷安装在容器中现有目录的顶部，则`docker export`将导出底层目录的内容，而不是卷的内容
+ 功能：将容器的文件系统导出为tar存档
+ `docker export 容器id > 容器名称.tar , docker export 容器id --output 容器名称.tar`
  - 导出本地某个容器到tar包
+ 参数
  - `--output, -o` : 写入一个文件，而不是`stdout`

## docker import

+ 语法：`docker import [options] file|URL|- [REPOSITORY[:TAG]]`
+ 作用：从一个tar包导入文件数据并创建一个文件系统镜像
+ `[options]` :
  - `--change, -c` : 应用于创建镜像的dockerfile 指示
  - `--message, -m` : 为导入的镜像设置提交信息
+ `cat docker/ubuntu.tar | docker import - test/ubuntu:v1`
  - 通过管道和标准输入的方式导入容器快照

## docker load

+ 导入镜像文件：`docker load --input imagePath`

## docker commit

+ 更新镜像:通过命令`docker commit`来提交容器副本,Warning:使用此命令保存镜像，会以层的概念保存，每一次保存都会增加一层，镜像会越来越大
  + 示例:`docker commit -m="has update" -a="runoob" e218edb10161 runoob/ubuntu:v2`
  + 参数说明:
    - `-m`:提交的描述信息
    - `-a`:指定镜像作者
    - `e218edb10161` : 容器ID
    - `runoob/ubuntu:v2` : 指定要创建的目标镜像名
  
## docker tag

+ 修改镜像标签:`docker tag image-id name:tag`
