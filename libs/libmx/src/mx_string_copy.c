#include "libmx.h"

static void error_msg() {
	char *msg = "mx_string_copy error| one of the values is NULL";

	write(2, msg, (int)strlen(msg));
	exit(1);
}

// Copies str into new allocated memmory.
char *mx_string_copy(char *str) {
	if (str == NULL)
		error_msg();
    char *new_str = mx_strnew((int)strlen(str));

    for (int i = 0; str[i]; ++i) {
        new_str[i] = str[i];
    }
    return new_str;
}
