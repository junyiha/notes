## 简介

+ linux系统的常用技巧和方法

## 重启系统

在 `systemd` 下，可以使用 `systemctl` 命令来执行与重启系统相关的操作。以下是一些常用的 `systemctl` 命令及其说明：

1. `reboot`：用于重启系统。执行此命令会向系统发送重启信号，导致系统重新启动。
   ```
   sudo systemctl reboot
   ```

2. `poweroff`：用于关闭系统。执行此命令会向系统发送关闭信号，导致系统完全关闭。
   ```
   sudo systemctl poweroff
   ```

3. `halt`：用于停止系统。执行此命令会向系统发送停止信号，导致系统停止运行。
   ```
   sudo systemctl halt
   ```

4. `suspend`：用于挂起系统。执行此命令会将系统置于挂起状态，节省电源但保留系统状态。
   ```
   sudo systemctl suspend
   ```

5. `hibernate`：用于休眠系统。执行此命令会将系统置于休眠状态，将内存中的内容保存到磁盘，以便稍后恢复。
   ```
   sudo systemctl hibernate
   ```

需要注意的是，执行上述命令通常需要超级用户权限（使用 `sudo` 或以 `root` 用户身份运行）。

此外，还可以使用 `shutdown` 命令来执行系统重启操作，该命令提供了更多选项和参数以灵活控制系统的行为。