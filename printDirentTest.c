
#include <stdio.h> 
#include <stdlib.h>
#include<sys/types.h> 
#include<dirent.h> 

int main (int argc, char **argv) { 
	/* ejemplo lectura de directorio */	
	
	DIR *dir;
	struct dirent *dir_ent; 
	
	if ( (dir=opendir(argv[1])) == NULL ) 
	{
		fprintf(stderr,"error opening directory\n"); 
		perror("opendir"); 
		exit(-1);
	}

	while( (dir_ent=readdir(dir)) != NULL ) { 
		printf("nombre: %s\n",dir_ent->d_name);
		printf("inodo: %ld\n",dir_ent->d_ino);
		printf("offset: %ld\n",dir_ent->d_off);
		printf("record lenght: %d\n",dir_ent->d_reclen);
		printf("type of file: %d\n",dir_ent->d_type);
		printf("\n");
	}
	
	closedir(dir); 
	exit(0);	
}

