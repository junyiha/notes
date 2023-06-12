## 简介

+ shell脚本编程的常用方法

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