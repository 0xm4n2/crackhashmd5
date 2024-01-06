#include "process.h" 
// receive hash from server
// try to crack the password
// then send the right password (hopefully)
void handle(int clientfd, char **passwords) {
    char md5hex[32] = {0};
    char password[MAX_PASS_LEN+1] = {0};

    // get hash from server
    read(clientfd, md5hex, sizeof(md5hex));
    printf("gonna crack: %.*s\n", 32, md5hex);
    // crack the hash
    // found is ok because its either a pointer to password 
    // which is on the stack here or to "nope" which is a static string
    char *found = crack(md5hex, password, passwords);
    // reply to server
    write(clientfd, md5hex, 32);
    write(clientfd, found, strlen(found));
    close(clientfd);
}
