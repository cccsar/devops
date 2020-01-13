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
	list<int> *adyl;  
	
public: 
	Graph(int v, int e) { 
		int i_ ;
		n = v;
		m = e;
		adyl = (list<int> *) malloc( sizeof(list<int> ) * n)  ;
		for(i_=0; i_<n ; i_++) {
			adyl[i_] = new list<int>  ;
		}	
	}
	int getN() {
	       return n; 
	}
	int getE()  {
		return  m ;
	}

	void printGraph();

	void addNode(); 
	void addEdge(int u, int v); 
	void deleteNode(int e); 
	void deleteEdge(int u, int v);
	void test();
};

void Graph::test(){ 
	int i_; 

	for(i_=0; i_<n ; i_++) {
		cout<<"list "<<i_<<"size: "<<adyl[i_].size()<<endl;	
	}		
}

void Graph::printGraph() { 
	int i_; 

	for(i_=0; i_<n ; i_++) {

		for(auto it: adyl[i_]) {
			cout<<it<<" ";   	
		}	
		cout<<endl; 
	}
}


void Graph::addNode() { 
	adyl = (list<int> *) realloc(adyl, sizeof(list<int>) * (n+1)) ;
}

void Graph::addEdge(int u, int v) { 
	adyl[u].push_back(v); 

}


int main() 
{
	int i_, n, m, u, v; 

	rii(n, m); 

	Graph G(n,m); 


	for(i_=0; i_<G.getN() ; i_++) {
		rii(u,v); 
		G.addEdge(u,v); 	
	}	

	G.printGraph(); 


	return 0; 
}
