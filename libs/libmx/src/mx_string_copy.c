#include "libmx.h"

// Copies str into new allocated memmory.
char *mx_string_copy(char *str) {
    char *new_str = mx_strnew((int)strlen(str));

    for (int i = 0; str[i]; ++i) {
        new_str[i] = str[i];
    }
    return new_str;
}
