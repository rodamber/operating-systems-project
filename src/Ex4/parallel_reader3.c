#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "../Ex1/wrrd.h"

/*
 *  FIXME: Falar daquilo dos mutex e da variavel que permite ver se o ficheiro esta
 *  escrito apenas por um tipo de letra
 *
 */

int thread_maker (int  nbThreads){

  int thread_id_list[nbThreads];
  pthread_t thread_list[nbThreads];
  int nb_lines = 1024/k; /* pode ser a causa de algum erro care ss*/
  int i = 0;

  void ** return_values[nbThreads];
  
  char filename[FNLEN + 1];
  
  getfile(filename);
  
  printf("Os threads vao executar sobre o ficheiro: %s\n", &filename);

  void ** return_values[nbThreads]; 

  for( ; i < nbThreads-1; i++){
    thread_id_list[i] = pthread_create ( &thread_list[i], NULL, &reader, (void *) &/*fd*/, (void*) &(i*nb_lines), (void*) &(nb_lines), (void*) &filename );
  }
  /*last thread made can have different number of lines to read, thus a separate case is needed*/
  thread_id_list[nbThreads-1] = pthread_create ( &thread_list[i], NULL, &reader, (void *) &/*fd*/, (void*) &(i*nb_lines), (void*) &( 1024 -(nb_lines*(i - 1))), (void*) &filename);
  
  thread_id_list[nbThreads-1] = pthread_creat ( &thread_list[i], NULL, (void*) &/*FIX ME*/, (void *) &/*fd*/, (void*) &(i*nb_lines), (void*) &( 1024 -(nb_lines*(i - 1))));


  for(i=0; i < nbThread; i++){

    pthread_join (thread_list[i], return_values[i]);
  }

  for(i=0; i < nbThread; i++){
    if ( *(int*) return_values[i] != 0){
      printf("o thread %d deu treta, comeca a ler na linha %d", i+1, (i*nb_lines));
      return -1;
    }
    return 0;
  }



void* reader(void* argv) {

    char line[STRLEN + 1];
    char firstline[STRLEN + 1];
    int  i;
    int  fdesc;     /* file descriptor */
    int  strn;

    /*
     * Open file. Return if there was an error opening the file.
     *
     * O_RDONLY: Open the file so that it is read only.
     */
    if ((fdesc = open(filename, O_RDONLY)) < 0) {
        perror("Error opening file");
        exit(-1);
    }

    printf("Checking %s...\n", filename);

    if (flock(fdesc, LOCK_SH) < 0) {
        perror("Error locking file");
        exit(-1);
    }

    /*
     * Read file. Return if there was an error reading the file.
     */
    if ((read(fdesc, firstline, STRLEN)) < 0) {
        perror("Error reading file");
        exit(-1);
    }

    firstline[STRLEN] = '\0';

    /*
     * First line must be composed of STRLEN - 1  equal chars between
     * 'a' and 'j', followed by a newline character, '\n'.
     */
    if (strlen(firstline) != STRLEN || firstline[0] < 'a'
                                    || firstline[0] > 'j') {
        exit(-1);
    }
    for (i = 1; i < STRLEN - 1; i++) {
        if (firstline[i] != firstline[0]) {
            exit(-1);
        }
    }
    if (firstline[STRLEN - 1] != '\n') {
        exit(-1);
    }

    /*
     * Check if all lines are equal. Return if not.
     */
    for  (strn = 0; read(fdesc, line, STRLEN); strn++) {
        line[STRLEN] = '\0';

        if (strcmp(line, firstline)) {
            exit(-1);
        }
    }

    /*
     * Return if there aren't STRNUM valid strings in the file or if there
     * was an error reading the file.
     */
    if (strn != STRNUM - 1) { /* -1 because the first line was already read */
        exit(-1);
    }

    if (flock(fdesc, LOCK_UN) < 0) {
        perror("Error unlocking file");
        exit(-1);
    }

    /*
     * Return upon failure to close.
     */
    if (close(fdesc) < 0) {
        perror("Error closing file");
        exit(-1);
    }

    printf("%s is correct.\n", filename);
    return 0;
}
