## EtherCAT 配置流程

1. init master
2. init slave
3. init pdo
4. init pdo_entry
5. config pdo_entry
6. config pdo
7. config slave 
8. config master
9.  config sdo
10. lock memory
11. start master
12. start slave

## EtherCAT 通讯流程

1. master receive 
2. slave receive 
3. pdo read update
4. control strategy
5. pdo write update
6. master sync
7. slave send 
8. master send

## PDO 

+ pdo 可以分为三级
  + SM(sync manager)，每个SM可以同步多个 pdo
  + pdo，每个 pdo 包含多个 pdo entry
  + pdo entry，每个 pdo entry 对应一个 index 和 subindex
