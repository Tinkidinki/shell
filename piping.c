#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <pwd.h>

#include "header.h"

int split_by_pipe(char** args){
    pipe_split = malloc(64 * sizeof(char**));
    pipe_split[0] = malloc(64*sizeof(char*));
    int i = 0;
    int p = 0;
    int count = 0;
    
    while(args[i]){
        if (strcmp(args[i], "|")!=0){
            pipe_split[p][count] = args[i];
            count++;
        }
        else{
            pipe_split[p][count] = NULL;
            count = 0;
            p++;
            pipe_split[p] = malloc(64 * sizeof(char*));
        }
        i++;
    }
    int num_expressions = p+1;

    for (int exp=0; exp< num_expressions; exp++){
        print_list(pipe_split[exp]);
        printf("___________________\n");
    }
    return num_expressions;
}