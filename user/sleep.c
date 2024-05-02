
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main (int argc, char *argv[]){
    if (argc <= 1){
        printf("missing arguments\n");
        exit(1);
    }

    int sleep_seconds = atoi(argv[1]);

    sleep(sleep_seconds);

    exit(0);
}