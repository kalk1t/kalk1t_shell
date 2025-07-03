#include "shell.h"
#include <fcntl.h>


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

int i;

int in_redirect=0;
char *infile=NULL;

int out_redirect=0;
char *outfile=NULL;

//check for output redirection
for (i=0; args[i]!=NULL;i++){
	if(strcmp(args[i],">")==0){
		out_redirect=1;
		outfile=args[i+1];
		args[i]=NULL; // remove '>' from args
		break;
	}
	else if(strcmp(args[i],"<")==0){
		in_redirect=1;
		infile=args[i+1];
		args[i]=NULL; // remove '<' from args
		break;
	}
}


pid=fork();
	if(pid==0){
	//child process
		
		if(out_redirect){
			int fd=open(outfile,O_WRONLY|O_CREAT|O_TRUNC, 0644);
			if(fd<0){
				perror("kalk1t_shell");
				exit(EXIT_FAILURE);
			}
			dup2(fd,STDOUT_FILENO); //redirect stdout to file
			close(fd);

		}

		if(in_redirect){
			int fd=open(infile,O_RDONLY);
			if(fd<0){
				perror("kalk1t_shell");
				exit(EXIT_FAILURE);
			}
			dup2(fd,STDIN_FILENO);
			close(fd);
		}

		//error forking
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


