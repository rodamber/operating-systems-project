#include <stdlib.h>
#include <string.h>
#include "wrrd.h"

char *getfilename() {
    /* 
     * Returns a string of type "SO2014-X.txt", where X is a random integer
     * between 0 and FILENUM.
     */
    int r = rand() % FILENUM;
    char *fn = (char*)malloc(sizeof(char) * 13);
    char *prefix = "SO2014-";
    char number[2] = {'0' + r};	/* number between 0 and FILENUM - 1 */
    char *ext = ".txt";

    strcpy(fn, prefix);
    strcat(fn, number);
    strcat(fn, ext);

    return fn;
}


char *getstr() {
    /* 
     * Returns a STRLEN size character string composed of STRLEN - 1 equal 
     * characters between 'a' and 'a' + STRLEN plus a '\n'.
     */
    int  r = rand() % STRLEN, i = 0;
    char *str = (char*)malloc(sizeof(char) * (STRLEN + 1));
    char letter = 'a' + r;

    while(i++ < STRLEN - 1)
	str[i] = letter;

    str[i++] = '\n';
    str[i] = '\0';

    return str;
}
