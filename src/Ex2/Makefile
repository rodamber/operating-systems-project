# Identification

# Group  24

# 78294  José Semedo
# 78471  João Marçal
# 78942  Rodrigo Bernardo


CFLAGS=-ansi -Wall -Wextra -pedantic

all: wr rd p_wr

rd: reader.o wrrdaux.o
	gcc ${CFLAGS} -o rd reader.o wrrdaux.o

wr: writer.o wrrdaux.o
	gcc ${CFLAGS} -o wr writer.o wrrdaux.o

p_wr: parallel_writer.o
	gcc ${CFLAGS} -o p_wr parallel_writer.o

parallel_writer.o:
	gcc ${CFLAGS} -c -g parallel_writer.c

writer.o: writer.c wrrd.h
	gcc ${CFLAGS} -c -g writer.c

reader.o: reader.c wrrd.h
	gcc ${CFLAGS} -c -g reader.c

wrrdaux.o: wrrdaux.c wrrd.h
	gcc ${CFLAGS} -c -g wrrdaux.c

clean:
	rm -f *.o wr rd p_wr
