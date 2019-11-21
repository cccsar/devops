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
#define MAX_PS 10
#define VSIZE 50



/*
 * --------------
 *
 *
 */
void initVect(vect *vv) { 
	vv->words = (char**) malloc(sizeof(char*)*VSIZE) ;
	vv->size = 0;
}


/*
 * --------------
 *
 *
 */
void destVect(vect *vv) {
	int i_;
	for(i_=0; i_<vv->size ; i_++) 
		free(vv->words[i_]);
	free(vv->words);
}


/*
 * --------------
 *
 *
 */
void resizeVect(vect *vv) {
	if (vv->size % VSIZE == 1) {
		vv->words = realloc( vv->words, 2*(vv->size + 1) ); 
	}
}


/*
 * --------------
 *
 *
 */
void putVect(vect *vv, char* word) { 
	vv->words[ vv->size ] = (char*) malloc(sizeof(char) * strlen(word) + 1);
	strcpy(vv->words[ vv->size ], word); 
	vv->words[ vv->size ][ strlen(word) + 1] = '\0';

	vv->size++;
}


/*
 * --------------
 *
 *
 */
void printVect(vect *vv) { 
	int i_;
	for(i_=0; i_<vv->size ; i_++) 
		printf("%s\n",vv->words[i_]);	
}


/*
 * --------------
 *
 *
 */
int testing() {
	int i_;
	char *dummie; 
	vect perico; 
	initVect(&perico);

	dummie = (char*) malloc(sizeof(char) * 20);

	for(i_=0; i_<2 ; i_++) {
		scanf("%s",dummie); 
		putVect(&perico, dummie); 	
	}

	printVect(&perico);

	destVect(&perico);
}
