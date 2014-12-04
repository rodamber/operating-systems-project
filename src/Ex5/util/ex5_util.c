#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ex5_util.h"


int main(void) {
    char word[13] = {'\0'};
    int ret;

    printf("Hello mate. Insert a word\n");
    while (strcmp(word, "sair") != 0) {
        if ((ret = read_word(word, 12)) == -1) {
            die("Error reading from stdin");
        }
        printf("That's your word mate: %s\n", word);
    }
    printf("return of read_word: %d\n", ret);
    return EXIT_SUCCESS;
}

void die(const char* msg) {
    perror(msg);
    exit(-1);
}

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

/**
 * Reads a word from stdin.
 */
int read_word2(char* dst, int max_length) {
    int  i;
    char c;

    for (i = 0; i < max_length; i++) {
        if (read(STDIN_FILENO, &c, 1) == -1) {
            return -1;
        }
        if (c != '\n' && c != ' ' && c != EOF) {
            dst[i] = c;
        }
        else {
            break;
        }
    }
    dst[i] = '\0';

    while (c != '\n' && c != ' ' && c != EOF) {
        if (read(STDIN_FILENO, &c, 1) == -1) {
            return -1;
        }
    }
    return i;
}

