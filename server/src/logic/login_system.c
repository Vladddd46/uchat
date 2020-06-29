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

static char *json_packet_former_from_list(chats_t *chat, char *status) {
    char *key;
    char *value;
    cJSON *packet     = cJSON_CreateObject();
    char  *packet_str = NULL;

    printf("\nSEGMENTATION ERROR HERE 1 -> \n\n");
    key = "STATUS";
    value = status;
    cJSON *json_value = cJSON_CreateString(value);
    cJSON_AddItemToObject(packet, key, json_value);
    if(mx_strcmp(status, "true") == 0) {
        while (chat -> chat_name != NULL) {
            if(chat -> last_message != NULL) {
                key   = "LASTMESSAGE";
                value = mx_strncpy(chat -> last_message);
                printf("Error founder here 0 - %s\n", value);
                json_value = cJSON_CreateString(value);
                printf("Error founder here 1\n");
                cJSON_AddItemToObject(packet, key, json_value);
            }
            printf("Error founder here 2\n");
            key   = "CHATNAME";
            value = chat -> chat_name;
            printf("Error founder here 3 - %s\n", value);
            json_value = cJSON_CreateString(value);
            printf("Error founder here 4\n");
            cJSON_AddItemToObject(packet, key, json_value);
            printf("Error founder here 5\n");
            if (json_error(json_value)) {
                printf("Error founder here 6\n");
                return NULL;
            }
            chat = chat -> next;
        }
    }
    // printf("\nSEGMENTATION ERROR HERE 7 -> \n\n");
    packet_str = cJSON_Print(packet);
    // cJSON_Delete(packet); // ??? after 5 iterations there was malloc error.
    return packet_str;
}

char *login_system(char *packet) {
    char *login = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *return_status = mx_confirm_users_password(login, password);
    // printf("\nSEGMENTATION ERROR HERE -1 -> \n\n");
    chats_t *chat = mx_get_users_chats(login); // list чатов доступных пользователю с login (chatname, last message)
    chats_t* copy = chat;
    while(copy -> chat_name) {
        printf("name: %s\n", copy -> chat_name);
        copy = copy -> next;
    }
    printf("FOUNDED !!!!\n");
    char *nickname = mx_get_nickname(login);
    // printf("\nSEGMENTATION ERROR HERE 0 -> \n\n");
    // printf("\nSEGMENTATION ERROR HERE 0 %s-> \n\n", return_status);
    char *sendback_packet    = json_packet_former_from_list(chat, return_status);
    // printf("\nSEGMENTATION ERROR HERE 2 -> \n\n");

    printf("\nPacket shmaket: %s\n\n", sendback_packet);
    // char   *sendback_packet = json_packet_former(2, "TYPE:login_s", "STATUS:true"); // Debug.
    return sendback_packet;
}
