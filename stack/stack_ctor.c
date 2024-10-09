#include "stack.h"

stack_func_t stack_ctor (my_stack_t *stk, const size_t cap, const char *name, const char *file, const size_t line, const char *func) {
    assert(stk);
    
    #ifdef DEBUG
        stk->left_cannary_stk = left_cannary;
        stk->name = name;
        stk->file = file;
        stk->line = line;
        stk->func = func;
    #endif

    stk->capacity = cap;
    stk->size = 0;
    if (cap == 0) {
        stk->data = NULL;
    } else if (cap < min_nonzero_stk_cap) {
        stk->data = (stack_elem_t *)calloc(min_nonzero_stk_cap 
        #ifdef DEBUG
                                                                + 2
        #endif
                                                                    , sizeof(stack_elem_t));
    } else {
        stk->data = (stack_elem_t *)calloc(cap 
        #ifdef DEBUG
                                               + 2
        #endif
                                                   , sizeof(stack_elem_t));
    }

    #ifdef DEBUG
    *(stk->data) = left_cannary;
    #endif

    for(size_t i = 0; i != stk->capacity; ++i) {
        stk->data[i
    #ifdef DEBUG
                    + 1
    #endif
                       ] = poizon_value;
    }

    #ifdef DEBUG
    *(stk->data + stk->capacity) = right_cannary;
    #endif

    #ifdef DEBUG
        stk->right_cannary_stk = right_cannary;
    #endif

    HASH_COUNTER;

    STK_ASSERT(stk);

    printf("Stack \"%s\" is successfully constructed!\n", name);
    printf("At %s : %d in function %s\n", file, line, func);
}