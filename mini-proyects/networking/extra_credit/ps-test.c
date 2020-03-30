#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <ctype.h> 
#include <malloc.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAXPS 10


int main(int argc, char ** argv) { 
	pid_t ps[MAXPS], i_, status[MAXPS]; 
	int bound; 
	
	if ( argc < 1 ) {
		fprintf(stderr, "At least two arguments\n"); 
		exit(-1); 
	}

	for(i_=1; i_<argc ;i_++) { 
		ps[i_] = fork(); 
		if ( ps[i_] == 0 )
			break; 
	}	

	if (ps[i_] == 0) { 
		int fd = open(argv[i_], O_RDWR); 

		if ( fd == -1) 
			exit(-1); 

		sleep(1000); 
	}

	for(i_=0; i_<argc ;i_++) { 
		wait(&status[i_]); 
	}	
	return 0;
}
