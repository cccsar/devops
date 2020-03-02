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
	
const int MAXSIZE = 5000;
const int TEST = 1000;

int cost[MAXSIZE]; 
int dummie_cost[MAXSIZE]; 
int parent[MAXSIZE] ;
int dummie_parent[MAXSIZE] ;
int resp[MAXSIZE];

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


void printWGraph(vii graph[], int *parent, int *cost, int size) { 
	int i_;
	for(i_=0; i_<size ; i_++) {
		for (pi k : graph[i_]) 
			cout<<i_<<" "<<k.second<<" "<<k.first<<endl; 
	}

}


void dijkstra(vii graph[],int *parent, int *cost, int source ) { 
	priority_queue<pi> next_q; 
	pi dummie, u; 

	cost[ source ] = 0; 
	parent[ source ] = source; 

	dummie.first = cost[ source ] ; 
	dummie.second = source; 

	next_q.push(dummie); 

	while ( !next_q.empty() )  { 
		u = next_q.top(); 
		next_q.pop(); 

		for(pi v: graph[ u.second ] ) { 
			if ( cost[ v.second ] > cost[ u.second ] + v.first ) { 
				cost[ v.second ] = cost[ u.second ] + v.first  ; 
				parent[ v.second ] = u.second ; 

				dummie.first = cost[ v.second ] ; 
				dummie.second = v.second;
				
				next_q.push(dummie); 
			}
		}
	}
}


void resetArrays(int *parent, int *cost, int size) { 
	int i_; 
	
	for (i_=0 ; i_<size ; i_++) { 
		parent[i_] = -1; 
		cost[i_] = INT_MAX; 
	}
}

void perro() { 
	int i_, n, m; 
	vii *graph = new vii[MAXSIZE]; 
	
	readWGraph(graph, &n, &m); 

	resetArrays(parent, cost, n); 

	dijkstra(graph, parent, cost, 0) ;
	cout<<"Costo: "<<endl; 
	for (i_=0 ; i_<n ; i_++) { 
		cout<<cost[i_]<<" "; 
	}	
	cout<<endl;
	cout<<"Parents: "<<endl; 
	for (i_=0 ; i_<n ; i_++) { 
		cout<<parent[i_]<<" "; 
	}	
	cout<<endl;

	//return 0; 
}

int main() 
{
	int c, n, b, j, s, i_, j_, u, v, w, count; 
	vii *graph = new vii[MAXSIZE] ; 

	resetArrays(parent, cost, MAXSIZE);
	resetArrays(dummie_parent, dummie_cost, MAXSIZE); 

	count = 0;  

	while ( true ) {

		int bc_cost, help, bn_cost, pref, n_pref; 

		riii(j, b, c); 
		rii(n, s); 

		if ( j == -1) 
			break; 
	
		for (i_=0 ; i_<s ; i_++)  
			readWGraph(graph, &j, &s );


		dijkstra(graph, parent, cost, b);//calculate mincost from bar to each vertix and keep cost and forest info 

		bc_cost = cost[ c ]; 
		bn_cost = cost[ n ] ;

		pref = ( min(bc_cost, bn_cost) == bc_cost )? c: n; 
		n_pref = ( pref == c )? n: c; 

		help = pref; 
	
					//then run dijstra from charlie's (could also be nito)
					//house and through each vertix w on charlie's dijtra forest, run dijstra
					//then compare a = cost[w] + dummie_cost[c] with b = cost[c] and when a goes
					//greater ( or equal ... ) than a, break
					//
		cout<<"fuera"<<endl;			
		while ( help != parent[ help ] ) { 
			
			dijkstra(graph, dummie_cost, dummie_parent, help); 

			if ( cost[ help ] + dummie_cost[ help ] == cost[ n_pref ] ) { 
				resp[ count ] = cost[ help ] ; 
			}

			resetArrays(dummie_cost, dummie_parent, j); 		//reset size for following dijstra

			help = parent[help] ;
			cout<<"llego\n";
		}

	
		resetArrays(cost, parent, j); 		//clearing
		for (i_=0 ; i_<j ; i_++)  
			graph[i_].clear(); 	

		count += 1; 
	}


	for (i_=0 ; i_<count ; i_++) { 
		cout<<resp[i_]<<endl; 
	}

	return 0; 
}
