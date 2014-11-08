#ifndef __WRRD_H__
#define __WRRD_H__

#define CYCLENUM 512           /* number of iterations */
#define STRNUM   1024	        /* number of strings to write */
#define STRLEN   10		/* length of the strings to be written */
#define FILENUM  5		/* number of possible files to write on */
#define FNLEN    12		/* file name length */


/*
 * dst will point to a string like "SO2014-X.txt", where X is n if n >= 0.
 * Otherwise X will be a random integer between 0 and FILENUM - 1.
 *
 * Uses rand(), so maybe you'll want to set a seed using srand().
 */
void getfile(char *dst, char n);

/*
 * dst will point to a STRLEN sized string composed of STRLEN - 1  equal
 * characters between 'a' and 'a' + STRLEN followed by a '\n'.
 *
 * Uses rand(), so maybe you'll want to set a seed using srand().
 */
void getstr(char *dst);

int corrige(const char * filename);


#endif
