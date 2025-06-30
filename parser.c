#include "shell.h"

char *read_line(void){

	char *line=NULL;
	size_t bufsize=0;
	getline(&line,&bufsize,stdin);
	return line;
}


char **parse_line(char *line){

	int bufsize=64;
	int position=0;
	char **tokens=malloc(bufsize * sizeof(char*));
	char *token;


	token=strtok(line," \t\r\n");
	while(token != NULL){
		tokens[position++]=token;
	
	
	if(position>=bufsize){
		bufsize+=64;
		tokens=realloc(tokens,bufsize * sizeof(char*));
	}

	token=strtok(NULL," \t\r\n");
	}
	tokens[position]=NULL;
	return tokens;
}
