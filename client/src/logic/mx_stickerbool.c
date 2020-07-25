#include "client.h"
               
void stickerbool (GtkWidget* widget,gpointer data){ 
    client_context->sticker = 0;
    gtk_widget_destroy(widget);
}
