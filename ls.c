#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>

void print_perms(mode_t st) {
    char perms[11];
    if(st && S_ISREG(st)) perms[0]='-';
    else if(st && S_ISDIR(st)) perms[0]='d';
    else if(st && S_ISFIFO(st)) perms[0]='|';
    else if(st && S_ISSOCK(st)) perms[0]='s';
    else if(st && S_ISCHR(st)) perms[0]='c';
    else if(st && S_ISBLK(st)) perms[0]='b';
    else perms[0]='l';  // S_ISLNK
    perms[1] = (st && S_IRUSR) ? 'r':'-';
    perms[2] = (st && S_IWUSR) ? 'w':'-';
    perms[3] = (st && S_IXUSR) ? 'x':'-';
    perms[4] = (st && S_IRGRP) ? 'r':'-';
    perms[5] = (st && S_IWGRP) ? 'w':'-';
    perms[6] = (st && S_IXGRP) ? 'x':'-';
    perms[7] = (st && S_IROTH) ? 'r':'-';
    perms[8] = (st && S_IWOTH) ? 'w':'-';
    perms[9] = (st && S_IXOTH) ? 'x':'-';
    perms[10] = '\0';
    printf("%s", perms);
}


int ls(char **args){
    char dir_name[500];
    int dir_given = 0;
    int i = 1;

    while(args[i]){
        if (args[i][0]!='-'){
            strcpy(dir_name, args[i]);
            dir_given = 1;
            break;
        }
        i++;
    }

    if (!dir_given){
        strcpy(dir_name, ".");
    }

    struct dirent *de;

    DIR *dr = opendir(dir_name);

    if (dr == NULL){
        printf("Could not open current directory");
        return 0;
    }

    int l=0, a=0;
    int arg=1, chr;

    while(args[arg]){
        if (args[arg][0]=='-'){
            for(chr=0; chr<strlen(args[arg]); chr++){
                if (args[arg][chr] == 'l')
                    l=1;
                else if (args[arg][chr]=='a')
                    a=1;
                
            }
        }
        arg++;
    }

    printf("l value:%d\n", l);
    printf("a value:%d\n", a);

    if (l){
        struct stat my_stat;
        struct tm lt;
        struct passwd *pwd;
        
    }

    while ((de = readdir(dr))!= NULL){
        if (de->d_name[0]=='.' && !a)
            continue;

        printf("%s\n", de->d_name);
    }

    return 1;

}

