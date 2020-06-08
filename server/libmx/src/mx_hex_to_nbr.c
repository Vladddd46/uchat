#include"libmx.h"

/*
 * Converts number from hex to decimal.
 */
unsigned long mx_hex_to_nbr(char *hex) {
    int i = 0;
    unsigned long result = 0;
    long  multipl = 1;

    while(hex[i] != '\0')
        i++;
    
    for(i -=1; i >= 0; i--) {
        if(hex[i] >= '0' && hex[i] <= '9') {
            result += (hex[i] - 48) * multipl;
            multipl *= 16;
        }
        else if(hex[i] >= 'A' && hex[i] <= 'F') {
            result += (hex[i] - 55) * multipl;
            multipl *= 16;
        }
        else if(hex[i] >= 'a' && hex[i] <= 'f') {
            result += (hex[i] - 87) * multipl;
            multipl *= 16;
        }
    }
    return result;
}

