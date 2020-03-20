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
#define READ 0
#define WRITE 1

int main (int argc, char **argv) { 

	int fd[2], st_1, st_2; 
	pid_t ps_1, ps_2; 
	

	if( pipe(fd) == -1)
		perror("pipe"); 

	/* First process: writer */ 
	ps_1 = fork(); 
	if( ps_1 == -1)
		perror("fork");

	if (ps_1 == 0) { 

		close(fd[READ]); 

		printf("llego pid %d\n",getpid());
		printf("ejecutando %s\n",argv[1]);
		dup2(fd[WRITE],1); 

		close(fd[WRITE]); 

		execlp(argv[1], argv[1], (char *) NULL) ;
		perror("execlp"); 
		exit(0);  
	}

	/* Second process: reader */
	ps_2 = fork(); 
	if( ps_2 == -1)
		perror("fork");

	if (ps_2 == 0) {
		close(fd[WRITE]); 

		dup2(fd[READ], 0); 

		close(fd[READ]); 

		printf("llego pid %d\n",getpid());
		printf("ejecutando %s\n",argv[2]);
		execlp(argv[2], argv[2], "-l", (char*) NULL)  ;
		perror("execlp");
		exit(0); 
	}


	/*printf("el padre %d llego pid \n",getpid());*/
	close(fd[READ]); 
	close(fd[WRITE]); 
	if ( wait(&st_1) == -1) 
		perror("wait");
	/*printf("termino %d\n",ps_1);*/

	if ( wait(&st_2) == -1) 
		perror("wait");
	/*printf("termino %d\n",ps_2);*/


	return 0; 
}

