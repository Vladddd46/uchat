#include "server.h"

/*
 * Retrieves needed data from the login_c packet.
 * Makes request to db and checks data validity.
 * Forms back packet.
 */

/*
 * Does the query to db and checks, whether user
 * with such login and password exists.
 * returns "success"/"false"
 */
static char *mx_confirm_users_password(char *user, char *password) {
    sqlite3 *db = opening_db();
    char sql[400];
    bzero(sql, 400);
    char *return_status = "false";
    sqlite3_stmt *res;
    char *pass_result = NULL;

    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE LOGIN='%s';", user);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    if(sqlite3_column_text(res, 0) == NULL) 
        return_status = "false";
    pass_result = (char*)sqlite3_column_text(res, 0);
    if(pass_result != NULL && mx_strcmp(pass_result, password) == 0)
        return_status = "success";
    sqlite3_finalize(res);

    sqlite3_close(db);
    return mx_string_copy(return_status);
}

static char *mx_get_special_chat_name(char *chat_name) {
    char string[100];
    bzero(string, 100);

    sprintf(string, "(%s)", chat_name);
    return mx_string_copy(string);
}

static void add_lists_of_chats(cJSON *packet, int list_len, chats_t *chat) {
    chats_t *tmp = chat;
    cJSON *json_value;

    for(int i = 0; i < list_len; i++) {
        char chat_name_former[100];
        bzero(chat_name_former, 100);
        sprintf(chat_name_former, "CHATNAME=%d", i);
        json_value = cJSON_CreateString(tmp -> chat_name);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        json_value = cJSON_CreateString(tmp -> last_message);
        sprintf(chat_name_former, "LASTMESSAGE=%d", i);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        json_value = cJSON_CreateString(tmp -> chat_id);
        sprintf(chat_name_former, "CHATID=%d", i);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        tmp = tmp -> next;
    }
}

static char *json_packet_former_from_list(chats_t *chat, char *status, char *login) {
    int   list_len    = mx_chats_list_len(chat);
    cJSON *packet     = cJSON_CreateObject();
    char  *packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("login_s");
    char  *nickname;
    
    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(status);
    cJSON_AddItemToObject(packet, "STATUS", json_value);
    if (!strcmp(status, "true")) {
        nickname   = mx_get_nickname_by_login(login);
        json_value = cJSON_CreateString(nickname);
        cJSON_AddItemToObject(packet, "NICKNAME", json_value);
        free(nickname);
    }
    json_value =  cJSON_CreateString(login);
    cJSON_AddItemToObject(packet, "TO", json_value);
    char *list_len_str = mx_itoa(list_len);
    json_value =  cJSON_CreateString(list_len_str);
    free(list_len_str);
    cJSON_AddItemToObject(packet, "LENGTH", json_value);
    add_lists_of_chats(packet, list_len, chat);
    packet_str = cJSON_Print(packet);
    return packet_str;
}

char *login_system(char *packet) {
    char *login         = get_value_by_key(packet, "LOGIN");
    char *password      = get_value_by_key(packet, "PASSWORD");
    if (login == NULL || password == NULL)
        mx_null_value_error("login_system"); 
    char *return_status = mx_confirm_users_password(login, password);
    char *sendback_packet = NULL;
    chats_t *chat         = NULL;

    if (!strcmp(return_status, "success"))
        chat = mx_get_users_chats(login);
    sendback_packet = json_packet_former_from_list(chat, return_status, login);
    return sendback_packet;
}
