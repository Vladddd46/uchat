#include "server.h"

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
	for(int i = 0; i < argc; i++) {
		printf("%s: %s\n", az_con_name[i], argv[i]);
	}
	return 0;
}

static chat_message_t* mx_fill_list(int chat_id, int from, int to) {
	chat_message_t* list = malloc(sizeof(chat_message_t));
	chat_message_t* head = list;
    sqlite3 *db;
    sqlite3_stmt *res;
    char sql[100];
    
    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT SENDER, TIME, MESSAGE FROM MESSAGES WHERE CHATID='%s';", mx_itoa(chat_id));
    // sqlite3_prepare_v2(db, sql, -1, &res, 0);
    // for(int i = 0; i < from; i++) {
    // 	sqlite3_step(res);
    // }
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    for(int i = from, j = 0; i < to; i++) {
    	sqlite3_step(res);
        list -> sender = sqlite3_column_text(res, 0);
        list -> time = sqlite3_column_text(res, 1);
        list -> message = sqlite3_column_text(res, 2);
        list -> next = malloc(sizeof(chat_message_t));
        list = list -> next;
        // list -> sender = NULL;
        // list -> time = NULL;
        // list -> message = NULL;
        // list -> next = NULL;
        // printf("%s", sqlite3_column_text(res, 2));
    }
    // char* sql1 = "SELECT SENDER, TIME, MESSAGE FROM MESSAGES WHERE CHATID=1";
    // sqlite3_exec(db, sql1, mx_callback, NULL, NULL);
    // sqlite3_finalize(res);
    return head;
}

char* mx_get_message(char* packet) {
    int chat_id = atoi(get_value_by_key(packet, "CHATID"));
    int from = atoi(get_value_by_key(packet, "FROM"));
    int to = atoi(get_value_by_key(packet, "TO"));

    chat_message_t* list = mx_fill_list(chat_id, from, to);
    for(int i = 0; i < 5; i++) {
    	printf("Sender: %s   Time: %s\nMessage: %s\n\n", list -> sender, list -> time, list -> message);
        list = list -> next;
    }
    printf("chat_id = %d\nfrom = %d\nto = %d\n", chat_id, from, to);
    return NULL;	
}
