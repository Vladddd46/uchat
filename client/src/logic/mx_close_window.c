#include "client.h"

void close_window(GtkWidget *widget){
    gtk_window_close(GTK_WINDOW(widget));
    g_idle_add ((int (*)(void *))show_widget, window);

}
