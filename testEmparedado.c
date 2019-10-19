// Main

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MY_PERM S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH
#define SAVE_UNITS 16 

#define FNAME_LIMIT 256
#define FMODE_LIMIT 10
#define FSIZE_LIMIT 20

#define STUFF_TOKEN '#'

#define TRUE 1
#define FALSE 0


void appendIt(int fd_dest, char* buffer, int to_rw) {	//It is only appended if the file is opened
							//O_WRONLY | O_APPEND 
	int read; 
	
	/* secure writting */
	read = 0;
	while(to_rw>read)
		read+=write(fd_dest, buffer+read,to_rw-read);

}

void stuffIt(int fd_dest,int content_size, int token_field_size, int tail_flag) {
	
	int reminder, to_write_size, k;
	char buffer[token_field_size];

	/* here i calculate how much to stuff */
	reminder = token_field_size%content_size;

	if(reminder == 0 )
		to_write_size= token_field_size;
	else
	{
		/* This is added to separate head token stuffing from tail token stufifng */
		to_write_size =  (tail_flag)? reminder : token_field_size - reminder;
	}

	/* create the stuff string and append It to my fd */
	for (k=0; k<to_write_size; ++k)
		buffer[k] = STUFF_TOKEN;

	printf("%d\n",k);
	appendIt(fd_dest, buffer, to_write_size);
}

void stuffHeadFields(struct stat state, int fd_dest) {

	int len;

	len = dprintf(fd_dest,"%d",(int)state.st_size); 
	stuffIt(fd_dest, len, FSIZE_LIMIT, FALSE); 

	len = dprintf(fd_dest,"%ld",(unsigned long)state.st_mode);	
	stuffIt(fd_dest, len, FMODE_LIMIT, FALSE);
}


int main (int argc, char **argv) { 

	char buff[256], stuff_buff[16]; 
	struct stat estado;
	int len, len1, fdf, fds, i;
	len = 5;

	fdf = open(argv[1], O_RDONLY);
	if(fdf == -1)
	{
		perror("open");
		exit(-1);
	}

	fds = open(argv[2], O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, MY_PERM);	
	if(fds == -1)
	{
		perror("open");
		exit(-1);
	}

	if( stat(argv[1], &estado) == -1)
	{
		perror("stat");
		exit(-2);
	}


	int n_written;
	n_written = dprintf(fds,"%s",argv[1]);		//estoy asumiendo que lee correctamente
	
	/* anado cabecera */
	stuffIt(fds, n_written, FNAME_LIMIT, FALSE);
	stuffHeadFields(estado, fds);


	/* hago cat de argv[1] y redirecciono a argv[2]  */
	while ( (len = read(fdf, buff, len)) != 0 ) {
		
		len1 = 0;
		while(len1 < len) 
			len1 += write(fds, buff+len1, len-len1);
	}

	/* anado cola */
	stuffIt(fds, SAVE_UNITS, estado.st_size, TRUE);


	/* cierro los archivos abiertos */
	close(fdf);
	close(fds);


	return 0; 
}

