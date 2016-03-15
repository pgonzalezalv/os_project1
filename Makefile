CC=gcc
CFLAGS=-W -Wall
PATH1=$(HOME)/local/include
PATH2=$(HOME)/local/lib

all:hello

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) -c mymalloc.c

myfree.o: myfree.c myfree.h mymalloc.h
	$(CC) -c myfree.c

mycalloc.o: mycalloc.c mycalloc.h mymalloc.h
	$(CC) -c mycalloc.c

test.o: test.c mymalloc.h myfree.h mycalloc.h
	$(CC) -I$(PATH1) -L$(PATH2) -lcunit -c test.c

hello: test.o mymalloc.o myfree.o mycalloc.o
	$(CC) -I$(PATH1) -L$(PATH2) -lcunit -o hello test.o mymalloc.o myfree.o mycalloc.o

clean:
	rm -f *.o
