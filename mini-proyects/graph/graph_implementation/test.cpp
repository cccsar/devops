#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<set> 
#include<vector>
#include<deque> #include<stack> #include<queue>
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

int main() 
{
	int i_; 
	vector<int> hola; 
	vector<int>::iterator it; 
	
	for (i_=0 ; i_<5 ; i_++) { 
		hola.push_back(i_); 
	}

	for (int i: hola) 
		cout<<i<<" " ;
	cout<<endl; 

	hola.erase(hola.begin()+3); 

	for (it : hola) 
		cout<<*i<<" " ;
	cout<<endl; 


	return 0; 
}
