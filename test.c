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

#define VSIZE 50

char** prueba(int tumama) { 
	char** eresmarico;

	eresmarico = (char**) malloc( sizeof(char*) * tumama );
	return eresmarico;
}
int main (int argc, char *argv[]) {
	char **hola; 

	hola = prueba(10); 
	sprintf(hola[0],"rolo de pu;sdlkfta");
	printf("gay %s\n",hola[0]);

	return 0;

}
