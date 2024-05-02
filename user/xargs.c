#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    if (argc <= 1){
        printf("not enough arguments\n");

        exit(0);
    }

    char * arguments_buffer = (char *)malloc(sizeof(char) * 4096);

    arguments_buffer[0] = '\0';

    if(argc > 2){
        int i;
        for(i = 1; i < argc; i++){
            strcpy(&arguments_buffer[strlen(arguments_buffer)],argv[i]);
            
            arguments_buffer[strlen(arguments_buffer)] = ' ';
        }
    }

    gets(&arguments_buffer[strlen(arguments_buffer)],4096-strlen(arguments_buffer));
    
    arguments_buffer[strlen(arguments_buffer)-1] = '\0';

    //printf("%s\n",arguments_buffer);
    
    int i, argument_counter;
    for(i = 0, argument_counter = 0; arguments_buffer[i] != '\0'; i++){
        if(arguments_buffer[i]== ' '){
            argument_counter++;
        }
    }

    argument_counter ++;

    //printf("%d\n",argument_counter);

    char ** exec_argv = (char **)malloc(sizeof(char *)*argument_counter);
    
    int j = 0;
    int anchor_point = 0;
    for (i = 0; i < argument_counter; i++){
        while(arguments_buffer[j] != ' '){
            j++;

            if(arguments_buffer[j] == ' ' || arguments_buffer[j] == '\0'){
                arguments_buffer[j] = '\0';
                exec_argv[i] = (char *)malloc(sizeof(char)*strlen(&arguments_buffer[anchor_point]));
                strcpy(exec_argv[i], &arguments_buffer[anchor_point]);
                //printf("exec_argv: %s\n",exec_argv[i]);
                anchor_point = j+1;
                break;
            }
        }
    }
    

    
    if(fork() == 0){
        exec(argv[1],exec_argv);

        exit(0);
    }

    free(arguments_buffer);
    
    wait(0);

    exit(0);
}