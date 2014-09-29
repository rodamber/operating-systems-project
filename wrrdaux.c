#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wrrd.h"

void getfile(char *dst) {
    /* 
     * Returns a string of type "SO2014-X.txt", where X is a pseudo-random 
     * integer between 0 and FILENUM.
     */
    int r;
    char *prefix = "SO2014-";
    char number[2];
    char *ext = ".txt";

    /* 
     * Launch seed based on current time and then get pseudo-random number.
     */
    srand(time(NULL));
    r = rand() % FILENUM;

    number[0] = '0' + r;
    number[1] = '\0';

    strcpy(dst, prefix);
    strcat(dst, number);
    strcat(dst, ext);
}


void getstr(char *dst) {
    /* 
     * Returns a STRLEN size character string composed of STRLEN - 1 equal 
     * characters between 'a' and 'a' + STRLEN ending on a newline character.
     */
    int  r;
    char letter;

    /* 
     * Launch seed based on current time and then get pseudo-random number.
     */
    srand(time(NULL));
    r = rand() % STRLEN;

    letter = 'a' + r;

    for (r = 0; r < STRLEN - 1; r++)
	dst[r] = letter;

    dst[r++] = '\n';
    dst[r] = '\0';
}
