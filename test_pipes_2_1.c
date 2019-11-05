#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h> 

#define READ 0
#define WRITE 1

int main (int argc, char *argv[]) {
	int fd[2];
	pipe(fd);
	if (fork()==0) { /* codigo del hijo */
		close(fd[READ]);
		dup2(fd[WRITE],1); /* redireccion de la salida al pipe */
		close(fd[WRITE]);
		execlp(argv[1], argv[1], NULL); /* Porque se usa execlp ?*/
		perror("connect");
	} else {
		close(fd[WRITE]); /* codigo del padre */
		dup2(fd[READ],0);
		close(fd[READ]);
		execlp(argv[2], argv[2], NULL);
		perror("connect");
	}
	
	return 0; 
}
