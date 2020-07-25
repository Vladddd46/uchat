#include "client.h"

void mx_draw_edit_profile(GtkWidget *widget, gpointer data){
    if (client_context->edit == 0) {
        client_context->edit = 1;
        editwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_resizable (GTK_WINDOW(editwindow), FALSE);
        gtk_window_set_transient_for (GTK_WINDOW(editwindow),GTK_WINDOW(window));
        g_signal_connect(editwindow,"delete-event",G_CALLBACK(mx_editbool),NULL);
        if (client_context->Ukraine == FALSE)
            gtk_window_set_title(GTK_WINDOW(editwindow),"Settings");
        else
            gtk_window_set_title(GTK_WINDOW(editwindow),"Налаштування");
        gtk_widget_set_size_request(GTK_WIDGET(editwindow),300,500);
        editfixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(editwindow), editfixed);
        editgrid = gtk_grid_new();
        gtk_fixed_put(GTK_FIXED(editfixed),editgrid,25,100);
        gtk_widget_set_name(editgrid,"editgrid");
        if (client_context->Ukraine == FALSE)
            themelabel = gtk_label_new("Dark mode");
        else
            themelabel = gtk_label_new("Темна тема");
        gtk_grid_attach(GTK_GRID(editgrid),themelabel, 0, 0, 1, 1);

        switchtheme = gtk_switch_new();
        gtk_grid_attach(GTK_GRID(editgrid),switchtheme, 0, 1, 1, 1);
        gtk_widget_set_size_request(switchtheme,25,25);
         if (client_context->Ukraine == FALSE)
            languagelabel = gtk_label_new("Ukrainan");
        else
            languagelabel = gtk_label_new("Українська");
        gtk_grid_attach(GTK_GRID(editgrid),languagelabel, 0, 2, 1, 1);
        
        switchlanguage = gtk_switch_new();
        if(client_context->Ukraine == TRUE)
            gtk_switch_set_state(GTK_SWITCH(switchlanguage),TRUE);
        gtk_grid_attach(GTK_GRID(editgrid),switchlanguage, 0, 3, 1, 1);
        g_signal_connect(switchlanguage,"state-set", G_CALLBACK(mx_switchlanguage_system), NULL);
        changepassword = gtk_entry_new();
        if (client_context->Ukraine == FALSE)
            gtk_entry_set_placeholder_text(GTK_ENTRY(changepassword),"Change password");
        else
            gtk_entry_set_placeholder_text(GTK_ENTRY(changepassword),"Змінити пароль");
        gtk_grid_attach(GTK_GRID(editgrid),changepassword, 0, 4, 2, 1);
        g_signal_connect(changepassword,"activate", G_CALLBACK(mx_change_password_system), NULL);

         if (client_context->Ukraine == FALSE)
            logout = gtk_button_new_with_label("logout");
        else
            logout = gtk_button_new_with_label("Вихід");
         gtk_grid_attach(GTK_GRID(editgrid),logout, 0, 5, 1, 1);
        g_signal_connect(logout,"clicked", G_CALLBACK(mx_logout_system), NULL);
        g_idle_add ((int (*)(void *))show_widget, editwindow);
    }
}
