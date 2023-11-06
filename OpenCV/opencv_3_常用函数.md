## 简介

+ OpenCV 常见类，函数

## OpenCV cv::findChessboardCorners() 函数 详解



## C++ OpenCV cv::ellipse() 函数 详解

`cv::ellipse()` 函数是OpenCV中用于绘制椭圆的函数。它允许您在图像上绘制椭圆，可以用于标记或可视化图像中的对象或区域。以下是`cv::ellipse()`函数的详解：

```cpp
void cv::ellipse(
    InputOutputArray img,           // 输出图像
    Point center,                   // 椭圆的中心坐标
    Size axes,                      // 长轴和短轴的大小
    double angle,                   // 旋转角度（以度为单位）
    double startAngle,              // 开始角度（以度为单位）
    double endAngle,                // 结束角度（以度为单位）
    const Scalar& color,           // 椭圆的颜色（BGR格式）
    int thickness = 1,             // 边框线宽
    int lineType = LINE_8,          // 线的类型
    int shift = 0                   // 点坐标的小数位数
);`cv::findChessboardCorners()` 是 OpenCV 中用于检测棋盘格角点的函数。这个函数主要用于摄像机标定和校正。下面是有关 `cv::findChessboardCorners()` 函数的详细解释：

```cpp
bool cv::findChessboardCorners(const cv::Mat& image, cv::Size patternSize, cv::OutputArray corners, int flags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE)
```

参数解释：
- `image`：输入的图像，通常是拍摄的包含了棋盘格的图像。
- `patternSize`：一个 `cv::Size` 对象，指定了棋盘格的内部角点的行和列数，通常为 `(num_cols, num_rows)`。
- `corners`：用于输出检测到的角点坐标的 `cv::OutputArray`。这是一个包含检测到的角点的 2D 坐标的向量。
- `flags`：可选参数，用于指定不同的标志位以控制检测的方式。常用的标志包括：
  - `cv::CALIB_CB_ADAPTIVE_THRESH`：使用自适应阈值方法。
  - `cv::CALIB_CB_NORMALIZE_IMAGE`：在角点检测之前归一化图像。
  - `cv::CALIB_CB_FAST_CHECK`：执行快速检查以排除不合格的图像。

返回值：
- 如果成功检测到棋盘格角点，函数返回 `true`，否则返回 `false`。

使用示例：
```cpp
cv::Mat image = cv::imread("chessboard.jpg");
cv::Size patternSize(7, 6); // 棋盘格的列数和行数
cv::Mat grayImage;
cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

std::vector<cv::Point2f> corners;
bool found = cv::findChessboardCorners(grayImage, patternSize, corners);

if (found) {
    // 在图像上绘制角点
    cv::drawChessboardCorners(image, patternSize, cv::Mat(corners), found);
    cv::imshow("Chessboard Corners", image);
    cv::waitKey(0);
}
```

`cv::findChessboardCorners()` 函数的主要用途是用于相机标定，以便校正图像畸变。检测到的角点可以用于计算相机的内部和外部参数，以及图像的校正和畸变校正。通常，使用棋盘格图像进行标定是摄影测量和计算机视觉中的一个重要步骤。
```

参数说明：

- `img`：输入输出图像，您可以在其上绘制椭圆。

- `center`：椭圆的中心坐标，通常表示为`cv::Point`对象。

- `axes`：一个`cv::Size`对象，表示椭圆的长轴和短轴的大小。

- `angle`：椭圆的旋转角度，以度为单位。正值表示顺时针旋转，负值表示逆时针旋转。

- `startAngle`：起始角度，以度为单位。椭圆将从这个角度开始绘制。

- `endAngle`：结束角度，以度为单位。椭圆将绘制到这个角度。

- `color`：椭圆的颜色，通常表示为`cv::Scalar`对象，使用BGR颜色格式。

- `thickness`：椭圆的边框线宽，默认为1。

- `lineType`：线的类型，可以是`LINE_4`、`LINE_8`或`LINE_AA`中的一个，分别表示4-连通、8-连通和抗锯齿线。

- `shift`：点坐标的小数位数，通常为0。

示例用法：

```cpp
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat image(400, 400, CV_8UC3, Scalar(255, 255, 255)); // 创建白色背景图像

    Point center(200, 200);
    Size axes(100, 50);
    double angle = 30;
    double startAngle = 0;
    double endAngle = 360;
    Scalar color(0, 0, 255); // 蓝色

    ellipse(image, center, axes, angle, startAngle, endAngle, color, 2);

    imshow("Ellipse", image);
    waitKey(0);

    return 0;
}
```

上述示例创建了一个400x400的白色背景图像，在其中绘制了一个蓝色的椭圆。您可以根据需要调整参数以满足您的绘制需求。

## Mat operator()( const Rect& roi ) const 详解

`cv::Mat` 类中的 `operator()(const Rect& roi) const` 是一个用于提取感兴趣区域（Region of Interest，ROI）的运算符重载。它允许你根据给定的矩形区域来创建一个新的 `cv::Mat` 对象，其中包含了原始图像中该矩形区域的像素数据。以下是这个运算符重载的详细解释：

```cpp
cv::Mat cv::Mat::operator()(const cv::Rect& roi) const;
```

参数说明：
- `roi`：一个 `cv::Rect` 对象，表示感兴趣区域的位置和大小。

运算符重载的返回值是一个新的 `cv::Mat` 对象，其中包含了原始图像中指定感兴趣区域的像素数据。

使用示例：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像
    cv::Mat image = cv::imread("image.jpg");

    // 定义感兴趣区域的矩形
    cv::Rect roiRect(100, 100, 200, 150);  // (x, y, width, height)

    // 使用运算符重载提取感兴趣区域
    cv::Mat roi = image(roiRect);

    // 显示感兴趣区域
    cv::imshow("感兴趣区域", roi);
    cv::waitKey(0);

    return 0;
}
```

在上述示例中，我们首先读取了一张图像，然后定义了一个 `cv::Rect` 对象 `roiRect`，表示感兴趣区域的位置和大小。接着，我们使用运算符重载 `image(roiRect)` 来提取图像中指定的感兴趣区域，并将其存储在 `roi` 中。最后，我们显示了这个感兴趣区域。这个运算符重载使得提取感兴趣区域变得非常方便，可以快速获取图像的子区域进行进一步处理。

## cv::Mat::setTo() 函数 详解

`cv::Mat::setTo()` 函数用于将图像中的所有像素设置为指定的值或颜色。这个函数非常有用，可以用来创建具有特定像素值的图像，或者将图像的所有像素设置为某个常数值。以下是 `cv::Mat::setTo()` 函数的详解：

```cpp
void cv::Mat::setTo(const Scalar& value, const Mat& mask = Mat());
```

参数说明：
- `value`：要设置的像素值，通常是一个 `cv::Scalar` 对象，表示图像的颜色或强度。例如，如果你想将图像设置为纯黑色，可以使用 `cv::Scalar(0, 0, 0)`。
- `mask`：可选参数，一个与输入图像相同大小的掩码图像，用于指定哪些像素应该被设置为指定的值。只有在掩码图像中对应的像素值为非零时，对应的目标图像像素才会被设置。默认情况下，没有掩码。

使用示例：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个空的图像
    cv::Mat image(300, 400, CV_8UC3); // 3通道，8位无符号整数类型

    // 设置整个图像为纯蓝色
    cv::Scalar blueColor(255, 0, 0);
    image.setTo(blueColor);

    // 创建一个掩码图像，只有图像中心部分的像素会被修改
    cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);
    cv::Rect roiRect(100, 100, 200, 100);
    mask(roiRect) = 255; // 将中心区域的掩码设置为255

    // 使用掩码将中心部分设置为绿色
    cv::Scalar greenColor(0, 255, 0);
    image.setTo(greenColor, mask);

    // 显示图像
    cv::imshow("图像", image);
    cv::waitKey(0);

    return 0;
}
```

在上述示例中，我们首先创建了一个空的彩色图像，然后使用 `setTo()` 函数将整个图像设置为纯蓝色。接下来，我们创建了一个掩码图像，只有中心区域的像素才会被修改。最后，我们使用掩码将中心部分的像素设置为绿色。这是一个简单示例，演示了如何使用 `cv::Mat::setTo()` 函数来设置图像的像素值。

## cv::resize() 函数 详解

`cv::resize()` 函数用于调整图像或图像区域的大小。你可以使用它来缩小或放大图像，或者将图像裁剪到指定的尺寸。以下是 `cv::resize()` 函数的详解：

```cpp
void cv::resize(
    InputArray src,         // 输入图像，可以是 cv::Mat 或其他图像数据结构
    OutputArray dst,        // 输出图像，可以是 cv::Mat 或其他图像数据结构
    Size dsize,             // 目标图像的大小，指定为 cv::Size(width, height)
    double fx = 0,          // 沿水平轴的缩放因子
    double fy = 0,          // 沿垂直轴的缩放因子
    int interpolation = INTER_LINEAR // 插值方法，可选，默认为线性插值
);
```

参数说明：
- `src`：输入图像，可以是 `cv::Mat` 或其他支持的图像数据结构。
- `dst`：输出图像，可以是 `cv::Mat` 或其他支持的图像数据结构。它将包含调整大小后的图像。
- `dsize`：目标图像的大小，以 `cv::Size` 对象表示，指定为目标宽度和高度。
- `fx`：沿水平轴的缩放因子。如果为0，则根据垂直缩放因子 `fy` 来确定输出大小。
- `fy`：沿垂直轴的缩放因子。如果为0，则根据水平缩放因子 `fx` 来确定输出大小。
- `interpolation`：插值方法，用于在调整大小时估算像素值。可以选择以下插值方法之一：
  - `INTER_NEAREST`：最近邻插值（速度最快，但质量较差）
  - `INTER_LINEAR`：双线性插值（默认，速度适中，质量较好）
  - `INTER_CUBIC`：双三次插值（速度较慢，质量较好）
  - `INTER_LANCZOS4`：Lanczos插值（速度较慢，质量最好）

使用示例：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像
    cv::Mat image = cv::imread("image.jpg");

    // 指定目标大小
    cv::Size targetSize(200, 150);

    // 调整图像大小
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, targetSize, 0, 0, cv::INTER_LINEAR);

    // 显示原始图像和调整大小后的图像
    cv::imshow("原始图像", image);
    cv::imshow("调整大小后的图像", resizedImage);
    cv::waitKey(0);

    return 0;
}
```

上述示例将读取一张图像，将其调整为指定的目标大小，然后显示原始图像和调整大小后的图像。你可以根据需要选择不同的插值方法和目标大小。

## cv::convexHull

在 OpenCV 中，`cv::convexHull()` 函数用于计算一个给定点集的凸包。凸包是包含给定点集中所有点的最小凸多边形。以下是关于 `cv::convexHull()` 函数的详细解释：

**函数签名**：
```cpp
cv::convexHull(InputArray points, OutputArray hull, bool clockwise = false, bool returnPoints = true)
```

**参数**：
- `points`：输入的点集，可以是 `cv::Mat`、`cv::Mat_<T>`、`cv::vector<Point>` 等。
- `hull`：计算出的凸包点集。
- `clockwise`：指定计算的凸包是否按逆时针方向排列。
- `returnPoints`：如果为 `true`，函数将返回凸包的点集；如果为 `false`，函数将返回凸包的索引。

**返回值**：
- 函数没有返回值。凸包的点集或索引存储在 `hull` 参数中。

**示例**：
以下示例演示了如何使用 `cv::convexHull()` 函数计算一组点的凸包：

```cpp
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::vector<Point2f> points;
    points.push_back(Point2f(100, 100));
    points.push_back(Point2f(300, 100));
    points.push_back(Point2f(300, 200));
    points.push_back(Point2f(100, 200));

    std::vector<Point2f> hull;
    convexHull(points, hull);

    Mat image = Mat::zeros(300, 400, CV_8UC3);
    for (const Point2f& p : points) {
        circle(image, p, 5, Scalar(0, 0, 255), -1); // 绘制红色点
    }

    for (size_t i = 0; i < hull.size(); i++) {
        line(image, hull[i], hull[(i + 1) % hull.size()], Scalar(255, 0, 0), 2); // 绘制蓝色凸包边界
    }

    imshow("Convex Hull", image);
    waitKey(0);

    return 0;
}
```

在上述示例中，我们创建了一个点集 `points`，并使用 `convexHull()` 函数计算了这些点的凸包。然后，我们使用绘图函数绘制了原始点和凸包的边界。

运行示例代码后，你将在窗口中看到原始点和计算出的凸包。你可以根据需要调整点的坐标，了解函数的不同参数和用法，以适应你的实际需求。

## cv::RotatedRect::points() 函数 详解

`cv::RotatedRect::points()` 是 OpenCV 中 `cv::RotatedRect` 类的一个成员函数，用于获取旋转矩形的四个顶点坐标。以下是对 `cv::RotatedRect::points()` 函数的详细解释：

**函数原型：**
```cpp
void cv::RotatedRect::points(cv::Point2f pts[]) const
```

**函数功能：**
`cv::RotatedRect::points()` 函数用于获取一个旋转矩形的四个顶点坐标，并将这些坐标存储在提供的数组 `pts` 中。旋转矩形是由中心点、宽度、高度和旋转角度定义的，它可以是在任意角度下旋转的矩形。

**参数：**
- `pts`：一个大小为4的 `cv::Point2f` 数组，用于存储旋转矩形的四个顶点坐标。数组应该在调用函数之前分配好空间。

**返回值：**
函数没有返回值，它直接将四个顶点的坐标存储在提供的数组 `pts` 中。

**示例用法：**
以下是一个使用 `cv::RotatedRect::points()` 函数的示例代码：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::Point2f points[4]; // 存储顶点坐标的数组
    cv::RotatedRect rotatedRect(cv::Point2f(100, 100), cv::Size2f(200, 100), 30); // 创建一个旋转矩形

    rotatedRect.points(points); // 获取旋转矩形的顶点坐标

    for (int i = 0; i < 4; ++i) {
        std::cout << "Point " << i + 1 << ": (" << points[i].x << ", " << points[i].y << ")" << std::endl;
    }

    return 0;
}
```

在上面的示例中，我们首先创建了一个 `cv::RotatedRect` 对象，然后使用 `cv::RotatedRect::points()` 函数获取了该旋转矩形的四个顶点坐标。最后，我们遍历数组 `points`，输出每个顶点的坐标。

总之，`cv::RotatedRect::points()` 函数是一个方便的函数，用于获取旋转矩形的四个顶点坐标，这对于后续的绘制和分析操作非常有用。

## cv::Size2i::area() 函数 详解

`cv::Size2i`是OpenCV中用于表示二维大小的类，其中`cv::Size2i::area()`是一个成员函数，用于计算这个二维大小的面积。以下是对`cv::Size2i::area()`函数的详细解释：

**函数原型：**
```cpp
int cv::Size2i::area() const
```

**函数功能：**
`cv::Size2i::area()`函数用于计算表示二维大小的`cv::Size2i`对象的面积。对于`cv::Size2i`对象，面积等于其宽度（`width`）乘以高度（`height`）。

**参数：**
该函数没有参数，因为它是一个成员函数，作用于`cv::Size2i`对象本身。

**返回值：**
函数返回一个整数，表示`cv::Size2i`对象的面积。

**示例用法：**
下面是一个使用`cv::Size2i::area()`函数的示例代码：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::Size2i size(5, 8); // 创建一个二维大小为(5, 8)的对象
    int area = size.area(); // 计算面积，area = 5 * 8 = 40

    std::cout << "Width: " << size.width << ", Height: " << size.height << std::endl;
    std::cout << "Area: " << area << std::endl;

    return 0;
}
```

在上面的示例中，我们创建了一个`cv::Size2i`对象，然后使用`cv::Size2i::area()`函数计算了其面积。面积的计算结果是对象的宽度和高度的乘积。

总而言之，`cv::Size2i::area()`函数是OpenCV中用于计算`cv::Size2i`对象面积的方便函数，它直接返回对象宽度和高度的乘积。

## cv::fillPoly() 函数 详解

`cv::fillPoly()` 函数是 OpenCV 库中的一个函数，用于在图像上填充指定的多边形区域。

以下是关于 `cv::fillPoly()` 函数的详细解释：

- **函数签名**：函数的签名如下：

  ```cpp
  void cv::fillPoly(
      InputOutputArray img,
      InputArrayOfArrays pts,
      const Scalar &color,
      int lineType = LINE_8,
      int shift = 0,
      Point offset = Point());
  ```

- **参数**：
  - `img`：要填充的图像。
  - `pts`：多边形的顶点集合，可以是一个包含 `cv::Point` 的 `std::vector`，也可以是 `cv::Mat`。
  - `color`：填充的颜色，类型为 `cv::Scalar`，表示 BGR 通道的颜色值。
  - `lineType`：线段的类型，默认为 `LINE_8`，表示8连通线段。
  - `shift`：坐标的小数部分位数，默认为0。
  - `offset`：坐标的偏移，默认为 `Point()`。

- **功能**：
  - 该函数用于在图像上填充一个或多个多边形区域，根据给定的多边形顶点集合和颜色进行填充。
  - 填充的多边形可以是简单多边形，也可以是包含洞的多边形。

- **示例**：
  ```cpp
  cv::Mat image(300, 300, CV_8UC3, cv::Scalar(0, 0, 0));

  std::vector<cv::Point> polygon;
  polygon.push_back(cv::Point(50, 50));
  polygon.push_back(cv::Point(150, 50));
  polygon.push_back(cv::Point(150, 150));
  polygon.push_back(cv::Point(50, 150));

  std::vector<std::vector<cv::Point>> polygons;
  polygons.push_back(polygon);

  cv::fillPoly(image, polygons, cv::Scalar(0, 255, 0));

  cv::imshow("Filled Image", image);
  cv::waitKey(0);
  ```

- **注意事项**：
  - `pts` 参数接受一个包含多个多边形的顶点集合，因此你可以一次性填充多个多边形。
  - 该函数会直接在输入图像上进行填充操作，所以确保图像的尺寸和类型与所需操作匹配。

总之，`cv::fillPoly()` 函数是用于在图像上填充多边形区域的函数。通过提供多边形的顶点集合和填充颜色，你可以在图像中创建各种填充区域，用于可视化和图像处理。

## cv::Mat::ptr() 函数 详解

`cv::Mat::ptr()` 函数是 OpenCV 库中 `cv::Mat` 类的一个成员函数，用于获取指定行的指针，从而允许对图像或矩阵数据进行低级别的访问和操作。

以下是关于 `cv::Mat::ptr()` 函数的详细解释：

- **函数签名**：函数的签名如下：

  ```cpp
  uchar* cv::Mat::ptr(int i = 0);
  ```

- **参数**：
  - `i`：指定要获取指针的行数（默认为0），即行的索引。行索引从0开始。

- **返回值**：
  - 返回一个 `uchar*` 类型的指针，指向指定行的数据。这个指针可以用于低级别的数据访问操作。

- **功能**：
  - 该函数用于获取指定行的指针，允许你对图像或矩阵数据进行低级别的访问和操作。通过获取指针，你可以在不使用高级 OpenCV 函数的情况下，直接读取和修改像素值。

- **示例**：
  ```cpp
  cv::Mat image = cv::imread("image.jpg", cv::IMREAD_COLOR);

  if (!image.empty()) {
      int row = 100;

      uchar* ptr = image.ptr(row);

      for (int col = 0; col < image.cols; ++col) {
          uchar blue = ptr[col * 3];     // Blue channel
          uchar green = ptr[col * 3 + 1]; // Green channel
          uchar red = ptr[col * 3 + 2];   // Red channel
      }
  }
  ```

- **注意事项**：
  - 通过 `cv::Mat::ptr()` 获取的指针可以用于访问指定行的像素数据。如果你需要访问其他通道的像素值，你需要根据通道数进行适当的偏移。
  - 注意确保访问的像素在图像范围内，以避免越界访问。

总之，`cv::Mat::ptr()` 函数是用于获取指定行的指针，从而允许你对图像或矩阵数据进行低级别的访问和操作。这对于一些特定的图像处理任务可能会很有用，但需要小心越界访问。

## cv::Mat::ptr<uint16_t>() 函数 详解

`cv::Mat::ptr<uint16_t>()` 函数是 OpenCV 库中 `cv::Mat` 类的一个成员函数的模板化版本，用于获取指定行的指针，并将指针的数据类型设置为 `uint16_t`，从而允许对图像或矩阵数据进行低级别的访问和操作，特别适用于 `uint16_t` 类型的像素数据。

以下是关于 `cv::Mat::ptr<uint16_t>()` 函数的详细解释：

- **函数签名**：函数的签名如下：

  ```cpp
  uint16_t* cv::Mat::ptr<uint16_t>(int i = 0);
  ```

- **参数**：
  - `i`：指定要获取指针的行数（默认为0），即行的索引。行索引从0开始。

- **返回值**：
  - 返回一个 `uint16_t*` 类型的指针，指向指定行的数据。这个指针可以用于低级别的数据访问操作。

- **功能**：
  - 该函数用于获取指定行的指针，并将指针的数据类型设置为 `uint16_t`，允许你对图像或矩阵数据进行低级别的访问和操作。通过获取指针，你可以在不使用高级 OpenCV 函数的情况下，直接读取和修改像素值。

- **示例**：
  ```cpp
  cv::Mat depth_image = cv::imread("depth_image.png", cv::IMREAD_ANYDEPTH);

  if (!depth_image.empty() && depth_image.depth() == CV_16U) {
      int row = 100;

      uint16_t* ptr = depth_image.ptr<uint16_t>(row);

      for (int col = 0; col < depth_image.cols; ++col) {
          uint16_t depth_value = ptr[col];
      }
  }
  ```

- **注意事项**：
  - 通过 `cv::Mat::ptr<uint16_t>()` 获取的指针可以用于访问指定行的像素数据，数据类型为 `uint16_t`。确保图像的深度为 `CV_16U`，以匹配数据类型。
  - 注意确保访问的像素在图像范围内，以避免越界访问。

总之，`cv::Mat::ptr<uint16_t>()` 函数是用于获取指定行的指针，并将数据类型设置为 `uint16_t`，允许你对图像或矩阵数据进行低级别的访问和操作。这对于访问 `uint16_t` 类型的像素数据非常有用，但需要小心越界访问。

## cv::pointPolygonTest() 函数 详解

`cv::pointPolygonTest()` 函数是 OpenCV 库中的一个函数，用于计算一个点与一个多边形之间的关系，即点相对于多边形的内部、外部还是在多边形的边界上。

以下是关于 `cv::pointPolygonTest()` 函数的详细解释：

- **函数签名**：函数的签名如下：

  ```cpp
  double cv::pointPolygonTest(
      InputArray contour,
      Point2f pt,
      bool measureDist);
  ```

- **参数**：
  - `contour`：表示多边形的轮廓的输入数组。可以是一个 `std::vector<cv::Point>`，也可以是一个 `cv::Mat`。
  - `pt`：要测试的点的坐标，类型为 `cv::Point2f`。
  - `measureDist`：一个布尔值，表示是否要计算点到多边形边界的距离。如果为 `true`，函数将返回点到多边形的距离；如果为 `false`，函数将只返回点相对于多边形的关系（内部、外部或边界）。

- **返回值**：
  - 如果 `measureDist` 参数为 `false`，返回值的含义如下：
    - 正数：点在多边形内部。
    - 零：点在多边形的边界上。
    - 负数：点在多边形外部。
  - 如果 `measureDist` 参数为 `true`，返回值表示点到多边形边界的有符号距离。距离为正数表示点在多边形内部，为零表示点在多边形边界上，为负数表示点在多边形外部。

- **功能**：
  - 该函数用于计算一个点与一个多边形之间的关系。它可以确定点相对于多边形的位置，以及点到多边形边界的距离（可选）。

- **示例**：
  ```cpp
  std::vector<cv::Point> contour = {cv::Point(50, 50), cv::Point(200, 50), cv::Point(200, 200), cv::Point(50, 200)};
  cv::Point2f point(100, 100);

  double distance = cv::pointPolygonTest(contour, point, true);

  if (distance > 0) {
      std::cout << "Point is inside the polygon." << std::endl;
  } else if (distance == 0) {
      std::cout << "Point is on the polygon boundary." << std::endl;
  } else {
      std::cout << "Point is outside the polygon." << std::endl;
  }
  ```

- **注意事项**：
  - 如果你只关心点相对于多边形的关系而不需要距离信息，可以将 `measureDist` 参数设置为 `false`，以提高性能。
  - 多边形的轮廓必须是闭合的，并且点的坐标应在 `float` 或 `double` 类型的范围内。

总之，`cv::pointPolygonTest()` 函数是用于计算点与多边形之间关系的函数，可以判断点是否在多边形内部、外部或边界上，并可以计算点到多边形边界的距离。

## cv::Mat::at<cv::Vec3b>() 函数 详解

`cv::Mat::at<cv::Vec3b>()` 函数是 OpenCV 库中 `cv::Mat` 类的一个成员函数，用于访问图像或矩阵中特定位置的像素值。在这个函数中，`cv::Vec3b` 是一个表示三通道（BGR 或 RGB）像素值的数据类型。

以下是关于 `cv::Mat::at<cv::Vec3b>()` 函数的详细解释：

- **函数签名**：函数的签名如下：

  ```cpp
  cv::Vec3b& cv::Mat::at<cv::Vec3b>(int row, int col);
  ```

- **参数**：
  - `row`：像素所在的行数（y 坐标）。
  - `col`：像素所在的列数（x 坐标）。

- **返回值**：
  - 返回一个引用（`cv::Vec3b&`）到指定位置的像素值。`cv::Vec3b` 表示一个三通道的像素，例如 `(B, G, R)` 或 `(R, G, B)`。

- **功能**：
  - 该函数用于访问图像或矩阵中指定位置的像素值。返回的引用允许你读取或修改像素的通道值。

- **示例**：
  ```cpp
  cv::Mat image = cv::imread("image.jpg");

  if (!image.empty()) {
      int row = 100;
      int col = 150;

      cv::Vec3b pixel = image.at<cv::Vec3b>(row, col);

      uchar blue = pixel[0];
      uchar green = pixel[1];
      uchar red = pixel[2];

      std::cout << "Pixel at (" << col << ", " << row << "): "
                << "B: " << int(blue) << " G: " << int(green) << " R: " << int(red) << std::endl;
  }
  ```

- **注意事项**：
  - `cv::Vec3b` 表示三通道像素值，它的索引是 `[0]`、`[1]` 和 `[2]` 分别表示蓝色、绿色和红色通道。但需要注意，OpenCV 中的图像默认使用 BGR 顺序。

总之，`cv::Mat::at<cv::Vec3b>()` 函数是用于访问图像或矩阵中指定位置的三通道像素值的函数。通过该函数，你可以方便地读取和修改图像的像素值，并进行各种图像处理操作。

## cv::circle

在 OpenCV 中，`cv::circle` 是一个用于在图像上绘制圆的函数。这个函数可以用来绘制一个圆，或者在图像上绘制多个圆。

函数原型如下：

```cpp
void cv::circle(cv::InputOutputArray img, cv::Point center, int radius, const cv::Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
```

函数参数解释：
- `img`: 输入/输出图像，可以是单通道或多通道图像。
- `center`: `cv::Point` 类型的参数，表示圆心的坐标。
- `radius`: 圆的半径。
- `color`: 绘制圆的颜色，可以使用 `cv::Scalar` 类来表示颜色。
- `thickness`: 圆边界的宽度（线条粗细），默认值为 1。
- `lineType`: 圆边界的类型，可以是 `LINE_8`（8 连通线）或 `LINE_AA`（反锯齿线）。
- `shift`: 坐标值的小数位数，通常为 0。

下面是一个示例代码，演示了如何使用 `cv::circle` 函数绘制圆：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个黑色图像
    cv::Mat image(300, 400, CV_8UC3, cv::Scalar(0, 0, 0));

    // 定义圆心坐标和半径
    cv::Point center(200, 150);
    int radius = 50;

    // 绘制圆
    cv::circle(image, center, radius, cv::Scalar(0, 0, 255), 2);

    // 显示绘制的图像
    cv::imshow("Circle Example", image);
    cv::waitKey(0);

    return 0;
}
```

在这个示例中，我们创建了一个黑色的图像，然后使用 `cv::circle` 函数绘制了一个红色的圆，圆心为 `(200, 150)`，半径为 50。

`cv::circle` 函数在图像绘制中非常有用，可以用于标记、可视化、边缘检测结果显示等多种情况。可以通过调整参数来控制圆的颜色、半径和边界样式。

---

## cv::Rect

在 OpenCV 中，`cv::Rect` 是一个用于表示矩形的类。它通常用于图像处理和计算机视觉中，用于表示图像中的感兴趣区域（ROI），或者用于描述物体的边界框。

`cv::Rect` 的定义位于 `opencv2/core.hpp` 头文件中，其结构如下：

```cpp
class Rect {
public:
    Rect();
    Rect(int x, int y, int width, int height);
    Rect(const Rect& r);

    int x, y;       // 矩形左上角的坐标
    int width, height; // 矩形的宽度和高度
};
```

这个类有以下几个构造函数和成员变量：

- `Rect()`: 默认构造函数，会将矩形的属性初始化为默认值。
- `Rect(int x, int y, int width, int height)`: 构造函数，传入矩形的左上角坐标、宽度和高度。
- `Rect(const Rect& r)`: 复制构造函数，用于创建一个已有矩形的副本。
- `x` 和 `y`: 整数类型的成员变量，表示矩形左上角的 x 和 y 坐标。
- `width` 和 `height`: 整数类型的成员变量，表示矩形的宽度和高度。

下面是一个示例代码，演示了如何使用 `cv::Rect` 类：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个矩形对象
    cv::Rect rect1(100, 50, 200, 150);

    // 访问矩形的属性
    int x = rect1.x;
    int y = rect1.y;
    int width = rect1.width;
    int height = rect1.height;

    // 输出矩形的属性
    std::cout << "Rectangle: x=" << x << ", y=" << y << ", width=" << width << ", height=" << height << std::endl;

    // 创建另一个矩形对象
    cv::Rect rect2(50, 30, 100, 80);

    // 使用复制构造函数创建新矩形对象
    cv::Rect rect3 = rect2;

    return 0;
}
```

`cv::Rect` 类在许多图像处理和计算机视觉任务中非常有用，特别是在需要表示感兴趣区域、物体的边界框等情况。它可以帮助您存储和操作矩形的属性，以及在图像处理中进行相关操作，例如提取感兴趣区域、绘制边界框等。

---

## cv::line

在 OpenCV 中，`cv::line` 是一个用于在图像上绘制直线的函数。这个函数可以用来绘制一条连接两个点的直线，或者在图像上绘制多条直线。

函数原型如下：

```cpp
void cv::line(cv::InputOutputArray img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
```

函数参数解释：
- `img`: 输入/输出图像，可以是单通道或多通道图像。
- `pt1` 和 `pt2`: 两个 `cv::Point` 类型的参数，表示直线的起点和终点。
- `color`: 绘制直线的颜色，可以使用 `cv::Scalar` 类来表示颜色。
- `thickness`: 直线的宽度（线条粗细），默认值为 1。
- `lineType`: 直线的类型，可以是 `LINE_8`（8 连通线）或 `LINE_AA`（反锯齿直线）。
- `shift`: 坐标值的小数位数，通常为 0。

下面是一个示例代码，演示了如何使用 `cv::line` 函数绘制直线：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个黑色图像
    cv::Mat image(300, 400, CV_8UC3, cv::Scalar(0, 0, 0));

    // 定义起点和终点坐标
    cv::Point pt1(50, 100);
    cv::Point pt2(350, 200);

    // 绘制直线
    cv::line(image, pt1, pt2, cv::Scalar(0, 0, 255), 2);

    // 显示绘制的图像
    cv::imshow("Line Example", image);
    cv::waitKey(0);

    return 0;
}
```

在这个示例中，我们创建了一个黑色的图像，然后使用 `cv::line` 函数在图像上绘制了一条红色的直线，连接了起点 `(50, 100)` 和终点 `(350, 200)`。

`cv::line` 函数在图像绘制中非常有用，可以用于标记、可视化、边缘检测结果显示等多种情况。可以通过调整参数来控制直线的颜色、宽度和类型。

---

## cv::Size

在 OpenCV 中，`cv::Size` 是一个用于表示大小（尺寸）的类。它通常用于图像处理和计算机视觉中，用于表示图像的宽度和高度，或者表示其他物体、区域的尺寸。

`cv::Size` 的定义位于 `opencv2/core.hpp` 头文件中，其结构如下：

```cpp
class Size {
public:
    Size();
    Size(int width, int height);
    Size(const Size& sz);

    int width, height;
};
```

这个类有以下几个构造函数和成员变量：

- `Size()`: 默认构造函数，会将宽度和高度初始化为 0。
- `Size(int width, int height)`: 构造函数，传入宽度和高度。
- `Size(const Size& sz)`: 复制构造函数，用于创建一个已有尺寸的副本。
- `width` 和 `height`: 整数类型的成员变量，分别表示尺寸的宽度和高度。

下面是一个示例代码，演示了如何使用 `cv::Size` 类：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个尺寸对象
    cv::Size size1(640, 480);

    // 访问尺寸的宽度和高度
    int width = size1.width;
    int height = size1.height;

    // 输出尺寸的宽度和高度
    std::cout << "Size: " << width << " x " << height << std::endl;

    // 创建另一个尺寸对象
    cv::Size size2(320, 240);

    // 使用复制构造函数创建新尺寸对象
    cv::Size size3 = size2;

    return 0;
}
```

`cv::Size` 类在许多图像处理和计算机视觉任务中非常有用，特别是在需要表示图像的大小、物体的尺寸等情况。它可以帮助您存储和操作尺寸信息，以及在图像处理中进行相关操作，例如调整图像大小、计算物体的尺寸等。

---

## cv::Point2f

在 OpenCV 中，`cv::Point2f` 是一个用于表示二维浮点坐标点的类。它是 `cv::Point` 的变体，其中坐标值使用浮点数而不是整数表示。`cv::Point2f` 类通常用于图像处理和计算机视觉中，特别是在需要使用浮点坐标来表示像素位置、图像上的点、图像中的特征点等情况。

`cv::Point2f` 的定义位于 `opencv2/core/types.hpp` 头文件中，其结构如下：

```cpp
class Point2f {
public:
    Point2f();
    Point2f(float x, float y);
    Point2f(const Point2f& pt);

    float x, y;
};
```

这个类有以下几个构造函数和成员变量：

- `Point2f()`: 默认构造函数，会将坐标点初始化为 (0, 0)。
- `Point2f(float x, float y)`: 构造函数，传入 x 和 y 坐标值。
- `Point2f(const Point2f& pt)`: 复制构造函数，用于创建一个已有点的副本。
- `x` 和 `y`: 浮点数类型的成员变量，表示点的 x 和 y 坐标。

下面是一个示例代码，演示了如何使用 `cv::Point2f` 类：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个点对象
    cv::Point2f pt1(10.5, 20.3);

    // 访问点的坐标
    float x = pt1.x;
    float y = pt1.y;

    // 输出点的坐标
    std::cout << "Point coordinates: (" << x << ", " << y << ")" << std::endl;

    // 创建另一个点对象
    cv::Point2f pt2(5.2, 8.7);

    // 使用复制构造函数创建新点对象
    cv::Point2f pt3 = pt2;

    return 0;
}
```

`cv::Point2f` 类在许多情况下都非常有用，特别是当需要使用浮点坐标来精确表示像素位置、特征点位置等时。它是 OpenCV 中基本的数据结构之一，用于处理图像中的点和坐标。

---

## cv::RotatedRect

在 OpenCV 中，`cv::RotatedRect` 是一个用于表示旋转矩形的类。旋转矩形是一个带有角度的矩形，通常用于表示在图像中检测到的旋转物体的边界框。

`cv::RotatedRect` 的定义位于 `opencv2/core/types.hpp` 头文件中，其结构如下：

```cpp
class RotatedRect {
public:
    RotatedRect();
    RotatedRect(const Point2f& center, const Size2f& size, float angle);

    Point2f center;  // 旋转矩形中心坐标
    Size2f size;     // 旋转矩形的尺寸，宽度和高度
    float angle;     // 旋转矩形的角度（以度为单位）
};
```

这个类有以下几个构造函数和成员变量：

- `RotatedRect()`: 默认构造函数，会将旋转矩形的属性初始化为默认值。
- `RotatedRect(const Point2f& center, const Size2f& size, float angle)`: 构造函数，传入旋转矩形的中心坐标、尺寸和角度。

成员变量解释：
- `center`: 一个 `Point2f` 类型的成员变量，表示旋转矩形的中心坐标。
- `size`: 一个 `Size2f` 类型的成员变量，表示旋转矩形的宽度和高度。
- `angle`: 一个浮点数，表示旋转矩形的角度，单位为度。

下面是一个示例代码，演示了如何使用 `cv::RotatedRect` 类：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::Point2f center(100, 100);
    cv::Size2f size(200, 100);
    float angle = 30.0;

    // 创建一个旋转矩形对象
    cv::RotatedRect rotatedRect(center, size, angle);

    // 访问旋转矩形的属性
    cv::Point2f rectCenter = rotatedRect.center;
    cv::Size2f rectSize = rotatedRect.size;
    float rectAngle = rotatedRect.angle;

    // 输出旋转矩形的属性
    std::cout << "Center: (" << rectCenter.x << ", " << rectCenter.y << ")" << std::endl;
    std::cout << "Size: " << rectSize.width << " x " << rectSize.height << std::endl;
    std::cout << "Angle: " << rectAngle << " degrees" << std::endl;

    return 0;
}
```

`cv::RotatedRect` 类在许多图像处理和计算机视觉任务中非常有用，特别是在需要表示旋转物体的边界框时。它可以帮助您存储和操作旋转矩形的属性，以及在图像中进行相关操作，例如绘制旋转矩形、计算旋转矩形的边界框等。

---

## cv::Point

在 OpenCV 库中，`cv::Point` 是一个用于表示二维坐标点的类。它通常用于图像处理和计算机视觉中，用于表示像素位置、图像上的点、图像中的特征点等。

`cv::Point` 的定义位于 `opencv2/core.hpp` 头文件中，其结构如下：

```cpp
class Point {
public:
    Point();
    Point(int x, int y);
    Point(const Point& pt);

    int x, y;
};
```

这个类有以下几个构造函数和成员变量：

- `Point()`: 默认构造函数，会将坐标点初始化为 (0, 0)。
- `Point(int x, int y)`: 构造函数，传入 x 和 y 坐标值。
- `Point(const Point& pt)`: 复制构造函数，用于创建一个已有点的副本。
- `x` 和 `y`: 整数类型的成员变量，表示点的 x 和 y 坐标。

下面是一个示例代码，演示了如何使用 `cv::Point` 类：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个点对象
    cv::Point pt1(10, 20);

    // 访问点的坐标
    int x = pt1.x;
    int y = pt1.y;

    // 输出点的坐标
    std::cout << "Point coordinates: (" << x << ", " << y << ")" << std::endl;

    // 创建另一个点对象
    cv::Point pt2(5, 8);

    // 使用复制构造函数创建新点对象
    cv::Point pt3 = pt2;

    return 0;
}
```

`cv::Point` 类在许多情况下都非常有用，例如在图像上标记特定位置、表示特征点、进行坐标计算等。它是 OpenCV 中基本的数据结构之一，用于处理图像中的点和坐标。

---

## cv::Scalar 

`cv::Scalar` 是 OpenCV 库中的一个类，用于表示一个包含四个分量的向量，通常用于表示颜色、像素值等。这四个分量可以分别表示蓝色、绿色、红色和透明度（BGR-A）。

这个类在图像处理中经常用于设置颜色、像素值等。每个分量都是一个双精度浮点数，通常取值范围是 0 到 255，表示一个 8 位无符号整数值的颜色分量。

下面是一个简单的例子，演示了如何使用 `cv::Scalar` 来创建颜色以及像素值：

```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个红色的 Scalar 对象
    cv::Scalar redColor(0, 0, 255);

    // 创建一个白色的 Scalar 对象
    cv::Scalar whiteColor(255, 255, 255);

    // 输出 Scalar 对象的分量值
    std::cout << "Red Color: " << redColor[0] << ", " << redColor[1] << ", " << redColor[2] << std::endl;

    // 创建一个像素值为 (100, 150, 200) 的 Scalar 对象
    cv::Scalar pixelValue(100, 150, 200);

    return 0;
}
```

需要注意的是，这里提供的颜色顺序是 BGR，与一般人们常见的 RGB 顺序不同。另外，如果不需要使用透明度，可以忽略透明度分量。

`cv::Scalar` 通常用于填充矩形、绘制文本、设置像素值等场景，方便地表示颜色和值。在图像处理和计算机视觉领域中，`cv::Scalar` 是一个很有用的工具，使颜色和值的处理变得简单且易于理解。

---

## cv::Mat 

+ 简介：
  + cv::Mat 是 OpenCV 库中表示图像和矩阵的核心数据结构之一。它是一个多维数组，可以存储和操作图像、矩阵和其他类型的数据

+ 原型：
```cpp
class Mat {
public:
    // 构造函数
    Mat();
    Mat(int rows, int cols, int type);
    Mat(Size size, int type);
    Mat(int rows, int cols, int type, const Scalar& scalar);
    Mat(Size size, int type, const Scalar& scalar);
    Mat(const Mat& m);

    // 数据访问
    int rows;
    int cols;
    int type();
    int channels();
    int depth();
    size_t elemSize();
    size_t elemSize1();
    bool empty();
    void release();
    Mat clone() const;
    Mat& operator=(const Mat& m);
    Mat operator()(const Range& rowRange, const Range& colRange) const;
    Mat row(int y) const;
    Mat col(int x) const;
    Mat rowRange(int startrow, int endrow) const;
    Mat colRange(int startcol, int endcol) const;
    Mat reshape(int cn, int rows = 0) const;

    // 数据操作
    void create(int rows, int cols, int type);
    void create(Size size, int type);
    void convertTo(Mat& m, int rtype, double alpha = 1, double beta = 0) const;
    void copyTo(Mat& m) const;
    void copyTo(Mat& m, const Mat& mask) const;
    void assignTo(Mat& m, int type = -1) const;
    void swap(Mat& m);
    Mat& setTo(const Scalar& scalar, const Mat& mask = Mat());
    Mat& setTo(const Scalar& scalar, const Mat& mask);
    Mat reshape(int cn, int newndims, const int* newsz) const;

    // 图像加载和保存
    static Mat imread(const String& filename, int flags = IMREAD_COLOR);
    bool imwrite(const String& filename, const std::vector<int>& params = std::vector<int>()) const;

    // 其他函数和操作符重载
    // ...
};
```

+ 详解：
  + cv::Mat 的主要特点和功能包括
    + 多维数组表示：cv::Mat 可以表示多维数组，如二维图像（矩阵）和三维图像（彩色图像）等。
    + 数据访问：可以通过 rows 和 cols 成员变量获取矩阵的行数和列数，通过 at 成员函数或数组索引操作符 [] 来访问和修改矩阵中的元素。
    + 数据操作：可以对 cv::Mat 执行各种数据操作，如创建矩阵、复制矩阵、转换数据类型、调整大小、提取子矩阵等
    + 图像加载和保存：通过 imread 和 imwrite 函数可以加载和保存图像文件
    + 运算符重载：cv::Mat 支持许多运算符重载，如加法、减法、乘法等，以及与其他 cv::Mat 对象之间的操作

+ 注：
  + 需要注意的是，cv::Mat 的默认构造函数创建了一个空的矩阵对象，必须使用 create 函数来分配内存空间并指定矩阵的大小和数据类型
  + 使用 cv::Mat，你可以进行各种图像处理和计算机视觉任务，如图像加载、图像处理、特征提取、模式识别等。了解和熟悉 cv::Mat 的功能和使用方法是使用 OpenCV 进行图像处理和计算机视觉开发的基础。你可以参考 OpenCV 官方文档和示例代码，深入学习关于 cv::Mat 的更多信息和用法

---

## cv::imread

+ 简介：
  + cv::imread() 是 OpenCV 库中用于读取图像文件的函数。它接受图像文件的路径作为输入，并返回一个表示图像的 cv::Mat 对象

+ 原型：
```cpp
cv::Mat cv::imread(const cv::String& filename, int flags = cv::IMREAD_COLOR);
```

+ 参数：
  + filename：图像文件的路径
  + flags（可选）：指定读取图像的方式，默认值为 cv::IMREAD_COLOR。可以使用以下标志来指定读取图像的颜色模式
    + cv::IMREAD_COLOR：读取彩色图像（默认值）
    + cv::IMREAD_GRAYSCALE：将图像以灰度模式读取
    + cv::IMREAD_UNCHANGED：以原始图像的包含 alpha 通道的方式读取

+ 返回值：
  + 如果成功读取图像文件，则返回一个 cv::Mat 对象，表示读取到的图像数据
  + 如果无法读取图像文件，返回一个空的 cv::Mat 对象

+ 示例：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像文件
    cv::Mat image = cv::imread("image.jpg");

    if (image.empty()) {
        std::cout << "无法加载图像文件" << std::endl;
        return -1;
    }

    // 处理图像...

    return 0;
}
```

+ 注：
  + 在上述示例中，cv::imread() 函数尝试加载名为 "image.jpg" 的图像文件。如果成功读取图像文件，将返回一个非空的 cv::Mat 对象，可以对其进行进一步的图像处理操作
  + 需要注意的是，cv::imread() 函数需要提供正确的图像文件路径，并确保所使用的图像格式与 OpenCV 支持的图像格式相匹配。如果无法加载图像文件，可以检查文件路径是否正确、文件是否存在以及文件格式是否受支持
  + 另外，OpenCV 还提供了其他的图像读取函数，如 cv::imdecode() 用于从内存中读取图像数据，以及 cv::VideoCapture 类用于读取视频文件或摄像头视频流。你可以根据具体的需求选择适当的图像读取方法

---

## cv::imwrite

+ 简介：
  + cv::imwrite() 是 OpenCV 库中用于将图像数据保存到文件的函数。它接受图像数据和目标文件路径作为输入，并将图像数据写入指定的文件

+ 原型：
```cpp
bool cv::imwrite(const cv::String& filename, const cv::Mat& image, const std::vector<int>& params = std::vector<int>());
```

+ 参数：
  + filename：保存图像的文件路径。
  + image：要保存的图像数据，为一个 cv::Mat 对象。
  + params（可选）：保存图像的参数，为一个整数向量。参数可以控制图像的压缩格式、质量等。常用的参数包括：
    + cv::IMWRITE_JPEG_QUALITY：指定 JPEG 格式的图像质量，取值范围为 0 到 100。
    + cv::IMWRITE_PNG_COMPRESSION：指定 PNG 格式的压缩级别，取值范围为 0 到 9，其中 0 表示无压缩，9 表示最高压缩

+ 返回值：
  + 如果成功将图像数据写入文件，则返回 true
  + 如果无法将图像数据写入文件，则返回 false

+ 示例：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像文件
    cv::Mat image = cv::imread("image.jpg");

    if (image.empty()) {
        std::cout << "无法加载图像文件" << std::endl;
        return -1;
    }

    // 保存图像文件
    bool result = cv::imwrite("output.jpg", image);

    if (result) {
        std::cout << "图像保存成功" << std::endl;
    } else {
        std::cout << "图像保存失败" << std::endl;
    }

    return 0;
}
```

+ 注：
  + 在上述示例中，cv::imread() 函数尝试加载名为 "image.jpg" 的图像文件，然后将图像数据存储在 cv::Mat 对象 image 中。接下来，通过调用 cv::imwrite() 函数，将图像数据保存到名为 "output.jpg" 的文件中
  + 需要注意的是，cv::imwrite() 函数需要提供正确的文件路径，并确保所指定的文件格式与 OpenCV 支持的图像格式相匹配。如果无法将图像数据写入文件，可以检查文件路径是否正确、文件是否可写以及图像数据是否有效
  + 另外，OpenCV 还提供了其他的图像保存函数，如 cv::imencode() 用于将图像数据编码为内存缓冲区，并将其保存为图像文件。你可以根据具体的需求选择适当的图像保存方法

---

## cv::rectangle

+ 简介：
  + cv::rectangle() 是 OpenCV 库中用于在图像上绘制矩形的函数。它接受一个图像对象和矩形参数，并在图像上绘制指定的矩形

+ 原型：
```cpp
void cv::rectangle(cv::Mat& img, const cv::Rect& rect, const cv::Scalar& color, int thickness = 1, int lineType = cv::LINE_8, int shift = 0);
```

+ 参数：
  + img：要在其上绘制矩形的图像对象，为一个 cv::Mat 对象。
  + rect：矩形的位置和大小，为一个 cv::Rect 对象。
  + color：矩形的颜色，为一个 cv::Scalar 对象，可以是 BGR 或灰度值。
  + thickness（可选）：矩形线条的粗细，默认值为 1。
  + lineType（可选）：线条的类型，默认值为 cv::LINE_8，表示8连通线条。
  + shift（可选）：点坐标的小数位数，默认值为 0

+ 示例：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个空白图像
    cv::Mat image(300, 400, CV_8UC3, cv::Scalar(255, 255, 255));

    // 绘制矩形
    cv::Rect rect(50, 50, 200, 150);
    cv::Scalar color(0, 0, 255);  // 红色
    int thickness = 2;
    int lineType = cv::LINE_8;
    int shift = 0;
    cv::rectangle(image, rect, color, thickness, lineType, shift);

    // 显示图像
    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;
}
```

+ 注：
  + 在上述示例中，我们创建了一个大小为 300x400 像素、颜色为白色的图像 image。然后，我们定义了一个矩形 rect，它位于图像上的 (50, 50) 点，宽度为 200，高度为 150。我们将矩形的颜色设置为红色，线条粗细为 2。最后，我们使用 cv::rectangle() 函数在图像上绘制矩形
  + 需要注意的是，cv::rectangle() 函数会在原始图像对象上进行绘制，因此在函数调用之前，确保图像对象已经被创建并且是可写的
  + 除了 cv::rectangle()，OpenCV 还提供了其他的绘制函数，如绘制直线、圆形、多边形等。你可以根据具体的需求选择适当的绘制函数，并使用不同的参数来调整绘制效果

---

## cv::imshow 

+ 简介：
  + cv::imshow() 是 OpenCV 库中用于显示图像的函数。它接受一个窗口名称和图像对象，并在一个新的窗口中显示图像

+ 原型：
```cpp
void cv::imshow(const cv::String& winname, const cv::Mat& image);
```

+ 参数：
  + winname：窗口的名称，为一个字符串。
  + image：要显示的图像数据，为一个 cv::Mat 对象

+ 示例：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像文件
    cv::Mat image = cv::imread("image.jpg");

    if (image.empty()) {
        std::cout << "无法加载图像文件" << std::endl;
        return -1;
    }

    // 显示图像
    cv::imshow("Image", image);

    // 等待按下任意按键
    cv::waitKey(0);

}
```

+ 注：
  + 在上述示例中，我们使用 cv::imread() 函数加载一个名为 "image.jpg" 的图像文件，并将图像数据存储在 cv::Mat 对象 image 中。然后，我们调用 cv::imshow() 函数，将图像显示在一个名为 "Image" 的窗口中
  + 需要注意的是，cv::imshow() 函数会创建一个新的窗口来显示图像。窗口名称是唯一的，可以使用不同的名称来创建多个窗口并显示不同的图像。如果窗口名称已经存在，则会将新的图像显示在现有窗口中
  + 在调用 cv::imshow() 函数后，通常需要调用 cv::waitKey() 函数来等待用户按下按键。这样可以使窗口保持打开状态，直到用户关闭窗口或按下按键。cv::waitKey() 函数返回按下的键的 ASCII 值，如果没有按下按键，则返回 -1
  + 除了 cv::imshow()，OpenCV 还提供了其他的图像显示和交互函数，如调整窗口大小、绘制图形、注册鼠标事件等。你可以根据具体的需求选择适当的函数，并使用相关的参数和事件处理机制来进行图像显示和交互操作

---

## namedWindow

+ 简介：
  + cv::namedWindow() 是 OpenCV 库中用于创建一个带有指定名称的窗口的函数。它可以用于显示图像、绘制图形和接收用户交互事件

+ 原型：
```cpp
void cv::namedWindow(const cv::String& winname, int flags = cv::WINDOW_AUTOSIZE);
```

+ 参数：
  + winname：窗口的名称，为一个字符串。
  + flags（可选）：窗口的属性标志，用于指定窗口的行为和外观。常用的标志包括：
    + cv::WINDOW_NORMAL：创建一个可调整大小的窗口。
    + cv::WINDOW_AUTOSIZE：创建一个自适应大小的窗口，窗口大小将根据图像大小自动调整

+ 示例：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 读取图像文件
    cv::Mat image = cv::imread("image.jpg");

    if (image.empty()) {
        std::cout << "无法加载图像文件" << std::endl;
        return -1;
    }

    // 创建一个名为 "Image" 的窗口
    cv::namedWindow("Image", cv::WINDOW_NORMAL);

    // 显示图像
    cv::imshow("Image", image);

    // 等待按下任意按键
    cv::waitKey(0);

    return 0;
}
```

+ 注：
  + 在上述示例中，我们使用 cv::imread() 函数加载一个名为 "image.jpg" 的图像文件，并将图像数据存储在 cv::Mat 对象 image 中。然后，我们调用 cv::namedWindow() 函数，创建一个名为 "Image" 的窗口。通过设置 flags 参数为 cv::WINDOW_NORMAL，我们可以创建一个可调整大小的窗口
  + 接下来，我们调用 cv::imshow() 函数将图像显示在 "Image" 窗口中。最后，通过调用 cv::waitKey() 函数等待按键，以保持窗口打开状态，直到用户关闭窗口或按下按键
  + 使用 cv::namedWindow() 函数可以为窗口指定名称，并设置窗口的属性标志以控制其行为和外观。这样可以在显示多个图像时，为每个图像创建独立的窗口，并根据需要进行大小调整

---

## cv::destroyWindow

+ 简介：
  + cv::destroyWindow() 是 OpenCV 库中用于关闭指定名称的窗口的函数。它可以用于关闭已创建的窗口并释放与窗口相关的资源

+ 原型：
```cpp
void cv::destroyWindow(const cv::String& winname);
```

+ 参数：
  + winname：要关闭的窗口的名称，为一个字符串

+ 示例：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个名为 "Image" 的窗口
    cv::namedWindow("Image");

    // ... 一些图像处理操作 ...

    // 关闭名为 "Image" 的窗口
    cv::destroyWindow("Image");

    return 0;
}
```

+ 注：
  + 在上述示例中，我们通过调用 cv::namedWindow() 函数创建了一个名为 "Image" 的窗口。然后，在执行一些图像处理操作后，我们通过调用 cv::destroyWindow() 函数关闭了名为 "Image" 的窗口
  + 使用 cv::destroyWindow() 函数可以在不需要显示某个窗口时，将其关闭并释放相关资源。这对于图像处理过程中动态创建和关闭窗口非常有用
  + 除了关闭单个窗口，还可以使用 cv::destroyAllWindows() 函数关闭所有已创建的窗口，释放所有窗口相关的资源
  + 请注意，窗口的创建和销毁是在 OpenCV 的 HighGUI 模块中进行的，因此在使用这些函数之前，需要确保已经正确链接和初始化了 OpenCV 库

---

## cv::waitKey

+ 简介：
  + cv::waitKey() 是 OpenCV 库中用于等待用户按下按键的函数。它在程序执行过程中暂停，并等待用户按下键盘上的按键

+ 原型：
```cpp
int cv::waitKey(int delay = 0);
```

+ 参数：
  + delay（可选）：等待按键的时间（以毫秒为单位），默认值为 0。如果设置为正整数，表示等待指定的时间后，如果没有按键按下，则函数将继续执行。如果设置为 0，则函数将无限期等待按键的按下

+ 返回值：
  + 返回按下的键的 ASCII 值。
  + 如果在指定的时间内没有按键按下，或者未能获取按键的值，则返回 -1。

+ 示例：
```cpp
#include <opencv2/opencv.hpp>

int main() {
    // 创建一个名为 "Image" 的窗口
    cv::namedWindow("Image");

    // 显示图像
    cv::Mat image = cv::imread("image.jpg");
    cv::imshow("Image", image);

    // 等待按下任意按键
    int key = cv::waitKey(0);

    // 输出按下的键的 ASCII 值
    std::cout << "按下的键的 ASCII 值: " << key << std::endl;

    return 0;
}
```

+ 注：
  + 在上述示例中，我们通过调用 cv::namedWindow() 函数创建了一个名为 "Image" 的窗口，并通过 cv::imshow() 函数显示了一张图像。然后，我们调用 cv::waitKey() 函数，等待用户按下键盘上的按键。将 delay 参数设置为 0 表示无限期等待按键按下
  + 当用户按下按键时，cv::waitKey() 函数将返回按键的 ASCII 值。我们可以通过输出语句将其打印出来。如果没有按键按下或无法获取按键的值，函数将返回 -1
  + 需要注意的是，调用 cv::waitKey() 函数会使程序暂停执行，直到用户按下按键或达到指定的等待时间。这通常与图像显示和交互操作配合使用，以保持窗口打开状态并等待用户操作
  + 除了返回按键的 ASCII 值，cv::waitKey() 函数还可以用于实现视频播放和实时图像处理等应用，其中按键事件用于控制程序的流程和操作