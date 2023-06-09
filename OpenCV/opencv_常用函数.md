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