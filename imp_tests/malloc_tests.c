#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define TSIZE 1 

int main (int argc, char **argv) { 

	char *a = (char*) malloc( sizeof(char) * 20 ); 
	char *b = (char*) malloc( sizeof(char) * (1+TSIZE) );
	char *c = (char*) malloc( sizeof(char) * TSIZE); 
	int i_; 

	printf("Init addr for a: %p\nInit addr for b: %p\nInit addr for c: %p\n",a,b,c); 

	*(a+2) = 'a';
	*(a+17) = 'b'; 
	*(a+33) = 'c';

	printf("\nTests with a\n");
	printf("Inside memory range, normal: %c, ptr is %p\n",*(a+2),a+2); 
	printf("out of my memory range, but within constraint: %c the corresp ptr is %p\n",*(a+17), a+17); 
	printf("out of my memory range, but outside constraint: %c the corresp ptr is %p\n",*(a+33), a+33); 

	/* Here, constraint represent de address space that begins after the allocated
	 * memory with a malloc, and the next allocated space */


	/* Ergo:
	 * 	one can modify addresses outside of allocated memory space with malloc()
	 * 	malloc does a padding to keep a certain boundary between calls to it
	 * 		how much is that padding? Idunno
	 */
	return 0; 
}

