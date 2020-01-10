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
#define NEWLINE printf("\n");

//Se asume que las etiquetas de vertices indexan de 0

/*
 * --------------
 *
 *
 */
void init(int **mat, int n, int m) { 
	int i_, j_; 
	for (i_=0 ; i_<n ; i_++) { 

		for (j_=0 ; j_<m ; j_++)  
			mat[i_][j_] = FALSE; 
	}

}


/*
 * --------------
 *
 *
 */
void create(int **mat, int m) { 
	int i_, u, v; 

	for (i_=0 ; i_<m ; i_++) { 
		scanf("%d %d", &u, &v); 
		mat[u][i_] = TRUE; 
		mat[v][i_] = TRUE; 
	}
}


/*
 * --------------
 *
 *
 */
void print(int ** mat, int n, int m ) {
	int i_, j_; 
	
	for (i_=0 ; i_<n ; i_++) { 

		for (j_=0 ; j_<m ; j_++)  
			printf("%d ",mat[i_][j_]); 
		NEWLINE
	}
}


/*
 * --------------
 *
 *
 */
void addEdge(int n, int *m ,int **mat) { 
	int i_, u, v;
			
	scanf("%d %d", &u, &v);
	*m += 1;

	for (i_=0 ; i_<n ; i_++){ 
		mat[i_] = (int *) realloc ( (void*) mat[i_], sizeof(int)* (*m) ); 	

		if ( i_ == u || i_ == v )  
			mat[i_][ *m - 1 ] = TRUE;
		else 
			mat[i_][ *m - 1 ] = FALSE;
	}
}


int main (int argc, char **argv) { 
	int i_, n, m, **incmat; 

	scanf("%d %d", &n, &m); 

	//space allocation
	incmat = (int**) malloc( sizeof(int*) * n ); 	
	for (i_=0 ; i_<m ; i_++)  
		incmat[i_] = (int*) malloc( sizeof(int) * m) ; 

	init(incmat, n, m); 

	print(incmat, n, m); 
	NEWLINE

	create(incmat, m); 

	print(incmat, n, m); 
	NEWLINE

	addEdge(n, &m, incmat); 
	print(incmat, n, m) ;
	NEWLINE
	


	return 0; 
}
