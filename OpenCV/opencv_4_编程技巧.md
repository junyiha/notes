## 简介

+ OpenCV 相关编程技巧

## 多张图像编码为视频

+ MJPEG --> avi
+ mp4v --> mp4

## 图像的滤波平滑处理

```cpp
//均值滤波
void blur(InputArray src, OutputArray dst,
                    Size ksize, Point anchor = Point(-1,-1),
                    int borderType = BORDER_DEFAULT);
//src参数表示输入图像，dst参数表示输出图像，与输入图像有同样的size和type；ksize参数表示核的大小
//anchor参数表示核的中心，默认值为Point(-1,-1)，会转化为核的中点；borderType参数表示边缘点插值类型

//中值滤波
void medianBlur(InputArray src, OutputArray dst, int ksize);
//src参数表示输入图像，dst参数表示输出图像，与输入图像有同样的size和type；ksize参数表示正方形的边长. 边长必须是奇数而且大于1
//需要注意的是，当ksize是3或5的时候，图像的深度可以是CV_8U、CV_16U或CV_32F，对于更大的ksize，那么图像的深度只能是CV_8U

//高斯滤波
void GaussianBlur(InputArray src, OutputArray dst, Size ksize,
                    double sigmaX, double sigmaY = 0,
                    int borderType = BORDER_DEFAULT);
//src参数表示输入图像，dst参数表示输出图像，与输入图像有同样的size和type；ksize参数表示高斯核大小
//ksize.width和ksize.height可以不同，但是都必须是正整数而且是奇数，也可以是O，如果是0的话，它的值由sigmaX和sigmaY决定
//sigmaX参数表示X方向上的标准差，sigmaY参数表示Y方向上的标准差，如果Y方向为0，则被设置和X方向一样，如果X和Y方向都为0，则它们由ksize.width和ksize.height计算得到，建议全部都给定数值。
//borderType参数表示边缘点插值类型

//双边滤波器
void bilateralFilter( InputArray src, OutputArray dst, int d,
                    double sigmaColor, double sigmaSpace,
                    int borderType = BORDER_DEFAULT );
//src参数表示输入图像为单通道或3通道的8比特图像，dst参数表示输出图像，与输入图像有同样的size和type
//d参数表示每个像素领域的直径，如果为负数，则由sigmaSpace确定
//sigmaColor参数表示颜色空间的标准偏差，sigmaSpace表示坐标空间的标准偏差，borderType参数表示边缘点插值类型
```

## cv::Point 乘以0.5

要实现 `cv::Point` 乘以标量的操作，你可以直接使用 `cv::Point` 类的成员函数 `operator*=` 或者全局函数 `operator*`。这两个函数支持将 `cv::Point` 与标量相乘。

以下是示例代码：

```cpp
#include <iostream>
#include <opencv2/core.hpp>

int main() {
    cv::Point pt1(2, 4);

    // 使用 operator*=
    pt1 *= 0.5;

    // 使用 operator*
    cv::Point pt2 = pt1 * 0.5;

    std::cout << "pt1: (" << pt1.x << ", " << pt1.y << ")" << std::endl;
    std::cout << "pt2: (" << pt2.x << ", " << pt2.y << ")" << std::endl;

    return 0;
}
```

在这个示例中，`pt1` 被乘以0.5，结果存储在 `pt1` 中，然后再将 `pt1` 乘以0.5，结果存储在 `pt2` 中。最后输出两个点的坐标。

你也可以通过直接使用 `operator*` 来将 `cv::Point` 与标量相乘，结果会存储在新的 `cv::Point` 中。

## C++ OpenCV 图片 画上指定字符串

要在C++中使用OpenCV在图像上添加指定的字符串，你可以按照以下步骤进行操作：

1. 导入必要的头文件：

```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
```

2. 读取图像文件：

```cpp
cv::Mat image = cv::imread("input_image.jpg");
```

3. 定义要添加的文本内容以及其他绘制参数：

```cpp
std::string text = "Your text here";
cv::Point org(50, 50); // 文本的起始位置
int fontFace = cv::FONT_HERSHEY_SIMPLEX; // 字体类型
double fontScale = 1.0; // 字体缩放系数
cv::Scalar color(255, 255, 255); // 文本颜色
int thickness = 2; // 文本粗细
```

4. 在图像上绘制文本：

```cpp
cv::putText(image, text, org, fontFace, fontScale, color, thickness);
```

5. 显示结果图像：

```cpp
cv::imshow("Image with Text", image);
cv::waitKey(0);
```

完整示例代码如下所示：

```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main() {
    // 读取图像文件
    cv::Mat image = cv::imread("input_image.jpg");

    // 定义要添加的文本内容以及其他绘制参数
    std::string text = "Your text here";
    cv::Point org(50, 50); // 文本的起始位置
    int fontFace = cv::FONT_HERSHEY_SIMPLEX; // 字体类型
    double fontScale = 1.0; // 字体缩放系数
    cv::Scalar color(255, 255, 255); // 文本颜色
    int thickness = 2; // 文本粗细

    // 在图像上绘制文本
    cv::putText(image, text, org, fontFace, fontScale, color, thickness);

    // 显示结果图像
    cv::imshow("Image with Text", image);
    cv::waitKey(0);

    return 0;
}
```

确保将 `"input_image.jpg"` 替换为你实际要操作的图像文件路径。

## OpenCV 将图片编码成jpg格式并保存在内存中

要将图像编码为JPEG格式并保存在内存中，您可以使用 `cv::imencode` 函数。以下是一个示例代码：

```cpp
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
    // 读取图像
    cv::Mat image = cv::imread("input_image.png"); // 替换为您的图像文件路径

    // 检查图像是否成功加载
    if (image.empty()) {
        std::cerr << "Failed to load image." << std::endl;
        return 1;
    }

    // 编码图像为JPEG格式
    std::vector<uchar> buffer;
    std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 95}; // JPEG质量设置为95
    cv::imencode(".jpg", image, buffer, params);

    // 检查编码是否成功
    if (buffer.empty()) {
        std::cerr << "Failed to encode image." << std::endl;
        return 1;
    }

    // 在此处可以将 buffer 保存到内存中或者传输到其他地方

    std::cout << "Image encoded successfully." << std::endl;

    return 0;
}
```

在这个示例中，我们首先使用 `cv::imread` 函数加载了一个图像（这里假设图像是PNG格式的）。然后，我们使用 `cv::imencode` 函数将图像编码为JPEG格式，并将结果保存到一个名为 `buffer` 的 `std::vector` 中。我们还可以通过 `params` 参数设置JPEG的质量。最后，我们检查了编码是否成功，并打印出相应的消息。

您可以在代码的注释中看到如何将 `buffer` 保存到内存中或者传输到其他地方。

## OpenCV 给出左上角和右下角的两个点的坐标 在图像上画出对应的矩形框

您可以使用OpenCV中的 `cv::rectangle` 函数来在图像上画出矩形框。下面是一个示例代码，它接受左上角和右下角的点坐标，并在图像上绘制出对应的矩形框：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像
    cv::Mat image = cv::imread("input_image.jpg");

    // 确定矩形框的左上角和右下角点坐标
    cv::Point topLeft(100, 100); // 左上角坐标
    cv::Point bottomRight(300, 400); // 右下角坐标

    // 在图像上画出矩形框
    cv::rectangle(image, topLeft, bottomRight, cv::Scalar(0, 255, 0), 2);

    // 显示绘制矩形框后的图像
    cv::imshow("Rectangle", image);
    cv::waitKey(0);

    return 0;
}
```

在这个示例中，我们首先读取了一张图像。然后，我们定义了矩形框的左上角和右下角点的坐标。接下来，我们使用 `cv::rectangle` 函数在图像上绘制矩形框，该函数的参数包括图像，左上角和右下角的点坐标，以及矩形框的颜色和线条宽度。最后，我们显示了绘制了矩形框的图像。

确保将 `"input_image.jpg"` 替换为您实际的图像文件路径。

## OpenCV cv::Mat 获取图像在内存中字节大小

在OpenCV中，可以使用`cv::Mat`的`total()`函数和`elemSize()`函数来获取图像在内存中的字节大小。具体地说，`total()`函数返回矩阵中元素的总数，而`elemSize()`函数返回每个元素的字节大小。通过将这两个值相乘，你可以得到整个矩阵的字节大小。

以下是一个示例代码：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像
    cv::Mat image = cv::imread("path/to/your/image.jpg");

    if (image.empty()) {
        std::cerr << "Error: Couldn't read the image." << std::endl;
        return -1;
    }

    // 计算图像在内存中的字节大小
    size_t byteSize = image.total() * image.elemSize();

    std::cout << "Image size in bytes: " << byteSize << std::endl;

    return 0;
}
```

请确保你已经安装了OpenCV库，并在编译时链接了相应的库文件。上述示例代码中，`path/to/your/image.jpg`应替换为实际图像的文件路径。

## OpenCV 在图像上绘制旋转矩形框 函数 

要在C++中使用OpenCV在图像上绘制旋转矩形框，您可以使用以下步骤：

1. 首先，确保您已经包含OpenCV库的头文件和命名空间：

```cpp
#include <opencv2/opencv.hpp>
using namespace cv;
```

2. 创建一个旋转矩形框的数据结构，通常使用`RotatedRect`类来表示。该类包含了旋转矩形的中心坐标、大小和角度。

```cpp
RotatedRect rotatedRect(Point2f(centerX, centerY), Size2f(width, height), angle);
```

在上述代码中，`centerX`和`centerY`是旋转矩形框的中心坐标，`width`和`height`是矩形框的宽度和高度，`angle`是旋转角度（以度为单位）。

3. 创建一个空白图像或使用已有的图像作为绘制目标。

```cpp
Mat image = imread("input.jpg");
```

4. 使用`ellipse()`函数绘制旋转矩形框。您可以将旋转矩形的参数传递给该函数，然后选择颜色和线宽来绘制矩形框。

```cpp
Scalar color(0, 255, 0); // 颜色（BGR格式）
int thickness = 2; // 线宽

ellipse(image, rotatedRect, color, thickness);
```

5. 最后，您可以选择将绘制后的图像保存到磁盘上或显示它。

完整的示例代码如下：

```cpp
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat image = imread("input.jpg");
    if (image.empty()) {
        // 处理图像加载失败的情况
        return -1;
    }

    Point2f center(image.cols / 2, image.rows / 2);
    float width = 200; // 矩形框的宽度
    float height = 100; // 矩形框的高度
    float angle = 45; // 旋转角度（以度为单位）

    RotatedRect rotatedRect(center, Size2f(width, height), angle);

    Scalar color(0, 255, 0); // 颜色（BGR格式）
    int thickness = 2; // 线宽

    ellipse(image, rotatedRect, color, thickness);

    imshow("Rotated Rectangle", image);
    waitKey(0);

    return 0;
}
```

这将加载名为"input.jpg"的图像，在图像上绘制一个旋转的矩形框，并显示在窗口中。您可以根据需要调整图像文件名、矩形框参数以及颜色和线宽。

## OpenCV cv::Rect 获取四个点的cv::Point

要从一个 `cv::Rect` 对象中获取其四个角的 `cv::Point`，你可以使用 `cv::Rect` 的成员函数 `tl()` 和 `br()`，分别表示矩形的左上角和右下角。然后，可以使用这两个点来构建其他两个角的坐标。以下是示例代码：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个矩形
    cv::Rect rect(100, 100, 200, 150);

    // 获取矩形的四个角
    cv::Point tl = rect.tl(); // 左上角
    cv::Point br = rect.br(); // 右下角

    // 计算其他两个角的坐标
    cv::Point tr(rect.x + rect.width, rect.y); // 右上角
    cv::Point bl(rect.x, rect.y + rect.height); // 左下角

    // 打印四个角的坐标
    std::cout << "左上角: " << tl << std::endl;
    std::cout << "右上角: " << tr << std::endl;
    std::cout << "左下角: " << bl << std::endl;
    std::cout << "右下角: " << br << std::endl;

    return 0;
}
```

在上述示例中，我们首先创建了一个 `cv::Rect` 对象，然后使用 `tl()` 和 `br()` 方法分别获取了左上角和右下角的坐标。接着，我们使用矩形的属性 `x`、`y`、`width` 和 `height` 来计算右上角和左下角的坐标。最后，我们打印出四个角的坐标。这样，你就可以获取矩形的所有四个角的 `cv::Point` 坐标。

## cv::Mat(cv::Rect) 是什么用法

`cv::Mat` 的构造函数可以接受一个 `cv::Rect` 参数，用于创建一个新的 `cv::Mat` 对象，该对象表示了原始图像中指定区域的像素数据。这可以用于从原始图像中提取感兴趣的区域（Region of Interest，ROI）。

构造函数的用法如下：

```cpp
cv::Mat::Mat(const cv::Mat& m, const Rect& roi);
```

其中，`m` 是原始图像，`roi` 是一个 `cv::Rect` 对象，表示要提取的区域。`cv::Mat` 对象将只包含 `roi` 指定的区域的像素数据，而不包含整个原始图像的数据。

以下是一个示例，演示如何使用 `cv::Mat` 的构造函数来提取图像中的感兴趣区域：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像
    cv::Mat image = cv::imread("image.jpg");

    // 定义感兴趣区域的矩形
    cv::Rect roiRect(100, 100, 200, 150);  // (x, y, width, height)

    // 使用构造函数提取感兴趣区域
    cv::Mat roi = cv::Mat(image, roiRect);

    // 显示原始图像和感兴趣区域
    cv::imshow("原始图像", image);
    cv::imshow("感兴趣区域", roi);
    cv::waitKey(0);

    return 0;
}
```

在上述示例中，我们首先定义了一个矩形 `roiRect`，表示感兴趣区域的位置和大小。然后，使用 `cv::Mat` 的构造函数，我们从原始图像中提取了这个感兴趣区域，最后将原始图像和感兴趣区域显示出来。这种方法允许你对感兴趣区域进行进一步的处理，而无需复制整个图像数据。

## OpenCV 检查矩形框是否在四个点围成的四边型之内

要检查一个矩形框是否在由四个点围成的四边形内部，你可以使用 OpenCV 提供的点与多边形关系判断函数。以下是一个示例，演示了如何使用 OpenCV 检查一个矩形框是否在四个点围成的四边形内部：

```cpp
#include <opencv2/opencv.hpp>

using namespace cv;

bool isRectangleInsideQuadrilateral(const Point2f& p1, const Point2f& p2, const Point2f& p3, const Point2f& p4, const Rect& rect) {
    std::vector<Point2f> quadPoints = {p1, p2, p3, p4};
    cv::Mat quadMat = cv::Mat(quadPoints).reshape(1);
    cv::convexHull(quadMat, quadMat);

    std::vector<Point2f> rectPoints(4);
    rectPoints[0] = Point2f(rect.x, rect.y);
    rectPoints[1] = Point2f(rect.x + rect.width, rect.y);
    rectPoints[2] = Point2f(rect.x + rect.width, rect.y + rect.height);
    rectPoints[3] = Point2f(rect.x, rect.y + rect.height);

    for (const Point2f& point : rectPoints) {
        if (pointPolygonTest(quadMat, point, false) < 0) {
            return false;
        }
    }

    return true;
}

int main() {
    Point2f p1(100, 100);
    Point2f p2(300, 100);
    Point2f p3(300, 200);
    Point2f p4(100, 200);

    Rect rect(150, 150, 50, 50); // 矩形框在四边形内部

    if (isRectangleInsideQuadrilateral(p1, p2, p3, p4, rect)) {
        std::cout << "Rectangle is inside the quadrilateral." << std::endl;
    } else {
        std::cout << "Rectangle is not inside the quadrilateral." << std::endl;
    }

    return 0;
}
```

在上述示例中，我们首先定义了四个点的坐标（`p1`、`p2`、`p3`、`p4`）以及一个矩形框（`rect`）。然后，我们使用 `isRectangleInsideQuadrilateral` 函数来检查矩形框是否在由这四个点围成的四边形内部。

在 `isRectangleInsideQuadrilateral` 函数中，我们首先将四个点构成的四边形进行凸包处理，然后使用 `pointPolygonTest` 函数来检查矩形框的每个顶点是否在凸包内。如果所有顶点都在凸包内，那么矩形框就在四边形内部。

运行示例代码后，根据矩形框的位置关系，程序将输出相应的信息。

## OpenCV 四个点cv::Point创建一个矩形框cv::Rect

在OpenCV中，你可以使用四个点的坐标来创建一个包围这些点的矩形框。可以使用这些坐标来计算出最小包围矩形，并将其转换为`cv::Rect`对象。以下是一个示例，演示了如何使用四个点的坐标来创建一个矩形框：

```cpp
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // 定义四个点的坐标
    Point pt1(100, 100);
    Point pt2(300, 100);
    Point pt3(300, 200);
    Point pt4(100, 200);

    // 计算包围四个点的最小矩形框
    RotatedRect rotatedRect = minAreaRect(std::vector<Point2f>{pt1, pt2, pt3, pt4});

    // 将RotatedRect对象转换为Rect对象
    Rect boundingRect = rotatedRect.boundingRect();

    std::cout << "Bounding Rect: (x=" << boundingRect.x << ", y=" << boundingRect.y
              << ", width=" << boundingRect.width << ", height=" << boundingRect.height << ")" << std::endl;

    return 0;
}
```

在上述示例中，我们首先定义了四个点的坐标（`pt1`、`pt2`、`pt3`、`pt4`）。然后，我们使用`minAreaRect`函数计算包围这四个点的最小矩形框，这个矩形框可以是旋转的。最后，我们使用`boundingRect`成员函数将`RotatedRect`对象转换为`cv::Rect`对象，得到矩形框的参数（坐标、宽度和高度）。

运行示例代码后，你将得到最小包围矩形的参数信息。请注意，这个最小包围矩形可能是旋转的，因此其宽度和高度可能与矩形的边界不完全一致。

## OpenCV 判断一个一个矩形框是否在另一个矩形框中

在OpenCV中，你可以使用矩形的坐标信息来判断一个矩形是否完全包含另一个矩形。以下是一个示例，展示了如何判断一个矩形是否在另一个矩形内部：

```cpp
#include <opencv2/opencv.hpp>

using namespace cv;

bool isRectangleInside(const Rect& outerRect, const Rect& innerRect) {
    return (innerRect.x >= outerRect.x &&
            innerRect.y >= outerRect.y &&
            innerRect.x + innerRect.width <= outerRect.x + outerRect.width &&
            innerRect.y + innerRect.height <= outerRect.y + outerRect.height);
}

int main() {
    Rect outerRect(100, 100, 300, 200); // 外部矩形框
    Rect innerRect(150, 150, 100, 50);  // 内部矩形框

    if (isRectangleInside(outerRect, innerRect)) {
        std::cout << "Inner rectangle is inside the outer rectangle." << std::endl;
    } else {
        std::cout << "Inner rectangle is not inside the outer rectangle." << std::endl;
    }

    return 0;
}
```

在上述示例中，我们定义了一个`isRectangleInside`函数，该函数接受两个`Rect`对象（矩形框）作为参数，然后通过比较矩形的坐标信息来判断第二个矩形是否完全包含在第一个矩形内部。

请注意，矩形的坐标通常由 `(x, y)` 表示左上角的点，而 `width` 和 `height` 分别表示矩形的宽度和高度。在示例中，我们首先创建了一个外部矩形框和一个内部矩形框，并使用`isRectangleInside`函数判断内部矩形是否在外部矩形内部。

运行示例代码后，根据内部矩形的位置关系，程序将输出相应的信息。

## OpenCV 判断一个旋转矩形框是否在一个矩形框中

要判断一个旋转矩形是否完全位于另一个矩形框内部，你可以使用OpenCV的`cv::RotatedRect`和`cv::Rect`类来实现。以下是一个示例，展示了如何判断一个旋转矩形是否在一个矩形框内部：

```cpp
#include <opencv2/opencv.hpp>

using namespace cv;

bool isRotatedRectInside(const RotatedRect& outerRect, const Rect& innerRect) {
    // 获取旋转矩形框的四个顶点
    Point2f vertices[4];
    outerRect.points(vertices);

    for (int i = 0; i < 4; i++) {
        if (vertices[i].x < innerRect.x ||
            vertices[i].x > innerRect.x + innerRect.width ||
            vertices[i].y < innerRect.y ||
            vertices[i].y > innerRect.y + innerRect.height) {
            return false; // 旋转矩形框的某个顶点在内部矩形框外部
        }
    }

    return true;
}

int main() {
    RotatedRect rotatedRect(Point2f(200, 150), Size2f(200, 100), 45); // 旋转矩形框
    Rect innerRect(150, 100, 100, 50); // 内部矩形框

    if (isRotatedRectInside(rotatedRect, innerRect)) {
        std::cout << "Rotated rectangle is inside the rectangle." << std::endl;
    } else {
        std::cout << "Rotated rectangle is not inside the rectangle." << std::endl;
    }

    return 0;
}
```

在上述示例中，我们定义了一个`isRotatedRectInside`函数，该函数接受一个旋转矩形框和一个矩形框作为参数，然后通过比较旋转矩形框的顶点坐标和内部矩形框的位置关系来判断旋转矩形是否完全位于内部矩形框内部。

请注意，在判断旋转矩形框是否在矩形框内部时，我们需要获取旋转矩形框的四个顶点坐标，然后检查每个顶点是否在内部矩形框内。这个过程涉及到点与矩形的比较。运行示例代码后，根据旋转矩形的位置关系，程序将输出相应的信息。

## OpenCV 获取鼠标位置 图片 详解 示例

要使用OpenCV获取鼠标位置并在图像上显示鼠标位置，你可以遵循以下步骤。这里的示例将使用OpenCV的C++接口。

```cpp
#include <opencv2/opencv.hpp>

using namespace cv;

// 回调函数，用于获取鼠标位置
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_MOUSEMOVE) {
        Mat* image = static_cast<Mat*>(userdata);

        // 在图像上绘制鼠标位置
        Mat imageCopy = image->clone();
        circle(imageCopy, Point(x, y), 5, Scalar(0, 0, 255), -1);
        putText(imageCopy, "Mouse Position: (" + std::to_string(x) + ", " + std::to_string(y) + ")",
                Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);

        imshow("Image with Mouse Position", imageCopy);
    }
}

int main() {
    // 加载图像
    Mat image = imread("image.jpg"); // 替换为你的图像路径

    if (image.empty()) {
        std::cerr << "Error loading image!" << std::endl;
        return -1;
    }

    namedWindow("Image with Mouse Position");
    setMouseCallback("Image with Mouse Position", onMouse, &image);

    imshow("Image with Mouse Position", image);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
```

在这个示例中，我们使用`setMouseCallback`函数设置鼠标事件的回调函数，当鼠标在图像上移动时会调用这个回调函数。回调函数`onMouse`获取鼠标的坐标，并在图像上绘制一个红色的圆圈表示鼠标位置，同时在图像上方显示鼠标坐标信息。

你需要将 `"image.jpg"` 替换为你的图像文件的路径。运行示例代码后，窗口会显示原始图像，并在鼠标移动时在图像上绘制圆圈和坐标信息。

请注意，回调函数是在主循环中被调用的，因此它需要快速执行，以免影响其他的事件处理。

## 鼠标点击 获取坐标

要在 OpenCV 中获取鼠标点击事件的坐标，你可以使用鼠标事件的回调函数，并在回调函数中获取坐标信息。以下是一个示例代码，演示如何在鼠标点击时输出点的坐标：

```cpp
#include <opencv2/opencv.hpp>

// 鼠标点击事件的回调函数
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Point* p = static_cast<cv::Point*>(userdata);
        p->x = x;
        p->y = y;
    }
}

int main() {
    cv::Mat image = cv::imread("image.jpg");

    // 创建窗口并显示图像
    cv::namedWindow("Image");
    cv::imshow("Image", image);

    // 定义点的坐标
    cv::Point point;

    // 设置鼠标回调函数，并传递点的坐标作为用户数据
    cv::setMouseCallback("Image", onMouse, &point);

    // 等待鼠标点击
    cv::waitKey(0);

    // 输出点击点的坐标
    std::cout << "Clicked point coordinates: (" << point.x << ", " << point.y << ")" << std::endl;

    cv::destroyAllWindows();

    return 0;
}
```

在上述示例中，我们首先读取一张图像并显示在窗口中。然后，我们定义了一个 `cv::Point` 对象 `point` 用于存储鼠标点击的坐标。

接下来，我们使用 `cv::setMouseCallback()` 函数设置鼠标点击事件的回调函数，即 `onMouse` 函数，并将 `point` 对象的地址作为用户数据传递给回调函数。

在回调函数 `onMouse` 中，我们检测是否发生了鼠标左键点击事件，并将点击的坐标信息存储在 `point` 对象中。

最后，我们使用 `cv::waitKey(0)` 等待鼠标点击事件，并在用户点击后输出点击点的坐标信息。

请注意，点击事件发生后，点击点的坐标将存储在 `point` 对象中，可以在其他地方访问和使用。

运行示例代码后，在图像窗口中点击鼠标左键，程序将输出点击点的坐标信息。

需要注意的是，在使用 OpenCV 的鼠标事件时，确保已经创建了窗口并调用了 `cv::setMouseCallback()` 函数来设置回调函数，并通过用户数据参数传递要保存坐标信息的对象的地址。

## 从内存读取图片数据

以下是使用 OpenCV C++ 从内存中读取图像数据并显示的示例代码：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 假设图像数据存储在内存中的缓冲区 image_data 中

    // 图像参数
    int width = 640;
    int height = 480;
    int channels = 3; // RGB 图像，通道数为 3

    // 创建一个 cv::Mat 对象，将图像数据与缓冲区关联起来
    cv::Mat image(height, width, CV_8UC3, image_data);

    // 创建一个名为 "Image" 的窗口
    cv::namedWindow("Image");

    // 显示图像
    cv::imshow("Image", image);

    // 等待按下任意按键
    cv::waitKey(0);

    return 0;
}
```

在上述示例中，假设图像数据存储在内存中的 `image_data` 缓冲区中。我们使用图像的宽度、高度和通道数创建了一个 `cv::Mat` 对象 `image`，并将其与缓冲区关联起来。

然后，我们通过调用 `cv::namedWindow()` 函数创建了一个名为 "Image" 的窗口。接下来，使用 `cv::imshow()` 函数将 `image` 显示在窗口中。

最后，我们调用 `cv::waitKey()` 函数等待用户按下任意按键，以保持窗口打开状态。当用户按下按键后，程序将继续执行，并返回按键的 ASCII 值。

请注意，上述示例假设图像数据已经按正确的格式（像素顺序、颜色通道顺序等）存储在 `image_data` 缓冲区中。如果图像数据的格式不匹配，可能会导致图像显示不正确。确保以正确的格式存储图像数据非常重要。

此外，还可以根据实际需要对图像进行预处理，例如调整大小、转换颜色空间等操作。以上示例仅演示了从内存中读取图像数据并显示的基本操作，具体的图像处理和操作可以根据实际需求进行扩展。

请注意，以上信息基于 OpenCV 4.5.2 版本。不同的版本可能会略有差异，建议参考官方文档获取特定版本的详细信息。