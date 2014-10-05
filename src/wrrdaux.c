/*
 * Identification
 *
 * 78294  José Semedo
 * 78471  João Marçal
 * 78942  Rodrigo Bernardo
 */

#include <stdlib.h>
#include <string.h>
#include "wrrd.h"


void getfile(char *dst) {
    int r;
    char *prefix = "SO2014-";
    char number[2];
    char *ext = ".txt";

    r = rand() % FILENUM;

    number[0] = '0' + r;
    number[1] = '\0';

    strcpy(dst, prefix);
    strcat(dst, number);
    strcat(dst, ext);
}

void getstr(char *dst) {
    int  r;
    char letter;

    r = rand() % STRLEN;

    letter = 'a' + r;

    for (r = 0; r < STRLEN - 1; r++)
	dst[r] = letter;

    dst[r++] = '\n';
    dst[r] = '\0';
}
