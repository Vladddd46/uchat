#include "libmx.h"

// The same as std. strcmp
int mx_strcmp(char *s1, char *s2){
    int counter = 0;
    
    while (s1[counter] == s2[counter]) {
        if (s1[counter] == '\0' && s2[counter] == '\0')
            return 0;
    counter++;
    }
    return s1[counter] - s2[counter];
}
