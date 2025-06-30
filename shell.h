#ifndef SHELL_H
#define SHELL_H

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
