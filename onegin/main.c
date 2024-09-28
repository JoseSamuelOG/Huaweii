#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

#include "file_size.h"
#include "tokenize.h"

long int file_size (FILE *fp);
Parts split_buffer_to_parts(size_t filesz, char *buffer);

int main() {

    FILE *file = fopen("filename", "rb");
    char *buffer = NULL;
    if(!file) {
        printf("Error while opening file\n");
        return 1;
    } else {
        long int filesz = file_size(file);
        Parts onegin = {0, NULL};

        buffer = (char *)calloc(filesz + 1, sizeof(char));
        fread(buffer, sizeof(char), filesz, file);

        onegin = split_buffer_to_parts(filesz, buffer);

        fclose(file);

        // Отсортировать его по qsort'у, своей сортировке и отсортировтаь указателеи как было

        // Записать и закрыть файл
    }
}
