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



int turtle_execute(char **args){
    printf("Went into turtle execute\n");

    if (strcmp(args[0], "quit")){
        printf("Exiting the turtle shell. Have a nice day!\n");
        return 0;
    }
    
    if (args[0] == NULL){
        return 1;
    }
    
    else if (strcmp(args[0], "cd")==0){
        cd(args);
    }

    else if (strcmp(args[0], "pwd")==0){
        pwd();
    }

    else if (strcmp(args[0], "echo")==0){
        echo(args);
    }

    else if (strcmp(args[0], "ls") == 0){
        ls(args);
    }

    else if(strcmp(args[0], "remindme") == 0){
        remindme(args);
    }

    else if(strcmp(args[0], "pinfo")==0){
        if (args[1]){
            pinfo(atoi(args[1]));
        }
        else{
            pinfo(getpid());
        }
    }

    else{
        printf("Went in the else part\n");
        int fg = 1;
        int i=0;


        while(args[i]){
            printf("In the while loop for &\n");
            if (strcmp(args[i], "&")==0){
                fg = 0;
                args[i] = NULL;
                break;
            }
            i++;
        }

        int status = launch(args, fg);
        if (status == -1){
            printf("Command does not exist\n");
            exit(0);
        }

    }
}

#define TURTLE_TOK_BUFSIZE 64
#define TURTLE_TOK_DELIM " \t\r\n\a"
char **turtle_split_line(char* line){
    int bufsize = TURTLE_TOK_BUFSIZE, position =0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        fprintf(stderr, "turtle: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TURTLE_TOK_DELIM);
    while (token!=NULL){
        tokens[position] = token;
        position++;

        if (position >= bufsize){
            bufsize += TURTLE_TOK_BUFSIZE;
            tokens = realloc( tokens, bufsize * sizeof(char*));
            if (!tokens){
                fprintf(stderr, "turtle: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TURTLE_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;

}

char *turtle_read_line(void){
    char* line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}


int turtle_loop(){
    char *line;
    char **args;
    int status =1;
    int num_expressions;
    signal(SIGINT, SIG_IGN);
    int exp;
    

    // Set the home directory
    
    do{
        display_prompt();
        copy_streams();
        line = turtle_read_line();
        args = turtle_split_line(line);
        num_expressions = split_by_pipe(args);
    
        for (exp = 0; exp < num_expressions-1; exp++){
            control_flow(pipe_split[exp], 1); // precedes a pipe
        }
        
        control_flow(pipe_split[num_expressions - 1], 0); // does not precede a pipe
    
    } while(status);

    return 1;
}

int main(){
    get_home_directory();
    turtle_loop();
    return 0;
    
}