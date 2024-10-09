#include "stack.h"

size_t min_nonzero_stk_cap = 16;
stack_elem_t poizon_value = -1488;
// size_t cannary_len = sizeof(cannary_t)/sizeof(stack_elem_t);
cannary_t left_cannary = 0xCAFEBABE;
cannary_t right_cannary = 0xFEE1DEAD;

my_stack_hash_t hash_str = {0, 0};