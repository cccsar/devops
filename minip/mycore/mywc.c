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

//identifiers
#define BLANK ' '
#define TAB '\t'
#define NEWLINE '\n'

//flags	
#define NOPTS 5
#define WORD "word"
#define CHAR "chars"
#define BYTE "bytes"
#define LENGTH "max-line-lenght"
#define LINE "lines"

#define FLIMIT 100

struct attribs { 
	int valid; //this is to validate associated file
	int nlines; //l
	int nbytes; //c
	int nwords; //w
	int maxlength; //L
} ;

struct pair_int { 
	int first, second ;
}typedef pi;

int flags[NOPTS]; 



pi parse(int argc, char **argv, char** files) { 
	int i_, j_, nflags, fcount; 
	pi resp; 

	resp.first = -1 ;
	resp.second = -1 ; 

	nflags = fcount = 0 ;

	for(i_=0; i_<argc ; i_++) {
		j_ = 1 ;
		if ( argv[i_][0] == '-' ) { 

			while ( argv[i_][j_] != '\0' ) { 

				switch( argv[i_][j_] ) { 
					case 'l': 
						flags[0] = TRUE; 
						nflags += 1; 
						break; 
					case 'c': 
						flags[1] = TRUE; 
						nflags += 1; 
						break; 
					case 'w': 
						flags[2] = TRUE; 
						nflags += 1; 
						break; 
					case 'L': 
						flags[3] = TRUE; 
						nflags += 1; 
						break; 
					case '-': //this needs debugging
						printf("entro\n");
						if ( argv[i_][1] == '-') { 
							char *word; 
							word = (char*) malloc( sizeof(char) * strlen( argv[i_]+3 ) ) ;

							strcpy( word, argv[i_] + 2 ); 
							//this fucking set of if is because switch wont
							//let me compare strings

							if ( strcmp(word, LINE) == 0 ) { 
								flags[0] = TRUE; 
								nflags += 1; 
							}
							else if ( strcmp(word, CHAR) == 0 ) { 
								flags[1] = TRUE; 
								nflags += 1; 
							}
							else if ( strcmp(word, WORD) == 0 ) { 
								flags[2] = TRUE; 
								nflags += 1; 
							}
							else if ( strcmp(word, LENGTH) == 0 ) { 
								flags[3] = TRUE; 
								nflags += 1; 
							}
							else  
								fprintf(stderr, "mywc: Not a valid flag\n");
						}

						break; 
					default: 
						fprintf(stderr, "mywc: Not a valid flag\n");
						return resp; 
				}
	
				j_++ ;
			}
		}
		else { //se podra?
			files[i_] = (char*) malloc( sizeof(char) * strlen(argv[i_]) ) ;  		
			fcount +=1; 
			
			strcpy( files[i_], argv[i_] ) ; 
		}
	}	

	//udpate response
	resp.first = nflags; 
	resp.second = fcount; 

	return resp; 
}


int main (int argc, char **argv) { 
	int fd, i_; 
	char files[FLIMIT]; 
	struct stat check[FLIMIT]; 
	struct attribs follow[FLIMIT]; 
	pi info; 


	info = parse(argc, argv, files); 


	if ( info.first == -1)  {
		fprintf(stderr,"mywc: Error parsing\n");	
		exit(-1) ;
	}

	for(i_=0; i_<info.second ; i_++) { //go throug given files

		if ( (fd = open( files[i_], O_RDONLY) ) == -1 ) { 
			perror("open"); 
			follow[i_].valid = FALSE ;
			continue;
		}
		
		if ( (fstat( files[i_], & check[i_] )) == -1) { 
			perror("stat"); 
			follow[i_].valid = FALSE ;
			continue; 
		}

		//here read and check for identifiers while reading from file
		//whenever one is found increase the count associated to each file in follow
		//consider: 
		//	if a file doesn't exist there's no reason to stop exection, just skip 

	}


	return 0; 
}

