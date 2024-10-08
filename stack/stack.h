#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STK_CTOR(stk, capacity) stack_ctor((stk), (capaciy), #stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define STK_ASSERT(stk) stack_assert_func (stk, __FILE__, __LINE__)

typedef double stack_elem_t;
const size_t min_nonzero_stk_cap = 16;

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
        const size_t line;
        const char *func;
    #endif
    stack_elem_t *data;
    size_t size;
    size_t capacity;
} my_stack_t;

int stack_ctor (my_stack_t *stk, const size_t cap, const char *name, const char *file, const size_t line, const char *func) {
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
    STK_ASSERT(&stk);
}

int stack_dtor (my_stack_t *stk) {
    STK_ASSERT(&stk);
    free(stk->data);
    stk->size = 0;
    stk->capacity = 0;
}

int stack_push (my_stack_t *stk, stack_elem_t token) {
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
}

int stack_pop (my_stack_t *stk) {
    STK_ASSERT(&stk);
    if (stk->capacity == 0) {
        return 0;
    } else if ((stk->size - 1) * 4 <= stk->capacity && min_nonzero_stk_cap * 4 >= stk->capacity) {
        stk->capacity /= 4;
        stk->data = (stack_elem_t *)realloc(stk->data, stk->capacity * sizeof(stack_elem_t));
    }
    STK_ASSERT(&stk); 
}

size_t stack_verify (my_stack_t *stk) {
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

int stack_dump (my_stack_t *stk) {

}

void stack_assert_func (my_stack_t *stk, const char *file, int line) {
    if(!stack_verify(stk)) {
        stack_dump(stk);
        printf("ERROR: In file %s at line %d\n", file, line);
        //abort();
    }
}

