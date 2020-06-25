#include"libmx.h"

/*
 * Integer to ASCII convertation.
 */

static int len_counter(int number) {
    long number2 = number;
    int len = 0;

    if(number < 0)
        number2 *= -1;

    while(number2 != 0){
        number2 = number2/10;
        len++;
    }
    return len;
}

char *mx_itoa(int number) {
    if(number == 0)
        return mx_string_copy("0");
    char *result = mx_strnew(100);
    int len = len_counter(number);

    if(number < 0)
        len++;
    if(number < 0) {
        result[0] = '-';
        number *= -1;
    }
    while(number != 0){
        result[len - 1] = number % 10 + 48;
        number = number / 10;
        len--;
    }
    return result;
}
