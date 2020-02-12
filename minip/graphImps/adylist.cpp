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
#include<list>


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


class Graph{ 
	int n, m;	
	vector< list<int> > adyl;  
	
public: 
	Graph(int v, int e) { 
		int i_ ;
		n = v;
		m = e;
		adyl.resize(n); 
	}
	int getN() {
	       return n; 
	}
	int getM()  {
		return  m ;
	}

	void printGraph();

	void addNode(); 
	void addEdge(int u, int v); 
	void deleteNode(int e); 
	void deleteEdge(int u, int v);

	list<int> successors(int e) ;
	int degree(int e); 
};


void Graph::printGraph() { 
	int i_; 

	for(i_=0; i_<n ; i_++) {

		for(auto it: adyl[i_]) {
			cout<<i_<<" "<<it<<endl; 
		}
	}
}


void Graph::addNode() { 
	adyl.resize(n+1);
}


void Graph::addEdge(int u, int v) { 
	adyl[u].push_back(v); 

}

void Graph::deleteNode(int e) { 
	int i_, count; 
	list<int>::iterator it; 

	adyl.erase(adyl.begin()+(e-1)); 

	n-=1; 

	//search the whole structure for e, and delete it from lists
	for (i_=0 ; i_<n ; i_++) { 

		for(it=adyl[i_].begin(); it!=adyl[i_].end(); it++) {
			if (*it == e-1) {
				adyl[i_].erase(it); 
				break; 
			}
		}
	}

}

void deleteEdge(int u, int v) { 

}
list<int> Graph::successors(int e) {
	return adyl[e]; 
}


int Graph::degree(int e) { 
	return adyl[e].size(); 
}



void printList(list<int> l) { 

	for( int i: l) 
		cout<<i<<" "; 
	cout<<endl; 
}


int main() 
{
	int i_, n, m, u, v; 
	list<int> my_list;

	rii(n, m); 

	Graph G(n,m); 


	for(i_=0; i_<G.getM() ; i_++) {
		rii(u,v); 
		G.addEdge(u,v); 	
	}	

	G.printGraph(); 

	printList(my_list); 

	G.deleteNode(2); 

	G.printGraph(); 



	return 0; 
}
