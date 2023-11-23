
nvr.exe 版本 6.2.18

一般选项：

        --help [ BRANCH ]
                打印帮助信息。

                version: 仅版本信息。
                all: 全部信息。

日志选项：

        --log-verbose
                记录详细日志。默认：记录重要日志

任务选项：

        --survival-duration < SECONDS >
                生存时长(秒)。默认：3122064000(99x365x24x60x60)

        --input-fmt < FORMAT >
                输入媒体格式。

        --input-uri < URI >
                输入媒体地址。

        --input-timeout < SECONDS >
                输入媒体超时时长(秒)。默认：30

        --input-retry < SECONDS >
                输入媒体断开重连间隔(秒)。默认：15

        --input-xspeed < RATIO >
                输入媒体倍速。默认：1.0

        --record-name < NAME >
                录像文件的名称(包括路径)。

        --record-duration < SECONDS >
                录像文件的时长(秒)。默认：60

        --record-count < COUNT >
                录像文件的保留数量(1~65535)。默认：60

        --publish-fmt < FORMAT >
                推流的格式。

        --publish-uri < URI >
                推流的地址。

        --onvif-username < NAME >
                ONVIF协议账户名称。

        --onvif-password < PAWD >
                ONVIF协议账户密码。

        --onvif-xaddr < URI >
                ONVIF协议设备地址。

        --onvif-version < VERSION >
                ONVIF协议API版本。

服务选项：

        --daemon
                启用后台驻留模式。
                注：此功能不支持supervisor守护或类似的工具。

        --getway-listen < ADDRESS > 
                网关监听地址。默认：0.0.0.0:37008

        --work-path < PATH >
                工作路径。默认:/tmp/nvr/

        --sms-ssl-path < PATH >
                SMS证书路径。默认:./sms/ssl/ 

        --sms-http-port < PORT >
                HTTP(HLS)端口。默认:80

        --sms-https-port < PORT >
                HTTPS(HLSS)端口。默认:443

        --sms-rtsp-port < PORT >
                RTSP端口。默认:554

        --sms-rtsps-port < PORT >
                RTSPS端口。默认:1554

        --sms-rtmp-port < PORT >
                RTMP端口。默认:1935

        --sms-rtmps-port < PORT >
                RTMPS端口。默认:11935

客户端选项：

        --cmd  < COMMAND >
                命令。

                1：输入测试
                2：录像任务列表
                3：添加录像任务
                4：删除录像任务
                202：推流任务列表
                203：添加推流任务
                204：删除推流任务
                101：扫描摄像头地址(ONVIF)
                102：获取摄像头URI(ONVIF)

客户端请求样例：

        curl -d '@Params.txt' -H 'Content-Type: text/plain' http://server.vam:27008/api
                Params.txt: 明文参数文件，参数的键带前缀

        curl -d '@Params.txt' -H 'Content-Type: application/x-www-form-urlencoded' http://server.vam:27008/api
                Params.txt: 表单参数文件，参数的键不带前缀