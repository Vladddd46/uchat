#include "server.h"

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
    for(int i = 0; i < argc; i++) {
        printf("%s: %s\n", az_con_name[i], argv[i]);
    }
    return 0;
}

static void mx_add_last_message(int chat_id, char* message, char* time, char* sender) {
	sqlite3 *db;
    char *message_error;
    char sql[500];
    int check;

	sprintf(sql, "INSERT INTO MESSAGES (CHATID, SENDER, TIME, MESSAGE) VALUES(%d, '%s', '%s', '%s');", chat_id, sender, time, message);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
}

static void mx_add_message_with_id(int message_id, int chat_id, char* message) {
	sqlite3 *db;
    char *message_error;
    char sql[500];
    int check;

	sprintf(sql, "UPDATE MESSAGES SET MESSAGE = '%s' WHERE MESSAGEID = %d;", message ,message_id);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
}

char* mx_add_message_by_id(char* packet) {
    int message_id = atoi(get_value_by_key(packet, "MESSAGEID"));
    char* time = get_value_by_key(packet, "TIME");
    char* message = get_value_by_key(packet, "MESSAGE");
    int chat_id = atoi(get_value_by_key(packet, "CHATID"));
    char* sender = get_value_by_key(packet, "SENDER");

    if(message_id == 0) {
    	mx_add_last_message(chat_id, message, time, sender);
    }
    else {
    	mx_add_message_with_id(message_id, chat_id, message);
    }

    sqlite3 *db;
    char* sql1 = "SELECT * FROM MESSAGES WHERE CHATID=1";
    sqlite3_exec(db, sql1, mx_callback, NULL, NULL);
    return NULL;
}
