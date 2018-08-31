#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>



int main(){
    int pid;
    int status;
    // char s[100];
    // scanf("%s",s);

    // //strtok is clearly not a pure function
    // char* token = strtok(s, "-");

    // while (token!=0){
    //     printf("%s\n", token);
    //     token = strtok(0, "*-");
    // }

    pid = fork();
    int x = 0;

    if (pid==0){
        printf("%d\n", 5/3);
        printf("Child process:%d\n", status);
    }
    else {
        printf("parent process:%d\n", status);

    }


    return 0;

    
}