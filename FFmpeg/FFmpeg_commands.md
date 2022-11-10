## ffmpeg保存摄像头视频到本地

+ `ffmpeg -rtsp_transport tcp -i rtsp://admin:a1234567@192.167.0.56:554 -c copy -f mp4 -t 00:10:00 /data/output.mp4`

## ffmpeg缩放视频（等比例）

+ `ffmpeg -i input-video.mp4 -vf scale=300:180 ./output.mp4`
+ 参数：
  + `-vf`  --  filter_graph, set video filters

## FFmpeg将视频按帧截取保存为图片

+ `ffmpeg -i /home/user/Videos/new_year.mp4 -r 5 -f image2 image-%03d.jpg`
+ 参数：
  + `-i`  --  指定输入源
  + `-r`  --  指定抽取的帧，即从视频中每秒抽取的图片数量
  + `-f`  --  fmt，强迫采用格式fmt 保存图片使用的格式
  + `image-%03d.jpg`  --  指定文件的输出名字

## 获取音视频信息

+ `ffprobe`是FFmpeg项目提供的用于分析视频信息的命令工具
+ 例如:`ffprobe -v quiet -print_format json -show_format -show_streams test.mp4`可以活动json格式的输出的视频信息
  + `-v quiet` : 将日志级别设为quiet，避免日志信息污染json
  + `-show_format` : 显式文件的容器信息
  + `-show_stream` : 显式容器中流的信息
  + `-show_frames` : 则可以显式视频中每一帧的信息

## 使用ffmpeg进行视频处理

+ ffmpeg的命令格式：
  ```
    ffmpeg \
        [global_options] \
        [input_file_options] -i input_url \
        [actions] \
        [output_file_options] output_url
  ```
+ 可以将ffmpeg的选项分为全局选项和局部选项
  + 局部选项用于设置输入输出或滤镜等，通常位于被修饰的指令前面
+ ffmpeg的基本流程为：将容器中的各流进行解码，然后重新编码为指定的格式。在编码之前，可以使用`filter`对视频进行处理

+ 选项
  + `-y / -n` : 全局选项，`-y`表示直接覆盖已经存在的输入文件，`-n`表示若某个输出文件已经存在则退出。若没有设置`-y`或`-n`选项，且某个输出文件已经存在，ffmpeg会询问是否要覆盖输出文件
  + `-codec , -c` ： 指定输入输出的编解码器，可用的编解码器参考官方文档
    + codec指定为`copy`，**则将输入流直接复制到输出流不进行编码操作**
    + 使用`-c:STREAM_INDEX`方式可以指定某一个流的编码器，`STREAM_INDEX`为stream对象的index属性
    + `-c:v, -vcodec`，可以为所有视频流指定编解码器， `-c:v:1`为第2各视频流指定编解码器
    + `-c:a, -acodec`，可以为所有音频流指定编解码器， `-c:a:12`为第13个视频流指定编解码器
  + `-ss` : 用于设置流的开始视频，可以设置输入输出或滤镜，在开始时间之前的帧将被跳过部处理（输入不被解码，输出不被编码，滤镜不被处理）
    + 秒数 ： `-t 10, -t 24.134`
    + 时分秒 ： `-t 10:23, -t 21:31:00.233`
  + `-t` ： 选项用于设置输入输出，它在`-i`前可以限制输入时长，在输入文件前可限制输出时长
  + `-to` : 类似于`-t`选项，不同的是它指定结束时刻，`-t`指定持续时间
  + `-f` : 强制设置输入输出的文件格式，**默认情况下ffmpeg会根据文件后缀名判断格式**
    + `ffmpeg-formats` 命令会显示所有支持的编码格式
  + `-vframes` : 设置输出文件中包含的总帧数
  + `-vn` : 不将视频流写到输出文件中
  + `-an` : 不将音频流写到输出文件中
  + `-r` : 设置某个流的帧率
  + `-s` ： 设置帧的大小
  + `-threads` : 设置处理线程数
  + `-shortest` : 当最短的输入流结束后，即停止编码和输出
