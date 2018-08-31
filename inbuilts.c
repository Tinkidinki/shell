#include "inbuilts.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>

int cd(char **args){
    printf("cd function called\n");

    // if (strcpy(args[1], ".")==0){
    //     //
    // }

    if (chdir(args[1]) != 0){
        perror("turtle: ");
    }

    return 1;
}

int pwd(){
    char directory[PATH_MAX];
    printf ("pwd called\n");
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

int ls(char **args){
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL){
        printf("Could not open current directory");
        return 0;
    }

    int l=0, a=0;
    int arg=1, chr;

    while(args[arg]){
        if (args[arg][0]=='-'){
            for(chr=0; chr<strlen(args[arg]); chr++){
                if (args[arg][chr] == 'l')
                    l=1;
                else if (args[arg][chr]=='a')
                    a=1;
                
            }
        }
        arg++;
    }

    printf("l value:%d\n", l);
    printf("a value:%d\n", a);

    while ((de = readdir(dr))!= NULL){
        if (de->d_name[0]=='.' && !a)
            continue;

        printf("%s\n", de->d_name);
    }

    return 1;

}
