#include "stack.h"

#ifdef DEBUG
stack_func_t stack_verify (my_stack_t *stk) {
    size_t errcode = 0;
    if (!stk) {
        errcode += STK_NOT_EXIST;
        return errcode;
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
    /*if (error_code == 0) { */
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
        for ( ; i != stk->size; ++i) {
            printf("|\t\t\t *[%d] = %d at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
        }
        for ( ; i != stk->capacity; ++i) {
            printf("|\t\t\t  [%d] = %d \033[36;42mPOIZON_VALUE!\033[0;0m at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
        }
        printf("|\t\t\t**[%d] = 0x%X - \033[30;43mright data cannary\033[0m at address: <0x%X>\n", i, stk->data[i], &(stk->data[i]));
        printf("|\t\t}\n");
        printf("|\t\tstk_right_cannary = 0x%X\n", stk->right_cannary_stk);
        printf("|\t}\n");
    //}
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

    /*    printf("stack_t[0x%X]:\n", stk);
        printf("|\tcalled from %s : %d from function: %s\n", file, line, func);
        printf("|\tname \"%s\" born at %s : %d in function %s\n", stk->name, stk->file, stk->line, stk->func);
        printf("|\t{\n");
        printf("|\t\tstk_left_cannary = %d\n", stk->left_cannary_stk);
        printf("|\t\tcapacity = %d\n", stk->capacity);
        printf("|\t\tsize = %d\n", stk->size);
        printf("|\t\tstack hash = %d\n", hash_str.stack_hash);
        printf("|\t\tdata hash = %d\n", hash_str.data_hash);
        printf("|\t\tstk_right_cannary = %d", stk->right_cannary_stk);
        printf("|\t}\n");  */
    }
}

stack_func_t stack_assert_func (my_stack_t *stk, const char *file, const size_t line, const char *func) {
    if(!stack_verify(stk)) {
        printf("||\t\t\033[5;31mERROR ASSERTION FAILED!!!\033[0m\n");
        printf("||\t\tIN FILE: %s\n", file);
        printf("||\t\tAT LINE: %d\n", line);
        printf("||\t\tFUNCTION CALLED: %s|\n", func);
        printf("||\t\tCHECK DUMP BELOW\n\n");
        printf("||\t\tERROR CODE = %d", stack_verify(stk));
        STK_DUMP(stk);
        free(stk->data);
        free(stk);
        abort();
    }
}

#endif