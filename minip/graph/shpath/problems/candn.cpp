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
typedef vector< pii > jic; 
	
const int MAXSIZE = 5000;
const int TEST = 1000;

int bar_cost[MAXSIZE]; 
int bar_parent[MAXSIZE] ;
int nito_cost[MAXSIZE]; 
int nito_parent[MAXSIZE]; 
int charlie_cost[MAXSIZE];
int charlie_parent[MAXSIZE];  

int resp[MAXSIZE][3];

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


void readWGraph(vii graph[], int m) {
	int u, v, w, i_;

	
	for(i_=0; i_<m ; i_++) {
		scanf("%d %d %d", &u, &v, &w); 
		addWEdge(graph, u-1, v-1, w) ;
	}	
}


void printWGraph(vii graph[], int size) { 
	int i_;
	for(i_=0; i_<size ; i_++) {
		for (pi k : graph[i_]) 
			cout<<i_<<" "<<k.second<<" "<<k.first<<endl; 
	}

}


void dijkstra(vii graph[],int this_cost[], int this_parent[], int source ) { 
	priority_queue<pi, vector<pi>, greater<pi> > next_q; 
	pi dummie, u; 

	this_cost[ source ] = 0; 
	this_parent[ source ] = source; 

	dummie.first = this_cost[ source ] ; 
	dummie.second = source; 

	next_q.push(dummie); 

	while ( !next_q.empty() )  { 
		u = next_q.top(); 
		next_q.pop(); 

		for(pi v: graph[ u.second ] ) { 
			if ( this_cost[ v.second ] > this_cost[ u.second ] + v.first ) { //check out this line
				this_cost[ v.second ] = this_cost[ u.second ] + v.first  ; 
				this_parent[ v.second ] = u.second ; 

				dummie.first = this_cost[ v.second ] ; 
				dummie.second = v.second;
				
				next_q.push(dummie); 
			}
		}
	}
}


void reset(int size) { 
	int i_; 
	for (i_=0 ; i_<size ; i_++) { 
		bar_cost[i_] = nito_cost[i_] = charlie_cost[i_] = INT_MAX; 
		bar_parent[i_] = nito_parent[i_] = charlie_parent[i_] = -1; 
	}
}


int pathLength(int some_parent[], int e) { 
	int count, dummie; 

	dummie = e; 
	count = 0; 

	while ( dummie != some_parent[dummie] ) { 
		count += 1; 
		dummie = some_parent[dummie]; 
	}

	return count; 
}


void perro() { 
	int i_, j_, j, b, s;
	vii *graph = new vii[MAXSIZE];


	rii(j, s ); 
	reset( j ) ;

	readWGraph(graph, s); 

	ri(b); 

	dijkstra(graph, bar_cost, bar_parent, b); 

	cout<<"costs:"<<endl; 
	for (i_=0 ; i_<j ; i_++)  
		cout<<bar_cost[i_]<<" "; 
	cout<<endl; 

	cout<<"parent:"<<endl; 
	for (i_=0 ; i_<j ; i_++)  
		cout<<bar_parent[i_]<<" "; 
	cout<<endl; 
	
}


int main() 
{
	int c, n, b, j, s, i_, count, best_path_length, dummie; 
	vii *graph = new vii[MAXSIZE] ; 

	reset( MAXSIZE ) ;
	count = 0;  

	for (i_=0 ; i_<MAXSIZE ; i_++) { 
		resp[i_][0] = INT_MAX; 
	}

	while ( true ) {

		riii(j, b, c); 
		rii(n, s); 

		if ( j == -1) 
			break; 
	
		readWGraph(graph, s); 
		c -=1;
		n -=1;
		b -=1;
	
		dijkstra(graph, bar_cost, bar_parent, b); 	
		dijkstra(graph, nito_cost, nito_parent, n); 	
		dijkstra(graph, charlie_cost, charlie_parent, c); 	

		best_path_length = -1 ; 

		for (i_=0 ; i_<j ; i_++) { 
			if( bar_cost[i_] + nito_cost[i_] == bar_cost[n] &&
					bar_cost[i_] + charlie_cost[i_] == bar_cost[c] ) { 

				dummie = pathLength( bar_parent, i_ ); 

				if ( dummie > best_path_length ) {
					best_path_length = dummie; 
					resp[count][0] = bar_cost[i_] ;
					resp[count][1] = charlie_cost[i_];
					resp[count][2] = nito_cost[i_];
				 }
			}
		}

		reset( j ) ;  	//clear size
		for (i_=0 ; i_<j ; i_++)  
			graph[i_].clear(); 

		count += 1; 
	}

	for (i_=0 ; i_<count ; i_++)  
		cout<<resp[i_][0]<<" "<<resp[i_][1]<<" "<<resp[i_][2]<<endl; 

	return 0; 
}
