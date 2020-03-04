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
	
const int MAXSIZE = 1000; 

int adymat[MAXSIZE][MAXSIZE] ;
int pathmat[MAXSIZE][MAXSIZE]; 

//consider ndirected graph
void addWedge(int graph[][MAXSIZE],int paths[][MAXSIZE], int u, int v, int w) {
	graph[u][v] = w; 
	paths[u][v] = u; 
}

void readWGraph(int graph[][MAXSIZE],int paths[][MAXSIZE], int *n, int *m) { 
	int i_, u, v, w, test; 

	test = rii(*n,*m); 
	for(i_=0; i_<*m ; i_++) {
		riii(u,v,w); 
		addWedge(graph, paths, u, v, w); 
	}	

}



void initMats(int graph[][MAXSIZE], int paths[][MAXSIZE], int size)  {
	int i_, j_; 

	for(i_=0; i_<size ; i_++) {
		for(j_=0; j_<size ; j_++) {
			graph[i_][j_] = (i_==j_)? 0: INT_MAX; 
			paths[i_][j_] = INT_MAX; 
		}	
	}
}

void recoverPath(int cost[],int parent[], int size) { 
	int i_, j_, dummie;
	stack<int> *paths = new stack<int>[size]; 
	vector<int> valid; 


	for(i_=0; i_<size ; i_++) {
		
		if (parent[i_] != -1) {
			valid.push_back(i_);
			dummie = i_;	
			while( dummie != parent[ dummie ] ) { 
				paths[i_].push( dummie ) ; 
				dummie = parent[ dummie ];	
			}	
			paths[i_].push( dummie );
		}
	}		


	for(int k : valid)  {
		while( ! paths[k].empty() ) {
			cout<<paths[k].top()<<" "; 
			paths[k].pop();
		}		
		cout<<endl;
	}
}

void floydWarshall(int graph[][MAXSIZE], int paths[][MAXSIZE], int size) { 
	int i_, j_, k_; 

	for(k_=0; k_<size; k_++) {
		for(i_=0; i_<size ; i_++) {
			if ( graph[i_][k_] < INT_MAX && i_ != k_ ) { 
				for(j_=0; j_<size ; j_++) {
					
					if ( graph[i_][j_] > graph[i_][k_] + graph[k_][j_] ) {
						graph[i_][j_] = graph[i_][k_] + graph[k_][j_] ;
						paths[i_][j_] = paths[k_][j_] ; 
					}
				}	
			}
		}	
	}
}


void printMats(int graph[][MAXSIZE], int paths[][MAXSIZE], int size) {
	int i_, j_; 

	cout<<"Costs: "<<endl; 
	for(i_=0; i_<size ; i_++) {
		for(j_=0; j_<size ; j_++) {
			if ( graph[i_][j_] == INT_MAX ) 
				cout<<"/ "; 
			else
				cout<<graph[i_][j_]<<" "; 
		}	
		cout<<endl; 
	}	
	cout<<"Paths: "<<endl; 
	for(i_=0; i_<size ; i_++) {
		for(j_=0; j_<size ; j_++) {
			if ( paths[i_][j_] == INT_MAX ) 
				cout<<"/ "; 
			else
				cout<<paths[i_][j_]<<" "; 
		}	
		cout<<endl; 
	}	
}


int main() 
{
	int n, m; 

	initMats(adymat, pathmat, MAXSIZE) ;  


	readWGraph(adymat, pathmat, &n, &m); 

	floydWarshall(adymat, pathmat, n); 

	printMats(adymat, pathmat, n) ;

	return 0; 
}
