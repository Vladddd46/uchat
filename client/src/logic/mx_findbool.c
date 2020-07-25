#include "client.h"

void mx_findbool (GtkWidget* widget,gpointer data){ 
    client_context->find = 0;
    gtk_widget_destroy(widget);
}
