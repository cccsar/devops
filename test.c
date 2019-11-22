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


int main (int argc, char *argv[]) {
	FILE *fp ; 
	char* hola; 


	if ( !(fp = fopen(argv[1],"r"))  )
		perror("fopen");


	hola = (char*) malloc( sizeof(char) * 10);
	fscanf(fp,"%s",hola);

	printf("%s\n",hola);

	fclose(fp);

	return 0;
}
