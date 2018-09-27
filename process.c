#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <limits.h>

#include "header.h"

int launch(char** args, int fg){
    printf("Launched\n");
    int wpid,pid, status;
    

    pid = fork();
    if (pid==0){
        signal(SIGINT, SIG_DFL);
        if (fg){
            printf("This is in the fg portion\n");
            char* path = "/proc/self/fd/0";
            char buf[1000];
            readlink(path, buf, 1000);
            printf("0 points to: %s\n", buf);
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
            printf("Parent of fg\n");
            if( waitpid( pid, &status, 0 ) == -1 ) {
  				printf( "waitpid\n" );
                return -1;
			} 
        }
    }
    printf("Done with the else part\n");
    return 1;
}