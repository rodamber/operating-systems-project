#include <stdlib.h>
#include <string.h>
#include "wrrd.h"

void getfilename(char *dst) {
    /* 
     * Returns a string of type "SO2014-X.txt", where X is a random integer
     * between 0 and FILENUM.
     */
    int r = rand() % FILENUM;
    char *prefix = "SO2014-";
    char number[2] = {'0' + r};	/* number between 0 and FILENUM - 1 */
    char *ext = ".txt";

    strcpy(dst, prefix);
    strcat(dst, number);
    strcat(dst, ext);
}


void getstr(char *dst) {
    /* 
     * Returns a STRLEN size character string composed of STRLEN - 1 equal 
     * characters between 'a' and 'a' + STRLEN plus a '\n'.
     */
    int  r = rand() % STRLEN, i = 0;
    char letter = 'a' + r;

    while(i < STRLEN - 1)
	dst[i++] = letter;

    dst[i++] = '\n';
    dst[i] = '\0';
}
