CC = gcc
CFLAGS=-g -Wall -Werror -fsanitize=address -std=c99

all: memgrind

mymalloc: mymalloc.c
	$(CC) $(CFLAGS) -o mm mymalloc.c

memgrind: mymalloc.c memgrind.c
	$(CC) $(CFLAGS) -c mymalloc.c
	$(CC) $(CFLAGS) -o memgrind memgrind.c mymalloc.o

clean:
	rm -f mymalloc.o memgrind
