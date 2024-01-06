#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./Libraries/Server/stack.h"
#include "./Libraries/Server/process.h"


int main(int argc, char **argv) {
    printf("\n");
    printf("########################################################################################################################################\n");
    printf("#      __    __       ___           _______. __    __     .______   .______       _______     ___       __  ___  _______ .______       #\n");
    printf("#     |  |  |  |     /   \\         /       ||  |  |  |    |   _  \\  |   _  \\     |   ____|   /   \\     |  |/  / |   ____||   _  \\      #\n");
    printf("#     |  |__|  |    /  ^  \\       |   (----`|  |__|  |    |  |_)  | |  |_)  |    |  |__     /  ^  \\    |  '  /  |  |__   |  |_)  |     #\n");
    printf("#     |   __   |   /  /_\\  \\       \\   \\    |   __   |    |   _  <  |      /     |   __|   /  /_\\  \\   |    <   |   __|  |      /      #\n");
    printf("#     |  |  |  |  /  _____  \\  .----)   |   |  |  |  |    |  |_)  | |  |\\  \\----.|  |____ /  _____  \\  |  .  \\  |  |____ |  |\\  \\----. #\n");
    printf("#     |__|  |__| /__/     \\__\\ |_______/    |__|  |__|    |______/  | _| `._____||_______/__/     \\__\\ |__|\\__\\ |_______|| _| `._____| #\n");
    printf("#                                                                                                                                      #\n");
    printf("#        _______. _______ .______     ____    ____  _______  __    __  .______                                                         #\n");
    printf("#       /       ||   ____||   _  \\    \\   \\  /   / |   ____||  |  |  | |   _  \\                                                        #\n");
    printf("#      |   (----`|  |__   |  |_)  |    \\   \\/   /  |  |__   |  |  |  | |  |_)  |                                                       #\n");
    printf("#       \\   \\    |   __|  |      /      \\      /   |   __|  |  |  |  | |      /                                                        #\n");
    printf("#   .----)   |   |  |____ |  |\\  \\----.  \\    /    |  |____ |  `--'  | |  |\\  \\----.                                                   #\n");
    printf("#   |_______/    |_______|| _| `._____|   \\__/     |_______| \\______/  | _| `._____|                                                   #\n");
    printf("#                                                                                                                                      #\n");
    printf("# by Manu Van Hoofstadt Chong Wen Wang                                                                                                 #\n");
    printf("########################################################################################################################################\n");
    printf("\n");
    if (argc != 4) {
        return printf("usage: %s [ip] [port] [hash file]\n", argv[0]);
    }

    int rc = 0;
    Stack hashes = load_from_file(argv[3]);
    if (hashes.length == 0)
        return fprintf(stderr, "couldnt load from file: %s\n", argv[3]);

    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (!serverfd) return fprintf(stderr, "socket(): %s\n", strerror(errno));
    struct sockaddr_in server_addr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = inet_addr(argv[1]),
        .sin_port        = htons(atoi(argv[2])),
    };
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    rc = bind(serverfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (rc < 0) return fprintf(stderr, "bind(): %s\n", strerror(errno));
    rc = listen(serverfd, 32);
    if (rc < 0) return fprintf(stderr, "listen(): %s\n", strerror(errno));
    printf("listening on %s:%d\n", argv[1], atoi(argv[2]));

    char *hash = 0;
    while ((hash = pop(&hashes))) {
        printf("loaded: %s\n", hash);
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int clientfd = accept(serverfd, (struct sockaddr*)&client_addr, &client_len);
        if (rc < 0) {
            fprintf(stderr, "accept(): %s\n", strerror(errno));
            continue;
        }
        printf("new client !\n");
        if (!handle(clientfd, hash)) {
            push(&hashes, hash);
        }
    }

    free_stack(&hashes);
}
