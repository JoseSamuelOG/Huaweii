#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "debug.h"

#define STK_CTOR(stk, capacity) stack_ctor((stk), capacity, #stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define STK_ASSERT(stk) stack_assert_func ((stk), __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define STK_DUMP(stk) stack_dump((stk), __FILE__, __LINE__, __PRETTY_FUNCTION__, (hash_str))
#define HASH_COUNTER hash_counter(&hash_str, stk);

typedef size_t stack_elem_t;
typedef size_t stack_func_t;
typedef size_t cannary_t;  /*uint64_t*/
typedef uint64_t hash_t;

enum {
    STK_NOT_EXIST = 1,
    STK_DATA_NOT_EXIST = 2,
    STK_BAD_CAP = 4,
    STK_BAD_SZ = 8,
    STK_CANNARY_DEAD = 16,
    STK_DATA_CANNARY_DEAD = 32,
    STK_BAD_HASH = 64,
    STK_DATA_BAD_HASH = 128
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

typedef struct my_stack_hash_t {
    hash_t stack_hash;
    hash_t data_hash;
} my_stack_hash_t;

extern size_t min_nonzero_stk_cap;
extern stack_elem_t poizon_value;
// extern size_t cannary_len;
extern cannary_t left_cannary;
extern cannary_t right_cannary;

extern my_stack_hash_t hash_str;

stack_func_t stack_ctor (my_stack_t *stk, const size_t cap, const char *name, const char *file, const size_t line, const char *func);
stack_func_t stack_dtor (my_stack_t *stk);
stack_func_t stack_push (my_stack_t *stk, stack_elem_t token);
stack_func_t stack_pop (my_stack_t *stk);
#ifdef DEBUG
stack_func_t stack_verify (my_stack_t *stk);
stack_func_t stack_dump (my_stack_t *stk, const char *file, const size_t line, const char *func, my_stack_hash_t hash_struct);
stack_func_t stack_assert_func (my_stack_t *stk, const char *file, const size_t line, const char *func);
hash_t hash_func(const void *data, size_t size);
void hash_counter(my_stack_hash_t *hash_struct, my_stack_t *stk);
#endif