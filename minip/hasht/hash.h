/*
 * --------------
 *
 *
 */
#include "singly.h"

#ifndef __HASHT__
#define __HASHT__

/*constant for testing*/
#define HASH_SIZE 499

/* hasht
 * --------------
 *
 *
 */
typedef singly * hasht[HASH_SIZE]; 

/* hashtInit
 * --------------
 *
 *
 */
void hashtInit(hasht h_);


/* hashDestroy
 * --------------
 *
 *
 */
void hashDestroy(hasht h_) ;


/* hashtInsert
 * --------------
 *
 *
 */
int hashtInsert(hasht h_, int number);


/* hashtPrint
 * --------------
 *
 *
 */
void hashtPrint(hasht t_) ;


/* hashTesting 
 * --------------
 *
 *
 */
int hashTesting () ;

#endif
