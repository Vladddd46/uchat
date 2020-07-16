#include "server.h"

/*
 * Retrieves needed data from the packet.
 * Makes request to db and checks data validity.
 * Forms back packet.
 */

static int json_error(cJSON *object) {
    if (object == NULL) {
        cJSON_Delete(object);
        return 1;
    }
    return 0;
}

static char* mx_confirm_users_password(char* user, char* password) {
    sqlite3 *db;
    char sql[100];
    sqlite3_stmt *res;

    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE LOGIN='%s';", user);
    sqlite3_open("uchat.db", &db);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    if(sqlite3_column_text(res, 0) == NULL) {
        return "false";
    }
    if(sqlite3_column_text(res, 0) != NULL && mx_strcmp((char*)sqlite3_column_text(res, 0), password) == 0) {
        return "success";
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return "false";
}

static char* mx_get_nickname(char* login) {
    sqlite3 *db = NULL;
    char sql[200];
    sprintf(sql, "SELECT NICKNAME FROM USERS WHERE LOGIN='%s';", login);
    sqlite3_stmt *res;
    char* nickname;

    sqlite3_open("uchat.db", &db);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    nickname = (char*)sqlite3_column_text(res, 0);
    return nickname;
}

static int mx_list_len(chats_t* chat) {
    int len = 0;
    chats_t* head = chat;

    while(chat -> chat_name != NULL) {
        chat = chat -> next;
        len++;
    }
    head = chat;
    return len;
}

static char* mx_get_special_chat_name(char* chat_name, char* login) {
    char* result = mx_strnew(mx_strlen(chat_name) + 2);

    if(*(login) != *(chat_name)) {
        char* str = strstr(chat_name, login);
        int len = mx_strlen(chat_name) - mx_strlen(str);

        for(int i = 0; i < len; i++) {
            *(result + i) = *(chat_name + i);
        }
        *(result + mx_strlen(result)) = '(';
        result = mx_strjoin(result, str);
        *(result + mx_strlen(result)) = ')';
    }
    else {
        char* str = strstr(chat_name, login);
        int len = mx_strlen(chat_name) - mx_strlen(str);

        for(int i = 0; i < len; i++) {
            *(result + i) = *(chat_name + mx_strlen(login));
        }
        *(result + mx_strlen(result)) = '(';
        result = mx_strjoin(result, str);
        *(result + mx_strlen(result)) = ')';
    }
    return result;
}

static char *json_packet_former_from_list(chats_t *chat, char *status, char* login) {
    int list_len = mx_list_len(chat);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("login_s");
    char *nickname = mx_get_nickname(login);

    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(status);
    cJSON_AddItemToObject(packet, "STATUS", json_value);
    json_value = cJSON_CreateString(nickname);
    cJSON_AddItemToObject(packet, "NICKNAME", json_value);
    json_value =  cJSON_CreateString(login);
    cJSON_AddItemToObject(packet, "TO", json_value);
    json_value =  cJSON_CreateString(mx_itoa(list_len));
    cJSON_AddItemToObject(packet, "LENGTH", json_value);
    for(int i = 0; i < list_len; i++) {
        char chat_name_former[100];

        sprintf(chat_name_former, "CHATNAME=%d", i);
        json_value = cJSON_CreateString(mx_get_special_chat_name(chat -> chat_name, login));
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        json_value = cJSON_CreateString(chat -> last_message);
        sprintf(chat_name_former, "LASTMESSAGE=%d", i);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        chat = chat -> next;
    }
    packet_str = cJSON_Print(packet);

    return packet_str;
}

char *login_system(char *packet) {
    char *login = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *return_status = mx_confirm_users_password(login, password);
    chats_t *chat = mx_get_users_chats(login); // list чатов доступных пользователю с login (chatname, last message)
    char *sendback_packet;

    if(mx_strcmp(return_status, "false") == 0) {
        chat -> chat_name = NULL;
    }
    sendback_packet = json_packet_former_from_list(chat, return_status, login);
    return sendback_packet;
}
