CC=gcc
CFLAGS=-lm

all: client server


client: client.c
	$(CC) client.c -o client

server: server.c
	$(CC) server.c -o server -lm

clean:
	rm client server
