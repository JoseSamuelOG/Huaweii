#include "stack.h"

stack_func_t stack_dtor (my_stack_t *stk) {
    STK_ASSERT(stk);

    free(stk->data);
    stk->data = NULL;
    stk->size = -1;
    stk->capacity = -1;

    #ifdef DEBUG
        stk->name = 0;
        stk->file = 0;
        stk->line = -1;
    #endif

    stk = NULL;

    printf("Stack is successfully destructed!\n");
}