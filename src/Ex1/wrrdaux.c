/*
 * Identification
 *
 * Group  24
 *
 * 78294  José Semedo
 * 78471  João Marçal
 * 78942  Rodrigo Bernardo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "wrrd.h"


void getfile(char *dst, char n) {
    char *prefix = "SO2014-";
    char number[2];
    char *ext = ".txt";

    if (n < 0) {
        n = '0' + rand() % FILENUM;
    }

    number[0] = n;
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


int corrige(const char * filename) {
    char firstline[STRLEN + 1];
    int i;
    int fdesc;

    /* Abre o ficheiro para leitura */
    if ((fdesc = open(filename, O_RDONLY)) < 0) {
	return -1;
    }

    if (flock(fdesc, LOCK_EX) < 0) {
	perror("Error opening file");
	return -1;
    }

    /* Le o primeiro caracter do ficheiro  */
    if (read(fdesc, firstline, 1) < 0) {
	return -1;
    }

    firstline[STRLEN] = '\0';

    /* Setup de uma linha com caracteres iguais ao primeiro caracter do ficheiro */
    for (i = 1; i < STRLEN - 1; i++) {
	firstline[i] = firstline[0];
    }

    firstline[STRLEN - 1] = '\n';

    /* Fechar o ficheiro */
    if (close(fdesc) < 0) {
	return -1;
    }

    /* Abrir o ficheiro para escrita */
    if ((fdesc = open(filename, O_WRONLY)) < 0) {
	return -1;
    }

    /* Escrever a firstline no ficheiro STRNUM vezes */
    for (i = 0; i < STRNUM; i++) {
	if (write(fdesc, firstline, STRLEN) != STRLEN) {
	    return -1;
	}
    }

    if (flock(fdesc, LOCK_UN) < 0) {
	perror("Error unlocking file");
    }

    /* Fechar o ficheiro */
    if (close(fdesc) < 0) {
	return -1;
    }

    printf("%s is now correct.\n", filename);
    return 0;
}
