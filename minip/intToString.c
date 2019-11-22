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

#define SOME_MAX 20
#define NAME "ls"
#define MAX_DIGITS 20


int intToString(char* arr, int a, int *i) { 

	if( a/10 != 0 )  {
		*i = intToString(arr, a/10, i) ;
		arr[*i] = a%(10) + 48; 
	}
	else   
		arr[*i] = a + 48;

	*i += 1;

	return *i; 
}

int main (int argc, char *argv[]) {
	char *prueba; 
	int i_, size, perico;

	perico = 0;
	prueba = (char *) malloc( sizeof(char)*MAX_DIGITS );

	size = intToString(prueba, atoi(argv[1]), &perico);

	for(i_=0; i_<size+1 ; i_++) 
		printf("%c ",prueba[i_]);	

	printf("\n");	

	return 0;
}
