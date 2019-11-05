
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 

#define TRUE 1
#define P_664 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
#define C_W_T O_WRONLY | O_TRUNC | O_CREAT

/* Imitating redirection of type command > file */ 
/* Para dup el nuevo copia al viejo, nada pasa con el viejo
 * Si el nuevo estaba abierto, se cierra y luego se abre
 * Esto se hace de forma atomica */ 
int main (int argc, char **argv) { 

	int term_pid, wstatus, my_fd, pid, cached_fd; 

	cached_fd = dup(1); 
	
	if ( !(my_fd = open(argv[2], C_W_T, P_664 )) )
		perror("open"); 

	if ( !dup2(my_fd,1) )
		perror("dup2");


	pid = fork(); 	
	if ( pid == -1)  {
		perror("fork"); 
		exit(1);
	}

	if ( pid == 0) { 		/* child */

		if (execl(argv[1], argv[1], (char *) NULL) == -1) 
			perror("execlp"); 
	}
	else { 				/* parent */

		if ( pid = wait(&wstatus) == -1 ) /* usar waitpid() */
			perror("wait"); 

		/* Reestablesco salida estandar */
		dup2(cached_fd,1); 
		fprintf(stdout, "child with pid: %d terminated\n",pid); 
	}

	close(cached_fd); 
	close(my_fd) ;

	return 0;
}
