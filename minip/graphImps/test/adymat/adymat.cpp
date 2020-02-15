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
#include"adymat.h"


#define rii(c,cc) scanf("%d %d", &c, &cc)


	
using namespace std; 


Digraph::Digraph(int v, int e) {
	int i_; 

	n = v; 
	m = e;
	adymat.resize(n); 
	for(i_=0; i_<n ; i_++) 
		adymat[i_].resize(n); 	
}


int Digraph::VSize() { 
	return n; 
}

int Digraph::ESize() { 
	return m; 
}
void Digraph::print() {
	int i_, j_; 

	for(i_=0; i_<n ; i_++) {
		for(j_=0; j_<n ; j_++) 
			cout<<adymat[i_][j_]<<" "; 	

		cout<<endl; 	
	}			

}


void Digraph::addEdge(int u, int v){
	adymat[u][v] = true; 
}


void Digraph::init() { 
	int i_, j_, u, v; 

	for(i_=0; i_<m ; i_++) {
		rii(u, v); 
		addEdge(u, v); 
	}	
}


bool Digraph::isEdge(int u, int v) {
	if (adymat[u][v])
		return true; 
	return false; 
}


vector<int> Digraph::successors(Digraph *graph, int e) { 
	int i_; 
	vector<int> suc; 

	for(i_=0; i_<graph->VSize() ; i_++) {
		if ( graph->isEdge(e,i_) )
			suc.push_back(i_);	
	}

	return suc; 
}
	


void Digraph::roywarshall() { 
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



