
#include <stdio.h> 
#include <stdlib.h>
#include<sys/types.h> 
#include<dirent.h> 
#include <string.h> 


void dirTraverse(DIR *dir, char *dirname, char *name) { 

	struct dirent *current_ent; 
	DIR *ith_pointer;
	char path[256], pathname[256], pathname_buff[256];	

	strcpy(path,dirname); 

	while( (current_ent=readdir(dir)) != NULL ) { 

		if( strcmp(current_ent->d_name,".")!=0 && strcmp(current_ent->d_name,"..")!=0) 
		{
			int len; 			

			strcpy(pathname, path); 		//creo buffer para pathname antes de extenderlo
			len = strlen(pathname); 
			strcpy(pathname_buff, pathname); 

			if ( pathname[len-1] != '/' )
				strcat(pathname,"/"); 

			strcat(pathname, current_ent->d_name);	//modifico pathname

			if ( strcmp(name,current_ent->d_name) == 0 )  
				printf("%s\n",pathname); 

			if (current_ent->d_type == DT_DIR )  
			{ 
				if ( (ith_pointer = opendir(pathname)) == NULL )  	//abro directorio	
				{
					perror("opendir");
					return ;
				}
				
				dirTraverse(ith_pointer, pathname, name); //esta llamada cambia pathname, ergo el buffer
				closedir(ith_pointer); 					//cierro directorio
			}
			
			strcpy(pathname, pathname_buff);	//aqui recupero e lvalor de pathname
		}
	}
}

int main (int argc, char **argv) { 
	
	
	DIR *dir;
	struct dirent *entry; 
	char *dir_path, *search_name; 
       	dir_path = (char*) malloc(256*sizeof(char));
	search_name = (char*) malloc(256*sizeof(char));	

	if ( argc < 2 ) 
	{
		fprintf(stderr, "Not enough arguments, 2 needed"); 
		exit(-1);
	}

	strcat(dir_path, argv[1]); 
	strcat(search_name, argv[2]); 

	if ( (dir=opendir(argv[1])) == NULL ) 
	{
		fprintf(stderr,"error opening directory\n"); 
		perror("opendir"); 
	}

	dirTraverse(dir, dir_path, search_name); 
	closedir(dir); 
		
	exit(0);	
}

