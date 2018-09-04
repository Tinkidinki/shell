#include "header.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>

int cd(char **args){

    
    if (!args[1]){
        if (chdir(home_directory)){
            perror("turtle");
        }
    }

    else if (args[1][0]=='~'){
        if (chdir(home_directory)){
            perror("turtle");
        }
    }

    else if (chdir(args[1]) != 0){
        perror("turtle");
    }

    return 1;
}

int pwd(){
    char directory[PATH_MAX];
    if (getcwd(directory, sizeof(directory))!=NULL){
        printf("%s\n", directory);
    }
    else{
        perror("getcwd() error");
    }
}

int echo(char **args){
    int i=1;
    while(args[i]){
        printf("%s ",args[i]);
        i++;
    }
    printf("\n");
}

