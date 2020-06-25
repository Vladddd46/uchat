#include "libmx.h"

// prints str on stdout.
void mx_printstr(char *s){
    int length = mx_strlen(s);

    for (int i = 0; i < length; i++)
        write(1, &s[i], 1);
}
