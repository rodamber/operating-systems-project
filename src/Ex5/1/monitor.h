#ifndef __PARALLEL_READER_H__
#define __PARALLEL_READER_H__

#include "../../../Ex1/wrrd.h"

#define BUFFER_SIZE 10
#define NB_THREADS	20

char buffer[BUFFER_SIZE][FNLEN + 1];
int  nb_readers;
int  next_read_index;
int  next_write_index;

sem_t sem_no_info;
sem_t sem_info;
pthread_mutex_t buffer_mutex;


void* reader(void*);

#endif /* end of include guard: __PARALLEL_READER_H__ */
