#include "libmx.h"

/*
 * Takes str and char.
 * Allocates mem for new str + c
 * returns new str + c
 */

char *mx_char_to_str_add(char *str, char c) {
    char *new_str = mx_strnew((int)strlen(str) + 1);
    int i = 0;

    for (; str[i]; ++i)
        new_str[i] = str[i];
    new_str[i] = c;

    return new_str;
}

