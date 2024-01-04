## 简介

+ OpenCV 常用的函数

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