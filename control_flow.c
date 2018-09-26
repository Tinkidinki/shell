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

int control_flow(char** args, int precedes){

    printf("Inside control flow\n");

    int stdin_copy_pipe = dup(0);
    if (stdin_copy_pipe==-1)
        perror("stdin_copy_pipe was not made\n");

    int stdout_copy_pipe = dup(1);
    if (stdout_copy_pipe==-1)
        perror("stdout_copy_pipe was not made\n");

    if (precedes){
        printf("precedes\n");
        int fd[2];
        
        if (pipe(fd) == -1){
            fprintf(stderr, "pipe failed\n");
        }

        close(1);
        if (dup2(fd[1], 1)!=1)
            perror("dup2 error 1 to p_in\n");

        redirect(args);
        status = turtle_execute(args);
        printf("done FIRST\n");
        finish_redirect();

        close(0);
        if (dup2(fd[0], 0)!=0)
            perror("dup2 error 0 to p_out\n");
        
        close(1);
        if (dup2(stdout_copy_pipe, 1)!=1)
            perror("dup2 error 1 to stdout_copy_pipe\n");

        printf("After the if part\n");
    }

    else{
        
        redirect(args);
        status = turtle_execute(args);
        // finish_redirect();
        printf("done SECOND\n");
        
        // if (dup2(stdin_copy_pipe, 0)!=1)
        //     perror("dup2 error 1 to stdin_copy_pipe");
        //finish_redirect();
    }

    return 0;
}