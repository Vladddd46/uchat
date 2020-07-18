#include "server.h"

/*
 * Finds user in db by login/nickname.
 * Returns packet with found users.
 */

static bool mx_check_complability(char *login, char *nickname, char *user) {
    bool status = false;

    if(strstr(login, user) != NULL)
        status = true;
    else if(strstr(nickname, user) != NULL)
        status = true;
    return status;
}

static int mx_list_len(users_list_t *chat) {
    int len = 0;

    users_list_t *tmp = chat;
    while(tmp != NULL) {
        tmp = tmp -> next;
        len++;
    }
    return len;
}

static users_list_t *mx_fill_users_list(char *user) {
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    char *sql = "SELECT * FROM USERS;";
    char *login;
    char *nickname;
    char *id_str;
    users_list_t *list = NULL;

    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    for(int i = 0; sqlite3_column_text(res, 0) != NULL; i++) {
        login    = (char*)sqlite3_column_text(res, 1);
        nickname = (char*)sqlite3_column_text(res, 3);
        if(mx_check_complability(login, nickname, user)) {
            id_str = (char*)sqlite3_column_text(res, 0);
            if (id_str == NULL || login == NULL || nickname == NULL)
                mx_db_null_error("mx_fill_users_list");
            mx_push_users_list_node_back(&list, atoi(id_str), 
                                             mx_string_copy(login), 
                                             mx_string_copy(nickname));
        }
        sqlite3_step(res);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return list;
}

static char *mx_json_packet_former_from_list(users_list_t *list, char *login_to) {
    int list_len = mx_list_len(list);

    cJSON *packet     = cJSON_CreateObject();
    char  *packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("find_user_s");
    char *id_str;

    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(login_to);
    cJSON_AddItemToObject(packet, "TO", json_value);
    json_value = cJSON_CreateString(mx_itoa(list_len));
    cJSON_AddItemToObject(packet, "LENGTH", json_value);

    for(int i = 0; i < list_len; i++) {
        char packet_former[100];
        bzero(packet_former, 100);
        sprintf(packet_former, "ID%d", i);
        id_str = mx_itoa(list->id);
        json_value = cJSON_CreateString(id_str);
        free(id_str);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        json_value = cJSON_CreateString(list->nickname);
        sprintf(packet_former, "NICKNAME%d", i);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        json_value = cJSON_CreateString(list->login);
        sprintf(packet_former, "LOGIN%d", i);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        list = list->next;
    }
    packet_str = cJSON_Print(packet);
    return packet_str;
}

char *mx_find_user(char * packet) {
    char *user     = get_value_by_key(packet, "USER");
    char *login_to = get_value_by_key(packet, "TO");
    users_list_t *list_of_users = mx_fill_users_list(user);
    char *return_packet         = mx_json_packet_former_from_list(list_of_users, login_to);

    free(user);
    free(login_to);
    users_list_t *node_to_del;
    while(list_of_users) {
        node_to_del = list_of_users;
        list_of_users = list_of_users->next;
        free(node_to_del->login);
        free(node_to_del->nickname);
        free(node_to_del);
    }
    return return_packet;
}

