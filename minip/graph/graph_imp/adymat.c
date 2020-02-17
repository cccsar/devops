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
#define MAXSIZE 1000
#define NEWLINE printf("\n"); 

int adymat[MAXSIZE][MAXSIZE];



/* init | DI
 * --------------
 * duh
 */
void init(int size) { 
	int i_, j_;
	for(i_=0; i_<size ; i_++) {
		for(j_=0; j_<size ; j_++) {
			adymat[i_][j_] = FALSE; 	
		}		
	}
}


/* print | DI
 * --------------
 * duh
 */
void print (int size) { 
	int i_, j_;

	for(i_=0; i_<size ; i_++) {
		for(j_=0; j_<size ; j_++) {
			printf("%d ",adymat[i_][j_]); 
		}		
		NEWLINE
	}
} 


/* create | DI
 * --------------
 * recibe por stdin los datos del grafo para crearlos. Importan n y m
 */
void create(int m) { 
	int i_, u, v; 

	for(i_=0; i_<m ; i_++) {
		scanf("%d %d", &u, &v); 
		adymat[u][v] = TRUE;
		/*adymat[v][u] = TRUE;*/
	}

}



/* adyacents  | ¬DI
 * --------------
 * busca en O(n) sobre una fila/columna de la matriz (en caso de Grafo ND) 
 *
 * la implementacion es analoga para sucesores/predecesores (Digrafo )
 */
void adyacents(int u, int size) { 
	int i_;

	for(i_=0; i_<size ; i_++) {
		if ( adymat[u][i_] ) 
			printf("%d ",i_ ); 
	}
	NEWLINE
}


/* addEdge | DI  con la salvedad de que se anade solo (u,v) y no (v,u)
 * --------------
 * modifica una entrada de la matriz en O(1)
 *
 */
void addEdge(int *n_edges) { 
	int u,v; 

	*n_edges += 1; 

	scanf("%d %d", &u, &v); 

	adymat[u][v] = TRUE; 
	/*adymat[v][u] = TRUE; */

}


/* deleteEdge | DI
 * --------------
 * modifica una entrada de la matriz en O(1)
 *
 */
void deleteEdge(int *n_edges) { 
	int u,v; 

	*n_edges -= 1; 

	scanf("%d %d", &u, &v); 

	adymat[u][v] = FALSE; 
	adymat[v][u] = FALSE; 
}



/* addVertex | DI
 * --------------
 * Aumenta el tamano interpretable de la matriz e inicializa
 * el nuevo espacio en O(2n).. se escoge esto a inicializarlo completo
 * al comienzo por evitar usar la cota superior de tamano desde el comienzo
 *
 * 	**Si fuese memoria estatica se necesitaria O( (n+1)^2 ) en tiempo y memoria
 * 	adicionales ###
 */
void addVertex(int *size) {
	int i_; 

	*size += 1;
	
	for(i_=0; i_<*size ; i_++) {
		adymat[ *size ][i_] = FALSE; 	
		adymat[i_][ *size ] = FALSE; 	
	}	
}



/* deleteVertex | DI
 * --------------
 * Si elimino un vertice, coloco FALSE en toda su fila y columna. De seguir
 * esto sin disminuir el # de vertices, puede que si elimino demasiado
 * los algoritmos que recorran la matriz tengan mucho overhead.
 *
 * 	**Si por otro lado, decido reajustar la matriz dinamicamente, la copiare en
 * 	O ( (n-1)^2 ) ###
 *
 */
void deleteVertex(int e, int size) {
	int i_; 

	for(i_=0; i_<size  ; i_++) {
		adymat[i_][e] = FALSE; 	
		adymat[e][i_] = FALSE; 	
	}	
}



/************************* MISCELANEA *************************/ 



/* simmetric | ¬DI
 * --------------
 * Convierte el grafo en su simetrico .. O(n^2)
 *
 * 	Se utiliza malloc por cambio a ultima hora
 */
int ** simmetric(int n) { 
	int i_ , **sim, j_;	

	//space request
	sim = (int**) malloc(sizeof(int*)*n);
	for(i_=0; i_<n ; i_++) 
		sim[i_] = (int*) malloc(sizeof(int)*n); 	

	//initializing
	for(i_=0; i_<n ; i_++) {

		for(j_=0; j_<n ; j_++) 
			sim[i_][j_] = FALSE ;
	}	
	

	//creation
	for(i_=0; i_<n ; i_++) {

		for(j_=0; j_<n ; j_++) {

			if ( adymat[i_][j_] ) { 

				if ( !adymat[j_][i_] && i_ != j_ ) 
					sim[j_][i_] = TRUE; 
				else if ( adymat[j_][i_] && i_ != j_) {
					sim[j_][i_] = TRUE; 
					sim[i_][j_] = TRUE; 
				}
				else
					sim[i_][j_] = TRUE;
			}
		}		
	}


	return sim; 
}


/* complement | ¬DI
 * --------------
 * Halla el grafo complemento dado un grafo .. O(n^2)
 */
int ** complement(int n) { 
	int i_, j_, **comp; 

	//creating
	comp = (int**) malloc(sizeof(int*) * n);
	for(i_=0; i_<n ; i_++) 
		comp[i_] = (int*) malloc( sizeof(int) * n); 	

	//initializing
	for(i_=0; i_<n ; i_++) {

		for(j_=0; j_<n ; j_++) 
			comp[i_][j_] = FALSE ;
	}	
	

	for(i_=0; i_<n ; i_++) {

		for(j_=0; j_<n ; j_++) 
			if (i_ != j_ ) 
				comp[i_][j_] = (adymat[i_][j_] && i_ != j_)? FALSE: TRUE; 
			else 	
				comp[i_][j_] = adymat[i_][j_]; 
		}


	return comp;
}



int main(int argc, char** argv) { 
	int adymat[MAXSIZE][MAXSIZE], n, m, i_, j_;


	scanf("%d %d", &n, &m) ; 
	init(n);
	create(m); 

	print(n); 
	NEWLINE

	printf("adyacentes de 3: ");
	adyacents(3, n); 
	NEWLINE

	printf("anadiendo arco: "); 
	addEdge(&m); 
	print(n);
	NEWLINE

	printf("anadiendo vertice: \n"); 	
	addVertex(&n);
	print(n); 
	NEWLINE

	printf("matriz simetrica:\n");
	int **sim; 
	sim = simmetric(n); 

	for(i_=0; i_<n ; i_++) {
		for(j_=0; j_<n ; j_++) 
			printf("%d ",sim[i_][j_] ); 	
		NEWLINE
	}	

	printf("matriz complemento:\n"); 
	int **comp ;
	comp = complement(n);

	for(i_=0; i_<n ; i_++) {
		for(j_=0; j_<n ; j_++) 
			printf("%d ", comp[i_][j_] ); 	
		NEWLINE
	}	

	return 0; 
}
