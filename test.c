
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define P_664 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
#define C_W_T O_WRONLY | O_TRUNC | O_CREAT

int main (int argc, char **argv) { 

	int term_pid, wstatus, my_fd, pid; 

	if ( !(my_fd = open(argv[2], C_W_T, P_664 )) )
		perror("open"); 

	if ( !dup2(my_fd,1) )
		perror("dup2");


	pid = fork(); 	
	if ( pid == -1)  {
		perror("fork"); 
		exit(1);
	}

	if ( pid == 0) { 
		/* child */
		if (execv(argv[1], argv[]) == -1){
			perror("execv"); 
			exit(0); 
		}

	}
	else { 
		/* parent */
		if ( t_pid = wait(&wstatus) == -1 ) /* usar waitpid() */
			perror("wait"); 

		printf("child with pid: %d terminated\n",t_pid); 
	}


	return 0;
}
