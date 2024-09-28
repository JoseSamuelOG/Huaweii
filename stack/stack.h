#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef DEBUG
    #define ON_DEBUG(code) code
#else
    #define ON_DEBUG(code)
#endif

typedef double stack_elem_t;

enum {
    STK_BAD_CAP = -5,
    STK_DATA_NOT_EXIST = -4,
    STK_SIZE_GREATER_CAP = -3,
    STK_SIZE_LESS_ZERO = -2,
    STK_NOT_EXIST = -1
};

struct my_stack_t {
    stack_elem_t *data;
    size_t size;
    size_t capacity;
};

int stack_ctor (my_stack_t *stk, const size_t cap) {

    stk->capacity = cap;
    stk->size = 0;
    if (cap == 0)
        stk->data = NULL;
    else
        stk->data = (stack_elem_t *)calloc(cap, sizeof(stack_elem_t));

}

int stack_dtor (my_stack_t *stk) {
    free(stk->data);
    stk->size = 0;
    stk->capacity = 0;
}

void stack_assert_func (my_stack_t *stk, const char *file, int line) {
    if(!stack_verify(stk)) {
        stack_dump(stk);
        printf("ERROR: In file %s at line %d\n", file, line);
    }
}

int stack_verify (my_stack_t *stk) {
    if (!stk) {
        printf("ERROR: stack do not exist: stack addr = NULL\n");
        return STK_NOT_EXIST;
    }
    if (!stk->data && stk->capacity != 0) {
        printf("ERROR: data do not exist && capacity != 0\n");
        return STK_DATA_NOT_EXIST;
    }
    if (stk->size < 0) {
        printf("ERROR: stack size < 0>\n");
        return STK_SIZE_LESS_ZERO;
    }
    if (stk->size > stk->capacity) {
        printf("ERROR: stack size > capacity\n");
        return STK_SIZE_GREATER_CAP;
    }
    if (stk->capacity < 0) {
        printf("ERROR: stack capacity is < 0\n");
        return STK_BAD_CAP;
    }
}

int stack_dump (my_stack_t *stk) {

}