#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

// didn't get this
int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins(){
    return sizeof(builtin_str) / sizeof(char *);
};

int lsh_cd(char **args){
    if (args[1] == NULL){
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else {
        if (chdir(args[1]) !=0) {
            perror ("lsh");
        }
    }
};

int lsh_help(char **args){
    int i;
    printf("This is my shell\n");
    printf("Type commands and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i=0; i< lsh_num_builtins(); i++){
        printf(" %s\n", builtin_str[i]);
    }
}

int lsh_exit(char **args){
    return 0;
}



int lsh_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0){
        execvp(args[0], args);
        perror("lsh");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0){
        perror("lsh");
    }
    else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        }while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int lsh_execute(char **args){
    int i;
    if (args[0] == NULL){
        return 1;
    }

    for (i=0; i<lsh_num_builtins();i++){
        if (strcmp(builtin_str[i], args[0])){
            return (*builtin_func[i])(args);
            return 0;
        }
    }

    return lsh_launch(args);
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE, position =0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL){
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc (tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
    
}

char *lsh_read_line(void){
    char* line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = lsh_read_line();
        printf("line: %s\n", line);
        args = lsh_split_line(line);
        printf("first argument: %s, second argument: %s\n",args[0], args[1]);
        status = lsh_execute(args);

        free(line);
        free(args);
    }while (status);
}

int main(){
    lsh_loop();
    return 0;
}

