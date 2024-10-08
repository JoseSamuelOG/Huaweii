#include "stack.h"

stack_func_t stack_pop (my_stack_t *stk) {
    STK_ASSERT(stk);

    stack_elem_t val = stk->data[stk->size];

    if (stk->capacity == 0) {
        return 0;
    } else if ((stk->size - 1) * 4 <= stk->capacity && min_nonzero_stk_cap * 4 >= stk->capacity) {
        stk->capacity /= 2;
        stk->data = (stack_elem_t *)realloc(stk->data, (stk->capacity 
        #ifdef DEBUG
                                                                       + 2
        #endif
                                                                           ) * sizeof(stack_elem_t));
    }
    stk->data[stk->size--] = poizon_value;
    
    #ifdef DEBUG
        stk->data[stk->capacity + 1] = right_cannary;
    #endif

    HASH_COUNTER;
    STK_ASSERT(stk); 
    printf("Pop is succesful!\n");
    return val;
}