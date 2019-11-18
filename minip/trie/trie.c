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
#include "trie.h"

#define TRUE 1
#define FALSE 0


/* parseChar
 * --------------
 *
 *
 */
int parseChar(char* number, int i_) { 
	return (int)number[i_] % 48;
	/* return (int)number[i_] % 97; */
}


/* nodeInit
 * --------------
 *
 *
 */
void nodeInit(node *word){ 
	int i_; 
	for(i_=0; i_<ALPHA_SIZE; i_++) 
		word->sons[i_] = -1; 

	word->flag = FALSE; 
}


/* trieInit
 * --------------
 *
 *
 */
void trieInit(trie *tree) { 
	tree->root = (node *) malloc(sizeof(node)*SOFT_L);
	tree->size = 1 ;
	tree->n_words = 0;
	tree->capacity = SOFT_L; 

	node first; 
	nodeInit(&first); 
	tree->root[0] = first ;
}


/* trieTerm
 * --------------
 *
 *
 */
void trieTerm(trie *tree) { 
	free(tree->root); 
}


/* trieResize
 * --------------
 *
 *
 */
int trieResize(trie *tree) {
	
	if( tree->capacity * 2 >= HARD_L ) {
		fprintf(stderr,"Reached maxium capacity\n");
		return FALSE; 
	}
	
	tree->root = (node *) realloc(tree->root, sizeof(node) * 2 * tree->capacity );
	tree->capacity *= 2;

	return TRUE; 
}
	

/* trieContains
 * --------------
 *
 *
 */
int trieContains(trie *tree, char *word) { 
	int word_size, i_, digit; 
	node dummie; 

	dummie = tree->root[0] ;
	word_size = strlen(word); 
	for(i_=0; i_<word_size; i_++){ 
		
		digit = parseChar(word, i_); 

		if ( dummie.sons[digit] != -1) 
			dummie = tree->root[ dummie.sons[digit] ]; 
		else
			break; 
	}

	if( i_ == word_size && dummie.flag == TRUE ) 
		return TRUE; 
	else
		return FALSE; 

}


/* trieInsert
 * --------------
 *
 *
 */
int trieInsert(trie *tree, char *number ) { 
	int i_, word_size, digit; 
	node *current; 

	word_size = strlen(number);

	current = &(tree->root[0]); 
	for(i_=0; i_<word_size; i_++) {

		digit = parseChar(number,i_);

		/* Adjust capacity */
		if (tree->size == tree->capacity)  {

			if( !trieResize(tree) ) {
				fprintf(stderr,"Unable to complete insertion\n");
				return -1;  
				/* ### add error correct */
			} 
			/* still problem with realloc() ###*/

		}

		/* check if ith letter is already saved */
		if( current->sons[ digit ] == -1 ) {
			node dummie; 
			nodeInit(&dummie); 

			tree->root[ tree->size ] = dummie;
			current->sons[ digit ] = tree->size ; 

			tree->size++; 
		}
		else {
			if( i_ == word_size-1 ) {
				printf("Already inserted\n");
				return -2;  
				/* ### add error correct */
			}
		}

		current = &( tree->root[ current->sons[digit] ] ) ; 
	}

	tree->n_words++;
	current->flag = TRUE; 
}


/* trieDfsRec
 * --------------
 *
 *
 */
void trieDfsRec(pair *visited, int size) {
	int i_, j_, k_, counter;
	int word[size];

	for(i_=0; i_<size; i_++) {

		k_ = i_;
		counter=0;
		while( visited[k_].first != k_ ) {
			word[counter] = visited[k_].second; 
			k_ = visited[k_].first;
			counter++;
		}
		
		if(counter > 0) {
			for(j_ = counter-1; j_ >= 0; j_--)   
				printf("%c",word[j_]+48);
		}
		printf("\n");
		
	}

}


/* trieDfs
 * --------------
 *
 *
 */
void trieDfs (trie *tree, pair *visited, int this, node *dummie) {
	int i_, index; 

	for(i_=0; i_<ALPHA_SIZE ; i_++) { 

		if (dummie->sons[i_] != -1) {

			index = dummie->sons[i_];
			if(visited[ index ].first == -1) {
				visited[ index ].first = this;
				visited[ index ].second = i_;

				trieDfs(tree, visited, index, &tree->root[ index ]);
			}
		}
	}

}


