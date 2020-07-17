#include "crypt.h"

// Conver string to int array with ASCII symbol numbers
int *mx_get_input_message(char* user_write) {
    int len = mx_strlen(user_write);
    int *result;
    char *msg;

    result = malloc(sizeof(int) * (len + 1));
    if (result == NULL) {
        msg = "Malloc Error\n";
        write(2, msg, (int)strlen(msg));
    }

    for(int i = 0; i < len; i++)
        *(result + i) = *(user_write + i);
    *(result + len) = -1;
    return result;
}
