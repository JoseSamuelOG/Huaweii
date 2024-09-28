#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
    size_t N;
    char **lines;
} Parts;

Parts split_buffer_to_parts(size_t filesz, char *buffer) {
    Parts onegin = {0, NULL};
    onegin.N = 0;
        for (size_t i = 0; i != filesz; ++i) {
            if (buffer[i] == '\n') {
                ++(onegin.N);
            }
        }
        char **lines = NULL;
        onegin.lines = (char **)calloc(onegin.N + 1, sizeof(char *));
        *(onegin.lines) = buffer;
        printf("%d\t%d\t%.20s\n", onegin.N, 0, lines[0]);

        size_t i = 0;
        for (size_t j = 0; j != filesz; ++j) {
            if (buffer[j] == '\n') {
                lines[++i] = buffer + j + 1;
                printf("%d\t%d\t%.20s\n", onegin.N, i, lines[i]);
            } 
            if (buffer[j] == '\n' || buffer[j] == '\r') {
                buffer[j] = '\0';
            }
        }
    return onegin;
}