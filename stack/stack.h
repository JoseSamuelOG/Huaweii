#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG

#define STK_CTOR(stk, capacity) stack_ctor((stk), (capaciy), #stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define STK_ASSERT(stk) stack_assert_func (stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define STK_DUMP(stk) stack_dump((stk), __FILE__, __LINE__, __PRETTY_FUNCTION__)

typedef double stack_elem_t;
typedef size_t stack_func_t;

enum {
    STK_NOT_EXIST = 1,
    STK_DATA_NOT_EXIST = 2,
    STK_BAD_CAP = 4,
    STK_BAD_SZ = 8,
};
typedef struct my_stack_t {
    #ifdef DEBUG
        const char *name;
        const char *file;
        size_t line;
        const char *func;
    #endif
    stack_elem_t *data;
    size_t size;
    size_t capacity;
} my_stack_t;

const size_t min_nonzero_stk_cap = 16;
const stack_elem_t poizon_value = -1488;

stack_func_t stack_ctor (my_stack_t *stk, const size_t cap, const char *name, const char *file, const size_t line, const char *func) {
    assert(stk);
    
    #ifdef DEBUG
        stk->name = name;
        stk->file = file;
        stk->line = line;
        stk->func = func;
    #endif

    stk->capacity = cap;
    stk->size = 0;
    if (cap == 0)
        stk->data = NULL;
    else if (cap < min_nonzero_stk_cap)
        stk->data = (stack_elem_t *)calloc(min_nonzero_stk_cap, sizeof(stack_elem_t));
    else
        stk->data = (stack_elem_t *)calloc(cap, sizeof(stack_elem_t));

    for(size_t i = 0; i != stk->capacity; ++i) {
        stk->data[i] = poizon_value;
    }
    STK_ASSERT(&stk);
}

stack_func_t stack_dtor (my_stack_t *stk) {
    STK_ASSERT(&stk);
    free(stk->data);
    stk->size = 0;
    stk->capacity = 0;
}

stack_func_t stack_push (my_stack_t *stk, stack_elem_t token) {
    STK_ASSERT(&stk);
    if (stk->capacity == 0) {
        stk->capacity = min_nonzero_stk_cap;
        stk->data = (stack_elem_t *)realloc(stk->data, stk->capacity * sizeof(stack_elem_t));
    } else if (stk->size == stk->capacity) {
        stk->capacity *= 2;
        stk->data = (stack_elem_t *)realloc(stk->data, stk->capacity * sizeof(stack_elem_t));
    } 
    stk->data[stk->size++] = token;
    STK_ASSERT(&stk);
    return stk->data[stk->size];
}

stack_func_t stack_pop (my_stack_t *stk) {
    STK_ASSERT(&stk);
    if (stk->capacity == 0) {
        return 0;
    } else if ((stk->size - 1) * 4 <= stk->capacity && min_nonzero_stk_cap * 4 >= stk->capacity) {
        stk->capacity /= 4;
        stk->data = (stack_elem_t *)realloc(stk->data, stk->capacity * sizeof(stack_elem_t));
    }
    STK_ASSERT(&stk); 
    return stk->data[--stk->size];
}

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
    return errcode;
}

stack_func_t stack_dump (my_stack_t *stk, const char *file, const size_t line, const char *func) {
    printf("stack_t[0x%X]:\n", stk);
    printf("|\tcalled from %s : %d from function: %s\n", file, line, func);
    printf("|\tname \"%s\" born at %s : %d in function %s\n", stk->name, stk->file, stk->line, stk->func);
    printf("|\t{\n");
    //printf("|\t\tstk_left_cannary = %d\n");
    printf("|\t\tcapacity = %d\n", stk->capacity);
    printf("|\t\tsize = %d\n", stk->size);
    printf("|\t\tpoizon_value = %d\n", poizon_value);
    printf("|\t\tdata[0x%X]:\n", stk->data);
    printf("|\t\t{\n");
    size_t i = 0;
    for ( ; i != stk->size; ++i) {
        printf("|\t\t\t*[%d] = %d at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
    }
    for ( ; i != stk->capacity; ++i) {
        printf("|\t\t\t [%d] = %d \033[36;42mPOIZON_VALUE!\033[0 at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
    }
    printf("|\t\t}\n");
    //printf("|\t\tstk_right_cannary = %d");
    printf("|\t}\n");

}

stack_func_t stack_assert_func (my_stack_t *stk, const char *file, const size_t line, const char *func) {
    if(!stack_verify(stk)) {
        printf("||\t\t\033[5;31mERROR ASSERTION FAILED!!!\033[0m\t\n");
        printf("||\t\tIN FILE: %s\n", file);
        printf("||\t\tAT LINE: %d\n", line);
        printf("||\t\tFUNCTION CALLED: %s|\n", func);
        printf("||\t\tCHECK DUMP BELOW\n\n");
        STK_DUMP(stk);
        free(stk->data);
        free(stk);
        abort();
    }
}

