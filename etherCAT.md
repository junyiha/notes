## EtherCAT

+ `EtherCAT`是`Ethernet for Control Automation Technolog`的简称，是一个实时控制的开放标准。

+ `ETG`, `EtherCAT技术小组`，该组织是`Beckhoff`为支持和推广`EtherCAT`而成立的。`ETG`网站是关于`EtherCAT`的信息来源。

### EtherCAT xenomai 安装

+ ~~`notes/PDF/EtherCAT（ubuntu18.04，linux4.9.38，xenomai3.1，igh1.52）配置完整流程.docx`~~ 
+ pdf文档配置menuconfig时步骤不完整，坑！！！
+ 另一个地址:`https://www.icode9.com/content-3-916631.html`

### 固定`RxPDOs` 

+ `notes/PDF/AP系列驱动器+EtherCAT+手册V1.0.pdf -- P12`

+ **对于`CSP`(循环同步位置)**0x6060的操作方式=8：
  + 接收PDO 4 ： 0x1700
    + `0x6040` -- 控制字
    + `0x607A` -- 轨迹目标位置
    + `0x60B1` -- 速度偏移
    + `0x60B2` -- 转矩偏移

+ 对于`CSV`(循环同步速度)0x6060的操作模式=9：
  + 接收PDO 5：0x1701
    + `0x6040` -- 控制字
    + `0x60FF` -- 目标速度
    + `0x60B2` -- 转矩偏移量

+ 对于`CST`(循环同步转矩)0x6060的操作方式=10：
  + 接收PDO 6：0x1702
    + `0x6040` -- 控制字
    + `0x60FF` -- 目标速度
    + `0x60B2` -- 转矩偏移量

### 固定`TxPDO`

+ 发送PDO 5：0x1B00
  + `0x6041` -- 16 -- 状态字
  + `0x6064` -- 32 -- 实际电机位置
  + `0x60F4` -- 32 -- 位置循环错误（跟随错误）
  + `0x606C` -- 32 -- 实际电机速度
  + `0x6077` -- 16 -- 转矩实际值

### 请求主站

+ 用户程序通过`ecrt_request_master`请求主站设备，该函数调用`ecrt_request_master_err()`，取得`master`设备，并执行`ec_master_enter_operation_phase()`函数

+ 请求主站设备完成后，开始**创建数据域**，调用`ecrt_master_create_domain()`

+ 创建数据域成功后，分别完成对各从站设备的配置，配置内容包括：`PDO`映射，SM配置，`FFMU`配置和`DC`配置

+ 用户程序调用的入口是`ecrt.h`和相关的库文件，通过`ioctl`以驱动的形式实现，与`master`文件夹中的部分函数稍有区别

### 从站配置

+ 从站配置是应用层通过`ecrt_master_slave_config()`函数添加到主站的`config`链表中

## PDO

+ 过程数据对象(`Process Data Object, PDO`)，是用来传输实时数据的，提供对设备应用对象的直接访问通道，它用来传输实时短帧数据，具有较高的优先权。
  
+ `PDO`传输的数据必须少于或等于8个字节，`PDO`的**CAN报文数据域**中每个字节都用作数据传输，因此，在应用层上不包含传输控制信息，报文利用率极高。

+ `PDO`通信是基于生产者/消费者的通讯模式，每个`PDO`有一个唯一的标识符且可以通过一个节点发送，但有多个节点可以接收。`PDO`的接收不需要消费者确认。
  - 由生产者发送的`PDO`称为发送PDO`(TPDO)`
  - 消费者接收的`PDO`称为接收PDO`(RPDO)`

+ 每个`PDO`在对象字典中由两个对象描述： 通信参数和映射参数
  - `PDO`通信参数指明使用哪个`COB-ID`，传输类型，禁用时间和定时时间
  - `PDO`映射参数用于设定`PDO`报文中的数据的映射关系，确定要传输的数据在`CAN`报文数据域中的定位。该参数允许`PDO`的生产者和消费者知道正在传输什么信息，而不需要在`CAN`报文中增加额外的协议控制信息，使传输的效率达到最高。一个`PDO`最多可以映射64个对象

+ `PDO`通讯具有三种出发模式：内部事件驱动或内部定时器触发，同步触发，远程请求触发
  - **内部事件驱动或内部定时触发。**通讯由某一事件触发。例如数字I/O口状态改变，超过预先设定的值，定时器中断等都会触发节点发送一个`PDO`。这种模式可使总线负载达到最小，在相对低的波特率下获得比较高的通讯特性。
  - **同步触发。**同步触发`PDO`是指`CANopen`节点收到由管理节点发出的同步报文（同步对象Sync）之后，根据触发报文条件向总线发出`PDO`报文。同步传输又分为周期性和非周期性。周期性是指`CANopen`节点收到一定数量的同步报文之后才开始发送；非周期性`PDO`是指`PDO`触发条件成立之后，当收到下一个同步对象后马上发送`PDO`
  - **远程请求触发。**`PDO`消费者可以给`PDO`生产者发送远程`PDO`请求，相应`PDO`生产者将对远程帧作出相应，向总线上发送相应的`PDO`数据。

+ `PDO`通讯时的触发模式由`PDO`通信参数中的传输类型来确定，传输类型是一个8位无符号整数，这个传输类型值的大小与`PDO`触发方式的对应关系

+ 主站和从站`PDO`通信的机制
  + `PDO`的基本概念及其在对象字典中的索引，在主站和从战采用`PDO`通信方式时，思路是 -- 先配置主站的`PDO`的通信参数(COB-ID,数据传输类型)，再配置从站的通信参数与主站一致，这样就建立了主站与从站的`PDO`通信的关系。然后再通过字典配置主站`PDO`映射参数，配置完成后从主站就可以通过`PDO`通信传输数据。

+ `PDO`传输的“总指挥”就是对象字典。`PDO`发送什么数据，接收什么数据，什么时候发送和接收，发送和接收的数据都放在哪儿，都是由对象字典配置。

## CAN

+ CAN是控制器局域网络(`Controller Area Network, CAN`)的简称，是由以研发和生产汽车电子产品著称的德国`BOSCH`公司开发的，并最终称为国际标准，是国际上应用最广泛的**现场总线**之一

## EtherCAT 使用与解析--关于ethercat应用层使用

+ url -- `https://blog.csdn.net/lswdcyy/article/details/105441470`
  
+ 下载`ethercat`源码并且安装好之后，测试`ethercat`使用可以遵循以下步骤

+ 开启`ethercat`系统 -- `sudo /etc/init.d/ethercat start`
  + 执行这一步需要确保一点 -- 按照`ethercat`源码中的`README`指导将一些需要的文件复制以及创建软连接到`/opt/init.d/ethercat`以及`/opt/sysconfig/ethercat`两个文件，前者是系统启动文件，后者是系统配置文件
  + 系统配置文件，是一份变量定义文件，在系统启动脚本中执行，定义两类变量，一个是主站MAC地址(`MASTER0_DEVICE`)，一个是使用的模块驱动名称(`DEVICE_MODULES`)

+ 开启系统后，要在应用层进行对主站模块的使用，本质上是通过开启`/dev/EtherCAT`字符设备，而后基于`ioctl`方式调用内核主站模块各种功能
  + 开启系统后，用户主要需要进行从站配置与PDO映射，域操作功能，然后就可以进行PDO交换了
  + **主站程序运行在内核空间，应用层需要一种方式实现对内核调用。通过打开主站创建的字符设备`/dev/EtherCAT`就是这个作用**
  + 主要用到的函数
    - `ec_master_t *ecrt_request_master(unsigned int master_index);` -- 
      - **负责打开字符设备文件，传入参数为使用主站索引**（使用`/etc/init.d/ethercat`开启系统的时候可以一次性传入多个MAC地址从而开启多个主站，不同主站创建不同的字符设备，例如`/dev/EtherCAT0, /dev/EtherCAT1...`），
      - 而这个索引就是用于开启对应的字符设备，从而使用不同的主站，使用`open接口`打开，然后返回文件描述符，该文件描述符用于`ioctl`调用对应主站功能。另外在申请到主站后就不再允许进行总线的重新扫描，固化了主站连接的从站链表，而且设置从站状态当前申请状态为`PREOP`
    - `ec_domain_t *ecrt_master_create_domain(ec_master_t* master);`
      - **负责创建域，**`domain`与`PDO`映射有密切联系，在激活的位置详谈
      - 这个函数具体内容就是直接在内核空间中创建一块`ec_domain`空间并且将该空间连接到主站`domain`链表尾部
    - `ec_slave_config_t *ecrt_master_slave_config(ec_master_t* master, uint16_t alias, uint16_t position, uint32_t vendor_id, uint32_t product_code);`
      - **从站配置函数**，
      - 主站模块中的从站链表，它们之间的关系为：从站配置是应用层通过`ecrt_master_slave_config()`函数添加到主站的`configs`链表中的，而从站链表`slaves`则是通过`ethercat`主站状态机通过扫描`ethercat`总线得到的，两者的共同之处在于**从站配置过程的`alias, position, VID, PID`，这些在主站扫描到的从站链表中都是有一份参数的，当应用层设置配置和主站扫描到从站信息相匹配的时候，那就将从站与从站配置相联系**（这时候会将主站扫描的`SII`信息关于`sync`关联的`PDO`信息复制到从站配置中，也就是默认`PDO`配置）；这样，就可以通过从站配置寻找到主站模块中从站配置信息，进而获取到从站信息。
    - `int ecrt_slave_config_reg_pdo_entry(ec_slave_config_t *sc, uint16_t index, uint8_t subindex, ec_domain_t *domain, unsigned int *bit position);`
      - **从站配置`PDO`函数**
      - 需要注意的一点 -- 在主站正式激活之前，所有配置`PDO`相关的其实并没有相对应的空间申请操作，一切都是进行的计算，计算`PDO`需要多大空间，计算`domains`的逻辑位置，计算`FMMU`的逻辑位置，计算`PDO`的逻辑位置，直到主站正式激活，主站会根据自身已经申请的域链表`domains`，获取所有域所需要的空间大小，而后对每个域进行逻辑地址分配，每个域中再对每个`FMMU`进行逻辑地址分配。
      - 接口参数
        - `uint16_t index` -- 对象字典索引
        - `uint8_t subindex` -- 对象字典子索引
        - `ec_domain_t *domain` -- 使用的域
        - `unsigned int* bit_position` -- 一个Byte中的偏移量，当PDO映射逻辑地址不是完整的Byte时有用
      - 首先，通过从站应用层配置索引可以获取到主站的从站配置链表中对应的从站配置，而后根据配置目标domain的索引获取到主站的domains链表对应的域，这样就可以实现应用层的从站配置和domain切换到主站对应的从站配置和domain，然后进行pdo映射操作。
      - 每次进行PDO映射的时候，并不是只对设置的一个对象进行处理，而是直接将整个sync关联的PDO都进行批次化处理。所以，本质上来讲，PDO配置映射就是确定PDO的逻辑地址位置
    - `int ecrt_master_activate(ec_master_t *master);`
      - **函数为正式激活的函数**
      - 主站注册的domains链表整体大小计算；经过PDO注册映射之后，对主站中关联的每个domains都是相互独立的，并且每个domains都只是一个计算得到的值，其实并没有需要的空间申请，因此在主站激活的时候会将全部domians需要的空间进行统一申请。具体申请到的PDO映射逻辑空间存放在字符设备打开文件的priv指针处，关于字符设备的file->priv在字符设备打开eccdev_open的时候进行指定。然后按照主站连接的domains链表顺序对每个domian起始地址进行设置：主要是domain的逻辑起始地址，domain的大小，以及domain中的FMMU的逻辑地址重新设置，最终，domain和FMMU的逻辑起始地址都是在主站全部domains环境下的逻辑起始地址。为了进行PDO映射，在主站激活过程中还对每个domain需要的子报文进行空间申请。在计算子报文需要个数的时候，各个domain计算各自需要的子报文需要，这样就可以满足不同domain的PDO交换周期是可以单独设置的；在domain计算自己需要的子报文个数的时候，计算是以FMMU为一个基本单位进行计算的，每个子报文可承载的数据大小为1486Byte，然后根据一个子报文中FMMU的输入输出情况设置子报文类型，也就是EC_DATAGRAM_LRD类型子报文，EC_DATAGRAM_LRR类型子报文以及EC_DATAGRAM_LRW类型子报文。然后将这些子报文添加到domain的datagram_pairs链表中。当然，整体过程中，domain映射空间和子报文使用的数据空间都是同一段空间。
      - 完成主站的domains域空间处理，之后就停止主站的空闲阶段线程（等待空间阶段线程退出）
      - 开启主站的操作阶段线程，该线程和空闲阶段线程相比不同之处--在于将主站子报文队列组合发送移动到用户手中进行处理
    - `uint8_t *ecrt_domain_data(ec_domain_t *domain);`
      - **返回domain在逻辑空间的逻辑地址**
    - `void ecrt_domain_queue(ec_domain_t *domain);`
      - **将对应domain空间使用的子报文排列到主站子报文发送链表中**
    - `void ecrt_master_send(ec_master_t *master);`
      - **将主站的子报文发送链表的子报文进行发送**，在发送过程中，默认的会将从站状态机子报文和主站状态机子报文进行排队发送

## 头文件接口

+ `ecrt_master_receive()`
  + 功能：从硬件获取接收到的帧并处理数据报。通过调用中断服务例程查询网络设备接收到的帧。提取收到的数据报并将结果发送到队列中的数据报对象。接收到的数据报和超时的数据报将被标记并退出队列
  + 函数原型：`void ecrt_master_receive(ec_master_t* master);`
  + 参数：`master` -- `ethercat`主机
  + 返回值：无

+ `ecrt_domain_process()`
  + 功能：确定域数据报的状态。评估接收到的数据报的工作计数器，并在必要时输出统计信息。必须在`ecrt_master_receive()`接收域数据报之后调用此函数，以便`ecrt_domain_state()`返回上一次进程数据交换的结果。
  + 函数原型：`void ecrt_domain_process(ec_domain_t *domain);`
  + 参数：`domain` -- 域
  + 返回值：无

+ `EC_READ_U16()`
  + 功能：宏函数，计算整数数据，同样还有`EC_READ_U32()`

+ `EC_WRITE_U16()`
  + 功能：宏函数，将整型数据写入内存。内存大小是`ecrt_slave_config_create_sdo_request()`的参数。

+ `ecrt_master_sync_reference_clock()`
  + 功能：将DC参考时钟偏移补偿数据报排队发送，参考时钟将上次取消`ecrt_master_application_time()`提供的应用程序时间同步
  + 函数原型：`void ecrt_master_sync_reference_clock(ec_master_t *master)`
  + 参数：`master` -- `ethercat`主机
  + 返回值：无

+ `ecrt_master_sync_slave_clocks()`
  + 功能：将DC时钟偏移补偿数据报排队发送，所有的子时钟与基准时钟同步
  + 函数原型：`void ecrt_master_sync_slave_clocks(ec_master_t* master);`
  + 参数：`master` -- `ethercat`主机
  + 返回值：无

+ `ecrt_domain_queue()`
  + 功能：**将主数据报队列中的所有域数据报排队**。调用此函数可标记域的数据报以便在`ecrt_master_send()`的下一次调用
  + 函数原型：`void ecrt_domain_queue(ec_domain_t* domain);`
  + 参数：`domain` -- 域
  + 返回值：无

+ `ecrt_master_send()`
  + 功能：**发送队列中的所有数据报**。该方法接收所有排队等待传输的数据报，将他们放入帧中，并将他们传递给以太网设备进行发送
  + 函数原型：`void ecrt_master_send(ec_master_t* master);`
  + 参数：`master` -- `ethercat`主机
  + 返回值：无

+ `ecrt_master_application_time()`
  + 功能：设置应用程序时间。在使用分布式时钟操作从机时，主机必须知道应用程序的时间。时间不是由主机本身增加的，因此必须循环调用此方法
  + 函数原型：`void ecrt_master_application_time(ec_master_t* master, uint64_t app_time);`
  + 参数：`master` -- `ethercat`主机；`app_time` -- 应用时间
  + 返回值：无

+ `ecrt_release_master()`
  + 功能：释放请求的`ethercat`主机
  + 函数原型：`void ecrt_release_master(ec_master_t* master);`
  + 参数：`master` -- `ethercat`主机
  + 返回值：无

## 关于PDO映射

+ `https://www.codeleading.com/article/95113301360/#:~:text=%E5%BD%93%E7%84%B6%E5%8F%A6%E5%A4%96%E4%B8%80%E7%A7%8D%E5%B0%B1%E6%98%AF%E4%BD%BF%E7%94%A8ecrt_slave_config_pdos,%28%29%E5%87%BD%E6%95%B0%E5%AF%B9%E4%BB%8E%E7%AB%99%E9%85%8D%E7%BD%AE%E8%BF%9B%E8%A1%8C%E8%AE%BE%E7%BD%AE%EF%BC%8C%E8%AF%A5%E5%87%BD%E6%95%B0%E4%BC%9A%E5%B0%86%E5%8E%9F%E6%9C%ACSII%E5%A4%8D%E5%88%B6%E5%88%B0%E7%9A%84%E4%BB%8E%E7%AB%99%E9%85%8D%E7%BD%AE%E4%B8%AD%E7%9A%84sync%E8%BF%9B%E8%A1%8C%E6%B8%85%E9%99%A4%EF%BC%8C%E8%80%8C%E5%90%8E%E4%BE%9D%E6%8D%AE%E6%96%B0%E7%9A%84%E9%85%8D%E7%BD%AE%E8%BF%9B%E8%A1%8C%E8%AE%BE%E7%BD%AE%EF%BC%9A%E9%9C%80%E8%A6%81%E4%BD%BF%E7%94%A8%E7%9A%84%E9%85%8D%E7%BD%AE%E7%BB%93%E6%9E%84%E5%A6%82%E4%B8%8B%EF%BC%9A`

+ 对于PDO映射，首先它是已经有了一个sync中关联PDO的链表的前提下才进行的PDO映射。
+ 使用`ecrt_slave_config_pdos()`函数进行PDO的在`sync`中的配置
  + 之所以有这样一个步骤，是因为主站状态部分，主站状态机在扫描SII信息时会提取`TxPDO`和`RxPDO`到从站的同步管理器(SII信息中有PDO和sync相关的信息)；然后再使用`ecrt_master_slave_config()`进行函数配置的时候会将对应从站的sync相关的PDO(`master->slaves->sync`)复制到从站配置部分，这样即使不去人为的配置同步管理器和PDO的映射关系，也没有什么影响

+ `ecrt_slave_config_pdos()`
  + 函数对从站配置进行设置，会将原本SII复制到从站配置中的sync进行清除，而后依据新的配置进行设置，（目的就是为了对从站同步管理器的自定义设置）
  + 需要使用到的参数分别是`sync, pdo, pdo_entry`结构体，三者关系是`sync`索引`PDO`， `PDO`索引`PDO_entry`
  + 从站如何获取PDO配置，可以使用`sudo ethercat cstruct`命令进行该信息的提取
  + 针对每个`ec_sync_info_t`输入结构数组进行PDO映射处理，分为三个层次
    + sync层次 -- sync层次主要配置同步管理器的方向和看门狗设置
    + PDO层次 -- 处理PDO的时候需要两个过程，一个是对之前的PDO配置进行清除，另一个是将自定义配置的`PDO`设置到从站配置的同步管理器链表中，这个过程还会查询之前的默认配置，将之前`PDO`中的`PDO_entry`复制到`PDO`中

+ 以上两种PDO配置并不冲突，可以理解为前者是从站的默认配置，后者是用户为了个性化自定义配置（有无均可，只不过自定义的化可能会有冗余信息）