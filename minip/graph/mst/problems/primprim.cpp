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

const int MAXINT = 2147483647;


const int MAXT = 10; 
const int MAXS = 10; 

bool excluded[MAXS][MAXS];
int rk[MAXS]; 
int parent[MAXS]; 
int resp[MAXT];

int myFind(int e) { 
	int k = e; 
	
	while( k != -1)
		k = parent[k]; 

	if (k != e )
		parent[e] = k ;

	return k; 
}

bool myUnion(int x, int y ) { 
	int rx, ry; 

	rx = myFind(x); 
	ry = myFind(y); 	

	if ( rx != ry ) { 
		if ( rk[ rx ] >= rk[ ry ] ) { 
			parent[ry] = rx; 
			if ( rk[rx] == rk[ry] ) 
				rk[rx] += 1;
		}
		else 
			parent[rx] = ry; 

		return true; 

	return false; 
}

void myKruskal (vii graph[], int size ) { 
	int i_, cost; 
	priority_queue<pii, vector<pii>, greater<pii> > pq; 
	pii dum; 

	cost = 0 ;

	for(i_=0; i_<size ; i_++) {
		for(pi k : graph[i_] ) { 

			if ( !excluded[i_][k.second] )  
				pq.push( { k.first, { i_, k.second } }); 
		}	
	}	

	while ( !pq.empty()  ) {
		dum = pq.top(); 
		pq.pop(); 

		if ( !excluded[ dum.second.first ][ dum.second.second ] ) { 
			if ( myFind( dum.second.first, dum.second.second ) ) {
				excluded[ dum.second.first ][ dum.second.second ] = true ;
				cost += dum.first;
			}
		}
	}

	return cost; 
}


int main() 
{
	int n, m, a, b, c, i_, cnt, fst, scd; 

	cnt = 0; 

	vii *graph = new vii[MAXS] ; 

	while ( true ) { 
		rii(n,m ); 
		if ( n == 0 ) 
			break; 

		for(i_=0; i_<m ; i_++) {
			riii(a,b,c ); 
			graph[a].push_back( {c, b} ); 	
			graph[b].push_back( {c, a} ); 	
		}		


		fst = myKruskal(grahp, m);  	
		scd = myKruskal(graph, m); 



		for(i_=0; i_<n ; i_++) {
			for(j_=0; j_<n ; j_++)
				excluded[i_][j_] = false ;	
		}	
		
		cnt +=1 ;
	}


	for(i_=0; i_<cnt ; i_++) {
			
	}	

	return 0; 
}
