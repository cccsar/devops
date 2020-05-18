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
#define CRETURN '\r'
#define VTAB '\v'
#define FFED '\f'

//flags	
#define WORD "words"
#define CHAR "chars"
#define BYTE "bytes"
#define LENGTH "max-line-length"
#define LINE "lines"
#define HELP "help"

//limits
#define FLIMIT 100
#define BUFFSIZE 512
#define NOPTS 4

//colors
#define RED "\033[1;31m" 
#define WHITE "\033[0;37m"

//file desc
#define STDIN 0
#define STDOUT 1
#define STDERR 2

//messages
#define HELPMESSAGE "wm counts metrics of a file. When invoked with no options\n\
it counts the number of words, lines and bytes.\n\n\
options:\n\
\t-w --words\t\tnumber words of the file\n \
\t-c --bytes\t\tnumber bytes of the file\n \
\t-l --lines\t\tnumber lines of the file\n \
\t-L --max-line-lenght\toutput the maximum line lenght \n \
\t--help\t\t\tshow this help\n \
\t- read form standard input\n \
\nDone by cCc\n"


//structures and global stuff
int flags[NOPTS]; 
int breaker; 

struct attributes{ 
	int valid; //this is to validate associated file
	int nlines; 
	int nbytes;
	int nwords;
	int maxlength;
} typedef attrib;

void initAttrib(attrib *some) { 
	some->valid = TRUE; 
	some->nlines = 0;
	some->nbytes = 0 ;
	some->nwords = 0 ;
	some->maxlength = 0 ;
}


struct pair_int { 
	int first, second ;
}typedef pi;


void sigIntHandler() { //signal handler to change state of breaker glob
	breaker = FALSE; 
}


void colorEWrapper(int fd, const char* string, int flag){ 
	int tty = isatty(fd); 
	
	fprintf(stderr,"wm: ");

	if ( tty )  
		fprintf(stderr,"%s",RED) ;	

	if ( flag )  
		perror(string); 
	else  
		fprintf(stderr,"%s\n",string); 	

	if ( tty )
		fprintf(stderr,"%s",WHITE); 
}


//help flag overrides other flags 
pi parse(int argc, char **argv, char** files) { 
	int i_, j_, nflags, fcount, helper; 
	pi resp; 

	resp.first = -1 ;
	resp.second = -1 ; 

	nflags = fcount =  0 ;

	for(i_=1; i_<argc ; i_++) {
		j_ = 1 ;
		if ( argv[i_][0] == '-' ) { 

			helper = TRUE; //this is to break wloop in case of error cond
			while ( argv[i_][j_] != '\0' && helper) { 

				switch( argv[i_][j_] ) { 
					case 'l': 
						nflags += 1; 
						if ( !flags[0] ) 
							flags[0] = nflags; 
						break; 
					case 'w': 
						nflags += 1; 
						if ( !flags[1] ) 
							flags[1] = nflags; 
						break; 
					case 'c': 
						nflags += 1; 
						if ( !flags[2] ) 
							flags[2] = nflags; 
						break; 
					case 'L': 
						nflags += 1; 
						if ( !flags[3] ) 
							flags[3] = nflags; 
						break; 
					case '-': //check if could be changed so it uses a case

						if ( argv[i_][1] == '-') { 
							char *word; 
							word = (char*) malloc( sizeof(char) * strlen( argv[i_]+2 ) ) ;

							strcpy( word, argv[i_] + 2 ); 

							//INCORPORATE HELP FLAG ###
							if ( strcmp(word, HELP) == 0 ) 
								return resp; 
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
								colorEWrapper(STDERR, "Not a valid flag\n", FALSE); 

							free(word); 
						}

						helper = FALSE ; 
						break; 
					default: 
						colorEWrapper(STDERR, "Not a valid flag", FALSE ) ;

						helper = FALSE;
				}
	
				j_++ ;
			}

			//include '-' as a file when encountered
			if( argv[i_][1] == '\0') { //this could be enhanced for readibility ### 
				files[fcount] = (char*) malloc( sizeof(char) ) ;  		
				strcpy( files[fcount], argv[i_] ) ; 
	
				fcount +=1; 
			}
		}
		else { 

			//include anything not beggining with '-' as a file when encountered
			files[fcount] = (char*) malloc( sizeof(char) * strlen(argv[i_]) ) ;  		
			strcpy( files[fcount], argv[i_] ) ; 

			fcount +=1; 
		}
	}	

	//udpate response
	if( nflags > 0 || fcount >0 ) { 
		resp.first = nflags; 
		resp.second = fcount; 
	}
	return resp; 
}


int isNewline(char e) { 
	if ( e == NEWLINE ) 
		return 1; 
	return 0; 
}


int isWhiteSpace(char e) { 
	if ( e == BLANK || e == TAB || isNewline(e) || e == CRETURN
	 	|| e == VTAB || e == FFED )  
		return 1; 
	return 0; 
}


void updateAttrib(attrib *flw, int fd, int size) { 
	int i_, rd, run, prev, word, temp; 
	char buff[BUFFSIZE]; 

	word = FALSE; 
	rd = temp = run =  0 ;
	prev = -1; 

	breaker = (size == -1)? TRUE: FALSE; 

	while ( run < size || breaker) { 

		rd = read(fd, buff, BUFFSIZE);  
		//to enhance: How to disable reading with a signal without
		//having to wait for next read? <-using signals

		if ( !breaker && size ==-1) //this upsets me ### 
			break; 

		for(i_=0; i_<rd ; i_++) {

			if( isWhiteSpace( buff[i_] ) ) { 
				// if whitespace and previously a word, increase
				// number of words and change word state
				if ( word ) { 
					flw->nwords += 1; 
					word = FALSE ;
				}
			}
			else { 
				//if not whitespace and previously not a word, 
				//change word state
				if ( !word )  
					word = TRUE ;
			}


			if ( isNewline( buff[i_] ) )  {
				//if newline increase newline count and keep track
				//of maximum line size
				flw->nlines += 1; 

				if ( temp > prev) 
					prev = temp ; 	//compute maximum line length
				temp = 0 ;
			}
			else  
				temp +=1;

			flw->nbytes += 1; 
		}	

		if ( !breaker && size != -1)  //this upsets me ###
			run += rd; 
	}	

	flw->maxlength = prev ;
}


int main (int argc, char **argv) { 
	int fd, i_;  
	char *files[FLIMIT]; 

	struct stat check[FLIMIT]; 
	attrib follow[FLIMIT], total; 
	pi info; 

	void (*old_handler)(); 


	old_handler = signal(SIGINT, sigIntHandler ); 
	initAttrib(&total); 

	info = parse(argc, argv, files); //info.first = # of flags, info.second = # of files
	if( info.second == -1 ) { //if not even a file or flag, or help flag, print help message
		printf("%s",HELPMESSAGE); 
		exit(0); 
	}

	if ( info.first == -1)  {
		colorEWrapper(STDERR, "Error parsing\n", FALSE); 
		exit(-1) ;
	}


	for(i_=0; i_<info.second ; i_++) { 

		initAttrib( &follow[i_] ) ; //initialize attributes

		if ( files[i_][0] != '-' ) { 

			if ( (fd = open( files[i_], O_RDONLY) ) == -1 ) { 
				colorEWrapper(STDERR, "", TRUE); 
	
				follow[i_].valid = FALSE ;
				continue;
			}
			
			if ( (stat( files[i_], & check[i_] )) == -1) { 
				colorEWrapper(STDERR, "", TRUE); 
	
				close(fd); 
				follow[i_].valid = FALSE ;
				continue; 
			}


			updateAttrib( &follow[i_], fd, check[i_].st_size ) ; 

			close(fd); 
		}
		else 
			updateAttrib( &follow[i_], STDIN, -1 ) ; 
	}

	//printing output: if no flags specied default is to print
	//	#lines		#nwords		#nbytes
	for(i_=0; i_<info.second ; i_++) { 
		if ( follow[i_].valid != FALSE ) { 
			
			if ( flags[0] || info.first == 0 ) {
				printf("%1d ", follow[i_].nlines ) ; 
				total.nlines += follow[i_].nlines; 
			}
			if ( flags[1] || info.first == 0 ) {
				printf("%1d ", follow[i_].nwords ) ; 
				total.nwords += follow[i_].nwords; 
			}
			if ( flags[2] || info.first == 0 ) {
				printf("%1d ", follow[i_].nbytes ) ; 
				total.nbytes += follow[i_].nbytes; 
			}

			if ( flags[3] )  {
				printf("%1d ", follow[i_].maxlength ) ; 
				if ( follow[i_].maxlength > total.maxlength ) 
					total.maxlength = follow[i_].maxlength;
			}

			printf("%s\n", files[i_] ) ; 
		}
	}

	if ( info.second > 1 ) {	//this doesn't consider failed files
					//wc doesn't either tough
		//if i-th flag set or no flags given, print corresponding attrib
		//and accumulate for total attribs

		if ( flags[0] || info.first == 0 ) 	
			printf("%1d ", total.nlines ) ; 
		if ( flags[1] || info.first == 0 ) 
			printf("%1d ", total.nwords ) ; 
		if ( flags[2] || info.first == 0 ) 
			printf("%1d ", total.nbytes ) ; 

		if ( flags[3] )  
			printf("%1d ", total.maxlength ) ; 

		printf("total\n") ; 
	}


	//clearing 
	for(i_=0; i_<info.second ; i_++) 
		free(files[i_]); 
	
	return 0; 
}


//final considerations
//
//	check first : 
//		--flags and number of them and wether or not they'll have options
//		--check the logic of the parser: every posible combination of options 
//		and filter nonsense options	 <-	most important
//		--if ouput requires formatting, think how to save info requested from
//		parsing so it is easily outputted
//		--Correctness of arguments and option arguments
//
//	in-out considerations: Since a cmd is only a program that receives input, parses it
//	produces output we must take into account: 
//		--There might be commands or subset of flags that allow producing output on
//		the run instead of waiting till the end to produce output. 
//		i.e. find ./ -name "somename.txt" --printf
//		--if program output must be sorted somehow, whatever fullfills requirements of 
//		command and arguments must be saved
//
// 	/--write the parser thinking it as a state machine and cut down invalid combinations 
// 		and if order of a subset of flags isn't relevant, ignore permutations --/
//
//	-- Only after having this tought through, one should proceed to : 
//
//	Code having in mind that within the minimum functionallity a flag bifurcation may be 
//	included and this shouldn't create duplication of code. i. e: repeating code for grep
//	when searching for special files. This isn't programming minimum functionality first 
//	and then extending it. This is programme minimum-half-past functionality that takes
//	into account every possible valid combination of flags.
//	
//	
//	################################### PARSER  #################################### 
//
//how to handle long options? -> up until now it encompasses strcmp against 
//	defined tokens
//
//does it matter the order where options appear in parsing? -> not for this cmd
//
//does it matter wheter options are requested in a single flag or in different ones? 
//	in general no
//
//how to include option argument ?  ***
//
//handling mutally exclusive flags
//
//handling flags that cancel invocation of others
//
// 	#### additional #### 
//
// after taking all af this into account, consider give some color to your output
// this of course conditioned to wether the output device ( destination fd ) is 
// a terminal
//


