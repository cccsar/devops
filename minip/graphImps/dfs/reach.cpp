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
	
#define MAXSIZE 1000


bool reachm[MAXSIZE][MAXSIZE];

void addEdge(adl &list, int u, int v) { 
	list[u].push_back(v); 
}


void reach(adl &list, int u, int v) { 
	reachm[u][v] = true; 
	
	for (int w : list[u]) { 
		if ( ! reachm[u][w] ) 
			reach(list, u, w) ; 
	}
}


void print_mat(int size) {
	int i_, j_; 

	for(i_=0; i_<size ; i_++) {
		for(j_=0; j_<size ; j_++) 
			cout<<reachm[i_][j_]<<" "; 	
		cout<<endl; 
	}
}

void royWarshall(int size) { 
	int i_, j_, k_; 

	for(k_=0; k_<size ; k_++) {
		for(i_=0; i_<size ; i_++) {
			if ( reachm[i_][k_] && i_!= k_) { 
				for(j_=0; j_<size ; j_++) {
					reachm[i_][j_] = reachm[i_][j_] || reachm[k_][j_];
				}		
			}
		}		
	}

}

void createMat(adl &list) { 
	int i_; 	
	for(i_=0; i_<list.size() ; i_++) {
		for(int j_ : list[i_] ) 
			reachm[i_][j_] = true;
	}

}


// ###FALTA COMPARAR CONR ROY WARSHALL
int main() 
{
	int i_, j_, n, m, u, v; 
	adl list; 


	rii(n,m); 
	list.reserve(n);

	for(i_=0; i_<m ; i_++) {
		rii(u,v); 			
		addEdge(list, u, v); 
	}

	//for(i_=0; i_<n ; i_++) 
	//	reach(list, i_, i_); 	
	
	//createMat(list); 
	//royWarshall(n); 

	print_mat(n); 

	return 0; 
}
