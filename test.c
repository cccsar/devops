
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

	int fd, len, prev_mask;
	struct stat st;

	prev_mask = umask(0000);
	fd = open(argv[1], O_CREAT, MY_PERM);
	fstat(fd, &st);

	close(fd);

	printf("current umask: %o\tmy_perm: %o\n",0000,MY_PERM);
	printf("resulting mask %o\n",MY_PERM & ~0000);


	return 0; 
}

