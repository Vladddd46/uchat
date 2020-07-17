#include "server.h"

/*
 * Retrieves needed data from the login_c packet.
 * Makes request to db and checks data validity.
 * Forms back packet.
 */


static char *mx_confirm_users_password(char *user, char *password) {
    sqlite3 *db = opening_db();
    char sql[400];
    bzero(sql, 400);
    char *return_status = NULL;
    sqlite3_stmt *res;

    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE LOGIN='%s';", user);

    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    if(sqlite3_column_text(res, 0) == NULL) 
        return_status = "false";
    if(sqlite3_column_text(res, 0) != NULL && mx_strcmp((char*)sqlite3_column_text(res, 0), password) == 0)
        return_status = "success";

    sqlite3_finalize(res);
    sqlite3_close(db);
    return mx_string_copy(return_status);
}

static int mx_list_len(chats_t *chat) {
    int len = 0;
    chats_t *tmp = chat;

    while(tmp != NULL) {
        tmp = tmp -> next;
        len++;
    }
    return len;
}

static char *mx_get_special_chat_name(char *chat_name) {
    char string[100];
    bzero(string, 100);

    sprintf(string, "(%s)", chat_name);
    return mx_string_copy(string);
}

static char *json_packet_former_from_list(chats_t *chat, char *status, char *login) {
    int   list_len    = mx_list_len(chat);
    cJSON *packet     = cJSON_CreateObject();
    char  *packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("login_s");
    char  *nickname   = mx_get_nickname_by_login(login);

    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(status);
    cJSON_AddItemToObject(packet, "STATUS", json_value);
    json_value = cJSON_CreateString(nickname);
    cJSON_AddItemToObject(packet, "NICKNAME", json_value);
    json_value =  cJSON_CreateString(login);
    cJSON_AddItemToObject(packet, "TO", json_value);
    char *list_len_str = mx_itoa(list_len);
    json_value =  cJSON_CreateString(list_len_str);
    free(list_len_str);
    cJSON_AddItemToObject(packet, "LENGTH", json_value);
    chats_t *tmp = chat;
    for(int i = 0; i < list_len; i++) {
        char chat_name_former[100];
        bzero(chat_name_former, 100);

        sprintf(chat_name_former, "CHATNAME=%d", i);
        char *chat_name = mx_get_special_chat_name(tmp -> chat_name);
        json_value = cJSON_CreateString(chat_name);
        free(chat_name);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        json_value = cJSON_CreateString(tmp -> last_message);
        sprintf(chat_name_former, "LASTMESSAGE=%d", i);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        tmp = tmp -> next;
    }
    packet_str = cJSON_Print(packet);
    free(nickname);
    return packet_str;
}

static void free_chats_list(chats_t **chats) {
    chats_t *chat = *chats;
    chats_t *del;

    while(chat) {
        del = chat;
        chat = chat->next;
        free(del->chat_name);
        free(del->last_message);
        free(del);
    }
}

char *login_system(char *packet) {
    char *login         = get_value_by_key(packet, "LOGIN");
    char *password      = get_value_by_key(packet, "PASSWORD");
    char *return_status = mx_confirm_users_password(login, password);
    chats_t *chat       = mx_get_users_chats(login);
    
    char *sendback_packet;
    if(mx_strcmp(return_status, "false") == 0)
        chat -> chat_name = NULL;

    sendback_packet = json_packet_former_from_list(chat, return_status, login);
    free(login);
    free(password);
    free(return_status);
    free_chats_list(&chat);
    return sendback_packet;
}
