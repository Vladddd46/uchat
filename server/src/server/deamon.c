#include "server.h"

void mx_deamon_start() {
    pid_t pid;

    //forking child process of server
    pid = fork();
    if (pid < 0) {
        write(2, "Error: Start deamon failed", 26);
        exit(EXIT_FAILURE);
    }
    if (pid > 0 ) {
        write(1, "Start deamon successfull\n", 25);
        exit(EXIT_SUCCESS);
    }
    else {
        umask(0);   //make files available to read/write
           //make child process parent
        printf("%d\n", pid);
        chdir("/");  //avoid problem with dir tree in oracle mac os
        close(STDIN_FILENO);    //close input from terminal
        close(STDOUT_FILENO);   //close output to terminal
        close(STDERR_FILENO);   //close error stream
        setsid();
    }
    return;
}
