#include "libmx.h"

/*
 *  Convert number from decimal to hex.
 */
char *mx_nbr_to_hex(unsigned long nbr){
    unsigned long number = nbr;

    // case with 0 
    if (number == 0){
        char *p = mx_strnew(1);
        p[0] = 48;
        return p;
    }
    // Counts len of number in hex (how much chars it will have).
    unsigned long length_number = 0;
    unsigned long tmp = number;
    while(tmp != 0){
        tmp /= 16;
        length_number++;
    }
    char *hex_num = mx_strnew(length_number);

    // decimal -> hex algorithm
    for (unsigned long i = 0; number != 0; ++i, length_number--) {
        unsigned long rest = number % 16;
        number /= 16;
        if ( rest > 9 && rest < 16)
            hex_num[length_number - 1] = rest + 87;
        else if (rest >= 0 && rest <= 9)
            hex_num[length_number-1] = rest + 48;
    }
    return hex_num;
}

