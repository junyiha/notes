## 开机启动服务/脚本

+ 系统启动时需要加载的配置文件
  + /etc/profile
  + /root/.bash_profile
  + /etc/bashrc
  + /root/.bashrc
  + /etc/profile.d/*.sh
  + /etc/sysconfig/
  + /etc/rc.local

+ 自定义服务文件，添加到系统服务，通过`Systemctl`管理
  + 写服务文件，例如nginx.service, redis.service, supervisord.service
    ```
        [Unit]      --  服务说明
        Description --  描述服务
        After       --  描述服务类别

        [Service]    -- 服务运行参数的设置
        Type=forking -- 为后台运行的形式
        ExecStart    -- 为服务的具体运行命令
        ExecReload   -- 为服务的重启命令
        ExecStop     -- 为服务的停止命令
        PrivateTmp=True  -- 表示给服务分配独立的临时空间
        注意：启动，重启，停止命令全部要求使用绝对路径

        [Install]    --  服务安装的相关设置，可设置为多用户
        WantedBy=multi-user.target
    ``` 

+ 文件保存在`/usr/lib/systemd/system/`路径下，权限为`754`

+ 设置开机自动启动
  + `systemctl enable nginx.service`

+ 停止开机自启动
  + `systemctl disable nginx.service`

+ 验证是否为开机自启动
  + `systemctl is-enabled nginx`

+ 查看所有已经启动的服务
  + `systemctl list-units --type=service`