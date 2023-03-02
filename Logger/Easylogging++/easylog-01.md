## 快速使用

### 1.1 简单输出日志

+ 示例：
  ```
    #include "easylogging++.h"  
      
    INITIALIZE_EASYLOGGINGPP  
      
    int main(int argv, char* argc[]) {  
       LOG(INFO) << "My first info log using default logger";  
       return 0;  
    }
  ``` 
+ 代码解析：
  + 包含 `easylogging++.h` 头文件
  + 使用宏 `INITIALIZE_EASYLOGGINGPP` 初始化
  + 使用 `LOG(INFO)` 开始日志记录
+ 注意：
  + 这里需要特别说明的是，初始化宏 `INITIALIZE_EASYLOGGINGPP` 必须使用而且只能使用一次，否则会产生编译错误。
  + 最好的放置这个初始化宏的地方是位于程序入口函数所在文件的顶部，紧跟在包含头文件的代码后面

### 1.2 接入easylogging++的两种方式

+ 接入 `easylogging++` 有两种方式，两种方式都需要在你的项目中直接包含源码(`easylogging++.h` 和 `easylogging++.cc`):

#### 主程序中直接初始化

+ 通过 `INITIALIZE_EASYLOGGINGPP` 宏初始化即可开始，例如上面`1.1简单输出日志`的示例代码

#### 隐式初始化

+ 或者也可以不直接在程序入口处添加 `INITIALIZE_EASYLOGGINGPP` 宏，改为隐式初始化，借由定义 `AUTO_INITIALIZE_EASYLOGGINGPP` 宏实现。
+ 在`CMakeLists.txt`中定义宏，例如：
  ```
    # easylogging++ 隐式声明宏
    add_definitions(-DAUTO_INITIALIZE_EASYLOGGINGPP)
  ``` 

### 1.3 输出到指定日志文件

+ 通过完成 `Easylogging++` 日志的配置，才可以实现输出到指定文件

+ 要完成 `Easylogging++` 日志的配置功能，可以通过三种方式实现，而且每一种方法都非常简单。
  + 使用配置文件，这种方法的好处就是只要修改配置文件即可实现日志格式的重新配置，而不需要修改源程序代码，缺点就是发布程序时必须打包配置文件一起发布，否则程序无法正常运行。
  + 使用`el::Configurations`类提供的成员函数，这种方法和第一种方法的优缺点正好相反。
  + 使用 `Easylogging++` 的内联配置功能，但是并不推荐使用这种方式，因为它会显得配置十分凌乱。

#### 1.3.1 使用配置文件

+ 在程序运行时，可以通过使用 `el::Configurations` 类加载配置文件来完成 `Easylogging++` 的配置功能，配置文件必须遵循下面的语法：
  ```
    * LEVEL:  
      CONFIGURATION NAME  = "VALUE" ## Comment  
      CONFIGURATION NAME  = "VALUE"
  ``` 
+ 语法简要说明：
  + `*LEVEL`，指的是日志级别，以星号符`"*"`开始，并以英文冒号`":"`结束。
  + `CONFIGURATION NAME`， 指的是配置项的名称，全部名称见下面的表格。
  + `"VALUE"`，指的是配置项的值，各个配置对应的值类型详见下面的表格。
  + `##Comment`，指的是注释，其中两个连续井号`"##"`表示注释，`Comment`是注释的内容。注释是可有可无的，但是千万不要在注释中使用双引号，否则可能会出现意想不到的错误
+ 编写配置文件时，强烈建议先写 `Global` 级别的配置，这样的好处是可以使其他未在配置文件中明确指出的级别都将会自动继承使用 `Global` 级别的配置。

+ 下表列举了GitHub上给出的Easylogging++在配置文件中支持的配置项：

|   Configuration Name    |   Type   |            Description                   |
|-------------------------|----------|------------------------------------------|
| `Enabled`               |   bool   | 确定是否启用记录器的相应级别。你可以使用' el::Level::Global '禁用所有日志 |
| `To_File`               |   bool   | 是否将相应的日志写入日志文件               |
| `To_Standard_Output`    |   bool   | 是否将日志写入标准输出，如终端或命令提示符  |
| `Format`                |   char*  | 确定相应级别和记录器的日志格式/模式.        |
| `Filename`              |   char*  | 为相应级别和日志记录器确定要写入日志的日志文件(全路径) |
| `Subsecond_Precision`   |   uint   | 指定亚秒精度(以前称为“毫秒宽度”)。宽度可在(1-6)范围内 |
| `Performance_Tracking`  |   bool   | 确定是否启用性能跟踪。这与记录器或级别无关。性能跟踪总是使用' Performance '记录器，除非指定 |
| `Max_Log_File_Size`     |   size_t | 如果对应级别的日志文件大小为>=指定大小，则日志文件将被截断. |
| `Log_Flush_Threshold`   |   size_t | 指定在清除挂起的日志数据之前要保留的日志项数  |

+ 配置文件示例 my_log.conf ：
  ```
    * GLOBAL:  
        ENABLED                 =   true  
        TO_FILE                 =   true  
        TO_STANDARD_OUTPUT      =   true  
        FORMAT                  =   "[%level | %datetime] | %msg"  
        FILENAME                =   "log\\log_%datetime{%Y%M%d}.log"  
        MILLISECONDS_WIDTH      =   3  
        PERFORMANCE_TRACKING    =   false  
        MAX_LOG_FILE_SIZE       =   1048576  
        LOG_FLUSH_THRESHOLD     =   0  
          
    * TRACE:  
        FILENAME                =   "log\\trace_log_%datetime{%Y%M%d}.log"  
          
    * DEBUG:  
        FILENAME                =   "log\\debug_log_%datetime{%Y%M%d}.log"  
          
    * FATAL:  
        ENABLED                 =   false  
          
    * ERROR:  
        FILENAME                =   "log\\error_log_%datetime{%Y%M%d}.log"  
          
    * WARNING:  
        FILENAME                =   "log\\warning_log_%datetime{%Y%M%d}.log"  
          
    * INFO:  
        FILENAME                =   "log\\info_log_%datetime{%Y%M%d}.log"  
          
    * VERBOSE:  
        ENABLED                 =   false
  ``` 
+ 在上面的文件中，我们以 `Global` 级别开始，并在 `Global` 级别中把 `Easylogging++` 支持的所有的配置项都设置好了，这样 `Global` 级别的配置就会被后续的日志级别所继承，一直到后续的日志级别再次明确地设置配置项才会覆盖原有的来自于 `Global` 级别的配置。
+ 比如这里的`TRACE`、`DEBUG`、`ERROR`、`WARNING`、`INFO`等级别都显式地定义了 `Filename` ，所以这几个级别的日志记录会各自保存在相应的文件里面。
+ 而`FATAL、VERBOSE`这两个级别则显式地定义了 `ENABLE` ，并将其值设置为`false`，所以这两个级别的日志记录将会被禁用。下面的代码再次演示如何使用该配置文件（注意注释的内容）：
  ```
    #include "easylogging++.h"  
      
    INITIALIZE_EASYLOGGINGPP  
      
    int main(int argc, char** argv)  
    {  
        /*///////////////////////////////////////////////////////////////////////// 
        必须设置标记 LoggingFlag::StrictLogFileSizeCheck 
        否则,配置文件中MAX_LOG_FILE_SIZE = 1048576不生效 
        /////////////////////////////////////////////////////////////////////////*/  
        el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);  
      
        el::Configurations conf("my_log.conf");  
      
        /// 可以单独设置某一个logger的配置  
        el::Loggers::reconfigureLogger("default", conf);  
      
        /// 也可以设置全部logger的配置  
        el::Loggers::reconfigureAllLoggers(conf);  
      
        LOG(INFO) << "***** info log  *****";  
      
        system("pause");  
        return 0;  
    }
  ``` 

#### 1.3.2 使用`el::Configurations`类的成员函数

+ 在`Easylogging++`日志库中，封装了配置类`el::Configurations`，该类提供了完成日志配置功能的全部接口，建议参考该类的源码，可以查看和了解更多更详细和更全面的功能接口。
+ 下面的代码演示了几个常用接口的用法：
  ```
    #include "easylogging++.h"  
      
    INITIALIZE_EASYLOGGINGPP  
      
    int main(int argc, const char** argv)   
    {  
        /// 使用默认配置  
        el::Configurations defaultConf;  
        defaultConf.setToDefault();  
        LOG(INFO) << "Using el::Configurations class";  
          
        /// 重新设置INFO级别的配置项FORMAT的值  
        defaultConf.set(el::Level::Info,  
            el::ConfigurationType::Format, "%datetime %level %msg");  
        /// 重新设置配置  
        el::Loggers::reconfigureLogger("default", defaultConf);  
        LOG(INFO) << "Using el::Configurations class";  
      
        // 重新设置GLOBAL级别的配置项FORMAT的值  
        defaultConf.setGlobally(  
            el::ConfigurationType::Format, "%datetime %msg");  
        /// 重新设置配置  
        el::Loggers::reconfigureLogger("default", defaultConf);  
        LOG(INFO) << "Using el::Configurations class";  
      
        system("pause");  
        return 0;  
    }
  ``` 

#### 1.3.3 使用内联配置功能

+ 所谓的内联配置功能，就是说你可以通过使用`std::string`字符串来完成日志的配置功能，但是要注意在`std::string`字符串中加上换行符保证字符串的格式遵循配置文件中的格式。
+ 比如，如果要使用内联配置功能实现和方法二中一样的输出格式，那么实现代码必须像下面这样：
  ```
    #include "easylogging++.h"  
      
    INITIALIZE_EASYLOGGINGPP  
      
    int main(int argc, const char** argv)   
    {  
        /// 使用默认配置  
        el::Configurations defaultConf;  
        defaultConf.setToDefault();  
        LOG(INFO) << "Using inline configuration";  
          
        /// 重新设置INFO级别的配置项FORMAT的值  
        defaultConf.parseFromText("*INFO:\n FORMAT = %datetime %level %msg");  
        /// 重新设置配置  
        el::Loggers::reconfigureLogger("default", defaultConf);  
        LOG(INFO) << "Using inline configuration";  
      
        // 重新设置GLOBAL级别的配置项FORMAT的值  
        defaultConf.parseFromText("*INFO:\n FORMAT = %datetime %msg");  
        /// 重新设置配置  
        el::Loggers::reconfigureLogger("default", defaultConf);  
        LOG(INFO) << "Using inline configuration";  
      
        system("pause");  
        return 0;  
    }
  ```
+ 仔细看上面的代码，注意每一次调用函数`parseFromText()`的参数中都包含了一个换行符 `“\n”`。假如没有这个换行符，就不能正确的解析出配置项的内容，从而会导致配置无效。
+ 由于这个原因，当需要设置的配置项很多的时候，如果还使用内联配置功能完成日志的配置，就会使得代码变得凌乱复杂，而且很容易造成错误，所以尽量不要使用这种方法或者避免使用这种方法。 

#### 1.3.4 默认配置功能

+ 如果你希望为现有的或建立的日志记录器设置一个默认的配置，你可以使用下面的这个函数：
  + `el::Loggers::setDefaultConfigurations(el::Configurations& configurations, bool configureExistingLoggers = false)`
+ 当你在编写大型程序或者调用同样使用`Easylogging++`的第三方库时，默认配置功能显得十分有用。这个功能使得后续任何新建的日志记录器，都将会使用默认配置；如果你希望现有的日志记录也是用默认配置，只需把函数的第二个参数设置为`true`即可。下面的代码演示了默认配置功能：
  ```
    #include "easylogging++.h"  
      
    INITIALIZE_EASYLOGGINGPP  
      
    int main(void)  
    {  
        el::Configurations defaultConf;  
        defaultConf.setGlobally(el::ConfigurationType::Format, "[%logger] %level: %msg");  
      
        /// 只为新建的日志记录器设置默认配置  
        el::Loggers::setDefaultConfigurations(defaultConf);  
        LOG(INFO) << "Set default configuration but existing loggers not updated yet";  
      
        /// 新建日志记录器 testDefaultConf1  
        el::Loggers::getLogger("testDefaultConf1");  
        CLOG(INFO, "testDefaultConf1") << "Logging using new logger 1";  
      
        // 为现有的日志记录器设置默认配置  
        el::Loggers::setDefaultConfigurations(defaultConf, true);  
        LOG(INFO) << "Existing loggers updated as well";  
      
        /// 新建日志记录器 testDefaultConf2  
        el::Loggers::getLogger("testDefaultConf2");  
        CLOG(INFO, "testDefaultConf2") << "Logging using new logger 2";  
      
        system("pause");  
        return 0;  
    }
  ``` 

#### 1.3.5 全局配置功能 

+ 全局配置并不是指Global级别，而是值利用全局配置文件为全部或部分，甚至是为新建的日志记录器注册配置。全局配置文件必须遵循下面的语法：
  ```
    -- LOGGER ID ## Case sensitive  
      ## Everything else is same as configuration file  
      
    -- ANOTHER LOGGER ID  
      ## Configuration for this logger
  ``` 
+ 语法简要说明如下：
  + `LOGGER ID`，指的是记录器ID，大小写敏感，并以两个破折号开始
+ 其余部分的语法规则和本文中方法一的配置文件的语法规则完全一样。

+ 一旦你编写好了全局配置文件，你仅需使用一个函数就可以完成你的日志记录器的配置，甚至是注册一个全新的日志记录器。
+ 需要注意的是，你不能使用空白的配置来注册新的日志记录器，也就是说在 `LOGGER ID` 下面，你至少得定义一个配置项。
+ 下面的代码演示了全局配置功能：
  ```
    #include "easylogging++.h"  
      
    INITIALIZE_EASYLOGGINGPP  
      
    int main(void)   
    {  
        LOG(INFO) << "Info log before using global configuration";  
      
        /// 只需一个函数即可实现全局配置功能  
        el::Loggers::configureFromGlobal("global.conf");  
      
        LOG(INFO) << "Info log AFTER using global configuration";  
        LOG(ERROR) << "Error log AFTER using global configuration";  
      
        /// 用全局配置文件中新建的日志记录器 testGlobalConf 来记录日志  
        CLOG(TRACE, "testGlobalConf") << "TRACE Logging using new logger";  
        CLOG(DEBUG, "testGlobalConf") << "DEBUG Logging using new logger";  
        CLOG(WARNING, "testGlobalConf") << "WARNING Logging using new logger";  
        CLOG(ERROR, "testGlobalConf") << "ERROR Logging using new logger";  
        CLOG(INFO, "testGlobalConf") << "INFO Logging using new logger";  
      
        system("pause");  
        return 0;  
    }
  ``` 
+ 其中全局配置文件global.conf的内容如下：
  ```
    -- default   
       *INFO:  
          FORMAT   = "%level %msg"  
          FILENAME = "/tmp/logs/wow.log"  
       *ERROR:  
          FORMAT   = "%levshort %fbase:%line %msg"  
      
            
    -- testGlobalConf  
       *GLOBAL:  
          FORMAT                  =   "[%level | %datetime] | %msg"  
          ENABLED                 =   true  
          TO_FILE                 =   true  
          TO_STANDARD_OUTPUT      =   true  
          MILLISECONDS_WIDTH      =   3
  ``` 

#### 1.3.6 读取配置

+ 在某些情况下，如果我们想要获取某一个日志记录器的当前配置，可以通过使用 `el::Loggers` 类的成员函数 `typedConfigurations()` 来实现，建议参考该类的源码，可以查看和了解更多更详细和更全面的功能接口.
+ 下面的代码片段演示了该功能：
  ```
    el::Logger* defaultLogger = el::Loggers::getLogger("default");  
    /// 记录器default是否被禁用  
    bool enabled = defaultLogger->typedConfigurations()->enabled(el::Level::Info);  
    /// 记录器default的INFO级别的日志输出格式  
    std::string format =  defaultLogger->typedConfigurations()->logFormat(el::Level::Info).format();
  ``` 