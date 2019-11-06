#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <signal.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int delay;

int main (int argc, char **argv) { 
	int pid; 

	void (*childHandler); 
	/* Creo manejador de senales de hijos */
	signal(SIGCHLD, childHandler); 

	pid = fork(); 
	if (pid == 0) { 
			execvp(argv[2], &argv[2], &argv[3]); 
		perror("exec"); 
	}
	else { 
		delay = atoi(argv[1]); 
		sleep(delay); 
		printf("El hijo %d se excedio en tiempo.. debe morir ..\n",pid); 
	}


	return 0; 

}

void childHandler(){ 

	int childPid, childStatus; 
	printf("perico\n"); 

	childPid = wait(&childStatus); 

	printf("El hijo %d termino en menos de %d segundo ..\n",childPid,delay); 
	exit(0); 
}
