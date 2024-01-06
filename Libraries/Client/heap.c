#include "heap.h"
// load file into an array of line
char **load_from_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    // count the number of line to allocate
    int nline = 0, c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') nline++;
    }
    rewind(file);

    // allocate array of string
    // +1 to have a 0 terminated array
    char **lines = malloc((nline+1) * sizeof(char*));
    if (!lines) {
        fclose(file);
        return 0;
    }
    lines[nline] = 0; //fin du tableau 

    // load each line into the array
    char line[1024] = {0};
    nline = 0;
    while(fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = 0;
        lines[nline] = strdup(line); // error handling
        if (!lines[nline]) {
            lines[nline] = 0;
            continue;
        }
        nline++;
    }

    fclose(file);
    return lines;
}

