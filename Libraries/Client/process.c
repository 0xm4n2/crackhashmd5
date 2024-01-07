#include "process.h" 
// receive hash from server
// try to crack the password
// then send the right password (hopefully)
void handle(int clientfd, char **passwords) {
    char md5hex[32] = {0};
    char password[MAX_PASS_LEN + 1] = {0};

    // get hash from server using recv
    if (recv(clientfd, md5hex, sizeof(md5hex), 0) < 0) {
        perror("recv");
        close(clientfd);
        return;
    }

    printf("gonna crack: %.*s\n", 32, md5hex);

    // crack the hash
    char *found = crack(md5hex, password, passwords);

    // reply to server using send
    if (send(clientfd, md5hex, sizeof(md5hex), 0) < 0) {
        perror("send");
        close(clientfd);
        return;
    }
    
    if (send(clientfd, found, strlen(found), 0) < 0) {
        perror("send");
    }

    close(clientfd);
}
