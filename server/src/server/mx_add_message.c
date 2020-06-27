#include "server.h"

static char* mx_insert_all_args(int chat_id, char* sender, char* time, char* message) {
	char request[1024];

    sprintf(request, "%s%d%s%s%s%s%s%s%s", "INSERT INTO MESSSAGES (CHATID, SENDER, TIME, MESSAGE) VALUE('", chat_id, "', ", sender, "', ", time, "', ", message, ");");
    return request;
}

int mx_add_message(int chat_id, char* sender, char* time, char* message) {
    sqlite3 *db;
    char *message_error;
    int exit = sqlite3_open("chat.db", &db);
    char* sql = mx_insert_all_args(chat_id, sender, time, message);

    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    if(exit != SQLITE_OK) {
    	printf("Error insert");
    	sqlite3_free(message_error);
    }
    return 0;
}
