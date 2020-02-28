#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<vector>
#include<stack>
#include<queue>
#include<utility>


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

//Implementation for directed graphs
//
void addWEdge(vii graph[], int u, int v, int w) { 
	pi help ;

	help.first = w; 
	help.second = v;

	graph[u].push_back(help); 
}


void readWGraph(vii graph[], int *n, int *m ) { 
	int u, v, w, i_;

	rii(*n,*m); 
	
	for(i_=0; i_<*m ; i_++) {
		scanf("%d %d %d", &u, &v, &w); 
		addWEdge(graph, u, v, w) ;
	}	
}


void printWGraph(vii graph[], int size) { 
	int i_;
	for(i_=0; i_<size ; i_++) {
		for (pi k : graph[i_]) 
			cout<<i_<<" "<<k.second<<" "<<k.first<<endl; 
	}

}


void Dijkstra(vii graph[], int size, vi &cost, vi &parents) { 
	priority_queue<pi> set; 
	
	
}

int main() 
{
	int i_, n, m; 
	vii *graph = new vii[MAXSIZE]; 
	vi cost, parents; 

	cost.reserve(MAXSIZE); 
	parents.reserve(MAXSIZE); 

	for (i_=0 ; i_<n ; i_++) { 

	}	

	return 0; 
}
