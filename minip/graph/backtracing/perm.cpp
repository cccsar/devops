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

#define rc(c) scanf("%c",&c) 
typedef vector< char > word; 
typedef vector< word > wlist; 

	
#define MAXSIZE 1000

bool valid[MAXSIZE];

void perm(word solutions[], deque<int> cc,  word acc,char letter, int *count) { 
	acc.push_back(letter);
	cout<<letter<<endl;
	
	if (cc.size() == 0)  {
		*count=+1; 
		solutions[*count]=acc;
	} 
	else { 
		int i_, size, temp; 

		size = cc.size() ; 	

		for(i_=0; i_<size ; i_++) {
			temp = cc.front(); 
			
			cc.pop_back(); 
			perm(solutions, cc, acc, temp, count); 	
			cc.push_front(temp);

		}
	}
}


int fact(long long n) { 
	int i_, acc; 
	acc = 1; 

	for (i_=2; i_<=n ; i_++) { 
		acc = acc * i_; 	
	}

	return acc;
}


int main() 
{
	int n, e, i_, count, big;
	word help, *solutions, mas; 
	deque<int> set_char; 

	ri(n);
	solutions = new word[MAXSIZE];
	big = fact(n);


	for (i_=0 ; i_<n+1 ; i_++)  {
		rc(e);
		set_char.push_back(e); 
		mas.push_back(e); 
	}


	for (char k: mas) 
		perm(solutions, set_char, help, k, &count);


	for (i_=0 ; i_<big ; i_++) { 
		for(char k: solutions[i_])
			cout<<k<<" ";
		cout<<endl;
	}
	
	return 0; 
}
