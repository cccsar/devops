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


int main(int argc, char **argv) 
{
	char word[WORD_L]; 
	int i_;
	pair *visited;
	trie castano; 

	/* Construct trie */
	trieInit(&castano); 


	/* Read TEST_SIZE input words */
	for(i_=0; i_<TEST_SIZE; i_++) { 
		scanf("%s",word); 
		trieInsert(&castano, word); 
	}


	/* Testing contains */
	for(i_=0; i_<TEST_SIZE; i_++) {
		scanf("%s",word); 
		if( trieContains(&castano, word) ) 
			printf("Found word\n");
	}

	/* Allocate space for visited array) */
	visited = (pair*) malloc( castano.size * sizeof(pair));
	for(i_=0; i_<castano.size; i_++)  { 
		visited[i_].first = -1;
		visited[i_].second = -1;
	}
	visited[0].first = 0; 

	trieDfs(&castano, visited, 0, &castano.root[0]); 
	trieDfsRec(visited, castano.size);


	/* Destroy trie and free stuff*/
	trieTerm(&castano);
	free(visited);

	return 0; 
}


	/*
	 * DBG for each element of the trie
	for(i_=0; i_<TEST_SIZE; i_++) {
		printf("Looking at index %d of trie\n",i_);
		for(int j_=0; j_<ALPHA_SIZE; j_++) { 
			if(castano.root[i_].sons[j_] != -1 )
				printf("%d ",castano.root[i_].sons[j_]);
		}
		printf("\n");
	}
	*/

