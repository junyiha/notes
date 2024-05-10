## 简介

+ VCR 说明文档

## 机械臂服务

+ host ip : 192.169.7.32 
+ user name : root
+ password : 111111

+ 启动服务:
```bash 
cd /home/user/zjy/cob_github/beijing-main-beta/web_backend/

./tool.sh -ds
```

## vcr 服务

+ host ip : 192.169.0.152
+ user name : root
+ password : 111111

+ 启动服务:
```bash 
source /home/user/vcr_release/20230921/source.sh 

cd /home/user/vcr_release/20230921/6.2/VideoProcess/bin/

./vcr.exe
```

+ 服务端口：
  + 192.169.0.152:28000

+ 配置文件
  + 默认配置文件路径:/home/user/workspace/video_process/build/model_config.json