#include "tokenize.h"

long int file_size (FILE *fp);
Parts split_buffer_to_parts(size_t filesz, char *buffer);

int main() {
    char *filename = "onegin.txt";

    char *buffer = write_file_to_buffer(filename, "rb");
    Parts onegin = split_buffer_to_parts(buffer, file_size(fopen("onegin.txt", "rb")));
}
