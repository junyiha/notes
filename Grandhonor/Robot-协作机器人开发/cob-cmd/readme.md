## 简介

+ cob-cmd，调试机械臂的命令
  + 通过curl工具发送HTTP请求，请求数据存放在JSON文件中
  + 通过wscat工具建立websocket连接

## 相机标定命令 详解

+ compile
  + ./tool.sh -c

+ recompile
  + ./tool.sh -re

+ run robot server
  + ./tool.sh -ds

+ 进入拖动示教模式：
  + ./cob-cmd.sh --drag-control ./open_drag.json

+ 退出拖动示教模式：
  + ./cob-cmd.sh --drag-control ./close_drag.json

+ 保存当前位姿(/home/user/Desktop/robot-status)
  + ./cob-cmd.sh --save-status

+ move to zero position
  + ./cob-cmd.sh --move-to ./joint_space.json