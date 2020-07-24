#include "server.h"

static bool mx_check_complability(char* login, char* nickname, char* user) {
    bool status = false;

    if(strstr(login, user) != NULL) {
    	status = true;
    }
    else if(strstr(nickname, user) != NULL) {
    	status = true;
    }
    return status;
}

static int mx_list_len(users_list_t* chat) {
    int len = 0;
    users_list_t *tmp = chat;

    while(tmp -> next != NULL) {
        tmp = tmp -> next;
        len++;
    }
    return len;
}

static users_list_t* mx_fill_users_list(char* user) {
	sqlite3 *db = mx_opening_db();
	sqlite3_stmt *res;
	char* sql = "SELECT * FROM USERS;";
	users_list_t* list = (users_list_t*)malloc(sizeof(users_list_t));
    list -> login = NULL;
    list -> next  = NULL;
	users_list_t *head = list;

    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    for(int i = 0; sqlite3_column_text(res, 0) != NULL; i++) {
        char* login = mx_string_copy((char*)sqlite3_column_text(res, 1));
        char* nickname = mx_string_copy((char*)sqlite3_column_text(res, 3));

    	if(mx_check_complability(login, nickname, user)) {
    	    char* value1 = mx_string_copy((char*)sqlite3_column_text(res, 0));
    	    int a = atoi(value1);
    	  	list -> id = atoi(value1);
    		list -> login = login;
            list -> nickname = nickname;
            list -> next = (users_list_t*)malloc(sizeof(users_list_t));
            list = list -> next;
            list -> next = NULL;
    	}
        sqlite3_step(res);
    }
    if(head -> login == NULL) {
        list = NULL;
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return head;
}

static char *packet_former(users_list_t* list, char* login_to) {
    int list_len = mx_list_len(list);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("find_user_s");

    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(login_to);
    cJSON_AddItemToObject(packet, "TO", json_value);
    json_value = cJSON_CreateString(mx_itoa(list_len));
    cJSON_AddItemToObject(packet, "LENGTH", json_value);
    for(int i = 0; i < list_len; i++) {
        char packet_former[100];
        sprintf(packet_former, "ID%d", i);
        json_value = cJSON_CreateString(mx_itoa(list -> id));
        cJSON_AddItemToObject(packet, packet_former, json_value);
        json_value = cJSON_CreateString(list -> nickname);
        sprintf(packet_former, "NICKNAME%d", i);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        json_value = cJSON_CreateString(list -> login);
        sprintf(packet_former, "LOGIN%d", i);
        cJSON_AddItemToObject(packet, packet_former, json_value);
        list = list -> next;
    }
    packet_str = cJSON_Print(packet);
    return packet_str;
}

static char *mx_json_packet_former_from_list(users_list_t* list, char* login_to) {
    char* packet_str = NULL;
    if(list != NULL) {
        packet_str = packet_former(list, login_to);
        return packet_str;
    }
    else {
        cJSON *packet = cJSON_CreateObject();
        cJSON *json_value = cJSON_CreateString("find_user_s");
        cJSON_AddItemToObject(packet, "TYPE", json_value);
        json_value = cJSON_CreateString(login_to);
        cJSON_AddItemToObject(packet, "TO", json_value);
        json_value = cJSON_CreateString("0");
        cJSON_AddItemToObject(packet, "LENGTH", json_value);
        packet_str = cJSON_Print(packet);
        return packet_str;
    }
}

char* mx_find_user(char* packet) {
	char* user = get_value_by_key(packet, "USER");
    char* login_to = get_value_by_key(packet, "TO");
    users_list_t* list = mx_fill_users_list(user);

    char* return_packet = mx_json_packet_former_from_list(list, login_to);
    return return_packet;
}
