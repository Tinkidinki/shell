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

    if (precedes){
        printf("precedes\n");
        //int fd[2];
        
        if (pipe(fd) == -1){
            fprintf(stderr, "pipe failed\n"); // Make a pipe
        }

        close(fd[0]); // Close the exit of the pipe
        if (dup2(fd[1], 1)!=1)   // Point 1 to the entry of the pipe
            perror("dup2 error 1 to p_in\n");
        

        redirect(args);
        status = turtle_execute(args); // Execute the args
        printf("done FIRST\n");
        finish_redirect();

        if (dup2(fd[0], 0)!=0)   // Point 0 to the exit of the pipe
            perror("dup2 error 0 to p_out\n");
        close(fd[1]); // Close the entry of the pipe
        
        if (dup2(stdout_copy, 1)!=1)  // Point 1 back to std output
            perror("dup2 error 1 to stdin_copy\n");

        printf("After the if part\n");
    }

    else{
        
        redirect(args);
        printf("reached the else part\n");
        status = turtle_execute(args);
        finish_redirect();
        printf("done SECOND\n");
        if (dup2(stdin_copy, 0)!=0)  // Point 0 back to standard input
            perror("dup2 error 1 to stdin_copy");
        
    }

    return 0;
}