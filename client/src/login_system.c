#include "client.h"

/*
 * System, which implements authentication of the user.
 * 1. Takes user-specified login and password.
 * 2. Froms "login" packet.
 * 3. Sends formed packet to the server.
 * 4. Waits for server`s answer. (Server returns corresponding code)
 */

static int json_error(cJSON *object) {
    if (object == NULL) {
        cJSON_Delete(object);
        return 1;
    }
    return 0;
}

// Froms  "login" packet in json format.
static char *json_packet_creation(char *user_login, char *user_password) {
    cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;

    if (json_error(packet))
        return NULL;

    cJSON *type = cJSON_CreateString("login");
    cJSON *log  = cJSON_CreateString(user_login);
    cJSON *pass = cJSON_CreateString(user_password);
    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "LOGIN: ", log);
    cJSON_AddItemToObject(packet, "PASSWORD: ", pass);
    if (json_error(type) || json_error(log) || json_error(pass))
        return NULL;

    packet_str = cJSON_Print(packet);
    cJSON_Delete(packet);
    return packet_str;
}

int login_system(int socket, char *user_login, char *user_password) {
    char *packet = json_packet_creation(user_login, user_password);
    if (packet == NULL)
        return LOGIN_PACKET_CREATION_ERROR;

    // Sending formed packet to server.
    send(socket, packet, (int)strlen(packet),0);

    // Receiving status code of login.
    // char buffer[256];
    // bzero(buffer,256);
    // recv(socket, buffer, 255, 0);
    // int result = atoi(buffer);

    return 0;
}
