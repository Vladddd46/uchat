#include "client.h"
 
void mx_add_new_user(GtkWidget *newchatbutton, gpointer data){
    if (client_context->find == 0) {
        client_context->find = 1;
    	miniwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_resizable (GTK_WINDOW(miniwindow), FALSE);
        gtk_window_set_transient_for (GTK_WINDOW(miniwindow),GTK_WINDOW(window));
        g_signal_connect(miniwindow,"delete-event",G_CALLBACK(mx_findbool),NULL);
        if (client_context->Ukraine == FALSE)
            gtk_window_set_title(GTK_WINDOW(miniwindow),"Find User");
        else
            buttonrefresh = gtk_button_new_with_label("Знайти Користувача"); 
        gtk_widget_set_size_request(GTK_WIDGET(miniwindow),300,500);
        minifixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(miniwindow), minifixed);
        minientry = gtk_entry_new();
        gtk_fixed_put(GTK_FIXED (minifixed), minientry, 50,50);
        gtk_widget_set_size_request(GTK_WIDGET(minientry),200,40);
        if (client_context->Ukraine == FALSE)
            minibuttonfind = gtk_button_new_with_label("Find User");
        else
            minibuttonfind = gtk_button_new_with_label("Знайти Користувача");
        gtk_widget_set_name(minibuttonfind,"minibuttonfind");
        gtk_fixed_put(GTK_FIXED (minifixed), minibuttonfind, 90,10);
        g_signal_connect (G_OBJECT (minibuttonfind), "clicked", G_CALLBACK (mx_mini_button_release), NULL);
        miniscroll = gtk_scrolled_window_new(0,0);
        gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
        gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);
        minilistbox = gtk_list_box_new();
        gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);
        gtk_widget_set_name(minilistbox,"minilistbox");
        g_idle_add ((int (*)(void *))show_widget, miniwindow);
    }
}
