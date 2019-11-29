#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <dirent.h> 
#include <string.h> 
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

#define WRITE 1
#define READ 0

#define MAX_PS 1000 

#define MSG_LEN 26 
#define MSG "Estoy en la RC, mi id es: %d\n"

#define SMP0 "/mutex_1"
#define SMP1 "/mutex_2"
#define SMP2 "/mutex_3"
#define MODE S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH 

#define NSIZE 20

	/*Por ahora esta implementacion asume que el 'buffer' es el numero de procesos*/

int main (int argc, char **argv) { 
	int i_;

	/*PROCESS*/
	pid_t w_pid[MAX_PS], r_pid, term;  
	int w_status[MAX_PS], r_status, n_ps;

	/*PIPE*/
	int pfd[2];

	/*SEMAPHORE*/
	sem_t *mutex, *smp_r, *smp_w; 
	int trash;

	/*BUFFERS DE LECTURA / ESCRITURA */
	char *r_buffer;  
	char *w_buffer;
	pid_t *curr_ps;
	pid_t *forked_pid;

	/*OTROS*/
	int numbers[NSIZE];
	int *debug; 
	int curr_smpval; 
	int controller_1, term_count ;
	int *controller_2, *this_num ;



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


	if( ( n_ps = atoi( argv[1] ) ) == -1)
		perror("atoi ");


	/*CREO LOS SEMAFOROS*/
	if( ( mutex = sem_open(SMP0, O_CREAT | O_RDWR , MODE, 1) ) == SEM_FAILED)
		perror("mutex ");

	if( ( smp_r = sem_open(SMP1, O_CREAT | O_RDWR, MODE, n_ps) ) == SEM_FAILED)
		perror("smp_r ");

	if( ( smp_w = sem_open(SMP2, O_CREAT | O_RDWR, MODE, 0) ) == SEM_FAILED)
		perror("smp_w ");


	/*CREO EL PIPE*/
	if( pipe(pfd) == -1 )
		perror("pipe");


	for(i_=0; i_<NSIZE ; i_++) {
		numbers[i_] = i_;	
	}	

	/*********************READER SECTION*********************/


	switch( r_pid = fork() ) {
		default: 
			break;
		case 0:

			
			if( ( r_buffer = (char*) malloc( sizeof(char) * MSG_LEN ) ) == NULL)
				perror("malloc");

			if( ( curr_ps = (pid_t *) malloc( sizeof(pid_t) ) ) == NULL )  
				perror("malloc");


			if( close(pfd[WRITE]) == -1)
				perror("close");

			if( dup2(pfd[READ], 0) == -1)
				perror("dup2");

			if( close( pfd[READ]) == -1)
				perror("close");


			/*printf("FORKEO EL PROCESO LECTOR, PID %d\n", getpid());*/
			debug = (int*) malloc(sizeof(int));  /*###*/
			this_num = (int *) malloc( sizeof(int) );
			controller_2 = (int *) malloc( sizeof(int) );
			term_count = 0; 


			while( term_count != n_ps ) {
	
				/*mientras leer el tamano de mensaje devuelva el tamano de mensaje*/
				
				if( sem_wait(smp_w) == -1 )
					perror("sem_wait");

				if( sem_wait(mutex) == -1 )
					perror("sem_wait");


					/*REGION CRITICA*/


				if( read(0, controller_2, sizeof(int) ) == -1)
					perror("read");

				if( *controller_2 != -1)  {

					if( read(0, this_num, sizeof(int) ) == -1)
						perror("read");

				} 
				else  {
					term_count++;					
					printf("terminated already: %d\n",term_count); 
				}
				
				/*###*/
				/*curr_smpval = sem_getvalue(smp_r, debug); */
				/*printf("Valor actual del semaforo %d\n",*debug); */


					/*FIN DE LA REGION CRITICA*/


				if( sem_post(mutex) == -1 )
					perror("sem_post");

				if( sem_post(smp_r) == -1 )
					perror("sem_post");

				
				/*si un proceso termino escritura, no hace falta imprimir*/
				if (*controller_2 != -1) 
					printf("current number: %d\n", *this_num);
			}	


			close(0);
			/*free(r_buffer);*/
			/*free(curr_ps);*/


			exit(0);
		case -1:
			perror("fork");
	}


	/*********************WRITERS SECTION*********************/


	for(i_=0; i_<n_ps ; i_++) {

		switch( w_pid[i_] = fork() ) {
			default: 
				continue; 
			case 0:
				if( close(pfd[READ]) == -1)
					perror("close");

				if( dup2(pfd[WRITE], 1) == -1)
					perror("dup2");

				if( close(pfd[WRITE]) == -1)
					perror("close");


				w_buffer = (char*) malloc( sizeof(char) * MSG_LEN );
				forked_pid = (pid_t *) malloc( sizeof(pid_t) );


				w_buffer = MSG;
				*forked_pid = getpid();
				controller_1 = 1;


				/*fprintf(stderr,"FORKEO UN PROCESO ESCRITOR, PID %d\n", getpid());*/






				for(i_=0; i_<NSIZE ; i_++) {

					if( sem_wait(smp_r) == -1)
						perror("sem_wait");

					if( sem_wait(mutex) == -1)
						perror("sem_wait");

					/*REGION CRITICA*/

					controller_1 = 0;

					if(i_ == NSIZE - 1) {
						controller_1 = -1;

						if( write(1, &controller_1, sizeof(int) ) == -1)
							perror("write");
					}
					else {

						if( write(1, &controller_1, sizeof(int)) == -1)
							perror("write");
	
						if( write(1, &numbers[i_], sizeof(int)) == -1)
							perror("write");
					}


					/*FIN DE REGION CRITICA*/

					if( sem_post(mutex) == -1)
						perror("sem_post");

					if( sem_post(smp_w) == -1)
						perror("sem_post");

				}	


				close(1);
				/*free(w_buffer);*/
				/*free(forked_pid);*/


				exit(0);
			case -1:
				perror("fork");
		}
		
	}	


	/*********************FINALE*********************/

	
	/*CIERRO PIPES*/
	close(pfd[WRITE]);
	close(pfd[READ]);


	/*ESPERO PROCESOS*/
	for(i_=0; i_<n_ps + 1 ; i_++) {

		if( ( term = wait(&w_status[i_]) ) == -1)
			perror("wait");

		/*printf("El proceso %d termino exitosamente\n", term);*/
	}	
	

	/*ELIMINO A LOS SEMAFOROS */
	if( sem_unlink(SMP0) == -1)
		perror("sem_unlink");

	if( sem_unlink(SMP1) == -1)
		perror("sem_unlink");

	if( sem_unlink(SMP2) == -1)
		perror("sem_unlink");

	/*CIERRO A LOS SEMAFOROS*/
	if( sem_close(mutex) == -1)
		perror("sem_close");

	if( sem_close(smp_r) == -1)
		perror("sem_close");

	if( sem_close(smp_w) == -1)
		perror("sem_close");


	return 0; 
}

