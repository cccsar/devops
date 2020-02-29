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
	

int main() 
{
	int i_, n;
	string query;
	map<string, int> dict; 
	pair<string, int> dummie; 

	ri(n); 
	for(i_=0; i_<n ; i_++) { //do I have to recreate dummie?
		cin>>dummie.first>>dummie.second; 	
		dict.insert(dummie); 
	}
	cout<<"which string would you like to query?"<<endl; 
	cin>>query;
	
	cout<<dict[query]<<endl; 

	return 0;
}
