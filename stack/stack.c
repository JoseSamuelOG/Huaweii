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
    stk->data[0] = left_cannary;
    #endif

    for(size_t i = 0; i != stk->capacity; ++i) {
        stk->data[i
    #ifdef DEBUG
                    + 1
    #endif
                       ] = poizon_value;
    }

    #ifdef DEBUG
    stk->data[stk->capacity + 1] = right_cannary;
    #endif

    #ifdef DEBUG
        stk->right_cannary_stk = right_cannary;
    #endif

    STK_ASSERT(&stk);

    printf("Stack \"%s\" is successfully constructed!\n", name);
    printf("At %s : %d in function %s\n", file, line, func);
}

stack_func_t stack_dtor (my_stack_t *stk) {
    STK_ASSERT(&stk);
    STK_DUMP(&stk);

    free(stk->data);
    stk->size = -1;
    stk->capacity = -1;

    #ifdef DEBUG
        stk->name = 0;
        stk->file = 0;
        stk->line = -1;
    #endif

    stk = -1;

    printf("Stack is successfully destructed!");
}

stack_func_t stack_push (my_stack_t *stk, stack_elem_t token) {
    STK_ASSERT(&stk);

    if (stk->capacity == 0)
        stk->capacity = min_nonzero_stk_cap;
    else if (stk->size == stk->capacity)
        stk->capacity *= 2;

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
        stk->data[stk->capacity + 1] = right_cannary;
    #endif

    stk->data[stk->size++
    #ifdef DEBUG
                           + 1
    #endif
                              ] = token;
    STK_ASSERT(&stk);
    return stk->data[stk->size];
}

stack_func_t stack_pop (my_stack_t *stk) {
    STK_ASSERT(&stk);

    if (stk->capacity == 0) {
        return 0;
    } else if ((stk->size - 1) * 4 <= stk->capacity && min_nonzero_stk_cap * 2 >= stk->capacity) {
        stk->capacity /= 2;
        stk->data = (stack_elem_t *)realloc(stk->data, (stk->capacity 
        #ifdef DEBUG
                                                                       + 2
        #endif
                                                                           ) * sizeof(stack_elem_t));
    }
    
    #ifdef DEBUG
        stk->data[stk->capacity + 1] = right_cannary;
    #endif

    STK_ASSERT(&stk); 

    return stk->data[--stk->size];
}

#ifdef DEBUG
stack_func_t stack_verify (my_stack_t *stk) {
    size_t errcode = 0;
    if (!stk) {
        errcode += STK_NOT_EXIST;
    }
    if (!stk->data && stk->capacity != 0) {
        errcode += STK_DATA_NOT_EXIST;
    }
    if (stk->capacity < min_nonzero_stk_cap) {
        errcode += STK_BAD_CAP;
    }
    if (stk->size < 0) {
        errcode += STK_BAD_SZ;
    }
    if (stk->left_cannary_stk != left_cannary || stk->right_cannary_stk != right_cannary) {
        errcode += STK_CANNARY_DEAD;
    }
    if (stk->data[0] != left_cannary || stk->data[stk->capacity + 1] != right_cannary) {
        errcode += STK_DATA_CANNARY_DEAD;
    }
    return errcode;
}
#endif

#ifdef DEBUG
stack_func_t stack_dump (my_stack_t *stk, const char *file, const size_t line, const char *func) {
    printf("stack_t[0x%X]:\n", stk);
    printf("|\tcalled from %s : %d from function: %s\n", file, line, func);
    printf("|\tname \"%s\" born at %s : %d in function %s\n", stk->name, stk->file, stk->line, stk->func);
    printf("|\t{\n");
    printf("|\t\tstk_left_cannary = %d\n", stk->left_cannary_stk);
    printf("|\t\tcapacity = %d\n", stk->capacity);
    printf("|\t\tsize = %d\n", stk->size);
    printf("|\t\tpoizon_value = %d\n", poizon_value);
    printf("|\t\tdata[0x%X]:\n", stk->data);
    printf("|\t\t{\n");
    size_t i = 0;
    printf("|\t\t\t**[%d] = 0x%X - \033[30;43mleft data cannary\033[0 at address: <0x%X>\n", ++i, stk->data[i], &(stk->data[i]));
    for ( ; i != stk->size; ++i) {
        printf("|\t\t\t *[%d] = %d at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
    }
    for ( ; i != stk->capacity; ++i) {
        printf("|\t\t\t  [%d] = %d \033[36;42mPOIZON_VALUE!\033[0 at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
    }
    printf("|\t\t\t**[%d] = 0x%X - \033[30;43mright data cannary\033[0 at address: <0x%X>\n", ++i, stk->data[i], &(stk->data[i]));
    printf("|\t\t}\n");
    printf("|\t\tstk_right_cannary = %d", stk->right_cannary_stk);
    printf("|\t}\n");
}
#endif
