#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "debug.h"

#define STK_CTOR(stk, capacity) stack_ctor((stk), (capaciy), #stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define STK_ASSERT(stk) stack_assert_func (stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define STK_DUMP(stk) stack_dump((stk), __FILE__, __LINE__, __PRETTY_FUNCTION__)

typedef double stack_elem_t;
typedef size_t stack_func_t;
typedef size_t cannary_t;  /*uint64_t*/

enum {
    STK_NOT_EXIST = 1,
    STK_DATA_NOT_EXIST = 2,
    STK_BAD_CAP = 4,
    STK_BAD_SZ = 8,
    STK_CANNARY_DEAD = 16,
    STK_DATA_CANNARY_DEAD = 32
};
typedef struct my_stack_t {
    #ifdef DEBUG
        cannary_t left_cannary_stk;
        const char *name;
        const char *file;
        size_t line;
        const char *func;
    #endif
    stack_elem_t *data;
    size_t size;
    size_t capacity;
    #ifdef DEBUG
        cannary_t right_cannary_stk;
    #endif
} my_stack_t;

const size_t min_nonzero_stk_cap = 16;
const stack_elem_t poizon_value = -1488;
// const size_t cannary_len = sizeof(cannary_t)/sizeof(stack_elem_t);
const cannary_t left_cannary = 0xCAFEBABE;
const cannary_t right_cannary = 0xFEE1DEAD;

stack_func_t stack_assert_func (my_stack_t *stk, const char *file, const size_t line, const char *func) {
    if(!stack_verify(stk)) {
        printf("||\t\t\033[5;31mERROR ASSERTION FAILED!!!\033[0m\t\n");
        printf("||\t\tIN FILE: %s\n", file);
        printf("||\t\tAT LINE: %d\n", line);
        printf("||\t\tFUNCTION CALLED: %s|\n", func);
        printf("||\t\tCHECK DUMP BELOW\n\n");
        STK_DUMP(&stk);
        free(stk->data);
        free(stk);
        abort();
    }
}