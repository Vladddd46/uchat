#include "server.h"

/*
 * Creates json string.
 * Takes undefined number of str. arguments. "key=value".
 * Returns string in json format: {'key': 'value', ..., 'keyX':'valueX'}
 */

static int json_error(cJSON *object) {
    if (object == NULL) {
        cJSON_Delete(object);
        return 1;
    }
    return 0;
}

char *json_packet_former(int num, ...) {
    va_list valist;
    va_start(valist, num);
    cJSON *packet     = cJSON_CreateObject();
    char  *packet_str = NULL;

    for (int i = 0; i < num; ++i) {
        char *str = va_arg(valist, char *);
        char data[(int)strlen(str) + 1];
        int i = 0;
        for (; str[i]; ++i)
            data[i] = str[i];
        data[i] = '\0';

        char *value_str = strtok(data, "=");
        char *key_str   = strtok(NULL, "=");
        cJSON *value = cJSON_CreateString(value_str);
        cJSON_AddItemToObject(packet, key_str, value);
        if (json_error(value))
            return NULL;
    }
    
    packet_str = cJSON_Print(packet);
    cJSON_Delete(packet);
    va_end(valist);
    return packet_str;
}


