#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"



void find(char * file, char * path){
    struct stat st;
    struct dirent directory_entry;
    int path_end_index = strlen(path);
    //char buffer[256];
    
    int path_fd = open(path, O_RDONLY);
    
    /*switch(st.type){
        case T_FILE:
            printf("testing, seen a file\n");
            break;

        case T_DIR:
            printf("testing, seen a directory\n");
            break;
    }*/

    while(read(path_fd, &directory_entry, sizeof(directory_entry)) == sizeof(directory_entry)){
        

        if(directory_entry.inum == 0){
            continue;
        }

        strcpy(&path[path_end_index], "/");

        strcpy(&path[path_end_index+1], directory_entry.name);
        
        if(strcmp(file, directory_entry.name) == 0){
            printf("%s\n",path);
        }


        //printf("%s\n", path);

        stat(path, &st);

        /*if(strcmp("a", directory_entry.name)==0){
            printf("found a st.type:%d\n", st.type);
        }*/

        switch(st.type){
            case 1:
                //printf("found directory: %s\n",path);
                if(strcmp(directory_entry.name, ".") == 0 || strcmp(directory_entry.name, "..") == 0){
                    break;
                }

                //printf("found directory:%s\n", path);
                find(file, path);
                break;
        }
        
        //printf("%s\n",path);
        path[path_end_index] = '\0';
        //printf("%s\n",path);
    }

}

int main(int argc, char *argv[]){

    if(argc < 3){
        printf("not enough arguments\n");

        printf("format: find /path/to/look file_name\n");

        exit(0);
    }

    char *file = (char *) malloc(sizeof(argv[1]));
    char *path = (char *) malloc(sizeof(char)*4096); 

    strcpy(file, argv[2]);
    strcpy(path, argv[1]);

    //printf("%s\n", file);

    find(file, path);

    exit(0);
}