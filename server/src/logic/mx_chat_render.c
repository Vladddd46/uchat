#include "server.h"

/*
 * This set of functions is called, when user clicks on chats in the
 * left sidebar.
 * 1. Receive chat_render_c packet with values:
 *      CHATNAME 
 *      CHATID
 *      FROMMSG < range of msg ids to render. 
 *      TOMSG   > 
 *      TOMSG
 * 2. Does the request to db.
 * 3. Forms sendback packet.
 */

static void db_null_error() {
    char *msg = "mx_chat_render| Request to db returned NULL\n";

    write(2, msg, (int)strlen(msg));
    exit(1);
}

/*
 * Returns list of messages in range <from> <to>.
 * Each node represents one message.
 */
static chat_message_t *mx_fill_list(char *chat_id, int from, int to) {
    chat_message_t *list = NULL;
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    char sql[100];
    bzero(sql, 100);

    sprintf(sql, "SELECT SENDER, TIME, MESSAGE FROM MESSAGES WHERE CHATID='%s';", chat_id);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    for(int i = 0; i <= from; i++)
        sqlite3_step(res);

    for(int i = from; i < to && sqlite3_column_text(res, 0) != NULL; i++) {
        char *sender  = (char*)sqlite3_column_text(res, 0);
        char *time    = (char*)sqlite3_column_text(res, 1);
        char *message = (char*)sqlite3_column_text(res, 2);
        if (!sender || !time || !message)
            db_null_error();
        mx_push_back_message_node(&list, mx_string_copy(sender), mx_string_copy(time), mx_string_copy(message));
        sqlite3_step(res);
    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    return list;
}

/*
 * Retrieves all members of chat with chat_id.
 * Returns string with logins of all members, 
 * separated with space.
 */
static char *mx_get_all_users(int chat_id) {
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    char sql[500];
    bzero(sql, 500);
    char *user_login = NULL;
    char *users = NULL;
    char *tmp;
    char *tmp2;

    sprintf(sql, "SELECT USERS.LOGIN FROM USERCHAT INNER JOIN USERS ON USERS.ID = USERCHAT.USERID AND USERCHAT.CHATID=%d;", chat_id);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);

    while(sqlite3_column_text(res, 0) != NULL) {
        user_login = (char*)sqlite3_column_text(res, 0);
        if (user_login == NULL)
            db_null_error();
        tmp = mx_strjoin(user_login, " ");
        tmp2 = users;
        users = mx_strjoin(users, tmp);
        free(tmp2);
        free(tmp);
        sqlite3_step(res);
    }

    sqlite3_finalize(res);
    sqlite3_close(db);  
    return users;
}

static int mx_list_len(chat_message_t* chat) {
    int len = 0;

    chat_message_t *tmp = chat;
    while(tmp != NULL) {
        tmp = tmp -> next;
        len++;
    }
    return len;
}

static char *mx_json_packet_former_from_list(chat_message_t* chat, int from, char *chat_name, char* all_users) {
    int list_len = mx_list_len(chat);

    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("msg_s");

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

char *mx_chat_render(char *packet) {
    char *chat_id_str = get_value_by_key(packet, "CHATID");
    char *from_str    = get_value_by_key(packet, "FROMMSG");
    char *to_str      = get_value_by_key(packet, "TOMSG");
    char *chat_name   = get_value_by_key(packet, "CHATNAME");

    int chat_id         = atoi(chat_id_str);
    int from            = atoi(from_str);
    int to              = atoi(to_str);
    int last_message_id = mx_get_last_message_id(chat_id);
    
    int amount_of_msg = to - from;
    from = last_message_id - amount_of_msg - from;
    to   = from + to;

    chat_message_t *list = mx_fill_list(chat_id_str, from, to);
    char *all_users      = mx_get_all_users(chat_id);
    char *return_packet  = mx_json_packet_former_from_list(list, from, chat_name, all_users);

    free(chat_id_str);
    free(from_str);
    free(to_str);
    free(chat_name);
    free(all_users);

    chat_message_t *node_to_del;
    while(list) {
        node_to_del = list;
        list        = list->next;
        free(node_to_del->sender);
        free(node_to_del->time);
        free(node_to_del->message);
        free(node_to_del);
    }
    printf(">>>%s\n", return_packet);
    return return_packet;   
}
