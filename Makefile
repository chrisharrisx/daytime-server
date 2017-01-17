CC = gcc
CFLAGS = -std=c99 -g -Wall -D_POSIX_C_SOURCE=200112L
SOURCES = server.c
OBJECTS = $(SOURCES:.c=.o)
MAIN = server

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(MAIN)

clean:
	@rm -f $(OBJECTS) $(MAIN)
	@rm -rf $(MAIN).dSYM
