#include <stdio.h>
#include "stack.h"

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