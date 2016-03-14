CC=gcc
CFLAGS=-W -Wall
EXEC=project1
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

project1: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f *.o

mrclean: clean
	rm -f $(EXEC)
