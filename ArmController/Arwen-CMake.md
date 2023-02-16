## CMakeLists.txt 调试方法

+ 输出变量值：
  ```
    include(CMakePrintHelpers)
    cmake_print_variables(PROJECT_BINARY_DIR)
  ``` 

+ 输出目标属性：
  ```
    include(CMakePrintHelpers)
    cmake_print_properties(TARGETS ${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE)
  ``` 

## 变量表述的值

### ${PROJECT_BINARY_DIR}

+ `PROJECT_BINARY_DIR="/home/user/zhangjunyi/arwen/build"`