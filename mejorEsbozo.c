
#include <stdio.h> 
#include <stdlib.h>
#include<sys/types.h> 
#include<dirent.h> 
#include <string.h> 
#include <unistd.h>

#define max(x,y) (x>y)? x: y; 	// esto puede estar malo	###
#define MY_LIMIT max(RLIMIT_FSIZE,SSIZE_MAX) //estas constantes pueden no ser conocidaas, verificar ###


void myCat(int fd_source, int fd_dest) { 
		
	char buffer[MY_LIMIT+1]; 

	while( read(fd_source, buffer, MY_LIMIT) != EOF) { 
		//verificar lectura y escritura apropiada
		//
		//utilizar desplazamiento %TAMANO_DEF para copiar metadata
		write(fd_dest, buffer, MY_LIMIT); 
	}
}

void fileCat(DIR *dir, char *dirname, int fd) { 

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
			//printf("%s\n",pathname); 

			if (current_ent->d_type == DT_DIR )  
			{ 
				if ( (ith_pointer = opendir(pathname)) == NULL )  	//abro directorio	
				{
					perror("opendir");
					return; 
				}

				fileCat(ith_pointer, pathname); //esta llamada cambia pathname, ergo el buffer
				closedir(ith_pointer); 					//cierro directorio
			}
			else if ( current_ent->d_type == DT_REG) 
			{
				int current_fd; 

				current_fd = open(pathname,O_RDONLY); 
				myCat(current_fd, fd);	
			}
				
			
			strcpy(pathname, pathname_buff);	//aqui recupero e lvalor de pathname
		}
	}
}

int main (int argc, char **argv) { 
	
	
	DIR *dir;
	struct dirent *entry; 
	char *local_path = (char*) malloc(256*sizeof(char));
	int fd, ith_fd,  i; //file descriptor for the file to be created
	struct stat *st;
	/* comandline goes like  fileCat name_dest args** */
	/*First assuming the commandline goes right */
	
	

	fd = open(argv[1], O_WRONLY || O_APPEND); 	//create file and receive file descriptor

	// necesito abrir el directorio actual para verificar que lo que proceso es un archivo o directorio?	
	// no, solo necesito un struct stat para consultar eso
	//
	// este for existe porque una llamada directa a fileCat recibe solo directorios
	// asi que reviso primero que tipo de archivo es 
	// 	si es un archivo regular ***en el directorio actual
	// 		lo concateno a mi arch_dest
	// 	si es un directorio, llamo a opendir
	for(i=2; i<argc; i++) { 
		ith_fd = open(argv[i], O_RDONLY); 	//Estoy asumiendo que lo que pasan es un nombre de archivo existente

		if( stat(ith_fd, st) != 0) 
		{
			fprintf(stderr,"error al leer estado\n");
			perror("stat");
			exit(-1);
		}

		if( (st->st_mode && S_IFMT) == S_IFREG ) 	//El argumento pasado es archivo regular 
		{
			myCat(ith_fd, fd);		
		}
		else if( (st->st_mode && S_IFMT) == S_IFDIR)   //El argumento pasado es directorio
								//falta ajuste para el resto de tipos de arhcivo
		{

			strcpy(local_path, "./"); 
			strcat(local_path, argv[i]); 

			if ( (dir=opendir(local_path)) == NULL ) 
			{ 
				fprintf(stderr,"error opening directory\n"); 
				perror("opendir"); 
			}

			fileCat(dir, argv[i], fd);  		//convendria que ajuste esto para que trabaje con fd
			closedir(dir); 
		}
			

	}
		
	exit(0);	
}

