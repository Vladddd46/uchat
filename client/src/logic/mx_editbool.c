#include "client.h"

void editbool (GtkWidget* widget,gpointer data){ 
    client_context->edit = 0;
    gtk_widget_destroy(widget);
}
