#include "shell.h"
#include <signal.h>


int main(){

	
	char *line;
	char **args;
	int status;

	char cwd[MAX_PATH_LEN];
	//signal(SIGINT,SIG_IGN); ignores cntrl+C
	
	signal(SIGINT,sigint_handler);

	do{				
	
	line=read_line();
	args=parse_line(line);
	status=execute(args);

	free(line);
	free(args);

	}while(status);


return 0;
}

