#include "db.h"

int mx_strcmp(char *s1, char *s2){
    int counter = 0;
    
    while (s1[counter] == s2[counter]) {
        if (s1[counter] == '\0' && s2[counter] == '\0')
            return 0;
    counter++;
    }
    return s1[counter] - s2[counter];
}

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
	for(int i = 0; i < argc; i++) {
		printf("%s: %s\n", az_con_name[i], argv[i]);
	}
	return 0;
}

int mx_confirm_user(const char* str, char* login, char* password) {
	sqlite3 *db;
	int exit = sqlite3_open(str, &db);

	char* sql = "SELECT * FROM USERS;";

	sqlite3_exec(db, sql, mx_callback, NULL, NULL);
	return 0;
}
