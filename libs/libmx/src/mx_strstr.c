#include "libmx.h"

// The same behaviour of std. strstr.
char *mx_strstr(char *haystack, char *needle) {
    int len_needle = mx_strlen(needle);
    int i = 0;

    while(haystack[i]) {
        // identity of first symbols.
        if (haystack[i] == needle[0]) {
            // further checking of str. identity.
            int j = 0;
            int tmp = i;
            while (haystack[tmp] == needle[j]){
                // needle found of haystack.
                if (j == len_needle - 1) {
                    char *p = (char *)&haystack[i];
                    return p;
                }
                j++;
                tmp++;
            }
        }
        i++;
    }
    return NULL;
}
