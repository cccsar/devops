
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

#define MY_PERM S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH
#define SAVE_UNITS 16 

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
 * fd_dest: file descriptor of the file to write.
 * content_size: 
 * token_field_size:
 * tail_flag: 
 *
 */
void fillField(int fd_dest,int content_size, int token_field_size, int tail_flag) {
	
	int reminder, to_write_size, k;
	char buffer[token_field_size];

	/* here i calculate how much to stuff */
	reminder = token_field_size%content_size;

	if(reminder == 0 )
		to_write_size = (tail_flag)? content_size: token_field_size;
	else
	{
		/* This is added to separate head token stuffing from tail token stufifng */
		to_write_size =  (tail_flag)? reminder : token_field_size - reminder;
	}

	/* create the stuff string and append It to my fd */
	for (k=0; k<to_write_size; ++k)
		buffer[k] = STUFF_TOKEN;

	//printf("%d\n",k);
	writeToDest(fd_dest, buffer, to_write_size);
}


/* setHeadFields
 * ----------
 * Sets the header fields for files.
 *
 * state: state of the file whose attributes are being added to the archive.
 * fd_dest: file descriptor of my archive.
 * name: Name of the file being processed.
 *
 */
void setHeadFields(struct stat state, int fd_dest, char *name) {
						//Aun no verifico que lea todo lo que debe leer
	int len;

	/* append and stuff the name of the file */
	len = dprintf(fd_dest,"%s",name); 
	fillField(fd_dest, len, FNAME_LIMIT, FALSE);

	/* append and stuff the size of the file */
	len = dprintf(fd_dest,"%d",(int)state.st_size); 
	fillField(fd_dest, len, FSIZE_LIMIT, FALSE); 

	/* append and stuff the mode of the file */
	len = dprintf(fd_dest,"%ld",(unsigned long)state.st_mode);	
	fillField(fd_dest, len, FMODE_LIMIT, FALSE);
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
 * the file content. It does this recursively
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
			printf("%s\n",pathname); 

			/* If the current entry is a directory, set its header 
			 * fields, then open and call traverseDir recursively
			 */
			if (current_ent->d_type == DT_DIR )  
			{ 
				ith_pointer = opendir(pathname);
				if ( ith_pointer == NULL )  			//#a#d
				{
					perror("opendir");
					break; 
				}

				len = dprintf(fd,"%s",pathname); 		//###
				fillField(fd, len, FNAME_LIMIT, FALSE);
				
				traverseDir(ith_pointer, pathname, fd); //esta llamada cambia pathname, ergo el buffer

				closedir(ith_pointer); 				//#c#d
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
					perror("open");
					break;
				}

				struct stat current_file_status;

				if(stat(pathname,&current_file_status) == -1)
				{
					perror("stat");
					break;
				}

				setHeadFields(current_file_status,fd, pathname);
				fileWriter(current_fd, fd);	
				fillField(fd, SAVE_UNITS, current_file_status.st_size, TRUE);

				close(current_fd);				//#c#
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
	 

	fd = open(argv[1], O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, S_IRWXU | S_IRGRP); 
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
			fprintf(stderr, "error, input is ./out something.my tar files..\n");
			perror("open\n"); 
			exit(-1); 
		}

		if( stat(argv[i], &st) != 0) 					//verifico que el stat se guarde
		{
			fprintf(stderr,"error reading status\n");
			perror("stat");
			exit(-2);
		}

		
		printf("%s\n",argv[i]);

		if( (st.st_mode & S_IFMT) == S_IFREG ) 	//C1: El argumento pasado es archivo regular 
		{	
			/* Set propper head and tail for ith file in the cmd */
			setHeadFields(st,fd, argv[i]);
			fileWriter(ith_fd, fd);		
			fillField(fd, SAVE_UNITS, st.st_size, TRUE);

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
			int len;
			len = dprintf(fd,"%s",argv[i]); 
			fillField(fd, len, FNAME_LIMIT, FALSE);
			traverseDir(dir, argv[i], fd);  		//###convendria que ajuste esto para que trabaje con fd

			closedir(dir);						//#c#d
		}
			

	}

	close(fd);								//#c#
		
	exit(0);	
}


