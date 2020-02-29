#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<vector>
#include<deque>
#include<stack>
#include<queue>
#include<utility>
#include<climits> 
#include<string.h>
#include<map>

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
	
const int MAXSIZE = 100000;
const int MAXQUERIES = 1000; 

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
		riii(u, v, w); 
		addWEdge(graph, u, v, w) ;
	}	
}


void dijkstra(vii graph[], int *cost, int *parent, int source) { 
	priority_queue< pi, vector< pi >, greater<pi> > next_q; 
	pi dummie, next; 

	parent[ source ] = source; 		//initialize source cost and parent and push it to q'
	cost[ source ] = 0; 

	dummie.first = cost[ source ]; 	
	dummie.second = source; 

	next_q.push( dummie );			//insert root

	while ( ! next_q.empty() ) { 
		dummie = next_q.top();			//get smaller vertix and consider succesors
		next_q.pop() ;
		
		for(pi succ : graph[ dummie.second ]) {
			if(cost[ succ.second ] > cost[ dummie.second ] + succ.first) {	
				cost[ succ.second ] = cost[ dummie.second ] + succ.first;		//relax vertix
				parent[ succ.second ] = dummie.second; 

				next.first = cost[ succ.second ]; 	//push to q the relaxed vertix
				next.second = succ.second; 

				next_q.push( next ) ; 
			}
		}
	}
}


int checkSubPath(int *cost, int *parent, int u, int v) { 	//this is O(V) ~ single elemental path case
	int dummie, pummie, s_cost, d_cost; 
	bool found = false; 

	dummie = v; 
	s_cost = cost[u], d_cost = cost[v] ;

	if ( parent[u] == -1 || parent[v] == -1)
		return -1; 

	while ( dummie != parent[ dummie ] ) { 	//if not enter cost found must be 0
		if (dummie == u ) { 	
			found = true; 
			break; 
		}
		dummie = parent[dummie]; 			
	}

	if ( ! found ) { 
		dummie = u; 
		while ( dummie != parent[ dummie ] ) { 
			if (dummie == v ) { 	
				found = true; 
				break; 
			}
			dummie = parent[dummie]; 			
		}		
	}	

	if (found)  
		return abs(d_cost - s_cost); 	
	return -1; 
}


int main() 
{
	int i_, j_, k_, n, m, t, acum; 
	int parent[MAXSIZE], cost[MAXSIZE], resp[MAXQUERIES] ; 
	string source, dest; 

	pair<string, int> city; 		//pair for dict
	map<string, int> dict; 			//dict of pair for cities
						//it is to be queried each time

	for(i_=0; i_<MAXSIZE ; i_++) {
		cost[i_] = INT_MAX;	
		parent[i_] = -1; 
	}

	vii *graph = new vii[MAXSIZE]; 		
	acum = -1 ;

	ri(t);
	for(i_=0; i_<t ; i_++) {

		ri(n); 
		for(j_=0; j_<n ; j_++) {

			cin>>city.first;  		//read city name and insert on dict
			city.second = j_+1;
			dict.insert(city); 

			ri(m); 	
			int v, c; 
			for(k_=0; k_<m ; k_++) { 	//read info on each succ and update graph
				rii(v, c); 	
				addWEdge(graph, j_, v-1, c);
			}
		}

		int r, s_val, d_val, question; 
		ri(r); 
			//since each reachable vertix from source is given a mincost
			//then if two vertix are on the same branch it is possible 
			//to find mincost among them
		for(k_=0; k_<r ; k_++) {	

			cin>>source>>dest; 			
			s_val = dict[ source ] - 1;
			d_val = dict[ dest ] - 1;	
			
			question = checkSubPath(cost, parent, s_val, d_val); //###which value will i get on first it?

			acum += 1; 
			if (question == -1)  {	//this to avoid repeating much dijstra
				dijkstra(graph, cost, parent, s_val); 
				resp[ acum ] = cost[ d_val ] ; 
			}
			else  {//if not a path already found by dijkstra:
				resp[ acum ] = question; 	
			}
		}
			

		//reset structures

		for(j_=0; j_<n ; j_++) {
			parent[j_] = -1 ;
			cost[j_] = INT_MAX;
			graph[j_].clear();	//###not sure if works 	
		}	
	}

	for(i_=0; i_<=acum ; i_++) {		//print output
		cout<<resp[i_]<<endl; 	
	}

	return 0;
}

