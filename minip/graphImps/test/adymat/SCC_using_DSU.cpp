#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<set> 
#include<vector>
#include<deque>
#include<stack>
#include<queue>
#include<utility>
#include<climits> 
#include<cassert>
#include"graph.h" 

#define FOR(u,l) for(int i=l; i<u; i++) 
#define ROF(l,u) for(int i=u; i>l-1; i--) 
#define ri(c) scanf("%d",&c)
#define rii(c,cc) scanf("%d %d", &c, &cc)
#define riii(c,cc,ccc) scanf("%d %d %d", &c, &cc, &ccc)
#define rw(s) scanf("%s",&s)
#define vi vector< int > 
#define vii vector< pair<int, int> >  
#define viii vector< int, pair<int, int> >
#define pi pair <int, int> 
#define pii pair <int, pair<int, int> > 
#define adl vector< vi > 
#define wadl vector< vii > 
#define adym vector< vector< bool > > 

using namespace std; 

	/*Counts number of strongly connected componets for a given directed graph*/


int myFind(int *parents, int e) {
	int dummie; 

	dummie = e; 

	while( parents[dummie] != -1 ) 
		dummie = parents[dummie]; 	

	if (dummie != e) 
		parents[e] = dummie; 

	return dummie; 
}	


int myFind(int *parents, int *rank, int x, int y, int *size) {
	int repx, repy; 

	repx = myFind(parents, x); 
	repy = myFind(parents, y) ;

	if ( repx != repy) { 

		if ( rank[ repx ] >= rank[ repy ] ) {
			parents[ repy ] = repx ;

			if ( rank[ repx ] == rank[ repy ] )
				rank[ repx ] += 1; 
		}
		else  {
			parents[ repx ]  = repy; 
		}

		*size -= 1; 
	}

}


void traverseAndJoin(Digraph *mat, int *parents, int *rank, int *size) {
	int i_, j_; 

	for(i_=0; i_<mat->VSize() ;  i_++) {
	
		for(j_=i_+1; j_<mat->ESize() ; j_++) {

			if ( mat->isEdge(i_,j_) && mat->isEdge(j_,i_) ) 
				myFind(	parents, rank, i_, j_, size); 
		}		
	}
}


int main() 
{
	int n, m, i_, j_; 
	int *parents, *rank, size;
	rii(n,m) ;

	//memory allocation + initialization
	Digraph *gg = new Digraph(n,m); 
	parents = (int*) malloc( sizeof(int)*n); 
	rank = (int*) malloc( sizeof(int)*n); 

	for(i_=0; i_<n ; i_++) {
		rank[i_] = 0; 
		parents[i_] = -1; 	
	}	
	size = n ;

	gg->init(); 
	gg->roywarshall(); 
	traverseAndJoin(gg, parents, rank, &size); 
	

	cout<<"Reach:" <<endl; 
	gg->print(); 
	cout<<"Number of SCC: "<<size<<endl; 

	return 0; 
}
