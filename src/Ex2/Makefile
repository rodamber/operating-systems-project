# Identification

# Group  24

# 78294  José Semedo
# 78471  João Marçal
# 78942  Rodrigo Bernardo


CFLAGS=-ansi -Wall -Wextra -pedantic

all: p_wr
	(cd ../Ex1/; make all)

p_wr: parallel_writer.o
	gcc ${CFLAGS} -o p_wr parallel_writer.o

parallel_writer.o: parallel_writer.c
	gcc ${CFLAGS} -c -g parallel_writer.c

clean:
	rm -f *.o wr rd p_wr
	(cd ../Ex1/; make clean)
