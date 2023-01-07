## git clone 出错

+ 今天克隆GitHub仓库中的项目时，执行git clone git://github.com/alibaba/Tangram-Android.git却失败报错：
  ```
    Cloning into 'Tangram-Android'...
    fatal: unable to access 'http://github.com/alibaba/Tangram-Android.git/': OpenSSL SSL_read: Connection was reset, errno 10054
  ``` 
+ 解决方法，需要执行以下两个步骤：
  + 输入git config --global http.sslVerify "false"，解除SSL验证；
  + 将地址https://改为git://，避开SSL验证。