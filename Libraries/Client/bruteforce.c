#include "bruteforce.h"

// convert password to md5digest then to hex
// compare md5hex with password hex digest
int md5check(char *password, char md5hex[static 32]) {
    unsigned char password_digest[16] = {0};
    char password_digest_hex[32] = {0};

    // password to md5 digest
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (EVP_DigestInit_ex(ctx, EVP_md5(), NULL) == 0)
        return fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL)), 0;
    if (EVP_DigestUpdate(ctx, password, strlen(password)) == 0)
        return fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL)), 0;
    if (EVP_DigestFinal_ex(ctx, password_digest, NULL) == 0)
        return fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL)), 0;
    EVP_MD_CTX_free(ctx);

    // password digest to hex
    char *pass_hex = password_digest_hex;
    for (int i = 0; i < 16; i++)
        pass_hex += sprintf((char *)pass_hex, "%02x", password_digest[i]);

    // check if it is the hashes match
    printf("pass(%s): %.*s\n", password, 32, password_digest_hex);
    printf("md5h: %.*s\n", 32, md5hex);
    if (!strncmp(password_digest_hex, md5hex, 32)) { //si différent de 0
        printf("FOUND !\n");
        return 1;
    }
    return 0;
}

// gen password recursively using charset
// if md5check(str, md5hex) then stop and return the current
// generated password
char *
gen_pass(char *str, int str_pos, char *charset, int charset_len, char md5hex[static 32], int length)
{
    // if current string as the right length
    // check if is the right password
    if (str_pos == length)
        return md5check(str, md5hex) ? str : 0;

    for (int i = 0; i < charset_len-1; i++) {
        str[str_pos] = charset[i];
        if (gen_pass(str, str_pos+1, charset, charset_len, md5hex, length))
            return str;
    }

    return 0;
}
// start the recursive function that generate
// password using charset
int try_all(char md5hex[static 32], char *password) {
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    if (gen_pass(password, 0, charset, sizeof(charset), md5hex, MAX_PASS_LEN))
        return 1;

    return 0;
}

// try to crack the hash using all the password in `passwords`
// if didnt work then try to generate password recursively
char *crack(char md5hex[static 32], char password[MAX_PASS_LEN], char **passwords) {
    for (int i = 0; passwords[i]; i++) {
        printf("trying '%s' against %.*s\n", passwords[i], 32, md5hex);
        if (md5check(passwords[i], md5hex)) {
            return passwords[i];
        }
    }
    return  try_all(md5hex, password) ? password : (printf("didnt find...\n"), "nope");
}