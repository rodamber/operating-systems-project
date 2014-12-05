#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ex5_util.h"


int read_word(char* dst, int max_length) {
    int  i = 0;
    char c;

    while (i < max_length && (c = read_char()) != '\n' && c != ' ' && c != EOF) {
        if (c == -1) {
            return -1;
        }
        dst[i++] = c;
    }
    dst[i] = '\0';

    while (c != '\n' && c != ' ' && c != EOF) {
        c = read_char();
    }
    return i;
}

char read_char() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1) {
        return -1;
    }
    return c;
}

