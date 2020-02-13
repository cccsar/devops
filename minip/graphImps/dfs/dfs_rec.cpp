#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<set> 
#include<vector>
#include<deque>
#include<stack>
#include<queue>
#include<utility>
#include<list>
#include<climits> 

using namespace std; 

#define FOR(u,l) for(int i=l; i<u; i++) 
#define ROF(l,u) for(int i=u; i>l-1; i--) 
#define ri(c) scanf("%d",&c)
#define rii(c,cc) scanf("%d %d", &c, &cc)
#define riii(c,cc,ccc) scanf("%d %d %d", &c, &cc, &ccc)
#define rw(s) scanf("%s",&s)

typedef pair <int, int> pi; 
typedef pair <int, pair<int, int> > pii;
typedef vector< int > vi;
typedef vector< vi > adl; 
typedef vector< pi > vii; 
typedef vector< vii > wadl; 
typedef vector< list<int> > myst; 

#define MAXSIZE 200

void addEdge(adl &graph, int u, int v) { 
	graph[u].push_back(v); 
}


void dfs_rec(adl &graph, int vtd[], int r) { 

	for (int k: graph[r]) { 
		if ( vtd[k] == -1 ) { 
			vtd[k] = r; 
			dfs_rec(graph, vtd, k);
		}
	}
}

//Algorithm to recover path: goes throug each depth first tree in inverse order and
//pushes to a stack the found nodes. Then it prints them .
void rec_path(int vtd[], int size) { 
	int i_, j_, k , path_count; 
	stack<int> *recovered = new stack<int>[size]; 
	path_count = 0;

	for(i_=0; i_<size ; i_++) {
		
		if (vtd[i_] != -1) { 
			path_count++; 
			k = i_; 

			while ( k != vtd[k] ) { 
				recovered[i_].push(k); 
				k = vtd[ k ] ; 
			}
			recovered[i_].push(k);
			
		}
	}

	for(i_=0; i_<path_count ; i_++) {
		while(! recovered[i_].empty() ) {
			cout<<recovered[i_].top()<<" ";	
			recovered[i_].pop(); 
		}		
		cout<<endl; 
	}	

}


// ###PROBAR MAS
int main() 
{
	int n, m, i_, j_, u, v; 
	int visited[MAXSIZE];
	adl graph; 

	rii(n,m); 
	graph.reserve(MAXSIZE); 

	for (i_=0 ; i_<n ; i_++)  
		visited[i_] = -1; 
	visited[0] = 0;


	for (i_=0 ; i_<m ; i_++) { 
		rii(u,v); 
		addEdge(graph, u, v); 
	}
	
	dfs_rec(graph, visited, 0);

	//Aqui se calculan los caminos recorridos
	cout<<"recovered paths"<<endl; 
	rec_path(visited, n); 

	return 0; 
}
