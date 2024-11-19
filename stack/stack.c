#include "stack.h"

size_t min_nonzero_stk_cap = 16;
stack_elem_t poizon_value = -1488;
// size_t cannary_len = sizeof(cannary_t)/sizeof(stack_elem_t);
cannary_t left_cannary = 0xCAFEBABE;
cannary_t right_cannary = 0xFEE1DEAD;

my_stack_hash_t hash_str = {0, 0};

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
        #ifdef DEBUG
            stk->data = (stack_elem_t *)calloc(2, sizeof(stack_elem_t));
        #else
            stk->data = NULL; // Тут пизда у нас две канарейки вообще-то
        #endif
    } else if (cap < min_nonzero_stk_cap) {
        stk->data = (stack_elem_t *)calloc(min_nonzero_stk_cap 
        #ifdef DEBUG
                                                                + 2
        #endif
                                                                    , sizeof(stack_elem_t)); // Cука должно быть 11 а не 10, надо в других ифдефах хуярить!
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
        if (stk->capacity == 0) 
            stk->data[stk->capacity + 1] = right_cannary;
        else
            stk->data[stk->capacity + 1] = right_cannary;
    #endif

    #ifdef DEBUG
        stk->right_cannary_stk = right_cannary;
    #endif

    HASH_COUNTER;

    STK_ASSERT(stk);

    printf("Stack \"%s\" is successfully constructed!\n", name);
    printf("At %s : %d in function %s\n", file, line, func);
}

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

stack_func_t stack_push (my_stack_t *stk, stack_elem_t token) {
    STK_ASSERT(stk);

    if (stk->capacity == 0)
        stk->capacity = min_nonzero_stk_cap;
    else if (stk->size == stk->capacity) {
        stk->capacity *= 2;
        printf("capaciry increased = %d\n", stk->capacity);
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
        stk->data[stk->capacity + 1] = right_cannary;
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

#ifdef DEBUG
hash_t hash_func(const void *data, size_t size) {
    hash_t hash = 5381;
    for (size_t i = 0; i != size; ++i) {
        hash = ((hash << 5) + hash) ^ *((char *)data + i);
    }
    return hash;
}

void hash_counter(my_stack_hash_t *hash_struct, my_stack_t *stk) {
    hash_struct->stack_hash = hash_func((const void *)&stk, sizeof(stk));
    printf("stk hash = <%d>\n", hash_struct->stack_hash);
    hash_struct->data_hash = hash_func((const void *)&stk->data, sizeof(stk->data));
    printf("data hash = <%d>\n", hash_struct->data_hash);
    printf("\n");
}
#endif

#ifdef DEBUG
stack_func_t stack_verify (my_stack_t *stk) {
    size_t errcode = 0;
    if (!stk) {
        errcode += STK_NOT_EXIST;
        return errcode;
    }
    if (!stk->data && (stk->capacity != 0)) {
        errcode += STK_DATA_NOT_EXIST;
    }
    if (stk->capacity < min_nonzero_stk_cap && (errcode & STK_DATA_NOT_EXIST == STK_DATA_NOT_EXIST)) {
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
    if (hash_str.stack_hash != hash_func((const void *)&stk, sizeof(stk))) {
        errcode += STK_BAD_HASH;
    }
    if (hash_str.data_hash != hash_func((const void *)&stk->data, sizeof(stk->data))) {
        errcode += STK_DATA_BAD_HASH;
    }
    return errcode;
}

stack_func_t stack_dump (my_stack_t *stk, const char *file, const size_t line, const char *func, my_stack_hash_t hash_struct) {
    stack_func_t error_code = stack_verify(stk);
    if (error_code & STK_NOT_EXIST == STK_NOT_EXIST) {
        printf("|\n|\t\t\033[5;31mERROR: STACK DOES NOT EXIST!!!\033[0m\t\n|\n");
    } else {
        if (error_code & STK_DATA_NOT_EXIST == STK_DATA_NOT_EXIST) {
            printf("|\n|\t\t\033[5;31mERROR: DATA DOES NOT EXIST!!!\033[0m\t\n|\n");
        }
        if (error_code & STK_BAD_CAP == STK_BAD_CAP) {
            printf("|\n|\t\t\033[5;31mERROR: BAD CAPACITY!!!\033[0m\t\n|\n");
        }
        if (error_code & STK_BAD_SZ == STK_BAD_SZ) {
            printf("|\n|\t\t\033[5;31mERROR: BAD SIZE!!!\033[0m\t\n|\n");
        }
        if (error_code & STK_CANNARY_DEAD == STK_CANNARY_DEAD) {
            printf("|\n|\t\t\033[5;31mERROR: STACK CANNARY IS CORRUPTED!!!\033[0m\t\n|\n");
        }
        if (error_code & STK_DATA_CANNARY_DEAD == STK_DATA_CANNARY_DEAD) {
            printf("|\n|\t\t\033[5;31mERROR: DATA CANNARY IS CORRUPTED!!!\033[0m\t\n|\n");
        }
        if (error_code & STK_BAD_HASH == STK_BAD_HASH) {
            printf("|\n|\t\t\033[5;31mERROR: STACK HASH IS CORRUPTED!!!\033[0m\t\n|\n");
        }
        if (error_code & STK_DATA_BAD_HASH == STK_DATA_BAD_HASH) {
            printf("|\n|\t\t\033[5;31mERROR: DATA HASH IS CORRUPTED!!!\033[0m\t\n|\n");
        }

                printf("\nstack_t[0x%X]:\n", stk);
        printf("|\tcalled from %s : %d from function: %s\n", file, line, func);
        printf("|\tname \"%s\" born at %s : %d in function %s\n", stk->name, stk->file, stk->line, stk->func);
        printf("|\t{\n");
        printf("|\t\tstk_left_cannary = 0x%X\n", stk->left_cannary_stk);
        printf("|\t\tcapacity = %d\n", stk->capacity);
        printf("|\t\tsize = %d\n", stk->size);
        printf("|\t\tstack hash = %d\n", hash_str.stack_hash);
        printf("|\t\tdata hash = %d\n", hash_str.data_hash);
        printf("|\t\tdata[0x%X]:\n", stk->data);
        printf("|\t\t{\n");
        size_t i = 0;
        printf("|\t\t\t**[%d] = 0x%X - \033[30;43mleft data cannary\033[0;0m at address: <0x%X>\n", i++, stk->data[i], &(stk->data[i]));
        for ( ; i < stk->size + 1; ++i) {
            printf("|\t\t\t *[%d] = %d at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
        }
        for ( ; i < stk->capacity + 1; ++i) {
            printf("|\t\t\t  [%d] = %d \033[36;42mPOIZON_VALUE!\033[0;0m at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
        }
        printf("|\t\t\t**[%d] = 0x%X - \033[30;43mright data cannary\033[0m at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
        printf("|\t\t}\n");
        printf("|\t\tstk_right_cannary = 0x%X\n", stk->right_cannary_stk);
        printf("|\t}\n");
    }
}

stack_func_t stack_assert_func (my_stack_t *stk, const char *file, const size_t line, const char *func) {
    if(stack_verify(stk)) {
        printf("||\t\t\033[5;31mERROR ASSERTION FAILED!!!\033[0m\n");
        printf("||\t\tIN FILE: %s\n", file);
        printf("||\t\tAT LINE: %d\n", line);
        printf("||\t\tFUNCTION CALLED: %s\n", func);
        printf("||\t\tCHECK DUMP BELOW\n");
        printf("||\t\tERROR CODE = %d\n\n", stack_verify(stk));
        STK_DUMP(stk);
        free(stk->data);
        free(stk);
        abort();
    }
}

#endif