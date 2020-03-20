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
#include<string> 
#include<map>

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
	

void foo(int *prepago, int hola) {
	int i_; 
	for(i_=0; i_<hola ; i_++) {
		prepago[i_] = 69;	
	}	
}

int main() 
{
	int i_; 
	int prueba[60]; 

	foo(prueba, 10); 

	for(i_=0; i_<10 ; i_++) {
		cout<<prueba[i_]<<" "; 
	}
	cout<<endl;
	return 0 ;
}
