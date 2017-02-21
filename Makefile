CC=gcc
CFLAGS=-g -Wall --std=gnu99
all:
	$(CC) snake.c -o snake -lncurses $(CFLAGS)
clean:
	rm *o snake

