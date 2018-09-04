#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <limits.h>

#include "header.h"

int remindme(char** args){
    int pid, wpid, status;
  
    pid = fork();
    
    if (pid==0){
        pid = fork();

        if (pid==0){

            int seconds = atoi(args[1]);
            sleep(seconds);
            return 0;
        }
        else{
            do{
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));

            int word = 2;
            while(args[word]){
                printf("%s ",args[word]);
                word++;
            }
            printf("\n");

        }
    }

    return 1;
}
