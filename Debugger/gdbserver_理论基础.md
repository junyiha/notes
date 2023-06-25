## 简介

+ gdbserver使用过程中遇到的理论知识

## gdbserver 常用 选项

GDBserver是一个用于远程调试的程序，它与GDB一起使用，允许你在目标系统上进行远程调试。以下是一些常用的GDBserver选项的详解：

1. `--multi`：启动GDBserver以支持多个GDB客户端连接。这允许多个调试器同时连接到同一个目标系统进行并行调试。

2. `--attach <pid>`：将GDBserver附加到指定进程的PID上进行调试。通过这个选项，你可以在目标系统上调试正在运行的进程。

3. `--once`：让GDBserver只调试一个进程，并在该进程退出后自动停止。这对于单次调试会话很有用。

4. `--remote-debug`：启用远程调试支持，允许GDB通过网络与GDBserver通信进行远程调试。通常与`--port`选项一起使用。

5. `--port <port>`：指定GDBserver监听的端口号，以便GDB通过网络连接到GDBserver进行远程调试。

6. `--attach-command <command>`：在附加到进程时执行指定的GDB命令。这对于在附加时自动执行特定的调试命令非常有用。

7. `--wrapper <wrapper>`：在启动目标程序之前运行指定的包装器程序。这对于在目标系统上执行额外的初始化步骤或设置环境变量非常有用。

8. `--localhost`：GDBserver仅允许本地主机连接。这可以增加调试的安全性，限制远程访问。

9. `--persistent`：使GDBserver保持持久运行，即使GDB客户端断开连接或退出。这样，当GDB客户端重新连接时，调试会话可以继续。

10. `--separate`：将每个连接的GDB客户端隔离开，使它们无法相互干扰。这在并行调试多个目标时很有用。

这些选项只是GDBserver的一部分，还有其他选项可供使用。你可以参考GDBserver的文档或运行`gdbserver --help`命令获取完整的选项列表和详细说明。GDBserver是一个强大的工具，可用于在目标系统上进行远程调试，帮助你调试和分析嵌入式系统或其他远程目标。