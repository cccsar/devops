#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<vector>
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


void Dijkstra(vii graph[], int cost[], int parent[], int source, int size) { 
	priority_queue<pi, vector<pi>, greater<pi> > next_q; 
	pi current, next; 

	cost[ source ] = 0; 	
	parent[ source ] = source; 

	current.first = cost[ source ]; 
	current.second = source; 
	next_q.push( current ) ;	 //push first node to queue (along with its weight) 
	
	while ( !next_q.empty() )  { 

		current = next_q.top(); //pop node with smallest cost
		next_q.pop(); 	

		for ( pi succ : graph[ current.second ] ) { //visit each successor of popped node
			//if its current cost is greater than the cost of source node plus edge
			//update its cost and push it to the queue
			if ( cost [ succ.second ] > cost [ current.second ] + succ.first ) { 
				cost [ succ.second ] = cost [ current.second ] + succ.first; //update cost
				parent[ succ.second ] = current.second; //update parent

				next.first = cost[ succ.second ] ; 
				next.second = succ.second ; 

				next_q.push( next ); // add succ to q
			}
		}

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


void dbg(int *cost, int *parent, int size) { 
	int i_;

	cout<<"Cost"<<endl; 
	for(i_=0; i_<size ; i_++) {
		cout<<cost[i_]<<" ";
	}	
	cout<<endl; 

	cout<<"Parents: "<<endl; 
	for(i_=0; i_<size ; i_++) {
		cout<<parent[i_]<<" ";
	}	
	cout<<endl; 
}

int main() 
{
	int i_, n, m, root;
	int cost[MAXSIZE], parent[MAXSIZE]; 
	vii *graph = new vii[MAXSIZE]; 

	readWGraph(graph, &n, &m); 

	for (i_=0 ; i_<n ; i_++) { 
		cost[i_] = INT_MAX; 
		parent[i_] = -1; 
	}	

	ri( root ); 

	Dijkstra(graph, cost, parent, root, n);
	recoverPath(cost, parent, n);
	

	return 0; 
}
