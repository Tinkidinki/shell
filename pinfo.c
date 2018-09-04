#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <limits.h>

#include "header.h"

int pinfo(int pid){
    
    char stat_file[200];
    char mem_file[200];
    char exec_file[200];


    char state;
    long  int virtual_mem;
    char executable_path[100];


    sprintf(stat_file, "/proc/%d/stat", pid);
    sprintf(mem_file, "/proc/%d/statm", pid);
    sprintf(exec_file, "/proc/%d/exe", pid);

    // Finding the state
    FILE* stat_fd = fopen(stat_file, "r");
    if (stat_fd == NULL){
        printf("No process for the given id exists.\n");
        return 1;
    }
    int spaces =0;
    
    while(1){
        state = fgetc(stat_fd);
        if (spaces==2){
            break;
        }
        else if (state==' '){
            spaces++;
        }
    }
    //------------------

    // Finding the memory
    FILE* mem_fd = fopen(mem_file, "r");
    fscanf(mem_fd, "%lu", &virtual_mem);
    //--------------------

    //Finding the executable path
    readlink(exec_file, executable_path, 256);
    //--------------------

    printf("Process id: %d\n", pid);
    printf("Process State: %c\n", state);
    printf("Virtual Memory: %lu\n", virtual_mem);
    printf("Executable path:%s\n", executable_path);

    return 1;

}