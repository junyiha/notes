## 连接操作命令

+ `quit` : 关闭连接
+ `auth` : 简单密码认证
+ `help cmd` : 查看cmd帮助，例如：`help quit`

## 持久化

+ `save` : 将数据同步保存到磁盘
+ `bgsave` : 将数据异步保存到磁盘
+ `lastsave` : 返回上次成功将数据保存到磁盘的Unix时戳
+ `shundown` : 将数据同步保存到磁盘，然后关闭服务

## 远程服务控制

+ `info` : 提供服务器的信息和统计
+ `monitor` : 实时转储收到的请求
+ `slaveof` : 改变复制策略设置
+ `config` : 在运行时配置Redis服务器

## 对value操作的命令

+ `exists (key)` : 确认一个key是否存在
+ `del (key)` : 删除一个key
+ `type (key)` : 返回值的类型
+ `keys (pattern)` : 返回满足给定pattern的所有key
+ `randomkey` : 随即返回key空间的一个
+ `keyrename(oldname, newname)` : 重命名key
+ `dbsize` : 返回当前数据库中key的数目
+ `expire` : 设定一个key的活动时间(s)
+ `ttl` : 获得一个key的活动时间
+ `select (index)` : 按索引查询
+ `move (key, dbindex)` : 移动当前数据库中的key到dbindex数据库
+ `flushdb` : 删除当前选择数据库中所有key
+ `flushall` : 删除所有数据库中的所有key

## List

+ `rpush(key, value)` : 在名称为key的list尾部添加一个值为value的元素
+ `lpush(key, value)` : 在名称为key的list头部添加一个值为alue的元素
+ `llen(key)` : 返回名称为key的list长度
+ `lrange(key, start, end)` : 返回名称为key的list中start至end之间的元素
+ `ltrim(key, start, end)` : 截取名称为key的list
+ `lindex(key, index)` : 返回名称为key的list中index位置的元素
+ `lset(key, index, value)` : 给名称为key的list中index位置的元素赋值
+ `lrem(key, count, value)` : 删除count个key的list中值为value的元素
+ `lpop(key)` : 返回并删除名称为key的list中的首元素
+ `rpop(key)` : 返回并删除名称为key的list中的尾元素
+ `blpop(key1, key2, ... key N, timeout)` : lpop命令的block版本
+ `brpop(key1, key2, ... key N, timeout)` : rpop的block版本