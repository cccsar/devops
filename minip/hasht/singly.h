
#ifndef __SINGLY__
#define __SINGLY__

/* snode
 * --------------
 *
 *
 */
typedef struct singly_node {
	struct singly_node *next; 
	int element; 
} snode;


/* singly 
 * --------------
 *
 *
 */
typedef struct {
	snode *head, *tail; 
	int size;
} singly;


/* snodeInit
 * --------------
 *
 *
 */
void snodeInit(snode *n_, int number); 


/* singlyInit
 * --------------
 *
 *
 */
void singlyInit(singly *l_) ;


/* singlyDestroy
 * --------------
 *
 *
 */
void singlyDestroy(singly *l_) ;


/* singlyInsert
 * --------------
 *
 *
 */
void singlyInsert(singly *l_, snode *n_) ;


/* singlySearch
 * --------------
 *
 *
 */
int singlySearch(singly *l_, int number) ;


/* singlyPrint
 * --------------
 *
 *
 */
void singlyPrint(singly *l_) ; 


/* singlyTesting
 * --------------
 *
 *
 */
void singlyTesting() ;

#endif
