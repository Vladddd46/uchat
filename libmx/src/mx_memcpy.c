#include "libmx.h"

/*
 * The memcpy() function copies n bytes 
 * from memory area src to memory area dst.
 */
void *mx_memcpy(void *restrict dst, void *restrict src, size_t n) {
    unsigned long len = n;
    char *dst1 = (char *)dst;
    const char *src1 = (char *)src;

    for (unsigned long i = 0; i < len; ++i)
        dst1[i] = src1[i];
    return dst;
}

