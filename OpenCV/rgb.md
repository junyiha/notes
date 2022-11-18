一、RGB模型与YUV模型
1. RGB模型
    物理三基色分别是红（Red）、绿（Green）、蓝（Blue）。现代的显示器技术就是通过组合不通强度的红绿蓝三原色，来达成几乎任何一种可见光的颜色。
    在图像存储中，通过记录每个像素的红绿蓝强度，来记录图像的方法，称为RGB模型（RGB Model）。
    常见的图片格式中，PNG和BMP这两种就是基于RGB模型的。
2. YUV模型 
    YUV模型，又被称为亮度-色度模型。它是通过数学转换，将RGB三通道转换为一个代表亮度的通道（Y），和两个代表色度的通道（UV）来记录图像的模型

二、转换过程
1. RGB2YUV
    在做RGB信号到YUV信号的转换时，一般是先转换到YUV444格式，然后再将UV信号的分辨率降低，变成所需要的格式
2. YUV2RGB
    在播放视频或显示图像的时候，需要将YUV信号转换成RGB信号。这个步骤称为渲染（Rendering）
    在做YUV到RGB的转换时，首先需要将缩水的UV信号的分辨率拉升到与Y信号相同的分辨率，然后再转换到RGB信号。
3. 公式：
    Y = 0.299 * R + 0.587 * G + 0.114 * B
    U = -0.147 * R - 0.289 * G - 0.436 * B
    V = 0.615 * R - 0.515 * G - 0.100 * B 

    R = Y + 1.1140 * V
    G = Y - 0.395 * U - 0.581 * V
    B = Y + 2.032 * U 

收集箱：
1. Opencv没有提供BGR转NV12，但是提供了NV12转RGB：cvtColor(src,dst,CV_YUV2BGR_NV12);
2. 摄像机拍摄出来的视频很多都是用YUV格式保存，颜色空间的转换必须在RGB色彩模型上才能完成，所以第一步是将YUV颜色模型转换为RGB颜色模型
3.   split(image,yuvchannel); 
     merge(rgbchannel,3,img2);