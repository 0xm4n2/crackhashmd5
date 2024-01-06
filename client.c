#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./Libraries/Client/process.h"
#include "./Libraries/Client/heap.h"
#include "./Libraries/Client/bruteforce.h"



int main(int argc, char **argv) {
    if (argc != 4) {
        return printf("usage: %s [ip] [port] [password file]\n", argv[0]);
    }

    // load wordlist
    char **passwords = load_from_file(argv[3]);
    if (!passwords)
        return fprintf(stderr, "couldnt load from file: %s\n", argv[3]);

    // setup socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (!clientfd) return fprintf(stderr, "socket(): %s\n", strerror(errno));
    struct sockaddr_in server_addr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = inet_addr(argv[1]),
        .sin_port        = htons(atoi(argv[2])),
    };

    if (connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        return fprintf(stderr, "connect(): %s\n", strerror(errno));

    printf("connected to %s:%d\n", argv[1], atoi(argv[2]));
    handle(clientfd, passwords);

    // free passwords
    for (int i = 0; passwords[i]; i++) {
        free(passwords[i]);
    }
    free(passwords);
}
