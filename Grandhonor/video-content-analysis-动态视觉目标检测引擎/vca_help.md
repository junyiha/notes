vca.exe 版本 6.1.2

一般选项：

	--help
		打印这些信息。

	--version
		打印版本信息。

日志选项：

	--log-verbose
		记录详细日志。默认：记录重要日志

模型选项：

	--file < FILE >
		模型文件。

	例：model
	例：abc/model
	例：/abc/model
	例：http://abc/model
	例：https://abc/model

	--type < TYPE >
		模型类型。

		YOLOv3
		YOLOv4
		YOLOv5
		YOLOv5_6
		YOLOv4_NVIDIA_DeepStream
		SoftFPN_LP
		SoftFPN_S
		SoftFPN_T
		SoftFPN_U
		SoftFPN_X
		SoftFPN_W
		SoftFPN_L
		CenterNet
		CenterNet_MCOD
		RetinaFace
		RetinaFace_BITMAINLAND
		LPRNET_0312
		LPRNET
		Feature
		Feature_MobileNet_InsightFace
		Sort_GroupBy
		Sort_Bloom

	--sort-group-by < CLASS,OFFSET-B,OFFSET-E [ CLASS,OFFSET-B,OFFSET-E ... ]>
		按组分类。Sort_GroupBy有效。

	--yolo-output-tensor-name < SMALL MEDIUM LARGE >
		指定YOLO输出层名字(升序)。YOLOv3,YOLOv4,YOLOv5有效。

	--yolov5-output-tensor-4d
		YOLOv5输出是4维的。

	--yolov5-output-tensor-fmt < FORMAT >
 		YOLOv5输出层数据格式。默认：2

		2：HWC
		1：CHW

	--centernet-output-tensor-name < REG HW HM HM-MAX >
		指定centernet输出层名字。

	--disable-sigmoid
		禁用归一化。

	--label-normalize < 标签原值,标准值[,标准值,...] [ 标签原值,标准值[,标准值,...] ... ] >
		使标签值标准化。注：输出时会自动删除未能标准化的标签。

	--feature-normalize-l2
		特征标准化。

	--feature-output-name < NAME >
		指定Feature输出层名字。

	--feature-metric < TYPE >
		指定Feature度量类型。默认：1

		0：相似度
		1：欧式距离

	--input-scalar < channel-0,channel-1,channel-2 >
		输入层数据（乘）系数。默认：0.0039215,0.0039215,0.0039215

	--input-mean < channel-0,channel-1,channel-2 >
		输入层数据（减）均值。默认：0,0,0

	--input-std < channel-0,channel-1,channel-2 >
		输入层数据（除）方差。默认：1.0,1.0,1.0

	--delete-oblique-face
		删除侧脸。

任务选项：

	--id < ID >
		任务ID。

	--detector-conf-inline
		启用检测器内联配置。默认：停用

	--detector-conf-delim < CHAR >
		检测器内联配置分割符。默认：@

	--detector-conf < ARGS [ARGS ...] >
		检测器配置，支持多个配置。
		注1：启用内联配置时，ARGS是配置参数序列化后的字符串，由分割符切分键和值。
		注2：停用内联配置时，ARGS是配置文件，文件中的key和value分行输入，当行首字符为#时，忽略此行。

		--detector-id < ID >
			检测器ID。默认：随机

		--detector-type < NUMBER >
			检测器类型。默认：1

			1：一般检测。
				检测模型 特征模型 分类模型 OCR模型
			2：车辆检测。
				车辆检测模型 车辆特征模型 车辆分类模型 车牌检测模型 车牌OCR模型
			3：嵌套检测。
				检测模型 检测子模型
			4：异物检测。
				检测模型
			5：图像识别。
				检测模型 特征模型

		--detector-models < FILE [ FILE ... ] >
			检测器模型配置文件。
			注：检测器模型配置文件中的key和value分行输入，当行首字符为#时，忽略此行。

			例：model.conf
			例：abc/model.conf
			例：/abc/model.conf
			例：http://abc/model.conf
			例：https://abc/model.conf

		--detector-thresholds < MIN MIN ... >
			检测阀值。

		--detector-thresholds-nms < MAX MAX ... >
			NMS阀值。

		--detector-fbd-threshold < MIN >
			异物检测阀值。

		--detector-gap < NUMBER >
			检测器检测帧间隔。默认：-1

		--detector-fps < FLOAT >
			检测器检测帧频率(N/秒)。默认：5.0
			注1：频率为自然时间。
			注2：未设置检测帧间隔时有效。

		--tracker-type < TYPE >
			追踪器-类型，默认：1

			1：IOU。
			2：IOU with Feature。

		--tracker-init < NUMBER >
			追踪器-确认帧数，默认：3

		--tracker-max-lost-age < NUMBER >
			追踪器-最长追丢续上帧数，默认：15

		--tracker-max-center-k < NUMBER >
			追踪器-物体位移最大距离，默认：300

		--tracker-skip-frames < NUMBER >
			追踪器-相邻帧间隔，用于计算物体位移最大距离(max-center-k * skip-frames)，默认：1。

		--tracker-max-feature-budget < NUMBER >
			追踪器-特征存储最大数量，默认：30

		--tracker-max-tracking-distance < NUMBER >
			追踪器-目标匹配系数，默认：0.5

		--tracker-max-losing-distance < NUMBER >
			追踪器-丢失目标匹配系数，默认：0.5

		--tracker-max-new-distance < NUMBER >
			追踪器-新目标匹配系数，默认：0.5

		--tracker-losing-feature-weight < NUMBER >
			追踪器-丢失目标的特征权重，默认：0(不用使用特征或无特征)

		--tracker-matching-feature-weight < NUMBER >
			追踪器-匹配目标的特征权重，默认：0(不用使用特征或无特征)

		--tracker-enable-direction
			追踪器-使能方向因素。

		--tracker-disable
			追踪器禁用。

		--recognition-top < NUMBER >
			图像识别匹配数量。默认：3

		--recognition-list < FILE >
			图像识别清单。
			注1：“ID”和“图像文件”以英文“|”为分隔符，按行写入清单文件中。
			注2：ID为正整数。
			注3：图像文件包括路径。

			例：recognition.list
			例：/abc/recognition.list
			例：http://abc/recognition.list
			例：https://abc/recognition.list

		--trace-cast
			追踪耗时。

		--mcod-bg-delay < FRAMES >
			异物检测背景选择延时(帧)。默认：30

	--output-type < TYPE >
		输出类型。

		0：终端
		1：屏幕
		2：视频
		3：REDIS
		4：KAFKA
		5：共享内存(SHM)

	--output-screen-name < NAME >
		输出屏幕名称。默认：VCA Palyer

	--output-video-name < FILE >
		输出视频文件名称。默认：/dev/null

		例：abc.mp4
		例：/abc.mp4
		例：rtsp://$IP/abc.mp4
		例：rtmp://$IP/abc.mp4

	--output-video-fps < NUMBER >
		输出视频FPS。默认：25。

	--input-video-xspeed < RATIO  >
		输出视频的倍速。默认：1.0

	--output-video-use-h264
		输出视频编码使用H264。

	--output-video-use-fmp4
		输出视频格式为FMP4。默认：MP4

	--output-redis-addr < IP-ADDRESS | DOMAIN-NAME >
		输出REDIS地址。默认：127.0.0.1

	--output-redis-port < NUMBER >
		输出REDIS端口。默认：6379

	--output-redis-timeout < NUMBER >
		输出REDIS超时(秒)。默认：30

	--output-redis-db < NUMBER >
		输出REDIS库编号。默认：1

	--output-redis-queue < STRING >
		输出REDIS队列名称。默认：q1

	--output-redis-queue-max < NUMBER >
		输出REDIS队列最大长度(先进先出)。默认：5

	--output-redis-auth < STRING >
		输出REDIS授权。默认：无

	--output-kafka-brokerlist < HOST-1[:<PORT>],HOST-2[:<PORT>],... >
		输出KAFKA服务器地址。默认：127.0.0.1:9092

	--output-kafka-producer-topic < NAME >
		输出KAFKA发布主题。默认：q1

	--output-kafka-producer-partition < NUMBER >
		输出KAFKA发布分区。默认：0

	--output-shm-prefix < STRING >
		输出共享内存队列文件名的前缀。默认：任务ID

		写索引文件：PREFIX-producer.idx
		读索引文件：PREFIX-consumer.idx
		队列文件：PREFIX-frame-%llu.jpg

	--output-shm-queue-max < NUMBER >
		输出共享内存队列最大长度(先进先出)。默认：5

	--output-jpeg-preview < WIDTHxHEIGHT >
		输出JPEG的预览图。默认：无

	--input-type < TYPE >
		输入类型。默认：1

		1：视频
		2：图片

	--input-trace
		输入追踪。

	--input-video-format < FORMAT >
		输入视频格式。默认：自动检测

	--input-video-name  < FILE >
		输入视频文件名称。

		例：abc.mp4
		例：/abc.mp4
		例：rtsp://$IP/abc.mp4
		例：rtmp://$IP/abc.mp4
		例：http://$IP/abc.mp4
		例：https://$IP/abc.mp4

	--input-video-xspeed < RATIO  >
		输入视频的倍速。默认：1.0

	--input-video-retry-interval
		输入断线重试间隔(秒)。默认：-1(不重试)

	--input-video-timeout < NUMBER >
		输入视频IO超时(秒)。默认：15

	--input-video-only-kframe
		输入视频只取关键帧。

	--input-picture-index < NUMBER >
		输入图片的索引。默认：随机

	--input-picture-name < FILE >
		输入图片的名称。

		例：abc.jpg
		例：/abc.jpg
		例：http://abc.jpg
		例：https://abc.jpg

	--next-protocol-param < STRING >
		下层协议参数。

许可证选项：

	--licence < SN >
		许可证号。

服务端选项：

	--daemon
		启用后台驻留模式。
		注：此功能不支持supervisor守护或类似的工具。

	--service-mode < MODE >
		服务模式。默认：1

		0：单一任务
		1：一般节点
		2：主站节点
		3：从站节点

	--getway-listen < ADDRESS > 
		网关监听地址。默认：0.0.0.0:17008

	--master-listen < ADDRESS > 
		主站监听地址。默认：0.0.0.0:17009

	--slave-id < ID > 
		从站ID。

	--slave-uplink < ADDRESS > 
		从站上行地址。默认：127.0.0.1:17009

	--slave-getway-enable 
		从站启用网关监听。

	--device < NUMBER >
		设备。默认：0

客户端选项：

	--cmd  < COMMAND >
		命令。

		1：任务列表
		2：启动任务
		3：停止任务
		4：删除任务
		5：更新任务
		6：任务状态
		7：设置下层协议
		101：设备信息
		201：许可证信息
		202：更新许可证
		203：获取机器码
		301：从站列表

客户端请求样例：

	curl --data-binary '@Params.txt' -H 'Content-Type: text/plain' http://server.vca:17008/api
		Params.txt: 明文参数文件，参数的键带前缀

	curl --data-binary '@Params.txt' -H 'Content-Type: application/x-www-form-urlencoded' http://server.vca:17008/api
		Params.txt: 表单参数文件，参数的键不带前缀