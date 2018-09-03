#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h> 


int list_dir(const char *dirname){
    struct dirent* cur_dir;

    struct stat my_stat;
    struct tm lt;
    struct passwd *pwd;

    DIR* directory = opendir(dirname);
    char fullpath[PATH_MAX];

    if (directory ==NULL){
        printf("list_dir: %s : %s \n", dirname, strerror(errno));
        return 0;
    }

    printf("directory: %s\n", dirname);
    printf("\n");

    while (cur_dir = readdir(directory)){
        realpath(cur_dir->d_name, fullpath);
        //printf("current directory:%s\n", cur_dir->d_name);
        //printf("full path:%s\n", fullpath);
        if (stat(fullpath, &my_stat) == 0){
            pwd = getpwuid(my_stat.st_uid);
        }

        time_t t = my_stat.st_mtime;
        localtime_r(&t, &lt);
        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%c", &lt);

        if (pwd!=0){
            printf("%s \t %ld \t %s \t %s\n", pwd->pw_name, (long)my_stat.st_size, timebuf, cur_dir->d_name);
        }
        else {
            printf("%d \t %ld \t %s \t %s\n", my_stat.st_uid, (long)my_stat.st_size, timebuf, cur_dir->d_name);
        }
    }
    closedir(directory);
    return 0;
    
}

int main(int argc, char* argv[]){
    if (argc == 1){
        return list_dir(".");
    }
    
    else{
        int ret = 0;
        for (int i=1; i< argc; i++){
            if (list_dir(argv[i])!=0){
                ret = 1;
            }
        }
        return ret;
    }
}