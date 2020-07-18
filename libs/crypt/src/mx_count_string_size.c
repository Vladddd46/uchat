#include "crypt.h"

// void unit_test_mx_count_string_size() {
//     int t1 = mx_count_string_size("1-2-3-4-5-6-7-8-9");
//     int t2 = mx_count_string_size("1-2-3");
//     int t3 = mx_count_string_size("1-2-3-4-5");

//     printf("Output vs Funcs.Output\n");
//     printf("7=%d\n", t1);
//     printf("1=%d\n", t2);
//     printf("3=%d\n", t3);
// }

/*
 *  Return amount of words in a crypted string 
 *  with formant: xx-yy-zz-zz-zz 
 */
int mx_count_string_size(char *str) {
    int counter = 0;

    for(int i = 0; str[i]; i++) {
        if(*(str + i) == '-') {
            counter++;
        }
    }
    counter--;
    return counter;
}
