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

#define NONE -1
#define MAXEDGES 1000

#define NEWLINE printf("\n");

int sidearr[2][MAXEDGES];

	/* Implementacion de arreglo de lados para grafos no dirigidos
	 * Se asume que -1 es un valor de vertice no valido
	 * tambien se asume tamano maximo de la estructura y la estructura
	 * se hace global
	 */



/* Init | DI
 * --------------
 * Da valores iniciales a la estructura
 */
void init (int m) {
	int i_; 	
		for (i_= 0; i_<m ; i_++) { 
		sidearr[0][i_] = NONE; 
		sidearr[1][i_] = NONE; 
	}
}


/* create | DI
 * --------------
 * recibe de stdin los datos para llenar la estructura.
 * En este caso, n no es estrictamente necesario.
 */
void create (int m) { 
	int i_, u, v, count; 
	
	count = 0; 
	for (i_= 0; i_<m ; i_++) { 
		scanf("%d %d", &u, &v); 

		sidearr[0][count] = u; 
		sidearr[1][count] = v; 
		count ++ ;
	}

}


/* print | DI
 * --------------
 * duh
 */
void print(int m) { 
	int i_; 

	for (i_= 0; i_<m ; i_++) { 

		if ( sidearr[0][i_] != NONE) { 
			printf("edge %d: ", i_); 
			printf("%d ", sidearr[0][i_] ) ;
			printf("%d \n", sidearr[1][i_] ) ;
		}
	}
}





/* search -- auxiliar
 * --------------
 * busqueda lineal sobre un arreglo auxiliar para contar los vertices.. O(k)
 *
 * Se puede mejorar utilizando como est: 
 * 	thash: Costo de insercion y consulta O( k ) con k factor de carga
 *
 * 	bst balanceado: Costo de insercion y consulta O( log(k) ), con
 * 	k el tamano actual de la estructura
 */
int search(int *arr, int e, int size) { 
	int i_; 

	for (i_= 0 ; i_< size ; i_++) { 

		if ( e == arr[i_] )
			return FALSE ;
	}
	
	return TRUE; 
}


/* append -- auxiliar
 * --------------
 * Modifica la siguiente direccion de memoria no usada de un arreglo
 * auxiliar.. O(1)
 */
void append(int *arr, int e, int *size) { 
	arr[ *size ] = e; 
	*size += 1; 
}


/* nVertex  | DI
 * --------------
 * Calcula el numero de vertices del grafo. Se implementa por asumir
 * que la estructura no los recibe para definirse.
 *
 * 	O( 2m*(2m+1)/2 ) => O(m^2) 
 *
 */
int nVertex(int m) {  
	int count, *found , fcurrent, scurrent , i_;  

	found = (int*) malloc( 2 * MAXEDGES * sizeof(int)  ) ;
	count = 0; 

	for (i_= 0 ; i_< m ; i_++) {  //O(m)

		//verifico que sea una arista/arco valido 
		if ( sidearr[0][i_] != NONE)  {
			fcurrent = search( found, sidearr[0][i_], count) ; 

			if ( fcurrent )
				append(found, sidearr[0][i_], &count);  

			scurrent = search( found, sidearr[1][i_], count) ; 
	
			if ( scurrent ) 
				append(found, sidearr[1][i_], &count); 
		}
	}

	printf("Vertices: "); 
	for (i_= 0 ; i_<count ; i_++)  
		printf("%d ",found[i_]); 
	NEWLINE

	return count; 
}


/* nEdges | DI
 * --------------
 * Consulta de # de arcos/aristas.. O(1)
 */
int nEdges(int m) {
	return m; 	
}


/* addEdge | DI
 * --------------
 * Como es un arreglo de lados y se asume un maximo de arcos/aristas posibles
 * anadir una arista nueva es escribir en un posicion de memoria O(1)
 *
 * De utilizar un arreglo dinamico deberia copiarse la estructura haciendo realloc
 * lo que cuesta O(2*(m + 1)) en tiempo
 */
void addEdge(int *m, int *rsize) { 
	int u, v; 

	scanf("%d %d", &u, &v); 
	sidearr[0][*m] = u; 
	sidearr[1][*m] = v; 

	*m += 1; 
	*rsize = *m;
}


/* deleteEdges | DI
 * --------------
 * Se marca el lado como no valido.
 * Se evita disminuir el tamano puesto que se necesita recorrer la estructura
 * y no necesariamente se elimina siempre el ultimo, en cambio, se disminuye
 * el tamano "real" de la estructura
 *
 */
void deleteEdge(int ind, int *realsize) { 
	sidearr[0][ind] = NONE; 
	sidearr[1][ind] = NONE; 

	*realsize -= 1;
}



/* adyacents | ¬DI .. sus equivalentes en digrafos son predecesores y sucesores
 * --------------
 * adyacentes a un vertices.. O (2*m)
 *
 * 	**predecesores y sucesores se calculan en O(m)
 */
void adyacents(int m, int e) { 
	int i_, ady[m], count; 	
		
	count = 0;

	for(i_=0; i_<m ; i_++) {
		if ( sidearr[0][i_] == e) {  
			ady[count] = sidearr[1][i_];
			count++; 
		}
		if ( sidearr[1][i_] == e && sidearr[0][i_] != e )  { 
			ady[count] = sidearr[0][i_];
			count++; 	
		}
	}	

	for(i_=0; i_<count ; i_++) 
		printf("%d ",ady[i_]);
	NEWLINE
}

/******************** MISCELANEA ********************/ 

int **simmetric(int m) { 
	int i_, **sim; 

	sim = (int**) malloc(sizeof(int*)*2);
	
	sim[0] = (int*) malloc(sizeof(int) * m) ; 
	sim[1] = (int*) malloc(sizeof(int) * m) ; 

	for(i_=0; i_<m ; i_++) {
		sim[0][i_] = sidearr[1][i_] ;
		sim[1][i_] = sidearr[0][i_] ;
	}	

	return sim;
}


int main (int argc, char **argv) { 
	int n, m, i_, realsize; 

	scanf("%d %d", &n, &m); 
	realsize = m; 

	init(m); 
	create(m); 

	print(m); 
	printf("Numero de arcos: %d\n", nEdges(realsize)); 
	printf("Numero de vertices: %d \n", nVertex(m)) ; 
	NEWLINE

	printf("Anadiendo edges: "); 
	addEdge(&m, &realsize); 

	print(m); 
	printf("Numero de arcos: %d\n", nEdges(realsize)); 
	printf("Numero de vertices: %d \n", nVertex(m)) ; 
	NEWLINE

	printf("Eliminando arco 2 ");
	NEWLINE
	deleteEdge(2, &realsize);

	print(m); 
	printf("Numero de arcos: %d\n", nEdges(realsize)); 
	printf("Numero de vertices: %d \n", nVertex(m)) ; 
	NEWLINE

	printf("adyacentes de 2: \n");
	adyacents(m, 2); 
	NEWLINE

	printf("simetrico de un grafo dirigido: \n");
	int **sim; 
	sim = simmetric(m); 	
	for(i_=0; i_<m ; i_++) { 
		if ( sim[0][i_] != NONE) 
			printf("edge %d: %d %d\n", i_, sim[0][i_], sim [1][i_]);
	}


	return 0; 
}

	/*tc*/
	/*4 4*/
	/*1 2*/
	/*2 3*/
	/*3 4*/
	/*4 1*/

