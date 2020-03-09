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

int parent[MAXS]; 
int ranks[MAXS]; 

void addWEdge(vii graph[], int u, int v, int w) { 
	pi dummie; 

	dummie.first = w; 
	dummie.second = v; 	

	graph[u].push_back( dummie ) ; 

}


int myFind(int e) { 
	int dummie; 

	dummie = e; 

	while( parent[dummie] != -1 )  
		dummie = parent[dummie];

	if ( dummie != e ) 
		parent[e] = dummie; 

	return dummie; 
}


bool myUnion(int x, int y) { 
	int rx, ry; 

	rx = myFind(x); 
	ry = myFind(y); 

	if ( rx != ry ) { 
		if ( ranks[ rx ] >= ranks[ ry ] ) { 
			parent[ ry ] = rx ;

			if ( ranks[rx] == ranks[ry] ) 
				ranks[ rx ] += 1;
		}
		else 
			parent[ rx ] = ry; 

		return true; 
	}

	return false;
}


int myKruskal( vii graph[] , int size) { 
	int i_, count; 
	priority_queue< pii, vector<pii>, greater<pii> > my_pq; 
	pii dummie; 

	count = 0;

	for(i_=0; i_<size ; i_++) {
		for(pi k : graph[i_] ) { 
			dummie.first = k.first; 
			dummie.second.first = i_; 
			dummie.second.second = k.second; 

			my_pq.push( dummie ) ; 
		}	
	}	

	while ( ! my_pq.empty() ) { 
		dummie = my_pq.top(); 
		my_pq.pop() ;
		
		if( myUnion( dummie.second.first, dummie.second.second )  )
			count += dummie.first; 
		
	}

	return count; 	
}

int main() 
{
	int n, m, u, v, w, i_; 
	vii *graph = new vii[MAXS];

	for(i_=0; i_<MAXS ; i_++) {
		parent[i_] = -1; 
		ranks[i_] = 0; 	
	}

	rii(n,m); 

	for(i_=0; i_<m ; i_++) {
		riii(u, v, w); 
		addWEdge( graph, u, v, w) ; 	
	}

	cout<< myKruskal(graph, n)<<endl ; 

	return 0; 
}
