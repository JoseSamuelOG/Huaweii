#include "tokenize.h"

Parts split_buffer_to_parts(char *buffer, unsigned long int filesz) {
    Parts temp = {0, NULL};
    temp.tokens = 0;
        for (size_t i = 0; i != filesz; ++i) {
            if (buffer[i] == '\n') {
                ++(temp.tokens);
            }
        }
        char **lines = NULL;
        temp.lines = (char **)calloc(temp.tokens + 1, sizeof(char *));
        *(temp.lines) = buffer;
        #ifdef DEBUG
        printf("%d\t%d\t%.20s\n", temp.tokens, 0, lines[0]);
        #endif

        size_t i = 0;
        for (size_t j = 0; j != filesz; ++j) {
            if (buffer[j] == '\n') {
                lines[++i] = buffer + j + 1;
                #ifdef DEBUG
                printf("%d\t%d\t%.20s\n", temp.tokens, i, lines[i]);
                #endif
            } 
            if (buffer[j] == '\n' || buffer[j] == '\r') {
                buffer[j] = '\0';
            }
        }
    return temp;
}