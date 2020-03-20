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
	
	void (*marico_manejador)(); 

	printf("muero al Cc\n"); 
	sleep(3); 
	marico_manejador = signal(SIGINT, SIG_IGN); 
	printf("ya no \n"); 
	sleep(3); 

	signal(SIGINT, marico_manejador); 
	printf("Ahora si\n"); 

	return 0; 
}
