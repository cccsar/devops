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
typedef pair<float, int> pfi;

const int MAXINT = 2147483647;

const int MAXS = 500; 
const int MAXT = 100 ; 

float resp[MAXT]; 
float cost[MAXS] ;
float distmat[MAXS][MAXS] ; 


void myPrim(priority_queue<float> &check, int size) { 
	int i_; 
	priority_queue< pfi, vector<pfi> , greater<pfi> > best; 
	pfi dum; 

	best.push( {0, 0} ) ; 


	while( !best.empty() ) { 
		dum = best.top(); 
		best.pop(); 

		if ( cost[ dum.second ] == MAXINT ) { 

			cost[ dum.second ] = dum.first; 

			check.push( cost[ dum.second ] ); //this is to keep maximum of mst
							//and to iterate from last 
			

			for(i_=0; i_<size ; i_++) {

				if ( cost[i_] == MAXINT && i_!= dum.second )  
					best.push( { distmat[dum.second][i_], i_ } ); 	
			}	
		}
	}


	
}

float dist(pi p1, pi p2) { 
	return sqrt( pow (abs(p1.first - p2.first), 2) + pow(abs(p1.second - p2.second),2) ) ; 
}


int main() 
{
	int t, s, p, x, y, i_, j_, k_, count; 
	vii coord; 

	for(int c=0; c<MAXS; c++)  	//init adymat for costs
		cost[c] = MAXINT; 

	count = 0;

	ri(t); 

	for(i_=0; i_<t ; i_++) {
		priority_queue<float> to_exclude; 

		rii(s, p); 
		
		for(j_=0; j_<p ; j_++) {
			rii(x,y); 
			coord.push_back( {x, y} ); 
		}		

		for(j_=0; j_<p ; j_++) {

			for(k_=j_; k_<p ; k_++)
				distmat[j_][k_] = distmat[k_][j_] = dist( coord[j_], coord[k_] );
		}	

		myPrim(to_exclude, p);   
		
		while( !to_exclude.empty() && count < s-1 ) {
			
			to_exclude.pop(); 		
			count += 1;
		}

		resp[i_] = to_exclude.top();


		coord.clear(); 
		for(j_=0; j_<p ; j_++) {	//clearing

			cost[j_] = MAXINT; 
			for(k_=0; k_<p ; k_++)  
				distmat[j_][k_] = 0; 
		}		
	}	


	for(i_=0; i_<t ; i_++) 
		printf("%.2f\n",resp[i_]);	

	return 0; 
}
