#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "backstrcmp.h"

int ptrsorting (const void *a, const void *b) {
    return (const char *)a - (const char *)b;
}

int dir_comparator (const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void print_token(int num_of_tokens, const char** line, size_t line_num){
    printf("%d\t%d\t%p\t%.20s\n", num_of_tokens, line_num, line + line_num, line[line_num]);
}

long int file_size (FILE *fp) {
    long int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    printf("%ld\n", size);
    return size;
}

int main() {
    FILE *file = fopen("onegin.txt", "rb");
    char *buffer = NULL;

    if (!file) {
        printf("Error while opening file\n");
        return 1;
    } else {
        long int filesz = file_size(file);

        buffer = (char *)calloc(filesz + 1, sizeof(char));
        fread(buffer, sizeof(char), filesz, file);

        size_t token_num = 0;
        for (size_t i = 0; i != filesz; ++i) {
            if (buffer[i] == '\n') {
                ++token_num;
            }
        }
        char **lines = NULL;
        lines = (char **)calloc(token_num + 1, sizeof(char *));
        *lines = buffer;
        printf("%d\t%d\t%p\t%.20s\n", token_num, 0, lines, lines[0]);

        size_t i = 0;
        for (size_t j = 0; j != filesz; ++j) {
            if (buffer[j] == '\n') {
                lines[++i] = buffer + j + 1;
                print_token(token_num, lines, i);
            } 
            if (buffer[j] == '\n' || buffer[j] == '\r') {
                buffer[j] = '\0';
            }
        }
        printf("\n\n");
        qsort(lines, token_num + 1, sizeof(char *), dir_comparator);
        for (size_t i = 0; i != token_num + 1; ++i) {
            print_token(token_num, lines, i);
        }
        printf("\n\n");
        
        qsort(lines, token_num + 1, sizeof(char *), backstrcmp);
        for (size_t i = 0; i != token_num + 1; ++i) {
            print_token(token_num, lines, i);
        }
        printf("\n\n");
        
        qsort(lines, token_num + 1, sizeof(char *), ptrsorting);
        for (size_t i = 0; i != token_num + 1; ++i) {
            print_token(token_num, lines, i);
        }
        printf("\n\n");
        free(lines);
    }
    fclose(file);
    free(buffer);
}