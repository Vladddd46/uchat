#include "db.h"

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
	for(int i = 0; i < argc; i++) {
		printf("%s: %s\n", az_con_name[i], argv[i]);
	}
	return 0;
}

int mx_show_users(const char* str) {
	sqlite3 *db;
	int exit = sqlite3_open(str, &db);

	char* sql = "SELECT * FROM USERS;";

	sqlite3_exec(db, sql, mx_callback, NULL, NULL);
	return 0;
}
