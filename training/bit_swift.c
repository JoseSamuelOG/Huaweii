#include <stdio.h>

int main () {
    for (size_t i = 0; i < 30; ++i) {
        printf("#%d)\t\t0x%lX\t\t0x%lX\n", i, 0xCAFEBABE << i % 268435456, 0xFEE1DEAD << i % 268435456);
    }
}