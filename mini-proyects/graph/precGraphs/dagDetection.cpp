#include <stdio.h> 
#include <iostream> 
#include <vector> 
#include <climits> 


#define MAXS 10000000
#define MAXINT 2147483647 


using namespace std; 

typedef vector<int> vi ;

vi *graph = new vi[MAXS]; 
int cost[MAXS], parent[MAXS]; // for bellman

int disc[MAXS], term[MAXS]; // for dfs visit
bool vtd[MAXS]; 

bool bellman(int source, int size){ //cycle detection and partition by level in digraph
	int cnt = 0; 
	bool change = true; 

	cost[source] = 0 ;
	parent[source] = source; 

	while ( cnt != size && change ) { 

		change = false; 

		for(int c=0; c<size; c++) 
			for(int r : graph[c] ) 
				if ( cost[c] + 1 > cost[r] && ((cost[c] != -1)  ^ (cost[r] != -1)) ) {
					cost[r] = cost[c] + 1; 
					parent[r] = c; 

					change = true; 
					cnt +=1; 
				}
	}

	for(int i=0; i<size; i++) {
		for(int j : graph[i]) 
			if ( cost[i] + 1  > cost[j] ) 
				return true; 
	}

	return false; 
}

void dfsRec(int source, int *time, bool *resp) { // cycle detection in digraph
	
	*time +=1; 
	disc[source] = *time ;

	for(int ady : graph[source] ) 
		if (!vtd[ady]) { 
			vtd[ady] = true; 
			dfsRec(ady, time, resp); 	
		}
		else  
			if ( term[ady] == 0 )
				*resp = true;

	*time += 1; 
	term[source] = *time; 

}

int main () { 
	int n,m; 

	scanf("%d %d",&n, &m); 

	for(int i=0; i<n; i++) { 
		cost[i] = -1; parent[i] = i; 
		disc[i] = term[i] = 0; vtd[i] = false; 
	
	} 

	int k = m, u, v; 
	while (k--) { 
		scanf("%d %d",&u, &v); 
		graph[u].push_back( v ); 
	}	

	printf("Bellman: %s\n", ( bellman(0, n) )? "there's a cycle": "there's not a cycle" )  ; 
//	for(int c=0; c<n; c++) printf("%d %d\n",c,cost[c]);  


	bool resp = false; 
	int time = -1; 
	vtd[0] = true; 
	dfsRec(0, &time, &resp); 
	printf("dfs :%s\n", resp?"there's a cycle": "there's not a cycle"); 
}
