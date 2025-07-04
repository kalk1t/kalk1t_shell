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
	
	//check for pipeline
	for(int i=0;args[i]!=NULL;i++){
		if(strcmp(args[i],"|")==0){
			args[i]=NULL;
			int result=execute_pipeline(args,&args[i+1]);
			return result;
		}
	}

	//check for background
	int background=0;
	for(int i=0;args[i]!=NULL;i++){
		if(strcmp(args[i],"&")==0){
			background=1;
			args[i]=NULL; //remove & from args;
			break;		
		}
	}
			
	
	


	return launch(args,background);
}

int execute_pipeline(char **left_cmd,char **right_cmd){
	int pipefd[2];
	pid_t p1,p2;

	if(pipe(pipefd)<0){
		perror("kalk1t_shell");
		return 1;
	}

	p1=fork();
	if(p1==0){
		//first child
		dup2(pipefd[1],STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);

		if(execvp(left_cmd[0],left_cmd)==-1){
			perror("kalk1t_shell");
			exit(EXIT_FAILURE);
		}
	}

	if(p2==0){
		//secpnd child: right command
		dup2(pipefd[0],STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		
		if(execvp(right_cmd[0],right_cmd)==-1){
			perror("kalk1t_shell");
			exit(EXIT_FAILURE);

		}
	}
//parent closes pipe ends and waits
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(p1,NULL,0);
		waitpid(p2,NULL,0);

		return 1;
}

void sigint_handler(int sig){
	char cwd[MAX_PATH_LEN];
	getcwd(cwd,sizeof(cwd));
	printf("%s\n",cwd);
}


int launch(char **args,int background){
pid_t pid;
pid_t wpid;
int status;

int i;

int in_redirect=0;
char *infile=NULL;

int out_redirect=0;
char *outfile=NULL;

int append_redirect=0;

//check for output redirection
for (i=0; args[i]!=NULL;i++){
	if(strcmp(args[i],">")==0){
		out_redirect=1;
		outfile=args[i+1];
		args[i]=NULL; // remove '>' from args
		break;
	}
	else if(strcmp(args[i],">>")==0){
		append_redirect=1;
		outfile=args[i+1];
		args[i]=NULL;
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
		if(append_redirect){
			int fd=open(outfile,O_WRONLY|O_CREAT|O_APPEND,0644);
			if(fd<0){
				perror("kalk1t_shell");
				exit(EXIT_FAILURE);
			}
			dup2(fd,STDOUT_FILENO);
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
		if(!background){
			do {
				wpid=waitpid(pid,&status,WUNTRACED);	
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}else{
			printf("Process running in background with PID %d\n",pid);
		}
	}
	return 1;
}


