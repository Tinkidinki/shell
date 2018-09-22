#ifndef INBUILTS_H_   /* Include guard */
#define INBUILTS_H_

#include <stdbool.h>

int redirect(char **args);
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
void print_list(char** list);

char home_directory[500];
char infiles[100][100];
char outfiles[100][100];

#endif // INBUILTS_H_