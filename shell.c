#include "shell.h"

int execute(char **args){
	if(args[0]==NULL){
		return 1;
	}

	if(strcmp(args[0],"exit")==0){
		return 0;
	}
	if(strcmp(args[0],"cd")==0){
		if(args[1]==NULL){
			fprintf(stderr,"kalk1t_shell: expected arguments to \"cd\"\n");
		}
		else{
			chdir(args[1]);
		}
	return 1;
	}
	return launch(args);
}

int launch(char **args){
pid_t pid;
pid_t wpid;
int status;

pid=fork();
	if(pid==0){
	//child process
		if(execvp(args[0],args)==-1){
			perror("kalk1t_shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid<0){
		//error forking
		perror("kalk1t_shell");
	}
	else{
		//parent process
		do {
			wpid=waitpid(pid,&status,WUNTRACED);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}


