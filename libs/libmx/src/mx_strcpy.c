#include "libmx.h"

static void error_msg() {
    char *msg = "mx_strcpy error| one of the values is NULL";

    write(2, msg, (int)strlen(msg));
    exit(1);
}

// Copies str from src to dst.
char *mx_strcpy(char *dst, char *src) {
    if (dst == NULL || src == NULL)
        error_msg();
    int counter = 0;

    while(src[counter]) {
        dst[counter] = src[counter];
        counter++;
    }
    dst[counter] = '\0';
    return dst;
}
