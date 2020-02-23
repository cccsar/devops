#include<iostream> 
#include<stdio.h>
#include<vector>
#include<deque>
#include<pthread.h>

using namespace std; 

typedef vector< char > word; 

#define MAXSIZE 3628800  // this is 10! to keep a bound of ~34.61MB 


word *permutations = new word[MAXSIZE]; //globalized permutations to reduce args


void perm(deque<char> charset, word accumulator, char e, int *ind) { 
	accumulator.push_back( e );
	

	if (charset.size() == 0)  {
		*ind += 1; 
		permutations[*ind] = accumulator;
	} 
	else { 
		int i_, size; 
		char delta; 
		size = charset.size() ; 	
		
		for(i_=0; i_<size ; i_++) {
			delta = charset.front(); 


			charset.pop_front(); 
			perm(charset, accumulator, delta, ind); 	
			charset.push_back( delta );

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


int main(int argc, char **argv) 
{
	int n, i_, index, fact_n;
	char e, current_letter; 
	word accumulator; 
	deque<char> character_set; 

	scanf("%d",n); 
	index = -1;
	fact_n = fact(n);


	for (i_=0 ; i_<n ; i_++)  {
		scanf(" %c", &e);
		character_set.push_back(e); 
	}

	for (i_=0; i_<n; i_++) { 
		current_letter = character_set.front(); 

		character_set.pop_front(); 
		perm(character_set, accumulator, current_letter, &index);
		character_set.push_back( current_letter );
	}

	for(i_=0; i_<fact_n ; i_++) {
		for (char permut: permutations[i_]) 
			printf("%c ",permut); 
		printf("\n");
	}

	return 0; 
}
