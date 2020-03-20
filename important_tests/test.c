#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <malloc.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define SOME_MAX 20
#define NAME "ls"
#define MAX_DIGITS 20

#define NEW_SIZE 500

typedef struct packt { 

	void **objects; 
} packet;

int main (int argc, char *argv[]) {
	int i_;
	char * prueba; 
	FILE *file; 

	prueba = (char *) malloc( sizeof(char) * 20 );
	file = fopen(argv[1], "r"); 	

	while ( fscanf(file, "%s",prueba) != EOF )  
		printf("word: %s\tlength: %d\n", prueba,strlen(prueba) );


	return 0;
}
