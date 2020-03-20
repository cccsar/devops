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

void simple_handler(int hola){ 
	printf("Senal %d\n",hola); 
}

int main (int argc, char **argv) { 

	void (*old_handler)(int); 
	printf("muere al Cc\n"); 

	sleep(2); 

	old_handler = signal(SIGINT, simple_handler); 
	printf("ya no\n"); 

	while(1); 
	signal(SIGINT, old_handler); 
	printf("ahora si\n"); 

	return 0; 
}
