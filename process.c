#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <limits.h>

#include "header.h"

int launch(char** args, int fg){

    int wpid,pid, status;
    

    pid = fork();
    if (pid==0){
        
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
                return -1;
			} 

        }
    }

    return 1;
}