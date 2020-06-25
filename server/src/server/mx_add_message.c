#include "server.h"

static char* mx_insert_all_args(char* user, char* sender, char* time, char* message) {
	char* request = mx_strjoin("INSERT INTO MESSAGES (USER, SENDER, TIME, MESSAGE) VALUES('", user);

    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, sender);
    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, time);
    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, message);
    request = mx_strjoin(request, "');");
    // printf("%s", request);
    return request;
}

int mx_add_message(const char *str, char* user, char* sender, char* time, char* message) {
    sqlite3 *db;
    char *message_error;
    int exit = sqlite3_open(str, &db);
    char* sql = mx_insert_all_args(user, sender, time, message);

    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    if(exit != SQLITE_OK) {
    	printf("Error insert");
    	sqlite3_free(message_error);
    }
    return 0;
}
