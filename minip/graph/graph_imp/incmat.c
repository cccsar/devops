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

typedef struct pair{ 
	int first; 
	int *second; 
} pip; 


/* init
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


/* create
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


/* print
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

pip adyacents(int **mat, int n, int m, int e) {
	int i_, j_, *ady, n_ady; 
	pip ret; 

	n_ady = 0; 
	ady = (int*) malloc(sizeof(int) * (n-1)) ; 
	
	for(i_=0; i_<m ; i_++) {
		
		if ( !mat[e][i_] )  
			continue; 

		for(j_=0; j_<n ; j_++) {

			if ( mat[j_][i_] && j_!=e ) {
				ady[n_ady] = j_; 
				n_ady++; 
			}
		}	
	}	

	ret.first = n_ady; 
	ret.second = ady; 

	return ret; 
}

/* addEdge
 * --------------
 * 
 *
 */
void addEdge(int **mat,int n,int *m) { 
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


/* deleteEdge
 * --------------
 * 
 *
 */
void deleteEdge(int **mat, int n, int *m, int e) {
	int i_, j_, **help, *temp; 


	if ( e != *m-1 ) { 
		//ask for new submatrix
		help = (int**) malloc(sizeof(int*) * n); 
		for(i_=0; i_<n ; i_++) 
			help[i_] = (int*) malloc(sizeof(int) * (*m - (e+1) )) ;	

		//copy right segment of slice to submatrix
		for(i_=0; i_<n ; i_++) {
			for(j_=e+1; j_<*m ; j_++) 
				help[i_][j_ - (e+1)] = mat[i_][j_] ; 	
		}		

		//resize input matrix
		for(i_=0; i_<n ; i_++) 
			mat[i_] = (int*) realloc(mat[i_], sizeof(int*) * (*m-1)); 	
		
		//copy from submatrix
		for(i_=0; i_<n ; i_++) {
			for(j_=e; j_<*m-1 ; j_++) 
				mat[i_][j_] = help[i_][j_ - e]; 	
		}		

	}
	else { 
		for(i_=0; i_<n ; i_++) 
			mat[i_] = (int*) realloc(mat[i_], sizeof(int*) * (*m-1)); 	
	}

	*m -= 1; 
}



/* addNode
 * --------------
 * 
 *
 */
void addNode(int **mat, int *n, int m) { 
	int i_; 

	*n +=1 ;

	mat = (int**) realloc(mat, sizeof(int*) * (*n)); 
	mat[*n-1] = (int*) malloc ( sizeof(int) * m) ; 


	for(i_=0; i_<m ; i_++) 
		mat[*n-1][i_] = FALSE; 	

}

/* deleteNode
 * --------------
 * 
 *
 */
void deleteNode(int **mat, int *n, int *m, int e) { 
	int i_, j_, **help; 
	pip test; 

	//delete every edge with e as an extreme
	test = adyacents(mat, *n, *m, e);
	for(i_=0; i_<test.first ; i_++) 
		deleteEdge(mat, *n, m, test.second[i_]) ; 

	if ( e != *n-1) {
		//allocate space for copy submatrix
		help = (int**) malloc(sizeof(int*) * (*n-(e+1) )); 
		for(i_=0; i_<*n ; i_++) 
			help[i_] = (int*) malloc( sizeof(int) * (*m)) ;

		//save slice on submatrix
		for(i_=e+1; i_<*n ; i_++) {

			for(j_=0; j_<*m ; j_++) 
				help[i_-(e+1)][j_] = mat[i_][j_]  ;
		}	

		//resize original matrix
		mat = (int**) realloc(mat, sizeof(int*) * (*n-1) ) ;

		//paste submatrix on resized matrix
		for(i_=e; i_<*n-1 ; i_++) {

			for(j_=0; j_<*m ; j_++) 
				mat[i_][j_] = help[i_-e][j_] ; 
		}	

	}
	else  //in case e is last node, simply resize to *n-1
		mat = (int**) malloc(sizeof( int*) * (*n-1)); 	

	*n -= 1;
}




int main (int argc, char **argv) { 
	int i_, n, m, **incmat; 
	pip deg_ady; 

	scanf("%d %d", &n, &m); 

	//space allocation
	incmat = (int**) malloc( sizeof(int*) * n ); 	
	for (i_=0 ; i_<n ; i_++)  
		incmat[i_] = (int*) malloc( sizeof(int) * m) ; 

	init(incmat, n, m); 

	print(incmat, n, m); 
	printf("size: %d\tn_edges: %d", n, m);
	NEWLINE

	create(incmat, m); 

	print(incmat, n, m); 
	NEWLINE

	printf("Adding edge\n");
	addEdge(incmat, n, &m); 
	printf("size: %d\tn_edges: %d", n, m);
	NEWLINE;
	print(incmat, n, m) ;
	NEWLINE

	printf("Adding node\n");
	addNode(incmat,&n, m ); 
	printf("size: %d\tn_edges: %d", n, m);
	print(incmat, n, m ) ;
	NEWLINE;

	
	printf("Deleting edge 3\n");
	deleteEdge(incmat, n, &m, 3);
	printf("size: %d\tn_edges: %d", n, m);
	print(incmat, n, m ) ;
	NEWLINE;

	deg_ady = adyacents(incmat, n, m, 2); 
	printf("size: %d\tn_edges: %d", n, m);
	printf("Degre of 2: %d", deg_ady.first); 
	NEWLINE;

	printf("Adyacents of 2: ") ;
	for(i_=0; i_<deg_ady.first ; i_++) 
		printf("%d ", deg_ady.second[i_] ); 	
	NEWLINE;



	return 0; 
}
