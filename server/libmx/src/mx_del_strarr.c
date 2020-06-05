#include "libmx.h"

/*
 * Frees memory of array of strings.
 */
void mx_del_strarr(char ***arr) {
    if (*arr == NULL)
        return;
    for (int i = 0; (*arr)[i] != NULL; ++i)
        free((*arr)[i]);
    free(*arr);
    *arr = NULL;
}
