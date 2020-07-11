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
    int len = mx_strlen(login);
    int copy_name_len = mx_strlen(chat_name) - len;
    char* copy_last_name = mx_strnew(mx_strlen(chat_name));
    char* result = mx_strnew(mx_strlen(chat_name) + 2);

    // if(*(login) != *(chat_name)) {
    //     for(int i = 0; i < len; i++) {
    //         *(copy_last_name + i) = *(chat_name + i + copy_name_len);
    //     }
    //     int i = 0;
    //     for(; i < copy_name_len; i++) {
    //         *(result + i) = *(chat_name + i);
    //     }
    //     *(result + i) = '(';
    //     i++;
    //     for(int j = 0; j < len; j++, i++) {
    //         *(result + j + i) = *(copy_last_name + j);
    //     }
    //     *(result + i) = ')';
    //     return result;
    // }
    return login;
}

static char *json_packet_former_from_list(chats_t *chat, char *status, char* login) {
    int list_len = mx_list_len(chat);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("login_s");
    char *nickname = mx_get_nickname(login);
    printf("\nnickname: %s\n\n", nickname);

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
    printf("packet shmaket %s", packet_str);
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
    printf("Packet to client %s", sendback_packet);
    return sendback_packet;
}
