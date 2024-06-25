---
category: Project
date: 2024-05-22 09:00:00 +0800
layout: post
title: video_process_code04
tag: ProjectOfVideoContentAnalysis
---

+ 有四个输出
  + 输出到屏幕  --  output2Screen
  + 输出到视频  --  output2Video
  + 输出到redis --  output2Redis
  + 输出到kafka --  output2Kafka
+ 通过output()函数调用四个输出方式
  + 接收Image参数的调用output2Screen 或者 output2Video
  + 接收txt参数的调用output2Redis 或者 output2Kafka
  + 