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
#define MAXREAD 0x7ffff000

#define BUFFS 512
#define STDIN 0

int glob; 

void handler() { 
	glob = FALSE; 
}

int main(int argc, char *argv[])
{
	int d, i_; 
	return 0; 
}

