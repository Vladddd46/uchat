#include "libmx.h"

// Copies str from src to dst.
char *mx_strcpy(char *dst, char *src) {
    int counter = 0;

    while(src[counter]) {
        dst[counter] = src[counter];
        counter++;
    }
    dst[counter] = '\0';
    return dst;
}
