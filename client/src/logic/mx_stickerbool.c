#include "client.h"
               
void mx_stickerbool (GtkWidget* widget,gpointer data){ 
    client_context->sticker = 0;
    gtk_widget_destroy(widget);
}
