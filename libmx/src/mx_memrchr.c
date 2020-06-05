#include "libmx.h"

/*
 * The mx_memrchr function is like the mx_memchr function, 
 * except that it searches backward from 
 * the end of the n bytes pointed to by s instead 
 * of forward from the beginning.
 */
void *mx_memrchr(void *s, int c, size_t n) {
    unsigned long len = (unsigned long)n;
    unsigned char *s1 = (unsigned char *)s;

    for (;len - 1 >= 0; len--) {
        if (s1[len] == c)
            return &s1[len];
    }
    return NULL;
}
