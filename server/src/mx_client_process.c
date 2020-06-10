#include "server.h"

// Determines type of operation.
static char *operation_determine(char *buffer) {
	char **splt_buffer      = mx_strsplit(buffer, '\n');
	char **operation_line   = mx_strsplit(splt_buffer[0], ' ');
	char *operation         = mx_string_copy(operation_line[1]);

	mx_del_strarr(&splt_buffer);
	mx_del_strarr(&operation_line);
	return operation;
}


void mx_client_process(int client_socket) {
    int n;
    char buffer[256];
    bzero(buffer,256);
    while(1) {
        n = read(client_socket, buffer, 255);
       
      	char *operation = operation_determine(buffer);

      	if (!strcmp(operation, "login")) {
      		// login functionality.
      	}

        // refreshing buffer.
        bzero(buffer,256);
    }
}
