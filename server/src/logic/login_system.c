#include "server.h"

/*
 * Retrieves needed data from the packet.
 * Makes request to db and checks data validity.
 * Forms back packet.
 */

static char* mx_pack_string_in_double_dots(char* str) {
    char *new_str = mx_strnew(mx_strlen(str) + 2);
    int i = 0;

    *(new_str) = 34;
    for(; i < mx_strlen(str); i++)
        *(new_str + i + 1) = *(str + i);
    *(new_str + i + 1) = 34;
    return new_str;
}

static int json_error(cJSON *object) {
    if (object == NULL) {
        cJSON_Delete(object);
        return 1;
    }
    return 0;
}

static char* mx_confirm_users_password(char* user, char* password) {
    sqlite3 *db;
    sqlite3_open("uchat.db", &db);
    char* sql = "SELECT PASSWORD FROM USERS WHERE LOGIN=";
    sqlite3_stmt *res;

    user = mx_pack_string_in_double_dots(user);
    sql = mx_strjoin(sql, user);
    sql = mx_strjoin(sql, ";");
    // printf("\nSEGMENTATION ERROR HERE -4 -> \n\n");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    // printf("\nSEGMENTATION ERROR HERE -3 -> \n\n");

    if(sqlite3_column_text(res, 0) != NULL && mx_strcmp((char*)sqlite3_column_text(res, 0), password) == 0) {
        return "true";
    }
    // printf("\nSEGMENTATION ERROR HERE -2 -> \n\n");
    sqlite3_finalize(res);
    sqlite3_close(db);
    return "false";
}

static char* mx_get_nickname(char* login) {
    sqlite3 *db;
    char* sql = "SELECT NICKNAME FROM USERS WHERE LOGIN=";
    sqlite3_stmt *res;
    char* nickname;

    sql = mx_strjoin(sql, login);
    sql = mx_strjoin(sql, ";");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    nickname = (char*)sqlite3_column_text(res, 0);
    return nickname;
}

int mx_list_len(chats_t* chat) {
    int len = 0;
    chats_t* head = chat;

    while(chat -> chat_name != NULL) {
        chat = chat -> next;
        len++;
    }
    head = chat;
    return len;
}

static char *json_packet_former_from_list(chats_t *chat, char *status) {
    int list_len = mx_list_len(chat);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString(status);
    cJSON_AddItemToObject(packet, "STATUS", json_value);

    printf("status = %s\n", status);
    for(int i = 0; i < list_len; i++) {
        json_value = cJSON_CreateString(chat -> chat_name);
        cJSON_AddItemToObject(packet, "CHATNAME", json_value);
        json_value = cJSON_CreateString(chat -> last_message);
        cJSON_AddItemToObject(packet, "CHATNAME", json_value);
    }
    packet_str = cJSON_Print(packet);
    return packet_str;
}

char *login_system(char *packet) {
    char *login = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *return_status = mx_confirm_users_password(login, password);
    // printf("\nSEGMENTATION ERROR HERE -1 -> \n\n");
    chats_t *chat = mx_get_users_chats(login); // list чатов доступных пользователю с login (chatname, last message)
    // chats_t* copy = chat;
    if(mx_strcmp(return_status, "false") == 0) {
        chat -> chat_name = NULL;
    }
    // while(copy -> chat_name) {
    //     printf("name: %s\n", copy -> chat_name);
    //     copy = copy -> next;
    // }
    char *nickname = mx_get_nickname(login);
    // printf("\nSEGMENTATION ERROR HERE 0 -> \n\n");
    // printf("\nSEGMENTATION ERROR HERE 0 %s-> \n\n", return_status);
    char *sendback_packet    = json_packet_former_from_list(chat, return_status);
    // printf("\nSEGMENTATION ERROR HERE 2 -> \n\n");

    printf("\nPacket shmaket: %s\n\n", sendback_packet);
    // char   *sendback_packet = json_packet_former(2, "TYPE:login_s", "STATUS:true"); // Debug.
    return NULL;
}
