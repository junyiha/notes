## ffmpeg保存摄像头视频到本地

+ `ffmpeg -rtsp_transport tcp -i rtsp://admin:a1234567@192.167.0.56:554 -c copy -f mp4 -t 00:10:00 /data/output.mp4`
