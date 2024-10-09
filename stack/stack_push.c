#include "stack.h"

stack_func_t stack_push (my_stack_t *stk, stack_elem_t token) {
    STK_ASSERT(stk);

    if (stk->capacity == 0)
        stk->capacity = min_nonzero_stk_cap;
    else if (stk->size == stk->capacity) {
        stk->capacity *= 2;
    }
    stk->data = (stack_elem_t *)realloc(stk->data, (stk->capacity 
    #ifdef DEBUG
                                                                  + 2
    #endif
                                                                     ) * sizeof(stack_elem_t));
    
    for (size_t i = stk->size; i != stk->capacity; ++i) {
        stk->data[i 
    #ifdef DEBUG    
                    + 1
    #endif    
                        ] = poizon_value;
    }

    #ifdef DEBUG
        stk->data[stk->capacity] = right_cannary;
    #endif

    stk->data[stk->size++
    #ifdef DEBUG
                           + 1
    #endif
                              ] = token;

    HASH_COUNTER;
    STK_ASSERT(stk);
    printf("Push of %d is succesful!\n", stk->data[stk->size]);
    return stk->data[stk->size];
}