## 公司常用摄像头

### h264

+ 财务室门口 正对办公区域: `rtsp://admin:a1234567@192.169.7.123:554`

+ 实施组北门：`rtsp://admin:a1234567@192.169.7.113:554`

+ 大办公室二楼南: `rtsp://admin:a1234567@192.169.7.114:554`

+ 办公室外北侧走廊: `rtsp://admin:a1234567@192.169.7.117:554`

+ 大门处二楼走廊: `rtsp://admin:a1234567@192.169.7.118:554`

+ 中间喷泉南: `rtsp://admin:a1234567@192.169.7.120:554`

+ 南区办公室: `rtsp://admin:a1234567@192.169.7.121:554`

+ 南部外墙竹门: `rtsp://admin:a1234567@192.169.7.122:554`

+ 大门左侧: `rtsp://admin:a1234567@192.169.7.125:554`

+ 大门右侧: `rtsp://admin:a1234567@192.169.7.126:554`

+ 餐厅南: ` rtsp://admin:a1234567@192.169.7.101:554`

+ 实施组大厅: `rtsp://admin:a1234567@192.169.7.104:554`

+ 大门南通道: `rtsp://admin:a1234567@192.169.7.105:554`

+ 办公室北侧小门: ` rtsp://admin:a1234567@192.169.7.107:554 `

+ 大办公室二楼: ` rtsp://admin:a1234567@192.169.7.108:554 `

+ 阁楼二楼: ` rtsp://admin:a1234567@192.169.7.109:554 `

### h265

+ 总经理财务室门口：`rtsp://admin:a1234567@192.169.7.110:554`

+ 咖啡机：`rtsp://admin:a1234567@192.169.7.111:554`

+ 中间喷泉北: `rtsp://admin:a1234567@192.169.7.115:554`

## 常用rtsp模拟流

+ 烟火：`rtsp://192.169.4.16/test_fire_smoke.mp4`

+ 卓尔人脸识别: `rtsp://192.169.4.16/zhuoer_face_new2.mp4`

+ 高速公路：`rtsp://192.169.4.16/highway.mp4`

### 1920 * 1080 

+ tmp: `rtsp://192.169.4.16/1108_src.mp4`

+ 新年: `rtsp://192.169.4.16/new_year.mp4`

+ 打电话-安全帽：`rtsp://192.169.4.16/test-phone-Helmet.mp4`

+ 区域入侵：`rtsp://192.169.4.16/test_personcount.mp4`

## 摄像头详细信息

```bash
user@computer:workspace$ ffprobe rtsp://admin:a1234567@192.169.7.125:554
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://admin:a1234567@192.169.7.125:554':
  Metadata:
    title           : Media Presentation
  Duration: N/A, start: 0.033000, bitrate: N/A
  Stream #0:0: Video: h264 (Main), yuvj420p(pc, bt709, progressive), 1920x1080, 30 fps, 30 tbr, 90k tbn
```

```bash
user@computer:workspace$ ffprobe rtsp://admin:a1234567@192.169.7.126:554
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://admin:a1234567@192.169.7.126:554':
  Metadata:
    title           : Media Server
  Duration: N/A, start: 0.070000, bitrate: N/A
  Stream #0:0: Video: h264 (Main), yuvj420p(pc, bt709, progressive), 1920x1080, 25 fps, 25 tbr, 90k tbn
```

```bash
user@computer:workspace$ ffprobe rtsp://admin:a1234567@192.169.7.123:554
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://admin:a1234567@192.169.7.123:554':
  Metadata:
    title           : Media Presentation
  Duration: N/A, start: 0.040000, bitrate: N/A
  Stream #0:0: Video: h264 (Main), yuvj420p(pc, bt709, progressive), 1920x1080, 25 fps, 25 tbr, 90k tbn
```

```bash
user@computer:workspace$ ffprobe rtsp://admin:a1234567@192.169.7.105:554
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://admin:a1234567@192.169.7.105:554':
  Metadata:
    title           : Media Presentation
  Duration: N/A, start: 0.040000, bitrate: N/A
  Stream #0:0: Video: h264 (Main), yuvj420p(pc, bt709, progressive), 1920x1080, 25 fps, 25 tbr, 90k tbn
```

```bash
user@computer:workspace$ ffprobe rtsp://admin:a1234567@192.169.7.125:554
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
user@computer:workspace$ ffprobe rtsp://192.169.4.16/test_fire_smoke.mp4 
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://192.169.4.16/test_fire_smoke.mp4':
  Metadata:
    title           : No Title
  Duration: N/A, start: -0.002000, bitrate: N/A
  Stream #0:0: Video: h264 (Main), yuv420p(progressive), 854x480 [SAR 1:1 DAR 427:240], 29.97 fps, 29.97 tbr, 90k tbn
  Stream #0:1: Audio: aac (LC), 48000 Hz, stereo, fltp
user@computer:workspace$ 
```

```bash
user@computer:workspace$ ffprobe rtsp://192.169.4.16/zhuoer_face_new2.mp4
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://192.169.4.16/zhuoer_face_new2.mp4':
  Metadata:
    title           : No Title
  Duration: N/A, start: 2.921667, bitrate: N/A
  Stream #0:0: Video: h264 (High), yuv420p(tv, bt709, progressive), 1920x1080 [SAR 1:1 DAR 16:9], 60 fps, 60 tbr, 90k tbn
  Stream #0:1: Audio: aac (LC), 48000 Hz, stereo, fltp
```

```bash
user@computer:workspace$ ffprobe rtsp://192.169.4.16/highway.mp4
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://192.169.4.16/highway.mp4':
  Metadata:
    title           : No Title
  Duration: N/A, start: 2.943000, bitrate: N/A
  Stream #0:0: Video: h264 (High), yuv420p(tv, bt709, progressive), 1280x720, 29.97 fps, 29.97 tbr, 90k tbn
  Stream #0:1: Audio: aac (LC), 48000 Hz, stereo, fltp
```

```bash
user@computer:workspace$ ffprobe rtsp://192.169.4.16/test-phone-Helmet.mp4
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://192.169.4.16/test-phone-Helmet.mp4':
  Metadata:
    title           : No Title
  Duration: N/A, start: 10.168678, bitrate: N/A
  Stream #0:0: Video: h264 (High), yuvj420p(pc, progressive), 1920x1080, 24.67 fps, 24.67 tbr, 90k tbn
```

```bash
user@computer:workspace$ ffprobe rtsp://192.169.4.16/test_personcount.mp4
ffprobe version N-107810-gd5544f6457 Copyright (c) 2007-2022 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.5.0-3ubuntu1~18.04)
  configuration: 
  libavutil      57. 33.101 / 57. 33.101
  libavcodec     59. 42.101 / 59. 42.101
  libavformat    59. 30.100 / 59. 30.100
  libavdevice    59.  8.101 / 59.  8.101
  libavfilter     8. 46.103 /  8. 46.103
  libswscale      6.  8.102 /  6.  8.102
  libswresample   4.  8.100 /  4.  8.100
Input #0, rtsp, from 'rtsp://192.169.4.16/test_personcount.mp4':
  Metadata:
    title           : No Title
  Duration: N/A, start: 0.039000, bitrate: N/A
  Stream #0:0: Video: h264 (Main), yuv420p(progressive), 1920x1080 [SAR 1:1 DAR 16:9], 25 fps, 25 tbr, 90k tbn
user@computer:workspace$ 
```
