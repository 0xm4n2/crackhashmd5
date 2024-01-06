#include "process.h"

int handle(int clientfd, char *hash) {
    char client_hash[32] = {0};
    char password[1024] = {0};
    write(clientfd, hash, strlen(hash));
    int hash_size = read(clientfd, client_hash, 32);
    int pass_size = read(clientfd, password, 1024);
    close(clientfd);

    if (hash_size != 0 && strcmp("nope", password) != 0) {
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