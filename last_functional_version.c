/*
 * Archivo: nombre.c/.nombre.h
 *
 * Descripcion:	
 *
 * Autores:
 * 	Carlos Alejandro Sivira Munoz		15-11377
 * 	Cesar Alfonso Rosario Escobar		15-11295
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>
#include <errno.h>
#include "myFind.h"
#include "list.h"

#define TRUE 1
#define FALSE 0

#define WRITE 1
#define READ 0

#define MAX_PATH 5000

#define MAX_PS 1000 
#define MAX_FILES 419 

#define FD_DIGITS 5
#define FILES_DIGITS 10 

#define MAX_DIGITS 20

#define EXEC_NAME "freecpal"
#define FREECPAL 8

#define WORD_SIZE 20

#define SMP0 "/mutex"
#define SMP1 "/sem_reader"
#define SMP2 "/sem_writer"
#define MODE S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH


#define MIN(a,b) (a < b)? a: b;


/* intToString
 * --------------
 *
 *
 */
int intToString(char* arr, int a, int *i) { 

	if( a/10 != 0 )  {
		*i = intToString(arr, a/10, i) ;
		arr[*i] = a%(10) + 48; 
	}
	else   
		arr[*i] = a + 48;

	*i += 1;

	return *i; 
}


void countFrequencies(list *my_list, char** paths, int floor, int ceil, int reference) {
	int j_; 
	FILE *fp; 

	char* current_word; 
	node *space;


	for(j_=floor*reference; j_ < floor*reference + ceil   ; j_++) { 
	

		if ( !(fp = fopen(paths[j_],"r")) ){

			fprintf(stderr, "%s",paths[j_]);
			perror("fopen"); 
		
			exit(-3); 
		}
		

		/*Se reserva espacio para la primera palabra del archivo*/
		if ( (current_word = (char*) malloc(WORD_SIZE * sizeof(char)) ) == NULL ) {
			perror("malloc");
			exit(-2);
		}
		
		while( fscanf(fp,"%s",current_word) != EOF) { 
		
			if ( ( space = (node*) malloc( sizeof(node) ) ) == NULL ) {
				perror("malloc");
		
				exit(-2);
			}
		
			nodeInit(space, current_word, 1); 
		
			/*En caso de que solo la frecuencia de un elemento */
			/* se aumente como ese nodo ya esta creado, se libera*/
			/* la memoria que se almaceno para insertarlo.*/
			if (listInsert(my_list, space) < 0) {
				free(space);
				free(current_word);
			}
		
			/*Se reserva espacio para la i-esima palabra*/ 
			/* del archivo*/
			if ( (current_word = (char*) malloc(WORD_SIZE*sizeof(char)) ) == NULL ) {
				perror("malloc");
		
				exit(-2);
			}
		
		
		}
		
		
	} 


}

/* main
 * --------------
 *
 *
 */
int main (int argc, char **argv) { 
	int i_;

	int n_files, n_ps, quot, rem, p_, aux; 

	/*PS STUFF*/
	int status[MAX_PS], merger_stat; 
       	pid_t pid[MAX_PS], merger_pid; 
	
	/*PIPE STUFF*/
	int pipe_fd[2]; 

	/*ARRAYS OF STRINGS*/
	char **paths , *buff;

	int pid_dbg; 

	/*SEMAPHORE SUFF*/
	sem_t *mutex, *smp_r, *smp_w; 
	int *sem_deb, *r_controller; 
	int trash;

	/*INSIDE MERGER STUFF*/
	char* word; 
	int frequency, terminated;
	int* word_size; 
	list *freq_list; 
	node *dummie; 

	/*INSIDE COUNTERS STUFF*/
	char **help;

	int j_, k_; 
	FILE *fp; 
	char* current_word; 
	node *space;
	list *my_list;
	int *deb_semval;




	/*********************BEGINNING*********************/
	

	paths = (char**) malloc(sizeof(char*)*MAX_FILES); /*perror*/


	/*CREO PIPE*/
	if( pipe(pipe_fd)  == -1) {
		/*### usar sleep para asegurar apertura???*/
		fprintf(stderr, "Error abriendo pipe");
		perror("pipe");
		exit(-1);
	}

	/*ELIMINO SEMAFOROS POR SI EXISTEN*/
	trash = sem_unlink(SMP0);
	if( trash != 0 && errno != ENOENT)
		perror("sem_unlink");	

	trash = sem_unlink(SMP1);
	if( trash != 0 && errno != ENOENT)
		perror("sem_unlink");	

	trash = sem_unlink(SMP2);
	if( trash != 0 && errno != ENOENT)
		perror("sem_unlink");	


	/*ENCUENTRO ARCHIVOS */
	n_files = myFind(argv[2], paths); 
	/*printf("numero de archivos: %d\n",n_files); DBG*/


	/*CALCULO NUMERO DE PROCESOS A USAR*/
	n_ps = MIN(atoi(argv[1]), n_files);
	/*printf("Numero de procesos a usar %d\n",n_ps); DBG */


	/*CREO SEMAFORO*/
	if( ( mutex = sem_open(SMP0, O_CREAT | O_RDWR, MODE, 1) ) == SEM_FAILED ) {
		perror("sem_open");

		exit(-2); 
	}

	if( ( smp_r = sem_open(SMP1, O_CREAT | O_RDWR, MODE, n_ps ) ) == SEM_FAILED) {
		perror("sem_open");

		exit(-2); 
	}

	if( ( smp_w = sem_open(SMP2, O_CREAT | O_RDWR, MODE, 0) )  == SEM_FAILED) {
		perror("sem_open");

		exit(-2); 
	}





			/*********************CODIGO DEL MERGER*********************/


	switch( merger_pid = fork() ) 
	{
		default: 
			break; 
		case -1: 
			perror("fork");
			dprintf(stderr, "No se pudo abrir el merger\n");

			exit(-1);
		case 0: 
			terminated = 0; 

			if( close(pipe_fd[WRITE]) == -1)
				perror("close");

			if( dup2(pipe_fd[READ], 0) == -1)
				perror("dup2");

			if( close(pipe_fd[READ]) == -1)
				perror("close");


			word_size = (int *) malloc( sizeof(int) );
			r_controller = (int *) malloc( sizeof(int) );
			freq_list = (list *) malloc( sizeof(list) );


			listInit(freq_list); 


			while (terminated != n_ps) {

				if( sem_wait(smp_w) == -1)
					perror("sem_wait");

				if( sem_wait(mutex)  == -1)
					perror("sem_wait");


				/*********************REGION CRITICA *********************/
				/*leo el controlador*/
				if( read(0, r_controller, sizeof(int) ) == -1) /*###*/
					perror("read");
				/*fprintf(stderr,"controller %d\n", *r_controller); DBG*/

 
				if( *r_controller != -1) { 

					/*Inicializo nodo*/
					if ( (dummie = (node *) malloc( sizeof(node) ) ) == NULL )
						perror("malloc");
					
					/*leo el tamano de la palabra*/
					if( read(0, word_size, sizeof(int) ) == -1) /*###*/
						perror("read");

					/*leo la la palabra*/
					word = (char *) malloc( (*word_size) * sizeof(char) ); /*###*/
					if( read(0, word, *word_size)  == -1)
						perror("read");

					/*leo la frecuencia*/
					if( read(0, &frequency, sizeof(int) )  == -1) /*###*/
						perror("read");


					nodeInit(dummie, word, frequency); 


					listInsert(freq_list, dummie);

					/*fprintf(stderr,"controller: %d\tword_size: %d\nword: %s\tfrequency: %d\n",
						*r_controller,*word_size,word,frequency);DBG*/ 

				}
				else {
					terminated++; 
				}
				/*********************FIN DE REGION CRITICA *********************/
				/*fprintf(stderr,"terminados %d\n",terminated);*/

				if( sem_post(mutex)  == -1)
					perror("sem_post");

				if( sem_post(smp_r)  == -1)
					perror("sem_post");
				
			}

			close(0); 

			listSort(freq_list);
			listPrint(freq_list); 
			listDestroy(freq_list);

			exit(0);
	}


			/*********************FIN DE CODIGO DEL MERGER*********************/


	/* Se calcula la reparticion de archivos*/
	if ( n_ps >= n_files ) {
		quot = 1; 
		rem = 0;
	}
	else {
		quot = n_files / atoi(argv[1]) ;
		rem = n_files % atoi(argv[1]) ;
	}

			/*********************CODIGO DE CONTADORES*********************/


	for(i_=0; i_< n_ps ; i_++) {

		switch( pid[i_] = fork() ) 
		{
			case -1: 
				perror("fork"); 
				exit; 
			case 0: 

				if ( i_ != n_ps - 1) 
					aux = quot; 
				else 
					aux = quot + rem; 


				/*cierro los pipes*/
				if( close(pipe_fd[READ])  == -1)
					perror("close");

				if( dup2(pipe_fd[WRITE],1)  == -1)
					perror("dup2");

				if( close(pipe_fd[WRITE]) == -1)
					perror("close");


				if ( (my_list = (list*) malloc( sizeof(list) ) ) == NULL ) {
					perror("malloc"); 

					exit(-2); 
				}


				listInit(my_list);
			
			
				/*INSERTO NODOS*/
				countFrequencies(my_list, paths, quot, aux, i_); 
				
		
				/*fprintf(stderr," in\n"); DBG*/

				/*AQUI SE ENTRA EN LA REGION CRITICA*/
				listPrintRC(my_list, mutex, smp_r, smp_w);

				/*fprintf(stderr," out\n"); *DBG*/
			
				
				/*CIERRO SEMAFOROS*/
				if( sem_close(mutex) == -1)
						perror("sem_close");
				
				if( sem_close(smp_r) == -1)
					perror("sem_close");
				
				if (sem_close(smp_w) == -1) 
					perror("sem_close"); 
				
				
				/*CIERRO FD QUE APUNTA A PIPE*/
				close(1);
			
				/*FREE SPACE*/
				
				/*fprintf(stderr,"Antes de destruir la lista\n"); DBG*/
				listDestroy(my_list);
				/*fprintf(stderr,"Despues de destruir la lista\n"); DBG*/
				
				exit(0);

			default: 
				continue;

		}
	}

			/*********************FIN DE CODIGO DE CONTADORES*********************/
	
	

	/*CIERRO PIPES*/
	if( close(pipe_fd[0]) == -1)
		perror("close");

	if( close(pipe_fd[1]) == -1)
		perror("close");


	/*ESPERA PROCESOS*/
	for (i_=0 ; i_<n_ps ; i_++)   {

		if( (pid_dbg = wait(&status[i_]) ) == -1) 
			perror("waitpid ");
		
		/*fprintf(stderr,"termino %d\n", pid_dbg); DBG*/
	}

	if( wait(&status[0])  == -1)
		perror("waitpid");


	/*ELIMINO LOS SEMAFOROS*/
	if( sem_unlink(SMP0) == -1)
		perror("sem_unlink");

	if( sem_unlink(SMP1) == -1)
		perror("sem_unlink");

	if( sem_unlink(SMP2) == -1)
		perror("sem_unlink");
	

	/*CIERRO LOS SEMAFOROS*/
	if( sem_close(mutex) == -1)
		perror("sem_close");

	if( sem_close(smp_r) == -1)
		perror("sem_close");

	if( sem_close(smp_w) == -1)
		perror("sem_close");


	/*LIBERA ESPACIO*/
	for(i_=0; i_< n_files ; i_++) 
		free(paths[i_]);

	return 0; 
}



