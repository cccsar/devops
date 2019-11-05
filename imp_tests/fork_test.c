#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main (int argc, char *argv[]) {
	
	int  child_status; 
	pid_t pid; 

	if ( (pid = fork()) == -1) 
		perror("fork"); 

	if (pid == 0) { 
		printf("Soy el hijo\n\tmi pid es %d, mi padre es %d\n", getpid()
				, getppid()); 
	}
	else { 
		printf("Soy el padre, mi pid es %d\n",getpid()); 

		if (waitpid(pid,&child_status, WUNTRACED) == -1) 
			perror("wait"); 

		printf("Mi hijo %d termino\n",pid); 
	}

	return 0 ;

}
