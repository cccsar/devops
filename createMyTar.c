
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
#define FMODE_LIMIT 10 + 1
#define FSIZE_LIMIT 20 + 1

#define STUFF_TOKEN ''

#define TRUE 1
#define FALSE 0


/* writeToDest
 * ----------
 * Writes a string "text" to the file descriptor represented by fd_dest. Since 
 * we are creating a .mytar, it is assumed that fd_dest is asociated with a
 * file opened in append mode. 
 * 
 * 	fd_dest: An integer representing a file descriptor to the file to write.
 * 	text: String containing what will be written.
 * 	size: Size of the string to write.
 *
 */
void writeToDest(int fd_dest, char* text, int size) {	
						
	int read_size ; 
	
	/* secure writting */
	read_size = 0;
	while(size > read_size)
		read_size+=write(fd_dest, text+read_size,size-read_size);
}


/* fillField
 * ----------
 * This function calculates the remaining space after inserting a variable
 * size field, and padds it with a special character  == '\2' (by writting) until fitting 
 * a predefined fixed length field. 
 *
 * After that it calls writeToDest to put the field into the .mytar file
 *
 * fixed length fields are : FNAME_LIMIT, FMODE_LIMIT, FSIZE_LIMIT
 *
 *
 * 	fd_dest: file descriptor of the file to write.
 *	content_size:  Size of the field name to write 
 * 	token_field_size:
 */
void fillField(int fd_dest,int content_size, int token_field_size) {
	
	int k, diff, reminder, to_write_size, preferred_size;
	
	/* This is added to adjust the buffer for writting depending on the field being set */
	char buffer[token_field_size];

	/* here I calculate how much to fill to keep constant size fields */
	if (content_size < token_field_size) 
		diff = token_field_size - content_size;
	else  
		diff = content_size - token_field_size;

	if(diff == 0)
		to_write_size = token_field_size;
	else
		to_write_size = diff;

	printf("size of padding: %d\n",diff); 

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
 * 	state: state of the file whose attributes are being added to the archive.
 * 	fd_dest: file descriptor of my archive.
 * 	name: Name of the file being processed.
 *
 */
void setHeadFields(int fd_dest, struct stat state, char *name, int is_dir) {
						//Aun no verifico que lea todo lo que debe leer
	/* There could be more fields added or removed at will. This is 
	 * for now, just a test function */
	int len;
	//char space ; //previous_imp
	//space = '@'; //previous_imp


	/* append and fill the NAME field of the file */
	len = dprintf(fd_dest,"%s",name); 
	//len += dprintf(fd_dest,"%c",space); 	//previous_imp 
	/* If name limit exceeds the padding, complete properly */
	if(len >= FNAME_LIMIT)  
	{
		int padding; 
		padding = (len/FNAME_LIMIT + 1)*FNAME_LIMIT ; 
		//printf("new padding is: %d\n",padding); //#dbg#
		fillField(fd_dest, len, padding); 
		
	}
	else  
		fillField(fd_dest, len, FNAME_LIMIT);

	/* append and fill the MODE field of the file */
	len = dprintf(fd_dest,"%ld",(unsigned long)state.st_mode);	
	//len += dprintf(fd_dest,"%c",space); //previous_imp
	fillField(fd_dest, len, FMODE_LIMIT);
	
	if(!is_dir)
       	{
		/* append and stuff the SIZE of the file */
		len = dprintf(fd_dest,"%d",(int)state.st_size); 
		//len += dprintf(fd_dest,"%c",space);
		fillField(fd_dest, len, FSIZE_LIMIT); 

	}
}



/* fileWriter
 * ----------
 * Writes from a file to another by using its file descriptors.
 *
 * 	fd_source: file descriptor of the file to write from.
 * 	fd_dest: file descriptor of the file to write.
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
 * It does this by, first, avoiding "." and ".." directory entries and 
 * from there it goes by each directory entry, processing it fields (name, permissions, 
 * and size only for regfiles), and copying directories and regfile metadata to .mytar
 * as well as regfile content.
 *
 * 	dir: Directory pointer to the dir to traverse.
 * 	dirname: name of the directory to traverse.
 * 	fd: file descriptor of the archive file.
 *
 */
void traverseDir(DIR *dir, char *dirname, int fd) { 

	int current_fd; 
	struct dirent *current_ent; 
	DIR *ith_pointer;
	char path[1000], pathname[1000], pathname_buff[1000];	

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
			printf("pathname_size: %d\n",len);

			if ( pathname[len-1] != '/' )
				strcat(pathname,"/"); 

			strcat(pathname, current_ent->d_name);	//modifico pathname
			printf("archiving %s\n",pathname); 

			struct stat current_file_status; 

			if(stat(pathname,&current_file_status) == -1)
				perror("stat");

			/* If the current entry is a directory, set its header 
			 * fields, then open and call traverseDir recursively */
			if (current_ent->d_type == DT_DIR )  
			{ 
				ith_pointer = opendir(pathname);
				if ( ith_pointer == NULL )  			//#a#d
				{
					fprintf(stderr,"error opening %s\n",pathname);
					perror("opendir");
				}
				else {

					/* This adds a space at the end of the name part of the field 
					 * in order to recognize termination */
					setHeadFields(fd, current_file_status, pathname, TRUE);
					
					/* This this recursive call changes pathname, 
					 * therefore we need a buffer to save it temporarily */
					traverseDir(ith_pointer, pathname, fd);

					closedir(ith_pointer); 				//#c#d
				}
			}
			/* If the current entry is a regular file, set its header 
			 * fields */
			else if ( current_ent->d_type == DT_REG)			//###Leer man de readdir() 
			{
				current_fd = open(pathname,O_RDONLY); 		//#a#

				if(current_fd == -1) 
				{
					fprintf(stderr,"error opening %s\n",pathname);
					perror("open");
				}
				else { 
					setHeadFields(fd, current_file_status, pathname, FALSE);
					fileWriter(current_fd, fd); 

					close(current_fd);				//#c#
				}
			}
				
			/* Here the before-dir-traverse value of pathname is 
			 * recovered from buffer */
			strcpy(pathname, pathname_buff);	
		}
	}

}


/* createMyTar
 * --------------
 * Used to create the .mytar file. It beggins setting up the 
 * process creation mask and then it creates the .mytar file.
 *
 * After that it parses every file in the commandline first finding out
 * wether it exists, setting its head field, and then:
 * 	if it is a directory: open it -> traversing it -> on termination it is
 * 		closed
 * 	if it is a regular file: open it -> write it to mytar -> 
 * 		on termination it is closed
 *
 * Requires: 
 * 	access to argv
 *
 */
int main (int argc, char **argv) {  		//File create
	
	
	DIR *dir;
	struct dirent *entry; 
	char *local_path = (char*) malloc(1000*sizeof(char));
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
		
		/* regular file case */ 
		if( (st.st_mode & S_IFMT) == S_IFREG ) 	
		{	
			/* Set propper head for ith file in the */
			setHeadFields(fd ,st, argv[i], FALSE);
			fileWriter(ith_fd, fd);

			close(ith_fd);			//#c#f
		}
		/* directory case */ 
		else if( (st.st_mode & S_IFMT) == S_IFDIR)   
		{

			strcpy(local_path, "./"); 
			strcat(local_path, argv[i]); 

			dir = opendir(local_path);				//#a#d
			if (dir == NULL) 		
			{ 
				fprintf(stderr,"error opening directory\n"); 
				perror("opendir"); 
			}

			/* set proper head fields for directory */
			setHeadFields(fd, st, argv[i], TRUE);
			traverseDir(dir, argv[i], fd);  		//###convendria que ajuste esto para que trabaje con fd

			closedir(dir);						//#c#d
		}
			

	}

	close(fd);								//#c#
		
	exit(0);	
}


