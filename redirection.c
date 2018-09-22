#include "header.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>
#include<sys/stat.h>
#include<fcntl.h>


void remove_element(char** args, int index){
    int i = index;
    printf("After removing:%s\n", args[i]);
    while(args[i]){
        args[i] = args[i+1];
        i++;
    }
    print_list(args);
    printf("---------------\n");
}

int redirect(char** args){
    printf("inside redirect\n");
    print_list(args);

    // removing the in and out files
    int i=0;
    int in=0;
    int out=0;
    while(args[i]){
        if (strcmp(args[i], "<")==0){
            printf("Saw <\n");
            strcpy(infiles[in], args[i+1]);
            remove_element(args, i);
            remove_element(args, i);
            print_list(args);
            in++;
        }
        else if (strcmp(args[i], ">")==0){
            printf("Saw >\n");
            strcpy(outfiles[out], args[i+1]);
            remove_element(args, i);
            remove_element(args, i);
            print_list(args);
            out++;
        }
        else{
            i++;
        }
    }

    // redirecting to in and out files
    // in files
    in = 0;
    int fi;
    while(infiles[in]){
        fi = open(infiles[in], O_RDONLY);
        if (dup2(fi, 0)!=0){
            perror("dup2 failed");
        }
        in++;
    }

    // out files
    out = 0;
    int fo;
    while(outfiles[out]){
        fo = open(outfiles[out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dup2(fo, 1)!=1){
            perror("dup2 failed");
        }
        out++;
    }

}


