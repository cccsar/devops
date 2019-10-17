
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>

#define LOCAL_LIMIT 2147479552 


void myCat(int fd_source, int fd_dest) { 
		
	char buffer[LOCAL_LIMIT-1]; 

	while( read(fd_source, buffer, LOCAL_LIMIT) != EOF) { 
		//verificar lectura y escritura apropiada
		//
		//utilizar desplazamiento %TAMANO_DEF para copiar metadata
		write(fd_dest, buffer, LOCAL_LIMIT); 
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
			printf("%s\n",pathname); 

			if (current_ent->d_type == DT_DIR )  
			{ 
				if ( (ith_pointer = opendir(pathname)) == NULL )  	//verifico que abra el dir
				{
					perror("opendir");
					return; 
				}

				fileCat(ith_pointer, pathname, fd); //esta llamada cambia pathname, ergo el buffer
				closedir(ith_pointer); 					//cierro directorio
			}
			else if ( current_ent->d_type == DT_REG)			//###Leer man de readdir() 
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
	struct stat st;
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

		if (ith_fd = open(argv[i], O_RDONLY) == -1)  			// verifico que el archivo se abra
		{
			printf("%s\n",argv[i]);
			fprintf(stderr, "error al abrir archivo \n");
			perror("open\n"); 
			exit(-1); 
		}

		if( fstat(ith_fd, &st) != 0) 					//verifico que el stat se guarde
		{
			fprintf(stderr,"error al leer estado\n");
			perror("stat");
			exit(-2);
		}

		if( (st.st_mode && S_IFMT) == S_IFREG ) 	//C1: El argumento pasado es archivo regular 
		{
			myCat(ith_fd, fd);		
		}
		else if( (st.st_mode && S_IFMT) == S_IFDIR)   //C2: El argumento pasado es directorio
		{

			strcpy(local_path, "./"); 
			strcat(local_path, argv[i]); 

			if ( (dir=opendir(local_path)) == NULL ) 		//verifico que el dir abra
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

