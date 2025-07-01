#ifndef SHELL_H
#define SHELL_H
#define MAX_PATH_LEN 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//function dec
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
int launch(char **args);

#endif
