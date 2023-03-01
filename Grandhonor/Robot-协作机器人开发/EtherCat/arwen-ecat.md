## ethercat

### 1.1 启动，设置

+ ethercat都是在root用户下执行命令

+ 设置从站
  + ethercat alias -p 2 0:2

+ 启动ethercat
  + `/etc/init.d/ethercat start`

+ 查看状态
  + `ethercat slv`

### 1.2 调试命令

+ 查看从站状态码
  + `ethercat upload -t int16 -p 0 0x603f 00`

+ 查看从站位置：
  + `ethercat upload -t int32 -p 0 0x6064 00`

### 1.2 demo_webserver.c 分析

### 数据结构

#### `ec_pdo_entry_info_t`

+ 简介：PDO条目配置信息。这是`ec_pdo_info_t`中的`entries`字段的数据类型
+ 声明：
  ```
    typedef struct {
      uint16_t index;      /**< PDO entry index. */
      uint8_t  subindex;   /**< PDO entry subindex. */
      uint8_t  bit_length; /**< Size of the PDO entry in bit. */
    } ec_pdo_entry_info_t;
  ``` 

#### `ec_pdo_info_t`

+ 简介：PDO配置信息。这是`ec_sync_info_t`中的`pdos`字段的数据类型
+ 声明：
  ```
    typedef struct {
      uint16_t index;              /**< PDO index. */
      unsigned int n_entries;      /**< 要映射的entries PDO条目数 (0表示使用默认映射，这只能在从服务器处于总线配置时完成)*/
      ec_pdo_entry_info_t *entries;/**< 要映射的PDO项数组。可以是NULL，或者必须包含至少n_entries个值*/
    } ec_pdo_info_t;
  ``` 

#### `ec_sync_info_t`

+ 简介：同步管理器配置信息。这可以用于配置多个同步管理器，包括PDO分配和PDO映射。它被作为`ecrt_slave_config_pdos()`函数的输入参数使用
+ 声明：
  ```
    typedef struct {
      uint8_t index;  /**< 同步管理器索引。Sync manager index.Must be less than #EC_MAX_SYNC_MANAGERS for a valid sync manager,but can also be \a 0xff to mark the end of the list. */
      ec_direction_t dir;  /**<同步管理器方向 */
      unsigned int   n_pdos;  /**< PDOs在pdos结构体数组中的数量 */
      ec_pdo_info_t  *pdos;  /**<带有要分配的pdo的数组。所包含的PDOs必须不少于n_pdos
      ec_watchdog_mode_t watchdog_mode;  /**< 看门狗模式 */
    } ec_sync_info_t;
  ``` 

#### `ec_master_t`

+ 简介：主站

#### `ecrt_master_state_t`

+ 简介：主站状态，这个是用于函数`ecrt_master_state()`函数的输出参数
+ 声明：
  ```
    typedef struct {
      unsigned int slaves_responding;  // 所有Ethernet设备响应从站的总和
      unsigned int al_states : 4;      // 所有从站的应用层状态。状态被编码在较低的4位。如果设置了一个比特位，就意味着至少有一个从站在主线上响应：Bit 0: \a INIT；Bit 1: \a PREOP；Bit 2: \a SAFEOP；Bit 3: \a OP */
      unsigned int link_up : 1;        // true，如果至少有一个 Ethernet link是在线的，则为true
    } ec_master_state_t;
  ``` 

#### `ec_slave_config_t`

+ 简介：从站配置

#### `ec_slave_config_state_t`

+ 简介：从站配置状态。它用于函数`ecrt_slave_config_state()`的输出参数
+ 声明：
  ```
    typedef struct {
      unsigned int online : 1;      // 这个从站是在线的
      unsigned int operational : 1; // 这个从站通过指定配置进入OP状态
      unsigned int al_state : 4;    // 应用层的从站状态：1: \a INIT；2: \a PREOP；4: \a SAFEOP；8: \a OP
    } ec_slave_config_state_t;
  ``` 

#### `ec_domain_t`

+ 简介：域

#### `ec_wc_state_t`

+ 简介：域工作计数器状态说明。这个是在`ec_domain_state_t`中使用
+ 声明：
  ```
    typedef enum {
      EC_WC_ZERO = 0,   // 没有交换注册的过程数据
      EC_WC_INCOMPLETE, // 交换了一些已注册的过程数据(部分过程数据)
      EC_WC_COMPLETE    // 交换了所有已注册的过程数据
    } ec_wc_state_t;
  ``` 

#### `ec_domain_state_t`

+ 简介：域状态。它被作为函数`ecrt_domain_state()`的输出参数使用
+ 声明：
  ```
    typedef struct {
      unsigned int working_counter;   // 最后一个工作计数器的值
      ec_wc_state_t ws_state;         // 工作计数器状态说明
      unsigned int redundancy_active; // 冗余链路正在使用
    } ec_domain_state_t;
  ``` 

#### `ec_pdo_entry_reg_t`

+ 简介：列出PDO条目批量注册的记录类型。此类型用于`ecrt_domain_reg_pdo_entry_list()`的数组参数。
+ 声明：
  ```
    typedef struct {
      uint16_t alias;             // 从站别名地址
      uint16_t position;          // 从站位置
      uint32_t vendor_id;         // 从站供销商ID
      uint32_t product_code;      // 从站产品码
      uint16_t index;             // PDO条目索引
      uint8_t  subindex;          // PDO条目子索引
      unsigned int *offset;       // 指向在进程数据中存储PDO条目(字节-)偏移量的变量的指针。
      unsigned int *bit_position; // 指向一个变量的指针，用于在\a偏移量内存储位位置(0-7)。可以为NULL，在这种情况下，如果PDO条目不字节对齐会引发错误
    } ec_pdo_entry_reg_t;
  ``` 

### API

#### `ecrt_master_create_domain`

+ 简介：创建一个新的过程数据域。对于流程数据交换，至少需要一个流程数据域。这个方法创建一个新的过程数据域，并返回一个指向新域对象的指针。这个对象能够在循环操作中用于注册PDOs和交换PDOs
+ 声明：`ec_domain_t *ecrt_master_create_domain( ec_master_t *master);`

#### `ecrt_request_master`

+ 简介：请求EtherCAT主机进行实时操作。
  + 在应用程序可以访问EtherCAT主机之前，它必须预留一个专用的主机。
  + 在用户空间，这是`ecrt_open_master()`和`ecrt_master_reserve()`的方便函数。
  + 这个函数必须是应用程序使用EtherCAT时必须调用的第一个函数
  + 该函数以master的索引作为参数。第一个主节点的索引为0，第n个主节点的索引为n- 1。
  + 在加载master时，必须指定master的数量。
+ 声明：`ec_master_t *ecrt_request_master(unsigned int master_index);`

#### `ecrt_master_sdo_upload`

+ 简介：执行SDO上传请求从从站读取数据。
  + 此请求由主状态机处理。
  + 他的方法会阻塞，直到请求被处理，并且不能在实时上下文中调用。
+ 声明：`int ecrt_master_sdo_upload(ec_master_t *master, uint16_t slave_position, uint16_t index, uint8_t subindex, uint8_t *target, size_t target_size, size_t *result_size, uint32_t *abort_code);`
+ 参数：
  + `master`          --  EtherCAT主站
  + `slave_position`  --  从站位置
  + `index`           --  SDO索引
  + `subindex`        --  SDO的子索引
  + `target`          --  上传的目标缓冲区。
  + `target_size`     --  目标缓冲区的大小
  + `result_size`     --  已经上传的数据大小
  + `abort_code`      --  SDO上传的中止代码。
+ 返回值：
  + 成功 --  0
  + 失败 --  < 0

#### `ecrt_master_sdo_download`

+ 简介：执行SDO下载请求，将数据写入从站。
  + 此请求由主状态机处理。
  + 他的方法会阻塞，直到请求被处理，并且不能在实时上下文中调用。
+ 声明：`int ecrt_master_sdo_download(ec_master_t *master, uint16_t slave_position, uint16_t index, uint8_t subindex, uint8_t *data, size_t data_size, uint32_t *abort_code);`
+ 参数：
  + `master`          --  EtherCAT主站
  + `slave_position`  --  从站位置
  + `index`           --  SDO索引
  + `subindex`        --  SDO的子索引
  + `data`            --  要下载的数据缓冲区
  + `data_size`       --  数据缓冲区大小
  + `abort_code`      --  SDO上传的中止代码。
+ 返回值：
  + 成功 --  0
  + 失败 --  < 0

#### `ecrt_domain_reg_pdo_entry_list`

+ 简介：为一个域注册一堆PDO条目。此方法必须在`ecrt_master_activate()`之前在非实时上下文中调用。
+ 声明：`int ecrt_domain_reg_pdo_entry_list(ec_domain_t *domain, const ec_pdo_entry_reg_t *pdo_entry_regs);`
+ 参数：
  + `domain`  -- 域
  + `pdo_entry_regs`  -- PDO注册数组。注册数组必须以一个空结构体结束，或者将\a索引字段设置为0 !
+ 返回值：
  + 成功  -- 0
  + 失败  -- 其他

#### `ecrt_master_activate`

+ 简介：完成配置阶段并为循环操作做准备。
  + 这个函数告诉主机配置阶段已经完成，将开始实时操作。
  + 该函数为域分配内部内存，并为域成员计算逻辑FMMU地址。
  + 它告诉主状态机现在要应用总线配置。
  + 调用此函数后，实时应用程序负责循环调用`ecrt_master_send()`和`ecrt_master_receive()`以确保总线通信。
  + 在调用这个函数之前，由主线程负责，所以这些函数可能不会被调用!
  + 该方法本身分配内存，不应该在实时上下文中调用。
+ 声明：`int ecrt_master_activate(ec_master_t *master);`
+ 参数：
  + `master`  --  EtherCAT 主站
+ 返回值：
  + 成功  -- 0
  + 失败  -- < 0

#### `ecrt_domain_data`

+ 简介：返回域的过程数据。
  + 在内核上下文中:
    + 如果使用`ecrt_domain_external_memory()`提供外部内存，则返回的指针将包含该内存的地址。
    + 否则它将指向内部分配的内存。
    + 在后一种情况下，在`ecrt_master_activate()`之前不能调用此方法。
  + 在用户空间上下文中:
    + 必须在`ecrt_master_activate()`之后调用此方法以获取映射的域进程数据内存。
+ 声明：`uint8_t *ecrt_domain_data(ec_domain_t *domain);`
+ 参数：
  + `domain`  --  域
+ 返回值：
  + 返回指向过程数据内存区域的指针

#### `ecrt_master_select_reference_clock`

+ 简介：为分布式时钟选择参考时钟。如果这个方法没有被某个主时钟调用，或者从时钟配置指针为NULL，那么第一个具有DC功能的从时钟将提供参考时钟。
+ 声明：`int ecrt_master_select_reference_clock(ec_master_t *master, ec_slave_config_t *sc);`
+ 参数：
  + `master`  --  EtherCAT 主站
  + `sc`      --  Slave的Slave配置要引用的Slave(或NULL)。
+ 返回值：
  + 成功  -- 0
  + 失败  --  负数，错误码

#### `ecrt_master_application_time`

+ 简介：设置应用时间。在使用分布式时钟操作从服务器时，主服务器必须知道应用程序的时间。主程序本身不会增加时间，因此必须循环调用此方法。
  + 传递给该方法的时间用于计算从服务器的SYNC0/1中断的阶段。它应该经常在实时周期的同一点被调用。因此，建议在计算开始时调用它，以避免由于执行时间的变化而导致的偏差。
  + 该时间用于设置从机的系统时间偏移和循环操作开始时间寄存器，以及通过ecrt_master_sync_reference_clock()将DC参考时钟同步到应用程序时间。
  + 时间定义为从2000-01-01 00:00开始的纳秒。可以使用EC_TIMEVAL2NANO()宏来转换epoch时间，但这不是必需的，因为绝对值无关紧要
+ 声明：`void ecrt_master_application_time(ec_master_t *master, uint64_t app_time);`
+ 参数：
  + `master`  --  EtherCAT 主站
  + `app_time`  --  应用时间

#### `ecrt_master_sync_reference_clock`

+ 简介：将DC参考时钟漂移补偿数据报排队发送。参考时钟将被同步到由最后一次调用取消ecrt_master_application_time()提供的应用程序时间。
+ 声明：`void ecrt_master_sync_reference_clock(ec_master_t *master);`
+ 参数：
  + `master`  --  EtherCAT 主站

#### `ecrt_master_sync_slave_clocks`

+ 简介：将DC时钟漂移补偿数据报排队发送。所有从时钟同步到参考时钟。
+ 声明：`void ecrt_master_sync_slave_clocks(ec_master_t *master);`
+ 参数：
  + `master`  --  EtherCAT 主站

#### `ecrt_release_master`

+ 简介：释放一个请求的EtherCAT主机。
  + 在使用后，必须释放master，以便其他应用程序可以使用它。
  + 此方法释放所有已创建的数据结构。它不应该在实时上下文中调用。
  + 如果主站被激活，则内部调用`ecrt_master_deactivate()`。
+ 声明：`void ecrt_release_master(ec_master_t *master);`
+ 参数：
  + `master`  --  EtherCAT 主站

#### `ecrt_master_receive`

+ 简介：从硬件中获取接收到的帧并处理数据报。
  + 通过调用中断服务例程查询网络设备接收的帧。
  + 提取接收到的数据报，并将结果分派到队列中的数据报对象。
  + 接收到的数据报和超时的数据报将被标记，并退出队列
  + 必须在`ecrt_master_activate()`返回后由实时应用程序循环调用。
+ 声明：`void ecrt_master_receive(ec_master_t *master);`

#### `ecrt_domain_process`

+ 简介：确定域的数据报的状态。
  + 计算接收到的数据报的工作计数器，并在必要时输出统计信息。
  + 这必须在`ecrt_master_receive()`接收域数据报之后调用，以便使`ecrt_domain_state()`返回最后一次进程数据交换的结果。
+ 声明：`void ecrt_domain_process(ec_domain_t *domain);`

#### `ecrt_domain_queue`

+ 简介：(Re-)将所有域数据报放在主数据报队列中。调用此函数来标记域的数据报，以便在下一次调用`ecrt_master_send()`时进行交换
+ 声明：`void ecrt_domain_queue(ec_domain_t *domain);`

#### `ecrt_master_send`

+ 简介：发送队列中的所有数据报。
  + 该方法获取所有已排队等待传输的数据报，将它们放入帧中，并将它们传递给以太网设备进行发送。
  + 必须在`ecrt_master_activate()`返回后由应用程序循环调用。
+ 声明：`void ecrt_master_send(ec_master_t *master);`

#### `ecrt_domain_state`

+ 简介：读取域的状态。
  + 在给定的\a状态结构中存储域状态。
  + 利用该方法，可以实时监控过程数据交换情况。
+ 声明：`void ecrt_domain_state(const ec_domain_t *domain, ec_domain_state_t *state);`
+ 参数：
  + `domain`  --  域
  + `state`   --  指向用于存储信息的状态对象的指针。

#### `ecrt_master_state`

+ 简介：读取当前主站的状态。
  + 在给定的\a状态结构中存储主站状态。
  + 此方法返回一个全局状态。对于冗余总线拓扑中特定于链路的状态，请使用`ecrt_master_link_state()`方法。
+ 声明：`void ecrt_master_state(const ec_master_t *master, ec_master_state_t *state);`
+ 参数：
  + `master`  --  主站
  + `state`   --  指向用于存储信息的状态对象的指针

#### `ecrt_slave_config_state`

+ 简介：输出从站配置的状态。
  + 在给定的\a状态结构中存储状态信息。状态信息由主状态机更新，因此可能需要几个周期，直到它发生变化。
  + 如果需要实时监控进程数据交换的状态，则应该使用`ecrt_domain_state()`。
+ 声明：`void ecrt_slave_config_state(const ec_slave_config_t *sc, ec_slave_config_state_t *state);`
+ 参数：
  + `sc`  --  从站配置
  + `state`  --  需要写入的状态对象
