/* wrrd.h -- header of writer.c and reader.c source files */


#ifndef __WRRD_H__
#define __WRRD_H__

#define TIMES_TO_CYCLE 5120     /* number of times to do the whole process */
#define TIMES_TO_WRITE 1024	/* number of strings to write */
#define STRLEN  10		/* length of the strings to be written */
#define FILENUM 5		/* number of possible files to write on */

char *getfilename();
char *getstr();

#endif
