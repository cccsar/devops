
#define SOFT_L 1024 /* 2 ** 10 */
#define HARD_L 32768 /* 2^15 ###*/
#define WORD_L 30
#define ALPHA_SIZE 10
#define TEST_SIZE 5

#ifndef __TRIE__
#define __TRIE__

/* pair
 * --------------
 *
 *
 */
typedef struct {
	int first, second; 
} pair; 


/* node
 * --------------
 *
 *
 */
typedef struct { 
	int sons[ALPHA_SIZE]; 
	int flag; 
} node; 


/* trie
 * --------------
 *
 *
 */
typedef struct {
	node *root; 
	int size; 
	int n_words; 
	int capacity; 
} trie;


/* parseChar
 * --------------
 *
 *
 */
int parseChar(char* number, int i_) ; 



/* nodeInit
 * --------------
 *
 *
 */
void nodeInit(node *word); 


/*  trieInit
 * --------------
 *
 *
 */
void trieInit(trie *tree) ; 


/* trieTerm 
 * --------------
 *
 *
 */
void trieTerm(trie *tree) ; 


/* trieResize 
 * --------------
 *
 *
 */
int trieResize(trie *tree) ;



/* trieContains 
 * --------------
 *
 *
 */
int trieContains(trie *tree, char *word) ; 



/* trieInsert
 * --------------
 *
 *
 */
int trieInsert(trie *tree, char *number ) ; 



/* trieDfsRec
 * --------------
 *
 *
 */
void trieDfsRec(pair *visited, int size) ;



/* trieDfs
 * --------------
 *
 *
 */
void trieDfs (trie *tree, pair *visited, int this, node *dummie) ;

#endif
