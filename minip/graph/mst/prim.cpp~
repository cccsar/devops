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
	
const int MAXS = 1000;

int visited[MAXS] ;


void addWEdge(vii graph[], int u, int v, int w ) { 
	pi perico = { w, v }; 

	graph[u].push_back( perico ) ;

	perico.second = u; 

	graph[v].push_back( perico ) ; 
}


int myPrim(vii graph[], int root, int size) { 
	int mincost, count; 
	priority_queue< pi, vector<pi>, greater<pi> > my_pq; 
	pi dummie; 

	my_pq.push( {0, root} ); 

	count = 0; 
	mincost = 0; 
	
	while ( !my_pq.empty() && count < size - 1 ) {
		dummie = my_pq.top(); 
	       	my_pq.top(); 
		
		//De facto error, it won't enter on first iteration
		if (visited[ dummie.second ] > dummie.first) { 	//if not visisted check successors

			visited[ dummie.second ] = dummie.first ;
			count += 1 ;
			mincost += dummie.first ; 

			for(pi k : graph[dummie.second]) { 

				if ( visited[k.second] > k.first)  	//if sucessor not visited, push it
					my_pq.push( k ) ; 
			}
		}

	}

	return mincost; 
}


int main() 
{
	int n, m, a, b, c, i_; 
	vii *graph = new vii[MAXS]; 

	rii(n,m); 
	for(i_=0; i_<MAXS ; i_++) {
		visited[i_] = INT_MAX; 	
	}

	for(i_=0; i_<m ; i_++) {
		rii(a,b); 	
		addWEdge(graph, a, b, c); 
	}

	cout<<myPrim(graph, 0, n)<<endl; 

	return 0; 
}
