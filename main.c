#include "shell.h"
#include <signal.h>


int main(){

	
	char *lines;
	char **args;
	int status;

	char cwd[MAX_PATH_LEN];
	//signal(SIGINT,SIG_IGN); ignores cntrl+C
	
	signal(SIGINT,sigint_handler);

	do{
		
		if(getcwd(cwd,sizeof(cwd))!=NULL){
			printf("%s> ",cwd);
		}else{
			perror("getcwd error");
			printf("> ");
		}


	lines=read_line();
	args=parse_line(lines);
	status=execute(args);

	free(lines);
	free(args);

	}while(status);


return 0;
}

