#include "libmx.h"

/*
 * Returns the result of pow times 
 * multiplying the number n by itself
 */
double mx_pow(double n, unsigned int pow){
    if (pow == 0)
        return 1;
    double result = n;

    while(pow != 1){
        result *= n;
        pow--;
    }
    return result;
}

