#include "client.h"

client_context_t *client_context;

void registration_system(int socket, char *packet) {
    char *status = get_value_by_key(packet, "STATUS");
    client_context->username = get_value_by_key(packet,"TO");

    if (!strcmp(status, "success")) {
        draw_message_menu(entryspawn, client_context);
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
