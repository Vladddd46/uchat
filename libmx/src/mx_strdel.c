#include "libmx.h"

// Frees mem. of *str and repoints in to NULL.
void mx_strdel(char **str) {
    free(*str);
    *str = NULL;
}

