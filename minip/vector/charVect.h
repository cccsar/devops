


#ifndef __CHARVECT__
#define __CHARVECT__

/*	CODE GOES HERE		*/

/*
 * --------------
 *
 *
 */
typedef struct { 
	char **words; 
	int size; 
} vect;  

/*
 * --------------
 *
 *
 */
void initVect(vect *vv) ; 

/*
 * --------------
 *
 *
 */
void destVect(vect *vv) ;

/*
 * --------------
 *
 *
 */
void resizeVect(vect *vv) ;

/*
 * --------------
 *
 *
 */
void putVect(vect *vv, char* word) ; 

/*
 * --------------
 *
 *
 */
void printVect(vect *vv) ; 

/*
 * --------------
 *
 *
 */
int testing() ;

#endif 
