CC=gcc
CFLAGS=-W -Wall
PATH1=/home/tux/local/include/
PATH2=/home/tux/local/lib/

all:exec

mymalloc.o: mymalloc.c header.h
	$(CC) -c mymalloc.c

myfree.o: myfree.c header.h
	$(CC) -c myfree.c

mycalloc.o: mycalloc.c header.h
	$(CC) -c mycalloc.c

test.o: tests.c header.h
	$(CC) -I$(PATH1) -L$(PATH2) -lcunit -c tests.c

exec: tests.o mymalloc.o myfree.o mycalloc.o
	$(CC) -I$(PATH1) -L$(PATH2) -lcunit -o exec tests.o mymalloc.o myfree.o mycalloc.o

clean:
	rm -f *.o
