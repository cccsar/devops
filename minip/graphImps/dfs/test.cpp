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


	
using namespace std; 

adl graph;

void addEdge(int u, int v) { 
	graph[u].push_back(v); 
	graph[v].push_back(u); 
}

void print(int size) { 
	int i_,j_; 

	for (i_=0 ; i_<size ; i_++) { 
		for (j_=0 ; j_<graph[i_].size() ; j_++) { 
			cout<<i_<<" "<<graph[i_][j_]<<endl; 
		}
	}

}

int main() 
{
	int i_, j_, u, v, n, m; 

	rii(n,m); 

	graph.resize(n); 

	for (i_=0 ; i_<m ; i_++) { 
		rii(u,v); 
		addEdge(u,v); 
	}

	print(n); 

	return 0; 
}
