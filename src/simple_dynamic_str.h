//
// Created by WuYuanshou on 2019/2/22.
//

#ifndef LIGHT_STRING_SIMPLE_DYNAMIC_STR_H
#define LIGHT_STRING_SIMPLE_DYNAMIC_STR_H

#define SDS_MAX_PREALLOC (1024*1024)

#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
/**
 * \brief 类似于C++的string类的数据结构与相关函数
 * \typedef char *sds
 *
 */
typedef char *sds;

struct sdshdr {
    uint64_t len;//buf 已占用长度
    uint64_t free; // 剩余长度
    char buf[];//C99特性 柔性数组成员

};

//sdshdr的内存结构为 | 4 | 4 | str
//其中sizeof(struct sds) -> 8 即柔性数组只是一个符号，不占据实际的内存空间，
// 而从sds字符串获得struct sdshdr只需指针前移8个字节
//类似的技巧参见Linux内核 task_struct 结构体组织可重用的双向链表的做法


static inline size_t sdslen(const sds s)//指针常量
{
    struct sdshdr *sh = (void*) (s- (sizeof(struct sdshdr)));
    return sh->len;
}

static inline size_t sdsavail(const sds s) {
    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
    return sh->free;
}

sds sdsnewlen(const void *init, size_t initlen);
sds sdsnew(const char *init);
sds sdsempty();
sds sdsdup(const sds s);
void sdsfree(sds s);
sds sdsgrowzero(sds s, size_t len);
sds sdscatlen(sds s, const void *t, size_t len);
sds sdscat(sds s, const char *t);
sds sdscatsds(sds s, const sds t);
sds sdscpylen(sds s, const char *t, size_t len);
sds sdscpy(sds s, const char *t);

sds sdscatvprintf(sds s, const char *fmt, va_list ap);
#ifdef __GNUC__
sds sdscatprintf(sds s, const char *fmt, ...)
__attribute__((format(printf, 2, 3)));
#else
sds sdscatprintf(sds s, const char *fmt, ...);
#endif

sds sdstrim(sds s, const char *cset);
sds sdsrange(sds s, int start, int end);
void sdsupdatelen(sds s);
void sdsclear(sds s);
int sdscmp(const sds s1, const sds s2);
sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count);
void sdsfreesplitres(sds *tokens, int count);
void sdstolower(sds s);
void sdstoupper(sds s);
sds sdsfromlonglong(long long value);
sds sdscatrepr(sds s, const char *p, size_t len);
sds *sdssplitargs(const char *line, int *argc);
void sdssplitargs_free(sds *argv, int argc);
sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen);

/* Low level functions exposed to the user API */
sds sdsMakeRoomFor(sds s, size_t addlen);
void sdsIncrLen(sds s, int incr);
sds sdsRemoveFreeSpace(sds s);
size_t sdsAllocSize(sds s);


#endif //LIGHT_STRING_SIMPLE_DYNAMIC_STR_H
