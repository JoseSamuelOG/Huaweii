#include <stdio.h>

long int file_size (FILE *fp) {
    long int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    printf("%ld\n", size);
    return size;
}