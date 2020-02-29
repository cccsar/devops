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
//Implementation for ndirected graphs
//
void addWEdge(vii graph[], int u, int v, int w) { 
	pi help ;

	help.first = w; 
	help.second = v;

	graph[u].push_back(help); 

	help.second = u; 

	graph[v].push_back(help);
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


void bf(vii graph[], int *cost, int *parent, int source, int size) { 
	parent[ source ] = source;
	int i_, count = 0; 
	bool cond = true; 
	//the condition cuts the while when no changes are made, thus saving
	//iterations

	cost[ source ] = source ;

	while (count < size && cond) { 
		
		cond = false; 
		for(i_=0; i_<size ; i_++) { //this two loops make sure every edge 
			for(pi current: graph[i_]) { //is traversed

				if ( cost[ current.second ] > cost[i_] + current.first) { 

					cost[current.second] = cost[i_] + current.first; 
					parent[ current.second ] = i_;
					cond = true; 
				}
			}
		}	
		count += 1;
	}

	//### yet to put the negative cycle detection

}


int main() 
{
	int i_, n, m, root; 
	int cost[MAXSIZE], parent[MAXSIZE];
	vii *graph = new vii[MAXSIZE]; 

	readWGraph(graph, &n, &m); 

	for(i_=0; i_<n ; i_++) {
		cost[i_] = INT_MAX;	
		parent[i_] = -1; 
	}

	ri( root ) ;

	bf(graph, cost, parent, root, n);

	recoverPath(cost, parent, n);

	return 0; 
}
