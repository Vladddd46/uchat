#include "client.h"

void add_new_user(GtkWidget *newchatbutton, gpointer data){
	miniwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW(miniwindow), FALSE);
    gtk_window_set_transient_for (GTK_WINDOW(miniwindow),GTK_WINDOW(window));
    gtk_widget_set_size_request(GTK_WIDGET(miniwindow),300,500);

    minifixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(miniwindow), minifixed);

    minientry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED (minifixed), minientry, 50,50);
    gtk_widget_set_size_request(GTK_WIDGET(minientry),200,40);

    miniscroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
    gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);

    minilistbox = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);
    gtk_widget_set_name(minilistbox,"minilistbox");
    // gtk_fixed_put(GTK_FIXED (minifixed), minientry, 25,75);
    // gtk_widget_set_size_request(GTK_WIDGET(minientry),250,350);

    gtk_widget_show_all(miniwindow);

}
