#include "shell.h"

char *read_line(void){
	
	char *cwd=getcwd(NULL,0);
	size_t prompt_len=strlen(cwd)+4;
	char *prompt=malloc(prompt_len);
	snprintf(prompt,prompt_len,"%s >",cwd);
	free(cwd);

	char *line=readline(prompt); // display current directory as prompt
	free(prompt);

	if(line && *line){
		add_history(line);
	}
	
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
