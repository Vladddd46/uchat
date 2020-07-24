#include "client.h"

client_context_t *client_context;

gboolean mx_registration_system(void *data) {
    char *packet = (char *)data;
    char *status = get_value_by_key(packet, "STATUS");
    client_context->username = get_value_by_key(packet,"TO");

    if (!strcmp(status, "success")) {
        gtk_widget_destroy(grid);
        main_menu(); 
    }
    else {
        printf("%s\n", status);
       /* Денис:
        * Тут регестрация прошла неуспешно.
        * Пользователю должно вывестись уведомление о неуспешной регестрации
        * причина неуспешной регестрации хранится в char *status (printf(status))
        */
    }
    return 0;
}
