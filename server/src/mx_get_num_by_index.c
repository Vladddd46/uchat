#include "uchat.h"

/* Return encrypted ASCII number by argument index in a string of type: xx-yy-zz-zz-zz */

int mx_get_num_by_index(char* str, int index) {
    char* part_str = mx_strnew(10);
    int num1 = 0;
    int counter = 0;
    int ind = 0;

    for(; counter < index; ind++) {
        if(*(str + ind) == '-') {
            counter++;
        }
    }
    for(int i = 0; *(str + ind) != '-' && *(str + ind) != '\0'; ind++, i++) {
        *(part_str + i) = *(str + ind);
    }
    num1 = atoi(part_str);
    return num1;
}
