1. descriptive   [adj] 描述的，描写的

2. avio_open():
   1. create and initialize a AVIOContext for accessing the resource indicated by url.（创建并初始化AVIOContext以访问url指向的资源。）
3. int64_t AVPacket::pts
   1. presentation timestamp in AVStream->time_base units; the time at which the decompressed packet will be presented to the user.（以AVStream->time_base单位表示时间戳；解压缩的数据包将呈现给用户的时间。）
   2. Can be AV_NOPTS_VALUE if it is not stored in the file.(可以AV_NOPTS_VALUE 如果它不存储在文件中。)pts must be larger or equal to dts as presentiation cannot happen before decompression, unless one wants to view hex dumps.（pts必须大于或等于dts，因为在解压缩之间不能进行演示，除非想要查看十六进制转储。）some formats misuse the terms dts and pts/cts to mean something different. Such timestamps must be converted to true pts/dts before they are stored in AVPacket.（某些格式误用术语dts和pts/cts来表示不通的东西。此类时间戳必须转换为真正的pts/dts，然后才能存储在AVPacket）
4. int64_t av_rescale_q_rnd(int64_t a, AVRational bq, AVRational cq, enum AVRounding rnd);
   1. rescale a 64-bit integer by 2 rational numbers with specified rounding. the operation is mathematically equivalent to 'a * bq / cq'.（使用指定的舍入将64位整数按2个有理数重新缩放。该操作在数学上等效于‘a * bq / cq’）
   2. AVRational{int num; int den};
      1. num : numerators(分子)
      2. den : denominators(分母)
      3. while rational numbers can be expressed as floating-point numbers, the conversion process is a lossy one, so are floating-point operations. On the other hand, the nature of FFmpeg demands highly accurate calculation of timestamps.this set of rational number utilities serves as a generic interface for manipulation rational numbers as pairs of numerators and denominators.(虽然有理数可以表示为浮点数，但是转换过程是有损失的，浮点运算也是如此。另一方面，FFmpeg的本质需要高度准确的计算时间戳。这组有理数实用程序用作将有理数作为分子和分母对的通用接口)
5. int64_t AVPacket::dts
   1. decompression timestamp in AVStream->time_base units; the time at which the packet is decompressed.(以AVStream->time_base为单位的解压缩时间戳；解压缩数据包的时间)
6. int64_t AVPacket::duration
   1. duration of this packet in AVStream->time_base units, 0 if unknown. equals next_pts-this_pts in presentation order.（此数据包的持续时间（以AVStream->time_base为单位），如果未知，则为0。按表示顺序等于next_pts-this_pts。）
7. int av_interleaved_write_frame(AVFormatContext *s, AVPacket *pkt);
   1. write a packet to an output media file ensuring correct interleaving.this function will buffer the packets internally as needed to make sure the packets in the output file are properly interleaved in the order of increasing dts.（将数据包写入输出媒体文件，确保正确的交错。此函数将根据需要在内部缓冲数据包，以确保输出文件中的数据包按dts递增的顺序正确交错。）
   2. Callers doing their own interleaving should call av_write_frame() instead of this function. Using this function instead of av_write_frame() can give muxers advance knowledge of future packets, improving e.g. the behaviour of the mp4 muxer for VFR content in fragmenting mode.（执行自己的交错的调用方法应调用av_write_frame() 而不是此函数。使用此功能代替av_write_frame() 可以为多路复用器提供未来数据包的提前知识，从而改善例如mp4多路复用器在分段时对VFR内容的行为。）

今日工作总结：
    1. 编写并调试任务的代码，学习用到的相关类的方法和参数
    2. 阅读《C++程序设计 第1-3部分》电子书和观看候捷老师的C++课程，巩固学习C++的基础知识