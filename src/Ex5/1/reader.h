#ifndef __READER_H__
#define __READER_H__


#include "../../Ex1/wrrd.h"

#define BUFFER_SIZE 10
#define NB_READERS  20

char buffer[BUFFER_SIZE][FNLEN + 1];

extern int  next_read_index;
extern int  next_write_index;

sem_t 		   sem_no_info;
sem_t 		   sem_info;
pthread_mutex_t buffer_mutex;


void* reader(void*);
void* writer(void*);


#endif /* end of include guard: __READER_H__ */
