// do parsing_verify(fp)

#include "tokenize.h"

unsigned long int file_size(FILE *fp) {
    long int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    printf("%ld\n", size);
    return size;
}

char *write_file_to_buffer(char *filename, char *mode) {
    FILE *fp = fopen(filename, mode);
    char *buffer = NULL;
    parsing_verify(fp);
    unsigned long int filesz = file_size(fp);
    buffer = (char *)calloc(filesz + 1, sizeof(char));
    fread(buffer, sizeof(char), filesz, fp);
    return buffer;
}