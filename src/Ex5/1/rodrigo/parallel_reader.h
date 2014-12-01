#ifndef __PARALLEL_READER_H__
#define __PARALLEL_READER_H__

#include "../../../Ex1/wrrd.h"

#define BUFFER_SIZE 10

char buffer[BUFFER_SIZE][FNLEN + 1];
int  nb_readers = 0;
int  next_read_index = 0;

sem_t sem_info;
pthread_mutex_t buffer_mutex;


void* reader(void*);

#endif /* end of include guard: __PARALLEL_READER_H__ */
