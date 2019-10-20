#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define FNAME_LIMIT 256 //this is up to 256 char*
#define FMODE_LIMIT 10  //this is int 
#define FSIZE_LIMIT 20 	//this is long int
#define MAX_RW 16

#define MY_PERM S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH
#define CREATION_MODE O_WRONLY | O_TRUNC | O_CREAT

#define TRUE 1
#define FALSE 0

/* fileWriter
 * --------------
 *
 *
 */
void fileWriter(int fd_source, int fd_dest, int total) { 
		
	char buffer[MAX_RW], header[MAX_RW];
	int just_read, to_write, write_count;
	struct stat st_dest;

	just_read = 1;
	write_count = 0; 
	
	while( (just_read = read(fd_source, buffer, just_read)) != 0 && write_count < total){
	
		to_write = 0;
		while(just_read > to_write) {

			to_write += write(fd_dest, buffer+to_write, just_read - to_write);
		}
		write_count += just_read;
	}

}


/* getFieldSize
 * --------------
 *
 *
 */
off_t getFieldSize(int fd_orig, int roof,int floor) {
	char char_read[1];
	off_t current_offset, required_size, final_offset;
	ssize_t just_read ;
	


	current_offset = lseek(fd_orig, roof, SEEK_SET);
	fprintf(stdout,"current offset: %ld\n",current_offset); //#dbg# 


	/* Move file offset from roof till the first appareance of the @ 
	 * character */
	while(TRUE) {
		just_read = read(fd_orig, char_read, 1);
		if (char_read[0] == '@') 
		{
			current_offset = lseek(fd_orig, -1, SEEK_CUR);
			break;
		}
		else 
			current_offset = lseek(fd_orig, -2, SEEK_CUR);
	}

	//fprintf(stdout,"size of field %d\n",current_offset); #dbg#
	required_size = current_offset-floor;
	
	/* relocate the offset in the beggining. This could be avoided */
	final_offset = lseek(fd_orig,floor,SEEK_SET);
	
	//fprintf(stdout,"final offset %ld\n",final_offset); #dbg#
	

	return required_size;
}

char *getField(int fd, int roof, int floor) {
	char* name;
	int just_read, final_offset;
	off_t field_length;

	field_length = getFieldSize(fd, roof, floor);
	name = (char*) malloc(field_length);
	just_read = read(fd, name, field_length);

	final_offset = lseek(fd, roof, SEEK_SET);
	//fprintf(stdout,"\t\tcurrent offset: %d\n",final_offset);	#dbg#

	return name;
}


int main (int argc, char **argv) { 
	
	int fd_s, ith_roof, ith_floor, turn;
	long stop;
	char *file_name, *fmode, *fsize;
	mode_t file_mode;
	off_t file_size;
	struct stat mytar_state;

	ith_floor = ith_roof = 0;


	/*ARGV[1] is source file, and contains description for destination files*/

	if ( (fd_s = open(argv[1],O_RDONLY)) == -1) { 
		printf("eres marico\n");
		perror("open");
	}

	if ( stat(argv[1], &mytar_state) == -1) 
		perror("stat");

	stop = mytar_state.st_size;
	fprintf(stdout,".mytar total size: %ld\n",stop);
	

	while( ith_roof != stop ) {
		/* All of this is possible thanks to offset updating 
		 * to begin with, ith_floor and ith_roof represent, respectively,
		 * the symbolic beggining of next-to-process field, and the simbolic
		 * limit of next to process field.
		 *
		 * As a field is parsed, the limits are updated, and when a file is written,
		 * they need to be coincident, hence the +=FSIZE_LIMIT in ith_floor. (190).
		 *
		 */

		ith_roof +=  FNAME_LIMIT;

		/* Get both file name and mode */
		file_name = getField(fd_s, ith_roof, ith_floor) ;

		/* update mytar file offset */
		ith_roof += FMODE_LIMIT;
		ith_floor += FNAME_LIMIT;

		fmode = getField(fd_s, ith_roof, ith_floor);
		file_mode = (mode_t) atol(fmode);

		fprintf(stdout,"file name: %s\n", file_name);		//#dbg#
		fprintf(stdout,"file mode: %d\n",file_mode);	//#dbg#


		/* actions depending on the type of file */
		if ( (file_mode & S_IFMT) == S_IFDIR ) 
		{
			
			struct stat test_state;
			/*
			ith_fd = open(file_name, O_CREAT | O_DIRECTORY);
			if (ith_fd == -1) 
				perror("open");
			*/
			fprintf(stdout,"file type: DIRECTORY\n");

			if( stat(file_name,&test_state) == -1 ) {
			
				if( mkdir(file_name, file_mode) == -1)
					perror("mkdir");
			}

			ith_floor += FMODE_LIMIT ;
			
		}
		else if ( (file_mode & S_IFMT) == S_IFREG) {
			int ith_fd;
			
			fprintf(stdout,"file type: REGULAR FILE\n");
			char *fsize;
			long file_size;

			/* update mytar file offset */
			ith_roof += FSIZE_LIMIT;
			ith_floor += FMODE_LIMIT;

			/* store file size */
			fsize = getField(fd_s, ith_roof, ith_floor) ;
			file_size = (unsigned long) atol(fsize);

			fprintf(stdout,"file size: %ld\n",file_size);

			ith_fd = open(file_name, CREATION_MODE , file_mode);
			if( ith_fd == -1) 
			{
				printf("arriba\n");
				perror("open");
			}
			else {

				fprintf(stdout,"file %s,created.\nAdding content...\n",file_name);
			
				fileWriter(fd_s, ith_fd, file_size);

				/* update mytar file offset */
				ith_roof += file_size;
				ith_floor += file_size+FSIZE_LIMIT;

				close(ith_fd);
			}
		}
		printf("\n");
	}	

	/*close source file descriptor */
	close(fd_s);


	return 0; 
}


