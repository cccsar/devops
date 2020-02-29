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
	
int parents[MAXSIZE]; 
int rk[MAXSIZE] ;
int color[MAXSIZE] ;

void adl_insert(adl &graph, int u, int v) { 
	graph[u].push_back(v); 
	graph[v].push_back(u); 
};


//**anadir firma de padres en algun momento
//Dfs implementation to get conex component, use the same color for reachable
//nodes and change color in outer loop
void dfs_rec(adl &graph, int r, int count) { 
	int i_; 
	
	for (i_=0 ; i_<graph[r].size() ; i_++) { 

		if ( parents[ graph[r][i_] ] == -1) { 
			color[ graph[r][i_] ] = count; 
			parents[ graph[r][i_] ] = r; 
			dfs_rec(graph, graph[r][i_], count); 
		}
	}
};


int main() {
	int i_, j_, u, v, n, m , count;
	adl list;
	list.reserve(MAXSIZE);
	rii(n, m);

	for (i_=0 ; i_<n ; i_++)  
		parents[i_] = -1; 


	for (i_=0 ; i_<m ; i_++) { 
		rii(u, v); 
		adl_insert(list, u, v); 
	}
	
	count = 0; 
	for(i_=0; i_<n ; i_++) {
		if (parents[i_] == -1) {
			count ++ ;
			color[i_] = count; 
			parents[i_] = i_;  
			dfs_rec(list, i_, count); 
		}
	}	

	cout<<"CC: ";
	for (i_=0 ; i_<n ; i_++)  
		cout<<color[i_]<<" "; 
	cout<<endl; 	

	return 0; 
}
