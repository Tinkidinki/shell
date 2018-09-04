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
    int wpid,pid, status;
    

    pid = fork();
    if (pid==0){
        printf("step 3: enters the child process\n");
        
        if (fg){
            execvp(args[0], args);
        }

        else{
            pid = fork();
            if (pid == 0){
                execvp(args[0], args);
            }
            else{
                do{
                    wpid = waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));

                char name[500];
                char filename[500];
                char proc[] = "/proc/";
                char status[] = "/status";
                
                printf("\n Background process complete\n");
                printf("Process id: %d\n", pid);
            

            }

        }
    
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