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
int finish_redirect();
int split_by_pipe(char** args);

char home_directory[500];
char** infiles;
char** outfiles;
char** appendfiles;
int stdin_copy, stdout_copy;
char*** pipe_split;
#endif // INBUILTS_H_