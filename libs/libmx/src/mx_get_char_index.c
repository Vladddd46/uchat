#include "libmx.h"

/*
 * Return index of the first occurrence.-1  
 * if no occurrence found and -2 if string does not exist.
 */
int mx_get_char_index(char *str, char c) {
    if (!str)
        return -2;
    int i = 0;

    while(str[i]) {
        if (str[i] == c)
            return i;
        i++;
    }
    return -1;
}

