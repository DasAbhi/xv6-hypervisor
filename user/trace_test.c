#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main (int argc, char *argv[]){

    printf("calling trace\n");

    trace(1 << 22);

    printf("done trace syscall\n");

    exit(0);
}