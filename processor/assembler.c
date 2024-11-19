#include "assemble.h"

int assemble() {
    char *filein_name = NULL;
    char *fileout_name = NULL;
    char **commands = NULL;

    printf("enter the name of the input file\n");
    scanf("%s", filein_name);

    printf("enter the name of the output file\n");
    scanf("%s", fileout_name);

    char *instructions = write_file_to_buffer(filein_name, "rb");
    uint64_t token_number = parse_buffer(instructions, commands);
    assemble_t *commands_array = compile(commands, token_number, fileout_name);
}

uint64_t parse_buffer(char *buffer, char **lines) {
    uint64_t bufsz = strlen(buffer);
    uint64_t tokens = 0;

    for (uint64_t i = 0; i != bufsz; ++i) {
        if (buffer[i] == '\n' || buffer[i] == ' ')
            ++tokens;
    }
    lines = (char **)calloc(tokens + 1, sizeof(char *));

    size_t i = 0;
    for (size_t j = 0; j != bufsz; ++j) {
        if (buffer[j] == '\n' || buffer[j] == ' ') {
            lines[++i] = buffer + j + 1;
            } 
        if (buffer[j] == '\n' || buffer[j] == '\r' || buffer[j] == ' ') {
            buffer[j] = '\0';
        }
    }

    return tokens;
}

assemble_t *compile(char **lines, uint64_t tokens, char *filename) {
    
}