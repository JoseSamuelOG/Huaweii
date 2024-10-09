#include "stack.h"

int main () {
    int cap = 0;
    my_stack_t stakkk;
    STK_CTOR(&stakkk, cap);
    stack_push(&stakkk, 52);
    STK_DUMP(&stakkk);
}