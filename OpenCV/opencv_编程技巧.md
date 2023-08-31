## 简介

+ OpenCV 相关编程技巧

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