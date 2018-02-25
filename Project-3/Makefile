CC=gcc
CFLAGS=-lm

all: CLIENT DHCP


CLIENT: UDPClient.c
	$(CC) UDPClient.c -o CLIENT 

DHCP: UDPServer.c
	$(CC) UDPServer.c -o DHCP

clean:
	rm CLIENT DHCP
