### C库函数

calloc()
+ C库函数`void *calloc(size_t nitems, size_t size)`分配所需的内存空间,并返回一个指向它的指针
  + nitems -- 要被分配的元素的个数
  + size   -- 元素的大小
+ malloc和calloc之间的不同点是:malloc不会设置内存为零,而calloc会设置分配的内存为零