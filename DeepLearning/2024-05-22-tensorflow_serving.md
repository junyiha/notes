---
category: DeepLearning
date: 2024-05-22 09:00:00 +0800
layout: post
title: tensorflow_serving
tag: DL
---
## 简介

+ tensorflow serving库相关笔记

## TensorFlow Serving是什么

+ TensorFlow Serving 是一个适用于机器学习模型的灵活、高性能应用系统，专为生产环境而设计。借助 TensorFlow Serving，您可以轻松部署新算法和实验，同时保留相同的服务器架构和 API。TensorFlow Serving 提供与 TensorFlow 模型的开箱即用型集成，但也可以轻松扩展以应用其他类型的模型和数据。

## C++ tensorflow serving库 详解

TensorFlow Serving 是一个用于部署机器学习模型的开源库，它提供了一个高性能、灵活的方式来将训练好的 TensorFlow 模型部署到生产环境中，以便进行实时预测。虽然 TensorFlow Serving 主要是用 C++ 实现的，但它也提供了 Python API 以方便用户使用。

下面是对 TensorFlow Serving C++ 库的详细介绍：

1. **核心功能**：
   - 加载和管理模型：TensorFlow Serving 能够加载和管理训练好的 TensorFlow 模型，包括 SavedModel 格式。
   - 提供预测服务：一旦模型被加载，TensorFlow Serving 可以为客户端提供实时的预测服务，支持单个或批量请求。
   - 高性能和可扩展性：TensorFlow Serving 在设计上注重性能和可扩展性，能够处理高并发的请求并保持低延迟。

2. **架构**：
   - TensorFlow Serving 的架构主要由三个组件组成：Servable、Loader 和 Servable Manager。
   - Servable 是指 TensorFlow 模型的一种抽象，它代表了一个可部署的模型或模型的版本。
   - Loader 负责加载 Servable，并在需要时将其初始化或卸载。
   - Servable Manager 负责管理 Servable 的生命周期，包括加载、卸载和路由请求等。

3. **部署流程**：
   - 准备模型：首先需要使用 TensorFlow 训练模型，并将其保存为 SavedModel 格式。
   - 配置 TensorFlow Serving：创建一个模型配置文件，指定模型的路径、输入和输出等信息。
   - 启动 TensorFlow Serving：运行 TensorFlow Serving 服务器，并指定模型配置文件。
   - 发送请求：客户端向 TensorFlow Serving 发送预测请求，服务器返回预测结果。

4. **使用示例**：
   下面是一个简单的 TensorFlow Serving C++ 应用示例，假设我们已经有一个名为 `my_model` 的 SavedModel：

   ```cpp
   #include <iostream>
   #include <grpcpp/grpcpp.h>
   #include "tensorflow_serving/apis/prediction_service.grpc.pb.h"

   using grpc::Channel;
   using grpc::ClientContext;
   using grpc::Status;
   using tensorflow::serving::PredictRequest;
   using tensorflow::serving::PredictResponse;
   using tensorflow::serving::PredictionService;

   class TensorFlowServingClient {
   public:
       TensorFlowServingClient(std::shared_ptr<Channel> channel)
           : stub_(PredictionService::NewStub(channel)) {}

       // 发送预测请求
       void Predict() {
           PredictRequest request;
           PredictResponse response;
           ClientContext context;

           // 设置输入数据
           // request.mutable_model_spec()->set_name("my_model");
           // 添加输入数据
           // request.mutable_inputs()->...;

           // 发送预测请求
           Status status = stub_->Predict(&context, request, &response);

           // 处理预测结果
           if (status.ok()) {
               // 处理 response 中的输出结果
           } else {
               std::cerr << "RPC failed: " << status.error_message() << std::endl;
           }
       }

   private:
       std::unique_ptr<PredictionService::Stub> stub_;
   };

   int main() {
       // 创建 TensorFlow Serving 客户端
       TensorFlowServingClient client(grpc::CreateChannel("localhost:8500", grpc::InsecureChannelCredentials()));

       // 发送预测请求
       client.Predict();

       return 0;
   }
   ```

   该示例演示了如何创建一个 TensorFlow Serving 客户端，并发送预测请求。需要注意的是，你需要根据实际情况修改模型的名称、输入数据等信息。

总的来说，TensorFlow Serving 提供了一个功能强大的 C++ 库，用于部署 TensorFlow 模型并提供实时预测服务。通过了解其核心功能、架构和部署流程，你可以更好地使用 TensorFlow Serving 来满足你的部署需求。

## SavedModel格式是什么

SavedModel 是 TensorFlow 中用于保存和加载模型的标准格式。它是一种可移植、可恢复的模型表示形式，可以轻松地在不同的平台上进行部署和共享。SavedModel 以文件夹的形式存储，其中包含了模型的结构、权重参数、计算图以及其他相关的元数据。

SavedModel 主要由两个部分组成：

1. **模型图（GraphDef）**：模型的计算图以 Protocol Buffers 格式保存在名为 `saved_model.pb` 的文件中。计算图定义了模型的结构，包括输入、输出、各种操作（如张量运算、变量等）以及操作之间的连接关系。

2. **变量和资源**：模型的权重参数、变量和其他资源以二进制格式保存在名为 `variables/` 的文件夹中。这些文件包含了模型的具体参数值，用于在加载模型时恢复模型的状态。

除了这两个基本部分之外，SavedModel 还可以包含其他的元数据信息，例如模型的签名信息（用于描述模型的输入和输出）、运行配置、版本信息等。

SavedModel 的优点在于它具有跨平台和版本控制的能力，可以在不同的 TensorFlow 版本和不同的硬件平台上进行部署和加载。这使得 SavedModel 成为了 TensorFlow 模型部署和共享的标准格式，被广泛应用于生产环境中。

## C++ tensorflow serving加载onnx模型

TensorFlow Serving 最初设计用于加载和提供 TensorFlow 模型的预测服务，但它也支持加载其他格式的模型，包括 ONNX（Open Neural Network Exchange）格式的模型。ONNX 是一种开放的标准，用于表示深度学习模型，它允许用户在不同的深度学习框架之间交换模型，并在不同的硬件平台上运行这些模型。

要在 TensorFlow Serving 中加载 ONNX 模型，你需要先将 ONNX 模型转换为 TensorFlow 的 SavedModel 格式，然后再使用 TensorFlow Serving 加载 SavedModel。以下是一个大致的步骤：

1. **将 ONNX 模型转换为 TensorFlow SavedModel**：
   - 使用 ONNX-TensorFlow 或 onnx-tf 工具将 ONNX 模型转换为 TensorFlow 的 SavedModel 格式。这些工具可以帮助你将 ONNX 模型导入到 TensorFlow 中，并将其保存为 SavedModel 格式。

2. **使用 TensorFlow Serving 加载 SavedModel**：
   - 使用 TensorFlow Serving 的配置文件（通常是 TensorFlow Serving 的 Docker 镜像中的配置文件），将转换后的 SavedModel 添加到配置中。
   - 启动 TensorFlow Serving 服务器，并指定模型配置文件。

下面是一个大致的示例：

```bash
# 1. 将 ONNX 模型转换为 TensorFlow SavedModel
onnx-tf convert -i model.onnx -o saved_model/

# 2. 配置 TensorFlow Serving
# 创建一个模型配置文件，例如 model_config.json，指定模型的路径和类型
{
  "model_version_policy": { "specific": { "versions": { "1": {} } } },
  "model_platform": "tensorflow",
  "name": "onnx_model",
  "base_path": "/path/to/saved_model"
}

# 3. 启动 TensorFlow Serving
docker run -p 8500:8500 -p 8501:8501 --mount type=bind,source=/path/to/model_config.json,target=/models/onnx_model/config.json -t tensorflow/serving
```

这里的关键步骤是将 ONNX 模型转换为 TensorFlow 的 SavedModel 格式，并通过 TensorFlow Serving 的配置文件将 SavedModel 添加到 TensorFlow Serving 中。这样就可以在 TensorFlow Serving 中加载和提供 ONNX 模型的预测服务了。

## docker方式部署(官方示例)

```bash
# Download the TensorFlow Serving Docker image and repo
docker pull tensorflow/serving

git clone https://github.com/tensorflow/serving
# Location of demo models
TESTDATA="$(pwd)/serving/tensorflow_serving/servables/tensorflow/testdata"

# Start TensorFlow Serving container and open the REST API port
docker run -t --rm -p 8501:8501 \
    -v "$TESTDATA/saved_model_half_plus_two_cpu:/models/half_plus_two" \
    -e MODEL_NAME=half_plus_two \
    tensorflow/serving &

# Query the model using the predict API
curl -d '{"instances": [1.0, 2.0, 5.0]}' \
    -X POST http://localhost:8501/v1/models/half_plus_two:predict

# Returns => { "predictions": [2.5, 3.0, 4.5] }
```

## 拉取serving docker image

+ 运行命令
  + docker pull tensorflow/serving

+ tensorflow serving docker历史镜像
  + 地址: https://hub.docker.com/r/tensorflow/serving/tags/

## 从serving docker image 启动一个容器

+ serving images有以下属性
  + 8500 端口服务于gRPC
  + 8501 端口服务于 REST API
  + 可选的环境变量 MODEL_NAME(默认为 model)
  + 可选的环境变量 MODEL_BASE_PATH(默认为 /models)
+ 当 serving image运行一个容器时，其内部实际运行的命令是
```bash
tensorflow_model_server --port=8500 --rest_api_port=8501 \
  --model_name=${MODEL_NAME} --model_base_path=${MODEL_BASE_PATH}/${MODEL_NAME}
```