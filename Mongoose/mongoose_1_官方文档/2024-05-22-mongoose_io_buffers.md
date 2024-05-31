---
category: Mongoose
date: 2024-05-22 09:00:00 +0800
layout: post
title: mongoose_io_buffers
tag: Mongoose
---
## 简介

+ mongoose的出站入站缓冲区接口
+ IO缓冲区由结构mg_iobuf描述，是一个简单的数据结构，可以在任意偏移量插入或删除数据块，并自动增长/收缩。

## struct mg_iobuf 

+ 简介：
  + 通用IO缓冲区。size指定buf指向的数据的分配大小，len指定当前存储的字节数。

+ 原型：
```cpp
struct mg_iobuf {
  unsigned char *buf;  // Pointer to stored data
  size_t size;         // Total size available
  size_t len;          // Current number of bytes
  size_t align;        // Alignment during allocation
};
```

---

## mg_iobuf_init

+ 简介：
  + 初始化IO缓冲区，分配字节大小

+ 原型：
```cpp
int mg_iobuf_init(struct mg_iobuf *io, size_t size, size_t align);
```

+ 参数：
  + io    -- 要初始化的mg_iobuf结构的指针
  + size  -- 分配的字节数
  + align -- 将大小对齐到对齐内存边界。0表示不对齐

+ 返回值：
  + 1 -- 成功
  + 0 -- 失败

+ 示例：
```cpp
struct mg_iobuf io;
if (mg_iobuf_init(&io, 0, 64)) {
  // io successfully initialized
}
```

---

## mg_iobuf_resize 

+ 简介：
  + 调整IO缓冲区的大小，将新的大小设置为size。在此之后，io->buf指针可能会发生变化，例如缓冲区变大。如果size为0，则释放io->buf并将其设置为NULL，同时将size和len都设置为0。 得到的io->size总是与io->align字节边界对齐；因此，为了避免内存碎片和频繁的重新分配，将io->align设置为更高的值。

+ 原型：
```cpp
int mg_iobuf_resize(struct mg_iobuf *io, size_t size);
```

+ 参数：
  + io   -- 需要调整大小的iobuf
  + size -- 新的大小

+ 返回值：
  + 1 -- 成功
  + 0 -- 失败

+ 示例：
```cpp
struct mg_iobuf io;
mg_iobuf_init(&io, 0, 10);  // An empty buffer with 10-byte alignment

if (mg_iobuf_resize(&io, 1)) {
  // New io size is 10
}
```

---

## mg_iobuf_free

+ 简介：
  + 释放io->buf指向的内存并设置为NULL。size和len都被设置为0。

+ 原型：
```cpp
void mg_iobuf_free(struct mg_iobuf *io);
```

+ 参数：
  + io -- 需要释放的iobuf

+ 返回值：
  + 无

+ 示例：
```cpp
struct mg_iobuf io;
// IO buffer initialization
// ...

// Time to cleanup
mg_iobuf_free(&io);
```

---

## mg_iobuf_add 

+ 简介：
  + 在偏移量处插入数据缓冲区buf、len。如果需要，iobuf将被扩展。产生的io->size总是与io->align字节边界对齐；因此，为了避免内存碎片和频繁的重新分配，将align设置为一个较大的值。

+ 原型：
```cpp
size_t mg_iobuf_add(struct mg_iobuf *io, size_t offset, const void *buf, size_t len);
```

+ 参数：
  + io     -- 需要追加数据的iobuf
  + offset -- 追加数据的偏移
  + buf    -- 追加的数据
  + len    -- 追加数据的长度

+ 返回值：
  + 更新后iobuf的长度

+ 示例：
```cpp
struct mg_iobuf io;         // Declare buffer
mg_iobuf_init(&io, 0, 16);  // Initialise empty buffer with 16 byte alignment
mg_iobuf_add(&io, io.len, "hello", 5);  // Append "hello"
```

---

## mg_iobuf_del 

+ 简介：
  + 删除从偏移量开始的len字节，并移动剩余的字节。如果len大于io->len，则不会发生任何操作，因此这种调用会被忽略。

+ 原型：
```cpp
size_t mg_iobuf_del(struct mg_iobuf *io, size_t offset, size_t len);
```

+ 参数：
  + io -- 需要删除数据的iobuf
  + offset -- 开始位置的偏移量
  + len -- 删除的字节数

+ 返回值：
  + 更新后iobuf的长度

+ 示例：
```cpp
struct mg_iobuf io;
mg_iobuf_init(&io, 0, 16);          // Empty buffer, 16-bytes aligned
mg_iobuf_add(&io, 0, "hello", 2);   // io->len is 5, io->size is 16
mg_iobuf_del(&io, 1, 3);            // io->len is 2, io->size is still 16
```