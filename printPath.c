
#include <stdio.h> 
#include <stdlib.h>
#include<sys/types.h> 
#include<dirent.h> 
#include <string.h> 


void dirTraverse(DIR *dir, char *dirname) { 

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
			printf("%s\n",pathname); 

			if (current_ent->d_type == DT_DIR )  
			{ 
				if ( (ith_pointer = opendir(pathname)) == NULL )  	//abro directorio	
				{
					perror("opendir");
					return; 
				}

				dirTraverse(ith_pointer, pathname); //esta llamada cambia pathname, ergo el buffer
				closedir(ith_pointer); 					//cierro directorio
			}
			
			strcpy(pathname, pathname_buff);	//aqui recupero e lvalor de pathname
		}
	}
}

int main (int argc, char **argv) { 
	
	
	DIR *dir;
	struct dirent *entry; 
	char *local_path = (char*) malloc(256*sizeof(char));

	strcpy(local_path, "./"); 
	strcat(local_path, argv[1]); 

	if ( (dir=opendir(local_path)) == NULL ) 
	{
		fprintf(stderr,"error opening directory\n"); 
		perror("opendir"); 
	}

	dirTraverse(dir, argv[1]); 
	closedir(dir); 
		
	exit(0);	
}

