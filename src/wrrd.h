#ifndef __WRRD_H__
#define __WRRD_H__

#define CYCLENUM 5120           /* number of times to do the whole process */
#define STRNUM   1024	        /* number of strings to write */
#define STRLEN   10		/* length of the strings to be written */
#define FILENUM  5		/* number of possible files to write on */
#define FNLEN    12		/* filename length */


/* 
 * Returns a string of type "SO2014-X.txt", where X is a random integer
 * between 0 and FILENUM.
 */
void getfile(char *dst);

/* 
 * Returns a STRLEN sized character string composed of STRLEN - 1 equal 
 * characters between 'a' and 'a' + STRLEN plus a '\n'.
 */
void getstr(char *dst);

#endif
