#include <unistd.h>
#include <fcntl.h>  /* open, O_RDONLY */
#include <errno.h>  /* errno, perror */
#include <stdlib.h> /* exit */
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "so_stdio.h"

#include <stdio.h>

int so_pclose(SO_FILE* stream){
    if (stream->is_p == 1){
        int status;
        int s = waitpid(stream->pid, &status, 0);
        free(stream);
        return s;
    }else{
        perror("no so_popen was called\n");
        return -1;
    }
    return -1;
}