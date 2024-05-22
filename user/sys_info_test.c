#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/sysinfo.h"
#include "user/user.h"


int main(){
    struct  sysinfo * sysinfo_ptr = (struct sysinfo *) malloc(sizeof(struct sysinfo));
    
    if(sysinfo(sysinfo_ptr) < 0){
        printf("syscall sysinfo failure \n");
        exit(1);
    }

    exit(0);
}