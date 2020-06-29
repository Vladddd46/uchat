#include "libmx.h"

/*
 * Has the same behaviour as standart memccpy c function.
 */
void *mx_memccpy(void *restrict dst, void *restrict src, int c, size_t n) {
    unsigned long len = n;
    unsigned char *dst1 = (unsigned char *)dst;
    unsigned char *src1 = (unsigned char *)src;
    unsigned long i = 0;
    
    for(; i < len; i++) {
        if (src1[i] == c) {
            dst1[i] = src1[i];
            return &dst1[i+1];
        }
        dst1[i] = src1[i];
    }
    return NULL;
}



