#include "libmx.h"

static void error_msg() {
	char *msg = "mx_strcmp error| one of the values is NULL";

	write(2, msg, (int)strlen(msg));
	exit(1);
}

// The same as std. strcmp
int mx_strcmp(char *s1, char *s2) {
	if (s1 == NULL || s2 == NULL)
		error_msg();
    int counter = 0;
    
    while (s1[counter] == s2[counter]) {
        if (s1[counter] == '\0' && s2[counter] == '\0')
            return 0;
    	counter++;
    }
    return s1[counter] - s2[counter];
}
