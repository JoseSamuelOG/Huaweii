#include <stdio.h>
#include <string.h>

int backstrcmp (const void *s1, const void *s2) {
    #ifdef DEBUG
    printf("backstrcmp have been started\n\n");
    #endif

    size_t n1 = strlen(*(const char **)s1), n2 = strlen(*(const char **)s2);

    #ifdef DEBUG
    printf("%d\t%d\n", n1, n2);
    #endif 

    for (; n1 > 0 && n2 > 0; --n1, --n2) {
        #ifdef DEBUG
        printf("<%d> %s\t<%d> %s\n", n1, *(const char **)s1, n2, *(const char **)s2);
        #endif
        if (*(*(const char **)s1 + n1 - 1) != *(*(const char **)s2 + n2 - 1)) {
            #ifdef DEBUG
            printf("%c\t-\t%c\t=\t%d\n", *(*(const char **)s1 + n1 - 1), *(*(const char **)s2 + n2 - 1), *(*(const char **)s1 + n1 - 1) - *(*(const char **)s2 + n2 - 1));
            #endif

            return *(*(const char **)s1 + n1 - 1) - *(*(const char **)s2 + n2 - 1);
        }
    }
    return n1 - n2;
}