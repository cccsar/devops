//judge: 
// 	http://www.tzcoder.cn/acmhome/vProblemList.do?method=problemdetail&oj=UVA&pid=11354
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

const int MAXSIZE = 50000;
const int MAXQUERIES = 5; 

int parent[MAXSIZE] ; 
int cost[MAXSIZE] ; 
int resp[MAXSIZE]; 

//Implementation for ndirected graphs
//
void addWEdge(vii graph[], int u, int v, int w) { 
	pi help ;

	help.first = w; 
	help.second = v;

	graph[u].push_back(help); 

	help.second = u; 

	graph[v].push_back(help);
}


void readWGraph(vii graph[], int *n, int *m ) { 
	int u, v, w, i_;

	rii(*n,*m); 
	
	for(i_=0; i_<*m ; i_++) {
		scanf("%d %d %d", &u, &v, &w); 
		addWEdge(graph, u-1, v-1, w) ;
	}	
}

void recoverPath(int *cost, int *parent, int u, int v) { 
	;
}

void modifDijkstra(vii graph[], int source ) { 
	int help ;
	priority_queue<pi> next_q; 
	pi dummie, u; 

	parent[ source ] = source; 
	cost[ source ] = 0;
	
	dummie.first = cost[ source ] ; 
	dummie.second = source ;

	next_q.push(dummie); 

	while( !next_q.empty() ) { 
		
		u = next_q.top(); 
		next_q.pop(); 

		for(pi v: graph[ u.second ] ) { 
			
			help = max( cost[ u.second ], v.first ); //assign minimum of costs calculated

			if ( cost[v.second] == -1) { //hasn't been seen
				cost[v.second] = help;
				parent[v.second] = u.second; 

				dummie.first = cost[v.second] ; 
				dummie.second = v.second; 

				next_q.push(dummie);
			}
			else { 	//has been seen
	       			if ( help < cost[v.second] ) { 
					cost[v.second] = help; 
					parent[v.second] = u.second;

					dummie.first = cost[v.second] ; 
					dummie.second = v.second; 
	
					next_q.push(dummie);
				}			
			}


		}
	}
}



int main() 
{
	int n, m, q, i_, j_, k_; 
	vii *graph = new vii[MAXSIZE];
	vi *resp = new vi[MAXQUERIES]; 

	for(i_=0; i_<MAXSIZE ; i_++) {
		cost[i_] = -1; 
		parent[i_] = -1;	
	}		

	int u, v, w, count = 0;

	while( scanf("%d %d", &n, &m) != EOF ) { 
		
		for(i_=0; i_<m ; i_++) {
			riii(u,v,w); 
			addWEdge(graph, u-1, v-1, w) ;
		}	

		ri(q); 

		int s, t;
		for(j_=0; j_<q ; j_++) {
			rii(s, t); 
			modifDijkstra(graph, s-1); 	
			resp[count].push_back(cost[t-1]) ; 


			//if source changes try to avoid repeating ###
			for(k_=0; k_<n ; k_++) {	//reseting for future dijstras
				cost[k_] = -1 ;	
				parent[k_] = -1; 
			}		
		}	

			
		for(j_=0; j_<n ; j_++) {
			cost[j_] = -1 ;	
			parent[j_] = -1; 
			graph[j_].clear(); 
		}	

		count += 1;
	}

	for(i_=0; i_<count ; i_++) {
		for(int k : resp[i_] ) 
			cout<<k<<endl;
		if(i_ != count -1 ) 
			cout<<endl;
	}
	return 0; 
}
