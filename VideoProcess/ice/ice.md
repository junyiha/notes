## 加载人脸库

+ `./ice.exe --client --cmd 1 --id 2 --model-conf-path http://192.169.4.113:8084/ --detector-conf @--detect-model@models/Face_BITMAINLAND/DETECT.conf@--feature-model@models/Face_BITMAINLAND/FEATURE.conf@ --comparison-list http://192.169.4.113:8084/platform/images/recognize/研发中心/20221214211140.txt`

+ `./ice.exe --client --cmd 1 --id 2 --model-conf-path http://192.169.4.113:8084/ --detector-conf @--detect-model@models/Face_NVIDIA_1080/DETECT.conf@--feature-model@models/Face_NVIDIA_1080/FEATURE.conf@ --comparison-list http://192.169.4.113:8084/platform/images/recognize/研发中心/20221214211140.txt`

## 人脸识别

+ `FEATURE.conf`文件中的参数: `--feature-metric`必须设置为1，也就是设定输出的分数为相似度
+ `ice.exe`的参数`--feature-metric`默认为1，将模型输出的数值，乘以100

+ 模型，必须先加载人脸检测模型`DETECT.conf`，然后是特征提取模型`FEATURE.conf`