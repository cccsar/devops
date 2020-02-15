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


#define FOR(u,l) for(int i=l; i<u; i++) 
#define ROF(l,u) for(int i=u; i>l-1; i--) 
#define ri(c) scanf("%d",&c)
#define rii(c,cc) scanf("%d %d", &c, &cc)
#define riii(c,cc,ccc) scanf("%d %d %d", &c, &cc, &ccc)
#define rw(s) scanf("%s",&s)
#define vi vector< int > 
#define vii vector< pair<int, int> >  
#define viii vector< int, pair<int, int> >
#define pi pair <int, int> 
#define pii pair <int, pair<int, int> > 
#define adl vector< vi > 
#define wadl vector< vii > 

using namespace std; 

#define MAXS 2000

bool resp[MAXS];
int degrees[MAXS]; 

bool isEulerian(adl &graph, int *root) { 
	int i_, count; 

	for(i_=0; i_<graph.size(); i++) {
		degrees[i_] = graph[i_].size(); 
		if ( graph[i_].size()%2 == 1 ){
			count++; 
			*root = i_; 
		}
	}

	//if only two vertix have odd degre, then the graph is possibly an eulerian cicle
	//	errors: N = 2, 
	if(count != 2)
		return false; 

	return true; 
}


void adyacents(adl &graph, int e) {
	
}

void insert(adl &graph, int u, int v) { 
	ib primo, secondo; 
	
	primo.first = secondo.first = false; 
	primo.second = u; 
	secondo.second = v;

	graph[u].push_back(primo); 
	graph[v].push_back(secondo); 
}

void efs(adyl &graph, int r){

}; 

int main() 
{
	int q, i_, j_, n, m, u, v; 
	adl graph; 

	graph.resize(MAXS); 
	ri(q)
	for(i_=0; i_<q ; i_++) {
		rii(n,m); 

		for(j_=0; j_<m ; j_++) {
			rii(u,v); 
			insert(graph, u, v) ; 	
		}		

		if (!isEulerian) 
			resp[i_] = false; 
		else { 

		}
	}
}




	return 0; 
}
