## 简介

+ RK平台后端接口简介

## 相机模块

### 相机地址测试

+ 方法：POST
+ 路径：/api/setting/camera/test
+ 请求示例
```json
{
    "id":1
}
```

+ 成功响应
```json
{
    "code":0,
    "msg":"valid camera"
}
```

+ 失败响应
```json
{
    "code":-1,
    "msg":"错误信息"
}
```