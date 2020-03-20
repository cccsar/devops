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
#include "hash.h"

#define TRUE 1
#define FALSE 0
/*constant for debugging*/
#define CONSTANT 20



/*hashtInit
 * --------------
 *
 *
 */
void hashtInit(hasht h_){
	/*every cell has a list with an address*/
	int i_; 

	for(i_=0; i_<HASH_SIZE; i_++)  
		h_[i_] = (singly *) NULL; 		
}


/*hashDestroy
 * --------------
 *
 *
 */
void hashDestroy(hasht h_) {
	int i_;

	for(i_=0; i_<HASH_SIZE ; i_++) {
		if (h_[i_] != NULL) 
			singlyDestroy(h_[i_]);	
	}	
}


/*hashtInsert
 * --------------
 *
 *
 */
int hashtInsert(hasht h_, int number){
	/*implement hash function and mix it wih list insertion*/
	int index; 
	snode *dummie; 

	dummie = (snode *) malloc( sizeof(snode) );
	snodeInit(dummie, number);

	index = number % HASH_SIZE; 	

	if (h_[index] != NULL ) { 

		if ( singlySearch(h_[index], number)  ){ 
			/*la tabla no acepta elementos repetidos*/
			printf("Already in here\n");
			return FALSE; 
		}

		singlyInsert( h_[index], dummie);  
	}
	else {
		singly *new_list;

		new_list = (singly *) malloc( sizeof(singly) ); 
		singlyInit(new_list); 

		singlyInsert(new_list, dummie); 


		h_[index] = new_list; 
	}

	return TRUE;
}


/*hashtPrint
 * --------------
 *
 *
 */
void hashtPrint(hasht t_) {
	int i_;
	for(i_=0; i_<HASH_SIZE/2; i_++)   {
		if (t_[i_] != NULL ) 
		singlyPrint(t_[i_]); 
	}
}


/*  hashTesting 
 * --------------
 *
 *
 */
int hashTesting () { 

	hasht table; 
	int i_;
	
	hashtInit(table); 

	for(i_=0; i_<CONSTANT ; i_++) {
		hashtInsert(table, i_); 
	}	

	hashtPrint(table);

	hashDestroy(table);

	return 0; 
}

