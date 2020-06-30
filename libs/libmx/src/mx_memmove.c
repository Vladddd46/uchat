#include "libmx.h"

/*
 * The memmove() function copies len bytes from string src to string dst.
 */
void *mx_memmove(void *dst, void *src, size_t len) {
    unsigned long len1 =(unsigned long)len;
    char *a = (char *)dst;
    char *b = (char *)src;

    for(unsigned long i = 0; i < len1; i++)
        a[i] = b[i];
    return a;
}
