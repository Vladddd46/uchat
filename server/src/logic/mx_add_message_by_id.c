#include "server.h"

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
    for(int i = 0; i < argc; i++) {
        printf("%s: %s\n", az_con_name[i], argv[i]);
    }
    return 0;
}

static void dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        write(2, msg, (int)strlen(msg));
        write(2, "\n", 1);
        sqlite3_close(db); 
        exit(1);
    }
}

static int mx_get_last_message_id(int chat_id) {
    sqlite3 *db;
    sqlite3_stmt *res;
    char sql[100];
    int last_message_id = 0;

    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT MAX(MESSAGEID) FROM MESSAGES WHERE CHATID='%d';", chat_id);
    int exit = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    dberror(db, exit, "Error inserting to table");
	sqlite3_step(res);
	if((sqlite3_column_text(res, 0)) != NULL)
        last_message_id = atoi(sqlite3_column_text(res, 0));
    sqlite3_finalize(res);
    sqlite3_close(db);
    return last_message_id;
}

static void mx_add_last_message(int chat_id, char* message, char* time, char* sender) {
	sqlite3 *db;
    char *message_error;
    char sql[10000];
    int check;
    printf("\n\nSEG FAULT HERE -- 11\n\n");
    int message_id = mx_get_last_message_id(chat_id);

    message_id++;
    printf("\n\nSEG FAULT HERE -- 2\n\n");
    int x = sqlite3_open("uchat.db", &db);
	sprintf(sql, "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(%d, %d, '%s', '%s','%s');", chat_id, message_id, sender, time, message);
    printf("\n\nSEG FAULT HERE -- 3\n\n");
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, check, "Error inserting to table");

    char* sql1 = "SELECT * FROM MESSAGES WHERE CHATID=1";
    sqlite3_exec(db, sql1, mx_callback, NULL, NULL);
    printf("\n\nSEG FAULT HERE -- 4\n\n");
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
    printf("\n\nSEG FAULT HERE -- 1\n\n");
    int message_id = atoi(get_value_by_key(packet, "MESSAGEID"));
    printf("\n\nSEG FAULT HERE -- 1 2\n\n");
    char* time = get_value_by_key(packet, "TIME");
    printf("\n\nSEG FAULT HERE -- 1 3\n\n");
    char* message = get_value_by_key(packet, "MESSAGE");
    printf("\n\nSEG FAULT HERE -- 1 4\n\n");
    int chat_id = atoi(get_value_by_key(packet, "CHATID"));
    printf("\n\nSEG FAULT HERE -- 1 5\n\n");
    char* sender = get_value_by_key(packet, "SENDER");
    printf("\n\nSEG FAULT HERE -- 1 6\n\n");

    if(message_id == 0)
    	mx_add_last_message(chat_id, message, time, sender);
    else
    	mx_add_message_with_id(message_id, chat_id, message);
    printf("\n\nSEG FAULT HERE -- 5\n\n");
    return NULL;
}