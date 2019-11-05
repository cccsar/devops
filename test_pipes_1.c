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

char *frase="Mensaje de prueba";

int main (int argc, char *argv[]) {
	int fd[2], countbytes,status;
	char message[100];
	pid_t pid; 

	pipe(fd);
	pid = fork();
	if (pid==0) { /* codigo del hijo */
		close(fd[READ]);  /* Se cierran los descriptores que no se usan */
		printf("Entro al hijo\n");
		write(fd[WRITE], frase, strlen(frase) + 1);
		close(fd[WRITE]);
	} else { /* codigo del padre */
		close(fd[WRITE]); /* Se cierran los descriptores que no se usan */
		printf("Entro al padre\n");
		countbytes = read(fd[READ], message, 100);
		printf("Mensaje leido: %s\n", message);
		close(fd[READ]);
	}

	return 0 ; 
}

