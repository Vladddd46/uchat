#include "server.h"

static char* mx_get_nickname(char* login) {
    sqlite3 *db;
    char* sql = "SELECT NICKNAME FROM USERS WHERE LOGIN=";
    sqlite3_stmt *res;
    char* nickname;

    sql = mx_strjoin(sql, login);
    sql = mx_strjoin(sql, ";");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    nickname = sqlite3_column_text(res, 0);
    return nickname;
}

char* mx_send_back_packet(char* packet) {
	char *sender_login = get_value_by_key(packet, "SENDERLOGIN");
	int chat_id = get_value_by_key(packet, "CHATID");
    char *nickname = mx_get_nickname(sender_login);
    char *time = get_value_by_key(packet, "TIME");
    char *message = get_value_by_key(packet, "MESSAGE");
    int range_from = get_value_by_key(packet, "RANGEFROM");
    int range_to = get_value_by_key(packet, "RANGETO");

    mx_add_message(chat_id, sender_login, time, message);
    mx_list_of_range_messages(chat_id, range_from, range_to);

    return NULL;
}