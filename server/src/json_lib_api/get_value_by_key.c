#include "server.h"

/*
 * Takes str in json format and ket.
 * returns value stored by this key.
 * In case of no such key, NULL is returned.
 */
char *get_value_by_key(char *json_str, char *key) {
    char  *result = NULL;
    cJSON *jstr = cJSON_Parse(json_str);
    if (jstr == NULL) {
        cJSON_Delete(jstr);
        return NULL;
    }
    cJSON *value = cJSON_GetObjectItemCaseSensitive(jstr, key);
    if (cJSON_IsString(value) && (value->valuestring != NULL))
        result = mx_string_copy(value->valuestring);
    cJSON_Delete(jstr);
    return result;
}
