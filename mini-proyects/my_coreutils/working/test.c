#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <fcntl.h>  
#include <ctype.h> 
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>
#include <signal.h> 

#define TRUE 1
#define FALSE 0

#define BUFFS 512	
#define STDIN 0
#define TOK 'a'
#define REP '$'

int guard; 

void intHandler() { 
	guard = FALSE; 
	printf("guard: %d\taddress:%p\n",guard, &guard); 
}

int main(int argc, char *argv[])
{
  int  i_, k;
  char hola[BUFFS]; 

  void (*old_sh)();
  __sighandler_t old_h; 

  guard = TRUE; //init breaker

  old_sh = signal(SIGINT, intHandler ) ; //update handler

 
  while ( guard ) { //think on how to interrupt any time 

	k = read(0, hola, BUFFS); 

	printf("ARRIBA\n"); 
	for(i_=0; i_<k ;i_++) { 
		if (hola[i_] == 'a' ) 
			printf("found\n"); 
	}	

	if ( !guard) 
		break; 
	printf("guard: %d\n",guard); 
	printf("ABAJO\n");
  }

  signal(SIGINT , old_sh); 
  
  return 0; 
}
