#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../onegin2/tokenize.h"

typedef int assemble_t;

enum proc_commands {
    CMD_HLT = 0,
    CMD_PUSH = 1,
    CMD_POP = 2,
    CMD_ADD = 11,
    CMD_SUB = 12,
    CMD_MUL = 13,
    CMD_DIV = 14,
    CMD_SQR = 21,
    CMD_SQRT = 22,
    CMD_SIN = 23,
    CMD_COS = 24,
    CMD_DUMP = 69,
    CMD_OUT = 100,
    CMD_IN = 101
};