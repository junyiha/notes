## 简介

+ OpenCV 常用的函数

## OpenCV cv::imdecode() 函数 详解 中文

`cv::imdecode()` 是 OpenCV 库中的一个函数，用于将图像数据解码为 OpenCV 中的 `cv::Mat` 对象。该函数通常用于从内存中读取图像数据，而不是从文件中读取。

以下是 `cv::imdecode()` 函数的一些关键参数及其解释：

- **参数1 (`buf`)：** 这是一个包含图像数据的缓冲区。通常情况下，这是一个 `uchar` 类型的数组，存储着图像的原始数据。

- **参数2 (`flags`)：** 这是一个整数参数，用于指定如何解码图像。常用的标志包括 `cv::IMREAD_COLOR`（默认值，将图像以BGR颜色格式加载）、`cv::IMREAD_GRAYSCALE`（将图像以灰度格式加载）和 `cv::IMREAD_UNCHANGED`（加载图像的所有通道，包括 Alpha 通道）。

- **返回值：** 函数返回一个 `cv::Mat` 对象，该对象包含解码后的图像数据。

`cv::imdecode()` 函数的调用示例：

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 读取图像数据到内存中
    std::vector<uchar> data; // 图像数据的缓冲区
    // 假设 data 被填充了图像数据

    // 解码图像数据
    cv::Mat image = cv::imdecode(data, cv::IMREAD_COLOR);

    // 检查图像是否成功解码
    if (!image.empty()) {
        // 成功加载图像，进行进一步的处理
        cv::imshow("Decoded Image", image);
        cv::waitKey(0);
    } else {
        // 加载失败
        std::cerr << "Failed to decode image." << std::endl;
    }

    return 0;
}
```

这个例子演示了如何使用 `cv::imdecode()` 函数将图像数据解码为 `cv::Mat` 对象，并在图像成功加载时显示它。

## OpenCV cv::imencode() 详解

`cv::imencode()` 函数是 OpenCV 库中用于将图像编码为特定格式（如JPEG、PNG等）的函数。它可以将 `cv::Mat` 中存储的图像数据编码为指定格式的图像，并将编码后的图像数据存储到内存缓冲区中。

该函数的原型为：

```cpp
bool imencode(const String& ext, InputArray img, std::vector<uchar>& buf, const std::vector<int>& params = std::vector<int>());
```

其中参数含义如下：

- `ext`：字符串参数，用于指定输出图像的格式，例如 `".jpg"`、`".png"` 等。
- `img`：`cv::Mat` 对象，包含待编码的图像数据。
- `buf`：`std::vector<uchar>` 类型的输出参数，用于存储编码后的图像数据。
- `params`（可选）：一个可选的参数向量，用于指定图像编码的参数，如 JPEG 质量、PNG 压缩级别等。具体参数因图像格式而异。

下面是一些示例代码，展示了如何使用 `cv::imencode()` 函数将图像编码为 JPEG 格式并存储到内存中的 `std::vector<uchar>` 中：

```cpp
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
    cv::Mat image = cv::imread("path_to_your_image.jpg");

    if (image.empty()) {
        std::cout << "无法读取图像文件\n";
        return -1;
    }

    std::vector<uchar> buffer;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY); // 设置 JPG 质量
    params.push_back(95); // 设置 JPG 图像质量，可根据需要调整

    // 将图像编码为 JPG 格式并保存到内存
    bool success = cv::imencode(".jpg", image, buffer, params);

    if (success) {
        // buffer 中现在存储了编码后的 JPG 数据，可以进行保存或其他处理
        // 例如，将内存中的 JPG 数据保存到文件
        FILE *file = fopen("saved_image.jpg", "wb");
        if (file != NULL) {
            fwrite(buffer.data(), sizeof(uchar), buffer.size(), file);
            fclose(file);
            std::cout << "图像保存成功\n";
        } else {
            std::cout << "无法保存图像\n";
            return -1;
        }
    } else {
        std::cout << "图像编码失败\n";
        return -1;
    }

    return 0;
}
```

在示例中，`cv::imencode()` 将 `cv::Mat` 中的图像数据编码为 JPG 格式，并将编码后的数据存储在 `buffer` 中。之后，将 `buffer` 中的数据写入文件 `"saved_image.jpg"`。

要注意，在使用 `cv::imencode()` 函数之前，需要确保已经正确读取了图像数据并存储在 `cv::Mat` 对象中。