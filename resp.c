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
#define MAX_PS 10

#define MAX_WORDS 100
#define MAX_READ 1

void findEol(int fd, int size) { 
	char something; 

	/*busca el proximo fin de linea, o en su defecto la siguiente palabra*/
	while(lseek(fd, 0, SEEK_CUR) != size) { 
		read(fd, &something, MAX_READ); 
		
		if (something == '\n' || something != ' ' || something != '\t')
			break; 
	}
	/*get current offset*/
 	printf("file offset: %d\n", lseek(fd, 0, SEEK_CUR)); 

}

int main (int argc, char *argv[]) {
	int fd, count, help, wc, i_; 
	char * perico ;
	char **words; 
	char test; 
	struct stat estado; 

	words = (char**) malloc (sizeof(char*) MAX_WORDS ); 
	perico = (char*) malloc(sizeof(char) * 20); 

	fd = open(argv[1], O_RDONLY, ); 
	if (fd == -1) 
		perror("open"); 
	
	if ( lstat(argv[1], &estado) == -1 )
		perror("stat"); 

	count = -1;
	wc = 0;

	/*compare current offset with size*/
	while( lseek(fd, 0, SEEK_CUR) != estado.st_size) { 
		/*falta verificar lectura segura? */
		help = read(fd, &test, MAX_READ); 
		count += help; 

		if ( test == '\n') {
			perico[count] = '\0';
			words[wc] = perico; 
			wc++;
			count = 0;
			continue; 
		}
		else if ( test == ' ' || test == '\t') { 
			findEol(fd, estado.st_size); 
			continue;
		}

		perico[count] = test; 
	}

	for (i_=0; i_<wc; i_++) 
		printf("%s\n",words[i_]); 
	
	return 0;
}
