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
int control_flow(char** args, int precedes);
int turtle_execute(char** args);

int status;
char home_directory[500];
char** infiles;
char** outfiles;
char** appendfiles;
int stdin_copy_red, stdout_copy_red;
int stdin_copy_pipe, stdout_copy_pipe;
char*** pipe_split;
#endif // INBUILTS_H_