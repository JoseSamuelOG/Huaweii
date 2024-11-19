#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    size_t tokens;
    char **lines;
} Parts;

long int file_size (FILE *fp);
char *write_file_to_buffer(char *filename, char *mode);
Parts split_buffer_to_parts(char *buffer);
