#ifndef CRACK_HASH_MD5_PROCESS_H
#define CRACK_HASH_MD5_PROCESS_H
#include "bruteforce.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle(int clientfd, char **passwords);

#endif //CRACK_HASH_MD5_PROCESS_H