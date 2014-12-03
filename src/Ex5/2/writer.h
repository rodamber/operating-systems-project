#ifndef __WRITER_H__
#define __WRITER_H__


#define NB_WRITERS  4

int get_file_locking (void);
int get_error_writing(void);
int get_finish_flag  (void);

void* writer(void*);

#endif /* end of include guard: __WRITER_H__ */
