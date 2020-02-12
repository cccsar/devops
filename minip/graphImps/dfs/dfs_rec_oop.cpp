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

typedef pair <int, int> pi; 
typedef pair <int, pair<int, int> > pii;
typedef vector< int > vi;
typedef vector< vi > adl; 
typedef vector< pi > vii; 
typedef vector< vii > wadl; 



class Graph { 
private:
	int n, m; 

public: 
	adl graph; 
	Graph(int E, int V) { 
		n = V; 
		m = E; 
		
		graph.reserve(n) ; 
	}

	void addEdge(int u, int v) { 
		graph[u].push_back(v); 
		graph[v].push_back(u); 
	}


};

void dfs_rec(int p[], int s ) { 

	for (int k: graph[i_]) { 
		if ( p[k] == -1 ) { 
			p[k] = s; 
			dfs_rec(k);
		}
	}
}

int main() 
{
	int n, m, i_, j_, u, v; 

	rii(n,m); 

	Graph *hola = new Graph(n,m); 
	for (i_=0 ; i_<n ; i_++) { 
		hola->graph[i_] = new vector<int>(); 
	}

	for (i_=0 ; i_<m ; i_++) { 
		rii(u,v); 
		hola->addEdge(u,v); 
	}

	
		
	return 0; 
}
