#ifndef SHELL_H
#define SHELL_H
#define MAX_PATH_LEN 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef int (*builtin_func)(char **args);
typedef struct {
	char *name;
	builtin_func func;
}builtin_command;

//function dec
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
int execute_pipeline(char **left_cmd,char **right_cmd);
int launch(char **args,int background);
void sigint_handler(int sig);
int shell_cd(char **args);
int shell_exit(char **args);


#endif
