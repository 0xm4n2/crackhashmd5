#ifndef CRACK_HASH_MD5_BRUTEFORCE_H
#define CRACK_HASH_MD5_BRUTEFORCE_H
#include <openssl/evp.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_PASS_LEN 5

int md5check(char *password, char md5hex[static 32]); 
char *
gen_pass(char *str, int str_pos, char *charset, int charset_len, char md5hex[static 32], int length);
int try_all(char md5hex[static 32], char *password);
char *crack(char md5hex[static 32], char password[MAX_PASS_LEN], char **passwords);
#endif //CRACK_HASH_MD5_BRUTEFORCE_H