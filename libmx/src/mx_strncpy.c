#include "libmx.h"

// Copies len data from src. to dst.
char *mx_strncpy(char *dst, char *src, int len) {
    char *temp = dst;
    int i = 0;  

    for (; i < len; i++)
        *dst++ = *src++;
   return temp;
}

