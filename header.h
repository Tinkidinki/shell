#ifndef INBUILTS_H_   /* Include guard */
#define INBUILTS_H_

int cd(char **args);
int pwd();
int echo(char **args);
int ls(char **args);
int launch(char **args, int fg);
int remindme(char** args);
int pinfo(int pid);

#endif // INBUILTS_H_