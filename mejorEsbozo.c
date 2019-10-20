
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define MAX_RW 16

#define MY_PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH //this is probably optional ###

#define FNAME_LIMIT 256
#define FMODE_LIMIT 10
#define FSIZE_LIMIT 20 

#define STUFF_TOKEN '#'

#define TRUE 1
#define FALSE 0


/* writeToDest
 * ----------
 * Writes a string "text" to the file descriptor represented by fd_dest 
 * 
 * fd_dest: An integer representing a file descriptor to the file to write.
 * text: String containing what will be written.
 * size: Size of the string to write.
 *
 */
void writeToDest(int fd_dest, char* text, int size) {	//It is only appended if the file is opened
							//O_WRONLY | O_APPEND 
	int read_size ; 
	
	/* secure writting */
	read_size = 0;
	while(size > read_size)
		read_size+=write(fd_dest, text+read_size,size-read_size);
}


/* fillField
 * ----------
 * This function calculates the remaining space after inserting a variable
 * size field, and padds it with a special character (by writting) until fitting a predefined
 * fixed length field.
 *
 * tail_flag == TRUE: Ill be adding the tail, hence concern about reminder and quotient
 * else: Ill be adding header fields, hence i'll only concern about diff
 *
 * fd_dest: file descriptor of the file to write.
 * content_size: 
 * token_field_size:
 * tail_flag: 
 *
 */
void fillField(int fd_dest,int content_size, int token_field_size) {
	
	int k, quot, diff, reminder, to_write_size, preferred_size;
	
	/* This is added to adjust the buffer for writting depending on the field being set */
	char buffer[token_field_size];

	/* here i calculate how much to stuff */
	diff = token_field_size - content_size;

	if(diff == 0)
		to_write_size = token_field_size;
	else
		to_write_size = diff;

	/* create the stuff string and append It to my fd */
	for (k=0; k<to_write_size; ++k)
		buffer[k] = STUFF_TOKEN;

	//printf("%d\n",k);	//#dbg#
	writeToDest(fd_dest, buffer, to_write_size);
}


/* setHeadFields
 * ----------
 * Sets the header fields for files. This fields are name, mode and 
 * only for regular files, the size.
 *
 * state: state of the file whose attributes are being added to the archive.
 * fd_dest: file descriptor of my archive.
 * name: Name of the file being processed.
 *
 */
void setHeadFields(struct stat state, int fd_dest, char *name, int is_dir) {
						//Aun no verifico que lea todo lo que debe leer
	/* There could be more fields added or removed at will. This is 
	 * for now, just a test function */
	int len;
	char space ;

	space = '@';


	/* append and stuff the NAME of the file */
	len = dprintf(fd_dest,"%s",name); 
	len += dprintf(fd_dest,"%c",space);
	fillField(fd_dest, len, FNAME_LIMIT);

	/* append and stuff the MODE of the file */
	len = dprintf(fd_dest,"%ld",(unsigned long)state.st_mode);	
	len += dprintf(fd_dest,"%c",space);
	fillField(fd_dest, len, FMODE_LIMIT);
	
	if(!is_dir)
       	{
		/* append and stuff the SIZE of the file */
		len = dprintf(fd_dest,"%d",(int)state.st_size); 
		len += dprintf(fd_dest,"%c",space);
		fillField(fd_dest, len, FSIZE_LIMIT); 

	}
}



/* fileWriter
 * ----------
 * Writes from a file to another by using its file descriptors.
 *
 * fd_source: file descriptor of the file to write from.
 * fd_dest: file descriptor of the file to write.
 *
 */
void fileWriter(int fd_source, int fd_dest) { 
		
	char buffer[MAX_RW], header[MAX_RW];
	int just_read, to_write;
	struct stat st_dest;

	just_read = MAX_RW;
	
	while( (just_read = read(fd_source, buffer, just_read)) != 0) {
	
		to_write = 0;
		while(just_read > to_write) 
			to_write += write(fd_dest, buffer+to_write, just_read - to_write);
	}



}


/* traverseDir
 * ----------
 * Used to traverse a directory tree and write file fields into the archive, along with
 * the file content. It does this recursively, in a similar way to a dfs graph traverse.
 *
 * dir: Directory pointer to the dir to traverse.
 * dirname: name of the directory to traverse.
 * fd: file descriptor of the archive file.
 *
 */
void traverseDir(DIR *dir, char *dirname, int fd) { 

	struct dirent *current_ent; 
	DIR *ith_pointer;
	char path[256], pathname[256], pathname_buff[256];	

	strcpy(path,dirname); 

	while( (current_ent=readdir(dir)) != NULL ) { 

		if( strcmp(current_ent->d_name,".")!=0 && strcmp(current_ent->d_name,"..")!=0) 
		{
			int len; 
			
			/* Guardo el nombre del path en una variable temporal,
			 * para preservarlo tras llamadas recursivas 
			 */
			strcpy(pathname, path); 		
			len = strlen(pathname); 
			strcpy(pathname_buff, pathname); 

			if ( pathname[len-1] != '/' )
				strcat(pathname,"/"); 

			strcat(pathname, current_ent->d_name);	//modifico pathname
			printf("archiving %s\n",pathname); 

			struct stat current_file_status; 

			if(stat(pathname,&current_file_status) == -1)
				perror("stat");

			/* If the current entry is a directory, set its header 
			 * fields, then open and call traverseDir recursively
			 */
			if (current_ent->d_type == DT_DIR )  
			{ 
				ith_pointer = opendir(pathname);
				if ( ith_pointer == NULL )  			//#a#d
				{
					fprintf(stderr,"error opening %s\n",pathname);
					perror("opendir");
				}
				else {

					/* This adds a space at the end of the name part of the field */
					/* in order to recognize termination */
					setHeadFields(current_file_status, fd, pathname, TRUE);
					traverseDir(ith_pointer, pathname, fd); //esta llamada cambia pathname, ergo el buffer

					closedir(ith_pointer); 				//#c#d
				}
			}
			/* If the current entry is a regular file, set its header
			 * fields
			 */
			else if ( current_ent->d_type == DT_REG)			//###Leer man de readdir() 
			{
				int current_fd; 

				current_fd = open(pathname,O_RDONLY); 		//#a#

				if(current_fd == -1) 
				{
					fprintf(stderr,"error opening %s\n",pathname);
					perror("open");
				}
				else { 
					setHeadFields(current_file_status, fd, pathname, FALSE);
					fileWriter(current_fd, fd);	

					close(current_fd);				//#c#
				}
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
	/* comandline goes like  traverseDir name_dest args** */
	/*First assuming the commandline goes right */
	 

	umask(0000); 				//### Probablemente quiera cambiarla cuando vaya a crear
						//mejor dejar que open(..O_CREATE) haga el set de los permisos
						//la umask sera la del usuario
	fd = open(argv[1], O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, MY_PERM);
	if (fd == -1)
	{
		fprintf(stderr, "error opening directory\n");
		perror("open\n"); 
		exit(-1); 
	}


	for(i=2; i<argc; i++) { 

		ith_fd = open(argv[i], O_RDONLY);	
		if (ith_fd == -1) 						//#a#	
		{
			fprintf(stderr,"error opening %s\n",argv[i]);
			perror("open"); 
		}

		if( stat(argv[i], &st) != 0) 					//verifico que el stat se guarde
		{
			perror("stat");
		}

		
		printf("archiving %s\n",argv[i]);

		if( (st.st_mode & S_IFMT) == S_IFREG ) 	//C1: El argumento pasado es archivo regular 
		{	
			/* Set propper head and tail for ith file in the cmd */
			setHeadFields(st, fd, argv[i], FALSE);
			fileWriter(ith_fd, fd);		

			close(ith_fd);				//cierro despues de copiar
		}
		else if( (st.st_mode & S_IFMT) == S_IFDIR)   //C2: El argumento pasado es directorio
		{

			strcpy(local_path, "./"); 
			strcat(local_path, argv[i]); 

			dir = opendir(local_path);				//#a#d
			if (dir == NULL) 		
			{ 
				fprintf(stderr,"error opening directory\n"); 
				perror("opendir"); 
			}

			setHeadFields(st, fd, argv[i], TRUE);
			traverseDir(dir, argv[i], fd);  		//###convendria que ajuste esto para que trabaje con fd

			closedir(dir);						//#c#d
		}
			

	}

	close(fd);								//#c#
		
	exit(0);	
}


