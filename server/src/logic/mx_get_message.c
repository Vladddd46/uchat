#include "server.h"

static chat_message_t* mx_fill_list(int chat_id, int from, int to) {
    chat_message_t* list = malloc(sizeof(chat_message_t));
    chat_message_t* head = list;
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    char sql[100];
    
    sprintf(sql, "SELECT SENDER, TIME, MESSAGE FROM MESSAGES WHERE CHATID='%s';", mx_itoa(chat_id));
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    for(int i = 0; i < from; i++) {
        sqlite3_step(res);
    }
    sqlite3_step(res);
    for(int i = from; i < to && sqlite3_column_text(res, 0) != NULL; i++) {
        list -> sender = mx_string_copy((char*)sqlite3_column_text(res, 0));
        list -> time = mx_string_copy((char*)sqlite3_column_text(res, 1));
        list -> message = mx_string_copy((char*)sqlite3_column_text(res, 2));
        list -> next = (chat_message_t*)malloc(sizeof(chat_message_t));
        list = list -> next;
        list -> next = NULL;
        sqlite3_step(res);
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    return head;
}

static char* mx_get_all_users(int chat_id) {
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    char *users = "";

    sprintf(sql, "SELECT USERS.LOGIN FROM USERCHAT INNER JOIN USERS ON USERS.ID = USERCHAT.USERID AND USERCHAT.CHATID=%d;", chat_id);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    while(sqlite3_column_text(res, 0) != NULL) {
        char* second_user = mx_string_copy((char*)sqlite3_column_text(res, 0));
        users = mx_strjoin(users, second_user);
        users = mx_strjoin(users, " ");
        sqlite3_step(res);
    }

    sqlite3_finalize(res);
    sqlite3_close(db);  
    return users;
}

static int mx_list_len(chat_message_t* chat) {
    int len = 0;
    chat_message_t* head = chat;

    while(chat -> next != NULL) {
        chat = chat -> next;
        len++;
    }
    head = chat;
    return len;
}

static char *mx_json_packet_former_from_list(chat_message_t* chat, int from, char *chat_name, char* all_users) {
    int list_len = mx_list_len(chat);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("msg_s");

   // printf("\nLEN = %d\n", list_len);
    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(chat_name);
    cJSON_AddItemToObject(packet, "TO", json_value);
    for(int i = 0; i < list_len; i++, from++) {
        char packet_former[100];

        sprintf(packet_former, "ID%d", i);
        json_value = cJSON_CreateString(mx_itoa(from));
        cJSON_AddItemToObject(packet, packet_former, json_value);
        json_value = cJSON_CreateString(mx_itoa(list_len));
        cJSON_AddItemToObject(packet, "MSGLEN", json_value);
        json_value = cJSON_CreateString(all_users);
        cJSON_AddItemToObject(packet, "ALLUSERS", json_value);
        json_value = cJSON_CreateString(chat -> sender);
        sprintf(packet_former, "SENDER%d", i);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        json_value = cJSON_CreateString(chat -> time);
        sprintf(packet_former, "TIME%d", i);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        json_value = cJSON_CreateString(chat -> message);
        sprintf(packet_former, "MESSAGE%d", i);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        chat = chat -> next;
    }
    packet_str = cJSON_Print(packet);
    
    return packet_str;
}

char *mx_get_message(char* packet) {
    char *chat_id_str = get_value_by_key(packet, "CHATID");
    int chat_id       = atoi(chat_id_str);
    int from = atoi(get_value_by_key(packet, "FROMMSG"));
    int to = atoi(get_value_by_key(packet, "TOMSG"));
    char* chat_name = get_value_by_key(packet, "CHATNAME");

    chat_message_t* list = mx_fill_list(chat_id, from, to);
    char* all_users = mx_get_all_users(chat_id);
    char* return_packet = mx_json_packet_former_from_list(list, from, chat_name, all_users);

    return return_packet;   
}
