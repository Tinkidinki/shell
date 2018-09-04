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
    perms[1] = (st & S_IRUSR) ? 'r':'-';
    perms[2] = (st & S_IWUSR) ? 'w':'-';
    perms[3] = (st & S_IXUSR) ? 'x':'-';
    perms[4] = (st & S_IRGRP) ? 'r':'-';
    perms[5] = (st & S_IWGRP) ? 'w':'-';
    perms[6] = (st & S_IXGRP) ? 'x':'-';
    perms[7] = (st & S_IROTH) ? 'r':'-';
    perms[8] = (st & S_IWOTH) ? 'w':'-';
    perms[9] = (st & S_IXOTH) ? 'x':'-';
    perms[10] = '\0';
    printf("%s", perms);

    // printf("User has read: %d\n", S_IXUSR);
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

    // file name
    char short_name[1000];
    char name[1000];
    char buf[128];

    if (dr == NULL){
        //printf("turtle: Could not open the directory\n");
        return 1;
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


    struct stat my_stat;
    struct tm local_time;
    struct passwd pwent, *pwentpt;
    struct group grp, *grpt;
    char datestring[256];

    while ((de = readdir(dr))!= NULL){
        
        strcpy(short_name, de->d_name);
        realpath(short_name, name);
        //printf(" full path before: %s\n", name);
        
        if (short_name[0]=='.' && !a)
            continue;

        if (l){
            stat(name, &my_stat);
            print_perms(my_stat.st_mode);
            printf("%d", (int) my_stat.st_nlink);

            //printf(" full path middle 0: %s\n", name);

            if (!getpwuid_r(my_stat.st_uid, &pwent, buf, sizeof(buf), &pwentpt)){
                printf(" %s", pwent.pw_name);
            }
            else{
                printf(" %d", my_stat.st_uid);
            }

            //printf(" full path middle 1: %s\n", name);

            if (!getgrgid_r(my_stat.st_gid, &grp, buf, sizeof(buf), &grpt)){
                printf(" %s", grp.gr_name);
            }
            else{
            printf(" %d", my_stat.st_gid);
            }

            printf(" %5d", (int)my_stat.st_size);

            //printf(" full path middle 2: %s\n", name);

            localtime_r(&my_stat.st_mtime, &local_time);

            strftime(datestring, sizeof(datestring), "%F %T", &local_time);

            printf(" %s", datestring);
        }


        printf(" %s\n", short_name);
    }

    return 1;

}

