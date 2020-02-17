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
#define WHITE 0
#define GRAY 1
#define BLACK 2

int init[MAXSIZE];
int fin[MAXSIZE];
int parents[MAXSIZE];
int color[MAXSIZE];
	

void addEdge(vi graph[], int u, int v) { 
	graph[u].push_back(v); 
}


void read_input(vi graph[], int m) { 
	int i_, u, v; 

	for(i_=0; i_<m; i_++) { 
		rii(u,v); 
		addEdge(graph, u, v) ;
	}	

}


void printGraph(vi graph[], int size) {
	int i_; 

	for(i_=0; i_<size; i_++)  {
		for(int k : graph[i_])
			cout<<i_<<" "<<k<<endl; 
	}
}


//algorithm to reverse a grapm implemented as adyl
void reverseGraph(vi graph[], vi inverse[], int size) { 
	int i_; 

	for (i_=0; i_<size; i_++) {
		for (int k: graph[i_])
			inverse[k].push_back(i_); 
	}

}


//DFS VISIT
void dfsVisit (vi graph[], int *time, int e) {
	*time += 1; 
	init[e] = *time; 

	color[e] = GRAY; 

	for (int k : graph[e])  {
		if (color[k] == WHITE) 
		{
			parents[k] = e; 
			dfsVisit(graph, time, k);
		}
	}

	*time += 1;
	fin[e] = *time; 

	color[e] = BLACK ;
}


int main() 
{
	int i_,  n, m, time; 
	priority_queue< pi > ordered; 
	vi *graph = new vector<int>[MAXSIZE];
	vi *inverted = new vector<int>[MAXSIZE];


	rii(n,m); 

	for(i_=0; i_<n; i_++) 
		parents[i_] = -1; 
	read_input(graph, m); 


	//	Go throug every vertex (consider not connected graph)
	for(i_=0; i_<n; i_++) { 

		if ( color[i_] == WHITE)  
		{
			dfsVisit(graph, &time, i_); 
		}
	}

	//	reset used arrays and time
	for(i_=0; i_<n; i_++)  {
		parents[i_] = -1; 
		color[i_] = WHITE; 
	}
	time = 0;

	//	reverse order finalization time
	for(i_=0; i_<n ; i_++) {
		pi par; 

		par.first = fin[i_]; 
		par.second = i_; 

		ordered.push(par); 
	}

	//	reverse the graph
	reverseGraph(graph, inverted, n);

	//	repeat dfsVisit but with inverted
	//	###UNIFICAR ESTA VAINA QUE SE VE MUY FEA
	pi help; 
	while( ! ordered.empty() ) {

		help = ordered.top(); 
		ordered.pop();

		if ( color[help.second] == WHITE)  
			dfsVisit(inverted, &time, help.second); 
	}


	for(i_=0; i_<n ; i_++) 
		cout<<parents[i_]<<" ";
	cout<<endl;

	return 0; 
}
