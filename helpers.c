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

int get_home_directory(){
    
    if (getcwd(home_directory, sizeof(home_directory))==NULL){
        perror("getcwd() error");
    }
    return 1;
}

bool starts_with(const char *a, const char *b){
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

int display_prompt(){
    char directory[PATH_MAX];
    char prompt[PATH_MAX + 100];
    char username[100];
    char hostname[100];

    struct passwd *passwd;
    passwd = getpwuid(getuid());
    sprintf(username, "%s", passwd->pw_name);
    gethostname(hostname, 100);
    
    if (getcwd(directory, sizeof(directory))!=NULL){
        
        if (starts_with(directory, home_directory)){
            sprintf(prompt, "<%s@%s:~%s>", username, hostname, &directory[strlen(home_directory)]);
        }
        else{
            sprintf(prompt, "<%s@%s:%s>", username, hostname, directory);
        }
    }
    else{
        perror("getcwd() error");
    }
    
    printf("%s ", prompt);
}

void print_list(char** list){
    int i=0;
    while(list[i]){
        printf("%s\n", list[i]);
        i++;
    }
}
