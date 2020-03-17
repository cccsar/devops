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

#define TRUE 1
#define FALSE 0

#define BUFFS 512	
#define STDIN 0
#define TOK 'a'
#define REP '$'


int main(void)
{
  int i, j, n;

  printf("\033[1;31m"); 
  printf("hola\n"); 
 
  return 0; 
}
