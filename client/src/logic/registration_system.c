#include "client.h"

client_context_t *client_context;

void registration_system(int socket, char *packet) {
    char *status = get_value_by_key(packet, "STATUS");

    if (!strcmp(status, "success")) {
        do_login(entryspawn, client_context);
    }
    else {
        printf("%s\n", status);
       /* Денис:
        * Тут регестрация прошла неуспешно.
        * Пользователю должно вывестись уведомление о неуспешной регестрации
        * причина неуспешной регестрации хранится в char *status (printf(status))
        */
    }
}
