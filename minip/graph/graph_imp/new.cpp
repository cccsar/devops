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
#define adym vector< vector< bool > > 

	
using namespace std; 

class Digraph { 
	int n,m ; 
	vector< vector< bool > > adymat; 
public:

	Digraph(int v, int e) {
		int i_; 

		n = v; 
		m = e;
		adymat.resize(n); 
		for(i_=0; i_<n ; i_++) 
			adymat[i_].resize(n); 	
	}

	void print() {
		int i_, j_; 

		for(i_=0; i_<n ; i_++) {
			for(j_=0; j_<n ; j_++) 
				cout<<adymat[i_][j_]<<" "; 	

			cout<<endl; 	
		}			

	}

	void addEdge(int u, int v){
		adymat[u][v] = true; 
	}

	void init() { 
		int i_, j_, u, v; 

		for(i_=0; i_<m ; i_++) {
			rii(u, v); 
			addEdge(u, v); 
		}	
	}

	bool isEdge(int u, int v) {
		if (adymat[u][v])
			return true; 
		return false; 
	}

	void roywarshall() { 
		int i_, j_, k_; 

		//Identity
		for(i_=0; i_<n ; i_++) 
			adymat[i_][i_] = true; 	

		for(k_=0; k_<n ; k_++) {
			for(i_=0; i_<n ; i_++) {

				if ( adymat[i_][k_] && i_ != k_) {
					for(j_=0; j_<n ; j_++) 
						adymat[i_][j_] = adymat[i_][j_] || adymat[k_][j_]; 
				}
		
			}	
		
		}	
	
	}

};

