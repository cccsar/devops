#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <signal.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main (int argc, char **argv) { 
	alarm(6); 
	printf("eternal\n");
	alarm(3); 
	while(1);
	printf("algo\n");

	return 0; 
}

