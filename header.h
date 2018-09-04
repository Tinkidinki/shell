#ifndef INBUILTS_H_   /* Include guard */
#define INBUILTS_H_

#include <stdbool.h>

int cd(char **args);
int pwd();
int echo(char **args);
int ls(char **args);
int launch(char **args, int fg);
int remindme(char** args);
int pinfo(int pid);
int get_home_directory();
bool starts_with(const char *a, const char *b);
int display_prompt();

char home_directory[500];

#endif // INBUILTS_H_