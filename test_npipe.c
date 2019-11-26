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

	int fd, st_1, st_2; 
	pid_t ps_1, ps_2; 
	
	if( unlink("npipe") == -1)
		perror("unlink");
	if( mknod("npipe",S_IFIFO,0) == -1)
		perror("mknod");
	if( chmod("npipe",0666) == -1)
		perror("chmod");

	if( (fd = open("npipe", O_RDWR | O_APPEND) ) == -1)
		perror("open");
	printf("fd: %d\n",fd);


	/* First process: writer */ 
	ps_1 = fork(); 
	if( ps_1 == -1)
		perror("fork");

	if (ps_1 == 0) { 

		printf("llego pid %d ejecutando %s\n",getpid(), argv[1]);

		dup2(fd,1); 
		close(fd);

		execlp(argv[1], argv[1], "." , (char *) NULL) ; 
		perror(argv[1]);
		exit(0);  
	}

	/* Second process: reader */
	ps_2 = fork(); 
	if( ps_2 == -1)
		perror("fork");

	if (ps_2 == 0) {
		dup2(fd, 0); 
		close(fd);

		printf("llego pid %d ejecutando %s\n",getpid() ,argv[2]);

		execlp(argv[2], argv[2], "-l", (char*) NULL)  ;
		perror(argv[2]);
		exit(0); 
	}


	close(fd);
	printf("el padre llego pid %d \n",getpid());
	if ( wait(&st_1) == -1) 
		perror("wait");
	printf("termino %d\n",ps_1);

	if ( wait(&st_2) == -1) 
		perror("wait");
	printf("termino %d\n",ps_2);


	sleep(10);

	return 0; 
}

