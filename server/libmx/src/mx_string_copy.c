#include "libmx.h"

// the same as mx_strdup().
char *mx_string_copy(char *str) {
    char *copy = mx_strnew(mx_strlen(str));

    for(int i = 0; str[i]; i++)
        copy[i] = str[i];
    return copy;
}


