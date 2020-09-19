#include<stdio.h> 
#include<iostream> 
#include<vector> 
#include<queue> 

#define MAXS 1000000
#define MAXINT 429496729

using namespace std; 

vector< pair<int, int> > *graph = new vector< pair<int, int> > [MAXS]; 
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > myQ; //Q that organices vertix in topOrd

bool vtd[MAXS]; 
int funct[MAXS];

int cost[MAXS]; 

void bellmanInformed () { 

	cost[myQ.top().second] = 0; // top of the Q is the source

	while ( !myQ.empty() ) {
		for(pair<int, int> ady : graph[ myQ.top().second ] ) // nex vertix to check is given by topOrd
			if ( cost[myQ.top().second] + ady.first < cost[ ady.second] ) 
				cost[ ady.second ] = cost[myQ.top().second] + ady.first; 
		myQ.pop(); 
	}

}

void dfsRec (int source, int *cnt) { 

	for(pair<int, int> ady : graph[source] ) 
		if(!vtd[ady.second] )  {
			vtd[ady.second] = true; 
			dfsRec(ady.second, cnt);
		}

	myQ.push( {*cnt, source} ); 
	*cnt -=1; 
}

int main () { 
	int n,m, u,v,w; 

	scanf("%d %d",&n,&m); 

	for(int i=0; i<n; i++) { 
		vtd[i] = false; 
		cost[i] = MAXINT; 
	}

	for(int i=0; i<n; i++) { 
		scanf("%d %d %d",&u, &v,&w); 
		graph[u].push_back ( {w, v} ) ;
	}

	int cnt = n; 
	dfsRec(0, &cnt);

	while( !myQ.empty() ) { 
		printf("%d ",myQ.top().second) ; 
		myQ.pop(); 
	}
	cout<<endl; 

//	bellmanInformed(); 
//
//	for(int i=0 ;i<n; i++) printf("%d ",cost[i]); 
}
