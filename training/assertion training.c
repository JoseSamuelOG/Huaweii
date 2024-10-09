#include <stdio.h>
#include <stdlib.h>

#define ASSERTION() stack_assert_func(__FILE__, __LINE__, __PRETTY_FUNCTION__)

int stack_assert_func (const char *file, const size_t line, const char *func) {
    if(1) {
        printf("||\t\t\033[5;31mERROR ASSERTION FAILED!!!\033[0m\t\n");
        printf("||\t\tIN FILE: %s\n", file);
        printf("||\t\tAT LINE: %d\n", line);
        printf("||\t\tFUNCTION CALLED: %s|\n", func);
        printf("||\t\tCHECK DUMP BELOW\n\n");
    }
}

void sex_sex() {
    ASSERTION();
    abort();
}

int main () {
    ASSERTION();
    sex_sex();
}

