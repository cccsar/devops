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

typedef vector<char> word; 
	
void foo(word hola, word mas[], char n) { 
	hola.push_back(n+97); 

	for(char k : hola)
		cout<<k<<" ";
	cout<<endl;

	if ( n != 0 )  
		foo(hola, mas, n-1); 
	else 
		mas[0] = hola; 
}


int main() 
{
	int i_, n, size; 
	char e; 
	deque<char> test; 

	ri(n); 
	for(i_=0; i_<n ; i_++) {
		scanf(" %c",&e); 	
		test.push_back(e); 
	}	

	size = test.size(); 
	char temp; 

	cout<<"first test: "<<endl;

	for(char k : test) 
		cout<<k<<" ";
	cout<<endl; 

	for(i_=0; i_<size ; i_++) {
		temp = test.back(); 		
		test.pop_back(); 

		cout<<"current: "<<temp<<endl; 
		cout<<"complement: "<<endl;
		for(char k : test)
			cout<<k<<" "; 
		cout<<endl ;

		test.push_fron(temp);
	}

	return 0 ;
}
