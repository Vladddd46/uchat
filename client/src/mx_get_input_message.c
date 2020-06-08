#include "client.h"

/* Conver string to int array with ASCII symbol numbers */

int* mx_get_input_message(char* user_write) {
    int len = mx_strlen(user_write);
    int *result;

    // printf("%s", user_write);
    result = malloc(sizeof(int) * (len + 1));
    for(int i = 0; i < len; i++) {
        *(result + i) = *(user_write + i);
    }
    *(result + len) = -1;
    return result;
}
