CC = gcc
CFLAGS=-g -Wall -Werror -fsanitize=address -std=c99
DEPS = mymalloc.h
LFLAGS=-lm
OUTPUT=mymalloc
OBJ =  memgrind.o mymalloc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: mymalloc

mymalloc: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

mymalloc.o: mymalloc.h

clean:
	rm -f *.o $(OUTPUT)

