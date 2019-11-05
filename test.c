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
	
	pid_t ps_1; 
	int st_1; 

	ps_1 = fork(); 
	if (ps_1 == -1)
		perror("fork");

	if (ps_1== 0) 
		execlp(argv[1],argv[1], argv[2], (char*) NULL ) ;		
		

	if (wait(&st_1) == -1) 
		perror("wait"); 

	return 0; 

}
