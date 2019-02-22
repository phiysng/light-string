# light-string

This Project mainly came from Redis 2.6.

String in C is weak and immutable since cstr is is just a char array and the length of char array is fixed.

Modern Language Like Java/Python has powerful support for string with with we can append ... quickly
Redis has its sds(Simple Dynamic String) to deal with string operation and I found the concept it has is really good so I extract it out.

the sds has three component,the length str already occupied the space left and the array that actually store the data.
```c
typedef char *sds;

struct sdshdr {
    uint64_t len;//buf 已占用长度
    uint64_t free; // 剩余长度
    char buf[];//C99特性 柔性数组成员

};
```
The memory the ```struct sdshdr```use is as followed:

| len  | free | 不包含'\0'的字符串 | 终结符'\0' |
| ---- | ---- | ------------------ | ---------- |
| 8    | 8    | s                  | 1          |



```struct sdshdr```的大小实际上为8个字节，buf[]是C99特性，不占据实际空间；

在实际的使用中，我们分配一块内存，内存大小为**sizeof(struct sdshdr) + len + free + 1**.
将前一部分16个字节保留给结构体，最后一个字节留给```'\0'```,中间的空间属于str.
这种实现方式比较类似Pascal等的实现，`len()`等操作O(1)时间内就可以完成，同时包含很多字符串操作函数。

在实现的时候，我们返回结构体后面`st`r开始的地址，而如果需要访问结构体，只需对指向字符串的指针往回移动```sizeof(struct sdshdr)```个字节就好。


