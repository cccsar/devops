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

using namespace std; 

#define FOR(u,l) for(int i=l; i<u; i++) 
#define ROF(l,u) for(int i=u; i>l-1; i--) 
#define ri(c) scanf("%d",&c)
#define rii(c,cc) scanf("%d %d", &c, &cc)
#define riii(c,cc,ccc) scanf("%d %d %d", &c, &cc, &ccc)
#define rw(s) scanf("%s",&s)

typedef vector< int > vi; 
typedef vector< pair<int, int> >  vii; 
typedef vector< int, pair<int, int> >viii; 
typedef pair <int, int> pi; 
typedef pair <int, pair<int, int> > pii; 
typedef vector< vi > adl; 
typedef vector< vii > wadl; 
	
#define MAXSIZE 1000


bool reachm[MAXSIZE][MAXSIZE];

void addEdge(vi graph[], int u, int v) { 
	graph[u].push_back(v); 
}


void readGraph(vi graph[], int *n, int *m) { 
	int i_, u, v; 
	rii(*n, *m); 

	for(i_=0; i_<*m ; i_++) {
		rii(u,v); 
		addEdge(graph, u, v); 
	}
}


//creates an adyacency matrix based on an adyancy list
void createMat(vi graph[], int size) { 
	int i_; 	
	for(i_=0; i_<size ; i_++) {
		for(int j_ : graph[i_] ) 
			reachm[i_][j_] = true;
	}

}


//debugging for adyacency matrix 
void printMat(int size) {
	int i_, j_; 

	for(i_=0; i_<size ; i_++) {
		for(j_=0; j_<size ; j_++) 
			cout<<reachm[i_][j_]<<" "; 	
		cout<<endl; 
	}
}


//debugging for adyacency list
void printAdyl(vi graph[], int size) { 
	int i_; 

	for(i_=0; i_<size ; i_++) {
		for(int k : graph[i_] ) 
			cout<<i_<<" "<<k<<endl;
	}

}


//DFS REACH
void reach(vi graph[], int u, int v) { 
	reachm[u][v] = true; 
	
	for (int w : graph[v] ) {
		if ( ! reachm[u][w] )
			reach(graph, u, w) ; 
	}
}


//ROY WARSHALL for comparison with bfs reach algorithm
void royWarshall(int size) { 
	int i_, j_, k_; 

	for(i_=0; i_<size ; i_++) 
		reachm[i_][i_] = true;

	for(k_=0; k_<size ; k_++) {
		for(i_=0; i_<size ; i_++) {
			if ( reachm[i_][k_] && i_!= k_) { 
				for(j_=0; j_<size ; j_++) {
					reachm[i_][j_] = reachm[i_][j_] || reachm[k_][j_];
				}		
			}
		}		
	}

}


int main() 
{
	int i_,  n, m; 
	vi *graph = new vector<int>[MAXSIZE];

	readGraph(graph, &n, &m) ;


	for(i_=0; i_<n ; i_++) 
		reach(graph, i_, i_);
	
	//createMat(graph, n); 
	//royWarshall(n); 


	printMat(n); 
	//printAdyl(graph, n);
	//printMat(graph); 

	return 0; 
}
