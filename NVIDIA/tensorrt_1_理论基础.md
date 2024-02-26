## 简介

+ tensorrt库

## C++ tensorrt是什么

TensorRT（Tensor Runtime）是由 NVIDIA 开发的用于高性能深度学习推理（inference）的库。它主要用于加速深度学习模型在 NVIDIA GPU 上的推理阶段，以提高模型的实时性能。

TensorRT 提供了许多优化技术，以减少深度学习模型推理的计算和内存开销。它通过使用精确的数值计算、层融合（layer fusion）、动态 Tensor 网络（dynamic tensor network）、深度学习加速库（cuDNN）、自动混合精度（automatic mixed precision）等技术，提供高效的推理加速。

TensorRT 支持多种深度学习框架，包括 TensorFlow、PyTorch、ONNX（Open Neural Network Exchange）等。你可以使用 TensorRT 将经过训练的深度学习模型转换为 TensorRT 可以高效执行的格式，以利用 GPU 进行快速推理。

以下是 TensorRT 的一些主要特性：

1. **快速推理：** TensorRT 通过 GPU 加速深度学习推理，提供高性能的模型执行。

2. **精确数值计算：** TensorRT 支持对模型进行精确数值计算，以在不牺牲模型精度的情况下提高推理速度。

3. **层融合：** TensorRT 可以自动融合相邻层，减少计算和内存开销。

4. **支持多种框架：** TensorRT 提供用于与多种深度学习框架集成的工具，包括 TensorFlow、PyTorch、ONNX 等。

5. **动态 Tensor 网络：** TensorRT 支持构建动态的 Tensor 网络，适用于需要在推理期间动态改变形状的模型。

TensorRT 的使用通常涉及到以下几个步骤：

1. **创建和训练模型：** 使用深度学习框架创建和训练深度学习模型。

2. **模型转换：** 使用 TensorRT 提供的工具将训练好的模型转换为 TensorRT 可以高效执行的格式。

3. **加载和推理：** 在 C++ 或其他支持的语言中加载 TensorRT 格式的模型并进行推理。

TensorRT 是用于加速深度学习推理的强大工具，尤其在实时应用、嵌入式系统和边缘计算等场景中具有重要作用。

## C++ tensorrt 库 详解

TensorRT 是 NVIDIA 提供的深度学习推理库，专为在 NVIDIA GPU 上进行深度学习模型的加速而设计。TensorRT 提供了一系列工具和优化技术，以在推理阶段获得高性能、低延迟的模型执行。以下是关于 TensorRT 库的一些详细信息：

### TensorRT 的主要特性：

1. **快速推理：** TensorRT 通过 GPU 加速深度学习推理，提供高性能的模型执行。它针对 NVIDIA GPU 的架构进行了优化，充分利用了 GPU 的并行计算能力。

2. **精确数值计算：** TensorRT 支持深度学习模型的精确数值计算，同时考虑到模型推理过程中的计算精度和效率。

3. **层融合：** TensorRT 可以自动融合相邻层，减少计算和内存开销。这种层融合技术有助于减小模型的计算图，提高推理性能。

4. **多精度计算：** TensorRT 支持多种精度计算，包括 FP32、FP16 和 INT8。可以根据模型的需求选择合适的精度，以在保持精度的同时提高计算性能。

5. **层和操作库：** TensorRT 提供了包括卷积、归一化、激活函数等在内的一系列层和操作库，以满足不同模型结构的推理需求。

6. **支持多种框架：** TensorRT 支持多种深度学习框架，包括 TensorFlow、PyTorch、ONNX 等。通过支持多种框架，TensorRT 提供了灵活性，使用户能够在不同框架之间无缝转换和使用模型。

7. **动态 Tensor 网络：** TensorRT 支持构建动态的 Tensor 网络，适用于需要在推理期间动态改变形状的模型。

### TensorRT 的使用流程：

1. **创建和训练模型：** 使用深度学习框架（例如 TensorFlow、PyTorch）创建和训练深度学习模型。

2. **模型转换：** 使用 TensorRT 提供的工具将训练好的模型转换为 TensorRT 可以高效执行的格式。这通常涉及到使用 TensorRT 的 Python API 进行模型转换。

3. **TensorRT 推理引擎构建：** 使用 C++ 或其他支持的语言，在运行时加载 TensorRT 格式的模型并构建 TensorRT 推理引擎。推理引擎是 TensorRT 用于高效执行模型的核心组件。

4. **输入数据传递和推理：** 将输入数据传递给 TensorRT 推理引擎，并执行推理操作。TensorRT 会在 GPU 上对输入数据进行并行计算，并输出模型的推理结果。

5. **清理资源：** 在推理完成后，释放分配的 GPU 和 CPU 资源，以确保良好的系统资源管理。

### TensorRT C++ API 使用示例：

以下是一个简化的 TensorRT C++ API 使用示例，展示了加载 TensorRT 模型并进行推理的基本步骤：

```cpp
#include <iostream>
#include <fstream>
#include <NvInfer.h>

int main() {
    // 初始化 TensorRT
    nvinfer1::IRuntime* runtime = nvinfer1::createInferRuntime(gLogger);

    // 从文件中加载 TensorRT 模型
    const char* trtModelPath = "path/to/your/model.plan";
    std::ifstream trtModelStream(trtModelPath, std::ios::binary);
    trtModelStream.seekg(0, trtModelStream.end);
    const int modelSize = trtModelStream.tellg();
    trtModelStream.seekg(0, trtModelStream.beg);
    std::vector<char> modelData(modelSize);
    trtModelStream.read(modelData.data(), modelSize);

    nvinfer1::ICudaEngine* engine = runtime->deserializeCudaEngine(modelData.data(), modelSize, nullptr);

    // 创建执行上下文
    nvinfer1::IExecutionContext* context = engine->createExecutionContext();

    // 准备输入数据和输出缓冲区
    float inputData[INPUT_SIZE]; // INPUT_SIZE 是模型期望的输入大小
    float outputData[OUTPUT_SIZE]; // OUTPUT_SIZE 是模型期望的输出大小

    // 分配 GPU 内存并将输入数据传输到 GPU
    void* gpuInputBuffer;
    cudaMalloc(&gpuInputBuffer, INPUT_SIZE * sizeof(float));
    cudaMemcpy(gpuInputBuffer, inputData, INPUT_SIZE * sizeof(float), cudaMemcpyHostToDevice);

    // 分配 GPU 内存用于输出
    void* gpuOutputBuffer;
    cudaMalloc(&gpuOutputBuffer, OUTPUT_SIZE * sizeof(float));

    // 执行推理
    context->execute(1, &gpuInputBuffer, &gpuOutputBuffer, nullptr, nullptr);

    // 将输出数据从 GPU 复制回主机
    cudaMemcpy(outputData, gpuOutputBuffer, OUTPUT_SIZE * sizeof(float), cudaMemcpyDeviceToHost);

    // 处理输出数据...

    // 清理资源
    cudaFree(gpuInputBuffer);
    cudaFree(gpuOutputBuffer);
    context->destroy();
    engine->destroy();
    runtime->destroy();

    return 0;
}
```

请注意，实际的使用场景可能会更加复杂，具体的实现可能需要更多的代码，特别是在处理不同类型和形状的输入数据时。确保查阅 TensorRT 的文档和示例，以获得详细的使用说明。