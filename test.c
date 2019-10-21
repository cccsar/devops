
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define MY_PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define PERM_UMASK S_IRWXU & S_IRWXG & S_IRWXO

int main (int argc, char **argv) { 

	char prueba, otra, otra_mas;
	prueba = 'a'; 
	scanf("%c",&otra_mas); 
	printf("%d\n",prueba);
	printf("%d\n",otra_mas);

	return 0; 
}

