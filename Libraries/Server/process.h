#ifndef CRACK_HASH_MD5_PROCESS_H
#define CRACK_HASH_MD5_PROCESS_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int handle(int clientfd, char *hash);
#endif //CRACK_HASH_MD5_PROCESS_H