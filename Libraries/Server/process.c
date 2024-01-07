#include "process.h"

int handle(int clientfd, char *hash) {
    char client_hash[32] = {0};
    char password[1024] = {0};
    
    // send hash to server using send
    if (send(clientfd, hash, strlen(hash), 0) < 0) {
        perror("send");
        close(clientfd);
        return 0;
    }

    // receive hash and password from server using recv
    int hash_size = recv(clientfd, client_hash, sizeof(client_hash), 0);
    int pass_size = recv(clientfd, password, sizeof(password), 0);
    
    close(clientfd);

    if (hash_size > 0 && strcmp("nope", password) != 0) {
        printf("found %.*s  %.*s\n", hash_size, client_hash, pass_size, password);

        FILE *outputFile = fopen("output.txt", "a");
        if (outputFile == NULL) {
            perror("Error opening output file");
            printf("Failed to open the output file. Results will not be saved.\n");
            return 1;
        }

        fprintf(outputFile, "%.*s %.*s\n", hash_size, client_hash, pass_size, password);
        fclose(outputFile);
        return 1;
    }

    return 0;
}
