
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv) { 

	/*
	struct stat st;

	if( stat(argv[1], &st) == -1)
		perror("stat");

	printf("%d\n",sizeof((long long)st.st_size));
	*/

	printf("%d\n",sizeof(S_IFSOCK));
	
	return 0; 
}

