/*
 * Identification
 *
 * Group 24
 *
 * 78294  José Semedo
 * 78471  João Marçal
 * 78942  Rodrigo Bernardo
 */

#ifndef __WRRD_H__
#define __WRRD_H__

#define CYCLENUM 512           /* number of times to do the whole process */
#define STRNUM   1024	        /* number of strings to write */
#define STRLEN   10		/* length of the strings to be written */
#define FILENUM  5		/* number of possible files to write on */
#define FNLEN    12		/* filename length */


/*
 * dst will point to a string like "SO2014-X.txt", where X is a random integer
 * between 0 and FILENUM. Uses the rand() function, so maybe you'll want to
 * set a seed using srand().
 */
void getfile(char *dst);

/*
 * dst will point to a STRLEN sized string composed of STRLEN - 1  equal
 * characters between 'a' and 'a' + STRLEN plus a '\n'. Uses the rand()
 * function, so maybe you'll want to set a seed using srand().
 */
void getstr(char *dst);

int corrige(const char * filename);


#endif
