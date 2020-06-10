#include "libmx.h"

int mx_strlen(char *s) {
    int counter = 0;

    while(s[counter])
        counter++;
    return counter;
}

