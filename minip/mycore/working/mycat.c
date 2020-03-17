#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define BUFFSIZE 1024
#define STDOUT 1
#define SETSIZE 4

//implement -n -E -b -s
//	n: prepend line count to each line (overrides s)
//	E: show ends at the end of each line
//	b: number only non-blank  
//	s: suppress repeated blank consecutive lines

#define ENDL 1 
#define NUMBERBLANK 1
#define NUMBER 2
#define SQUEEZE 3

#define PREP 0
#define APD 1
#define REP 2
//parser searches argv[i_][0] == '-' and searches for letters belonging to the set
//	if not a valid letter exit with error
//	if a valid letter activate flag in a boolean manner(?)

int flags[SETSIZE]; 


int parse(int argc, char **argv){
	int i_, j_ , nflags;

	nflags = 0 ;
	for(i_=1; i_<argc ; i_++) {

		if ( argv[i_][0] == '-' )  { 

			for(j_=1; j_<strlen( argv[i_] ) ; j_++) { 
				switch(argv[i_][j_])  {
					case 'E':
						flags[0] = 1 ;
						nflags += 1; 
						break; 
					case 'b': 
						flags[1] = 1 ;
						nflags += 1; 
						break; 
					case 'n': 
						flags[2] = 1 ;
						nflags += 1; 
						break; 
					case 's': 
						flags[3] = 1 ;
						nflags += 1; 
						break; 
					default: 
						fprintf(stderr,"Not a valid flag\n"); 
						return -1 ;
				}

			}
		}
	}	

	return nflags; 
}


//replace output with a different vertion of itself
//if 	flag == REP then replace token by obj
//	flag == PREP then prepend obj to token	
//	flag == APP then append obj to token
int  arrange(char *src, char *dest, int size, const char token, const char obj, int flag){
	int i_, cnt; 

	cnt = 0; 

	for(i_=0; i_<size ; i_++) {
		if( flag == PREP && src[i_] == token) { //prepend obj to token 
			dest[i_ + cnt] = obj; 
			cnt +=1;
		}

		if ( flag == REP ) //replace token by obj
			dest[i_+cnt] = obj;
		else 
			dest[i_+cnt] = src[i_] ; 

		if( flag == APD && src[i_] == token) { //append obj to token
			cnt +=1;
			dest[i_ + cnt] = obj; 
		}
	}	

	return i_ + cnt; 
}


int main (int argc, char **argv) { 

	int fd, count, acum, help, nflags, temp; 
	char *buff, *actual; 
	struct stat checking; 

	buff = (char*) malloc( sizeof(char) * BUFFSIZE); 
	actual = (char*) malloc( sizeof(char) * BUFFSIZE * 4); 

	acum = 0 ;
	
	if ( (nflags = parse(argc, argv)) == -1 )  //check if error while parsing 
		exit(-1); 
	

	if ( stat(argv[1], &checking) ) 	{
		perror("mycat:"); 
		exit(-1); 
	}

	if ( checking.st_mode & (__S_IFMT != __S_IFREG) ) { 	
		fprintf(stderr,"mycat: Not a regular file\n"); 
		exit(-2) ;
	}

	if ( (fd = open(argv[1], O_RDWR)) == -1) {
		perror("open:");
		exit(-3); 
	}


	while ( acum < checking.st_size   ) { 

		count = read(fd, buff, BUFFSIZE); // check what to do when count < BUFFSIZE	
		temp = count; 
	
		if( nflags > 0 ) { //this would include any modification on output format 
					//implied by the parser ###

			if( flags[0] )  
				count = arrange(buff, actual,  count, '\n', '$', PREP); 
		}
		else
			strncpy(actual, buff, count) ;
		
		help = 0 ;
		while( help < count ) 
			help += write(1, actual, count - help ); 		

		count = temp ;
		acum += count; 
	}

	//freeing memory
	close(fd); 

	exit(0); 
}

