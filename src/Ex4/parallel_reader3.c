#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int thread_maker (int  nbThreads){

  int thread_id_list[nbThreads];
  pthread_t thread_list[nbThreads];
  int nb_lines = 1024/k; /* pode ser a causa de algum erro care ss*/
  int i = 0;
  void ** return_values[nbThreads];
  

  for( ; i < nbThreads-1; i++){
    thread_id_list[i] = pthread_create ( &thread_list[i], NULL, (void*) &/*FIX ME*/, (void *) &/*fd*/, (void*) &(i*nb_lines), (void*) &(nb_lines));
  }
  thread_id_list[nbThreads-1] = pthread_creat ( &thread_list[i], NULL, (void*) &/*FIX ME*/, (void *) &/*fd*/, (void*) &(i*nb_lines), (void*) &( 1024 -(nb_lines*(i - 1))));
  

  for(i=0; i < nbThread; i++){
    
    pthread_join (thread_list[i], return_values[i]);
  }

  for(i=0; i < nbThread; i++){
    if ( *(int*) return_values[i] != 0){
      printf("o thread %d deu treta que começo a ler na linha %d", i+1, (i*nb_lines));
      return -1;
    }
    return 0;
  }

