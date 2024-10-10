#include "stack.h"

int main () {
    my_stack_t stakkk;
    STK_CTOR(&stakkk, 1);
    STK_CTOR(&stakkk, 18);
    for(size_t i = 0; i != 33; ++i)
        stack_push(&stakkk, i);
    STK_DUMP(&stakkk);
    for(size_t i = 0; i != 25; ++i)
        printf("popped = %d\n", stack_pop(&stakkk));
    STK_DUMP(&stakkk);
    stack_dtor(&stakkk);
    STK_DUMP(&stakkk);
    stack_dtor(&stakkk);
    STK_DUMP(&stakkk);
}