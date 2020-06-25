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
    for(; i < mx_strlen(str); i++) {
    	*(new_str + i + 1) = *(str + i);
    }
    *(new_str + i + 1) = 34;
    return new_str;
}

static char** mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
	for(int i = 0; i < argc; i++) {
		printf("%s: %s\n", az_con_name[i], argv[i]);
	}
	return argv;
}

static char** mx_add_to_arr(char** arr, char* str, int index) {
	*(arr + index) = mx_strnew(mx_strlen(str));

    for(int i = 0; i < mx_strlen(str); i++) {
    	*(*(arr + index) + i) = *(str + i);
    }
    return arr;
}

static char* mx_confirm_users_password(const char* str, char* user, char* password) {
	sqlite3 *db;
	sqlite3_open(str, &db);
	char* sql = "SELECT PASSWORD FROM USERS WHERE LOGIN=";
	sqlite3_stmt *res;

	user = mx_pack_string_in_double_dots(user);
    sql = mx_strjoin(sql, user);
	sql = mx_strjoin(sql, ";");
	sqlite3_prepare_v2(db, sql, -1, &res, 0);
	sqlite3_step(res);

    if(mx_strcmp((char*)sqlite3_column_text(res, 0), password) == 0) {
        return "true";
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
	return "false";
}

char *login_system(char *packet) {
    // printf("Packet %s\n", packet);
    char *login    = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");

    // char *return_status      = mx_confirm_users_password("uchat.db", login, password);
    // char *status             = mx_strjoin("STATUS:", return_status);
    chats_t *chat = mx_get_users_chats(login);
    while(chat != NULL) {
        // printf("chat_name = '%s'\nlast_message = '%s'\n", chat -> chat_name, chat -> last_message);
        chat = chat -> next;
    }
    // char *opened_chats       = тут должен возвращаться массив из названий и айди открытых чатов
    // char *nickname			= тут должен быть никнейм 
    // char *sendback_packet    = json_packet_former(2, "TYPE:login_s", status);
    char   *sendback_packet = json_packet_former(2, "TYPE:login_s", "STATUS:true"); // Debug.
    return sendback_packet;
}
