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
#define MAX_PS 10

typedef int* marico; 

int main (int argc, char *argv[]) {


	marico hola;  

	printf("Prueba %p\n",hola);
	return 0;
}
