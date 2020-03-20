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
#include <semaphore.h>
#include <errno.h>

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

	pid_t w_pid[MAX_PS], r_pid, term;  
	int w_status[MAX_PS], r_status, n_ps;

	int pfd[2];

	sem_t *mutex, *smp_r, *smp_w; 

	/*BUFFERS DE LECTURA / ESCRITURA */
	char *r_buffer;  
	char *w_buffer;
	pid_t *curr_ps;
	pid_t *forked_pid;

	/*OTROS*/
	int numbers[NSIZE];
	char newline[1];
	int trash;


	newline[0] = '\n';

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
			if( ( r_buffer = (char*) malloc( sizeof(char) * MSG_LEN + 1) ) == NULL)
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


			for(i_=0; i_<n_ps ; i_++) {
	
				/*mientras leer el tamano de mensaje devuelva el tamano de mensaje*/
				
				if( sem_wait(smp_w) == -1 )
					perror("sem_wait");

				if( sem_wait(mutex) == -1 )
					perror("sem_wait");


					/*REGION CRITICA*/

				if( read(0, r_buffer, MSG_LEN) == -1) 
					perror("read");
					
				if( read(0, curr_ps, sizeof(pid_t) ) == -1)
					perror("read");

					/*FIN DE LA REGION CRITICA*/


				if( sem_post(mutex) == -1 )
					perror("sem_post");

				if( sem_post(smp_r) == -1 )
					perror("sem_post");


				if( printf("%s %d\n", r_buffer, *curr_ps) == -1)
					perror("printf");
			}	



			close(pfd[READ]);

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


				w_buffer = (char*) malloc( sizeof(char) * MSG_LEN + 1);
				forked_pid = (pid_t *) malloc( sizeof(pid_t) );


				w_buffer = MSG;
				*forked_pid = getpid();


				/*fprintf(stderr,"FORKEO UN PROCESO ESCRITOR, PID %d\n", getpid());*/


				if( sem_wait(smp_r) == -1)
					perror("sem_wait");

				if( sem_wait(mutex) == -1)
					perror("sem_wait");


					/*REGION CRITICA*/

				if( write(1, w_buffer, MSG_LEN) == -1)
					perror("write");
				if( write(1, forked_pid, sizeof( pid_t ) )  == -1)
					perror("write");

					/*FIN DE REGION CRITICA*/


				if( sem_post(mutex) == -1)
					perror("sem_post");

				if( sem_post(smp_w) == -1)
					perror("sem_post");


				close(pfd[WRITE]);

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

