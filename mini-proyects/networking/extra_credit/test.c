#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <ctype.h> 
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h> 

#define TRUE 1
#define FALSE 0

#define MAXT 10

//The program is suposed to create a thread for each file specified
//that reads the 3 first lines and outputs a pitagorean identity
//
struct atts {
	char * file_name; 
}; 

void start_rout( struct atts *attributes ) { 
	int resp, a, b; 
	FILE *fp; 
	
	
	fp = fopen( (const char *) attributes->file_name, "r"); 

	if ( fp == NULL ) { //if couldn't open file return NULL (this because pthread_join) 
		fclose(fp); 
		pthread_exit( (void *) NULL ) ;
	}

	fscanf(fp, "%d",&a); 	//read first line?
	fscanf(fp, "%d",&b); 	//read second line? 

	resp = a * b; 

	fclose(fp); 
	pthread_exit( (void *) &resp); 	
}


int main(int argc, char ** argv) { 
	int i_, len; 
	pthread_t threads[MAXT]; 
	int status[MAXT]; 
	struct atts attributes[MAXT]; 

	for(i_=0; i_<MAXT ;i_++) { //iniatilice
		status[i_] = -1	;
	}	

	for(i_=1; i_<=argc ;i_++) { //spawn threads for each argument provided, and pass arguments
					//as values to attributes
		len = strlen( argv[i_] ) ; 
		attributes[i_-1].file_name = (char*) malloc( sizeof(char) * (len + 1) )  ;
		strncpy(attributes[i_-1].file_name, argv[i_], strlen(argv[i_]) ); 

		pthread_create(&threads[i_-1], NULL, (void *) &start_rout,  (void *) &attributes[i_-1]); 
	}	

	printf("llego\n"); 
	for(i_=0; i_<argc ;i_++) { 
		pthread_join(threads[i_], (void *) &status[i_] ) ;
		if ( status[i_] != -1) { 
			printf("Result from %ld is: %d\n",threads[i_], status[i_]); 
		}
	}	
	exit(0); 
}

//       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);
//
//       void pthread_exit(void *retval);

//       int pthread_join(pthread_t thread, void **retval);
