#include "stack.h"
int push(Stack *s, char *data) {
    if (s->current == s->length) return 0;
    s->data[s->current++] = data;
    return 1;
}

char *pop(Stack *s) {
    if (s->current == 0) return 0;
    return s->data[--s->current];
}

void free_stack(Stack *s) {
    for (int i = 0; i < s->length; i++) {
        printf("%d. %s\n", i, s->data[i]);
        free(s->data[i]);
    }
    free(s->data);
}

Stack load_from_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return (Stack){0};

    // count the number of line to allocate
    int nline = 0;
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') nline++;
    }
    rewind(f);

    // allocate array of string
    char **lines = malloc(nline * sizeof(char*));
    if (!lines) {
        fclose(f);
        return (Stack){0};
    }

    // load each line into the array
    char line[1024] = {0};
    nline = 0;
    while(fgets(line, sizeof(line), f)) {
        line[strlen(line)-1] = 0;
        if (strlen(line) == 32) {// only add the lines which are the correct length
            lines[nline++] = strdup(line); // error handling
        }
    }

    fclose(f);

    return (Stack){ .length = nline, .data = lines, .current = nline };
}