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
#define NOTHING 0
#define OPEN 1
#define CLOSE 2

int visited[MAXSIZE];
int parents[MAXSIZE];


void addEdge(vi graph[], int u, int v) { 
	graph[u].push_back(v); 
}


void readGraph(vi graph[], int *n, int *m ) { 
	int u, v, i_;

	rii(*n,*m); 
	
	for(i_=0; i_<*m ; i_++) {
		rii(u,v);
		addEdge(graph, u, v) ;
	}	
}


void printGraph(vi graph[], int size) { 
	int i_;
	for(i_=0; i_<size ; i_++) {
		for (int k : graph[i_]) 
			cout<<i_<<" "<<k<<endl;	
	}

}


void recoverPath(int size, vi &order) { 
	int i_, dummie; 
	stack<int> *paths = new stack<int>[MAXSIZE];
	vector<int> actual; 

	for(int i_ : order )  {
		dummie = i_; 
		
		if ( parents[i_] != -1) 
		{
			actual.push_back(i_); 
			
			while (dummie != parents[dummie] ) {
				paths[i_].push(dummie); 
				dummie = parents[dummie] ;
			}
			paths[i_].push(dummie); 

		}
	}

	//print in order
	for(int k : actual ) { 
		while( ! paths[k].empty() ) { 
			cout<<paths[k].top()<<" "; 
			paths[k].pop(); 
		}
		cout<<endl;
	}
	
}


//predicate for choosing next path to open
bool del(int e) { 
	if (visited[e] == NOTHING ) 
		return false;
	return true;
}


//BFS
void bfs(vi graph[], queue<int> &opened, vi &order, int r) {
	opened.push(r); 
	parents[r] = r; 

	int dummie;
	while( !opened.empty() ) { 
		dummie = opened.front(); 
		opened.pop();

		visited[dummie] = CLOSE	;	
		order.push_back(dummie);
	
		for(int k : graph[dummie])  {

			if( !del(k) )  
			{
				parents[k] = dummie; 
				opened.push(k); 
				visited[k] = OPEN;
			}
		}
	}

}


//Iterative BFS implementation
int main() {
	int i_, n, m; 
	vi *graph = new vi[MAXSIZE];
	queue<int> opened;  //queue to go breadth
	vector<int> order;  //dynamic array to store the close order of paths


	readGraph(graph, &n, &m);	

	for(i_=0; i_<n ; i_++) 
		parents[i_] = -1;


	//This loops through all graph, even if not connected
	for(i_=0; i_<n ; i_++) {
		if (!visited[i_]) 
			bfs(graph, opened, order, i_); 
	}		


	for(i_=0; i_<n ; i_++) 
		cout<<parents[i_]<<" ";
	cout<<endl;

	recoverPath(n, order); 

	return 0; 
}
