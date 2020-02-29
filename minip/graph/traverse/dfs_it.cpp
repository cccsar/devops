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

bool usable[MAXSIZE];
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


bool del(int k ) { 
	if ( visited[k] == OPEN)  {
		usable[k] = false; 
		return false; 
	}
	else if( visited[k] == CLOSE ) 
		return true;

	return false;
}


//DFS
void dfs(vi graph[], stack<int> &opened, vi &order, int size, int r) {
	int dummie; 
	opened.push(r); 	

	while( !opened.empty() ) {
		dummie = opened.top(); 

		//if node was marked as deleted by del, then ignore and search next
		while( !usable[dummie] ) {  
			opened.pop();
			dummie = opened.top(); 
		}
		opened.pop();

		visited[dummie] = CLOSE; 
		order.push_back(dummie);

		for(int k: graph[dummie]) { 

			if ( !del(k) ) 
			{ 
				opened.push(k); 
				parents[k] = dummie; 
				visited[k] = OPEN; 
			}
		}
	}
}


int main() 
{
	int n, m, i_; 
	vi *graph = new vi[MAXSIZE];
	stack<int> opened; 
	vi order; 

	readGraph(graph, &n, &m); 

	for(i_=0; i_<n ; i_++)  {
		parents[i_] = -1;
		usable[i_] = false; 
	}

	for(i_=0; i_<n ; i_++) {
		if (parents[i_] != -1) 
		       dfs(graph, opened, order, n, i_); 
	}
	


	return 0; 
}
