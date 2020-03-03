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

int cost[MAXSIZE]; 
int parent[MAXSIZE] ;
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


void dijkstra(vii graph[],int this_parent[], int this_cost[], int source ) { 
	priority_queue<pi, vector<pi>, greater<pi> > next_q; 
	pi dummie, u; 
	int i_; 

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

				dummie.first = cost[ v.second ] ; 
				dummie.second = v.second;
				
				next_q.push(dummie); 
			}
		}
	}
}



void perro() { 
	int i_, n, m; 
	vii *graph = new vii[MAXSIZE]; 
	
	//readWGraph(graph, &n, &m); 

	for(i_=0; i_<MAXSIZE ; i_++) {
		parent[i_] = -1; 
		cost[i_] = INT_MAX; 	
	}

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
	int dummie_cost[MAXSIZE]; 
	int dummie_parent[MAXSIZE] ;

	for(i_=0; i_<MAXSIZE ; i_++) {
		parent[i_] = -1; 
		dummie_parent[i_] = -1; 
		cost[i_] = INT_MAX; 	
		dummie_cost[i_] = INT_MAX; 
	}

	count = 0;  

	while ( true ) {

		int bc_cost, help, bn_cost, pref, n_pref; 
		bool change; 

		change = false; 

		riii(j, b, c); 
		rii(n, s); 

		if ( j == -1) 
			break; 

	
		readWGraph(graph, s);
		c -=1;
		n -=1;
		b -=1;

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

		while ( help != parent[ help ] ) { 

			for(i_=0; i_<j ; i_++) {
				dummie_cost[i_] = INT_MAX; 
				dummie_parent[i_] = -1; 			
			}

			
			dijkstra(graph, dummie_cost, dummie_parent, help); 

			if ( cost[ help ] + dummie_cost[ help ] == cost[ n_pref ] ) { 
				resp[ count ][0] = cost[ help ] ; 
				resp[ count ][1] = dummie_cost[help] ;  
				resp[ count ][2] = dummie_cost[n_pref] ; 
				change = true;
				break; 
			}

			help = parent[help] ;
		}

		if ( !change ) {
			resp[ count ][0] = cost[ help ] ; 
			resp[ count ][1] = cost[ pref ] ;  
			resp[ count ][2] = cost[ n_pref ] ; 
		}

	
		for (i_=0 ; i_<j ; i_++)   {
			parent[i_] = -1; 
			cost[i_] = INT_MAX; 
			graph[i_].clear(); 	
		}

		count += 1; 
	}

	for (i_=0 ; i_<count ; i_++)  
		cout<<resp[i_][0]<<" "<<resp[i_][1]<<" "<<resp[i_][2]<<endl; 

	return 0; 
}
