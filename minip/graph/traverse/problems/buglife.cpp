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

const int MAXSIZE = 2000; 

const int NOTHING = 0; 
const int WHITE = 1; 
const int BLACK = 2; 

bool visited[MAXSIZE] ;
bool resp[MAXSIZE];
int color[MAXSIZE]; 
int parent[MAXSIZE]; 

void addEdge(vi graph[], int u, int v) { 
	graph[u].push_back(v); 
	graph[v].push_back(u);
}


void readGraph(vi graph[], int *n, int *m ) { 
	int u, v, i_;

	rii(*n,*m); 
	
	for(i_=0; i_<*m ; i_++) {
		rii(u,v);
		addEdge(graph, u, v) ;
	}	
}


bool bfs(vi graph[], int source) { 
	int dummie, cnt; 
	queue<int> next_s; 

	next_s.push(source) ; 
	visited[ source ] = true;

	cnt = 0;
	color[source] = BLACK; 

	while ( !next_s.empty() ) { 

		dummie = next_s.back();
		next_s.pop(); 

		for(int k : graph[dummie]  ) {
			if( !visited[k] ) { 
				next_s.push(k); 
				visited[k ] = true; 

				color[k] = (cnt%2==1 )? BLACK : WHITE; 
			}	
			else if ( (color[k] == BLACK && cnt%2 == 0) ||
					(color[k] == WHITE && cnt%2 == 1) ) {
				return false; 
				
			}
		}
			
		cnt += 1; 
	}

	return true; 
}


int main() { 
	int s, n, m, i_, j_; 
	vi *graph = new vi[MAXSIZE];

	ri(s);
	for(i_=0; i_<s ; i_++) {
		readGraph(graph, &n, &m);

		for(j_=0; j_<n ; j_++) {
			if ( !visited[i_] )  { 
				resp[i_] = resp[i_] || bfs(graph, i_); 	
				if (resp[i_] ) 
					break; 
			}
		}		
		
		for(j_=0; j_<n ; j_++) {
			visited[j_] = false; 
			color[j_] = 0 ;			
		}	
	}

	for(i_=0; i_<s ; i_++) {
		cout<<"Scenario #"<<i_+1<<":"<<endl; 
		if ( resp[i_] )  
			cout<<"Suspicious bugs found!";
		else  
			cout<<"No suspicious bugs found!";
		cout<<endl; 
	}	

	return 0; 
}
