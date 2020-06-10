#include "libmx.h"

void mx_swap_char(char *s1, char *s2) {
    char tmp = *s2;
    *s2 = *s1;
    *s1 = tmp; 
}
