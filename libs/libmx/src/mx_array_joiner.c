#include "libmx.h"

// Joins array into one string.
char *mx_array_joiner(char **arr) {
    int len = 0;
    for (int i = 0; arr[i]; ++i)
        len += (int)strlen(arr[i]);

    char *joined_str = mx_strnew(len);
    int index = 0;
    for (int i = 0; arr[i]; ++i) {
        for (int j = 0; arr[i][j]; ++j) {
            joined_str[index] = arr[i][j];
            index++;
        }
    }

    return joined_str;
}
