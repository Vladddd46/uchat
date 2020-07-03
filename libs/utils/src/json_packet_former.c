#include "utils.h"

/*
 * Creates json string by given values.
 * Takes undefined number of str. arguments. "key:value".
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
    char *key;
    char *value;
    cJSON *packet     = cJSON_CreateObject();
    char  *packet_str = NULL;

    for (int i = 0; i < num; ++i) {
        char *str = va_arg(valist, char *);
        char **arg = mx_strsplit(str, ':');
        key   = arg[0];
        value = arg[1];
    
        cJSON *json_value = cJSON_CreateString(value);
        cJSON_AddItemToObject(packet, key, json_value);
        if (json_error(json_value))
            return NULL;
    }
    
    packet_str = cJSON_Print(packet);
    // cJSON_Delete(packet); // ??? after 5 iterations there was malloc error.
    va_end(valist);
    return packet_str;
}


