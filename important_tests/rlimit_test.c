#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/time.h> 
#include <sys/resource.h>
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define NLIMITS 4

/* 	Check man for getrlimit 	*/
int main (int argc, char **argv) { 
	struct rlimit test[NLIMITS]; 
	int i_;
	
	/* memory limits for address space */
	getrlimit(RLIMIT_AS,&test[0]); 
	
	/* memory limits for data segment */
	getrlimit(RLIMIT_DATA,&test[1]); 	

	/* limit of process to be created */
	getrlimit(RLIMIT_NPROC,&test[2]);

	/* memory limit for stack */
	getrlimit(RLIMIT_STACK,&test[3]); 

	for(i_=0; i_<NLIMITS; i_++) {
		printf("Test %d:\n",i_);
		printf("\tSoft limit: %lld\n",(long long )test[i_].rlim_cur); 
		printf("\tHard limit: %lld\n",(long long )test[i_].rlim_max); 
	}


	return 0;
}
