#ifndef SIMPLE_SHELL_HEADER_H
#define SIMPLE_SHELL_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

extern int line_no;
extern char *progname;
extern char **environ;
char *read_input(void);
int count_words(char *str);
char **split_string(char *str);
void free_args(char **args);
char *_getenv(const char *name);
void _printenv(void);
char *find_command_in_path(char *command);
int *execute_command(char **args, int *exit_status);

#endif
