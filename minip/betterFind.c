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
#define FALSE 0
#define MAX_PATHNAME 5000


void traverseDir(DIR *dir, char *dirname, char *lookup) { 

	int len; 
	char path[MAX_PATHNAME], pathname[MAX_PATHNAME]; 
	DIR *curr_dir;
	struct dirent *current_ent; 
	struct stat current_st; 

	strcpy(path, dirname); 

	while( (current_ent=readdir(dir)) != NULL ) { 

		if( strcmp(current_ent->d_name,".")!=0 && strcmp(current_ent->d_name,"..")!=0) 
		{
			strcpy(pathname, path); 		
			
			len = strlen( pathname ); 

			if (pathname[len-1] != '/')
				strcat(pathname,"/"); 

			/* Extiendo el pathname para que incluya el nombre de la 
			 * entrada actual */
			strcat(pathname, current_ent->d_name);	

			if(lstat(pathname, &current_st) == -1)
				perror("stat");
			
			/* Compara la entrada actual con el nombre buscado, 
			 * de ser iguales lo indica */ 
			printf("%s\n",pathname); 
			if( strcmp(current_ent->d_name,lookup) == 0) 
				printf("\tMATCH: %s\n",current_ent->d_name); 

			else if ( S_ISDIR(current_st.st_mode) ) {
			  	curr_dir = opendir(pathname); 

			 	traverseDir(curr_dir, pathname, lookup); 

				closedir(curr_dir);
			}

		}
	}

}

int main (int argc, char **argv) { 

	DIR *dir; 
	struct stat d_stat; 	

	if ( stat(".", &d_stat) == -1 )
		perror("stat"); 

	/* Verificar que es un directorio antes de recorrer */
	if( !S_ISDIR(d_stat.st_mode) ) {
		fprintf(stderr,"Not a directory\n");
		exit(-1);
	}
	else { 
		dir = opendir("."); 
		traverseDir(dir, ".", argv[1]); 
	}

	return 0; 
}

