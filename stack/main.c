#include "stack.h"

int main () {
    int cap = 16;
    my_stack_t stakkk;
    STK_CTOR(&stakkk, 16);
    stack_push(&stakkk, 52);
    STK_DUMP(&stakkk);
}