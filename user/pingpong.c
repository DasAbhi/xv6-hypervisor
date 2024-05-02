#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main (int argc, char *argv[]){


    int parent_send_pipe[2];
    int child_send_pipe[2];

    int current_pid; 

    char buffer[25];

    pipe(parent_send_pipe);
    pipe(child_send_pipe);

    printf("within parent pid:%d\n", getpid());

    if (fork() == 0){
        current_pid = getpid();

        printf("within child pid:%d\n", getpid());

        read(parent_send_pipe[0], buffer, strlen("ping\n"));

        printf("%d: recieved %s\n", current_pid, buffer);

        write(child_send_pipe[1],"pong\n", strlen("pong\n"));

        exit(0);

    }else{
        current_pid = getpid();

        write(parent_send_pipe[1], "ping\n", strlen("ping\n"));

        read(child_send_pipe[0], buffer, strlen("pong\n"));
        
        printf("%d: recieved %s\n", current_pid, buffer);
    }

    exit(0);
    
}