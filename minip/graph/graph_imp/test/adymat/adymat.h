#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include <vector>

#ifndef __DIGRAPH__
#define __DIGRAPH__

class Digraph { 
	int n,m ;
	std::vector< std::vector< bool > > adymat; 
public: 
	Digraph(int v, int e) ;

	int VSize(); 
	int ESize(); 
	void print(); 
	void addEdge(int u, int v); 
	void init(); 
	bool isEdge(int u, int v); 
	void roywarshall(); 
	std::vector<int> successors(Digraph *graph, int e); 
};

#endif


	
