#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <limits.h>

#include "header.h"

int launch(char** args, int fg){
    printf("step 2 launch is called\n");
    printf("the command:%s\n", args[0]);
    int pid, status;

    pid = fork();
    if (pid==0){
        printf("step 3: enters the child process\n");
        execvp(args[0], args);
    }
    else{
        if (fg){
            
            if( waitpid( pid, &status, 0 ) == -1 ) {
  				perror( "waitpid" );
			} 

        }
    }

    return 1;
}