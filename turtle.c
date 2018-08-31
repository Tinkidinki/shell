#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <limits.h>

#include "inbuilts.h"

int get_home_directory(){

}

int display_prompt(){
    char directory[PATH_MAX];
    
    if (getcwd(directory, sizeof(directory))!=NULL){
        printf("%s>", directory);
    }
    else{
        perror("getcwd() error");
    }
    
}

int turtle_execute(char **args){
    int i;
    if (args[0] == NULL){
        return 1;
    }
    
    else if (strcmp(args[0], "cd")==0){
        printf("Args[0] contents:%s\n", args[0]);
        cd(args);
        printf ("comes back here?\n");
        return 1;
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

    // Set the home directory
    
    do{
        display_prompt();
        line = turtle_read_line();
        printf("line: %s\n", line);
        args = turtle_split_line(line);
        //printf("%s,%s", args[0], args[1]);        
        status = turtle_execute(args);
    } while(status);

    return 1;
}

int main(){
    turtle_loop();
    return 0;
}