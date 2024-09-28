#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main() {
    char *buf = NULL;
    char quit = 'q';
    size_t num = 0;
    size_t sum = 0;

    printf("To quit press q\n\n");
    printf("How many bytes do you want to allocate to the memory?\n");
    while(getchar() != quit) {
        printf("How many bytes do you want to allocate for memory?\n");
        scanf("%d", &num);

        sum += num;
        buf = (char *)calloc(num, sizeof(char));

        printf("Memory allocated successfully\n");

        for (size_t i = 0; i < sum; ++i) {
            printf("buf[i] = %c\n", buf[i] + '0');
        }
    }

    printf("Thanks for training, brachhoooo!!\nYou allocated %d bytes\n", sum);
    free(buf);
}
