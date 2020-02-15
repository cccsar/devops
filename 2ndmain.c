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


#define WRITE 1
#define READ 0

#define MAX_PS 1000 

#define WORD_SIZE 20

#define STANDARD_SIZE 419 

#define SMP0 "/mutex"
#define SMP1 "/sem_reader"
#define SMP2 "/sem_writer"
#define MODE S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH

#define MIN(a,b) (a < b)? a: b;

sem_t *mutex, *smp_r, *smp_w; 


/* countFrequencies
 * --------------
 *  	Cuenta el numero de ocurrencias de una palabra en un archivo. Para ello
 *  	lee cada palabra del archivo y la inserta en una "lista de frecuencias"
 *
 *  	Recibe los archivos de un arreglo de strings, seleccionando solo un 
 *  	segmento de este.
 *
 * 		
 *	my_list:  lista de frecuencias
 *	paths: arreglo con los nombres de los archivos a leer
 *	floor: cota inferior del arreglo de archivos a leer
 *	ceil: cota superior del arreglo de archivos a leer
 *	reference: se utiliza para desplazarse sobre el arreglo de string 
 *
 */
void countFrequencies(list *my_list, char** paths, int floor, int ceil, int reference) {
	int j_, *word_size, *controller; 
	FILE *fp; 

	char* current_word; 
	node *space;
	struct stat fstat; 


	word_size = (int *) malloc( sizeof(int) );
	controller = (int *) malloc( sizeof(int) ); 
	current_word = (char *) malloc( sizeof(char) * WORD_SIZE + 1 );


	for(j_=floor*reference; j_ < floor*reference + ceil   ; j_++) { 
	

		if ( !(fp = fopen(paths[j_],"r")) ){

			perror("fopen"); 
		
			exit(-3); 
		}

		if( lstat(paths[j_], &fstat)  == -1)
			perror("lstat");
		
		*controller = 0;
		while( fscanf(fp,"%s",current_word) != EOF) { 
		
			sem_wait(smp_r); 
			sem_wait(mutex); 
		
			write(1, controller, sizeof(int)); 

			*word_size = strlen(current_word); 
			write(1, word_size, sizeof(int) ); 

			write(1, current_word,  *word_size*sizeof(char) +  1);


			sem_post(mutex); 
			sem_post(smp_w); 
			/*if ( ( space = (node*) malloc( sizeof(node) ) ) == NULL ) {*/
				/*perror("malloc");*/
				/*exit(-2);*/
			/*}*/
		
			/*nodeInit(space, current_word, 1); */
		
			/* En caso de que solo la frecuencia de un elemento 
			 * se aumente como ese nodo ya esta creado, se libera
			 * la memoria que se almaceno para insertarlo. */
			/*if (listInsert(my_list, space) < 0) {*/
				/*free(space);*/
				/*free(current_word);*/
			/*}*/
		
			/* Se reserva espacio para la i-esima palabra 
			 * del archivo */
		
		}

		if( fclose(fp) == -1)
			perror("fclose");

		
		
	} 
	*controller = -1; 

	sem_wait(smp_r); 
	sem_wait(mutex); 
	
	write(1, controller, sizeof(int) );
	
	sem_post(mutex); 
	sem_post(smp_w);


}



/* main
 * --------------
 *	
 *
 *
 */
int main (int argc, char **argv) { 
	int n_files, n_ps, quot, rem, aux, i_; 
	char **paths ;

	/*	Procesos 	*/
	int status[MAX_PS], merger_stat; 
       	pid_t pid[MAX_PS], merger_pid; 
	
	/*	Pipe	*/
	int pipe_fd[2]; 

	/*	Semaforo	*/
	int *sem_deb, *r_controller; 
	int trash;

	/*	Proceso mezclador	 */
	char* word; 
	int frequency, terminated;
	int* word_size; 
	list *freq_list; 
	node *dummie; 

	/*	Procesos contadores 	*/
	int j_, k_; 
	list *my_list;
	int *deb_semval;
	int whiler; 

	int pid_dbg; 

	deb_semval = (int *) malloc( sizeof(int) );


	/*	Creo pipe	*/
	if( pipe(pipe_fd)  == -1) {
		fprintf(stderr, "Error abriendo pipe");
		perror("pipe");

		exit(-3);
	}

	/* 	Elimino a los semaforos en caso de que existan antes 	*/
	trash = sem_unlink(SMP0);
	if( trash != 0 && errno != ENOENT)
		perror("sem_unlink");	

	trash = sem_unlink(SMP1);
	if( trash != 0 && errno != ENOENT)
		perror("sem_unlink");	

	trash = sem_unlink(SMP2);
	if( trash != 0 && errno != ENOENT)
		perror("sem_unlink");	



	/*	 Ubico los archivos a procesar		*/
	paths = (char**) malloc(sizeof(char*) * STANDARD_SIZE); /*perror*/
	if (paths == NULL ) { 
		perror("malloc");
		exit(-1); 
	}

	n_files = myFind(argv[2], &paths); 
	/*printf("numero de archivos encontrados: %d\n",n_files);*/
	/*printf("direccion de path %p\t tamano: %d\n",(void*) paths, malloc_usable_size(paths));*/


	/*	Calculo el numero de procesos a usar 	*/
	n_ps = MIN(atoi(argv[1]), n_files);




	/*	Creo a los semaforos	*/
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


	/* 		Proceso merger
	 *
	 * 	Para empezar cierra los extremos del pipe que no se usaran
	 *
	 * 	Luego espera por la escritura al pipe en un semaforo
	 *
	 *
	 * 	Del pipe primero lee una variable "r_controller", que indica si 
	 * 	un proceso contador ha escrito o si ya termino de escribir. 
	 * 	En el primer caso, continua leyendo en el formato de escritura
	 * 	de los procesos contadores.
	 *
	 * 	
	 * 	Este proceso espera hasta que los contadores hayan dejado de 
	 * 	escribir al pipe, y luego imprime una lista de frecuencias 
	 * 	ordenada por salida estandar
	 *
	 */

	switch( merger_pid = fork() ) 
	{
		default: 
			break; 

		case -1: 
			perror("fork");
			fprintf(stderr, "No se pudo abrir el merger\n");

			exit(-4);

		case 0: 

			if( close(pipe_fd[WRITE]) == -1) {
				perror("close");
				
				exit(-3); 
			}

			if( dup2(pipe_fd[READ], 0) == -1) {
				perror("dup2");

				exit(-3); 
			}

			if( close(pipe_fd[READ]) == -1) {
				perror("close");

				exit(-3);
			}



			word_size = (int *) malloc( sizeof(int) );
			if( word_size == NULL) { 
				perror("malloc"); 

				exit(-1); 
			}
			r_controller = (int *) malloc( sizeof(int) );
			if( r_controller == NULL ) {
				perror("malloc");

				exit(-1);
			}
			freq_list = (list *) malloc( sizeof(list) );
			if( freq_list == NULL ) {
				perror("malloc");

				exit(-1);
			}


			listInit(freq_list); 

			terminated = 0; 

			while (terminated != n_ps) {

				if( sem_wait(smp_w) == -1) {
					perror("sem_wait");

					exit(-2);
				}

				if( sem_wait(mutex)  == -1) {
					perror("sem_wait");

					exit(-2);
				}

				/*********************REGION CRITICA *********************/

				read(0, r_controller, sizeof(int) ) ; 

 
				if( *r_controller != -1) { 


					/*Inicializo nodo*/
					dummie = (node *) malloc( sizeof(node) );
					if( dummie == NULL ) {
						perror("malloc");

						exit(-1);
					}
					
					/*leo el tamano de la palabra*/
					read(0, word_size, sizeof(int) ); 

					/*leo la la palabra*/
					word = (char *) malloc((*word_size) * sizeof(char)); 
					if( word == NULL ) {
						perror("malloc");

						exit(-1);
					}
					read(0, word, *word_size + 1);

					/*leo la frecuencia*/
					/*read(0, &frequency, sizeof(int) );*/



					/*nodeInit(dummie, word, frequency); */
					nodeInit(dummie, word, 1); 

					listInsert(freq_list, dummie);

				}
				else  
					terminated++; 


				/*********************FIN DE REGION CRITICA *********************/


				if( sem_post(mutex)  == -1) {
					perror("sem_post");

					exit(-2);
				}

				if( sem_post(smp_r)  == -1) {
					perror("sem_post");

					exit(-2);
				}
				
			}

			close(0); 

			listSort(freq_list);
			listPrint(freq_list); 

			exit(0);
	}



	/*		 Se calcula la reparticion de archivos		
	 *	Si se piden mas procesos que archivos encontrados, entonces se utilizaran
	 *	tantos procesos como archivos.
	 *
	 *	De lo contrario	se reparte una cantidad de "quot" archivos por proceso, 
	 *	salvo en el ultimo proceso, que recibe "quot + rem" archivos.
	 *
	 */
	
	if ( n_ps >= n_files ) {
		quot = 1; 
		rem = 0;
	}
	else {
		quot = n_files / atoi(argv[1]) ;
		rem = n_files % atoi(argv[1]) ;
	}


	/*	Procesos contadores
	 *
	 *
	 *	Comienzan cerrando los file descriptors del pipe que no se usaran
	 *
	 *	Luego calculan la frecuencia de las palabras en los archivos 
	 *	recibidos. Esto se almacena en una lista de frecuencias
	 *
	 *	Despues de esto pasan a escribir el contenido de la lista en un 
	 *	pipe, un nodo a la vez (con un formato en particular). Esto es 
	 *	mediado por semaforo, de forma que mientras un proceso escribe, ninguno 
	 *	otro lee o escribe. 
	 *
	 *	por ultime liberan buffers y cierran file descriptors
	 */

	for(i_=0; i_< n_ps ; i_++) {

		switch( pid[i_] = fork() ) 
		{
			default: 
				continue;

			case -1: 
				perror("fork"); 

				exit(-4); 

			case 0: 

				if ( i_ != n_ps - 1) 
					aux = quot; 
				else 
					aux = quot + rem; 


				/*Cierro extremos del pipe no usados*/
				if( close(pipe_fd[READ])  == -1) {
					perror("close");

					exit(-3); 
				}

				if( dup2(pipe_fd[WRITE],1)  == -1) {
					perror("dup2");

					exit(-3); 
				}

				if( close(pipe_fd[WRITE]) == -1) {
					perror("close");

					exit(-3); 
				}


				my_list = (list*) malloc( sizeof(list) ); 
				if (my_list == NULL ) {
					perror("malloc"); 

					exit(-1); 
				}
				listInit(my_list);
			

				/*	Inserto nodos y cuento frecuencias	*/
				countFrequencies(my_list, paths, quot, aux, i_); 
				
				/*	Escribo mi lista de frecuencias al pipe	*/
				/*listPrintRC(my_list, mutex, smp_r, smp_w);*/



				if( sem_close(mutex) == -1) 
					perror("sem_close");
				
				if( sem_close(smp_r) == -1)
					perror("sem_close");
				
				if (sem_close(smp_w) == -1) 
					perror("sem_close"); 


				close(1); 


				listDestroy(my_list); 
				
				
				exit(0);


		}
	}

	
	

	/*	Cierro pipes	*/
	if( close(pipe_fd[0]) == -1)
		perror("close");

	if( close(pipe_fd[1]) == -1)
		perror("close");


	/*	Espero procesos		*/
	for (i_=0 ; i_<n_ps ; i_++)   {

		if( (pid_dbg = wait(&status[i_]) ) == -1) 
			perror("waitpid ");

	}

	if( wait(&status[0])  == -1)
		perror("waitpid");


	/*	Elimino Semaforos	*/
	if( sem_unlink(SMP0) == -1)
		perror("sem_unlink");

	if( sem_unlink(SMP1) == -1)
		perror("sem_unlink");

	if( sem_unlink(SMP2) == -1)
		perror("sem_unlink");
	

	/*	Cierro los semaforos 	*/
	if( sem_close(mutex) == -1)
		perror("sem_close");

	if( sem_close(smp_r) == -1)
		perror("sem_close");

	if( sem_close(smp_w) == -1)
		perror("sem_close");


	return 0; 
}



				/*DEBUGGING DE SEMAFOROS*/
			/*fprintf(stderr,"#####COUNTER INSIDE RC DBG#####%d\n",getpid());

			if( sem_getvalue(reader, deb_semval)  == -1)
				perror("sem_getvalue");
			fprintf(stderr,"  Valor de reader:  %d\n", *deb_semval); 

			if( sem_getvalue(writer, deb_semval)  == -1)
				perror("sem_getvalue");
			fprintf(stderr,"  Valor de writer:  %d\n", *deb_semval); 

			if( sem_getvalue(mutex, deb_semval)  == -1)
				perror("sem_getvalue");
			fprintf(stderr,"  Valor de mutex:  %d\n", *deb_semval); */
