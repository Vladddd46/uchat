#include "libmx.h"

void mx_str_reverse(char *s) {
    if (s == NULL)
        return;
    int len = mx_strlen(s) - 1;
    int i = 0;

    while(i != len) {
        char tmp = s[i];
        s[i] = s[len];
        s[len] = tmp;
        len--;
        i++;
    }
}


