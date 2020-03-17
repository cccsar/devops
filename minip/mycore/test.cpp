#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define BUFFS 512	
#define STDIN 0
#define TOK 'a'
#define REP '$'
int main (int argc, char **argv) { 

	int i_ , cnt, ant, size; 
	int app, prep, rep;
	char hola[BUFFS], help[BUFFS * 2]; 

	app = prep = rep = TRUE ;
	ant = 0; 

	size = read(STDIN, hola, BUFFS) ;

	cnt = 0; 
	prep = TRUE; 

	for(i_=0; i_<size ; i_++) {
		if ( app && help[i_ + cnt] == TOK) {
			help[i_ + cnt] = REP;	
			cnt +=1; 
		}
		help[i_ + cnt] = hola[i_];	
		if ( prep && help[i_ + cnt] == TOK) {
			cnt +=1; 
			help[i_ + cnt] = REP;	
		}
	}	


	write(1,help, size + cnt);

	return 0 ;
}

