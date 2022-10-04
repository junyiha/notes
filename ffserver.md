## 使用ffserver 将本地视频转为rtsp视频流

+ 配置

```
    HTTPPort 9554
    RTSPPort 554
    MaxClients 1000
    MaxBandwidth 1000
    CustomLog -

    <Stream stat.html>
    Format status
    ACL allow localhost
    ACL allow 192.167.0.0 192.167.255.255
    </Stream>

    <Stream new_year.mp4>
    File "/home/user/Videos/new_year.mp4"
    Format rtp
    </Stream>
```

+ 使用：`rtsp://192.167.15.58:554/new_year.mp4`

+ 参数说明
  + `HTTPPort 9554` -- HTTP服务器监听的tcp端口
  + `Port 9554` -- 和`HTTPPort`一样，但是不推荐使用
  + `RTSPPort 554` -- rtsp服务器监听的tcp端口
  + `HTTPBindAddress 0.0.0.0` -- http服务器绑定地址
  + `RTSPBindAddress` -- rtsp服务器绑定的地址
  + `MaxHTTPConnections 2000` -- 可以同时处理的http连接数，必须在`MaxClients`之前，默认2000
  + `MaxClients 1000` -- 可以同时处理的请求数,默认为5
  + `MaxBandwidth 1000` -- 最大的传输比特率(kbps) kbit/sec 默认为1000
  + `CustomLog [filename/-]` -- 日志文件，使用标准的Apache日志文件格式， `-` 代表标准输出，没有这个选项不会产生日志，`-d`启动时忽略此配置并打印在标准输出上
  + `NoDaemon` -- 禁止为守护进程，若要以守护进程启动去掉此属性即可
  + `ACL allow 127.0.0.1` -- 允许本机连接feed
  + `Feed feed.ffm` -- 所关联的feed文件
  + `File filename` -- 预先准备好的文件
  + `Format flv/rtp` -- 输出流的格式