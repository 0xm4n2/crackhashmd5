CC = gcc
CFLAGS = -O3 -o
LIBS = -lcrypto

all: client server

client: client.c
    $(CC) $(CFLAGS) client client.c Libraries/Client/bruteforce.c Libraries/Client/heap.c Libraries/Client/process.c$(LIBS)

server: server.c
    $(CC) $(CFLAGS) server server.c Libraries/Server/process.c Libraries/Server/stack.c$(LIBS)

clean:
    rm -f client server
