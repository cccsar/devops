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

#define vi vector< int > 
#define vii vector< pair<int, int> >  
#define viii vector< int, pair<int, int> >
#define pi pair <int, int> 
#define pii pair <int, pair<int, int> > 
#define adl vector< vi > 
#define wadl vector< vii > 

#define CONST 1000

adl graph;

void foo(vi hola[], int u, int v) { 
	hola[u].push_back(v);	
}

int main() 
{
	int i_, j_, u, v; 
	priority_queue<int > hola; 


	for(i_=0; i_<10 ; i_++) 
		hola.push(i_); 

	for(i_=0; i_<10 ; i_++)  {
		cout<<hola.top()<<" ";
		hola.pop(); 
	}

	return 0; 
}
