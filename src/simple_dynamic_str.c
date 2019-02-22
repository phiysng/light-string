//
// Created by WuYuanshou on 2019/2/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "simple_dynamic_str.h"

sds sdsnewlen(const void *init, size_t initlen) {
    struct sdshdr *sh;
    size_t len = sizeof(struct sdshdr) + initlen + 1;
    if (init) {
        sh = malloc(len);
    } else {
        sh = calloc(1, len);//sizeof(char) = 1
    }
    if (sh == NULL) return NULL;
    sh->len = initlen;
    sh->free = 0;
    //如果给定init 且initlen != 0
    if (initlen && init) {
        memcpy(sh->buf, init, initlen);
    }
    sh->buf[initlen] = '\0';

    return (sds) sh->buf;

}

//创建一个只包含空字符串的sds
sds sdsempty(void) {
    return sdsnewlen("", 0);
}

//根据指定的cstr init 创建sds
//如果init == NULL 创建只包含 '\0'的sds
sds sdsnew(const char *init) {
    size_t initlen = (init == NULL) ? 0 : strlen(init);
    return sdsnewlen(init, initlen);
}

//复制指定sds
sds sdsdum(const sds s) {
    return sdsnewlen(s, sdslen(s));
}

//释放sds所对应的sdshdr所对应的结构的内存
//注意检查NULL指针
void sdsfree(sds s) {
    if (s == NULL) return;
    free(s- sizeof(struct sdshdr));
}

//更新sdshdr中的len
void sdsupdatelen(sds s){
    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));

    size_t reallen = strlen(s);

    sh->free += (sh->len - reallen);
    sh->len = reallen;
}

//清空sds中的内容使之成为空串
void sdsclear(sds s){
    struct sdshdr *sh =  (void*) (s-(sizeof(struct sdshdr)));

    sh->free += sh->len;
    sh->len = 0;
    sh->buf[0] = '\0';
}


