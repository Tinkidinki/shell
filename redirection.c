#include "header.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>
#include<sys/stat.h>
#include<fcntl.h>


void remove_element(char** args, int index){
    int i = index;
    // printf("After removing:%s\n", args[i]);
    while(args[i]){
        args[i] = args[i+1];
        i++;
    }
    // print_list(args);
    // printf("---------------\n");
}

int redirect(char** args){
    //printf("inside redirect\n");
    //print_list(args);
    infiles = malloc(64 * sizeof(char*));
    outfiles = malloc(64 * sizeof(char*));
    appendfiles = malloc(64 * sizeof(char*));

    // removing the in and out files
    int i=0;
    int in=0;
    int out=0;
    int app = 0;
    while(args[i]){
        if (strcmp(args[i], "<")==0){
            // printf("Saw <\n");
            infiles[in] = args[i+1];
            remove_element(args, i);
            remove_element(args, i);
            // print_list(args);
            in++;
        }
        else if (strcmp(args[i], ">")==0){
            // printf("Saw >\n");
            outfiles[out] = args[i+1];
            remove_element(args, i);
            remove_element(args, i);
            // print_list(args);
            out++;
        }
        else if (strcmp(args[i], ">>")==0){
            // printf("Saw >\n");
            appendfiles[app] = args[i+1];
            remove_element(args, i);
            remove_element(args, i);
            // print_list(args);
            app++;
        }

        else{
            i++;
        }
    }
    // strcpy(infiles[in], "\0");
    // strcpy(outfiles[out], "\0");
    infiles[in] = NULL;
    outfiles[out] = NULL;
    appendfiles[app] = NULL;


    // Trying output redirection
    out = 0;
    stdout_copy = dup(1);
    if (outfiles[out]){
        close(1);
        open(outfiles[out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    app = 0;
    stdout_copy = dup(1);
    if (appendfiles[app]){
        close(1);
        open(appendfiles[app], O_WRONLY | O_CREAT | O_APPEND, 0644);
    }

    // Trying input redirection
    in = 0;
    stdin_copy = dup(0);
    if (infiles[in]){
        close(0);
        open(infiles[in], O_RDONLY);
    }

    return 0;
}

int finish_redirect(){
    close(1);
    dup2(stdout_copy, 1);
    close(0);
    dup2(stdin_copy, 0);
}
