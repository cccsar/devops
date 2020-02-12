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

#define MAXSIZE 200

adl graph;

void addEdge(int u, int v) { 
	graph[u].push_back(v); 
	graph[v].push_back(u); 
}

void dfs_rec(int p[], int s ) { 
	int i_; 

	for (int k: graph[i_]) { 
		if ( p[k] == -1 ) { 
			p[k] = s; 
			dfs_rec(p, k);
		}
	}
}


int main() 
{
	int n, m, i_, j_, u, v; 
	int p[MAXSIZE];

	rii(n,m); 
	graph.resize(n); 

	for (i_=0 ; i_<n ; i_++)  
		p[i_] = -1; 
	p[0] = 0;


	for (i_=0 ; i_<m ; i_++) { 
		rii(u,v); 
		addEdge(u,v); 
	}

	dfs_rec(p, 0);
	cout<<"llego"<<endl;


	for (i_=0 ; i_<n ; i_++) 
		cout<<p[i_]<<" "<<endl; 
	cout<<endl; 

	return 0; 
}
