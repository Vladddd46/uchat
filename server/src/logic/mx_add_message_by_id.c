#include "server.h"

static char* mx_delete_slesh_n(char *str) {
    *(str + mx_strlen(str) - 1) = '\0';
    return str; 
}

static void mx_add_last_message(int chat_id, char* message, char* time, char* sender) {
    char *message_error;
    // char sql[1000];
    // bzero(sql, 1000);
    int check;
    int message_id = mx_get_last_message_id(chat_id);

    message_id++;
    sqlite3 *db = opening_db();
    char* sql = sqlite3_mprintf("INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(%q, %q, '%q', '%q', '%q');", mx_itoa(chat_id), mx_itoa(message_id), sender, mx_delete_slesh_n(time), mx_delete_slesh_n(message));

    printf("\n\nSQL req: %s\n\n", sql);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);

    dberror(db, check, "Error inserting to table");
    sqlite3_close(db);

}

static void mx_add_message_with_id(int message_id, int chat_id, char* message) {
    sqlite3 *db = opening_db();
    char *message_error;
    char sql[500];
    int check;

    sprintf(sql, "BEGIN; UPDATE MESSAGES SET MESSAGE = '%s' WHERE MESSAGEID = %d; COMMIT;", message ,message_id);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
    sqlite3_close(db);
}

static char *mx_json_packet_former_from_list(char* message, char* time, char* sender, int chat_id, char* all_users) {
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("add_msg_s");

    cJSON_AddItemToObject(packet, "TYPE", json_value);
    printf("===>>>%s\n", all_users);
    json_value = cJSON_CreateString(all_users);
    cJSON_AddItemToObject(packet, "TO", json_value);
    char packet_former[100];
    sprintf(packet_former, "ID0");
    json_value = cJSON_CreateString(mx_itoa(mx_get_last_message_id(chat_id)));
    cJSON_AddItemToObject(packet, packet_former, json_value);
    json_value = cJSON_CreateString("1");
    cJSON_AddItemToObject(packet, "MSGLEN", json_value);
    json_value = cJSON_CreateString(all_users);
    cJSON_AddItemToObject(packet, "ALLUSERS", json_value);
    json_value = cJSON_CreateString(sender);
    sprintf(packet_former, "SENDER0");
    cJSON_AddItemToObject(packet, packet_former, json_value);
    json_value = cJSON_CreateString(time);
    sprintf(packet_former, "TIME0");
    cJSON_AddItemToObject(packet, packet_former, json_value);
    json_value = cJSON_CreateString(message);
    sprintf(packet_former, "MESSAGE0");
    cJSON_AddItemToObject(packet, packet_former, json_value);
    packet_str = cJSON_Print(packet);
    return packet_str;
}

char* mx_add_message_by_id(char *packet) {
    char *message_id_str = get_value_by_key(packet, "MESSAGEID");
    char *time           = get_value_by_key(packet, "TIME");
    char *message        = get_value_by_key(packet, "MESSAGE");
    char *chat_id_str    = get_value_by_key(packet, "CHATID");
    char *sender         = get_value_by_key(packet, "SENDER");
    char *to             = get_value_by_key(packet, "TO");

    int message_id = atoi(message_id_str);
    int chat_id    = atoi(chat_id_str);

    if(message_id == 0)
        mx_add_last_message(chat_id, message, time, sender);
    else
        mx_add_message_with_id(message_id, chat_id, message);

    char *return_packet = mx_json_packet_former_from_list(message, time, sender, chat_id, to);

    free(message_id_str);
    free(time);
    free(message);
    free(chat_id_str);
    free(sender);
    free(to);
    printf("packet shmaket %s\n\n", return_packet);
    return return_packet;
}
