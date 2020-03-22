#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <ctype.h> 
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>
#include <signal.h> 

#define TRUE 1
#define FALSE 0

#define BUFFS 512
#define STDIN 0


//Sample implementation of secure read/write using arithmetic

int main(int argc, char *argv[])
{
	int  fd, rd, quot, rem, acum, to_read, guard;
	struct stat check;
	char buff[BUFFS+1]; 

	if (argc <= 1){ 
		fprintf(stderr, "error\n"); 
		exit(-1); 	
	}

	fd = open(argv[1],O_RDWR); 
	if ( fd == -1) {
		perror("open"); 
		exit(-1); 
	}
  
	if ( stat(argv[1], &check) == -1){
		perror("stat: ");
		exit(-2); 
	}

	acum = 0;

	if ( check.st_size > BUFFS) { 
		quot = check.st_size / BUFFS; 
		rem = check.st_size % BUFFS; 	

		to_read = BUFFS;
		guard = TRUE; 
	}	
	else 
		to_read = check.st_size; 

	int cnt = 0, wt; 

	while( acum < check.st_size ) { 
		if ( cnt == quot && guard )
			to_read = rem; 

		rd = read(fd, buff, to_read); 
		while( rd < to_read )
			rd += read(fd, buff, to_read - rd ); 

		wt = write(1, buff, rd); 
		while ( wt < rd)
		       wt += write(1, buff, rd - wt);	

		if (guard)
			cnt +=1 ;

		acum += rd; 
	}

	close(fd); 

	return 0; 
}
