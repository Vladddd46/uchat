#include "server.h"

char *mx_delete_user(char *packet) {
    char *send_back = NULL;
    char *login = get_value_by_key(packet, "USER");
    sqlite3 *db = opening_db();
    char sql[200];
    char *message_error;

    bzero(sql, 200);
    sprintf(sql, "DELETE FROM USERS WHERE LOGIN='%s';", login);
    int check = sqlite3_exec(db, sql, NULL, 0, &message_error);
	sqlite3_close(db);
    return send_back;
}
