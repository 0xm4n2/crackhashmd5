#ifndef CRACK_HASH_MD5_STACK_H
#define CRACK_HASH_MD5_STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int length;
    int current;
    char **data;
} Stack;
int push(Stack *s, char *data);
char *pop(Stack *s);
void free_stack(Stack *s);
Stack load_from_file(char *filename);

#endif //CRACK_HASH_MD5_STACK_H