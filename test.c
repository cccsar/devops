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

	hola = (char**) malloc( sizeof(char*) * 10);
	/*hola[0] = (char*) malloc( sizeof(char) * 10);*/
	/*strcpy(hola[0], (char*) NULL);*/
	hola[0] = (char*) NULL; 

	if (hola[0] == NULL) 
		printf("eres marico\n");
	return 0;

}
