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
#include "singly.h"

#define CONSTANT 20
#define TRUE 1
#define FALSE 0



/* snodeInit
 * --------------
 *
 *
 */
void snodeInit(snode *n_, int number) {
	/*next points to null and element is 0*/
	n_->next = (snode *) NULL; 
	n_->element = number; 
}


/* singlyInit
 * --------------
 *
 *
 */
void singlyInit(singly *l_) {
	/*head and tail point to null*/
	l_->head = l_->tail = (snode *) NULL; 
	l_->size = 0; 
}


/* singlyDestroy
 * --------------
 *
 *
 */
void singlyDestroy(singly *l_) {
	int i_; 
	snode *killed, *dummie; 

	if (l_->size > 1) {
	}
	else  {
		killed = l_->head;
		dummie = killed->next;
		while( dummie != (snode*) NULL ) {
			free(killed); 
			killed = dummie; 
			dummie = dummie->next; 
		}
		free(killed);
	}		

	free(l_);
}


/* singlyInsert
 * --------------
 *
 *
 */
void singlyInsert(singly *l_, snode *n_) {
	
	if (l_->size == 0)  {
		l_->head = l_->tail = n_; 
	}
	else if (l_->size >= 1 )  {
		(l_->tail)->next = n_; 
		l_->tail = n_;
	}

	l_->size++;
}


/* singlySearch
 * --------------
 *
 *
 */
int singlySearch(singly *l_, int number) {
	int i_; 
	snode *dummie; 

	dummie = l_->head; 
	for(i_=0; i_<l_->size; i_++) {
		
		if ( dummie->element == number) 
			return 1; 

		dummie = dummie->next;
	}

	return 0; 
}


/* singlyPrint
 * --------------
 *
 *
 */
void singlyPrint(singly *l_) { 
	snode *dummie; 

	if (l_->size == 0) 
		printf("NULL"); 
	else { 
		dummie = l_->head; 
		while(dummie != NULL) {
			printf("%d ",dummie->element);
			dummie = dummie->next; 
		}
		printf("\n");
	}
}

/* singlyTesting
 * --------------
 *
 *
 */
void singlyTesting() {
	/*remember to do malloc of all your shit*/
	singly *l_;
	int i_, term;
	snode *dummie; 

	l_ = (singly*) malloc( sizeof(singly) ); 
	singlyInit(l_); 


	singlyInit(l_);

	for(i_=0; i_<CONSTANT; i_++)  {
		dummie = (snode *) malloc( sizeof(snode) ); 
		snodeInit(dummie, i_);
		singlyInsert(l_, dummie);
	}

	printf("Search: ");
	scanf("%d",&term); 

	printf("%s\n", (singlySearch(l_, term))? "Esta": "no esta" );

	/*print it	*/


	/*free goes here*/
	singlyDestroy(l_);
}
