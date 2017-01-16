CC = gcc
CFLAGS = -std=c99 -g -Wall
SOURCES = server.c
OBJECTS = $(SOURCES:.c=.o)
MAIN = server

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(MAIN)

clean:
	rm $(OBJECTS) $(MAIN)
