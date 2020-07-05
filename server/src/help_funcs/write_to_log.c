#include "server.h"

/*
 * Function creat log-file (if does not exist) and write log msg to the
 * end of log-file.
 * Arguments:
 * msg: message, that have to been write to the log-file
 * stream: int like STDOUT (1) or STDERR (2)
 */

void mx_write_to_log(char *msg, int stream) {
    FILE *fd = 0;
    time_t cur = time(NULL); //get current time
    char *cur_time;
    char *stream_str = NULL;

    fd = fopen("uchat_server.log", "a+t");
    if (!fd)
        return;
    cur_time = ctime(&cur);
    cur_time[24] = '\0';
    if (stream == 2)
        stream_str = mx_strdup("STD_ERR");
    else
        stream_str = mx_strdup("STD_OUT");
    fprintf(fd, "%s: %s: %s\n", cur_time, stream_str, msg);
    if (fclose(fd) < 0)
        mx_write_to_log("error closing log-file", 2);
}
