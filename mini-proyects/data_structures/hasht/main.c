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
#include "hash.h"

#define TRUE 1
#define FALSE 0

int main (int argc, char **argv) { 

	hashTesting(); 

	return 0; 
}

