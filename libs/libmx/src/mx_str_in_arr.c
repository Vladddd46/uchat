#include "libmx.h"

int mx_str_in_arr(char *str, char **arr) {
    for(int i = 0; arr[i]; i++) {
        if (!strcmp(str, arr[i]))
            return 1;
    }
    return 0;
}

