CC = gcc
CFLAGS = -std=c99
FILES = server.c
OBJECTS = server

all:
	$(CC) $(CFLAGS) $(FILES) -o $(OBJECTS)

clean:
	rm $(OBJECTS)
 
